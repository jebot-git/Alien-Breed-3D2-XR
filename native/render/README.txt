AB3DII native GPU renderer
=========================

API: native/include/render.hpp, namespace ab3d2. A current OpenGL 3.3 core
context and initialized GLEW are required during construction/destruction.
loadAssets reads the extracted original PNG/OBJ/JSON asset tree. loadLevel
builds level meshes from levels/a.json through p.json. sync reads the parked
original core once per PAL tick; it never writes Mem::RAM or advances gameplay.

Caller owns framebuffer, viewport and color/depth clearing. Each drawEye uses
its column-major viewProjection and the same synchronized scene. headWorld
is the physical head-centre pose shared by both eyes; camera is physical
world metres. weaponWorld is a tracked right-hand pose whose -Z is forward.
worldScale uniformly calibrates original room/actor coordinates while held
weapons and head-relative panels remain in physical metres.

The renderer batches walls and floors into GPU VBO/VAOs. Original indexed
wall/floor textures and palette LUTs are resident in VRAM; per-point lighting
uses the original signed-byte animation blend and brightness decoding.
Door/lift wall coordinates and texture phases come from the live patched
original graphics stream; floor/ceiling heights follow live original zones.
Only changed geometry is uploaded, once during sync. A small light texture
updates with original animation data. There is no CPU world raster, pixel
upload per eye, or production framebuffer readback.

Every active actor uses original CID position, height word, zone, model/sheet,
frame, angle, palette and additive flag. Original shot pools are included.
OBJ model frames are cached in GPU buffers, with original texture atlas UVs.
Held weapons use the original held-entity model/frame and original relative
angle (4096-heldAngle+playerAngle), with a physical 0.22 mount scale. World
polygon models retain the extracted original 0.5 scale. Original bitmapped
font/art is reused for title/story/pause/end panels and the health/ammo/fuel HUD.

The optional renderer-check.cpp under tests runs a real GL3.3 context over
all 16 original retail RAM snapshots, with explicit capture only in that test.
It can be built independently with C++20, SDL2, GLEW, libpng, OpenGL and the
native/include, native/src/core and native/render include directories.
On EGL/Wayland, glewInit may report no GLX display even though GL3.3 entry
points loaded successfully; require GLEW_VERSION_3_3 in that case.

Current fidelity limits: polygon/sprite materials use original color PNGs
with object-brightness attenuation, rather than the full directional light
rings and per-face shaded palette pipeline. Water is a transparent original
floor texture, without the original refraction/underwater postprocessing.
Sky backdrops and bump/special material effects are not implemented yet.
The original game state, mechanisms and gameplay are not replaced by these
presentation approximations. Headset ergonomics, physical scaling and comfort
still require testing; no physical headset is used by the isolated GPU check.
