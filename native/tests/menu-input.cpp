#include "menu_input.hpp"
#include <stdexcept>
int main() {
  ab3d2::MenuInput n;
  auto check = [](bool v) {
    if (!v)
      throw std::runtime_error("Menu joystick hysteresis/repeat failed");
  };
  check(n.update(.2, .01, true) == 0);
  check(n.update(.4, .01, true) == 0);
  check(n.update(.7, .01, true) == -1);
  check(n.update(.7, .1, true) == 0);
  check(n.update(.7, .31, true) == -1);
  check(n.update(.2, .01, true) == 0);
  check(n.update(-.4, .01, true) == 0);
  check(n.update(-.7, .01, true) == 1);
  check(n.update(1, .01, false) == 0);
  check(n.update(1, .01, true) == -1);
}
