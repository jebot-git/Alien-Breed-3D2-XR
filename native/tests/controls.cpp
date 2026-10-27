#include "controls.hpp"
#include "original.hpp"
#include "runtime.hpp"
#include <iostream>
using namespace ab3d2;
void require(bool ok, const char *why) {
  if (!ok)
    throw std::runtime_error(why);
}
std::array<int, 6> body() {
  return {Mem::l(PlayerBss::Plr1_XOff_l),    Mem::l(PlayerBss::Plr1_YOff_l),
          Mem::l(PlayerBss::Plr1_ZOff_l),    Mem::uw(PlayerBss::Plr1_AngPos_w),
          Mem::uw(PlayerBss::Plr1_SinVal_w), Mem::uw(PlayerBss::Plr1_CosVal_w)};
}
int main(int argc, char **argv) {
  try {
    require(argc == 2, "Pass original asset directory");
    Runtime game(argv[1]);
    game.loadLevel(0);
    auto initial = game.player();
    auto move = [&](float amount, float yaw) {
      game.loadLevel(0);
      for (int n = 0; n < 8; n++) {
        game.clearInput();
        game.setYaw(yaw);
        controls::input.active = true;
        controls::input.forward = amount;
        game.tick();
      }
      return game.player();
    };
    auto slow = move(.25f, 0), fast = move(1, 0),
         right = move(1, 1.57079632679f);
    require(std::abs(fast.eye[2] - initial.eye[2]) >
                std::abs(slow.eye[2] - initial.eye[2]) * 2,
            "Analog movement is not proportional");
    require(fast.eye[2] < initial.eye[2] && right.eye[0] > initial.eye[0],
            "Movement is not head/yaw oriented");
    game.loadLevel(0);
    for (int n = 0; n < 12; n++) {
      game.clearInput();
      controls::input.active = true;
      controls::input.height = 1.13f;
      game.tick();
    }
    require(std::abs(Mem::l(PlayerBss::Plr1_SnapHeight_l) / 8192.f - 1.13f) <
                .001f,
            "Physical crouch did not settle at tracked height");
    game.loadLevel(0);
    auto position = game.player();
    game.clearInput();
    controls::input.active = true;
    controls::input.roomX = int(.08 * 64 * 65536);
    game.tick();
    require(game.player().eye[0] > position.eye[0] + .05f,
            "Physical movement did not enter original collision path");
    require(controls::input.roomX == 0,
            "Physical room delta was applied twice");
    for (float pitch : {-.7f, 0.f, .7f}) {
      game.loadLevel(0);
      auto player = game.player();
      int actor = Mem::l(LevelBss::Lvl_ObjectDataPtr_l),
          points = Mem::l(LevelBss::Lvl_ObjectPointsPtr_l);
      int target = -1;
      for (int p = actor; Mem::w(p) >= 0; p += Defs::ENT_NEXT) {
        Mem::wb(p + Defs::ObjT_SeePlayer_b, 0);
        if (target < 0 && Mem::ub(p + Defs::ObjT_TypeID_b) == 0 &&
            Mem::ub(p + Defs::EntT_HitPoints_b) > 0)
          target = p;
      }
      require(target >= 0, "Retail scene has no test alien");
      int point = points + Mem::uw(target) * 8;
      // Place an existing original alien close along the tracked ray,
      // above/below the eye. Keep source definition, collision extent and
      // damage routine.
      float dy = std::sin(pitch), dz = -std::cos(pitch);
      float distance = .6f;
      Mem::ww(point, int(std::lround(player.eye[0] * 64)));
      Mem::ww(point + 4,
              int(std::lround(-(player.eye[2] + dz * distance) * 64)));
      Mem::ww(target + 4,
              int(std::lround(-(player.eye[1] + dy * distance) * 64)));
      Mem::ww(target + Defs::ObjT_ZoneID_w, player.zone);
      Mem::wb(target + Defs::ObjT_SeePlayer_b, 1);
      Mem::wb(target + Defs::EntT_DamageTaken_b, 0);
      Mem::wb(PlayerBss::Plr1_TmpFire_b, 255);
      Mem::wb(PlayerBss::Plr1_TmpGunSelected_b, 3);
      Mem::ww(PlayerBss::Plr1_TimeToShoot_w, 0);
      Mem::ww(PlayerBss::Plr1_AmmoCounts_vw + 2, 100);
      Mem::ww(AnimBss::Anim_TempFrames_w, 1);
      controls::input.aim = true;
      controls::input.originSpace = controls::Input::OriginSpace::Eye;
      controls::input.origin = {};
      controls::input.direction = {0, dy, dz};
      auto before = body();
      Newplayershoot::Plr1_Shot();
      require(body() == before,
              "Tracked shot leaked pose into original player state");
      require(Mem::uw(PlayerBss::Plr1_AmmoCounts_vw + 2) < 100,
              "Close angled shot did not consume original ammunition");
      require(Mem::ub(target + Defs::EntT_DamageTaken_b) > 0,
              "Close/up/down tracked shot did not damage original alien");
      int ammo = Mem::uw(PlayerBss::Plr1_AmmoCounts_vw + 2);
      Newplayershoot::Plr1_Shot();
      require(Mem::uw(PlayerBss::Plr1_AmmoCounts_vw + 2) == ammo,
              "Tracked fire bypassed original cooldown");
    }
    for (float dy : {-1.f, 1.f}) {
      game.loadLevel(0);
      Mem::wb(PlayerBss::Plr1_TmpFire_b, 255);
      Mem::wb(PlayerBss::Plr1_TmpGunSelected_b, 3);
      Mem::ww(PlayerBss::Plr1_TimeToShoot_w, 0);
      Mem::ww(PlayerBss::Plr1_AmmoCounts_vw + 2, 100);
      controls::input.aim = true;
      controls::input.originSpace = controls::Input::OriginSpace::Eye;
      controls::input.direction = {0, dy, 0};
      auto before = body();
      Newplayershoot::Plr1_Shot();
      require(body() == before, "Vertical shot leaked player state");
      require(Mem::uw(PlayerBss::Plr1_AmmoCounts_vw + 2) < 100,
              "Vertical hitscan did not fire");
    }
    for (int gun : {1, 2, 4, 5, 6, 8, 9})
      for (float dy : {-1.f, 1.f}) {
        game.loadLevel(0);
        Mem::wb(PlayerBss::Plr1_TmpFire_b, 255);
        Mem::wb(PlayerBss::Plr1_TmpGunSelected_b, gun);
        Mem::ww(PlayerBss::Plr1_TimeToShoot_w, 0);
        for (int n = 0; n < 20; n++)
          Mem::ww(PlayerBss::Plr1_AmmoCounts_vw + n * 2, 1000);
        int shots = Mem::l(PlayerBss::Plr_ShotDataPtr_l);
        for (int n = 0; n < Defs::NUM_PLR_SHOT_DATA; n++)
          Mem::ww(shots + n * Defs::ObjT_SizeOf_l + Defs::ObjT_ZoneID_w, -1);
        controls::input.aim = true;
        controls::input.originSpace = controls::Input::OriginSpace::Eye;
        controls::input.direction = {0, dy, 0};
        auto before = body();
        Newplayershoot::Plr1_Shot();
        require(body() == before, "Projectile shot leaked player state");
        require(Mem::w(shots + Defs::ObjT_ZoneID_w) >= 0,
                "Original projectile did not spawn");
        require(Mem::l(shots + Defs::ShotT_VelocityX_w) == 0 &&
                    Mem::l(shots + Defs::ShotT_VelocityZ_w) == 0,
                "Vertical projectile gained horizontal velocity");
        int speed = 64 * (1 << Mem::uw(NewplayershootData::BulletSpd));
        require(Mem::w(shots + Defs::ShotT_VelocityY_w) == -dy * speed,
                "Tracked pitch was limited by original flat-screen auto-aim");
      }
    std::cout
        << "PASS analog/head-oriented movement, physical crouch/room delta, "
           "close/up/down damage, original cooldown and vertical hitscan\n";
  } catch (const std::exception &e) {
    std::cerr << e.what() << "\n";
    return 1;
  }
}
