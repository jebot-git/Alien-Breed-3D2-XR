#include "controls.hpp"
// Native tracked input: original movement/friction/gravity/collision remain authoritative.
#include "original.hpp"
namespace Player {
void Plr_Initialise(){
int32_t a1=Mem::l(LevelBss::Lvl_DataPtr_l);
(a1+=(Defs::LVLT_MESSAGE_LENGTH * Defs::LVLT_MESSAGE_COUNT));
int32_t d0=Mem::w(j_add(a1,Defs::TBLT_Plr1_StartZoneID_w));
int32_t a0=Mem::l(LevelBss::Lvl_ZonePtrsPtr_l);
(d0=Mem::l(j_add(a0,(int16_t(d0) * 4))));
Mem::wl(PlayerBss::Plr1_ZonePtr_l,d0);
(a0=Mem::l(PlayerBss::Plr1_ZonePtr_l));
(d0=Mem::l(j_add(a0,Defs::ZoneT_Floor_l)));
(d0-=Hires::PLR_STAND_HEIGHT);
Mem::wl(PlayerBss::Plr1_SnapYOff_l,d0);
Mem::wl(PlayerBss::Plr1_YOff_l,d0);
Mem::wl(PlayerBss::Plr1_SnapTYOff_l,d0);
Mem::wl(PlayerBss::plr1_OldRoomPtr_l,Mem::l(PlayerBss::Plr1_ZonePtr_l));
Mem::ww(PlayerBss::Plr1_SnapXOff_l,Mem::uw(j_add(a1,Defs::TBLT_Plr1_StartXPos_w)));
Mem::ww(PlayerBss::Plr1_SnapZOff_l,Mem::uw(j_add(a1,Defs::TBLT_Plr1_StartZPos_w)));
Mem::ww(PlayerBss::Plr1_XOff_l,Mem::uw(j_add(a1,Defs::TBLT_Plr1_StartXPos_w)));
Mem::ww(PlayerBss::Plr1_ZOff_l,Mem::uw(j_add(a1,Defs::TBLT_Plr1_StartZPos_w)));
Mem::wl(PlayerBss::plr1_DefaultEnemyFlags_l,0b100011);
if((Player::dbgSpawnZone >= 0)) {
int32_t zp=Mem::l(j_add(Mem::l(LevelBss::Lvl_ZonePtrsPtr_l),(Player::dbgSpawnZone * 4)));
Mem::wl(PlayerBss::Plr1_ZonePtr_l,zp);
Mem::wl(PlayerBss::plr1_OldRoomPtr_l,zp);
int32_t fl=(Mem::l(j_add(zp,Defs::ZoneT_Floor_l)) - Hires::PLR_STAND_HEIGHT);
Mem::wl(PlayerBss::Plr1_SnapYOff_l,fl);
Mem::wl(PlayerBss::Plr1_YOff_l,fl);
Mem::wl(PlayerBss::Plr1_SnapTYOff_l,fl);
Mem::ww(PlayerBss::Plr1_SnapXOff_l,Player::dbgSpawnX);
Mem::ww(PlayerBss::Plr1_XOff_l,Player::dbgSpawnX);
Mem::ww(PlayerBss::Plr1_SnapZOff_l,Player::dbgSpawnZ);
Mem::ww(PlayerBss::Plr1_ZOff_l,Player::dbgSpawnZ);
if((Player::dbgSpawnAng >= 0)) {
Mem::ww(PlayerBss::Plr1_AngPos_w,Player::dbgSpawnAng);
Mem::ww(PlayerBss::Plr1_SnapAngPos_w,Player::dbgSpawnAng);
}
}
(d0=Mem::w(j_add(a1,Defs::TBLT_Plr2_StartZoneID_w)));
(a0=Mem::l(LevelBss::Lvl_ZonePtrsPtr_l));
(d0=Mem::l(j_add(a0,(int16_t(d0) * 4))));
Mem::wl(PlayerBss::Plr2_ZonePtr_l,d0);
(a0=Mem::l(PlayerBss::Plr2_ZonePtr_l));
(d0=Mem::l(j_add(a0,Defs::ZoneT_Floor_l)));
(d0-=Hires::PLR_STAND_HEIGHT);
Mem::wl(PlayerBss::Plr2_SnapYOff_l,d0);
Mem::wl(PlayerBss::Plr2_YOff_l,d0);
Mem::wl(PlayerBss::Plr2_SnapTYOff_l,d0);
Mem::wl(PlayerBss::Plr2_YOff_l,d0);
Mem::wl(PlayerBss::plr2_OldRoomPtr_l,Mem::l(PlayerBss::Plr2_ZonePtr_l));
Mem::ww(PlayerBss::Plr2_SnapXOff_l,Mem::uw(j_add(a1,Defs::TBLT_Plr2_StartXPos_w)));
Mem::ww(PlayerBss::Plr2_SnapZOff_l,Mem::uw(j_add(a1,Defs::TBLT_Plr2_StartZPos_w)));
Mem::ww(PlayerBss::Plr2_XOff_l,Mem::uw(j_add(a1,Defs::TBLT_Plr2_StartXPos_w)));
Mem::ww(PlayerBss::Plr2_ZOff_l,Mem::uw(j_add(a1,Defs::TBLT_Plr2_StartZPos_w)));
Mem::wl(PlayerBss::plr2_DefaultEnemyFlags_l,0b010011);
}

void plr_MouseControl(int32_t a0){
SystemC::Sys_ReadMouse();
int32_t a1=TablesData::SinCosTable_vw;
int32_t d1=Mem::uw(j_add(a0,Defs::PlrT_SnapAngSpd_w));
int32_t d0=Mem::uw(HiresData::Vis_AngPos_w);
(d0=TablesData::AMOD_A(d0));
Mem::ww(j_add(a0,Defs::PlrT_SnapAngPos_w),d0);
Mem::ww(j_add(a0,Defs::PlrT_SnapSinVal_w),Mem::uw(j_add(a1,int16_t(d0))));
(a1+=TablesData::COSINE_OFS);
Mem::ww(j_add(a0,Defs::PlrT_SnapCosVal_w),Mem::uw(j_add(a1,int16_t(d0))));
int32_t d6=Mem::l(j_add(a0,Defs::PlrT_SnapXSpdVal_l));
int32_t d7=Mem::l(j_add(a0,Defs::PlrT_SnapZSpdVal_l));
(d6=-(d6));
if((d6 > 0)) {
(d6>>=1);
(d6+=1);
}
else {
(d6>>=1);
}
(d7=-(d7));
if((d7 > 0)) {
(d7>>=1);
(d7+=1);
}
else {
(d7>>=1);
}
int32_t d3=Mem::uw(HiresData::Sys_MouseY);
if((Mem::b(j_add(a0,Defs::PlrT_InvMouse_b)) != 0)) {
(d3=M68k::negw(d3));
}
(d3=M68k::setw(d3,(d3 - Mem::w(HiresData::Sys_OldMouseY))));
Mem::ww(HiresData::Sys_OldMouseY,j_add(Mem::uw(HiresData::Sys_OldMouseY),d3));
(d0=Mem::uw(HireswallData::STOPOFFSET));
int32_t d2=M68k::setw(0,d3);
if((Mem::b(VidBss::Vid_FullScreen_b) != 0)) {
(d2=M68k::muls(d2,85));
}
else {
(d2=M68k::setw(d2,j_shl(d2,7)));
}
Mem::ww(j_add(a0,Defs::PlrT_AimSpeed_l),j_add(Mem::uw(j_add(a0,Defs::PlrT_AimSpeed_l)),d2));
(d0=M68k::setw(d0,j_add(d0,d3)));
if((int16_t(d0) <= Mem::w(HiresData::View_LookMax_w))) {
Mem::ww(j_add(a0,Defs::PlrT_AimSpeed_l),(-(512) * 20));
(d0=M68k::setw(d0,Mem::uw(HiresData::View_LookMax_w)));
}
if((int16_t(d0) >= Mem::w(HiresData::View_LookMin_w))) {
Mem::ww(j_add(a0,Defs::PlrT_AimSpeed_l),(512 * 20));
(d0=M68k::setw(d0,Mem::uw(HiresData::View_LookMin_w)));
}
Mem::ww(HireswallData::STOPOFFSET,d0);
(d0=M68k::negw(d0));
(d0=M68k::setw(d0,j_add(d0,Mem::w(HireswallData::TOTHEMIDDLE))));
Mem::ww(HireswallData::SMIDDLEY,d0);
(d0=M68k::muls(d0,Hires::SCREEN_WIDTH));
Mem::wl(HireswallData::SBIGMIDDLEY,d0);
int32_t a5=TablesBss::KeyMap_vb;
(d7=0);
(d7=M68k::setb(d7,Mem::ub(ControlloopData::next_weapon_key)));
if((Mem::b(ControlloopData::Prefs_OriginalMouse_b) != 0)) {
(d7=M68k::setb(d7,Mem::ub(ControlloopData::forward_key)));
}
Mem::wb(j_add(a5,int16_t(d7)),(CustomChips::potinpBit2()?0:0xFF));
(d7=M68k::setb(d7,Mem::ub(ControlloopData::fire_key)));
Mem::wb(j_add(a5,int16_t(d7)),(CustomChips::ciaaPraBit6()?0:0xFF));
}

void plr_KeyboardControl(int32_t a0){
int32_t a5=TablesBss::KeyMap_vb;
int32_t d7=0;
int32_t d0{};
int32_t d1{};
int32_t d2{};
int32_t d3{};
int32_t d4{};
int32_t d5{};
int32_t d6{};
int32_t a1{};
int32_t a2{};
int32_t a3{};
int32_t a4{};
if((Mem::b(j_add(a5,Hires::QUIT_KEY)) != 0)) {
Mem::wb(ControlloopData::Game_ShouldQuit_b,0xFF);
Mem::wb(HiresData::Game_MasterQuit_b,0xFF);
}
(d7=M68k::setb(d7,Mem::ub(ControlloopData::next_weapon_key)));
if((Mem::b(j_add(a5,int16_t(d7))) != 0)) {
if((Mem::b(PlayerBss::plr_PrevNextWeaponKeyState_b) == 0)) {
Mem::wb(PlayerBss::plr_PrevNextWeaponKeyState_b,0xFF);
(d0=0);
(d0=M68k::setb(d0,Mem::ub(j_add(a0,Defs::PlrT_GunSelected_b))));
(a1=j_add(a0,Defs::PlrT_Weapons_vb));
do {
(d0+=1);
if((int16_t(d0) > 9)) {
(d0=0);
}
}
while((Mem::w(j_add(a1,(int16_t(d0) * 2))) == 0));
Mem::wb(j_add(a0,Defs::PlrT_GunSelected_b),d0);
if(Hires::dbgSwitchTest) j_log(j_add("[switch] -> arme ",d0));
Player::plr_ShowGunName(a0);
}
}
else {
Mem::wb(PlayerBss::plr_PrevNextWeaponKeyState_b,0);
}
for(int32_t g=0;(g <= 9);++(g)){
if((Mem::b(j_add(a5,j_add(g,1))) != 0)) {
if(((Mem::w(j_add(j_add(a0,Defs::PlrT_Weapons_vb),(g * 2))) != 0) && (Mem::ub(j_add(a0,Defs::PlrT_GunSelected_b)) != g))) {
Mem::wb(j_add(a0,Defs::PlrT_GunSelected_b),g);
Player::plr_ShowGunName(a0);
}
}
}
(d7=M68k::setb(d7,Mem::ub(ControlloopData::operate_key)));
(d1=Mem::ub(j_add(a5,int16_t(d7))));
if((int8_t(d1) != 0)) {
if((Mem::b(PlayerBss::plr_PrevUseKeyState_b) == 0)) {
Mem::wb(j_add(a0,Defs::PlrT_Used_b),0xFF);
}
}
Mem::wb(PlayerBss::plr_PrevUseKeyState_b,d1);
(d7=M68k::setb(d7,Mem::ub(ControlloopData::duck_key)));
if((Mem::b(j_add(a5,int16_t(d7))) != 0)) {
Mem::wb(j_add(a5,int16_t(d7)),0);
Mem::wl(j_add(a0,Defs::PlrT_SnapTargHeight_l),Hires::PLR_STAND_HEIGHT);
int32_t nb=(Mem::ub(j_add(a0,Defs::PlrT_Ducked_b)) & 0xFF);
Mem::wb(j_add(a0,Defs::PlrT_Ducked_b),nb);
if((nb != 0)) {
Mem::wl(j_add(a0,Defs::PlrT_SnapTargHeight_l),Hires::PLR_CROUCH_HEIGHT);
}
}
ab3d2::controls::crouch(a0);
(a4=Mem::l(j_add(a0,Defs::PlrT_ZonePtr_l)));
(d0=Mem::l(j_add(a4,Defs::ZoneT_Floor_l)));
(d0-=Mem::l(j_add(a4,Defs::ZoneT_Roof_l)));
if((Mem::b(j_add(a0,Defs::PlrT_StoodInTop_b)) != 0)) {
(d0=Mem::l(j_add(a4,Defs::ZoneT_UpperFloor_l)));
(d0-=Mem::l(j_add(a4,Defs::ZoneT_UpperRoof_l)));
}
Mem::wb(j_add(a0,Defs::PlrT_Squished_b),0);
Mem::wl(j_add(a0,Defs::PlrT_SnapSquishedHeight_l),Hires::PLR_STAND_HEIGHT);
if((d0 <= j_add(Hires::PLR_STAND_HEIGHT,(3 * 1024)))) {
Mem::wb(j_add(a0,Defs::PlrT_Squished_b),0xFF);
Mem::wl(j_add(a0,Defs::PlrT_SnapSquishedHeight_l),Hires::PLR_CROUCH_HEIGHT);
}
(d1=Mem::l(j_add(a0,Defs::PlrT_SnapTargHeight_l)));
(d0=Mem::l(j_add(a0,Defs::PlrT_SnapSquishedHeight_l)));
if((d1 >= d0)) {
(d1=d0);
}
(d0=Mem::l(j_add(a0,Defs::PlrT_SnapHeight_l)));
if((d0 != d1)) {
d0=ab3d2::controls::heightStep(a0,d0,d1);
}
Mem::wl(j_add(a0,Defs::PlrT_SnapHeight_l),d0);
if((Mem::b(j_add(a5,RawKeyMacros::RAWKEY_K)) != 0)) {
Mem::wb(j_add(a5,RawKeyMacros::RAWKEY_K),0);
Mem::wb(j_add(a0,Defs::PlrT_InvMouse_b),0xFF);
Message::Msg_PushLine(TextData::Game_InputKeyboard_vb,(Defs::OPTS_MESSAGE_LENGTH | Defs::MSG_TAG_OPTIONS));
Mem::wb(j_add(a0,Defs::PlrT_Keys_b),0xFF);
Mem::wb(j_add(a0,Defs::PlrT_Path_b),0);
Mem::wb(j_add(a0,Defs::PlrT_Mouse_b),0);
Mem::wb(j_add(a0,Defs::PlrT_Joystick_b),0);
}
if((Mem::b(j_add(a5,RawKeyMacros::RAWKEY_J)) != 0)) {
Mem::wb(j_add(a0,Defs::PlrT_InvMouse_b),0xFF);
Mem::wb(j_add(a5,RawKeyMacros::RAWKEY_J),0);
Mem::wb(j_add(a0,Defs::PlrT_Keys_b),0);
Mem::wb(j_add(a0,Defs::PlrT_Path_b),0);
Mem::wb(j_add(a0,Defs::PlrT_Mouse_b),0);
Mem::wb(j_add(a0,Defs::PlrT_Joystick_b),0xFF);
Message::Msg_PushLine(TextData::Game_InputJoystick_vb,(Defs::OPTS_MESSAGE_LENGTH | Defs::MSG_TAG_OPTIONS));
}
if((Mem::b(j_add(a5,RawKeyMacros::RAWKEY_M)) != 0)) {
Mem::wb(j_add(a5,RawKeyMacros::RAWKEY_M),0);
Mem::wb(j_add(a0,Defs::PlrT_Keys_b),0);
Mem::wb(j_add(a0,Defs::PlrT_Path_b),0);
Mem::wb(j_add(a0,Defs::PlrT_Mouse_b),0xFF);
Mem::wb(j_add(a0,Defs::PlrT_Joystick_b),0);
int32_t v=(Mem::ub(j_add(a0,Defs::PlrT_InvMouse_b)) ^ 0xFF);
Mem::wb(j_add(a0,Defs::PlrT_InvMouse_b),v);
if((v != 0)) {
Message::Msg_PushLine(TextData::Game_InputMouseInv_vb,(Defs::OPTS_MESSAGE_LENGTH | Defs::MSG_TAG_OPTIONS));
}
else {
Message::Msg_PushLine(TextData::Game_InputMouse_vb,(Defs::OPTS_MESSAGE_LENGTH | Defs::MSG_TAG_OPTIONS));
}
}
(a4=j_add(a5,1));
(a2=j_add(a0,Defs::PlrT_Weapons_vb));
(a3=Mem::l(j_add(a0,Defs::PlrT_ObjectPtr_l)));
(d1=9);
(d2=0);
do {
(d0=Mem::uw(a2));
(a2+=2);
(d0=M68k::setb(d0,(d0 & Mem::ub(a4))));
(a4+=1);
if((int8_t(d0) != 0)) {
Mem::wb(j_add(a0,Defs::PlrT_GunSelected_b),d2);
if((a0 == Mem::l(PlayerBss::Plr1_Data))) {
Mem::ww(j_add(j_add(a3,Defs::ENT_NEXT_2),Defs::EntT_Timer1_w),0);
Player::plr_ShowGunName(a0);
}
else {
Mem::ww(j_add(j_add(a3,Defs::ENT_NEXT),Defs::EntT_Timer1_w),0);
Player::plr_ShowGunName(a0);
}
break;
}
(d2+=1);
(d1=M68k::setw(d1,(d1 - 1)));
}
while((int16_t(d1) != -(1)));
if((Mem::b(j_add(a5,RawKeyMacros::RAWKEY_F10)) != 0)) {
if((Mem::b(PlayerBss::lastscr) == 0)) {
Mem::wb(PlayerBss::lastscr,0xFF);
Mem::wb(VidBss::Vid_FullScreenTemp_b,~(Mem::ub(VidBss::Vid_FullScreenTemp_b)));
Mem::wb(C2pData::C2P_NeedsInit_b,0xFF);
}
}
else {
Mem::wb(PlayerBss::lastscr,0);
}
if((Mem::b(j_add(a5,RawKeyMacros::RAWKEY_F7)) != 0)) {
Mem::wb(j_add(a5,RawKeyMacros::RAWKEY_F7),0);
if((Mem::w(SystemBss::Sys_FPSLimit_w) == 5)) {
Mem::ww(SystemBss::Sys_FPSLimit_w,-(1));
}
else {
Mem::ww(SystemBss::Sys_FPSLimit_w,j_add(Mem::w(SystemBss::Sys_FPSLimit_w),1));
}
}
if((Mem::b(j_add(a5,RawKeyMacros::RAWKEY_NUM_DOT)) != 0)) {
Mem::wb(ControlloopData::Prefs_CrossHairColour_b,j_add(Mem::ub(ControlloopData::Prefs_CrossHairColour_b),1));
Mem::wb(ControlloopData::Prefs_CrossHairColour_b,(Mem::ub(ControlloopData::Prefs_CrossHairColour_b) & 7));
Mem::wb(j_add(a5,RawKeyMacros::RAWKEY_NUM_DOT),0);
}
if((Mem::b(j_add(a5,RawKeyMacros::RAWKEY_X)) != 0)) {
Mem::wb(j_add(a5,RawKeyMacros::RAWKEY_X),0);
(a1=ZoneBss::Zone_BackdropDisable_vb);
(d0=Mem::uw(j_add(a0,Defs::PlrT_Zone_w)));
(d1=M68k::setw(0,d0));
(d0=M68k::setw(d0,j_ushr((d0 & 0xFFFF),3)));
(a1+=int16_t(d0));
Mem::wb(a1,(Mem::ub(a1) ^ j_shl(1,(d1 & 7))));
}
if((Mem::b(j_add(a5,RawKeyMacros::RAWKEY_Z)) != 0)) {
Mem::wb(j_add(a5,RawKeyMacros::RAWKEY_Z),0);
(d0=(j_div(ZoneBss::ZONE_BACKDROP_DISABLE_SIZE,16) - 1));
(a1=ZoneBss::Zone_BackdropDisable_vb);
do {
Mem::wl(a1,0);
(a1+=4);
Mem::wl(a1,0);
(a1+=4);
Mem::wl(a1,0);
(a1+=4);
Mem::wl(a1,0);
(a1+=4);
(d0=M68k::setw(d0,(d0 - 1)));
}
while((int16_t(d0) != -(1)));
}
Player::devCheckKey(a5,RawKeyMacros::RAWKEY_V,DevMacros::DEV_SKIP_DUMP_BG_DISABLE);
Player::devCheckKey(a5,RawKeyMacros::RAWKEY_E,DevMacros::DEV_SKIP_SIMPLE_WALLS);
Player::devCheckKey(a5,RawKeyMacros::RAWKEY_R,DevMacros::DEV_SKIP_SHADED_WALLS);
Player::devCheckKey(a5,RawKeyMacros::RAWKEY_T,DevMacros::DEV_SKIP_BITMAPS);
Player::devCheckKey(a5,RawKeyMacros::RAWKEY_Y,DevMacros::DEV_SKIP_GLARE_BITMAPS);
Player::devCheckKey(a5,RawKeyMacros::RAWKEY_U,DevMacros::DEV_SKIP_ADDITIVE_BITMAPS);
Player::devCheckKey(a5,RawKeyMacros::RAWKEY_I,DevMacros::DEV_SKIP_LIGHTSOURCED_BITMAPS);
Player::devCheckKey(a5,RawKeyMacros::RAWKEY_O,DevMacros::DEV_SKIP_POLYGON_MODELS);
Player::devCheckKey(a5,RawKeyMacros::RAWKEY_G,DevMacros::DEV_SKIP_FLATS);
Player::devCheckKey(a5,RawKeyMacros::RAWKEY_Q,DevMacros::DEV_SKIP_FASTBUFFER_CLEAR);
Player::devCheckKey(a5,RawKeyMacros::RAWKEY_N,DevMacros::DEV_SKIP_AI_ATTACK);
Player::devCheckKey(a5,RawKeyMacros::RAWKEY_B,DevMacros::DEV_SKIP_LIGHTING);
Player::devCheckKey(a5,RawKeyMacros::RAWKEY_H,DevMacros::DEV_SKIP_OVERLAY);
Player::devCheckKey(a5,RawKeyMacros::RAWKEY_COMMA,DevMacros::DEV_ZONE_TRACE);
Player::devCheckKey(a5,RawKeyMacros::RAWKEY_LSQR_BRKT,DevMacros::DEV_SKIP_EDGE_PVS);
(a1=TablesData::SinCosTable_vw);
(a5=TablesBss::KeyMap_vb);
(d0=Mem::uw(HireswallData::STOPOFFSET));
(d7=0);
(d7=M68k::setb(d7,Mem::ub(ControlloopData::look_up_key)));
if((Mem::b(j_add(a5,int16_t(d7))) != 0)) {
Mem::ww(j_add(a0,Defs::PlrT_AimSpeed_l),(Mem::uw(j_add(a0,Defs::PlrT_AimSpeed_l)) - 512));
(d0=M68k::setw(d0,(d0 - Mem::w(HiresData::View_KeyLook_w))));
if((int16_t(d0) <= Mem::w(HiresData::View_LookMax_w))) {
Mem::ww(j_add(a0,Defs::PlrT_AimSpeed_l),(-(512) * 20));
(d0=M68k::setw(d0,Mem::uw(HiresData::View_LookMax_w)));
}
}
(d7=0);
(d7=M68k::setb(d7,Mem::ub(ControlloopData::look_down_key)));
if((Mem::b(j_add(a5,int16_t(d7))) != 0)) {
Mem::ww(j_add(a0,Defs::PlrT_AimSpeed_l),j_add(Mem::uw(j_add(a0,Defs::PlrT_AimSpeed_l)),512));
(d0=M68k::setw(d0,j_add(d0,Mem::w(HiresData::View_KeyLook_w))));
if((int16_t(d0) >= Mem::w(HiresData::View_LookMin_w))) {
Mem::ww(j_add(a0,Defs::PlrT_AimSpeed_l),(512 * 20));
(d0=M68k::setw(d0,Mem::uw(HiresData::View_LookMin_w)));
}
}
(d7=M68k::setb(d7,Mem::ub(ControlloopData::centre_view_key)));
if((Mem::b(j_add(a5,int16_t(d7))) != 0)) {
if((Mem::b(HiresData::Plr_OldCentre_b) == 0)) {
Mem::wb(HiresData::Plr_OldCentre_b,0xFF);
(d0=M68k::setw(d0,0));
Mem::ww(j_add(a0,Defs::PlrT_AimSpeed_l),0);
}
}
else {
Mem::wb(HiresData::Plr_OldCentre_b,0);
}
Mem::ww(HireswallData::STOPOFFSET,d0);
(d0=M68k::negw(d0));
(d0=M68k::setw(d0,j_add(d0,Mem::w(HireswallData::TOTHEMIDDLE))));
Mem::ww(HireswallData::SMIDDLEY,d0);
(d0=M68k::muls(d0,Hires::SCREEN_WIDTH));
Mem::wl(HireswallData::SBIGMIDDLEY,d0);
(d0=Mem::uw(j_add(a0,Defs::PlrT_SnapAngPos_w)));
(d3=Mem::uw(j_add(a0,Defs::PlrT_SnapAngSpd_w)));
if((Mem::b(ControlloopData::Prefs_AlwaysRun_b) == 0)) {
(d1=35);
(d2=2);
Mem::ww(PlayerBss::Plr_TurnSpeed_w,10);
(d7=0);
(d7=M68k::setb(d7,Mem::ub(ControlloopData::run_key)));
if((Mem::b(j_add(a5,int16_t(d7))) != 0)) {
(d1=60);
(d2=3);
Mem::ww(PlayerBss::Plr_TurnSpeed_w,14);
}
}
else {
(d1=60);
(d2=3);
Mem::ww(PlayerBss::Plr_TurnSpeed_w,14);
(d7=0);
(d7=M68k::setb(d7,Mem::ub(ControlloopData::run_key)));
if((Mem::b(j_add(a5,int16_t(d7))) != 0)) {
(d1=35);
(d2=2);
Mem::ww(PlayerBss::Plr_TurnSpeed_w,10);
}
}
if(((Mem::b(j_add(a0,Defs::PlrT_Squished_b)) != 0) || (Mem::b(j_add(a0,Defs::PlrT_Ducked_b)) != 0))) {
(d2=M68k::setw(d2,j_shr(int16_t(d2),1)));
}
(d4=0);
if((Mem::b(PlayerBss::Plr_Decelerate_b) != 0)) {
(d5=M68k::setw(0,d3));
(d5=M68k::setw(d5,j_add(d5,d5)));
(d3=M68k::setw(d3,j_add(d3,d5)));
(d3=M68k::setw(d3,j_shr(int16_t(d3),2)));
if((int16_t(d3) < 0)) {
(d3=M68k::setw(d3,j_add(d3,1)));
}
}
Mem::wb(ControlloopData::templeftkey,Mem::ub(ControlloopData::turn_left_key));
Mem::wb(ControlloopData::temprightkey,Mem::ub(ControlloopData::turn_right_key));
Mem::wb(ControlloopData::tempslkey,Mem::ub(ControlloopData::sidestep_left_key));
Mem::wb(ControlloopData::tempsrkey,Mem::ub(ControlloopData::sidestep_right_key));
(d7=M68k::setb(d7,Mem::ub(ControlloopData::force_sidestep_key)));
if((Mem::b(j_add(a5,int16_t(d7))) != 0)) {
Mem::wb(ControlloopData::tempslkey,Mem::ub(ControlloopData::templeftkey));
Mem::wb(ControlloopData::tempsrkey,Mem::ub(ControlloopData::temprightkey));
Mem::wb(ControlloopData::templeftkey,255);
Mem::wb(ControlloopData::temprightkey,255);
}
if((Mem::b(PlayerBss::Plr_Decelerate_b) != 0)) {
(d7=M68k::setb(d7,Mem::ub(ControlloopData::templeftkey)));
if((Mem::b(j_add(a5,int16_t(d7))) != 0)) {
(d3=M68k::setw(d3,(d3 - Mem::w(PlayerBss::Plr_TurnSpeed_w))));
}
(a5=TablesBss::KeyMap_vb);
(d7=M68k::setb(d7,Mem::ub(ControlloopData::temprightkey)));
if((Mem::b(j_add(a5,int16_t(d7))) != 0)) {
(d3=M68k::setw(d3,j_add(d3,Mem::w(PlayerBss::Plr_TurnSpeed_w))));
}
if((int16_t(d3) > int16_t(d1))) {
(d3=M68k::setw(d3,d1));
}
(d1=M68k::negw(d1));
if((int16_t(d3) < int16_t(d1))) {
(d3=M68k::setw(d3,d1));
}
}
(d0=M68k::setw(d0,j_add(d0,d3)));
(d0=M68k::setw(d0,j_add(d0,d3)));
Mem::ww(j_add(a0,Defs::PlrT_SnapAngSpd_w),d3);
(d7=M68k::setb(d7,Mem::ub(ControlloopData::tempslkey)));
if((Mem::b(j_add(a5,int16_t(d7))) != 0)) {
(d4=M68k::setw(d4,j_add(d4,d2)));
(d4=M68k::setw(d4,j_add(d4,d2)));
(d4=M68k::setw(d4,j_shr(int16_t(d4),1)));
}
(a5=TablesBss::KeyMap_vb);
(d7=M68k::setb(d7,Mem::ub(ControlloopData::tempsrkey)));
if((Mem::b(j_add(a5,int16_t(d7))) != 0)) {
(d4=M68k::setw(d4,j_add(d4,d2)));
(d4=M68k::setw(d4,j_add(d4,d2)));
(d4=M68k::setw(d4,j_shr(int16_t(d4),1)));
(d4=M68k::negw(d4));
}
(d0=TablesData::AMOD_I(d0));
Mem::ww(j_add(a0,Defs::PlrT_SnapAngPos_w),d0);
Mem::ww(j_add(a0,Defs::PlrT_SnapSinVal_w),Mem::uw(j_add(a1,int16_t(d0))));
(a1+=TablesData::COSINE_OFS);
Mem::ww(j_add(a0,Defs::PlrT_SnapCosVal_w),Mem::uw(j_add(a1,int16_t(d0))));
(d6=Mem::l(j_add(a0,Defs::PlrT_SnapXSpdVal_l)));
(d7=Mem::l(j_add(a0,Defs::PlrT_SnapZSpdVal_l)));
if((Mem::b(PlayerBss::Plr_Decelerate_b) != 0)) {
(d6=-(d6));
if((d6 > 0)) {
(d6>>=3);
(d6+=1);
}
else {
(d6>>=3);
}
(d7=-(d7));
if((d7 > 0)) {
(d7>>=3);
(d7+=1);
}
else {
(d7>>=3);
}
}
(d3=0);
(d5=0);
(d5=M68k::setb(d5,Mem::ub(ControlloopData::forward_key)));
if((Mem::b(j_add(a5,int16_t(d5))) != 0)) {
(d2=M68k::negw(d2));
(d3=M68k::setw(d3,d2));
}
(d5=M68k::setb(d5,Mem::ub(ControlloopData::backward_key)));
if((Mem::b(j_add(a5,int16_t(d5))) != 0)) {
(d3=M68k::setw(d3,d2));
}
(d2=M68k::setw(d2,d3));
(d2=M68k::setw(d2,j_shl(d2,6)));
(d1=M68k::setw(0,d2));
Mem::ww(PlayerBss::Plr_AddToBobble_w,d1);
(d1=Mem::uw(j_add(a0,Defs::PlrT_SnapSinVal_w)));
(d1=M68k::muls(d1,d3));
(d2=Mem::uw(j_add(a0,Defs::PlrT_SnapCosVal_w)));
(d2=M68k::muls(d2,d3));
(d6-=d1);
(d7-=d2);
(d1=Mem::uw(j_add(a0,Defs::PlrT_SnapSinVal_w)));
(d1=M68k::muls(d1,d4));
(d2=Mem::uw(j_add(a0,Defs::PlrT_SnapCosVal_w)));
(d2=M68k::muls(d2,d4));
(d6-=d2);
(d7+=d1);
ab3d2::controls::accelerate(a0,d6,d7);
if((Mem::b(PlayerBss::Plr_Decelerate_b) != 0)) {
Mem::wl(j_add(a0,Defs::PlrT_SnapXSpdVal_l),j_add(Mem::l(j_add(a0,Defs::PlrT_SnapXSpdVal_l)),d6));
Mem::wl(j_add(a0,Defs::PlrT_SnapZSpdVal_l),j_add(Mem::l(j_add(a0,Defs::PlrT_SnapZSpdVal_l)),d7));
}
(d6=Mem::l(j_add(a0,Defs::PlrT_SnapXSpdVal_l)));
(d7=Mem::l(j_add(a0,Defs::PlrT_SnapZSpdVal_l)));
ab3d2::controls::roomMove(a0,d6,d7);
Mem::wl(j_add(a0,Defs::PlrT_SnapXOff_l),j_add(Mem::l(j_add(a0,Defs::PlrT_SnapXOff_l)),d6));
Mem::wl(j_add(a0,Defs::PlrT_SnapZOff_l),j_add(Mem::l(j_add(a0,Defs::PlrT_SnapZOff_l)),d7));
(d5=M68k::setb(d5,Mem::ub(ControlloopData::fire_key)));
if((Mem::b(j_add(a0,Defs::PlrT_Fire_b)) != 0)) {
if((Mem::b(j_add(a5,int16_t(d5))) != 0)) {
Mem::wb(j_add(a0,Defs::PlrT_Fire_b),0xFF);
return ;
}
Mem::wb(j_add(a0,Defs::PlrT_Fire_b),0);
return ;
}
if((Mem::b(j_add(a5,int16_t(d5))) == 0)) {
Mem::wb(j_add(a0,Defs::PlrT_Fire_b),0);
return ;
}
Mem::wb(j_add(a0,Defs::PlrT_Clicked_b),0xFF);
Mem::wb(j_add(a0,Defs::PlrT_Fire_b),0xFF);
}

void devCheckKey(int32_t a5,int32_t rawkey,int32_t devBit){
if((Mem::b(j_add(a5,rawkey)) != 0)) {
Mem::wb(j_add(a5,rawkey),0);
DevMacros::DEV_TOGGLE(DevInst::Dev_DebugFlags_l,devBit);
}
}

void plr_ShowGunName(int32_t a0){
int32_t d0=Mem::ub(j_add(a0,Defs::PlrT_GunSelected_b));
int32_t a4=Mem::l(HiresData::GLF_DatabasePtr_l);
(a4+=Defs::GLFT_GunNames_l);
(d0=M68k::muls(d0,Defs::GLFT_GUN_NAME_LENGTH));
(a4+=d0);
Message::Msg_PushLineDedupLast(a4,(Defs::GLFT_GUN_NAME_LENGTH | Defs::MSG_TAG_OTHER));
}

void plr_Fall(int32_t a0){
int32_t d0=Mem::l(j_add(a0,Defs::PlrT_SnapTYOff_l));
int32_t d1=Mem::l(j_add(a0,Defs::PlrT_SnapYOff_l));
int32_t d2=Mem::l(j_add(a0,Defs::PlrT_SnapYVel_l));
int32_t d3{};
int32_t d4{};
int32_t a2{};
int32_t a4{};
if((d0 < d1)) {
Mem::wb(PlayerBss::Plr_Decelerate_b,0xFF);
(d0-=d1);
if((d0 < -(512))) {
(d0=-(512));
}
(d1+=d0);
Player::proceed(a0,d1,d2);
return ;
}
if((d0 == d1)) {
(d2=Mem::w(j_add(a0,Defs::PlrT_FloorSpd_w)));
(d2<<=6);
(a4=Mem::l(j_add(a0,Defs::PlrT_ObjectPtr_l)));
(d3=Mem::w(PlayerBss::plr_FallDamage_w));
(d3=M68k::setw(d3,(d3 - 100)));
if((int16_t(d3) > 0)) {
Mem::wb(j_add(a4,Defs::EntT_DamageTaken_b),j_add(Mem::ub(j_add(a4,Defs::EntT_DamageTaken_b)),d3));
}
Mem::wb(PlayerBss::Plr_Decelerate_b,0xFF);
Mem::ww(PlayerBss::plr_FallDamage_w,0);
(d3=Mem::uw(PlayerBss::Plr_AddToBobble_w));
(d4=M68k::setw(0,d3));
(d3=M68k::setw(d3,j_add(d3,Mem::uw(j_add(a0,Defs::PlrT_Bobble_w)))));
(d3=TablesData::AMOD_A(d3));
Mem::ww(j_add(a0,Defs::PlrT_Bobble_w),d3);
(d4=M68k::setw(d4,j_add(d4,Mem::uw(j_add(a0,Defs::PlrT_WalkSFXTime_w)))));
(d3=M68k::setw(d3,d4));
(d4=M68k::setw(d4,(d4 & 4095)));
Mem::ww(j_add(a0,Defs::PlrT_WalkSFXTime_w),d4);
(d3=M68k::setw(d3,(d3 & -(4096))));
if((int16_t(d3) != 0)) {
Player::plr_DoFootstepFX(a0);
}
Mem::wl(PlayerBss::plr_JumpSpeed_l,-(1024));
(a2=Mem::l(j_add(a0,Defs::PlrT_ZonePtr_l)));
int32_t dw=Mem::l(j_add(a2,Defs::ZoneT_Water_l));
if((d1 >= dw)) {
Mem::wl(PlayerBss::plr_JumpSpeed_l,-(512));
}
if((Mem::w(j_add(a0,Defs::PlrT_Health_w)) > 0)) {
int32_t a5=TablesBss::KeyMap_vb;
int32_t d7=0;
(d7=M68k::setb(d7,Mem::ub(ControlloopData::jump_key)));
if((Mem::b(j_add(a5,int16_t(d7))) != 0)) {
(d2=Mem::l(PlayerBss::plr_JumpSpeed_l));
}
}
if((d2 > 0)) {
(d2=0);
}
(d1+=d2);
Player::proceed(a0,d1,d2);
return ;
}
Mem::wb(PlayerBss::Plr_Decelerate_b,0);
if(((Mem::w(j_add(a0,Defs::PlrT_Jetpack_w)) != 0) && (Mem::w(j_add(a0,Defs::PlrT_JetpackFuel_w)) != 0))) {
if((Mem::w(j_add(a0,Defs::PlrT_JetpackFuel_w)) > 250)) {
Mem::ww(j_add(a0,Defs::PlrT_JetpackFuel_w),250);
}
Mem::wb(PlayerBss::Plr_Decelerate_b,0xFF);
Mem::wl(PlayerBss::plr_JumpSpeed_l,-(128));
int32_t a5=TablesBss::KeyMap_vb;
int32_t d7=0;
(d7=M68k::setb(d7,Mem::ub(ControlloopData::jump_key)));
if((Mem::b(j_add(a5,int16_t(d7))) != 0)) {
Mem::ww(j_add(a0,Defs::PlrT_JetpackFuel_w),(Mem::w(j_add(a0,Defs::PlrT_JetpackFuel_w)) - 1));
(d2+=Mem::l(PlayerBss::plr_JumpSpeed_l));
Mem::ww(PlayerBss::plr_FallDamage_w,0);
(d3=40);
(d3=M68k::setw(d3,j_add(d3,Mem::uw(j_add(a0,Defs::PlrT_Bobble_w)))));
(d3=TablesData::AMOD_A(d3));
Mem::ww(j_add(a0,Defs::PlrT_Bobble_w),d3);
}
}
(d3=d0);
(d3-=d1);
if((d3 <= (16 * 64))) {
Mem::wb(PlayerBss::Plr_Decelerate_b,0xFF);
}
(d1+=d2);
if((d0 <= d1)) {
(d3=Mem::w(PlayerBss::plr_FallDamage_w));
(d3=M68k::setw(d3,(d3 - 100)));
if((int16_t(d3) > 0)) {
(a4=Mem::l(j_add(a0,Defs::PlrT_ObjectPtr_l)));
Mem::wb(j_add(a4,Defs::EntT_DamageTaken_b),j_add(Mem::ub(j_add(a4,Defs::EntT_DamageTaken_b)),d3));
}
Mem::ww(PlayerBss::plr_FallDamage_w,0);
(d2=Mem::w(j_add(a0,Defs::PlrT_FloorSpd_w)));
(d2<<=6);
Player::proceed(a0,d1,d2);
return ;
}
(d2+=64);
Mem::ww(PlayerBss::plr_FallDamage_w,j_add(Mem::uw(PlayerBss::plr_FallDamage_w),1));
(a2=Mem::l(j_add(a0,Defs::PlrT_ZonePtr_l)));
(d0=Mem::l(j_add(a2,Defs::ZoneT_Water_l)));
if((d1 >= d0)) {
if((d0 >= Mem::l(PlayerBss::plr_OldHeight_l))) {
Mem::ww(HiresData::Aud_SampleNum_w,6);
Mem::ww(HiresData::Aud_NoiseX_w,0);
Mem::ww(HiresData::Aud_NoiseZ_w,100);
Mem::ww(HiresData::Aud_NoiseVol_w,80);
Mem::ww(HiresData::IDNUM,0xfff8);
Mem::wb(HiresData::notifplaying,0);
Hires::MakeSomeNoise();
}
Mem::wb(PlayerBss::Plr_Decelerate_b,0xFF);
Mem::ww(PlayerBss::plr_FallDamage_w,0);
if((d2 >= 512)) {
(d2=512);
}
}
Player::proceed(a0,d1,d2);
}

void proceed(int32_t a0,int32_t d1,int32_t d2){
int32_t a2=Mem::l(j_add(a0,Defs::PlrT_ZonePtr_l));
int32_t d3=Mem::l(j_add(a2,Defs::ZoneT_Roof_l));
if((Mem::b(j_add(a0,Defs::PlrT_StoodInTop_b)) != 0)) {
(d3=Mem::l(j_add(a2,Defs::ZoneT_UpperRoof_l)));
}
(d3+=(10 * 256));
if((d3 >= d1)) {
(d1=d3);
if((d2 < 0)) {
(d2=0);
}
}
Mem::wl(j_add(a0,Defs::PlrT_SnapYVel_l),d2);
Mem::wl(j_add(a0,Defs::PlrT_SnapYOff_l),d1);
}

void plr_DoFootstepFX(int32_t a0){
int32_t a1=Mem::l(j_add(a0,Defs::PlrT_ZonePtr_l));
int32_t d0=Mem::uw(j_add(a1,Defs::ZoneT_FloorNoise_w));
int32_t d1=Mem::l(j_add(a1,Defs::ZoneT_Water_l));
bool haveWater=false;
if((((d1 < Mem::l(j_add(a1,Defs::ZoneT_Floor_l))) && (d1 >= Mem::l(j_add(a0,Defs::PlrT_YOff_l)))) && (Mem::b(j_add(a0,Defs::PlrT_StoodInTop_b)) == 0))) {
(d0=6);
(haveWater=true);
}
if(!(haveWater)) {
if((Mem::b(j_add(a0,Defs::PlrT_StoodInTop_b)) != 0)) {
(d0=Mem::uw(j_add(a1,Defs::ZoneT_UpperFloorNoise_w)));
}
(a1=Mem::l(HiresData::GLF_DatabasePtr_l));
(a1+=Defs::GLFT_FloorData_l);
(d0=Mem::uw(j_add(j_add(a1,(int16_t(d0) * 4)),2)));
(d0=M68k::setw(d0,(d0 - 1)));
if((int16_t(d0) < 0)) {
return ;
}
}
Mem::ww(HiresData::Aud_SampleNum_w,d0);
Mem::ww(HiresData::Aud_NoiseX_w,0);
Mem::ww(HiresData::Aud_NoiseZ_w,100);
Mem::ww(HiresData::Aud_NoiseVol_w,80);
Mem::ww(HiresData::IDNUM,0xfff8);
Mem::wb(HiresData::notifplaying,0);
Mem::wb(HiresData::SourceEcho,Mem::ub(j_add(a0,Defs::PlrT_Echo_b)));
Hires::MakeSomeNoise();
}

}