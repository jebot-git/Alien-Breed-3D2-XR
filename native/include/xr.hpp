#pragma once
#include <array>
#include <functional>
#include <memory>
#include <openxr/openxr.h>
#include <string>
struct SDL_Window;
namespace ab3d2 {
struct Tracking {
  XrPosef hands[2]{}, grips[2]{};
  bool valid[2]{}, gripValid[2]{}, headValid = false;
  bool supportHeld = false, supportAvailable = false, fire = false, use = false,
       menu = false, previousWeapon = false, nextWeapon = false, jump = false;
  XrVector2f move{}, turn{};
  XrVector3f anchor{}, headPosition{};
  float anchorYaw = 0, headYawRadians = 0;
};
class XR {
  struct Impl;
  std::unique_ptr<Impl> p;
  void initializeActions();
  void sampleActions(XrTime time);

public:
  XR();
  ~XR();
  XR(const XR &) = delete;
  XR &operator=(const XR &) = delete;
  void initialize(SDL_Window *);
  bool beginFrame();
  void endFrame(const std::function<void(const XrView &, int, int, int)> &draw);
  const Tracking &tracking() const;
  XrPosef headPose() const;
  bool focused() const;
  void setVisible(bool);
  void recenter();
  bool resetHeight();
  std::string description() const;
  void haptic(float amplitude = .15f, int milliseconds = 20);
};
} // namespace ab3d2
