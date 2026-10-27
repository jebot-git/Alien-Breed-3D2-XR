#include "original.hpp"
namespace Plr2control {
void Plr2_ShowGunName(){
Player::plr_ShowGunName(PlayerBss::Plr2_Data);
}

void Plr2_MouseControl(){
Player::plr_MouseControl(PlayerBss::Plr2_Data);
Plr2control::Plr2_KeyboardControl();
}

void Plr2_KeyboardControl(){
Player::plr_KeyboardControl(PlayerBss::Plr2_Data);
Plr2control::Plr2_Fall();
}

void Plr2_JoystickControl(){
Cd32joy::_ReadJoy2();
Plr2control::Plr2_KeyboardControl();
}

void Plr2_FootstepFX(){
Player::plr_DoFootstepFX(PlayerBss::Plr1_Data);
}

void Plr2_Fall(){
Player::plr_Fall(PlayerBss::Plr2_Data);
}

}