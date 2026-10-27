#include "audio.hpp"
#include "audio_bridge.hpp"
#include "controls.hpp"
#include "domed.hpp"
#include "math.hpp"
#include "render.hpp"
#include "runtime.hpp"
#include "xr.hpp"
#include <GL/glew.h>
#include <SDL.h>
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <set>
using namespace ab3d2;
namespace fs = std::filesystem;
namespace {
struct Options {
  std::string mode = "auto";
  bool standalone = false, noSound = false, testPlay = false, fixedStep = false,
       x11 = false;
  int level = 0, frames = 0;
  fs::path assets, report;
};
Options options(int argc, char **argv) {
  Options out;
  for (int n = 1; n < argc; n++) {
    std::string arg = argv[n];
    auto value = [&]() {
      if (++n >= argc)
        throw std::runtime_error("Missing value for " + arg);
      return std::string(argv[n]);
    };
    if (arg == "--desktop")
      out.mode = "desktop";
    else if (arg == "--xr")
      out.mode = "xr";
    else if (arg == "--standalone")
      out.standalone = true;
    else if (arg == "--nosound")
      out.noSound = true;
    else if (arg == "--test-play")
      out.testPlay = true;
    else if (arg == "--fixed-step")
      out.fixedStep = true;
    else if (arg == "--x11")
      out.x11 = true;
    else if (arg == "--assets")
      out.assets = value();
    else if (arg == "--report")
      out.report = value();
    else if (arg == "--frames")
      out.frames = std::stoi(value());
    else if (arg == "--level") {
      auto v = value();
      out.level = v.size() == 1 && std::isalpha(v[0]) ? std::tolower(v[0]) - 'a'
                                                      : std::stoi(v) - 1;
    } else if (arg == "--help") {
      std::cout
          << "Alien Breed 3D II XR (native C++)\n--desktop | --xr  "
             "--standalone  --level 1..16  --assets PATH  --nosound\nDesktop: "
             "WASD, mouse aim/fire, F use, Space jump, Q/E weapons, Escape "
             "pause, F5/F9 save/load.\nXR: left stick head-oriented movement, "
             "right stick turn, trigger fire, A/X use, Y/B weapons, "
             "right-stick click jump, left menu pause, left grip support.\n";
      std::exit(0);
    } else
      throw std::runtime_error("Unknown argument " + arg);
  }
  if (out.level < 0 || out.level >= 16 || out.frames < 0)
    throw std::runtime_error("Invalid level/frame count");
  return out;
}
fs::path stateRoot() {
  if (const char *root = std::getenv("XDG_STATE_HOME"))
    return fs::path(root) / "alien-breed3d2-xr";
  if (const char *home = std::getenv("HOME"))
    return fs::path(home) / ".local/state/alien-breed3d2-xr";
  return fs::temp_directory_path() / "alien-breed3d2-xr";
}
fs::path configPath() {
  if (const char *root = std::getenv("XDG_CONFIG_HOME"))
    return fs::path(root) / "alien-breed3d2-xr/settings.json";
  if (const char *home = std::getenv("HOME"))
    return fs::path(home) / ".config/alien-breed3d2-xr/settings.json";
  return stateRoot() / "settings.json";
}
nlohmann::json readJson(const fs::path &path) {
  std::ifstream input(path);
  if (!input)
    throw std::runtime_error("Cannot open " + path.string());
  nlohmann::json value;
  input >> value;
  return value;
}
fs::path assetsPath(const Options &opt, const char *argv0) {
  if (!opt.assets.empty())
    return fs::absolute(opt.assets);
  if (const char *root = std::getenv("AB3D2_XR_ASSETS"))
    return root;
  std::error_code ec;
  auto exe = fs::read_symlink("/proc/self/exe", ec);
  if (ec)
    exe = fs::absolute(argv0);
  for (auto root :
       {exe.parent_path() / "assets",
        exe.parent_path() / "../share/alien-breed3d2-xr",
        fs::current_path() / "assets", exe.parent_path() / "../assets"})
    if (fs::is_regular_file(root / "native/manifest.json"))
      return fs::weakly_canonical(root);
  throw std::runtime_error("Original game data not found; use --assets PATH");
}
struct Window {
  SDL_Window *window = nullptr;
  SDL_GLContext context = nullptr;
  Window(bool vr) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS))
      throw std::runtime_error(SDL_GetError());
    SDL_SetHint("SDL_APP_ID", "alien-breed3d2-xr");
    SDL_SetHint("SDL_VIDEO_WAYLAND_WMCLASS", "alien-breed3d2-xr");
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
                        SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    window = SDL_CreateWindow("Alien Breed 3D II XR", SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, 1280, 800,
                              SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    if (!window)
      throw std::runtime_error(SDL_GetError());
    context = SDL_GL_CreateContext(window);
    if (!context)
      throw std::runtime_error(SDL_GetError());
    glewExperimental = GL_TRUE;
    auto error = glewInit();
    if (error != GLEW_OK && !GLEW_VERSION_3_3)
      throw std::runtime_error("OpenGL 3.3 is required");
    while (glGetError() != GL_NO_ERROR) {
    }
    SDL_GL_SetSwapInterval(vr ? 0 : 1);
    std::cerr << "Native renderer: " << glGetString(GL_RENDERER)
              << "; video=" << SDL_GetCurrentVideoDriver() << "\n";
  }
  ~Window() {
    if (context)
      SDL_GL_DeleteContext(context);
    if (window)
      SDL_DestroyWindow(window);
    SDL_Quit();
  }
};
float deadzone(float v) {
  return std::abs(v) < .15f ? 0 : std::copysign((std::abs(v) - .15f) / .85f, v);
}
std::array<float, 3> point(const Matrix &m) { return {m[12], m[13], m[14]}; }
std::array<float, 3> forward(const Matrix &m) { return {-m[8], -m[9], -m[10]}; }
Matrix rotationX(float a) {
  auto m = Identity;
  float c = std::cos(a), s = std::sin(a);
  m[5] = c;
  m[6] = s;
  m[9] = -s;
  m[10] = c;
  return m;
}
Matrix supportPose(Matrix right, const Matrix &left, bool enabled) {
  if (!enabled)
    return right;
  auto f = forward(right);
  std::array<float, 3> d{left[12] - right[12], left[13] - right[13],
                         left[14] - right[14]};
  float length = std::sqrt(d[0] * d[0] + d[1] * d[1] + d[2] * d[2]);
  if (length < .12f || length > .8f ||
      (d[0] * f[0] + d[1] * f[1] + d[2] * f[2]) < length * .4f)
    return right;
  for (auto &v : d)
    v /= length;
  std::array<float, 3> up{right[4], right[5], right[6]},
      r{d[1] * up[2] - d[2] * up[1], d[2] * up[0] - d[0] * up[2],
        d[0] * up[1] - d[1] * up[0]};
  float norm = std::sqrt(r[0] * r[0] + r[1] * r[1] + r[2] * r[2]);
  if (norm < .05f)
    return right;
  for (auto &v : r)
    v /= norm;
  up = {r[1] * d[2] - r[2] * d[1], r[2] * d[0] - r[0] * d[2],
        r[0] * d[1] - r[1] * d[0]};
  for (int i = 0; i < 3; i++) {
    right[i] = r[i];
    right[4 + i] = up[i];
    right[8 + i] = -d[i];
  }
  return right;
}
} // namespace
int main(int argc, char **argv) {
  try {
    auto opt = options(argc, argv);
    tempest::DomeLaunch launch;
    if (!opt.standalone)
      launch = tempest::domeLaunch(opt.x11 ? "desktop" : opt.mode);
    bool vr = opt.mode == "xr" ||
              (opt.mode == "auto" && (launch.managed ? launch.xr : true));
    if (opt.x11 && launch.managed)
      vr = false;
    if (opt.x11)
      SDL_setenv("SDL_VIDEODRIVER", "x11", 1);
    else if (!std::getenv("SDL_VIDEODRIVER") && std::getenv("WAYLAND_DISPLAY"))
      SDL_setenv("SDL_VIDEODRIVER", "wayland", 0);
    tempest::DomeLink dome(launch);
    Window surface(vr);
    Runtime game(assetsPath(opt, argv[0]));
    game.loadLevel(opt.level);
    Renderer renderer;
    renderer.loadAssets(assetsPath(opt, argv[0]));
    renderer.loadLevel(opt.level);
    renderer.sync();
    audio_bridge::ensureStarted = audio::ensureStarted;
    audio_bridge::needsBuffer = audio::needsBuffer;
    audio_bridge::queueFromPaula = audio::queueFromPaula;
    audio_bridge::stop = audio::stop;
    audio_bridge::reset = audio::reset;
    nlohmann::json preferences = nlohmann::json::object();
    if (!opt.frames && fs::exists(configPath())) {
      try {
        preferences = readJson(configPath());
      } catch (const std::exception &e) {
        std::cerr << "Settings: " << e.what() << "; using defaults\n";
      }
    }
    bool sound = !opt.noSound && preferences.value("sound", true);
    audio::setEnabled(sound);
    std::unique_ptr<XR> xr;
    bool lease = false;
    if (vr) {
      if (launch.managed) {
        dome.begin();
        lease = true;
      }
      xr = std::make_unique<XR>();
      xr->initialize(surface.window);
    }
    enum Page { Title, Story, Play, Result, Ending, Credits };
    Page page = opt.testPlay ? Play : Title;
    bool paused = false, quit = false, armed = opt.testPlay,
         smooth = preferences.value("smooth_turn", true),
         twoHand = preferences.value("two_hand", true), snapReady = true,
         menuBefore = false, selectBefore = false, navBefore = false,
         prevBefore = false, nextBefore = false, mouseFire = false,
         pendingContinue = false;
    const auto story = readJson(assetsPath(opt, argv[0]) / "menu/story.json");
    size_t endingPage = 0;
    int selected = 0, titleSelected = 0, selectedLevel = opt.level, frame = 0;
    std::string notice;
    std::set<SDL_Keycode> keys;
    float yaw = game.player().yaw, pitch = 0, virtualYaw = 0,
          neutralHeight = 1.65f, standingHeight = 1.65f;
    bool neutralReady = false, stageReady = false;
    XrVector3f lastStage{};
    std::array<float, 3> pendingRoom{};
    double accumulator = 0;
    uint64_t last = SDL_GetPerformanceCounter();
    Matrix stageWorld = Identity, headWorld = Identity, weaponWorld = Identity;
    bool trackedWeapon = false, hadXRFocus = false;
    auto panel = [&]() {
      Panel out;
      if (paused) {
        out.kind = Panel::Pause;
        out.caption = "PAUSED";
        out.selection = selected;
        out.lines = {"Resume",
                     std::string("Turn: ") + (smooth ? "Smooth" : "Snap"),
                     "Save game",
                     "Load game",
                     "Reset floor / height",
                     std::string("Two-hand hold: ") + (twoHand ? "On" : "Off"),
                     std::string("Sound: ") + (sound ? "On" : "Off"),
                     "Restart level",
                     "Quit"};
        if (!notice.empty())
          out.lines.push_back(notice);
      } else if (page == Title) {
        out.kind = Panel::Title;
        out.selection = titleSelected;
        out.lines = {"New game", "Load game",
                     std::string("Level ") + char('A' + selectedLevel),
                     "Credits", "Quit"};
        if (!notice.empty())
          out.lines.push_back(notice);
      } else if (page == Story) {
        out.kind = Panel::Story;
        out.caption = std::string("LEVEL ") + char('A' + game.level());
        for (const auto &line : story.at("intro").at(game.level()))
          out.lines.push_back(line.value("text", ""));
        out.lines.push_back("");
        out.lines.push_back("Trigger / Enter to begin");
      } else if (page == Ending) {
        out.kind = Panel::Ending;
        out.caption = "THE END";
        size_t count = story.at("end").size();
        for (size_t n = endingPage * 16;
             n < std::min(count, (endingPage + 1) * 16); n++)
          out.lines.push_back(story.at("end").at(n).value("text", ""));
        out.lines.push_back("");
        out.lines.push_back("Trigger / Enter to continue");
      } else if (page == Credits) {
        out.kind = Panel::Pause;
        out.caption = "CREDITS";
        out.lines = {"Alien Breed 3D II: The Killing Grounds",
                     "Original game: Team17",
                     "Original engine: Andy Clitheroe",
                     "Maintained source: mheyer32 + contributors",
                     "Reference: guillaumemonet",
                     "Native XR: de-xr",
                     "",
                     "Trigger / Enter to return"};
      } else if (page == Result) {
        out.kind = Panel::Pause;
        out.caption = game.player().health > 0 ? "LEVEL COMPLETE" : "GAME OVER";
        out.lines = {"Trigger / Enter to continue"};
      } else
        out.kind = Panel::Gameplay;
      renderer.setPanel(out);
    };
    auto resetInput = [&]() {
      game.clearInput();
      armed = false;
      pendingRoom = {};
      stageReady = false;
      accumulator = 0;
    };
    auto beginLevel = [&](int level, bool carry) {
      game.loadLevel(level, carry);
      renderer.loadLevel(level);
      renderer.sync();
      selectedLevel = level;
      page = Story;
      paused = false;
      pendingContinue = false;
      yaw = game.player().yaw;
      resetInput();
    };
    auto save = [&]() {
      try {
        game.save(stateRoot() / "slot1.ab2xr");
        notice = "Game saved";
      } catch (const std::exception &e) {
        notice = e.what();
      }
    };
    auto load = [&]() {
      try {
        game.load(stateRoot() / "slot1.ab2xr");
        renderer.loadLevel(game.level());
        renderer.sync();
        page = Play;
        paused = false;
        yaw = game.player().yaw;
        resetInput();
        notice = "Game loaded";
      } catch (const std::exception &e) {
        notice = e.what();
      }
    };
    auto resume = [&]() {
      if (lease && dome.suspended())
        dome.begin();
      if (xr)
        xr->setVisible(true);
      paused = false;
      resetInput();
    };
    auto resetHeight = [&]() {
      if (xr && xr->tracking().headValid) {
        neutralHeight = xr->headPose().position.y;
        standingHeight = neutralHeight > .5f ? neutralHeight : 1.65f;
        neutralReady = true;
        stageReady = false;
        pendingRoom = {};
        notice = "Floor / height reset";
      }
    };
    panel();
    while (!quit) {
      SDL_Event event;
      while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT)
          quit = true;
        if (event.type == SDL_WINDOWEVENT &&
            event.window.event == SDL_WINDOWEVENT_FOCUS_LOST && !xr) {
          paused = true;
          keys.clear();
          mouseFire = false;
          resetInput();
        }
        if (event.type == SDL_MOUSEBUTTONDOWN &&
            event.button.button == SDL_BUTTON_LEFT)
          mouseFire = true;
        if (event.type == SDL_MOUSEBUTTONUP &&
            event.button.button == SDL_BUTTON_LEFT)
          mouseFire = false;
        if (event.type == SDL_KEYUP)
          keys.erase(event.key.keysym.sym);
        if (event.type == SDL_KEYDOWN && !event.key.repeat) {
          auto key = event.key.keysym.sym;
          if ((event.key.keysym.mod & KMOD_GUI) &&
              (key == SDLK_q || key == SDLK_w)) {
            quit = true;
            continue;
          }
          keys.insert(key);
          if (key == SDLK_ESCAPE) {
            if (paused)
              resume();
            else {
              paused = true;
              selected = 0;
              resetInput();
            }
          }
          if (key == SDLK_F5)
            save();
          if (key == SDLK_F9)
            load();
          if (key == SDLK_r)
            resetHeight();
          if (key == SDLK_UP) {
            if (paused)
              selected = (selected + 8) % 9;
            else if (page == Title)
              titleSelected = (titleSelected + 4) % 5;
          }
          if (key == SDLK_DOWN) {
            if (paused)
              selected = (selected + 1) % 9;
            else if (page == Title)
              titleSelected = (titleSelected + 1) % 5;
          }
          if (page == Title && titleSelected == 2 &&
              (key == SDLK_LEFT || key == SDLK_RIGHT))
            selectedLevel = (selectedLevel + (key == SDLK_RIGHT ? 1 : 15)) % 16;
        }
        if (event.type == SDL_MOUSEMOTION && !xr && page == Play && !paused) {
          yaw += event.motion.xrel * .002f;
          pitch = std::clamp(pitch - event.motion.yrel * .002f, -1.5f, 1.5f);
        }
      }
      if (quit)
        break;
      if (xr && !xr->beginFrame())
        break;
      auto now = SDL_GetPerformanceCounter();
      double dt =
          std::min(.1, double(now - last) / SDL_GetPerformanceFrequency());
      last = now;
      if (opt.fixedStep)
        dt = .02;
      const Tracking *tracking = xr ? &xr->tracking() : nullptr;
      bool focused = !xr || xr->focused();
      if (xr) {
        if (hadXRFocus && !focused && page == Play && !paused) {
          paused = true;
          selected = 0;
          resetInput();
          notice = "XR focus lost";
        }
        hadXRFocus = focused;
      }
      if (lease && !dome.active() && !paused) {
        paused = true;
        selected = 0;
        resetInput();
        xr->setVisible(false);
        notice = "Press Enter to resume XR";
      }
      float moveF = (keys.contains(SDLK_w) ? 1.f : 0) -
                    (keys.contains(SDLK_s) ? 1.f : 0),
            moveR = (keys.contains(SDLK_d) ? 1.f : 0) -
                    (keys.contains(SDLK_a) ? 1.f : 0),
            turn = (keys.contains(SDLK_RIGHT) ? 1.f : 0) -
                   (keys.contains(SDLK_LEFT) ? 1.f : 0),
            nav = 0;
      bool fire = mouseFire || keys.contains(SDLK_LCTRL),
           use = keys.contains(SDLK_f), jump = keys.contains(SDLK_SPACE),
           menu = false, previous = keys.contains(SDLK_q),
           next = keys.contains(SDLK_e);
      if (tracking) {
        moveF = deadzone(tracking->move.y);
        moveR = deadzone(tracking->move.x);
        turn = deadzone(tracking->turn.x);
        nav = std::abs(tracking->turn.y) > std::abs(tracking->move.y)
                  ? tracking->turn.y
                  : tracking->move.y;
        fire = tracking->fire;
        use = tracking->use;
        jump = tracking->jump;
        menu = tracking->menu;
        previous = tracking->previousWeapon;
        next = tracking->nextWeapon;
      }
      if (menu && !menuBefore) {
        if (paused)
          resume();
        else {
          paused = true;
          selected = 0;
          resetInput();
        }
      }
      menuBefore = menu;
      bool activate = fire || use || keys.contains(SDLK_RETURN);
      if (!activate && !jump && !previous && !next && std::abs(moveF) < .1f &&
          std::abs(moveR) < .1f && std::abs(turn) < .1f)
        armed = true;
      if ((paused || page == Title) && std::abs(nav) > .6f && !navBefore) {
        int change = nav > 0 ? -1 : 1;
        if (paused)
          selected = (selected + change + 9) % 9;
        else
          titleSelected = (titleSelected + change + 5) % 5;
      }
      navBefore = std::abs(nav) > .3f;
      if (activate && !selectBefore && armed) {
        if (paused) {
          switch (selected) {
          case 0:
            resume();
            break;
          case 1:
            smooth = !smooth;
            break;
          case 2:
            save();
            break;
          case 3:
            load();
            break;
          case 4:
            resetHeight();
            break;
          case 5:
            twoHand = !twoHand;
            break;
          case 6:
            sound = !sound;
            audio::setEnabled(sound);
            break;
          case 7:
            beginLevel(game.level(), false);
            break;
          case 8:
            quit = true;
            break;
          }
          resetInput();
        } else if (page == Title) {
          if (titleSelected == 0)
            beginLevel(selectedLevel, false);
          else if (titleSelected == 1)
            load();
          else if (titleSelected == 2)
            selectedLevel = (selectedLevel + 1) % 16;
          else if (titleSelected == 3) {
            page = Credits;
            resetInput();
          } else
            quit = true;
        } else if (page == Story) {
          page = Play;
          resetInput();
        } else if (page == Credits) {
          page = Title;
          resetInput();
        } else if (page == Ending) {
          endingPage++;
          if (endingPage * 16 >= story.at("end").size()) {
            beginLevel(0, false);
            page = Title;
            endingPage = 0;
          }
          resetInput();
        } else if (page == Result) {
          pendingContinue = true;
          game.skipIntermission();
          resetInput();
        }
      }
      selectBefore = activate;
      if (xr && tracking->headValid) {
        auto pose = xr->headPose();
        if (!neutralReady) {
          neutralHeight = pose.position.y;
          standingHeight = neutralHeight > .5f ? neutralHeight : 1.65f;
          neutralReady = true;
          virtualYaw = game.player().yaw;
        }
        if (stageReady && page == Play && !paused) {
          float dx = pose.position.x - lastStage.x,
                dz = pose.position.z - lastStage.z;
          if (dx * dx + dz * dz < .0625f) {
            auto rot = rotationY(-virtualYaw);
            pendingRoom[0] += rot[0] * dx + rot[8] * dz;
            pendingRoom[2] += rot[2] * dx + rot[10] * dz;
          }
        }
        lastStage = pose.position;
        stageReady = true;
        if (page == Play && !paused && armed) {
          float amount = turn * float(dt) * 1.8f;
          if (!smooth) {
            amount = 0;
            if (std::abs(turn) > .65f && snapReady) {
              amount = std::copysign(.5235987756f, turn);
              snapReady = false;
            }
            if (std::abs(turn) < .25f)
              snapReady = true;
          }
          virtualYaw += amount;
        }
      } else if (!xr && page == Play && !paused && armed)
        yaw += turn * float(dt) * 1.8f;
      auto poses = [&]() {
        auto player = game.player();
        trackedWeapon = false;
        if (xr && tracking->headValid) {
          auto head = xr->headPose();
          stageWorld = rotationY(-virtualYaw);
          float headHeight = standingHeight + head.position.y - neutralHeight;
          float eyeY = std::clamp(
              player.feetY + headHeight, player.floorY + .06f,
              std::max(player.floorY + .06f, player.ceilingY - .04f));
          stageWorld[12] = player.eye[0] - (stageWorld[0] * head.position.x +
                                            stageWorld[8] * head.position.z);
          stageWorld[13] = eyeY - head.position.y;
          stageWorld[14] = player.eye[2] - (stageWorld[2] * head.position.x +
                                            stageWorld[10] * head.position.z);
          headWorld = multiply(stageWorld, poseMatrix(head));
          if (tracking->valid[1]) {
            weaponWorld = multiply(stageWorld, poseMatrix(tracking->hands[1]));
            trackedWeapon = true;
            if (twoHand && tracking->supportHeld && tracking->gripValid[0])
              weaponWorld = supportPose(
                  weaponWorld,
                  multiply(stageWorld, poseMatrix(tracking->grips[0])), true);
          }
        } else {
          headWorld =
              multiply(translation(player.eye[0], player.eye[1], player.eye[2]),
                       multiply(rotationY(-yaw), rotationX(pitch)));
          weaponWorld = multiply(headWorld, translation(.12f, -.25f, -.32f));
        }
      };
      poses();
      game.clearInput();
      bool playing = page == Play && !paused && armed && focused &&
                     (!xr || tracking->headValid);
      if (playing) {
        if (xr) {
          controls::input.active = true;
          controls::input.forward = moveF;
          controls::input.strafe = moveR;
          controls::input.height =
              1.5f + xr->headPose().position.y - neutralHeight;
          controls::input.roomX = int(std::lround(pendingRoom[0] * 64 * 65536));
          controls::input.roomZ =
              -int(std::lround(pendingRoom[2] * 64 * 65536));
        } else {
          game.key(Key::Forward, moveF > 0);
          game.key(Key::Backward, moveF < 0);
          game.key(Key::Left, moveR < 0);
          game.key(Key::Right, moveR > 0);
          game.key(Key::Run, keys.contains(SDLK_LSHIFT));
        }
        game.key(Key::Fire, fire && (!xr || trackedWeapon));
        game.key(Key::Use, use);
        game.key(Key::Jump, jump);
        game.key(Key::Duck, !xr && keys.contains(SDLK_c));
        if (previous && !prevBefore)
          game.cycleWeapon(-1);
        if (next && !nextBefore)
          game.cycleWeapon(1);
        if (!xr || trackedWeapon) {
          auto player = game.player();
          controls::input.aim = true;
          controls::input.origin = point(xr ? weaponWorld : headWorld);
          controls::input.direction = forward(xr ? weaponWorld : headWorld);
          for (int i = 0; i < 3; i++)
            controls::input.origin[i] += controls::input.direction[i] *
                                         (xr ? renderer.muzzleDistance() : 0.f);
          controls::input.origin[0] -= player.eye[0];
          controls::input.origin[2] -= player.eye[2];
          controls::input.origin[1] -= xr ? player.feetY : player.eye[1];
          controls::input.originSpace = xr ? controls::Input::OriginSpace::Feet
                                           : controls::Input::OriginSpace::Eye;
        }
      }
      prevBefore = previous;
      nextBefore = next;
      if (!paused && focused && (playing || page == Result)) {
        accumulator += dt;
        while (accumulator >= .02 && !game.finished()) {
          if (playing)
            game.setYaw(xr ? std::atan2(-headWorld[8], headWorld[10]) : yaw);
          int ammo = game.ammunition();
          game.tick();
          if (xr && game.ammunition() < ammo)
            xr->haptic();
          pendingRoom = {};
          renderer.sync();
          accumulator -= .02;
        }
      } else
        accumulator = 0;
      if (page == Play && game.phase() != 0) {
        page = Result;
        resetInput();
      }
      if (page == Result && pendingContinue && game.finished()) {
        pendingContinue = false;
        if (game.player().health > 0 && game.level() == 15) {
          page = Ending;
          endingPage = 0;
          resetInput();
        } else
          beginLevel(game.player().health > 0 ? game.level() + 1 : game.level(),
                     game.player().health > 0);
      }
      poses();
      panel();
      SDL_SetRelativeMouseMode(!xr && page == Play && !paused ? SDL_TRUE
                                                              : SDL_FALSE);
      if (xr) {
        xr->endFrame([&](const XrView &eye, int, int, int) {
          auto world = multiply(stageWorld, poseMatrix(eye.pose));
          RenderView view;
          view.viewProjection =
              multiply(projection(eye.fov), inverseRigid(world));
          view.headWorld = headWorld;
          view.weaponWorld = weaponWorld;
          view.trackedWeapon = trackedWeapon;
          view.camera = point(world);
          renderer.drawEye(view);
        });
      } else {
        int width, height;
        SDL_GL_GetDrawableSize(surface.window, &width, &height);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glViewport(0, 0, width, height);
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        RenderView view;
        view.viewProjection =
            multiply(perspective(float(width) / std::max(1, height)),
                     inverseRigid(headWorld));
        view.headWorld = headWorld;
        view.weaponWorld = weaponWorld;
        view.camera = point(headWorld);
        renderer.drawEye(view);
      }
      if (opt.frames) {
        auto error = glGetError();
        if (error)
          throw std::runtime_error("OpenGL frame error " +
                                   std::to_string(error));
      }
      SDL_GL_SwapWindow(surface.window);
      frame++;
      if (opt.frames && frame >= opt.frames)
        quit = true;
    }
    if (!opt.report.empty()) {
      auto soundStats = audio::stats();
      const char *pages[] = {"title",  "story",  "play",
                             "result", "ending", "credits"};
      nlohmann::json out = {{"runtime", "native-cpp"},
                            {"jvm", false},
                            {"page", pages[page]},
                            {"paused", paused},
                            {"smooth_turn", smooth},
                            {"two_hand", twoHand},
                            {"xr", vr},
                            {"audio_buffers", soundStats.buffers},
                            {"audio_input_frames", soundStats.inputFrames},
                            {"audio_queue_failures", soundStats.queueFailures},
                            {"audio_peak", soundStats.peak},
                            {"frames", frame},
                            {"pal_ticks", game.ticks()},
                            {"level", game.level() + 1},
                            {"health", game.player().health},
                            {"ammo", game.ammunition()},
                            {"eye_frames", renderer.stats().eyeFrames},
                            {"triangles", renderer.stats().triangles},
                            {"weapons", renderer.stats().weaponDraws},
                            {"missing_assets", renderer.stats().missingAssets},
                            {"renderer", reinterpret_cast<const char *>(
                                             glGetString(GL_RENDERER))}};
      std::ofstream file(opt.report);
      file << out.dump(2) << "\n";
    }
    if (!opt.frames) {
      try {
        auto path = configPath();
        fs::create_directories(path.parent_path());
        auto temporary = path;
        temporary += ".tmp";
        std::ofstream out(temporary);
        out << nlohmann::json{{"smooth_turn", smooth},
                              {"two_hand", twoHand},
                              {"sound", sound}}
                   .dump(2)
            << "\n";
        out.close();
        if (out)
          fs::rename(temporary, path);
      } catch (const std::exception &e) {
        std::cerr << "Settings: " << e.what() << "\n";
      }
    }
    audio::setEnabled(false);
    xr.reset();
    if (lease)
      dome.end();
    return 0;
  } catch (const std::exception &error) {
    std::cerr << "Alien Breed 3D II XR: " << error.what() << "\n";
    return 1;
  }
}
