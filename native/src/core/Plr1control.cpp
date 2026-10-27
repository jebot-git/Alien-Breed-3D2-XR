#include "original.hpp"
namespace Plr1control {
void Plr1_ShowGunName(){
Player::plr_ShowGunName(PlayerBss::Plr1_Data);
}

void Plr1_MouseControl(){
Player::plr_MouseControl(PlayerBss::Plr1_Data);
Plr1control::Plr1_KeyboardControl();
}

void Plr1_KeyboardControl(){
Player::plr_KeyboardControl(PlayerBss::Plr1_Data);
Plr1control::Plr1_Fall();
}

void Plr1_JoystickControl(){
Cd32joy::_ReadJoy1();
Plr1control::Plr1_KeyboardControl();
}

void Plr1_FootstepFX(){
Player::plr_DoFootstepFX(PlayerBss::Plr1_Data);
}

void Plr1_Fall(){
Player::plr_Fall(PlayerBss::Plr1_Data);
}

void Plr1_FollowPath(){
int32_t a0=Mem::l(HiresData::pathpt);
int32_t d1=M68k::setw(0,Mem::uw(a0));
Mem::ww(PlayerBss::Plr1_SnapXOff_l,d1);
(d1=M68k::setw(d1,Mem::uw(j_add(a0,2))));
Mem::ww(PlayerBss::Plr1_SnapZOff_l,d1);
int32_t d0=M68k::setw(0,Mem::uw(j_add(a0,4)));
(d0=M68k::setw(d0,j_add(d0,d0)));
(d0=M68k::setw(d0,(d0 & TablesData::SINTAB_MASK_ADR)));
Mem::ww(PlayerBss::Plr1_AngPos_w,d0);
(d0=M68k::setw(0,Mem::uw(AnimBss::Anim_TempFrames_w)));
(d0=M68k::setw(d0,j_shl((d0 & 0xFFFF),3)));
(a0=j_add(a0,int16_t(d0)));
if((a0 >= HiresData::endpath)) (a0=HiresData::Path);
Mem::wl(HiresData::pathpt,a0);
}

}