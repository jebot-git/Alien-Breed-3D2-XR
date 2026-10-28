#pragma once
#include <cmath>
namespace ab3d2 {
// Enter at .6, release at .3. Crossing the release band must never consume
// the first selection; slow stick deflections are normal on real controllers.
struct MenuInput {
  bool held = false;
  double repeat = 0;
  int update(float axis, double dt, bool active) {
    if (!active || std::abs(axis) < .3f) {
      held = false;
      repeat = 0;
      return 0;
    }
    if (!held) {
      if (std::abs(axis) < .6f)
        return 0;
      held = true;
      repeat = .4;
      return axis > 0 ? -1 : 1;
    }
    repeat -= dt;
    if (repeat > 0 || std::abs(axis) < .6f)
      return 0;
    repeat = .18;
    return axis > 0 ? -1 : 1;
  }
};
} // namespace ab3d2
