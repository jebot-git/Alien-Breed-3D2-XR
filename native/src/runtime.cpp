#include "runtime.hpp"
#include "audio_bridge.hpp"
#include "controls.hpp"
#include "core_state.hpp"
#include "original.hpp"
#include <atomic>
#include <exception>
#include <fstream>
#include <nlohmann/json.hpp>
#include <semaphore>
#include <zlib.h>
using Json = nlohmann::json;
namespace ab3d2 {
namespace {
void put64(std::vector<uint8_t> &out, uint64_t value) {
  for (int n = 7; n >= 0; n--)
    out.push_back(uint8_t(value >> (n * 8)));
}
uint64_t get64(const std::vector<uint8_t> &bytes, size_t &pos) {
  if (pos + 8 > bytes.size())
    throw std::runtime_error("Truncated save");
  uint64_t v = 0;
  for (int n = 0; n < 8; n++)
    v = (v << 8) | bytes[pos++];
  return v;
}
std::vector<uint8_t> readFile(const std::filesystem::path &path, size_t limit) {
  std::ifstream in(path, std::ios::binary | std::ios::ate);
  if (!in)
    throw std::runtime_error("Cannot open " + path.string());
  auto length = in.tellg();
  if (length < 0 || uint64_t(length) > limit)
    throw std::runtime_error("Invalid file size");
  std::vector<uint8_t> out(size_t(length), uint8_t{});
  in.seekg(0);
  in.read(reinterpret_cast<char *>(out.data()), length);
  if (!in)
    throw std::runtime_error("Truncated file");
  return out;
}
int binding(Key key) {
  switch (key) {
  case Key::Forward:
    return ControlloopData::forward_key;
  case Key::Backward:
    return ControlloopData::backward_key;
  case Key::Left:
    return ControlloopData::sidestep_left_key;
  case Key::Right:
    return ControlloopData::sidestep_right_key;
  case Key::Run:
    return ControlloopData::run_key;
  case Key::Fire:
    return ControlloopData::fire_key;
  case Key::Use:
    return ControlloopData::operate_key;
  case Key::Jump:
    return ControlloopData::jump_key;
  case Key::Duck:
    return ControlloopData::duck_key;
  }
  throw std::runtime_error("Invalid input binding");
}
void restoreChips(const Json &chips) {
  for (auto [name, destination] : {std::pair{"audLC", &CustomChips::audLC},
                                   {"audLEN", &CustomChips::audLEN},
                                   {"audPER", &CustomChips::audPER},
                                   {"audVOL", &CustomChips::audVOL},
                                   {"dmaLC", &CustomChips::dmaLC},
                                   {"dmaLEN", &CustomChips::dmaLEN}})
    *destination = chips.at(name).get<std::array<int32_t, 4>>();
  CustomChips::dmaTrig = chips.at("dmaTrig").get<std::array<bool, 4>>();
  CustomChips::dmacon = chips.at("dmacon");
  CustomChips::ciaaPra = chips.at("ciaaPra");
  CustomChips::joy0dat = CustomChips::joy1dat = 0;
  CustomChips::mouseLeftPressed = CustomChips::mouseRightPressed =
      CustomChips::fire1Pressed = false;
}
} // namespace
struct Runtime::Impl {
  std::filesystem::path assets;
  Json manifest;
  std::vector<uint64_t> defaults;
  std::binary_semaphore ready{0}, advance{0};
  std::thread worker;
  std::atomic_bool ended{true};
  std::exception_ptr error;
  int current = 0;
  uint64_t count = 0;
  Impl(std::filesystem::path root)
      : assets(std::move(root)), defaults(captureCoreGlobals()) {
    std::ifstream file(assets / "native/manifest.json");
    if (!file)
      throw std::runtime_error("Original native game-data pack is missing");
    file >> manifest;
    if (manifest.value("version", 0) != 1 ||
        manifest.value("layout", "") != coreLayoutId())
      throw std::runtime_error(
          "Native game-data layout does not match this build");
  }
  void stop() {
    if (worker.joinable()) {
      Hires::headlessStop = true;
      advance.release();
      worker.join();
    }
    while (ready.try_acquire()) {
    }
    while (advance.try_acquire()) {
    }
    Hires::frameSync = nullptr;
  }
  void await() {
    if (!ready.try_acquire_for(std::chrono::seconds(10)))
      throw std::runtime_error(
          "Original native loop did not reach its frame boundary");
    if (error)
      std::rethrow_exception(error);
  }
  void start() {
    error = nullptr;
    ended = false;
    Hires::headless = true;
    Hires::headlessStop = false;
    Hires::presentationPhase = 0;
    Hires::loopFrameLimit = -1;
    Hires::frameSync = [this] {
      ready.release();
      advance.acquire();
    };
    worker = std::thread([this] {
      try {
        Hires::frameSync();
        if (!Hires::headlessStop) {
          Hires::markVisibleAndWorry();
          Hires::game_main_loop();
        }
      } catch (...) {
        error = std::current_exception();
      }
      ended = true;
      ready.release();
    });
    await();
  }
};
Runtime::Runtime(std::filesystem::path assets)
    : p(std::make_unique<Impl>(std::move(assets))) {}
Runtime::~Runtime() { p->stop(); }
void Runtime::loadLevel(int index, bool carry) {
  if (index < 0 || index >= 16)
    throw std::runtime_error("Invalid level");
  std::array<uint8_t, 44> inventory{};
  std::array<uint8_t, 24> equipment{};
  if (carry) {
    std::copy_n(Mem::RAM.begin() + PlayerBss::Plr1_Health_w, 44,
                inventory.begin());
    std::copy_n(Mem::RAM.begin() + PlayerBss::Plr1_Shield_w, 24,
                equipment.begin());
  }
  const auto &record = p->manifest.at("levels").at(index);
  auto bytes =
      readFile(p->assets / "native" / record.at("file").get<std::string>(),
               Mem::RAM_SIZE);
  if (bytes.size() != record.at("size").get<size_t>() ||
      crc32(0, bytes.data(), bytes.size()) !=
          record.at("crc32").get<uint32_t>())
    throw std::runtime_error("Original game-data checksum failed");
  // Validate host registers before stopping the current playable level.
  auto chips = record.at("chips");
  for (auto name :
       {"audLC", "audLEN", "audPER", "audVOL", "dmaLC", "dmaLEN", "dmaTrig"})
    if (chips.at(name).size() != 4)
      throw std::runtime_error("Invalid original audio-register state");
  p->stop();
  if (audio_bridge::reset)
    audio_bridge::reset(false);
  restoreCoreGlobals(p->defaults);
  std::fill(Mem::RAM.begin(), Mem::RAM.end(), 0);
  std::copy(bytes.begin(), bytes.end(), Mem::RAM.begin());
  Mem::cursor = bytes.size();
  p->current = index;
  p->count = 0;
  restoreChips(chips);
  if (audio_bridge::reset)
    audio_bridge::reset(true);
  if (carry) {
    std::copy(inventory.begin(), inventory.end(),
              Mem::RAM.begin() + PlayerBss::Plr1_Health_w);
    std::copy(equipment.begin(), equipment.end(),
              Mem::RAM.begin() + PlayerBss::Plr1_Shield_w);
  }
  clearInput();
  p->start();
}
void Runtime::tick() {
  if (p->ended) {
    if (p->error)
      std::rethrow_exception(p->error);
    return;
  }
  p->advance.release();
  p->await();
  p->count++;
}
void Runtime::key(Key key, bool down) {
  int address = binding(key);
  Mem::wb(TablesBss::KeyMap_vb + Mem::ub(address), down ? 255 : 0);
}
void Runtime::clearInput() {
  controls::input = {};
  std::fill_n(Mem::RAM.begin() + TablesBss::KeyMap_vb, 128, uint8_t{});
}
void Runtime::setYaw(float radians) {
  int angle = int(std::lround(radians / 6.283185307179586 * 8192)) & 8190;
  Mem::ww(PlayerBss::Plr1_AngPos_w, angle);
  Mem::ww(PlayerBss::Plr1_SnapAngPos_w, angle);
  Mem::ww(PlayerBss::Plr1_SnapAngSpd_w, 0);
}
void Runtime::cycleWeapon(int direction) {
  int gun = Mem::ub(PlayerBss::Plr1_GunSelected_b);
  for (int n = 0; n < 10; n++) {
    gun = (gun + direction + 10) % 10;
    if (Mem::uw(PlayerBss::Plr1_Weapons_vb + gun * 2)) {
      Mem::wb(PlayerBss::Plr1_GunSelected_b, gun);
      Player::plr_ShowGunName(PlayerBss::Plr1_Data);
      break;
    }
  }
}
PlayerState Runtime::player() const {
  PlayerState state;
  state.eye = {Mem::l(PlayerBss::Plr1_XOff_l) / 65536.f / 64,
               -Mem::l(PlayerBss::Plr1_YOff_l) / 8192.f,
               -Mem::l(PlayerBss::Plr1_ZOff_l) / 65536.f / 64};
  state.yaw = Mem::uw(PlayerBss::Plr1_AngPos_w) / 8192.f * 6.283185307179586f;
  state.feetY = -(Mem::l(PlayerBss::Plr1_TmpYOff_l) +
                  Mem::l(PlayerBss::plr1_TmpHeight_l)) /
                8192.f;
  int zone = Mem::l(PlayerBss::Plr1_ZonePtr_l);
  bool upper = Mem::b(PlayerBss::Plr1_StoodInTop_b);
  state.floorY =
      -Mem::l(zone + (upper ? Defs::ZoneT_UpperFloor_l : Defs::ZoneT_Floor_l)) /
      8192.f;
  state.ceilingY =
      -Mem::l(zone + (upper ? Defs::ZoneT_UpperRoof_l : Defs::ZoneT_Roof_l)) /
      8192.f;
  state.feetY = std::max(state.feetY, state.floorY);
  state.health = Mem::uw(PlayerBss::Plr1_Health_w);
  state.gun = Mem::ub(PlayerBss::Plr1_GunSelected_b);
  state.zone = Mem::uw(PlayerBss::Plr1_Zone_w);
  return state;
}
int Runtime::ammunition() const {
  int type =
      Mem::uw(Mem::l(HiresData::GLF_DatabasePtr_l) + Defs::GLFT_ShootDefs_l +
              Mem::ub(PlayerBss::Plr1_GunSelected_b) * 8);
  return Mem::uw(PlayerBss::Plr1_AmmoCounts_vw + type * 2);
}

int Runtime::level() const { return p->current; }
uint64_t Runtime::ticks() const { return p->count; }
bool Runtime::finished() const { return p->ended; }
int Runtime::phase() const { return Hires::presentationPhase; }
void Runtime::skipIntermission() {
  if (phase() != 0 && !finished())
    Mem::wb(Music::reachedend, 255);
}
void Runtime::save(const std::filesystem::path &target) {
  if (finished() || phase() != 0)
    throw std::runtime_error("Save is available during gameplay");
  std::vector<uint8_t> payload;
  put64(payload, p->current);
  put64(payload, p->count);
  auto globals = captureCoreGlobals();
  put64(payload, globals.size());
  for (auto value : globals)
    put64(payload, value);
  put64(payload, Mem::cursor);
  payload.insert(payload.end(), Mem::RAM.begin(),
                 Mem::RAM.begin() + Mem::cursor);
  uLongf size = compressBound(payload.size());
  std::vector<uint8_t> compressed(size);
  if (compress2(compressed.data(), &size, payload.data(), payload.size(), 3) !=
      Z_OK)
    throw std::runtime_error("Cannot compress save");
  compressed.resize(size);
  if (!target.parent_path().empty())
    std::filesystem::create_directories(target.parent_path());
  auto temporary = target;
  temporary += ".tmp";
  std::ofstream out(temporary, std::ios::binary | std::ios::trunc);
  std::string magic = "AB2XRCPP1\n" + std::string(coreLayoutId()) + "\n";
  out.write(magic.data(), magic.size());
  std::vector<uint8_t> lengths;
  put64(lengths, payload.size());
  out.write(reinterpret_cast<char *>(lengths.data()), lengths.size());
  out.write(reinterpret_cast<char *>(compressed.data()), compressed.size());
  out.close();
  if (!out)
    throw std::runtime_error("Cannot write save");
  std::filesystem::rename(temporary, target);
}
void Runtime::load(const std::filesystem::path &source) {
  auto file = readFile(source, Mem::RAM_SIZE + 65536);
  std::string magic = "AB2XRCPP1\n" + std::string(coreLayoutId()) + "\n";
  if (file.size() < magic.size() + 8 ||
      !std::equal(magic.begin(), magic.end(), file.begin()))
    throw std::runtime_error("Incompatible native save");
  size_t position = magic.size();
  auto size = get64(file, position);
  if (size > Mem::RAM_SIZE + 65536)
    throw std::runtime_error("Invalid save size");
  std::vector<uint8_t> payload(size);
  uLongf unpacked = size;
  if (uncompress(payload.data(), &unpacked, file.data() + position,
                 file.size() - position) != Z_OK ||
      unpacked != size)
    throw std::runtime_error("Corrupt native save");
  position = 0;
  int level = get64(payload, position);
  auto ticks = get64(payload, position), count = get64(payload, position);
  if (level < 0 || level >= 16 || count != p->defaults.size())
    throw std::runtime_error("Invalid save state");
  std::vector<uint64_t> globals;
  for (uint64_t n = 0; n < count; n++)
    globals.push_back(get64(payload, position));
  auto length = get64(payload, position);
  if (length > Mem::RAM_SIZE || position + length != payload.size())
    throw std::runtime_error("Invalid original RAM state");
  loadLevel(level);
  std::copy_n(payload.begin() + position, length, Mem::RAM.begin());
  std::fill(Mem::RAM.begin() + length, Mem::RAM.end(), 0);
  Mem::cursor = length;
  restoreCoreGlobals(globals);
  p->count = ticks;
  clearInput();
  ScreenC::Vid_LoadMainPalette();
  if (audio_bridge::reset)
    audio_bridge::reset(true);
}
} // namespace ab3d2
