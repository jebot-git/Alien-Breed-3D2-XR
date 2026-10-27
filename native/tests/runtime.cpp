#include "runtime.hpp"
#include "controls.hpp"
#include "original.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <zlib.h>
using namespace ab3d2;
namespace fs = std::filesystem;
void require(bool ok, const char *message) {
  if (!ok)
    throw std::runtime_error(message);
}
std::vector<uint8_t> snapshot() {
  std::vector<uint8_t> out{Mem::RAM.begin(), Mem::RAM.begin() + Mem::cursor};
  // Original profiling timestamps measure wall time rather than simulation.
  std::fill(out.begin() + SystemBss::Sys_FrameTimeECV_q,
            out.begin() + SystemBss::Sys_FrameNumber_l, uint8_t{});
  return out;
}
int main(int argc, char **argv) {
  try {
    require(argc == 3, "Pass assets and scratch directory");
    fs::path scratch = argv[2];
    fs::create_directories(scratch);
    Runtime game(argv[1]);
    game.loadLevel(0);
    auto initial = game.player();
    require(initial.health > 0 && initial.ceilingY > initial.floorY,
            "Invalid initial native player");
    for (int tick = 0; tick < 60; tick++) {
      game.clearInput();
      game.key(Key::Forward, tick < 30);
      game.key(Key::Fire, tick >= 30);
      game.tick();
    }
    auto savedPlayer = game.player();
    auto savedTicks = game.ticks();
    game.clearInput();
    game.save(scratch / "test.ab2xr");
    auto replay = [&] {
      for (int tick = 0; tick < 40; tick++) {
        game.clearInput();
        game.key(Key::Right, tick < 20);
        game.key(Key::Fire, tick >= 20);
        game.tick();
      }
      return snapshot();
    };
    auto expected = replay();
    game.load(scratch / "test.ab2xr");
    require(game.ticks() == savedTicks && game.player().eye == savedPlayer.eye,
            "Save did not restore player/tick");
    auto actual = replay();
    if (actual != expected) {
      int differences = 0;
      for (size_t n = 0; n < std::min(actual.size(), expected.size()); n++)
        if (actual[n] != expected[n]) {
          if (differences++ < 12)
            std::cerr << "Replay RAM " << n << ": " << int(actual[n])
                      << " != " << int(expected[n]) << "\n";
        }
      throw std::runtime_error("Save/replay is not deterministic: " +
                               std::to_string(differences) + " RAM bytes");
    }
    std::ofstream(scratch / "broken.ab2xr") << "broken";
    auto before = game.player();
    try {
      game.load(scratch / "broken.ab2xr");
      throw std::logic_error("Accepted broken save");
    } catch (const std::runtime_error &) {
    }
    require(game.player().eye == before.eye,
            "Rejected load changed player state");
    game.tick();
    Mem::ww(PlayerBss::Plr1_Health_w, 73);
    Mem::ww(PlayerBss::Plr1_AmmoCounts_vw, 91);
    Mem::ww(PlayerBss::Plr1_Weapons_vb + 4, 255);
    game.loadLevel(1, true);
    require(game.player().health == 73 &&
                Mem::uw(PlayerBss::Plr1_AmmoCounts_vw) == 91 &&
                Mem::uw(PlayerBss::Plr1_Weapons_vb + 4) == 255,
            "Campaign inventory did not carry");
    for (int level = 0; level < 16; level++) {
      game.loadLevel(level);
      game.tick();
      require(!game.finished() && game.ticks() == 1,
              "Level worker stopped unexpectedly");
    }
    game.loadLevel(0);
    Mem::ww(HiresData::Lvl_ExitZoneID_w, game.player().zone);
    for (int n = 0; n < 20 && game.phase() == 0; n++)
      game.tick();
    require(game.phase() == 1,
            "Original exit did not enter successful intermission");
    game.skipIntermission();
    for (int n = 0; n < 4 && !game.finished(); n++)
      game.tick();
    require(game.finished(), "Successful intermission did not complete");
    game.loadLevel(0);
    Mem::ww(PlayerBss::Plr1_Health_w, 0);
    for (int n = 0; n < 400 && game.phase() == 0; n++)
      game.tick();
    require(game.phase() == 2, "Original death did not enter intermission");
    game.skipIntermission();
    for (int n = 0; n < 4 && !game.finished(); n++)
      game.tick();
    require(game.finished(), "Original end music did not finish");
    std::cout << "PASS native worker lifecycle, exact save/replay, rejected "
                 "save, campaign carry, all16 level restarts and original "
                 "death/intermission\n";
  } catch (const std::exception &e) {
    std::cerr << e.what() << "\n";
    return 1;
  }
}
