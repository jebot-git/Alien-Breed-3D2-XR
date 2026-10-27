# Native Alien Breed 3D II XR port

The product is C++. No JVM, Java UI, Gradle or Java libraries are used by its
CMake build or native runtime. The active branch preserves the original Amiga
source history. The earlier Java GPU experiment is retained separately on
`reference/java-host-audit`; it is reference work, not the product.

The original fixed-point gameplay is migrated into checked-in C++ under
`src/core`. It retains big-endian memory, 680x0 register arithmetic, original
AI/collision/weapon routines and PAL frame boundaries. It does not use the
independent Rebirth gameplay simulation.

Build as the regular user:

```sh
cmake -S . -B build-native -DCMAKE_BUILD_TYPE=Release
cmake --build build-native -j4
ctest --test-dir build-native --output-on-failure -j4
```

Current validation covers native arithmetic, word promotion, integer traps,
RAM layout and original text formatting. With the local development fixtures
under `artifacts/native-oracle`, another 16 tests compare 80 movement/firing
frames per retail level against original-code reference states. These compare
player state, original weapon model/frame and every actor record, including
positions, zone/layer, animation, type and health. All 17 tests pass.

The fixtures contain original game data and are deliberately not committed.
Normal compilation uses checked-in C++ and does not invoke the optional offline
migration helper. That helper requires Python with `javalang==0.13.0`, the
separately obtained literal reference source, and exported reference layouts.
Its parser correction preserves negation before casts; labeled collision-loop
continues and Java integer promotion also have explicit native equivalents.

GPU presentation, native OpenXR control and the DomeD handoff are being
integrated. A passing core comparison is not a completed headset port or a
headset test. Native OS services outside the active core either have explicit
host implementations or fail visibly; see `src/core/host-services.json`.

See [SOURCE_AUDIT.txt](SOURCE_AUDIT.txt) for the original sources, revisions,
retail-data distinction and the renderer-swap defect found during the audit.
