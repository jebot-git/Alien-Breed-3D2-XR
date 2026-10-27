#pragma once
#include <array>
#include <cstdint>
#include <filesystem>
#include <memory>
namespace ab3d2 {
enum class Key { Forward, Backward, Left, Right, Run, Fire, Use, Jump, Duck };
struct PlayerState {
  std::array<float, 3> eye{};
  float yaw = 0, feetY = 0, floorY = 0, ceilingY = 1000;
  int health = 0, gun = 0, zone = 0;
};
class Runtime {
  struct Impl;
  std::unique_ptr<Impl> p;

public:
  explicit Runtime(std::filesystem::path assets);
  ~Runtime();
  Runtime(const Runtime &) = delete;
  Runtime &operator=(const Runtime &) = delete;
  void loadLevel(int level, bool carry = false);
  void tick();
  void key(Key, bool);
  void clearInput();
  void setYaw(float radians);
  void cycleWeapon(int direction);
  PlayerState player() const;
  int level() const;
  uint64_t ticks() const;
  bool finished() const;
  int phase() const;
  int ammunition() const;
  void skipIntermission();
  void save(const std::filesystem::path &);
  void load(const std::filesystem::path &);
};
} // namespace ab3d2
