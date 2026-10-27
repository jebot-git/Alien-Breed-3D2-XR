#include "controls.hpp"
#include "original.hpp"
namespace ab3d2::controls {
namespace {
thread_local bool ray = false;
thread_local std::array<float, 3> origin{}, direction{};
float length(const std::array<float, 3> &a) {
  return std::sqrt(a[0] * a[0] + a[1] * a[1] + a[2] * a[2]);
}
std::array<float, 3> centre(int actor) {
  int points = Mem::l(LevelBss::Lvl_ObjectPointsPtr_l) + Mem::uw(actor) * 8;
  return {Mem::w(points) / 64.f, -Mem::w(actor + 4) / 64.f,
          -Mem::w(points + 4) / 64.f};
}
float projected(int actor) {
  auto p = centre(actor);
  return (p[0] - origin[0]) * direction[0] + (p[1] - origin[1]) * direction[1] +
         (p[2] - origin[2]) * direction[2];
}
} // namespace
void crouch(int player) {
  if (!input.active || player != PlayerBss::Plr1_Data)
    return;
  int height = std::clamp(int(std::lround(input.height * 8192)),
                          Hires::PLR_CROUCH_HEIGHT, Hires::PLR_STAND_HEIGHT);
  Mem::wl(player + Defs::PlrT_SnapTargHeight_l, height);
  Mem::wb(player + Defs::PlrT_Ducked_b,
          height < Hires::PLR_STAND_HEIGHT - 1024 ? 255 : 0);
}
void accelerate(int player, int32_t &x, int32_t &z) {
  if (!input.active || player != PlayerBss::Plr1_Data)
    return;
  float f = input.forward, r = input.strafe, n = std::sqrt(f * f + r * r);
  if (n > 1) {
    f /= n;
    r /= n;
  }
  float speed = (Mem::b(player + Defs::PlrT_Ducked_b) ||
                 Mem::b(player + Defs::PlrT_Squished_b))
                    ? 1.f
                    : 3.f;
  int sn = Mem::w(player + Defs::PlrT_SnapSinVal_w),
      cs = Mem::w(player + Defs::PlrT_SnapCosVal_w);
  x += int(std::lround((sn * f + cs * r) * speed));
  z += int(std::lround((cs * f - sn * r) * speed));
  Mem::ww(PlayerBss::Plr_AddToBobble_w,
          -int(std::lround(std::min(1.f, n) * speed * 64)));
}
void roomMove(int player, int32_t &x, int32_t &z) {
  if (!input.active || player != PlayerBss::Plr1_Data)
    return;
  x += input.roomX;
  z += input.roomZ;
  input.roomX = input.roomZ = 0;
}
int heightStep(int player, int current, int target) {
  if (input.active && player == PlayerBss::Plr1_Data)
    return current + std::clamp(target - current, -1024, 1024);
  return current > target ? current - 1024 : current + 1024;
}
AimScope::AimScope() {
  if (!input.aim || Mem::b(PlayerBss::Plr1_TmpFire_b) == 0 ||
      Mem::w(PlayerBss::Plr1_TimeToShoot_w) != 0)
    return;
  float magnitude = length(input.direction);
  if (magnitude < .9f || magnitude > 1.1f)
    return;
  active = true;
  ray = true;
  origin = input.origin;
  for (int i = 0; i < 3; i++)
    direction[i] = input.direction[i] / magnitude;
  saved = {
      Mem::l(PlayerBss::Plr1_XOff_l),    Mem::l(PlayerBss::Plr1_YOff_l),
      Mem::l(PlayerBss::Plr1_ZOff_l),    Mem::uw(PlayerBss::Plr1_AngPos_w),
      Mem::uw(PlayerBss::Plr1_SinVal_w), Mem::uw(PlayerBss::Plr1_CosVal_w)};
  if (input.originSpace != Input::OriginSpace::World) {
    origin[0] += saved[0] / 65536.f / 64;
    origin[2] += -saved[2] / 65536.f / 64;
    origin[1] += input.originSpace == Input::OriginSpace::Eye
                     ? -saved[1] / 8192.f
                     : -(Mem::l(PlayerBss::Plr1_TmpYOff_l) +
                         Mem::l(PlayerBss::plr1_TmpHeight_l)) /
                           8192.f;
  }
  Mem::ww(ObjectmoveData::oldx, saved[0] >> 16);
  Mem::ww(ObjectmoveData::oldz, saved[2] >> 16);
  Mem::wl(ObjectmoveData::oldy, saved[1]);
  Mem::ww(ObjectmoveData::newx, int(std::lround(origin[0] * 64)));
  Mem::ww(ObjectmoveData::newz, int(std::lround(-origin[2] * 64)));
  Mem::wl(ObjectmoveData::newy, int(std::lround(-origin[1] * 8192)));
  Mem::wb(ObjectmoveData::exitfirst, 255);
  Mem::wb(ObjectmoveData::Obj_WallBounce_b, 0);
  Mem::ww(ObjectmoveData::Obj_ExtLen_w, 0);
  Mem::ww(ObjectmoveData::distaway, 0);
  Mem::ww(ObjectmoveData::wallflags, 1024);
  Mem::wl(ObjectmoveData::StepUpVal, 0);
  Mem::wl(ObjectmoveData::StepDownVal, 0x1000000);
  Mem::wl(ObjectmoveData::thingheight, 0);
  Mem::wl(ObjectmoveData::Obj_ZonePtr_l, Mem::l(PlayerBss::Plr1_ZonePtr_l));
  Mem::wb(ObjectmoveData::StoodInTop, Mem::ub(PlayerBss::Plr1_StoodInTop_b));
  Objectmove::MoveObject();
  if (Mem::b(ObjectmoveData::hitwall) ||
      Mem::l(ObjectmoveData::Obj_ZonePtr_l) !=
          Mem::l(PlayerBss::Plr1_ZonePtr_l))
    origin = {saved[0] / 65536.f / 64, -saved[1] / 8192.f,
              -saved[2] / 65536.f / 64};
  Mem::wl(PlayerBss::Plr1_XOff_l, int(std::lround(origin[0] * 64 * 65536)));
  Mem::wl(PlayerBss::Plr1_ZOff_l, int(std::lround(-origin[2] * 64 * 65536)));
  // The original routine adds 10*128 and then 20*128 to the projectile origin.
  Mem::wl(PlayerBss::Plr1_YOff_l,
          int(std::lround(-origin[1] * 8192)) - 30 * 128);
  int angle = int(std::lround(std::atan2(direction[0], -direction[2]) /
                              6.283185307179586 * 8192)) &
              8190;
  Mem::ww(PlayerBss::Plr1_AngPos_w, angle);
  Mem::ww(PlayerBss::Plr1_SinVal_w, int(std::lround(direction[0] * 32767)));
  Mem::ww(PlayerBss::Plr1_CosVal_w, int(std::lround(-direction[2] * 32767)));
}
AimScope::~AimScope() {
  if (!active)
    return;
  Mem::wl(PlayerBss::Plr1_XOff_l, saved[0]);
  Mem::wl(PlayerBss::Plr1_YOff_l, saved[1]);
  Mem::wl(PlayerBss::Plr1_ZOff_l, saved[2]);
  Mem::ww(PlayerBss::Plr1_AngPos_w, saved[3]);
  Mem::ww(PlayerBss::Plr1_SinVal_w, saved[4]);
  Mem::ww(PlayerBss::Plr1_CosVal_w, saved[5]);
  ray = false;
}
bool aimed() { return ray; }
bool intersects(int actor) {
  auto p = centre(actor);
  float halfHeight = std::max(.12f, Mem::ub(actor + 7) / 64.f),
        radius = std::max(.1f, Mem::ub(actor + 6) / 64.f);
  if (Mem::ub(actor + Defs::ObjT_TypeID_b) == 0) {
    int def = Mem::l(HiresData::GLF_DatabasePtr_l) + Defs::GLFT_AlienDefs_l +
              Mem::ub(actor + Defs::EntT_Type_b) * Defs::AlienT_SizeOf_l;
    halfHeight = std::max(.15f, Mem::uw(def + Defs::AlienT_Height_w) / 128.f);
    if (Mem::ub(actor + 6) == 255 || Mem::ub(actor + 6) == 0)
      radius = std::clamp(halfHeight * .4f, .12f, .8f);
  }
  float t = projected(actor);
  if (t < .01f)
    return std::abs(p[0] - origin[0]) <= radius &&
           std::abs(p[2] - origin[2]) <= radius &&
           std::abs(p[1] - origin[1]) <= halfHeight;
  float dx = p[0] - origin[0] - t * direction[0],
        dz = p[2] - origin[2] - t * direction[2],
        dy = p[1] - origin[1] - t * direction[1];
  return dx * dx + dz * dz <= radius * radius && std::abs(dy) <= halfHeight;
}
int distance(int actor) {
  return std::clamp(int(std::lround(projected(actor) * 128)), 1, 32767);
}
int verticalSpeed(int exponent) {
  return std::clamp(
      int(std::lround(-direction[1] * 64 * (1 << std::clamp(exponent, 0, 8)))),
      -32767, 32767);
}
int originY() { return int(std::lround(-origin[1] * 8192)); }
int rayYStep() { return int(std::lround(-direction[1] * 32768)); }
bool verticalRay() {
  if (!ray || std::abs(direction[0]) + std::abs(direction[2]) > .001f)
    return false;
  int zone = Mem::l(PlayerBss::Plr1_ZonePtr_l);
  bool upper = Mem::b(PlayerBss::Plr1_StoodInTop_b);
  int plane = Mem::l(
      zone + (direction[1] < 0
                  ? (upper ? Defs::ZoneT_UpperFloor_l : Defs::ZoneT_Floor_l)
                  : (upper ? Defs::ZoneT_UpperRoof_l : Defs::ZoneT_Roof_l)));
  Mem::wl(ObjectmoveData::newy, plane);
  Mem::wl(ObjectmoveData::wallhitheight, plane);
  Mem::wb(ObjectmoveData::hitwall, 255);
  return true;
}
} // namespace ab3d2::controls
