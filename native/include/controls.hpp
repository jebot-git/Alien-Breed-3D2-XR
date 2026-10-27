#pragma once
#include <array>
#include <cstdint>
namespace ab3d2::controls {
struct Input {
  enum class OriginSpace { World, Feet, Eye };
  bool active = false, aim = false;
  float forward = 0, strafe = 0, height = 1.5f;
  int32_t roomX = 0, roomZ = 0;
  std::array<float, 3> origin{}, direction{0, 0, -1};
  OriginSpace originSpace = OriginSpace::World;
};
inline Input input;
void crouch(int player);
void accelerate(int player, int32_t &x, int32_t &z);
void roomMove(int player, int32_t &x, int32_t &z);
int heightStep(int player, int current, int target);
struct AimScope {
  bool active = false;
  std::array<int32_t, 6> saved{};
  AimScope();
  ~AimScope();
};
bool aimed();
bool intersects(int actor);
int distance(int actor);
int verticalSpeed(int exponent);
int originY();
int rayYStep();
bool verticalRay();
} // namespace ab3d2::controls
