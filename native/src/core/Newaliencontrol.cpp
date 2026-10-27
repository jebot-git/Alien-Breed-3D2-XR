#include "original.hpp"
namespace Newaliencontrol {
void ItsAnAlien(int32_t a0){
if((Mem::b(AiBss::AI_NoEnemies_b) == 0)) {
Mem::ww(j_add(a0,Defs::ObjT_ZoneID_w),-(1));
return ;
}
Mem::wl(ObjectmoveData::StepUpVal,(32 * 256));
Mem::wl(ObjectmoveData::StepDownVal,(32 * 256));
Mem::ww(j_add(a0,Defs::EntT_ZoneID_w),Mem::uw(j_add(a0,Defs::ObjT_ZoneID_w)));
int32_t d2=Mem::w(j_add(a0,Defs::ObjT_ZoneID_w));
if((d2 < 0)) {
return ;
}
int32_t a5=Mem::l(LevelBss::Lvl_ZonePtrsPtr_l);
int32_t d0=Mem::l(j_add(a5,(int16_t(d2) * 4)));
Mem::wl(ObjectmoveData::Obj_ZonePtr_l,d0);
int32_t a6=d0;
Mem::wb(NewaliencontrolData::ALIENECHO,Mem::ub(j_add(a6,Defs::ZoneT_Echo_b)));
(d0=0);
(a6=Mem::l(HiresData::GLF_DatabasePtr_l));
(a5=a6);
(d0=M68k::setb(d0,Mem::ub(j_add(a0,Defs::EntT_Type_b))));
(a5+=Defs::GLFT_AlienBrights_l);
int32_t d1=Mem::uw(j_add(a5,(int16_t(d0) * 2)));
(d1=M68k::setw(d1,-(int16_t(d1))));
Mem::ww(NewaliencontrolData::ALIENBRIGHT,d1);
(d0=M68k::muls(d0,Defs::A_AnimLen));
(a6+=Defs::GLFT_AlienAnims_l);
(a6+=d0);
Mem::wl(NewaliencontrolData::AlienAnimPtr_l,a6);
int32_t a1=Mem::l(HiresData::GLF_DatabasePtr_l);
int32_t a2=a1;
(a2+=Defs::GLFT_AlienShootDefs_l);
(a1=j_add(a1,Defs::GLFT_AlienDefs_l));
(d0=0);
(d0=M68k::setb(d0,Mem::ub(j_add(a0,Defs::EntT_Type_b))));
(d1=Mem::l(j_add(a2,(int16_t(d0) * 8))));
(d1<<=7);
Mem::wl(NewaliencontrolData::SHOTYOFF,d1);
(d1=Mem::uw(j_add(j_add(a2,(int16_t(d0) * 8)),6)));
(d1=M68k::setw(d1,-(int16_t(d1))));
(d1=M68k::setw(d1,j_shl(d1,2)));
Mem::ww(NewaliencontrolData::SHOTOFFMULT,d1);
(d0=M68k::muls(d0,Defs::AlienT_SizeOf_l));
(a1+=int16_t(d0));
(d0=Mem::w(j_add(a1,Defs::AlienT_Height_w)));
(d0<<=7);
Mem::wl(ObjectmoveData::thingheight,d0);
Mem::ww(HiresData::AUXOBJ,Mem::uw(j_add(a1,Defs::AlienT_Auxilliary_w)));
Mem::ww(HiresData::CollId,Mem::uw(a0));
Mem::wb(AiBss::AI_VecObj_w,Mem::ub(j_add(a1,1)));
Mem::ww(AiBss::AI_ReactionTime_w,Mem::uw(j_add(a1,Defs::AlienT_ReactionTime_w)));
Mem::ww(AiBss::AI_DefaultMode_w,Mem::uw(j_add(a1,Defs::AlienT_DefaultBehaviour_w)));
Mem::ww(AiBss::AI_ResponseMode_w,Mem::uw(j_add(a1,Defs::AlienT_ResponseBehaviour_w)));
Mem::ww(AiBss::AI_RetreatMode_w,Mem::uw(j_add(a1,Defs::AlienT_RetreatBehaviour_w)));
Mem::ww(AiBss::AI_FollowupMode_w,Mem::uw(j_add(a1,Defs::AlienT_FollowupBehaviour_w)));
Mem::ww(AiBss::AI_ProwlSpeed_w,Mem::uw(j_add(a1,Defs::AlienT_DefaultSpeed_w)));
Mem::ww(AiBss::AI_ResponseSpeed_w,Mem::uw(j_add(a1,Defs::AlienT_ResponseSpeed_w)));
Mem::ww(AiBss::AI_RetreatSpeed_w,Mem::uw(j_add(a1,Defs::AlienT_RetreatSpeed_w)));
Mem::ww(AiBss::AI_FollowupSpeed_w,Mem::uw(j_add(a1,Defs::AlienT_FollowupSpeed_w)));
Mem::ww(AiBss::AI_FollowupTimer_w,Mem::uw(j_add(a1,Defs::AlienT_FollowupTimeout_w)));
(d0=Mem::uw(j_add(a1,Defs::AlienT_Girth_w)));
Mem::wb(ObjectmoveData::Obj_AwayFromWall_b,Mem::ub(j_add(j_add(NewaliencontrolData::diststowall,(int16_t(d0) * 4)),1)));
Mem::ww(ObjectmoveData::Obj_ExtLen_w,Mem::uw(j_add(j_add(NewaliencontrolData::diststowall,(int16_t(d0) * 4)),2)));
Ai::AI_MainRoutine(a0);
}

void ItsAnObject(int32_t a0){
int32_t a1=Mem::l(HiresData::GLF_DatabasePtr_l);
(a1=j_add(a1,Defs::GLFT_ObjectDefs));
int32_t d0=0;
(d0=M68k::setb(d0,Mem::ub(j_add(a0,Defs::EntT_Type_b))));
(d0=M68k::muls(d0,Defs::ODefT_SizeOf_l));
(a1+=int16_t(d0));
Mem::wl(NewaliencontrolData::obj_StatPtr_l,a1);
(d0=Mem::w(a1));
if((d0 < Defs::ENT_TYPE_ACTIVATABLE)) {
Newaliencontrol::Collectable(a0,a1);
return ;
}
if((d0 == Defs::ENT_TYPE_ACTIVATABLE)) {
Newaliencontrol::Activatable(a0,a1);
return ;
}
if((d0 < Defs::ENT_TYPE_DECORATION)) {
Newaliencontrol::Destructable(a0,a1);
return ;
}
if((d0 == Defs::ENT_TYPE_DECORATION)) {
Newaliencontrol::Decoration(a0,a1);
}
}

int32_t worryHeight(int32_t a0,int32_t a2stats){
int32_t d0=Mem::w(j_add(a0,Defs::ObjT_ZoneID_w));
int32_t a1=Mem::l(LevelBss::Lvl_ZonePtrsPtr_l);
(a1=Mem::l(j_add(a1,(int16_t(d0) * 4))));
int32_t h{};
if((Mem::w(j_add(a2stats,Defs::ODefT_FloorCeiling_w)) != 0)) {
(h=Mem::l(j_add(a1,Defs::ZoneT_Roof_l)));
if((Mem::b(j_add(a0,Defs::ShotT_InUpperZone_b)) != 0)) {
(h=Mem::l(j_add(a1,Defs::ZoneT_UpperRoof_l)));
}
}
else {
(h=Mem::l(j_add(a1,Defs::ZoneT_Floor_l)));
if((Mem::b(j_add(a0,Defs::ShotT_InUpperZone_b)) != 0)) {
(h=Mem::l(j_add(a1,Defs::ZoneT_UpperFloor_l)));
}
}
return j_shr(h,7);
}

void GUNHELD(int32_t a0,int32_t a1){
int32_t a2=a1;
Newaliencontrol::ACTANIMOBJ(a0,a2);
}

void Collectable(int32_t a0,int32_t a1){
int32_t d0=Mem::w(j_add(a0,Defs::ObjT_ZoneID_w));
if((d0 < 0)) {
return ;
}
if((Mem::b(j_add(a0,Defs::EntT_WhichAnim_b)) != 0)) {
Newaliencontrol::GUNHELD(a0,a1);
return ;
}
Mem::ww(j_add(a0,Defs::EntT_ZoneID_w),d0);
if((Mem::b(AiBss::AI_NoEnemies_b) != 0)) {
int32_t d1=Mem::l(j_add(a0,Defs::EntT_DoorsAndLiftsHeld_l));
Mem::wl(AnimBss::Anim_DoorAndLiftLocks_l,(Mem::l(AnimBss::Anim_DoorAndLiftLocks_l) | d1));
}
if((Mem::b(j_add(a0,Defs::ShotT_Worry_b)) == 0)) {
return ;
}
Mem::wb(j_add(a0,Defs::ShotT_Worry_b),(Mem::ub(j_add(a0,Defs::ShotT_Worry_b)) & 0x80));
int32_t a2=a1;
Mem::ww(j_add(a0,4),Newaliencontrol::worryHeight(a0,a2));
Newaliencontrol::DEFANIMOBJ(a0,a2);
(d0=Newaliencontrol::Plr1_CheckObjectCollide(a0));
if(Newaliencontrol::dbgCollect) j_log(j_add(j_add(j_add("[collect] def=",Mem::ub(j_add(a0,Defs::EntT_Type_b)))," worry collide="),(int8_t(d0) != 0)));
if((int8_t(d0) != 0)) {
(d0=Newaliencontrol::Plr1_CollectItem(a0));
if(Newaliencontrol::dbgCollect) j_log(j_add("[collect]   CollectItem=",int16_t(d0)));
if((int16_t(d0) != 0)) {
Mem::ww(j_add(a0,Defs::ObjT_ZoneID_w),-(1));
Mem::wb(j_add(a0,Defs::ShotT_Worry_b),0);
}
}
if((int8_t(Mem::b(PlayerBss::Plr_MultiplayerType_b)) != Hires::PLR_SINGLE)) {
(d0=Newaliencontrol::Plr2_CheckObjectCollide(a0));
if((int8_t(d0) != 0)) {
(d0=Newaliencontrol::Plr2_CollectItem(a0));
if((int16_t(d0) != 0)) {
Mem::ww(j_add(a0,Defs::ObjT_ZoneID_w),-(1));
Mem::wb(j_add(a0,Defs::ShotT_Worry_b),0);
}
}
}
}

void Activatable(int32_t a0,int32_t a1){
int32_t d0=Mem::w(j_add(a0,Defs::ObjT_ZoneID_w));
if((d0 < 0)) {
return ;
}
if((Mem::b(j_add(a0,Defs::EntT_WhichAnim_b)) != 0)) {
Newaliencontrol::ACTIVATED(a0,a1,d0);
return ;
}
Mem::ww(j_add(a0,Defs::EntT_ZoneID_w),d0);
if((Mem::b(AiBss::AI_NoEnemies_b) != 0)) {
int32_t d1=Mem::l(j_add(a0,Defs::EntT_DoorsAndLiftsHeld_l));
Mem::wl(AnimBss::Anim_DoorAndLiftLocks_l,(Mem::l(AnimBss::Anim_DoorAndLiftLocks_l) | d1));
}
if((Mem::b(j_add(a0,Defs::ShotT_Worry_b)) == 0)) {
return ;
}
Mem::wb(j_add(a0,Defs::ShotT_Worry_b),(Mem::ub(j_add(a0,Defs::ShotT_Worry_b)) & 0x80));
int32_t a2=a1;
Mem::ww(j_add(a0,4),Newaliencontrol::worryHeight(a0,a2));
Newaliencontrol::DEFANIMOBJ(a0,a2);
(d0=Newaliencontrol::Plr1_CheckObjectCollide(a0));
if(((int8_t(d0) != 0) && (Mem::b(PlayerBss::Plr1_TmpSpcTap_b) != 0))) {
Newaliencontrol::Plr1_CollectItem(a0);
Mem::ww(j_add(a0,Defs::EntT_Timer1_w),0);
Mem::wb(j_add(a0,Defs::EntT_WhichAnim_b),0xFF);
Mem::ww(j_add(a0,Defs::EntT_Timer2_w),0);
return ;
}
if((int8_t(Mem::b(PlayerBss::Plr_MultiplayerType_b)) != Hires::PLR_SINGLE)) {
(d0=Newaliencontrol::Plr2_CheckObjectCollide(a0));
if(((int8_t(d0) != 0) && (Mem::b(PlayerBss::Plr2_TmpSpcTap_b) != 0))) {
Newaliencontrol::Plr2_CollectItem(a0);
Mem::ww(j_add(a0,Defs::EntT_Timer1_w),0);
Mem::wb(j_add(a0,Defs::EntT_WhichAnim_b),0xFF);
Mem::ww(j_add(a0,Defs::EntT_Timer2_w),0);
}
}
}

void ACTIVATED(int32_t a0,int32_t a1,int32_t d0){
Mem::ww(j_add(a0,Defs::EntT_ZoneID_w),d0);
if((Mem::b(j_add(a0,Defs::ShotT_Worry_b)) == 0)) {
return ;
}
Mem::wb(j_add(a0,Defs::ShotT_Worry_b),(Mem::ub(j_add(a0,Defs::ShotT_Worry_b)) & 0x80));
int32_t a2=a1;
Mem::ww(j_add(a0,4),Newaliencontrol::worryHeight(a0,a2));
Newaliencontrol::ACTANIMOBJ(a0,a2);
(d0=Mem::uw(AnimBss::Anim_TempFrames_w));
Mem::ww(j_add(a0,Defs::EntT_Timer2_w),j_add(Mem::uw(j_add(a0,Defs::EntT_Timer2_w)),d0));
(d0=Mem::w(j_add(a2,Defs::ODefT_ActiveTimeout_w)));
if(((d0 >= 0) && (d0 <= Mem::w(j_add(a0,Defs::EntT_Timer2_w))))) {
Mem::ww(j_add(a0,Defs::EntT_Timer1_w),0);
Mem::wb(j_add(a0,Defs::EntT_WhichAnim_b),0);
return ;
}
(d0=Newaliencontrol::Plr1_CheckObjectCollide(a0));
if(((int8_t(d0) != 0) && (Mem::b(PlayerBss::Plr1_TmpSpcTap_b) != 0))) {
Mem::ww(j_add(a0,Defs::EntT_Timer1_w),0);
Mem::wb(j_add(a0,Defs::EntT_WhichAnim_b),0);
return ;
}
if((int8_t(Mem::b(PlayerBss::Plr_MultiplayerType_b)) != Hires::PLR_SINGLE)) {
(d0=Newaliencontrol::Plr2_CheckObjectCollide(a0));
if(((int8_t(d0) != 0) && (Mem::b(PlayerBss::Plr2_TmpSpcTap_b) != 0))) {
Mem::ww(j_add(a0,Defs::EntT_Timer1_w),0);
Mem::wb(j_add(a0,Defs::EntT_WhichAnim_b),0);
}
}
}

void Destructable(int32_t a0,int32_t a1){
int32_t a3=Mem::l(HiresData::GLF_DatabasePtr_l);
(a3+=Defs::GLFT_ObjectDefs);
int32_t d0=0;
(d0=M68k::setb(d0,Mem::ub(j_add(a0,Defs::EntT_Type_b))));
(d0=M68k::muls(d0,Defs::ODefT_SizeOf_l));
(a3+=d0);
(d0=0);
(d0=M68k::setb(d0,Mem::ub(j_add(a0,Defs::EntT_DamageTaken_b))));
if((int16_t(d0) < Mem::w(j_add(a3,Defs::ODefT_HitPoints_w)))) {
Newaliencontrol::StillHere(a0,a1);
return ;
}
if((Mem::b(j_add(a0,Defs::EntT_HitPoints_b)) != 0)) {
if((int8_t(Mem::b(PlayerBss::Plr_MultiplayerType_b)) == Hires::PLR_SINGLE)) {
(d0=Mem::w(j_add(a0,Defs::EntT_DisplayText_w)));
if((d0 >= 0)) {
(d0=M68k::muls(d0,Defs::LVLT_MESSAGE_LENGTH));
(d0+=Mem::l(LevelBss::Lvl_DataPtr_l));
Message::Msg_PushLine(d0,(Defs::LVLT_MESSAGE_LENGTH | Defs::MSG_TAG_NARRATIVE));
}
}
Mem::ww(j_add(a0,Defs::EntT_Timer1_w),0);
}
Mem::wb(j_add(a0,Defs::EntT_HitPoints_b),0);
(d0=Mem::w(j_add(a0,Defs::ObjT_ZoneID_w)));
if((d0 < 0)) {
return ;
}
if((Mem::b(j_add(a0,Defs::ShotT_Worry_b)) == 0)) {
return ;
}
int32_t a2=a1;
Mem::ww(j_add(a0,4),Newaliencontrol::worryHeight(a0,a2));
Newaliencontrol::ACTANIMOBJ(a0,a2);
}

void StillHere(int32_t a0,int32_t a1){
int32_t d0=Mem::w(j_add(a0,Defs::ObjT_ZoneID_w));
if((d0 < 0)) {
return ;
}
Mem::wb(j_add(a0,Defs::EntT_HitPoints_b),1);
if((Mem::b(AiBss::AI_NoEnemies_b) != 0)) {
int32_t d1=Mem::l(j_add(a0,Defs::EntT_DoorsAndLiftsHeld_l));
Mem::wl(AnimBss::Anim_DoorAndLiftLocks_l,(Mem::l(AnimBss::Anim_DoorAndLiftLocks_l) | d1));
}
if((Mem::b(j_add(a0,Defs::ShotT_Worry_b)) == 0)) {
return ;
}
int32_t d2=Mem::uw(j_add(a0,Defs::ObjT_ZoneID_w));
int32_t a5=Mem::l(LevelBss::Lvl_ZonePtrsPtr_l);
(d0=Mem::l(j_add(a5,(int16_t(d2) * 4))));
Mem::wl(ObjectmoveData::Obj_ZonePtr_l,d0);
(d0=Mem::uw(a0));
int32_t pa1=Mem::l(LevelBss::Lvl_ObjectPointsPtr_l);
Mem::ww(ObjectmoveData::newx,Mem::uw(j_add(pa1,(int16_t(d0) * 8))));
Mem::ww(ObjectmoveData::newz,Mem::uw(j_add(j_add(pa1,(int16_t(d0) * 8)),4)));
Ai::AI_LookForPlayer1(a0);
Newaliencontrol::Decoration(a0,a1);
}

void Decoration(int32_t a0,int32_t a1){
int32_t d0=Mem::w(j_add(a0,Defs::ObjT_ZoneID_w));
if((d0 < 0)) {
return ;
}
if((Mem::b(j_add(a0,Defs::ShotT_Worry_b)) == 0)) {
return ;
}
int32_t a2=a1;
Mem::ww(j_add(a0,Defs::ObjT_ZPos_l),Newaliencontrol::worryHeight(a0,a2));
Newaliencontrol::DEFANIMOBJ(a0,a2);
}

void obj_SetInventoryPointers(int32_t a0){
int32_t a2=Mem::l(HiresData::GLF_DatabasePtr_l);
int32_t a1=j_add(a2,Defs::GLFT_AmmoGive_l);
(a2+=Defs::GLFT_GunGive_l);
int32_t d0=0;
(d0=M68k::setb(d0,Mem::ub(j_add(a0,Defs::EntT_Type_b))));
int32_t d1=M68k::setw(0,d0);
(d0=M68k::muls(d0,Defs::AmmoGiveLen));
(d1=M68k::muls(d1,Defs::GunGiveLen));
(a2+=int16_t(d1));
(a1+=int16_t(d0));
Mem::wl(NewaliencontrolData::obj_ConsumablePtr_l,a1);
Mem::wl(NewaliencontrolData::obj_ItemsPtr_l,a2);
}

int32_t Plr1_CollectItem(int32_t a0){
Newaliencontrol::obj_SetInventoryPointers(a0);
if((Mem::l(j_add(a0,Defs::EntT_DoorsAndLiftsHeld_l)) == 0)) {
int32_t d0=GameC::Game_CheckInventoryLimits(PlayerBss::Plr1_Invetory_vw,Mem::l(NewaliencontrolData::obj_ConsumablePtr_l),Mem::l(NewaliencontrolData::obj_ItemsPtr_l));
if((int16_t(d0) == 0)) {
if((int8_t(Mem::b(PlayerBss::Plr_MultiplayerType_b)) == Hires::PLR_SINGLE)) {
if((Mem::w(j_add(a0,Defs::EntT_Timer2_w)) <= 0)) {
Message::Msg_PushLineDedupLast(TextData::Game_CantCollectItemText_vb,(Defs::LVLT_MESSAGE_LENGTH | Defs::MSG_TAG_NARRATIVE));
Mem::ww(j_add(a0,Defs::EntT_Timer2_w),200);
}
Mem::ww(j_add(a0,Defs::EntT_Timer2_w),(Mem::uw(j_add(a0,Defs::EntT_Timer2_w)) - 1));
}
return 0;
}
}
if((int8_t(Mem::b(PlayerBss::Plr_MultiplayerType_b)) == Hires::PLR_SINGLE)) {
int32_t d0=Mem::w(j_add(a0,Defs::EntT_DisplayText_w));
if((d0 >= 0)) {
(d0=M68k::muls(d0,Defs::LVLT_MESSAGE_LENGTH));
(d0+=Mem::l(LevelBss::Lvl_DataPtr_l));
Message::Msg_PushLine(d0,(Defs::LVLT_MESSAGE_LENGTH | Defs::MSG_TAG_NARRATIVE));
}
else {
if((int8_t(Mem::b(PlayerBss::Plr_MultiplayerType_b)) != Hires::PLR_SLAVE)) {
(d0=0);
(d0=M68k::setb(d0,Mem::ub(j_add(a0,Defs::EntT_Type_b))));
(d0=M68k::muls(d0,Defs::GLFT_OBJ_NAME_LENGTH));
int32_t na0=Mem::l(HiresData::GLF_DatabasePtr_l);
(d0+=Defs::GLFT_ObjectNames_l);
(na0+=d0);
Message::Msg_PushLine(na0,(Defs::GLFT_OBJ_NAME_LENGTH | Defs::MSG_TAG_DEFAULT));
}
}
}
GameC::Game_AddToInventory(PlayerBss::Plr1_Invetory_vw,Mem::l(NewaliencontrolData::obj_ConsumablePtr_l),Mem::l(NewaliencontrolData::obj_ItemsPtr_l));
int32_t a3=Mem::l(HiresData::GLF_DatabasePtr_l);
(a3+=Defs::GLFT_ObjectDefs);
int32_t d0=0;
(d0=M68k::setb(d0,Mem::ub(j_add(a0,Defs::EntT_Type_b))));
(d0=M68k::muls(d0,Defs::ODefT_SizeOf_l));
(a3+=d0);
(d0=Mem::w(j_add(a3,Defs::ODefT_SFX_w)));
if((d0 >= 0)) {
Mem::ww(HiresData::Aud_SampleNum_w,d0);
Mem::wb(HiresData::notifplaying,0);
Mem::ww(HiresData::IDNUM,Mem::uw(a0));
Mem::ww(HiresData::Aud_NoiseVol_w,80);
int32_t a1=TablesBss::ObjRotated_vl;
(d0=Mem::uw(a0));
(a1=j_add(a1,(int16_t(d0) * 8)));
Mem::wl(HiresData::Aud_NoiseX_w,Mem::l(a1));
Hires::MakeSomeNoise();
}
return 1;
}

int32_t Plr2_CollectItem(int32_t a0){
Newaliencontrol::obj_SetInventoryPointers(a0);
if((Mem::l(j_add(a0,Defs::EntT_DoorsAndLiftsHeld_l)) == 0)) {
int32_t d0=GameC::Game_CheckInventoryLimits(PlayerBss::Plr2_Invetory_vw,Mem::l(NewaliencontrolData::obj_ConsumablePtr_l),Mem::l(NewaliencontrolData::obj_ItemsPtr_l));
if((int16_t(d0) == 0)) {
return 0;
}
}
GameC::Game_AddToInventory(PlayerBss::Plr2_Invetory_vw,Mem::l(NewaliencontrolData::obj_ConsumablePtr_l),Mem::l(NewaliencontrolData::obj_ItemsPtr_l));
int32_t a3=Mem::l(HiresData::GLF_DatabasePtr_l);
(a3+=Defs::GLFT_ObjectDefs);
int32_t d0=0;
(d0=M68k::setb(d0,Mem::ub(j_add(a0,Defs::EntT_Type_b))));
(d0=M68k::muls(d0,Defs::ODefT_SizeOf_l));
(a3+=d0);
(d0=Mem::w(j_add(a3,Defs::ODefT_SFX_w)));
if((d0 >= 0)) {
Mem::ww(HiresData::Aud_SampleNum_w,d0);
Mem::wb(HiresData::notifplaying,0);
Mem::ww(HiresData::IDNUM,Mem::uw(a0));
Mem::ww(HiresData::Aud_NoiseVol_w,80);
int32_t a1=TablesBss::ObjRotated_vl;
(d0=Mem::uw(a0));
(a1=j_add(a1,(int16_t(d0) * 8)));
Mem::wl(HiresData::Aud_NoiseX_w,Mem::l(a1));
Mem::wb(HiresData::PlayEcho,0);
Hires::MakeSomeNoise();
}
Mem::wb(j_add(a0,Defs::ShotT_Worry_b),0);
return 1;
}

int32_t Plr1_CheckObjectCollide(int32_t a0){
int32_t a2=Mem::l(NewaliencontrolData::obj_StatPtr_l);
int32_t d0=Mem::ub(PlayerBss::Plr1_StoodInTop_b);
int32_t d1=Mem::ub(j_add(a0,Defs::ShotT_InUpperZone_b));
if((((d0 ^ d1) & 0xFF) != 0)) {
return 0;
}
Mem::ww(ObjectmoveData::oldx,Mem::uw(PlayerBss::Plr1_XOff_l));
Mem::ww(ObjectmoveData::oldz,Mem::uw(PlayerBss::Plr1_ZOff_l));
int32_t d7=Mem::uw(PlayerBss::Plr1_Zone_w);
if((int16_t(d7) != Mem::w(j_add(a0,Defs::ObjT_ZoneID_w)))) {
return 0;
}
(d7=Mem::l(PlayerBss::Plr1_YOff_l));
int32_t d6=Mem::l(PlayerBss::Plr1_Height_l);
(d6>>=1);
(d7+=d6);
(d7>>=7);
(d7=M68k::setw(d7,(d7 - Mem::uw(j_add(a0,4)))));
if((int16_t(d7) <= 0)) {
(d7=M68k::setw(d7,-(int16_t(d7))));
}
if((int16_t(d7) > Mem::w(j_add(a2,Defs::ODefT_CollideHeight_w)))) {
return 0;
}
(d0=Mem::uw(a0));
int32_t a1=Mem::l(LevelBss::Lvl_ObjectPointsPtr_l);
Mem::ww(ObjectmoveData::newx,Mem::uw(j_add(a1,(int16_t(d0) * 8))));
Mem::ww(ObjectmoveData::newz,Mem::uw(j_add(j_add(a1,(int16_t(d0) * 8)),4)));
int32_t d2=Mem::uw(j_add(a2,Defs::ODefT_CollideRadius_w));
(d2=M68k::muls(d2,d2));
Objectmove::CheckHit(d2);
return Mem::ub(ObjectmoveData::hitwall);
}

int32_t Plr2_CheckObjectCollide(int32_t a0){
int32_t a2=Mem::l(NewaliencontrolData::obj_StatPtr_l);
int32_t d0=Mem::ub(PlayerBss::Plr2_StoodInTop_b);
int32_t d1=Mem::ub(j_add(a0,Defs::ShotT_InUpperZone_b));
if((((d0 ^ d1) & 0xFF) != 0)) {
return 0;
}
Mem::ww(ObjectmoveData::oldx,Mem::uw(PlayerBss::Plr2_XOff_l));
Mem::ww(ObjectmoveData::oldz,Mem::uw(PlayerBss::Plr2_ZOff_l));
int32_t d7=Mem::uw(PlayerBss::Plr2_Zone_w);
if((int16_t(d7) != Mem::w(j_add(a0,Defs::ObjT_ZoneID_w)))) {
return 0;
}
(d7=Mem::l(PlayerBss::Plr2_YOff_l));
int32_t d6=Mem::l(PlayerBss::Plr2_Height_l);
(d6>>=1);
(d7+=d6);
(d7>>=7);
(d7=M68k::setw(d7,(d7 - Mem::uw(j_add(a0,4)))));
if((int16_t(d7) <= 0)) {
(d7=M68k::setw(d7,-(int16_t(d7))));
}
if((int16_t(d7) > Mem::w(j_add(a2,Defs::ODefT_CollideHeight_w)))) {
return 0;
}
(d0=Mem::uw(a0));
int32_t a1=Mem::l(LevelBss::Lvl_ObjectPointsPtr_l);
Mem::ww(ObjectmoveData::newx,Mem::uw(j_add(a1,(int16_t(d0) * 8))));
Mem::ww(ObjectmoveData::newz,Mem::uw(j_add(j_add(a1,(int16_t(d0) * 8)),4)));
int32_t d2=Mem::uw(j_add(a2,Defs::ODefT_CollideRadius_w));
(d2=M68k::muls(d2,d2));
Objectmove::CheckHit(d2);
return Mem::ub(ObjectmoveData::hitwall);
}

void animObj(int32_t a0,int32_t a2,int32_t animTableOffset){
int32_t a3=Mem::l(HiresData::GLF_DatabasePtr_l);
(a3=j_add(a3,animTableOffset));
int32_t d0=0;
(d0=M68k::setb(d0,Mem::ub(j_add(a0,Defs::EntT_Type_b))));
(d0=M68k::muls(d0,Defs::O_AnimSize));
(a3+=int16_t(d0));
(d0=Mem::uw(j_add(a0,Defs::EntT_Timer1_w)));
int32_t d1=M68k::setw(0,d0);
(d0=M68k::setw(d0,j_add(d0,d0)));
(d1=M68k::setw(d1,j_shl(d1,2)));
(d0=M68k::setw(d0,j_add(d0,d1)));
int32_t gfx=Mem::w(j_add(a2,Defs::ODefT_GFXType_w));
if((gfx < 1)) {
Mem::wl(j_add(a0,8),0);
Mem::wb(j_add(a0,9),Mem::ub(j_add(a3,int16_t(d0))));
Mem::wb(j_add(a0,11),Mem::ub(j_add(j_add(a3,int16_t(d0)),1)));
Mem::ww(j_add(a0,6),Mem::uw(j_add(j_add(a3,int16_t(d0)),2)));
(d1=Mem::b(j_add(j_add(a3,int16_t(d0)),4)));
(d1=j_add(d1,d1));
Mem::ww(j_add(a0,4),j_add(Mem::uw(j_add(a0,4)),d1));
(d1=Mem::ub(j_add(j_add(a3,int16_t(d0)),5)));
Mem::ww(j_add(a0,Defs::EntT_Timer1_w),d1);
}
else if((gfx == 1)) {
Mem::wl(j_add(a0,8),0);
Mem::wb(j_add(a0,9),Mem::ub(j_add(a3,int16_t(d0))));
Mem::wb(j_add(a0,11),Mem::ub(j_add(j_add(a3,int16_t(d0)),1)));
Mem::ww(j_add(a0,6),0xffff);
(d1=Mem::b(j_add(j_add(a3,int16_t(d0)),4)));
(d1=j_add(d1,d1));
Mem::ww(j_add(a0,4),j_add(Mem::uw(j_add(a0,4)),d1));
(d1=Mem::uw(j_add(j_add(a3,int16_t(d0)),2)));
Mem::ww(j_add(a0,Defs::EntT_CurrentAngle_w),j_add(Mem::uw(j_add(a0,Defs::EntT_CurrentAngle_w)),d1));
(d1=Mem::ub(j_add(j_add(a3,int16_t(d0)),5)));
Mem::ww(j_add(a0,Defs::EntT_Timer1_w),d1);
}
else {
Mem::wl(j_add(a0,8),0);
(d1=Mem::b(j_add(a3,int16_t(d0))));
(d1=-(d1));
Mem::ww(j_add(a0,8),d1);
Mem::wb(j_add(a0,11),Mem::ub(j_add(j_add(a3,int16_t(d0)),1)));
Mem::ww(j_add(a0,6),Mem::uw(j_add(j_add(a3,int16_t(d0)),2)));
(d1=Mem::b(j_add(j_add(a3,int16_t(d0)),4)));
(d1=j_add(d1,d1));
Mem::ww(j_add(a0,4),j_add(Mem::uw(j_add(a0,4)),d1));
(d1=Mem::ub(j_add(j_add(a3,int16_t(d0)),5)));
Mem::ww(j_add(a0,Defs::EntT_Timer1_w),d1);
}
}

void DEFANIMOBJ(int32_t a0,int32_t a2){
Newaliencontrol::animObj(a0,a2,Defs::GLFT_ObjectDefAnims_l);
}

void ACTANIMOBJ(int32_t a0,int32_t a2){
Newaliencontrol::animObj(a0,a2,Defs::GLFT_ObjectActAnims_l);
}

int32_t ViewpointToDraw(int32_t a0){
int32_t d3=Mem::uw(j_add(a0,Defs::EntT_CurrentAngle_w));
(d3=M68k::setw(d3,(d3 - Mem::uw(HiresData::Vis_AngPos_w))));
(d3=TablesData::AMOD_A(d3));
int32_t a2=TablesData::SinCosTable_vw;
int32_t d2=Mem::w(j_add(a2,int16_t(d3)));
(a2+=TablesData::COSINE_OFS);
(d3=Mem::w(j_add(a2,int16_t(d3))));
int32_t d0=d3;
int32_t d4=d2;
(d0=-(d0));
if((d0 > 0)) {
if((d4 <= 0)) {
(d4=-(d4));
if((d4 > d0)) {
return 3;
}
return 0;
}
if((d4 > d0)) {
return 1;
}
return 0;
}
if((d4 <= 0)) {
if((d0 > d4)) {
return 3;
}
return 2;
}
(d0=-(d0));
if((d4 > d0)) {
return 1;
}
return 2;
}

void RunAround(int32_t a0){
int32_t d0=Mem::uw(ObjectmoveData::oldx);
(d0=M68k::setw(d0,(d0 - Mem::uw(ObjectmoveData::newx))));
(d0=M68k::setw(d0,j_shr(int16_t(d0),1)));
int32_t d1=Mem::uw(ObjectmoveData::oldz);
(d1=M68k::setw(d1,(d1 - Mem::uw(ObjectmoveData::newz))));
(d1=M68k::setw(d1,j_shr(int16_t(d1),1)));
int32_t a1=Mem::l(LevelBss::Lvl_ObjectPointsPtr_l);
int32_t d2=Mem::uw(a0);
(a1=j_add(a1,(int16_t(d2) * 8)));
(d2=Mem::uw(a1));
(d2=M68k::setw(d2,(d2 - Mem::uw(NewaliencontrolData::tempx))));
int32_t d3=Mem::uw(j_add(a1,4));
(d3=M68k::setw(d3,(d3 - Mem::uw(NewaliencontrolData::tempz))));
(d2=M68k::muls(d2,Mem::w(NewaliencontrolData::tempcos)));
(d3=M68k::muls(d3,Mem::w(NewaliencontrolData::tempsin)));
(d2-=d3);
if((d2 >= 0)) {
(d0=M68k::setw(d0,-(int16_t(d0))));
(d1=M68k::setw(d1,-(int16_t(d1))));
}
Mem::ww(ObjectmoveData::newx,(Mem::uw(ObjectmoveData::newx) - d1));
Mem::ww(ObjectmoveData::newz,j_add(Mem::uw(ObjectmoveData::newz),d0));
}

void SHOOTPLAYER1(int32_t a0,int32_t a1){
Mem::ww(NewaliencontrolData::tsx,Mem::uw(ObjectmoveData::oldx));
Mem::ww(NewaliencontrolData::tsz,Mem::uw(ObjectmoveData::oldz));
Mem::ww(NewaliencontrolData::fsx,Mem::uw(ObjectmoveData::newx));
Mem::ww(NewaliencontrolData::fsz,Mem::uw(ObjectmoveData::newz));
Mem::ww(ObjectmoveData::newx,Mem::uw(PlayerBss::Plr1_TmpXOff_l));
Mem::ww(ObjectmoveData::newz,Mem::uw(PlayerBss::Plr1_TmpZOff_l));
Mem::ww(ObjectmoveData::oldx,Mem::uw(a1));
Mem::ww(ObjectmoveData::oldz,Mem::uw(j_add(a1,4)));
int32_t d1=Mem::uw(ObjectmoveData::newx);
(d1=M68k::setw(d1,(d1 - Mem::uw(ObjectmoveData::oldx))));
int32_t d2=Mem::uw(ObjectmoveData::newz);
(d2=M68k::setw(d2,(d2 - Mem::uw(ObjectmoveData::oldz))));
int32_t d0=Objectmove::GetRand();
(d0=M68k::setw(d0,j_shr(int16_t(d0),4)));
(d1=M68k::muls(d1,d0));
(d2=M68k::muls(d2,d0));
(d1=M68k::swap(d1));
(d2=M68k::swap(d2));
Mem::ww(ObjectmoveData::newz,j_add(Mem::uw(ObjectmoveData::newz),d1));
Mem::ww(ObjectmoveData::newx,(Mem::uw(ObjectmoveData::newx) - d2));
(d1=Mem::l(PlayerBss::Plr1_TmpYOff_l));
(d1+=(15 * 128));
(d1>>=7);
(d2=M68k::setw(0,d1));
(d2=M68k::muls(d2,d0));
(d2=M68k::swap(d2));
(d1=M68k::setw(d1,j_add(d1,d2)));
(d1=int16_t(d1));
(d1<<=7);
Mem::wl(ObjectmoveData::newy,d1);
(d1=Mem::w(j_add(a0,4)));
(d1<<=7);
Mem::wl(ObjectmoveData::oldy,d1);
Mem::wb(ObjectmoveData::StoodInTop,Mem::ub(j_add(a0,Defs::ShotT_InUpperZone_b)));
Mem::wb(ObjectmoveData::exitfirst,0xFF);
Mem::ww(ObjectmoveData::Obj_ExtLen_w,0);
Mem::wb(ObjectmoveData::Obj_AwayFromWall_b,0xFF);
Mem::ww(ObjectmoveData::wallflags,0b0000010000000000);
Mem::wl(ObjectmoveData::StepUpVal,0);
Mem::wl(ObjectmoveData::StepDownVal,0x1000000);
Mem::wl(ObjectmoveData::thingheight,0);
int32_t savedZone=Mem::l(ObjectmoveData::Obj_ZonePtr_l);
while(true){
Objectmove::MoveObject();
if((Mem::b(ObjectmoveData::hitwall) != 0)) {
break;
}
int32_t dd=Mem::uw(ObjectmoveData::newx);
(dd=M68k::setw(dd,(dd - Mem::uw(ObjectmoveData::oldx))));
Mem::ww(ObjectmoveData::oldx,j_add(Mem::uw(ObjectmoveData::oldx),dd));
Mem::ww(ObjectmoveData::newx,j_add(Mem::uw(ObjectmoveData::newx),dd));
(dd=Mem::uw(ObjectmoveData::newz));
(dd=M68k::setw(dd,(dd - Mem::uw(ObjectmoveData::oldz))));
Mem::ww(ObjectmoveData::oldz,j_add(Mem::uw(ObjectmoveData::oldz),dd));
Mem::ww(ObjectmoveData::newz,j_add(Mem::uw(ObjectmoveData::newz),dd));
int32_t dl=Mem::l(ObjectmoveData::newy);
(dl-=Mem::l(ObjectmoveData::oldy));
Mem::wl(ObjectmoveData::oldy,j_add(Mem::l(ObjectmoveData::oldy),dl));
Mem::wl(ObjectmoveData::newy,j_add(Mem::l(ObjectmoveData::newy),dl));
}
Mem::wl(NewaliencontrolData::backupZonePtr_l,Mem::l(ObjectmoveData::Obj_ZonePtr_l));
Mem::wl(ObjectmoveData::Obj_ZonePtr_l,savedZone);
int32_t sa0=Mem::l(PlayerBss::Plr_ShotDataPtr_l);
(d1=(Defs::NUM_PLR_SHOT_DATA - 1));
do {
if((Mem::w(j_add(sa0,Defs::ObjT_ZoneID_w)) < 0)) {
int32_t pa1=Mem::l(LevelBss::Lvl_ObjectPointsPtr_l);
(d2=Mem::uw(sa0));
Mem::ww(j_add(pa1,(int16_t(d2) * 8)),Mem::uw(ObjectmoveData::newx));
Mem::ww(j_add(j_add(pa1,(int16_t(d2) * 8)),4),Mem::uw(ObjectmoveData::newz));
Mem::wb(j_add(sa0,Defs::ShotT_Status_b),1);
Mem::ww(j_add(sa0,Defs::ShotT_Gravity_w),0);
Mem::wb(j_add(sa0,Defs::ShotT_Size_b),0);
Mem::wb(j_add(sa0,Defs::ShotT_Anim_b),0);
int32_t ba1=Mem::l(NewaliencontrolData::backupZonePtr_l);
Mem::ww(j_add(sa0,Defs::ObjT_ZoneID_w),Mem::uw(ba1));
Mem::wb(j_add(sa0,Defs::ShotT_Worry_b),0xFF);
int32_t dwh=Mem::l(ObjectmoveData::wallhitheight);
Mem::wl(j_add(sa0,Defs::ShotT_AccYPos_w),dwh);
(dwh>>=7);
Mem::ww(j_add(sa0,4),dwh);
break;
}
(sa0+=Defs::ObjT_SizeOf_l);
(d1=M68k::setw(d1,(d1 - 1)));
}
while((int16_t(d1) != -(1)));
Mem::ww(ObjectmoveData::oldx,Mem::uw(NewaliencontrolData::tsx));
Mem::ww(ObjectmoveData::oldz,Mem::uw(NewaliencontrolData::tsz));
Mem::ww(ObjectmoveData::newx,Mem::uw(NewaliencontrolData::fsx));
Mem::ww(ObjectmoveData::newz,Mem::uw(NewaliencontrolData::fsz));
}

void FireAtPlayer1(int32_t a0){
int32_t a1=Mem::l(LevelBss::Lvl_ObjectPointsPtr_l);
int32_t d1=Mem::uw(a0);
(a1=j_add(a1,(int16_t(d1) * 8)));
int32_t a5=Mem::l(LevelBss::AI_AlienShotDataPtr_l);
(d1=(Defs::NUM_ALIEN_SHOT_DATA - 1));
while(true){
if((Mem::w(j_add(a5,Defs::ObjT_ZoneID_w)) < 0)) {
break;
}
(a5+=Defs::ObjT_SizeOf_l);
(d1=M68k::setw(d1,(d1 - 1)));
if((int16_t(d1) == -(1))) {
return ;
}
}
Mem::wb(j_add(a5,Defs::ObjT_TypeID_b),Defs::OBJ_TYPE_PROJECTILE);
int32_t a6=TablesBss::ObjRotated_vl;
int32_t d0=Mem::uw(a0);
(a6=j_add(a6,(int16_t(d0) * 8)));
Mem::wl(HiresData::Aud_NoiseX_w,Mem::l(a6));
Mem::ww(HiresData::Aud_NoiseVol_w,100);
Mem::wb(HiresData::Aud_ChannelPick_b,1);
Mem::wb(HiresData::notifplaying,0);
(d0=Mem::ub(NewaliencontrolData::SHOTTYPE));
Mem::ww(j_add(a5,Defs::ShotT_Lifetime_w),0);
Mem::wb(j_add(a5,Defs::ShotT_Size_b),d0);
Mem::wb(HiresData::PlayEcho,Mem::ub(NewaliencontrolData::ALIENECHO));
Mem::wb(j_add(a5,Defs::ShotT_Power_w),Mem::ub(NewaliencontrolData::SHOTPOWER));
Mem::ww(HiresData::IDNUM,Mem::uw(a0));
Hires::MakeSomeNoise();
int32_t a2=Mem::l(LevelBss::Lvl_ObjectPointsPtr_l);
(d1=Mem::uw(a5));
(a2=j_add(a2,(int16_t(d1) * 8)));
Mem::ww(ObjectmoveData::oldx,Mem::uw(a1));
Mem::ww(ObjectmoveData::oldz,Mem::uw(j_add(a1,4)));
Mem::ww(ObjectmoveData::newx,Mem::uw(PlayerBss::Plr1_XOff_l));
Mem::ww(ObjectmoveData::newz,Mem::uw(PlayerBss::Plr1_ZOff_l));
Objectmove::CalcDist();
int32_t d6=Mem::uw(HiresData::XDiff_w);
(d6=M68k::muls(d6,Mem::w(ObjectmoveData::distaway)));
(d6=M68k::divs(d6,Mem::w(NewaliencontrolData::SHOTSPEED)));
(d6=M68k::setw(d6,j_shr(int16_t(d6),4)));
Mem::ww(ObjectmoveData::newx,j_add(Mem::uw(ObjectmoveData::newx),d6));
(d6=Mem::uw(HiresData::ZDiff_w));
(d6=M68k::muls(d6,Mem::w(ObjectmoveData::distaway)));
(d6=M68k::divs(d6,Mem::w(NewaliencontrolData::SHOTSPEED)));
(d6=M68k::setw(d6,j_shr(int16_t(d6),4)));
Mem::ww(ObjectmoveData::newz,j_add(Mem::uw(ObjectmoveData::newz),d6));
Mem::ww(NewaliencontrolData::futurex,Mem::uw(ObjectmoveData::newx));
Mem::ww(NewaliencontrolData::futurez,Mem::uw(ObjectmoveData::newz));
Mem::ww(ObjectmoveData::speed,Mem::uw(NewaliencontrolData::SHOTSPEED));
Mem::ww(ObjectmoveData::Range,0);
Objectmove::HeadTowards();
(d0=Mem::uw(ObjectmoveData::newx));
(d0=M68k::setw(d0,(d0 - Mem::uw(ObjectmoveData::oldx))));
(d1=Mem::uw(ObjectmoveData::newz));
(d1=M68k::setw(d1,(d1 - Mem::uw(ObjectmoveData::oldz))));
int32_t d2=Mem::uw(NewaliencontrolData::SHOTOFFMULT);
if((int16_t(d2) != 0)) {
(d0=M68k::muls(d0,d2));
(d1=M68k::muls(d1,d2));
(d0>>=8);
(d1>>=8);
Mem::ww(ObjectmoveData::oldx,j_add(Mem::uw(ObjectmoveData::oldx),d1));
Mem::ww(ObjectmoveData::oldz,(Mem::uw(ObjectmoveData::oldz) - d0));
Mem::ww(ObjectmoveData::newx,Mem::uw(NewaliencontrolData::futurex));
Mem::ww(ObjectmoveData::newz,Mem::uw(NewaliencontrolData::futurez));
Objectmove::HeadTowards();
}
(d0=Mem::uw(ObjectmoveData::newx));
Mem::ww(a2,d0);
(d0=M68k::setw(d0,(d0 - Mem::uw(ObjectmoveData::oldx))));
Mem::ww(j_add(a5,Defs::ShotT_VelocityX_w),d0);
(d0=Mem::uw(ObjectmoveData::newz));
Mem::ww(j_add(a2,4),d0);
(d0=M68k::setw(d0,(d0 - Mem::uw(ObjectmoveData::oldz))));
Mem::ww(j_add(a5,Defs::ShotT_VelocityZ_w),d0);
Mem::wl(j_add(a5,Defs::EntT_EnemyFlags_l),0b110010);
Mem::ww(j_add(a5,Defs::ObjT_ZoneID_w),Mem::uw(j_add(a0,Defs::ObjT_ZoneID_w)));
(d0=Mem::uw(j_add(a0,4)));
Mem::ww(j_add(a5,4),d0);
(d0=int16_t(d0));
(d0<<=7);
(d0+=Mem::l(NewaliencontrolData::SHOTYOFF));
Mem::wl(j_add(a5,Defs::ShotT_AccYPos_w),d0);
Mem::wb(j_add(a5,Defs::ShotT_InUpperZone_b),Mem::ub(NewaliencontrolData::SHOTINTOP));
(a2=Mem::l(PlayerBss::Plr1_ObjectPtr_l));
(d1=Mem::uw(j_add(a2,4)));
(d1=M68k::setw(d1,(d1 - 20)));
(d1=int16_t(d1));
(d1<<=7);
(d1-=d0);
(d1+=d1);
(d0=Mem::uw(ObjectmoveData::distaway));
(d2=Mem::uw(NewaliencontrolData::SHOTSHIFT));
(d0=M68k::setw(d0,j_shr(int16_t(d0),(d2 & 63))));
if((int16_t(d0) <= 0)) {
(d0=1);
}
(d1=M68k::divs(d1,d0));
Mem::ww(j_add(a5,Defs::ShotT_VelocityY_w),d1);
Mem::wb(j_add(a5,Defs::ShotT_Worry_b),0xFF);
}

void SHOOTPLAYER2(int32_t a0,int32_t a1){
Mem::ww(NewaliencontrolData::tsx,Mem::uw(ObjectmoveData::oldx));
Mem::ww(NewaliencontrolData::tsz,Mem::uw(ObjectmoveData::oldz));
Mem::ww(NewaliencontrolData::fsx,Mem::uw(ObjectmoveData::newx));
Mem::ww(NewaliencontrolData::fsz,Mem::uw(ObjectmoveData::oldx));
Mem::ww(ObjectmoveData::newx,Mem::uw(PlayerBss::Plr2_TmpXOff_l));
Mem::ww(ObjectmoveData::newz,Mem::uw(PlayerBss::Plr2_TmpZOff_l));
Mem::ww(ObjectmoveData::oldx,Mem::uw(a1));
Mem::ww(ObjectmoveData::oldz,Mem::uw(j_add(a1,4)));
int32_t d1=Mem::uw(ObjectmoveData::newx);
(d1=M68k::setw(d1,(d1 - Mem::uw(ObjectmoveData::oldx))));
int32_t d2=Mem::uw(ObjectmoveData::newz);
(d2=M68k::setw(d2,(d2 - Mem::uw(ObjectmoveData::oldz))));
int32_t d0=Objectmove::GetRand();
(d0=M68k::setw(d0,j_shr(int16_t(d0),4)));
(d1=M68k::muls(d1,d0));
(d2=M68k::muls(d2,d0));
(d1=M68k::swap(d1));
(d2=M68k::swap(d2));
Mem::ww(ObjectmoveData::newz,j_add(Mem::uw(ObjectmoveData::newz),d1));
Mem::ww(ObjectmoveData::newx,(Mem::uw(ObjectmoveData::newx) - d2));
(d1=Mem::l(PlayerBss::Plr2_TmpYOff_l));
(d1+=(15 * 128));
(d1>>=7);
(d2=M68k::setw(0,d1));
(d2=M68k::muls(d2,d0));
(d2=M68k::swap(d2));
(d1=M68k::setw(d1,j_add(d1,d2)));
(d1=int16_t(d1));
(d1<<=7);
Mem::wl(ObjectmoveData::newy,d1);
(d1=Mem::w(j_add(a0,4)));
(d1<<=7);
Mem::wl(ObjectmoveData::oldy,d1);
Mem::wb(ObjectmoveData::StoodInTop,Mem::ub(j_add(a0,Defs::ShotT_InUpperZone_b)));
Mem::wb(ObjectmoveData::exitfirst,0xFF);
Mem::ww(ObjectmoveData::Obj_ExtLen_w,0);
Mem::wb(ObjectmoveData::Obj_AwayFromWall_b,0xFF);
Mem::ww(ObjectmoveData::wallflags,0b0000010000000000);
Mem::wl(ObjectmoveData::StepUpVal,0);
Mem::wl(ObjectmoveData::StepDownVal,0x1000000);
Mem::wl(ObjectmoveData::thingheight,0);
int32_t savedZone=Mem::l(ObjectmoveData::Obj_ZonePtr_l);
while(true){
Objectmove::MoveObject();
if((Mem::b(ObjectmoveData::hitwall) != 0)) {
break;
}
int32_t dd=Mem::uw(ObjectmoveData::newx);
(dd=M68k::setw(dd,(dd - Mem::uw(ObjectmoveData::oldx))));
Mem::ww(ObjectmoveData::oldx,j_add(Mem::uw(ObjectmoveData::oldx),dd));
Mem::ww(ObjectmoveData::newx,j_add(Mem::uw(ObjectmoveData::newx),dd));
(dd=Mem::uw(ObjectmoveData::newz));
(dd=M68k::setw(dd,(dd - Mem::uw(ObjectmoveData::oldz))));
Mem::ww(ObjectmoveData::oldz,j_add(Mem::uw(ObjectmoveData::oldz),dd));
Mem::ww(ObjectmoveData::newz,j_add(Mem::uw(ObjectmoveData::newz),dd));
int32_t dl=Mem::l(ObjectmoveData::newy);
(dl-=Mem::l(ObjectmoveData::oldy));
Mem::wl(ObjectmoveData::oldy,j_add(Mem::l(ObjectmoveData::oldy),dl));
Mem::wl(ObjectmoveData::newy,j_add(Mem::l(ObjectmoveData::newy),dl));
}
Mem::wl(NewaliencontrolData::backupZonePtr_l,Mem::l(ObjectmoveData::Obj_ZonePtr_l));
Mem::wl(ObjectmoveData::Obj_ZonePtr_l,savedZone);
int32_t sa0=Mem::l(LevelBss::AI_AlienShotDataPtr_l);
(d1=(Defs::NUM_ALIEN_SHOT_DATA - 1));
do {
if((Mem::w(j_add(sa0,Defs::ObjT_ZoneID_w)) < 0)) {
int32_t pa1=Mem::l(LevelBss::Lvl_ObjectPointsPtr_l);
(d2=Mem::uw(sa0));
Mem::ww(j_add(pa1,(int16_t(d2) * 8)),Mem::uw(ObjectmoveData::newx));
Mem::ww(j_add(j_add(pa1,(int16_t(d2) * 8)),4),Mem::uw(ObjectmoveData::newz));
Mem::wb(j_add(sa0,Defs::ShotT_Status_b),1);
Mem::ww(j_add(sa0,Defs::ShotT_Gravity_w),0);
Mem::wb(j_add(sa0,Defs::ShotT_Size_b),0);
Mem::wb(j_add(sa0,Defs::ShotT_Anim_b),0);
int32_t ba1=Mem::l(NewaliencontrolData::backupZonePtr_l);
Mem::ww(j_add(sa0,Defs::ObjT_ZoneID_w),Mem::uw(ba1));
Mem::wb(j_add(sa0,Defs::ShotT_Worry_b),0xFF);
int32_t dwh=Mem::l(ObjectmoveData::wallhitheight);
Mem::wl(j_add(sa0,Defs::ShotT_AccYPos_w),dwh);
(dwh>>=7);
Mem::ww(j_add(sa0,4),dwh);
break;
}
(sa0+=Defs::ObjT_SizeOf_l);
(d1=M68k::setw(d1,(d1 - 1)));
}
while((int16_t(d1) != -(1)));
Mem::ww(ObjectmoveData::oldx,Mem::uw(NewaliencontrolData::tsx));
Mem::ww(ObjectmoveData::oldz,Mem::uw(NewaliencontrolData::tsz));
Mem::ww(ObjectmoveData::newx,Mem::uw(NewaliencontrolData::fsx));
Mem::ww(ObjectmoveData::oldx,Mem::uw(NewaliencontrolData::fsz));
}

void FireAtPlayer2(int32_t a0,int32_t a1){
int32_t a5=Mem::l(LevelBss::AI_AlienShotDataPtr_l);
int32_t d1=(Defs::NUM_ALIEN_SHOT_DATA - 1);
while(true){
if((Mem::w(j_add(a5,Defs::ObjT_ZoneID_w)) < 0)) {
break;
}
(a5+=Defs::ObjT_SizeOf_l);
(d1=M68k::setw(d1,(d1 - 1)));
if((int16_t(d1) == -(1))) {
return ;
}
}
Mem::wb(j_add(a5,Defs::ObjT_TypeID_b),Defs::OBJ_TYPE_PROJECTILE);
int32_t a6=TablesBss::ObjRotated_vl;
int32_t d0=Mem::uw(a0);
(a6=j_add(a6,(int16_t(d0) * 8)));
Mem::wl(HiresData::Aud_NoiseX_w,Mem::l(a6));
Mem::ww(HiresData::Aud_NoiseVol_w,100);
Mem::wb(HiresData::Aud_ChannelPick_b,1);
Mem::wb(HiresData::notifplaying,0);
(d0=Mem::ub(NewaliencontrolData::SHOTPOWER));
Mem::ww(j_add(a5,Defs::ShotT_Lifetime_w),0);
Mem::wb(j_add(a5,Defs::ShotT_Size_b),d0);
Mem::wb(j_add(a5,Defs::ShotT_Power_w),Mem::ub(NewaliencontrolData::SHOTPOWER));
Mem::ww(HiresData::IDNUM,Mem::uw(a0));
Mem::wb(HiresData::PlayEcho,Mem::ub(NewaliencontrolData::ALIENECHO));
Hires::MakeSomeNoise();
int32_t a2=Mem::l(LevelBss::Lvl_ObjectPointsPtr_l);
(d1=Mem::uw(a5));
(a2=j_add(a2,(int16_t(d1) * 8)));
Mem::ww(ObjectmoveData::oldx,Mem::uw(a1));
Mem::ww(ObjectmoveData::oldz,Mem::uw(j_add(a1,4)));
Mem::ww(ObjectmoveData::newx,Mem::uw(PlayerBss::Plr2_XOff_l));
Mem::ww(ObjectmoveData::newz,Mem::uw(PlayerBss::Plr2_ZOff_l));
Mem::ww(ObjectmoveData::speed,Mem::uw(NewaliencontrolData::SHOTSPEED));
Mem::ww(ObjectmoveData::Range,0);
Objectmove::HeadTowards();
(d0=Mem::uw(ObjectmoveData::newx));
(d0=M68k::setw(d0,(d0 - Mem::uw(ObjectmoveData::oldx))));
(d1=Mem::uw(ObjectmoveData::newz));
(d1=M68k::setw(d1,(d1 - Mem::uw(ObjectmoveData::oldz))));
int32_t d2=Mem::uw(NewaliencontrolData::SHOTOFFMULT);
if((int16_t(d2) != 0)) {
(d0=M68k::muls(d0,d2));
(d1=M68k::muls(d1,d2));
(d0>>=8);
(d1>>=8);
Mem::ww(ObjectmoveData::oldx,j_add(Mem::uw(ObjectmoveData::oldx),d1));
Mem::ww(ObjectmoveData::oldz,(Mem::uw(ObjectmoveData::oldz) - d0));
Mem::ww(ObjectmoveData::newx,Mem::uw(PlayerBss::Plr2_XOff_l));
Mem::ww(ObjectmoveData::newz,Mem::uw(PlayerBss::Plr2_ZOff_l));
Objectmove::HeadTowards();
}
(d0=Mem::uw(ObjectmoveData::newx));
Mem::ww(a2,d0);
(d0=M68k::setw(d0,(d0 - Mem::uw(ObjectmoveData::oldx))));
Mem::ww(j_add(a5,Defs::ShotT_VelocityX_w),d0);
(d0=Mem::uw(ObjectmoveData::newz));
Mem::ww(j_add(a2,4),d0);
(d0=M68k::setw(d0,(d0 - Mem::uw(ObjectmoveData::oldz))));
Mem::ww(j_add(a5,Defs::ShotT_VelocityZ_w),d0);
Mem::wl(j_add(a5,Defs::EntT_EnemyFlags_l),0b110010);
Mem::ww(j_add(a5,Defs::ObjT_ZoneID_w),Mem::uw(j_add(a0,Defs::ObjT_ZoneID_w)));
(d0=Mem::uw(j_add(a0,4)));
Mem::ww(j_add(a5,4),d0);
(d0=int16_t(d0));
(d0<<=7);
(d0+=Mem::l(NewaliencontrolData::SHOTYOFF));
Mem::wl(j_add(a5,Defs::ShotT_AccYPos_w),d0);
Mem::wb(j_add(a5,Defs::ShotT_InUpperZone_b),Mem::ub(NewaliencontrolData::SHOTINTOP));
(a2=Mem::l(PlayerBss::Plr2_ObjectPtr_l));
(d1=Mem::uw(j_add(a2,4)));
(d1=M68k::setw(d1,(d1 - 20)));
(d1=int16_t(d1));
(d1<<=7);
(d1-=d0);
(d1+=d1);
(d0=Mem::uw(ObjectmoveData::distaway));
(d2=Mem::uw(NewaliencontrolData::SHOTSHIFT));
(d0=M68k::setw(d0,j_shr(int16_t(d0),(d2 & 63))));
if((int16_t(d0) <= 0)) {
(d0=1);
}
(d1=M68k::divs(d1,d0));
Mem::ww(j_add(a5,Defs::ShotT_VelocityY_w),d1);
Mem::wb(j_add(a5,Defs::ShotT_Worry_b),0xFF);
Mem::ww(j_add(a5,Defs::ShotT_Gravity_w),0);
}

}