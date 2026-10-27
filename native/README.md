# Native Alien Breed 3D II XR

The game is native C++20. Its CMake build and installed executable use no JVM,
Java UI, Gradle or Java libraries. The active `domed-native-openxr` branch is
based on the maintained original Amiga history; the earlier Java experiment
is retained only on `reference/java-host-audit`.

The checked-in C++ gameplay retains the original fixed-point movement,
collision, AI, combat, pickups, mechanisms, campaign and 50 Hz PAL timing.
OpenGL 3.3 renders the world, stereo eyes, original animated polygon weapons
and menus. Gameplay never waits for a software framebuffer. Native OpenXR
uses EGL on Wayland, with an explicit X11/GLX fallback. The same DomeD native
XR handoff as Alien Breed XR/Tempest manages fullscreen input/background
ownership; desktop launches select DomeD's desktop realm.

## Build and run

Build as the regular user with SDL2, OpenXR, OpenGL/EGL, GLEW, X11, libpng,
libcurl, zlib and nlohmann-json development packages:

```sh
cmake -S . -B build-native -DCMAKE_BUILD_TYPE=Release
cmake --build build-native -j4
ctest --test-dir build-native --output-on-failure -j4
build-native/alien-breed3d2-xr --desktop --assets assets
build-native/alien-breed3d2-xr --xr --assets assets
```

The original retail assets and `assets/native/manifest.json` data pack must
already exist. No source/data downloads or development migrations run during
compilation or launch. Local game data, reference fixtures and toolchains are
ignored by Git. `--assets PATH` or `AB3D2_XR_ASSETS` selects another data pack.

Automatic launch mode follows DomeD's validated desktop/XR launch realm.
Outside DomeD it selects OpenXR; use `--desktop` for a desktop session.
`--standalone` explicitly bypasses the DomeD handoff. The currently running
older DomeD may lack that hook; installing this game never restarts a session.
`--x11` is an explicit desktop fallback and is routed to the desktop realm.

## Controls

XR: left stick for analog head-oriented movement/run; right stick for smooth
turning (default) or 30-degree snap turns. Right trigger fires; A/X operates
switches/doors; Y/B cycles weapons backward/forward. Right-stick click jumps
or powers the original jetpack. Crouching follows physical head height.
Physical horizontal motion goes through original collision and pushes the
virtual body/view back at walls. Left grip supports the gun with the other
hand; it changes physical aiming only. Original weapon meshes, animation,
ammunition, spread, damage and fire delay remain authoritative. A short,
depth-tested laser and shot origin share the calibrated original muzzle.

Left menu opens the overlaid pause menu: resume, turn mode, save/load,
floor/height reset, two-hand support, audio, restart and quit. Resume requires
neutral input before accepting movement/fire. Losing XR focus pauses play.
Original level narratives, title art and paginated ending are included.

Desktop: WASD, mouse aim/left-click or Ctrl fire, Shift run, C crouch, F use,
Space jump/fly, Q/E weapons, Escape pause, arrows/Enter menus, F5/F9 save/load.
Super+W and Super+Q close/quit. The app has no independent menu bar/tray.

Settings live in `$XDG_CONFIG_HOME/alien-breed3d2-xr/settings.json`; the default
is `~/.config`. The single save slot lives under
`$XDG_STATE_HOME/alien-breed3d2-xr/slot1.ab2xr` (default `~/.local/state`). Saves
contain original RAM, mutable native state and Paula registers with compression,
layout checks and atomic replacement. Audio restarts at the saved Paula loop;
subsample mixer phase is not serialized. Campaign transitions carry original
health, ammunition and owned equipment.

## Verification and staging

With local source reference fixtures, 16 tests compare 80 movement/fire ticks
per retail level: player state, weapon animation and every actor's position,
zone/layer, type, animation and health. Additional tests check native arithmetic,
worker lifecycle, exact save/replay, campaign carry, successful/death
intermissions, physical/analog controls, close/up/down damage, original fire
cooldown, vertical projectiles and exact Paula audio blocks.

Enable real GPU tests with `-DAB3D2_BUILD_GPU_TESTS=ON`. They check all16 scenes,
stereo parallax, read-only simulation access, doors/lifts, sky/water, every
original held weapon animation, depth-occluded aim guides and bitmap panels.
A separately isolated OpenXR fixture has checked the native application's two
eye swapchains and 50 Hz gameplay at 90 Hz presentation. These tests use no
physical headset. No headset ergonomics or complete campaign playthrough is
claimed yet. Presentation limits are listed in `render/README.txt`.

Stage an optimized install without root:

```sh
DESTDIR="$PWD/artifacts/stage" cmake --install build-native
```

This stages the native executable, launcher, desktop entry, local data pack
and notices under `/usr/local`. The staged launcher contains the final system
paths. Only copying staged system files requires sudo; builds and checks do
not. No desktop/display-manager service is restarted.

The optional offline migration tools are development references, not build or
runtime dependencies. See `SOURCE_AUDIT.txt` and `SOURCE_NOTICES.txt` for exact
source revisions and the reason direct compilation of the original Amiga C
was not sufficient.
