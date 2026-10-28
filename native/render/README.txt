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
frame, angle, palette and additive flag. Raw sprite bytes 6/7 are half
extents; full physical width/height is raw/32. A zero dimension suppresses
the sprite until the original engine initializes it. Original centers remain
unchanged. Original shot pools are included.
OBJ model frames are cached in GPU buffers, with original texture atlas UVs.
Held weapons use the original held-entity model/frame and original relative
angle (4096-heldAngle+playerAngle), with a physical 0.22 mount scale.
Hires sets the held angle to player+4096, then animObj adds the original
actAnim word2: 2048 for the -X shotgun, zero for the six -Z weapons. Each
gun uses its actual original held rest frame (actAnim[0], not pickup frame0)
to center the front muzzle ring on tracked -Z. This removes original screen
composition offsets without changing mesh, animation or game state. The
rest-frame socket remains stable through firing; muzzleDistance() returns
the physical distance used by the guide and native shot-origin adapter. World
polygon models retain the extracted original 0.5 scale. A 28 cm physical
laser segment follows the tracked -Z aim ray, beginning beyond the original
held rest muzzle and retaining world/weapon depth occlusion. Original bitmapped
font/art is reused for title/story/pause/end panels and the health/ammo/fuel HUD.

The optional renderer-check.cpp under tests runs a real GL3.3 context over
all 16 original retail RAM snapshots, with explicit capture only in that test.
It can be built independently with C++20, SDL2, GLEW, libpng, OpenGL and the
native/include, native/src/core and native/render include directories.
On EGL/Wayland, glewInit may report no GLX display even though GL3.3 entry
points loaded successfully; require GLEW_VERSION_3_3 in that case.

Sky and water
-------------
The extracted original 648x240 panorama wraps twice per turn and clamps
vertically, following Sky.java/Draw_SkyBackdrop. A head-centred cylinder
projects at infinity; it remains behind actual room geometry in both eyes.

Water follows Hires.draw_WaterSurface: original PAL water-frame pointers,
wateroff and wtan drive eight wave phases, the distance palette, and sine
screen-line displacement. A GPU-only copy of the current color target
retains actors/scenery beneath the water; a resident 64-cubed nearest-color
lookup restores original palette indices before applying the original
29-row water tint. The original underwater palette is applied to the scene
when the physical head is below the water plane of the original zone.
Framebuffer bindings and viewport remain owned by the caller. No CPU frame
pixels are accessed or uploaded. effects-check.cpp covers the panorama
half-turn repeat, water phase changes, underwater treatment and arbitrary
framebuffer preservation, depth-occluded aim guides and every original
held weapon animation with a stable physical muzzle socket.

Directional actors and panels
-----------------------------
lighting.hpp ports the original read-only CalcBrightsInZone, CalcBrightRings,
TweenBrights, flat polygon-angle table, and HQN sprite guff/willy color-group
math. Rings follow animated signed point brightness, the original border-list
spill into subsequent zones, portal neighbors, solid wall normals and upper
zones. sync snapshots these from parked RAM without touching original scratch
registers or simulation. Original polygon .lvl face base/angle records and
indexed texturemaps atlas use the original resident palette in GLSL. HQN enemy
sprites retain original indices, all four shade palettes and the original 29
groups of eight colors. Per-view head yaw/depth chooses source group levels;
only small uniform arrays change, and sprite pixels/palettes stay in VRAM.

The independent optional development oracle is lighting-check.cpp plus
lighting-reference.py. The script compiles the preserved LightRings/SpriteLight
source with an explicit assembly-semantics correction in a temporary directory; it is not a
native build/install/runtime dependency. All 7,880 original actor/zone positions
across all 16 levels, lower/upper zones, full/sprite-only rings, six brightness
ranges, both flip directions and the original flat polygon-angle table match
4,397,040 source-result bytes exactly.

Panel text measures original glyph widths and fits each caption/narrative line
inside 1.94 physical metres of the 2.24m panel. Existing menu text retains its
normal size; original 80-character stories stay inside the same panel.

Current fidelity limits: polygon shading uses the original flat-face path;
per-vertex Gouraud/glare face flags were not included in the current extracted
OBJ sidecars. Generic packed 5-bit sprites still use color PNG attenuation;
additive effects use GPU blending rather than original palette-compositing.
Water color reindexing uses nearest palette colors on a 64-cubed grid, so close
or duplicate original colors and remaining non-palette effects can map
ambiguously; screen displacement is scaled from the original 240-line
projection. Bump/special material effects are not implemented yet.
The original game state, mechanisms and gameplay are not replaced by these
presentation approximations. Headset ergonomics, physical scaling and comfort
still require testing; no physical headset is used by the isolated GPU check.

See ORIGINAL_CONTENT_AND_LIGHTING.txt for direct assembly verification,
CurrentPointBrights integration, all 16 raw placement/mechanism counts and
precise remaining rendering/secret-route validation limits.
