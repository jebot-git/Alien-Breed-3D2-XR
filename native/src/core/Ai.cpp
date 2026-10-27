#include "original.hpp"
namespace Ai {
void AI_MainRoutine(int32_t a0){
Mem::ww(j_add(a0,2),-(20));
int32_t mode=Mem::b(j_add(a0,Defs::EntT_CurrentMode_b));
if((int8_t(mode) < 1)) {
Ai::ai_DoDefault(a0);
return ;
}
if((int8_t(mode) == 1)) {
Ai::ai_DoResponse(a0);
return ;
}
if((int8_t(mode) < 3)) {
Ai::ai_DoFollowup(a0);
return ;
}
if((int8_t(mode) == 3)) {
Ai::ai_DoRetreat(a0);
return ;
}
if((int8_t(mode) == 5)) {
Ai::ai_DoDie(a0);
return ;
}
Ai::ai_DoTakeDamage(a0);
}

void ai_DoTakeDamage(int32_t a0){
Ai::ai_DoWalkAnim(a0);
int32_t saved4=Mem::uw(j_add(a0,4));
Ai::ai_GetRoomStatsStill(a0);
int32_t d0=saved4;
if((Mem::w(AiBss::AI_DefaultMode_w) >= 1)) {
Mem::ww(j_add(a0,4),d0);
}
if((Mem::b(AiBss::ai_FinishedAnim_b) != 0)) {
Mem::wb(j_add(a0,Defs::EntT_CurrentMode_b),0);
Mem::wb(j_add(a0,Defs::EntT_WhichAnim_b),0);
Mem::ww(j_add(a0,Defs::EntT_Timer2_w),0);
}
Ai::ai_DoTorch(a0);
if((Mem::w(j_add(j_add(a0,Defs::ObjT_ZoneID_w),Defs::ENT_PREV)) >= 0)) {
Mem::ww(j_add(j_add(a0,Defs::ObjT_ZoneID_w),Defs::ENT_PREV),Mem::uw(j_add(a0,Defs::ObjT_ZoneID_w)));
Mem::ww(j_add(j_add(a0,Defs::EntT_ZoneID_w),Defs::ENT_PREV),Mem::uw(j_add(a0,Defs::EntT_ZoneID_w)));
}
Mem::ww(ObjectmoveData::newx,Mem::uw(PlayerBss::Plr1_XOff_l));
Mem::ww(ObjectmoveData::newz,Mem::uw(PlayerBss::Plr1_ZOff_l));
int32_t d1=Mem::uw(a0);
int32_t a1=Mem::l(LevelBss::Lvl_ObjectPointsPtr_l);
(a1=j_add(a1,(int16_t(d1) * 8)));
Mem::ww(ObjectmoveData::oldx,Mem::uw(a1));
Mem::ww(ObjectmoveData::oldz,Mem::uw(j_add(a1,4)));
Mem::ww(ObjectmoveData::Range,-(20));
Mem::ww(ObjectmoveData::speed,20);
Objectmove::HeadTowardsAng();
(d0=Mem::uw(ObjectmoveData::AngRet));
(d0=M68k::setw(d0,j_add(d0,Mem::uw(AiBss::ai_AnimFacing_w))));
Mem::ww(j_add(a0,Defs::EntT_CurrentAngle_w),d0);
}

void ai_DoDie(int32_t a0){
Ai::ai_DoWalkAnim(a0);
Ai::ai_GetRoomStatsStill(a0);
if((Mem::b(AiBss::ai_FinishedAnim_b) != 0)) {
Macros::FREE_ENT(a0);
Mem::wb(j_add(a0,Defs::ObjT_TypeID_b),Defs::OBJ_TYPE_ALIEN);
Mem::wb(j_add(a0,Defs::ShotT_Worry_b),0);
Mem::wb(AiBss::ai_GetOut_w,0xFF);
}
Mem::wb(j_add(a0,Defs::EntT_HitPoints_b),0);
if((Mem::w(j_add(j_add(a0,Defs::ObjT_ZoneID_w),Defs::ENT_PREV)) >= 0)) {
Mem::ww(j_add(j_add(a0,Defs::ObjT_ZoneID_w),Defs::ENT_PREV),Mem::uw(j_add(a0,Defs::ObjT_ZoneID_w)));
Mem::ww(j_add(j_add(a0,Defs::EntT_ZoneID_w),Defs::ENT_PREV),Mem::uw(j_add(a0,Defs::EntT_ZoneID_w)));
}
}

void ai_TakeDamage(int32_t a0){
Mem::wb(AiBss::ai_GetOut_w,0);
int32_t d0=0;
(d0=M68k::setb(d0,Mem::ub(j_add(a0,Defs::EntT_DamageTaken_b))));
int32_t a2=Mem::l(AiBss::AI_DamagePtr_l);
Mem::ww(a2,j_add(Mem::uw(a2),d0));
(d0=M68k::setw(d0,Mem::uw(a2)));
(d0=M68k::setw(d0,j_shr(int16_t(d0),2)));
int32_t d1=0;
(d1=M68k::setb(d1,Mem::ub(j_add(a0,Defs::EntT_HitPoints_b))));
Mem::wb(j_add(a0,Defs::EntT_DamageTaken_b),0);
if((int16_t(d1) <= int16_t(d0))) {
Ai::ai_JustDied(a0);
return ;
}
Mem::ww(j_add(a0,Defs::EntT_Timer1_w),0);
Mem::ww(j_add(a0,Defs::EntT_Timer2_w),0);
(d0=Objectmove::GetRand());
if(((d0 & 3) != 0)) {
int32_t a5=Mem::l(TablesBss::WorkspacePtr_l);
Mem::wb(j_add(a5,1),0xFF);
Mem::wb(j_add(a0,Defs::EntT_CurrentMode_b),1);
Mem::ww(j_add(a0,Defs::EntT_Timer2_w),0);
Mem::ww(j_add(a0,Defs::EntT_Timer1_w),0);
Mem::wb(j_add(a0,Defs::EntT_WhichAnim_b),1);
(d0=M68k::setw(d0,Mem::uw(a0)));
int32_t a1=Mem::l(LevelBss::Lvl_ObjectPointsPtr_l);
Mem::ww(ObjectmoveData::oldx,Mem::uw(j_add(a1,(int16_t(d0) * 8))));
Mem::ww(ObjectmoveData::oldz,Mem::uw(j_add(j_add(a1,(int16_t(d0) * 8)),4)));
Mem::ww(ObjectmoveData::newx,Mem::uw(PlayerBss::Plr1_XOff_l));
Mem::ww(ObjectmoveData::newz,Mem::uw(PlayerBss::Plr1_ZOff_l));
Mem::ww(ObjectmoveData::speed,100);
Mem::ww(ObjectmoveData::Range,-(20));
Objectmove::HeadTowardsAng();
Mem::ww(j_add(a0,Defs::EntT_CurrentAngle_w),Mem::uw(ObjectmoveData::AngRet));
Mem::wb(AiBss::ai_GetOut_w,0xFF);
return ;
}
Mem::wb(j_add(a0,Defs::EntT_CurrentMode_b),4);
Mem::wb(j_add(a0,Defs::EntT_WhichAnim_b),2);
int32_t a5=Mem::l(TablesBss::WorkspacePtr_l);
Mem::wb(j_add(a5,1),0xFF);
Mem::wb(AiBss::ai_GetOut_w,0xFF);
}

void ai_JustDied(int32_t a0){
Mem::wb(j_add(a0,Defs::EntT_HitPoints_b),0);
int32_t d0=Mem::w(j_add(a0,Defs::EntT_DisplayText_w));
if((d0 >= 0)) {
(d0=M68k::muls(d0,Defs::LVLT_MESSAGE_LENGTH));
(d0+=Mem::l(LevelBss::Lvl_DataPtr_l));
Message::Msg_PushLine(d0,(Defs::LVLT_MESSAGE_LENGTH | Defs::MSG_TAG_NARRATIVE));
}
int32_t a2=Mem::l(LevelBss::Lvl_ObjectPointsPtr_l);
int32_t d3=Mem::uw(a0);
Mem::ww(ObjectmoveData::newx,Mem::uw(j_add(a2,(int16_t(d3) * 8))));
Mem::ww(ObjectmoveData::newz,Mem::uw(j_add(j_add(a2,(int16_t(d3) * 8)),4)));
(d0=0);
(d0=M68k::setb(d0,Mem::ub(j_add(a0,Defs::EntT_Type_b))));
int32_t sa1=j_add(GameBss::game_PlayerProgression,Defs::GStatT_AlienKills_vw);
Mem::ww(j_add(sa1,(int16_t(d0) * 2)),j_add(Mem::uw(j_add(sa1,(int16_t(d0) * 2))),1));
Mem::wl(GameBss::Game_ProgressSignal_l,1);
Macros::SET_MEM_BIT(Defs::GAME_EVENTBIT_KILL,GameBss::Game_ProgressSignal_l);
(d0=M68k::muls(d0,Defs::AlienT_SizeOf_l));
(a2=Mem::l(HiresData::GLF_DatabasePtr_l));
(a2=j_add(a2,Defs::GLFT_AlienDefs_l));
(a2+=d0);
(d0=M68k::setb(d0,Mem::ub(j_add(j_add(a2,Defs::AlienT_SplatType_w),1))));
Mem::wb(AnimBss::Anim_SplatType_w,d0);
if((int8_t(d0) < Defs::NUM_BULLET_DEFS)) {
int32_t d2=8;
Newanims::Anim_ExplodeIntoBits(d0,d2,d3,a0);
}
else {
Mem::wb(AnimBss::Anim_SplatType_w,(Mem::ub(AnimBss::Anim_SplatType_w) - Defs::NUM_BULLET_DEFS));
(d0=M68k::setb(d0,(d0 - Defs::NUM_BULLET_DEFS)));
(d0=M68k::setw(d0,int8_t(d0)));
(a2=Mem::l(HiresData::GLF_DatabasePtr_l));
(a2+=Defs::GLFT_AlienDefs_l);
(d0=M68k::muls(d0,Defs::AlienT_SizeOf_l));
(a2+=d0);
int32_t a4=a2;
int32_t d7=2;
(a2=Mem::l(AiBss::AI_OtherAlienDataPtrs_vl));
(a2+=Defs::ObjT_SizeOf_l);
int32_t a1=Mem::l(LevelBss::Lvl_ObjectPointsPtr_l);
int32_t d1=Mem::uw(a0);
(d0=Mem::l(j_add(a1,(int16_t(d1) * 8))));
(d1=Mem::l(j_add(j_add(a1,(int16_t(d1) * 8)),4)));
(d3=9);
while(true){
{
while(true){
int32_t d2=Mem::w(j_add(a2,Defs::ObjT_ZoneID_w));
if((d2 < 0)) {
break;
}
if((Mem::b(j_add(a2,Defs::EntT_HitPoints_b)) == 0)) {
break;
}
(a2+=Defs::ENT_NEXT_2);
(d3=M68k::setw(d3,(d3 - 1)));
if((int16_t(d3) == -(1))) {
goto spawn_loop_end;
}
}
Mem::wb(j_add(a2,Defs::EntT_HitPoints_b),Mem::ub(j_add(j_add(a4,Defs::AlienT_HitPoints_w),1)));
Mem::wb(j_add(a2,Defs::EntT_Type_b),Mem::ub(AnimBss::Anim_SplatType_w));
Mem::wb(j_add(a2,Defs::EntT_DisplayText_w),-(1));
Mem::wb(j_add(a2,16),0);
int32_t d4=Mem::uw(a2);
Mem::wl(j_add(a1,(int16_t(d4) * 8)),d0);
Mem::wl(j_add(j_add(a1,(int16_t(d4) * 8)),4),d1);
Mem::ww(j_add(a2,4),Mem::uw(j_add(a0,4)));
Mem::ww(j_add(a2,Defs::ObjT_ZoneID_w),Mem::uw(j_add(a0,Defs::ObjT_ZoneID_w)));
Mem::ww(j_add(a2,Defs::EntT_ZoneID_w),Mem::uw(j_add(a0,Defs::ObjT_ZoneID_w)));
Mem::ww(j_add(j_add(a2,Defs::ObjT_ZoneID_w),Defs::ENT_PREV),-(1));
Mem::ww(j_add(a2,Defs::EntT_CurrentControlPoint_w),Mem::uw(j_add(a0,Defs::EntT_CurrentControlPoint_w)));
Mem::ww(j_add(a2,Defs::EntT_TargetControlPoint_w),Mem::uw(j_add(a0,Defs::EntT_CurrentControlPoint_w)));
Mem::wb(j_add(a2,Defs::EntT_TeamNumber_b),-(1));
Mem::ww(j_add(a2,Defs::EntT_CurrentAngle_w),Mem::uw(j_add(a0,Defs::EntT_CurrentAngle_w)));
Mem::wb(j_add(a2,Defs::EntT_CurrentMode_b),0);
Mem::wb(j_add(a2,Defs::EntT_WhichAnim_b),0);
Mem::ww(j_add(a2,Defs::EntT_Timer2_w),0);
Mem::wb(j_add(a2,Defs::EntT_DamageTaken_b),0);
Mem::ww(j_add(a2,Defs::EntT_Timer1_w),0);
Mem::ww(j_add(a2,Defs::EntT_ImpactX_w),0);
Mem::ww(j_add(a2,Defs::EntT_ImpactZ_w),0);
Mem::ww(j_add(a2,Defs::EntT_ImpactY_w),0);
Mem::wb(j_add(a2,Defs::EntT_HitPoints_b),Mem::ub(j_add(j_add(a4,Defs::AlienT_HitPoints_w),1)));
Mem::wb(j_add(a2,Defs::EntT_DamageTaken_b),0);
Mem::wl(j_add(a2,Defs::EntT_DoorsAndLiftsHeld_l),Mem::l(j_add(a0,Defs::EntT_DoorsAndLiftsHeld_l)));
Mem::wb(j_add(a2,Defs::ShotT_InUpperZone_b),Mem::ub(j_add(a0,Defs::ShotT_InUpperZone_b)));
Mem::wb(j_add(j_add(a2,Defs::ObjT_TypeID_b),Defs::ENT_PREV),Defs::OBJ_TYPE_AUX);
(d7=M68k::setw(d7,(d7 - 1)));
if((int16_t(d7) == -(1))) {
break;
}
}

spawn_loop_continue:;
}
spawn_loop_end:;
}
Mem::wb(j_add(a0,Defs::EntT_CurrentMode_b),5);
Mem::wb(j_add(a0,Defs::EntT_WhichAnim_b),3);
Mem::ww(j_add(a0,Defs::EntT_Timer2_w),0);
int32_t a5=Mem::l(TablesBss::WorkspacePtr_l);
Mem::wb(j_add(a5,1),0xFF);
Mem::wb(AiBss::ai_GetOut_w,0xFF);
}

void ai_DoRetreat(int32_t a0){
}

void ai_DoDefault(int32_t a0){
if((Mem::w(AiBss::AI_DefaultMode_w) < 1)) {
Ai::ai_ProwlRandom(a0);
return ;
}
if((Mem::w(AiBss::AI_DefaultMode_w) == 1)) {
Ai::ai_ProwlRandomFlying(a0);
}
}

void ai_DoResponse(int32_t a0){
if(DevMacros::DEV_TEST(DevInst::Dev_DebugFlags_l,DevMacros::DEV_SKIP_AI_ATTACK)) {
Ai::ai_DoDefault(a0);
return ;
}
int32_t m=Mem::w(AiBss::AI_ResponseMode_w);
if((m < 1)) {
Ai::ai_Charge(a0);
return ;
}
if((m == 1)) {
Ai::ai_ChargeToSide(a0);
return ;
}
if((m < 3)) {
Ai::ai_AttackWithGun(a0);
return ;
}
if((m == 3)) {
Ai::ai_ChargeFlying(a0);
return ;
}
if((m < 5)) {
Ai::ai_ChargeToSideFlying(a0);
return ;
}
if((m == 5)) {
Ai::ai_AttackWithGunFlying(a0);
}
}

void ai_DoFollowup(int32_t a0){
int32_t m=Mem::w(AiBss::AI_FollowupMode_w);
if((m < 1)) {
Ai::ai_PauseBriefly(a0);
return ;
}
if((m == 1)) {
Ai::ai_Approach(a0);
return ;
}
if((m < 3)) {
Ai::ai_ApproachToSide(a0);
return ;
}
if((m == 3)) {
Ai::ai_ApproachFlying(a0);
return ;
}
if((m < 5)) {
Ai::ai_ApproachToSideFlying(a0);
}
}

void ai_ProwlRandomFlying(int32_t a0){
Mem::wl(ObjectmoveData::StepDownVal,(1000 * 256));
Mem::wb(AiBss::AI_FlyABit_w,0xFF);
Ai::ai_ProwlFly(a0);
}

void ai_ProwlRandom(int32_t a0){
Mem::wb(AiBss::AI_FlyABit_w,0);
Mem::wl(ObjectmoveData::StepDownVal,(30 * 256));
Ai::ai_ProwlFly(a0);
}

void ai_ProwlFly(int32_t a0){
Mem::wl(ObjectmoveData::StepUpVal,(20 * 256));
if((Mem::b(j_add(a0,Defs::EntT_DamageTaken_b)) != 0)) {
Ai::ai_TakeDamage(a0);
if((Mem::b(AiBss::ai_GetOut_w) != 0)) {
return ;
}
}
Ai::ai_DoWalkAnim(a0);
int32_t a1=Mem::l(AiBss::AI_BoredomPtr_l);
int32_t d1=Mem::uw(j_add(a1,2));
int32_t d2=Mem::uw(j_add(a1,4));
int32_t a2=Mem::l(LevelBss::Lvl_ObjectPointsPtr_l);
int32_t d3=Mem::uw(a0);
int32_t d4=Mem::uw(j_add(j_add(a2,(int16_t(d3) * 8)),4));
(d3=M68k::setw(d3,Mem::uw(j_add(a2,(int16_t(d3) * 8)))));
int32_t d5=M68k::setw(0,d3);
int32_t d6=M68k::setw(0,d4);
(d3=M68k::setw(d3,(d3 - d1)));
if((int16_t(d3) < 0)) {
(d3=M68k::setw(d3,-(int16_t(d3))));
}
(d4=M68k::setw(d4,(d4 - d2)));
if((int16_t(d4) < 0)) {
(d4=M68k::setw(d4,-(int16_t(d4))));
}
(d4=M68k::setw(d4,j_add(d4,d3)));
if((int16_t(d4) >= 50)) {
Mem::ww(j_add(a1,2),d5);
Mem::ww(j_add(a1,4),d6);
Mem::ww(a1,100);
}
else {
Mem::ww(a1,(Mem::uw(a1) - 1));
if((Mem::w(a1) <= 0)) {
Ai::ai_GetRoomCPT(a0);
int32_t d0=Objectmove::GetRand();
(d1=0);
(d1=M68k::setw(d1,d0));
(d1=Ai::M68kDivsMem(d1,LevelBss::Lvl_NumControlPoints_w));
(d1=M68k::swap(d1));
int32_t d7=7;
while(true){
Mem::ww(j_add(a0,Defs::EntT_TargetControlPoint_w),d1);
(d0=Mem::uw(j_add(a0,Defs::EntT_CurrentControlPoint_w)));
(d0=Objectmove::GetNextCPt(d0,d1));
if(((int16_t(d0) != Mem::w(j_add(a0,Defs::EntT_CurrentControlPoint_w))) && (int8_t(d0) != 0x7f))) {
break;
}
(d1=M68k::setw(d1,Mem::uw(j_add(a0,Defs::EntT_TargetControlPoint_w))));
(d1=M68k::setw(d1,j_add(d1,1)));
if((int16_t(d1) >= Mem::w(LevelBss::Lvl_NumControlPoints_w))) {
(d1=0);
}
(d7=M68k::setw(d7,(d7 - 1)));
if((int16_t(d7) == -(1))) {
break;
}
}
Mem::ww(a1,50);
}
}
if((Mem::w(PlayerBss::Plr1_NoiseVol_w) != 0)) {
(a1=Mem::l(PlayerBss::Plr1_ZonePtr_l));
if((Mem::b(PlayerBss::Plr1_StoodInTop_b) != 0)) {
(a1+=1);
}
(d1=0);
(d1=M68k::setb(d1,Mem::ub(j_add(a1,Defs::ZoneT_ControlPoint_w))));
int32_t d0=Mem::uw(j_add(a0,Defs::EntT_CurrentControlPoint_w));
(d0=Objectmove::GetNextCPt(d0,d1));
if((int8_t(d0) == 0x7f)) {
(d0=M68k::setw(d0,Mem::uw(j_add(a0,Defs::EntT_CurrentControlPoint_w))));
}
Mem::ww(j_add(a0,Defs::EntT_TargetControlPoint_w),d0);
}
int32_t d0=0;
(d0=M68k::setb(d0,Mem::ub(j_add(a0,Defs::EntT_TeamNumber_b))));
bool notSeenDone=false;
if((int8_t(d0) >= 0)) {
(a2=AiBss::AI_AlienTeamWorkspace_vl);
(d0=M68k::setw(d0,j_shl(d0,4)));
(a2+=int16_t(d0));
if((Mem::w(j_add(a2,Ai::AI_WorkT_SeenBy_w)) >= 0)) {
(d0=M68k::setw(d0,Mem::uw(a0)));
if((int16_t(d0) == Mem::w(j_add(a2,Ai::AI_WorkT_SeenBy_w)))) {
Mem::ww(j_add(a2,Ai::AI_WorkT_SeenBy_w),-(1));
}
else {
(d0=M68k::setw(d0,j_shl(d0,4)));
(a1=AiBss::ai_AlienWorkspace_vl);
(a1+=int16_t(d0));
Mem::ww(j_add(a1,Ai::AI_WorkT_DamageDone_w),0);
Mem::ww(j_add(a1,Ai::AI_WorkT_DamageTaken_w),0);
Mem::wl(a1,Mem::l(a2));
Mem::wl(j_add(a1,4),Mem::l(j_add(a2,4)));
Mem::wl(j_add(a1,8),Mem::l(j_add(a2,8)));
Mem::wl(j_add(a1,12),Mem::l(j_add(a2,12)));
Mem::ww(j_add(a0,Defs::EntT_TargetControlPoint_w),Mem::uw(j_add(a1,Ai::AI_WorkT_LastControlPoint_w)));
Mem::ww(j_add(a1,Ai::AI_WorkT_LastZone_w),-(1));
(notSeenDone=true);
}
}
}
if(!(notSeenDone)) {
(d0=M68k::setw(d0,Mem::uw(a0)));
(d0=M68k::setw(d0,j_shl(d0,4)));
(a1=AiBss::ai_AlienWorkspace_vl);
(a1+=int16_t(d0));
Mem::ww(j_add(a1,Ai::AI_WorkT_DamageDone_w),0);
Mem::ww(j_add(a1,Ai::AI_WorkT_DamageTaken_w),0);
if((Mem::w(j_add(a1,Ai::AI_WorkT_LastZone_w)) >= 0)) {
Mem::ww(j_add(a0,Defs::EntT_TargetControlPoint_w),Mem::uw(j_add(a1,Ai::AI_WorkT_LastControlPoint_w)));
Mem::ww(j_add(a1,Ai::AI_WorkT_LastZone_w),-(1));
}
}
(d0=Mem::uw(j_add(a0,Defs::EntT_CurrentControlPoint_w)));
(d1=Mem::uw(j_add(a0,Defs::EntT_TargetControlPoint_w)));
(d0=Objectmove::GetNextCPt(d0,d1));
bool yesRand{};
if((int8_t(d0) == 0x7f)) {
(yesRand=true);
}
else if((Mem::b(AiBss::AI_FlyABit_w) != 0)) {
(yesRand=false);
}
else {
(yesRand=(Mem::b(ObjectmoveData::ONLYSEE) != 0));
}
if(yesRand) {
(d0=Objectmove::GetRand());
(d1=0);
(d1=M68k::setw(d1,d0));
(d1=Ai::M68kDivsMem(d1,LevelBss::Lvl_NumControlPoints_w));
(d1=M68k::swap(d1));
int32_t d7=7;
while(true){
Mem::ww(j_add(a0,Defs::EntT_TargetControlPoint_w),d1);
(d0=Mem::uw(j_add(a0,Defs::EntT_CurrentControlPoint_w)));
(d0=Objectmove::GetNextCPt(d0,d1));
if(((int16_t(d0) != Mem::w(j_add(a0,Defs::EntT_CurrentControlPoint_w))) && (int8_t(d0) != 0x7f))) {
break;
}
(d1=M68k::setw(d1,Mem::uw(j_add(a0,Defs::EntT_TargetControlPoint_w))));
(d1=M68k::setw(d1,j_add(d1,1)));
if((int16_t(d1) >= Mem::w(LevelBss::Lvl_NumControlPoints_w))) {
(d1=0);
}
(d7=M68k::setw(d7,(d7 - 1)));
if((int16_t(d7) == -(1))) {
break;
}
}
}
Mem::ww(AiBss::ai_MiddleCPT_w,d0);
(a1=Mem::l(LevelBss::Lvl_ControlPointCoordsPtr_l));
Mem::ww(ObjectmoveData::newx,Mem::uw(j_add(a1,(int16_t(d0) * 8))));
Mem::ww(ObjectmoveData::newz,Mem::uw(j_add(j_add(a1,(int16_t(d0) * 8)),2)));
(d0=M68k::setw(d0,j_shl(d0,2)));
(d0=M68k::setw(d0,j_add(d0,Mem::uw(a0))));
(d0=M68k::muls(d0,0x1347));
(d0=(d0 & 4095));
(a1=TablesData::SinCosTable_vw);
(d1=Mem::w(j_add(a1,(int16_t(d0) * 2))));
(a1=j_add(TablesData::SinCosTable_vw,2048));
(d2=Mem::w(j_add(a1,(int16_t(d0) * 2))));
(d2=j_shl(d2,4));
(d2=M68k::swap(d2));
(d1=j_shl(d1,4));
(d1=M68k::swap(d1));
Mem::ww(ObjectmoveData::newx,j_add(Mem::uw(ObjectmoveData::newx),d1));
Mem::ww(ObjectmoveData::newz,j_add(Mem::uw(ObjectmoveData::newz),d2));
(d1=Mem::uw(a0));
(a1=Mem::l(LevelBss::Lvl_ObjectPointsPtr_l));
(a1=j_add(a1,(int16_t(d1) * 8)));
Mem::ww(ObjectmoveData::oldx,Mem::uw(a1));
Mem::ww(ObjectmoveData::oldz,Mem::uw(j_add(a1,4)));
Mem::ww(ObjectmoveData::speed,0);
if((Mem::b(AiBss::ai_DoAction_b) != 0)) {
(d2=0);
(d2=M68k::setb(d2,Mem::ub(AiBss::ai_DoAction_b)));
(d2=M68k::setw(d2,j_shl(d2,2)));
(d2=M68k::muls(d2,Mem::w(AiBss::AI_ProwlSpeed_w)));
Mem::ww(ObjectmoveData::speed,d2);
}
Mem::ww(ObjectmoveData::Range,40);
(d0=Mem::w(j_add(a0,4)));
(d0<<=7);
(d2=Mem::l(ObjectmoveData::thingheight));
(d2>>=1);
(d0-=d2);
Mem::wl(ObjectmoveData::newy,d0);
Mem::wl(ObjectmoveData::oldy,d0);
Mem::wb(ObjectmoveData::StoodInTop,Mem::ub(j_add(a0,Defs::ShotT_InUpperZone_b)));
Mem::wb(ObjectmoveData::canshove,0);
Mem::wb(ObjectmoveData::GotThere,0);
Objectmove::HeadTowardsAng();
Mem::ww(j_add(a0,Defs::EntT_CurrentAngle_w),Mem::uw(ObjectmoveData::AngRet));
if((Mem::b(ObjectmoveData::GotThere) != 0)) {
(d0=Mem::uw(AiBss::ai_MiddleCPT_w));
Mem::ww(j_add(a0,Defs::EntT_CurrentControlPoint_w),d0);
if((int16_t(d0) == Mem::w(j_add(a0,Defs::EntT_TargetControlPoint_w)))) {
(d0=Objectmove::GetRand());
(d1=0);
(d1=M68k::setw(d1,d0));
(d1=Ai::M68kDivsMem(d1,LevelBss::Lvl_NumControlPoints_w));
(d1=M68k::swap(d1));
Mem::ww(j_add(a0,Defs::EntT_TargetControlPoint_w),d1);
}
}
Mem::ww(ObjectmoveData::wallflags,0b1000000000);
Mem::wl(ObjectmoveData::Obj_CollideFlags_l,0b00001000110010000010);
Objectmove::Obj_DoCollision(a2);
if((Mem::b(ObjectmoveData::hitwall) != 0)) {
Mem::ww(ObjectmoveData::newx,Mem::uw(ObjectmoveData::oldx));
Mem::ww(ObjectmoveData::newz,Mem::uw(ObjectmoveData::oldz));
}
else {
Mem::wb(ObjectmoveData::Obj_WallBounce_b,0);
Objectmove::MoveObject();
Mem::wb(j_add(a0,Defs::ShotT_InUpperZone_b),Mem::ub(ObjectmoveData::StoodInTop));
}
if((Mem::w(j_add(j_add(a0,Defs::ObjT_ZoneID_w),Defs::ENT_PREV)) >= 0)) {
Mem::ww(j_add(j_add(a0,Defs::ObjT_ZoneID_w),Defs::ENT_PREV),Mem::uw(j_add(a0,Defs::ObjT_ZoneID_w)));
Mem::ww(j_add(j_add(a0,Defs::EntT_ZoneID_w),Defs::ENT_PREV),Mem::uw(j_add(a0,Defs::EntT_ZoneID_w)));
}
int32_t saved4=Mem::uw(j_add(a0,4));
Ai::ai_GetRoomStats(a0);
(d0=saved4);
if((Mem::b(AiBss::AI_FlyABit_w) != 0)) {
Mem::ww(j_add(a0,4),d0);
Ai::ai_FlyToCPTHeight(a0);
}
Ai::ai_DoTorch(a0);
Mem::wb(j_add(a0,Defs::EntT_CurrentMode_b),0);
Ai::AI_LookForPlayer1(a0);
Mem::wb(j_add(a0,Defs::EntT_WhichAnim_b),0);
if((Mem::b(j_add(a0,Defs::ObjT_SeePlayer_b)) != 0)) {
(d0=Ai::ai_CheckInFront(a0));
if((int8_t(d0) != 0)) {
(d0=Mem::uw(AnimBss::Anim_TempFrames_w));
Mem::ww(j_add(a0,Defs::EntT_Timer1_w),(Mem::w(j_add(a0,Defs::EntT_Timer1_w)) - d0));
if((Mem::w(j_add(a0,Defs::EntT_Timer1_w)) <= 0)) {
(d0=Ai::ai_CheckForDark(a0));
if((int8_t(d0) != 0)) {
bool attack{};
if((Mem::b(AiBss::AI_FlyABit_w) != 0)) {
(attack=true);
}
else if(((Mem::w(AiBss::AI_ResponseMode_w) == 2) || (Mem::w(AiBss::AI_ResponseMode_w) == 5))) {
(attack=true);
}
else {
(d0=Ai::ai_CheckAttackOnGround(a0));
(attack=(int8_t(d0) != 0));
}
if(attack) {
Mem::ww(j_add(a0,Defs::EntT_Timer2_w),0);
Mem::wb(j_add(a0,Defs::EntT_CurrentMode_b),1);
Mem::wb(j_add(a0,Defs::EntT_WhichAnim_b),1);
}
else {
Ai::ai_StorePlayerPosition(a0);
Mem::ww(j_add(a0,Defs::EntT_Timer1_w),Mem::uw(AiBss::AI_ReactionTime_w));
}
(d0=Mem::uw(AiBss::ai_AnimFacing_w));
Mem::ww(j_add(a0,Defs::EntT_CurrentAngle_w),j_add(Mem::uw(j_add(a0,Defs::EntT_CurrentAngle_w)),d0));
return ;
}
}
else {
(d0=Mem::uw(AiBss::ai_AnimFacing_w));
Mem::ww(j_add(a0,Defs::EntT_CurrentAngle_w),j_add(Mem::uw(j_add(a0,Defs::EntT_CurrentAngle_w)),d0));
return ;
}
}
}
Mem::ww(j_add(a0,Defs::EntT_Timer1_w),Mem::uw(AiBss::AI_ReactionTime_w));
(d0=Mem::uw(AiBss::ai_AnimFacing_w));
Mem::ww(j_add(a0,Defs::EntT_CurrentAngle_w),j_add(Mem::uw(j_add(a0,Defs::EntT_CurrentAngle_w)),d0));
}

int32_t M68kDivsMem(int32_t d,int32_t addr){
return M68k::divs(d,Mem::w(addr));
}

void ai_ChargeToSide(int32_t a0){
Mem::wb(AiBss::AI_FlyABit_w,0);
Mem::wb(AiBss::ai_ToSide_w,0xFF);
Mem::wl(ObjectmoveData::StepDownVal,(30 * 256));
Ai::ai_ChargeCommon(a0);
}

void ai_Charge(int32_t a0){
Mem::wb(AiBss::AI_FlyABit_w,0);
Mem::wb(AiBss::ai_ToSide_w,0);
Mem::wl(ObjectmoveData::StepDownVal,(30 * 256));
Ai::ai_ChargeCommon(a0);
}

void ai_ChargeCommon(int32_t a0){
if((Mem::b(j_add(a0,Defs::EntT_DamageTaken_b)) != 0)) {
Ai::ai_TakeDamage(a0);
if((Mem::b(AiBss::ai_GetOut_w) != 0)) {
return ;
}
}
Ai::ai_DoAttackAnim(a0);
Mem::ww(ObjectmoveData::FromZone,Mem::uw(j_add(a0,Defs::ObjT_ZoneID_w)));
int32_t a2t=Objectmove::CheckTeleport();
bool gotThere=false;
bool noMunch=false;
if((Mem::b(ObjectmoveData::OKTEL) != 0)) {
int32_t d0=Mem::l(ObjectmoveData::floortemp);
(d0>>=7);
Mem::ww(j_add(a0,4),j_add(Mem::uw(j_add(a0,4)),d0));
(noMunch=true);
}
else {
Mem::ww(ObjectmoveData::newx,Mem::uw(PlayerBss::Plr1_XOff_l));
Mem::ww(ObjectmoveData::newz,Mem::uw(PlayerBss::Plr1_ZOff_l));
Mem::ww(NewaliencontrolData::tempsin,Mem::uw(PlayerBss::Plr1_SinVal_w));
Mem::ww(NewaliencontrolData::tempcos,Mem::uw(PlayerBss::Plr1_CosVal_w));
Mem::ww(NewaliencontrolData::tempx,Mem::uw(PlayerBss::Plr1_TmpXOff_l));
Mem::ww(NewaliencontrolData::tempz,Mem::uw(PlayerBss::Plr1_TmpZOff_l));
if((Mem::b(AiBss::ai_ToSide_w) != 0)) {
Newaliencontrol::RunAround(a0);
}
int32_t d1=Mem::uw(a0);
int32_t a1=Mem::l(LevelBss::Lvl_ObjectPointsPtr_l);
(a1=j_add(a1,(int16_t(d1) * 8)));
Mem::ww(ObjectmoveData::oldx,Mem::uw(a1));
Mem::ww(ObjectmoveData::oldz,Mem::uw(j_add(a1,4)));
int32_t d2=Mem::uw(AiBss::AI_ResponseSpeed_w);
(d2=M68k::muls(d2,Mem::uw(AnimBss::Anim_TempFrames_w)));
Mem::ww(ObjectmoveData::speed,d2);
Mem::ww(ObjectmoveData::Range,160);
int32_t d0=Mem::w(j_add(a0,4));
(d0<<=7);
(d2=Mem::l(ObjectmoveData::thingheight));
(d2>>=1);
(d0-=d2);
Mem::wl(ObjectmoveData::newy,d0);
Mem::wl(ObjectmoveData::oldy,d0);
Mem::wb(ObjectmoveData::StoodInTop,Mem::ub(j_add(a0,Defs::ShotT_InUpperZone_b)));
Mem::wb(ObjectmoveData::canshove,0);
Mem::wb(ObjectmoveData::GotThere,0);
Objectmove::HeadTowardsAng();
Mem::ww(ObjectmoveData::wallflags,0b1000000000);
Mem::wl(ObjectmoveData::Obj_CollideFlags_l,0b100000);
Objectmove::Obj_DoCollision(a2t);
if((Mem::b(ObjectmoveData::hitwall) != 0)) {
Mem::ww(ObjectmoveData::newx,Mem::uw(ObjectmoveData::oldx));
Mem::ww(ObjectmoveData::newz,Mem::uw(ObjectmoveData::oldz));
Mem::wb(ObjectmoveData::GotThere,0xFF);
}
else {
Mem::wl(ObjectmoveData::Obj_CollideFlags_l,0b11111111110111000010);
Objectmove::Obj_DoCollision(a2t);
if((Mem::b(ObjectmoveData::hitwall) != 0)) {
Mem::ww(ObjectmoveData::newx,Mem::uw(ObjectmoveData::oldx));
Mem::ww(ObjectmoveData::newz,Mem::uw(ObjectmoveData::oldz));
}
else {
Mem::wb(ObjectmoveData::Obj_WallBounce_b,0);
Objectmove::MoveObject();
Mem::wb(j_add(a0,Defs::ShotT_InUpperZone_b),Mem::ub(ObjectmoveData::StoodInTop));
Mem::ww(j_add(a0,Defs::EntT_CurrentAngle_w),Mem::uw(ObjectmoveData::AngRet));
}
}
if((Mem::w(j_add(j_add(a0,Defs::ObjT_ZoneID_w),Defs::ENT_PREV)) >= 0)) {
Mem::ww(j_add(j_add(a0,Defs::ObjT_ZoneID_w),Defs::ENT_PREV),Mem::uw(j_add(a0,Defs::ObjT_ZoneID_w)));
Mem::ww(j_add(j_add(a0,Defs::EntT_ZoneID_w),Defs::ENT_PREV),Mem::uw(j_add(a0,Defs::EntT_ZoneID_w)));
}
(gotThere=(Mem::b(ObjectmoveData::GotThere) != 0));
}
if(((!(noMunch) && gotThere) && (Mem::b(AiBss::ai_DoAction_b) != 0))) {
int32_t a5=Mem::l(PlayerBss::Plr1_ObjectPtr_l);
int32_t d0=Mem::ub(AiBss::ai_DoAction_b);
(d0=M68k::setw(d0,j_shl(d0,1)));
Mem::wb(j_add(a5,Defs::EntT_DamageTaken_b),j_add(Mem::ub(j_add(a5,Defs::EntT_DamageTaken_b)),d0));
(d0=Mem::uw(ObjectmoveData::newx));
(d0=M68k::setw(d0,(d0 - Mem::uw(ObjectmoveData::oldx))));
(d0=int16_t(d0));
(d0=M68k::divs(d0,Mem::w(AnimBss::Anim_TempFrames_w)));
Mem::ww(j_add(a5,Defs::EntT_ImpactX_w),j_add(Mem::uw(j_add(a5,Defs::EntT_ImpactX_w)),d0));
(d0=Mem::uw(ObjectmoveData::newz));
(d0=M68k::setw(d0,(d0 - Mem::uw(ObjectmoveData::oldz))));
(d0=int16_t(d0));
(d0=M68k::divs(d0,Mem::w(AnimBss::Anim_TempFrames_w)));
Mem::ww(j_add(a5,Defs::EntT_ImpactZ_w),j_add(Mem::uw(j_add(a5,Defs::EntT_ImpactZ_w)),d0));
}
Ai::ai_StorePlayerPosition(a0);
Ai::ai_GetRoomStats(a0);
Ai::ai_GetRoomCPT(a0);
Ai::ai_DoTorch(a0);
Ai::AI_LookForPlayer1(a0);
Mem::wb(j_add(a0,Defs::EntT_CurrentMode_b),0);
if((Mem::b(j_add(a0,Defs::ObjT_SeePlayer_b)) != 0)) {
int32_t d0=Ai::ai_CheckInFront(a0);
if((int8_t(d0) != 0)) {
bool attack{};
if((Mem::b(AiBss::AI_FlyABit_w) != 0)) {
(attack=true);
}
else {
(d0=Ai::ai_CheckAttackOnGround(a0));
(attack=(int8_t(d0) != 0));
}
if(attack) {
(d0=Mem::uw(AiBss::ai_AnimFacing_w));
Mem::ww(j_add(a0,Defs::EntT_CurrentAngle_w),j_add(Mem::uw(j_add(a0,Defs::EntT_CurrentAngle_w)),d0));
Mem::wb(j_add(a0,Defs::EntT_CurrentMode_b),1);
Mem::wb(j_add(a0,Defs::EntT_WhichAnim_b),1);
return ;
}
}
}
Mem::wb(j_add(a0,Defs::EntT_WhichAnim_b),0);
Mem::ww(j_add(a0,Defs::EntT_Timer2_w),0);
int32_t d0=Mem::uw(AiBss::ai_AnimFacing_w);
Mem::ww(j_add(a0,Defs::EntT_CurrentAngle_w),j_add(Mem::uw(j_add(a0,Defs::EntT_CurrentAngle_w)),d0));
}

void ai_AttackWithGunFlying(int32_t a0){
Mem::wb(AiBss::AI_FlyABit_w,0xFF);
Ai::ai_AttackCommon(a0);
}

void ai_AttackWithGun(int32_t a0){
Mem::wb(AiBss::AI_FlyABit_w,0);
Ai::ai_AttackCommon(a0);
}

void ai_AttackCommon(int32_t a0){
int32_t a1=Mem::l(HiresData::GLF_DatabasePtr_l);
(a1=j_add(a1,Defs::GLFT_AlienDefs_l));
int32_t d0=0;
(d0=M68k::setb(d0,Mem::ub(j_add(a0,Defs::EntT_Type_b))));
(d0=M68k::muls(d0,Defs::AlienT_SizeOf_l));
(a1+=int16_t(d0));
(d0=M68k::setw(d0,Mem::uw(j_add(a1,Defs::AlienT_BulType_w))));
Mem::wb(NewaliencontrolData::SHOTTYPE,d0);
(a1=Mem::l(HiresData::GLF_DatabasePtr_l));
(a1=j_add(a1,Defs::GLFT_BulletDefs_l));
(d0=M68k::muls(d0,Defs::BulT_SizeOf_l));
(a1+=d0);
(d0=Mem::l(j_add(a1,Defs::BulT_HitDamage_l)));
Mem::wb(NewaliencontrolData::SHOTPOWER,d0);
int32_t d1=0;
(d0=Mem::l(j_add(a1,Defs::BulT_Speed_l)));
(d1|=j_shl(1,(d0 & 31)));
Mem::ww(NewaliencontrolData::SHOTSPEED,d1);
(d0-=1);
Mem::ww(NewaliencontrolData::SHOTSHIFT,d0);
if((Mem::l(j_add(a1,Defs::BulT_IsHitScan_l)) == 0)) {
Ai::ai_AttackWithProjectile(a0);
return ;
}
Ai::ai_AttackWithHitScan(a0);
}

void ai_AttackWithHitScan(int32_t a0){
if((Mem::b(j_add(a0,Defs::EntT_DamageTaken_b)) != 0)) {
Mem::wb(j_add(a0,Defs::EntT_CurrentMode_b),4);
Ai::ai_TakeDamage(a0);
if((Mem::b(AiBss::ai_GetOut_w) != 0)) {
return ;
}
}
Ai::ai_DoAttackAnim(a0);
Mem::ww(ObjectmoveData::newx,Mem::uw(PlayerBss::Plr1_XOff_l));
Mem::ww(ObjectmoveData::newz,Mem::uw(PlayerBss::Plr1_ZOff_l));
int32_t d1=Mem::uw(a0);
int32_t a1=Mem::l(LevelBss::Lvl_ObjectPointsPtr_l);
(a1=j_add(a1,(int16_t(d1) * 8)));
Mem::ww(ObjectmoveData::oldx,Mem::uw(a1));
Mem::ww(ObjectmoveData::oldz,Mem::uw(j_add(a1,4)));
Mem::ww(ObjectmoveData::Range,-(20));
Mem::ww(ObjectmoveData::speed,20);
Objectmove::HeadTowardsAng();
Mem::ww(j_add(a0,Defs::EntT_CurrentAngle_w),Mem::uw(ObjectmoveData::AngRet));
Ai::ai_StorePlayerPosition(a0);
Ai::AI_LookForPlayer1(a0);
Mem::wb(j_add(a0,Defs::EntT_CurrentMode_b),0);
int32_t d0{};
bool canSee=false;
if((Mem::b(j_add(a0,Defs::ObjT_SeePlayer_b)) != 0)) {
(d0=Ai::ai_CheckInFront(a0));
if((int8_t(d0) != 0)) {
Mem::wb(j_add(a0,Defs::EntT_CurrentMode_b),1);
Mem::wb(j_add(a0,Defs::EntT_WhichAnim_b),1);
(d0=Mem::uw(AiBss::ai_AnimFacing_w));
Mem::ww(j_add(a0,Defs::EntT_CurrentAngle_w),j_add(Mem::uw(j_add(a0,Defs::EntT_CurrentAngle_w)),d0));
(canSee=true);
}
}
if(!(canSee)) {
Mem::wb(j_add(a0,Defs::EntT_WhichAnim_b),0);
Mem::ww(j_add(a0,Defs::EntT_Timer2_w),0);
Mem::ww(j_add(a0,Defs::EntT_Timer1_w),Mem::uw(AiBss::AI_FollowupTimer_w));
Mem::ww(j_add(a0,Defs::EntT_Timer2_w),0);
(d0=Mem::uw(AiBss::ai_AnimFacing_w));
Mem::ww(j_add(a0,Defs::EntT_CurrentAngle_w),j_add(Mem::uw(j_add(a0,Defs::EntT_CurrentAngle_w)),d0));
return ;
}
if((Mem::b(AiBss::ai_DoAction_b) != 0)) {
(d1=Mem::uw(a0));
int32_t a6=TablesBss::ObjRotated_vl;
(a1=Mem::l(LevelBss::Lvl_ObjectPointsPtr_l));
(a1=j_add(a1,(int16_t(d1) * 8)));
(a6=j_add(a6,(int16_t(d1) * 8)));
(d0=Objectmove::GetRand());
(a6=TablesBss::ObjRotated_vl);
(d1=Mem::uw(a0));
(a6=j_add(a6,(int16_t(d1) * 8)));
(d0=(d0 & 0x7fff));
(d1=Mem::uw(a6));
(d1=M68k::muls(d1,d1));
int32_t d2=Mem::uw(j_add(a6,2));
(d2=M68k::muls(d2,d2));
(d1+=d2);
(d1>>=6);
(d0=int16_t(d0));
(d0<<=2);
if((d0 > d1)) {
(a1=Mem::l(PlayerBss::Plr1_ObjectPtr_l));
(d0=Mem::ub(NewaliencontrolData::SHOTPOWER));
Mem::wb(j_add(a1,Defs::EntT_DamageTaken_b),j_add(Mem::ub(j_add(a1,Defs::EntT_DamageTaken_b)),d0));
(a6-=TablesBss::ObjRotated_vl);
(a6+=Mem::l(LevelBss::Lvl_ObjectPointsPtr_l));
(d0=Mem::uw(a6));
(d0=M68k::setw(d0,(d0 - Mem::uw(PlayerBss::Plr1_TmpXOff_l))));
(d1=Mem::uw(j_add(a6,4)));
(d1=M68k::setw(d1,(d1 - Mem::uw(PlayerBss::Plr1_TmpZOff_l))));
(d2=M68k::setw(0,d0));
int32_t d3=M68k::setw(0,d1);
(d2=M68k::muls(d2,d2));
(d3=M68k::muls(d3,d3));
(d2+=d3);
(d2=Ai::ai_CalcSqrt(d2));
(d2+=d2);
(d3=0);
(d3=M68k::setb(d3,Mem::ub(NewaliencontrolData::SHOTPOWER)));
(d0=M68k::muls(d0,d3));
(d0=M68k::divs(d0,d2));
(d1=M68k::muls(d1,d3));
(d1=M68k::divs(d1,d2));
Mem::ww(j_add(a1,Defs::EntT_ImpactX_w),(Mem::uw(j_add(a1,Defs::EntT_ImpactX_w)) - d0));
Mem::ww(j_add(a1,Defs::EntT_ImpactZ_w),(Mem::uw(j_add(a1,Defs::EntT_ImpactZ_w)) - d1));
}
else {
Newaliencontrol::SHOOTPLAYER1(a0,a1);
}
}
(d1=Mem::uw(a0));
(a1=Mem::l(LevelBss::Lvl_ObjectPointsPtr_l));
(a1=j_add(a1,(int16_t(d1) * 8)));
Mem::ww(ObjectmoveData::newx,Mem::uw(a1));
Mem::ww(ObjectmoveData::newz,Mem::uw(j_add(a1,4)));
Ai::ai_DoTorch(a0);
if((Mem::b(AiBss::ai_FinishedAnim_b) != 0)) {
Mem::wb(j_add(a0,Defs::EntT_WhichAnim_b),0);
Mem::wb(j_add(a0,Defs::EntT_CurrentMode_b),2);
Mem::ww(j_add(a0,Defs::EntT_Timer1_w),Mem::uw(AiBss::AI_FollowupTimer_w));
Mem::ww(j_add(a0,Defs::EntT_Timer2_w),0);
(d0=Mem::uw(AiBss::ai_AnimFacing_w));
Mem::ww(j_add(a0,Defs::EntT_CurrentAngle_w),j_add(Mem::uw(j_add(a0,Defs::EntT_CurrentAngle_w)),d0));
}
}

void ai_AttackWithProjectile(int32_t a0){
if((Mem::b(j_add(a0,Defs::EntT_DamageTaken_b)) != 0)) {
Mem::wb(j_add(a0,Defs::EntT_CurrentMode_b),4);
Ai::ai_TakeDamage(a0);
if((Mem::b(AiBss::ai_GetOut_w) != 0)) {
return ;
}
}
Ai::ai_DoAttackAnim(a0);
Mem::ww(ObjectmoveData::newx,Mem::uw(PlayerBss::Plr1_XOff_l));
Mem::ww(ObjectmoveData::newz,Mem::uw(PlayerBss::Plr1_ZOff_l));
int32_t d1=Mem::uw(a0);
int32_t a1=Mem::l(LevelBss::Lvl_ObjectPointsPtr_l);
(a1=j_add(a1,(int16_t(d1) * 8)));
Mem::ww(ObjectmoveData::oldx,Mem::uw(a1));
Mem::ww(ObjectmoveData::oldz,Mem::uw(j_add(a1,4)));
Mem::ww(ObjectmoveData::Range,-(20));
Mem::ww(ObjectmoveData::speed,20);
Objectmove::HeadTowardsAng();
Mem::ww(j_add(a0,Defs::EntT_CurrentAngle_w),Mem::uw(ObjectmoveData::AngRet));
Ai::ai_StorePlayerPosition(a0);
if((Mem::b(AiBss::ai_DoAction_b) != 0)) {
Mem::wb(NewaliencontrolData::SHOTINTOP,Mem::ub(j_add(a0,Defs::ShotT_InUpperZone_b)));
Newaliencontrol::FireAtPlayer1(a0);
}
(d1=Mem::uw(a0));
(a1=Mem::l(LevelBss::Lvl_ObjectPointsPtr_l));
(a1=j_add(a1,(int16_t(d1) * 8)));
Mem::ww(ObjectmoveData::newx,Mem::uw(a1));
Mem::ww(ObjectmoveData::newz,Mem::uw(j_add(a1,4)));
Ai::ai_DoTorch(a0);
int32_t d0{};
if((Mem::b(AiBss::ai_FinishedAnim_b) != 0)) {
Mem::wb(j_add(a0,Defs::EntT_WhichAnim_b),0);
Mem::wb(j_add(a0,Defs::EntT_CurrentMode_b),2);
Mem::ww(j_add(a0,Defs::EntT_Timer1_w),Mem::uw(AiBss::AI_FollowupTimer_w));
Mem::ww(j_add(a0,Defs::EntT_Timer2_w),0);
(d0=Mem::uw(AiBss::ai_AnimFacing_w));
Mem::ww(j_add(a0,Defs::EntT_CurrentAngle_w),j_add(Mem::uw(j_add(a0,Defs::EntT_CurrentAngle_w)),d0));
return ;
}
Ai::AI_LookForPlayer1(a0);
Mem::wb(j_add(a0,Defs::EntT_CurrentMode_b),0);
if((Mem::b(j_add(a0,Defs::ObjT_SeePlayer_b)) != 0)) {
(d0=Ai::ai_CheckInFront(a0));
if((int8_t(d0) != 0)) {
Mem::wb(j_add(a0,Defs::EntT_WhichAnim_b),1);
Mem::wb(j_add(a0,Defs::EntT_CurrentMode_b),1);
(d0=Mem::uw(AiBss::ai_AnimFacing_w));
Mem::ww(j_add(a0,Defs::EntT_CurrentAngle_w),j_add(Mem::uw(j_add(a0,Defs::EntT_CurrentAngle_w)),d0));
return ;
}
}
Mem::wb(j_add(a0,Defs::EntT_WhichAnim_b),0);
Mem::ww(j_add(a0,Defs::EntT_Timer2_w),0);
Mem::ww(j_add(a0,Defs::EntT_Timer1_w),Mem::uw(AiBss::AI_FollowupTimer_w));
Mem::ww(j_add(a0,Defs::EntT_Timer2_w),0);
(d0=Mem::uw(AiBss::ai_AnimFacing_w));
Mem::ww(j_add(a0,Defs::EntT_CurrentAngle_w),j_add(Mem::uw(j_add(a0,Defs::EntT_CurrentAngle_w)),d0));
}

void ai_ChargeToSideFlying(int32_t a0){
Mem::wb(AiBss::AI_FlyABit_w,0xFF);
Mem::wb(AiBss::ai_ToSide_w,0xFF);
Mem::wl(ObjectmoveData::StepDownVal,(1000 * 256));
Ai::ai_ChargeFlyingCommon(a0);
}

void ai_ChargeFlying(int32_t a0){
Mem::wb(AiBss::ai_ToSide_w,0);
Mem::wb(AiBss::AI_FlyABit_w,0xFF);
Mem::wl(ObjectmoveData::StepDownVal,(1000 * 256));
Ai::ai_ChargeFlyingCommon(a0);
}

void ai_ChargeFlyingCommon(int32_t a0){
if((Mem::b(j_add(a0,Defs::EntT_DamageTaken_b)) != 0)) {
Ai::ai_TakeDamage(a0);
if((Mem::b(AiBss::ai_GetOut_w) != 0)) {
return ;
}
}
Ai::ai_DoAttackAnim(a0);
Mem::ww(ObjectmoveData::FromZone,Mem::uw(j_add(a0,Defs::ObjT_ZoneID_w)));
int32_t a2t=Objectmove::CheckTeleport();
bool noMunch=false;
bool gotThere=false;
if((Mem::b(ObjectmoveData::OKTEL) != 0)) {
int32_t d0=Mem::l(ObjectmoveData::floortemp);
(d0>>=7);
Mem::ww(j_add(a0,4),j_add(Mem::uw(j_add(a0,4)),d0));
(noMunch=true);
}
else {
int32_t d1=Mem::uw(a0);
int32_t a1=Mem::l(LevelBss::Lvl_ObjectPointsPtr_l);
(a1=j_add(a1,(int16_t(d1) * 8)));
Mem::ww(ObjectmoveData::oldx,Mem::uw(a1));
Mem::ww(ObjectmoveData::oldz,Mem::uw(j_add(a1,4)));
Mem::ww(ObjectmoveData::newx,Mem::uw(PlayerBss::Plr1_XOff_l));
Mem::ww(ObjectmoveData::newz,Mem::uw(PlayerBss::Plr1_ZOff_l));
Mem::ww(NewaliencontrolData::tempsin,Mem::uw(PlayerBss::Plr1_SinVal_w));
Mem::ww(NewaliencontrolData::tempcos,Mem::uw(PlayerBss::Plr1_CosVal_w));
Mem::ww(NewaliencontrolData::tempx,Mem::uw(PlayerBss::Plr1_TmpXOff_l));
Mem::ww(NewaliencontrolData::tempz,Mem::uw(PlayerBss::Plr1_TmpZOff_l));
if((Mem::b(AiBss::ai_ToSide_w) != 0)) {
Newaliencontrol::RunAround(a0);
}
int32_t d2=Mem::uw(AiBss::AI_ResponseSpeed_w);
(d2=M68k::muls(d2,Mem::uw(AnimBss::Anim_TempFrames_w)));
Mem::ww(ObjectmoveData::speed,d2);
Mem::ww(ObjectmoveData::Range,160);
int32_t d0=Mem::w(j_add(a0,4));
(d0<<=7);
(d2=Mem::l(ObjectmoveData::thingheight));
(d2>>=1);
(d0-=d2);
Mem::wl(ObjectmoveData::newy,d0);
Mem::wl(ObjectmoveData::oldy,d0);
Mem::wb(ObjectmoveData::StoodInTop,Mem::ub(j_add(a0,Defs::ShotT_InUpperZone_b)));
Mem::wb(ObjectmoveData::canshove,0);
Mem::wb(ObjectmoveData::GotThere,0);
Objectmove::HeadTowardsAng();
Mem::ww(ObjectmoveData::wallflags,0b1000000000);
Mem::wl(ObjectmoveData::Obj_CollideFlags_l,0b100000);
Objectmove::Obj_DoCollision(a2t);
if((Mem::b(ObjectmoveData::hitwall) != 0)) {
Mem::ww(ObjectmoveData::newx,Mem::uw(ObjectmoveData::oldx));
Mem::ww(ObjectmoveData::newz,Mem::uw(ObjectmoveData::oldz));
Mem::wb(ObjectmoveData::GotThere,0xFF);
}
else {
Mem::wl(ObjectmoveData::Obj_CollideFlags_l,0b11111111110111000010);
Objectmove::Obj_DoCollision(a2t);
if((Mem::b(ObjectmoveData::hitwall) != 0)) {
Mem::ww(ObjectmoveData::newx,Mem::uw(ObjectmoveData::oldx));
Mem::ww(ObjectmoveData::newz,Mem::uw(ObjectmoveData::oldz));
}
else {
Mem::wb(ObjectmoveData::Obj_WallBounce_b,0);
Objectmove::MoveObject();
Mem::wb(j_add(a0,Defs::ShotT_InUpperZone_b),Mem::ub(ObjectmoveData::StoodInTop));
Mem::ww(j_add(a0,Defs::EntT_CurrentAngle_w),Mem::uw(ObjectmoveData::AngRet));
}
}
(gotThere=(Mem::b(ObjectmoveData::GotThere) != 0));
}
if(((!(noMunch) && gotThere) && (Mem::b(AiBss::ai_DoAction_b) != 0))) {
int32_t a5=Mem::l(PlayerBss::Plr1_ObjectPtr_l);
int32_t d0=Mem::ub(AiBss::ai_DoAction_b);
(d0=M68k::setw(d0,j_shl(d0,1)));
Mem::wb(j_add(a5,Defs::EntT_DamageTaken_b),j_add(Mem::ub(j_add(a5,Defs::EntT_DamageTaken_b)),d0));
}
Ai::ai_StorePlayerPosition(a0);
int32_t saved4=Mem::uw(j_add(a0,4));
Ai::ai_GetRoomStats(a0);
Mem::ww(j_add(a0,4),saved4);
Ai::ai_GetRoomCPT(a0);
Ai::ai_FlyToPlayerHeight(a0);
Ai::ai_DoTorch(a0);
Ai::AI_LookForPlayer1(a0);
Mem::wb(j_add(a0,Defs::EntT_CurrentMode_b),0);
int32_t d0{};
if((Mem::b(j_add(a0,Defs::ObjT_SeePlayer_b)) != 0)) {
(d0=Ai::ai_CheckInFront(a0));
if((int8_t(d0) != 0)) {
Mem::wb(j_add(a0,Defs::EntT_CurrentMode_b),1);
Mem::wb(j_add(a0,Defs::EntT_WhichAnim_b),1);
(d0=Mem::uw(AiBss::ai_AnimFacing_w));
Mem::ww(j_add(a0,Defs::EntT_CurrentAngle_w),j_add(Mem::uw(j_add(a0,Defs::EntT_CurrentAngle_w)),d0));
return ;
}
}
Mem::wb(j_add(a0,Defs::EntT_WhichAnim_b),0);
Mem::ww(j_add(a0,Defs::EntT_Timer2_w),0);
(d0=Mem::uw(AiBss::ai_AnimFacing_w));
Mem::ww(j_add(a0,Defs::EntT_CurrentAngle_w),j_add(Mem::uw(j_add(a0,Defs::EntT_CurrentAngle_w)),d0));
}

void ai_PauseBriefly(int32_t a0){
if((Mem::b(j_add(a0,Defs::EntT_DamageTaken_b)) != 0)) {
Ai::ai_TakeDamage(a0);
if((Mem::b(AiBss::ai_GetOut_w) != 0)) {
return ;
}
}
Mem::ww(j_add(a0,Defs::EntT_Timer2_w),0);
Ai::ai_DoWalkAnim(a0);
int32_t d0=Mem::uw(AnimBss::Anim_TempFrames_w);
Mem::ww(j_add(a0,Defs::EntT_Timer1_w),(Mem::w(j_add(a0,Defs::EntT_Timer1_w)) - d0));
if((Mem::w(j_add(a0,Defs::EntT_Timer1_w)) > 0)) {
(d0=Mem::uw(AiBss::ai_AnimFacing_w));
Mem::ww(j_add(a0,Defs::EntT_CurrentAngle_w),j_add(Mem::uw(j_add(a0,Defs::EntT_CurrentAngle_w)),d0));
return ;
}
int32_t d1=Mem::uw(a0);
int32_t a1=Mem::l(LevelBss::Lvl_ObjectPointsPtr_l);
(a1=j_add(a1,(int16_t(d1) * 8)));
Mem::ww(ObjectmoveData::newx,Mem::uw(a1));
Mem::ww(ObjectmoveData::newz,Mem::uw(j_add(a1,4)));
Ai::ai_DoTorch(a0);
Ai::AI_LookForPlayer1(a0);
Mem::wb(j_add(a0,Defs::EntT_CurrentMode_b),0);
if((Mem::b(j_add(a0,Defs::ObjT_SeePlayer_b)) != 0)) {
(d0=Ai::ai_CheckInFront(a0));
if((int8_t(d0) != 0)) {
(d0=Ai::ai_CheckForDark(a0));
if((int8_t(d0) != 0)) {
Mem::wb(j_add(a0,Defs::EntT_WhichAnim_b),1);
Mem::wb(j_add(a0,Defs::EntT_CurrentMode_b),1);
(d0=Mem::uw(AiBss::ai_AnimFacing_w));
Mem::ww(j_add(a0,Defs::EntT_CurrentAngle_w),j_add(Mem::uw(j_add(a0,Defs::EntT_CurrentAngle_w)),d0));
return ;
}
}
}
Mem::wb(j_add(a0,Defs::EntT_WhichAnim_b),0);
(d0=Mem::uw(AiBss::ai_AnimFacing_w));
Mem::ww(j_add(a0,Defs::EntT_CurrentAngle_w),j_add(Mem::uw(j_add(a0,Defs::EntT_CurrentAngle_w)),d0));
}

void ai_Approach(int32_t a0){
Mem::wb(AiBss::AI_FlyABit_w,0);
Mem::wl(ObjectmoveData::StepDownVal,(30 * 256));
Mem::wb(AiBss::ai_ToSide_w,0);
Ai::ai_ApproachCommon(a0);
}

void ai_ApproachFlying(int32_t a0){
Mem::wb(AiBss::AI_FlyABit_w,0xFF);
Mem::wl(ObjectmoveData::StepDownVal,(1000 * 256));
Mem::wb(AiBss::ai_ToSide_w,0);
Ai::ai_ApproachCommon(a0);
}

void ai_ApproachToSideFlying(int32_t a0){
Mem::wb(AiBss::AI_FlyABit_w,0xFF);
Mem::wl(ObjectmoveData::StepDownVal,(1000 * 256));
Mem::wb(AiBss::ai_ToSide_w,0xFF);
Ai::ai_ApproachCommon(a0);
}

void ai_ApproachToSide(int32_t a0){
Mem::wb(AiBss::ai_ToSide_w,0xFF);
Mem::wb(AiBss::AI_FlyABit_w,0);
Mem::wl(ObjectmoveData::StepDownVal,(30 * 256));
Ai::ai_ApproachCommon(a0);
}

void ai_ApproachCommon(int32_t a0){
if((Mem::b(j_add(a0,Defs::EntT_DamageTaken_b)) != 0)) {
Ai::ai_TakeDamage(a0);
if((Mem::b(AiBss::ai_GetOut_w) != 0)) {
return ;
}
}
Ai::ai_DoWalkAnim(a0);
Mem::ww(ObjectmoveData::FromZone,Mem::uw(j_add(a0,Defs::ObjT_ZoneID_w)));
int32_t a2t=Objectmove::CheckTeleport();
if((Mem::b(ObjectmoveData::OKTEL) != 0)) {
int32_t d0=Mem::l(ObjectmoveData::floortemp);
(d0>>=7);
Mem::ww(j_add(a0,4),j_add(Mem::uw(j_add(a0,4)),d0));
}
else {
int32_t d1=Mem::uw(a0);
int32_t a1=Mem::l(LevelBss::Lvl_ObjectPointsPtr_l);
(a1=j_add(a1,(int16_t(d1) * 8)));
Mem::ww(ObjectmoveData::oldx,Mem::uw(a1));
Mem::ww(ObjectmoveData::oldz,Mem::uw(j_add(a1,4)));
Mem::ww(ObjectmoveData::newx,Mem::uw(PlayerBss::Plr1_XOff_l));
Mem::ww(ObjectmoveData::newz,Mem::uw(PlayerBss::Plr1_ZOff_l));
Mem::ww(NewaliencontrolData::tempsin,Mem::uw(PlayerBss::Plr1_SinVal_w));
Mem::ww(NewaliencontrolData::tempcos,Mem::uw(PlayerBss::Plr1_CosVal_w));
Mem::ww(NewaliencontrolData::tempx,Mem::uw(PlayerBss::Plr1_TmpXOff_l));
Mem::ww(NewaliencontrolData::tempz,Mem::uw(PlayerBss::Plr1_TmpZOff_l));
if((Mem::b(AiBss::ai_ToSide_w) != 0)) {
Newaliencontrol::RunAround(a0);
}
Mem::ww(ObjectmoveData::speed,0);
if((Mem::b(AiBss::ai_DoAction_b) != 0)) {
int32_t d2=0;
(d2=M68k::setb(d2,Mem::ub(AiBss::ai_DoAction_b)));
(d2=M68k::setw(d2,j_shl(d2,2)));
(d2=M68k::muls(d2,Mem::w(AiBss::AI_FollowupSpeed_w)));
Mem::ww(ObjectmoveData::speed,d2);
}
Mem::ww(ObjectmoveData::Range,160);
int32_t d0=Mem::w(j_add(a0,4));
(d0<<=7);
int32_t d2=Mem::l(ObjectmoveData::thingheight);
(d2>>=1);
(d0-=d2);
Mem::wl(ObjectmoveData::newy,d0);
Mem::wl(ObjectmoveData::oldy,d0);
Mem::wb(ObjectmoveData::StoodInTop,Mem::ub(j_add(a0,Defs::ShotT_InUpperZone_b)));
Mem::wb(ObjectmoveData::canshove,0);
Mem::wb(ObjectmoveData::GotThere,0);
Objectmove::HeadTowardsAng();
Mem::ww(ObjectmoveData::wallflags,0b1000000000);
Mem::wl(ObjectmoveData::Obj_CollideFlags_l,0b100000);
Objectmove::Obj_DoCollision(a2t);
if((Mem::b(ObjectmoveData::hitwall) != 0)) {
Mem::ww(ObjectmoveData::newx,Mem::uw(ObjectmoveData::oldx));
Mem::ww(ObjectmoveData::newz,Mem::uw(ObjectmoveData::oldz));
Mem::wb(ObjectmoveData::GotThere,0xFF);
}
else {
Mem::wl(ObjectmoveData::Obj_CollideFlags_l,0b11111111110111000010);
Objectmove::Obj_DoCollision(a2t);
if((Mem::b(ObjectmoveData::hitwall) != 0)) {
Mem::ww(ObjectmoveData::newx,Mem::uw(ObjectmoveData::oldx));
Mem::ww(ObjectmoveData::newz,Mem::uw(ObjectmoveData::oldz));
}
else {
Mem::wb(ObjectmoveData::Obj_WallBounce_b,0);
Objectmove::MoveObject();
Mem::wb(j_add(a0,Defs::ShotT_InUpperZone_b),Mem::ub(ObjectmoveData::StoodInTop));
Mem::ww(j_add(a0,Defs::EntT_CurrentAngle_w),Mem::uw(ObjectmoveData::AngRet));
}
}
if((Mem::w(j_add(j_add(a0,Defs::ObjT_ZoneID_w),Defs::ENT_PREV)) >= 0)) {
Mem::ww(j_add(j_add(a0,Defs::ObjT_ZoneID_w),Defs::ENT_PREV),Mem::uw(j_add(a0,Defs::ObjT_ZoneID_w)));
Mem::ww(j_add(j_add(a0,Defs::EntT_ZoneID_w),Defs::ENT_PREV),Mem::uw(j_add(a0,Defs::EntT_ZoneID_w)));
}
}
Ai::ai_StorePlayerPosition(a0);
if((Mem::b(AiBss::AI_FlyABit_w) != 0)) {
Ai::ai_FlyToPlayerHeight(a0);
}
int32_t saved4=Mem::uw(j_add(a0,4));
Ai::ai_GetRoomStats(a0);
int32_t d0=saved4;
if((Mem::b(AiBss::AI_FlyABit_w) != 0)) {
Mem::ww(j_add(a0,4),d0);
}
Ai::ai_GetRoomCPT(a0);
Ai::ai_DoTorch(a0);
Mem::wb(j_add(a0,Defs::EntT_CurrentMode_b),0);
if((Mem::b(AiBss::AI_FlyABit_w) == 0)) {
(d0=Ai::ai_CheckAttackOnGround(a0));
if((int8_t(d0) == 0)) {
Mem::wb(j_add(a0,Defs::EntT_WhichAnim_b),0);
(d0=Mem::uw(AiBss::ai_AnimFacing_w));
Mem::ww(j_add(a0,Defs::EntT_CurrentAngle_w),j_add(Mem::uw(j_add(a0,Defs::EntT_CurrentAngle_w)),d0));
return ;
}
}
Ai::AI_LookForPlayer1(a0);
if((Mem::b(j_add(a0,Defs::ObjT_SeePlayer_b)) != 0)) {
(d0=Ai::ai_CheckInFront(a0));
if((int8_t(d0) != 0)) {
Mem::wb(j_add(a0,Defs::EntT_CurrentMode_b),2);
(d0=Mem::uw(AnimBss::Anim_TempFrames_w));
Mem::ww(j_add(a0,Defs::EntT_Timer1_w),(Mem::w(j_add(a0,Defs::EntT_Timer1_w)) - d0));
if((Mem::w(j_add(a0,Defs::EntT_Timer1_w)) <= 0)) {
(d0=Ai::ai_CheckForDark(a0));
if((int8_t(d0) != 0)) {
Mem::wb(j_add(a0,Defs::EntT_CurrentMode_b),1);
Mem::ww(j_add(a0,Defs::EntT_Timer2_w),0);
Mem::wb(j_add(a0,Defs::EntT_WhichAnim_b),1);
(d0=Mem::uw(AiBss::ai_AnimFacing_w));
Mem::ww(j_add(a0,Defs::EntT_CurrentAngle_w),j_add(Mem::uw(j_add(a0,Defs::EntT_CurrentAngle_w)),d0));
return ;
}
}
}
}
Mem::wb(j_add(a0,Defs::EntT_WhichAnim_b),0);
(d0=Mem::uw(AiBss::ai_AnimFacing_w));
Mem::ww(j_add(a0,Defs::EntT_CurrentAngle_w),j_add(Mem::uw(j_add(a0,Defs::EntT_CurrentAngle_w)),d0));
}

void ai_FlyToCPTHeight(int32_t a0){
int32_t d0=Mem::uw(AiBss::ai_MiddleCPT_w);
int32_t a1=Mem::l(LevelBss::Lvl_ControlPointCoordsPtr_l);
int32_t d1=Mem::uw(j_add(j_add(a1,(int16_t(d0) * 8)),4));
Ai::ai_FlyToHeightCommon(a0,d1);
}

void ai_FlyToPlayerHeight(int32_t a0){
int32_t d1=Mem::l(PlayerBss::Plr1_YOff_l);
(d1>>=7);
Ai::ai_FlyToHeightCommon(a0,d1);
}

void ai_FlyToHeightCommon(int32_t a0,int32_t d1){
int32_t d0=Mem::uw(j_add(a0,4));
int32_t d2{};
if((int16_t(d1) > int16_t(d0))) {
(d2=Mem::uw(j_add(a0,Defs::EntT_VelocityY_w)));
(d2=M68k::setw(d2,j_add(d2,2)));
if((int16_t(d2) >= 32)) {
(d2=M68k::setw(d2,32));
}
Mem::ww(j_add(a0,Defs::EntT_VelocityY_w),d2);
Mem::ww(j_add(a0,4),j_add(Mem::uw(j_add(a0,4)),d2));
}
else {
(d2=Mem::uw(j_add(a0,Defs::EntT_VelocityY_w)));
(d2=M68k::setw(d2,(d2 - 2)));
if((int16_t(d2) <= -(32))) {
(d2=M68k::setw(d2,-(32)));
}
Mem::ww(j_add(a0,Defs::EntT_VelocityY_w),d2);
Mem::ww(j_add(a0,4),j_add(Mem::uw(j_add(a0,4)),d2));
}
Ai::ai_CheckFloorCeiling(a0);
}

void ai_CheckFloorCeiling(int32_t a0){
int32_t d2=Mem::uw(j_add(a0,4));
int32_t d4=Mem::l(ObjectmoveData::thingheight);
(d4>>=8);
int32_t d3=M68k::setw(0,d2);
(d2=M68k::setw(d2,(d2 - d4)));
(d3=M68k::setw(d3,j_add(d3,d4)));
int32_t a2=Mem::l(ObjectmoveData::Obj_ZonePtr_l);
int32_t d0=Mem::l(j_add(a2,Defs::ZoneT_Floor_l));
int32_t d1=Mem::l(j_add(a2,Defs::ZoneT_Roof_l));
if((Mem::b(j_add(a0,Defs::ShotT_InUpperZone_b)) != 0)) {
(d0=Mem::l(j_add(a2,Defs::ZoneT_UpperFloor_l)));
(d1=Mem::l(j_add(a2,Defs::ZoneT_UpperRoof_l)));
}
(d0>>=7);
(d1>>=7);
if((int16_t(d3) >= int16_t(d0))) {
(d3=M68k::setw(d3,d0));
(d2=M68k::setw(d2,d3));
(d2=M68k::setw(d2,(d2 - d4)));
(d2=M68k::setw(d2,(d2 - d4)));
}
if((int16_t(d2) <= int16_t(d1))) {
(d2=M68k::setw(d2,d1));
(d3=M68k::setw(d3,d2));
(d3=M68k::setw(d3,j_add(d3,d4)));
(d3=M68k::setw(d3,j_add(d3,d4)));
}
(d3=M68k::setw(d3,(d3 - d4)));
Mem::ww(j_add(a0,4),d3);
}

void ai_StorePlayerPosition(int32_t a0){
int32_t d0=Mem::uw(a0);
int32_t a2=AiBss::ai_AlienWorkspace_vl;
(d0=M68k::setw(d0,j_shl(d0,4)));
(a2+=int16_t(d0));
Mem::ww(j_add(a2,Ai::AI_WorkT_LastX_w),Mem::uw(PlayerBss::Plr1_XOff_l));
Mem::ww(j_add(a2,Ai::AI_WorkT_LastY_w),Mem::uw(PlayerBss::Plr1_ZOff_l));
int32_t a3=Mem::l(PlayerBss::Plr1_ZonePtr_l);
Mem::ww(j_add(a2,Ai::AI_WorkT_LastZone_w),Mem::uw(a3));
(d0=0);
(d0=M68k::setb(d0,Mem::ub(j_add(a3,Defs::ZoneT_ControlPoint_w))));
if((Mem::b(PlayerBss::Plr1_StoodInTop_b) != 0)) {
(d0=M68k::setb(d0,Mem::ub(j_add(j_add(a3,Defs::ZoneT_ControlPoint_w),1))));
}
Mem::ww(j_add(a2,Ai::AI_WorkT_LastControlPoint_w),d0);
(d0=M68k::setb(d0,Mem::ub(j_add(a0,Defs::EntT_TeamNumber_b))));
if((int8_t(d0) >= 0)) {
(a2=AiBss::AI_AlienTeamWorkspace_vl);
(d0=M68k::setw(d0,j_shl(d0,4)));
(a2+=int16_t(d0));
Mem::ww(j_add(a2,Ai::AI_WorkT_LastX_w),Mem::uw(PlayerBss::Plr1_XOff_l));
Mem::ww(j_add(a2,Ai::AI_WorkT_LastY_w),Mem::uw(PlayerBss::Plr1_ZOff_l));
(a3=Mem::l(PlayerBss::Plr1_ZonePtr_l));
Mem::ww(j_add(a2,Ai::AI_WorkT_LastZone_w),Mem::uw(a3));
(d0=0);
(d0=M68k::setb(d0,Mem::ub(j_add(a3,Defs::ZoneT_ControlPoint_w))));
if((Mem::b(PlayerBss::Plr1_StoodInTop_b) != 0)) {
(d0=M68k::setb(d0,Mem::ub(j_add(j_add(a3,Defs::ZoneT_ControlPoint_w),1))));
}
Mem::ww(j_add(a2,Ai::AI_WorkT_LastControlPoint_w),d0);
Mem::ww(j_add(a2,Ai::AI_WorkT_SeenBy_w),Mem::uw(a0));
}
}

void ai_GetRoomStats(int32_t a0){
int32_t d0=Mem::uw(a0);
int32_t a1=Mem::l(LevelBss::Lvl_ObjectPointsPtr_l);
(a1=j_add(a1,(int16_t(d0) * 8)));
Mem::ww(a1,Mem::uw(ObjectmoveData::newx));
Mem::ww(j_add(a1,4),Mem::uw(ObjectmoveData::newz));
Ai::ai_GetRoomStatsStill(a0);
}

void ai_GetRoomStatsStill(int32_t a0){
int32_t a2=Mem::l(ObjectmoveData::Obj_ZonePtr_l);
Mem::ww(j_add(a0,12),Mem::uw(a2));
int32_t d0=Mem::l(j_add(a2,Defs::ZoneT_Floor_l));
if((Mem::b(j_add(a0,Defs::ShotT_InUpperZone_b)) != 0)) {
(d0=Mem::l(j_add(a2,Defs::ZoneT_UpperFloor_l)));
}
int32_t d2=Mem::l(ObjectmoveData::thingheight);
(d2>>=1);
(d0-=d2);
(d0>>=7);
Mem::ww(j_add(a0,4),d0);
Mem::ww(j_add(a0,Defs::EntT_ZoneID_w),Mem::uw(j_add(a0,Defs::ObjT_ZoneID_w)));
}

int32_t ai_CheckForDark(int32_t a0){
int32_t d0=Mem::uw(a0);
int32_t a3=Mem::l(PlayerBss::Plr1_ZonePtr_l);
int32_t d1=Mem::uw(a3);
if((int16_t(d1) != int16_t(d0))) {
(d0=Objectmove::GetRand());
(d0=(d0 & 31));
if((int16_t(d0) < Mem::w(PlayerBss::Plr1_RoomBright_w))) {
return 0;
}
}
return -(1);
}

int32_t ai_CheckInFront(int32_t a0){
int32_t d0=Mem::uw(a0);
int32_t a1=Mem::l(LevelBss::Lvl_ObjectPointsPtr_l);
Mem::ww(ObjectmoveData::newx,Mem::uw(j_add(a1,(int16_t(d0) * 8))));
Mem::ww(ObjectmoveData::newz,Mem::uw(j_add(j_add(a1,(int16_t(d0) * 8)),4)));
(d0=Mem::uw(PlayerBss::Plr1_TmpXOff_l));
(d0=M68k::setw(d0,(d0 - Mem::uw(ObjectmoveData::newx))));
int32_t d1=Mem::uw(PlayerBss::Plr1_TmpZOff_l);
(d1=M68k::setw(d1,(d1 - Mem::uw(ObjectmoveData::newz))));
int32_t d2=Mem::uw(j_add(a0,Defs::EntT_CurrentAngle_w));
(d2=TablesData::AMOD_A(d2));
int32_t a3=TablesData::SinCosTable_vw;
int32_t d3=Mem::w(j_add(a3,int16_t(d2)));
(d2+=TablesData::COSINE_OFS);
int32_t d4=Mem::w(j_add(a3,int16_t(d2)));
(d0=M68k::muls(d0,d3));
(d1=M68k::muls(d1,d4));
(d1+=d0);
return M68k::setb(d0,((d1 > 0)?0xFF:0));
}

void AI_LookForPlayer1(int32_t a0){
Mem::wb(j_add(a0,Defs::ObjT_SeePlayer_b),0);
Mem::wb(ObjectmoveData::CanSee,0);
Mem::wb(ObjectmoveData::ViewerTop,Mem::ub(j_add(a0,Defs::ShotT_InUpperZone_b)));
Mem::wb(ObjectmoveData::TargetTop,Mem::ub(PlayerBss::Plr1_StoodInTop_b));
Mem::wl(ObjectmoveData::Obj_ToZonePtr_l,Mem::l(PlayerBss::Plr1_ZonePtr_l));
Mem::wl(ObjectmoveData::Obj_FromZonePtr_l,Mem::l(ObjectmoveData::Obj_ZonePtr_l));
Mem::ww(ObjectmoveData::Viewerx,Mem::uw(ObjectmoveData::newx));
Mem::ww(ObjectmoveData::Viewerz,Mem::uw(ObjectmoveData::newz));
Mem::ww(ObjectmoveData::Targetx,Mem::uw(PlayerBss::Plr1_XOff_l));
Mem::ww(ObjectmoveData::Targetz,Mem::uw(PlayerBss::Plr1_ZOff_l));
int32_t d0=Mem::l(PlayerBss::Plr1_YOff_l);
(d0>>=7);
Mem::ww(ObjectmoveData::Targety,d0);
Mem::ww(ObjectmoveData::Viewery,Mem::uw(j_add(a0,4)));
Objectmove::CanItBeSeen();
if((Mem::b(ObjectmoveData::CanSee) != 0)) {
Mem::wb(j_add(a0,Defs::ObjT_SeePlayer_b),1);
}
}

void AI_InitAlienWorkspace(){
int32_t a0=AiBss::ai_AlienWorkspace_vl;
int32_t d0=299;
do {
Mem::wl(a0,0);
Mem::wl(j_add(a0,4),-(1));
Mem::wl(j_add(a0,8),-(1));
(a0+=16);
(d0=M68k::setw(d0,(d0 - 1)));
}
while((int16_t(d0) != -(1)));
(a0=AiBss::AI_AlienTeamWorkspace_vl);
(d0=29);
do {
Mem::wl(a0,0);
Mem::wl(j_add(a0,4),-(1));
Mem::wl(j_add(a0,8),-(1));
(a0+=16);
(d0=M68k::setw(d0,(d0 - 1)));
}
while((int16_t(d0) != -(1)));
}

void ai_CheckDamage(int32_t a0,int32_t a1){
int32_t d2=0;
(d2=M68k::setb(d2,Mem::ub(j_add(a0,Defs::EntT_DamageTaken_b))));
if((int8_t(d2) == 0)) {
return ;
}
Mem::wb(j_add(a0,Defs::EntT_HitPoints_b),(Mem::ub(j_add(a0,Defs::EntT_HitPoints_b)) - d2));
if((int8_t(Mem::b(j_add(a0,Defs::EntT_HitPoints_b))) <= 0)) {
int32_t d0=0;
(d0=M68k::setb(d0,Mem::ub(j_add(a0,Defs::EntT_TeamNumber_b))));
if((int8_t(d0) >= 0)) {
int32_t a2=AiBss::AI_AlienTeamWorkspace_vl;
(d0=M68k::setw(d0,j_shl(d0,4)));
(a2+=int16_t(d0));
(d0=M68k::setw(d0,Mem::uw(a0)));
if((int16_t(d0) == Mem::w(j_add(a2,Ai::AI_WorkT_SeenBy_w)))) {
Mem::ww(j_add(a2,Ai::AI_WorkT_SeenBy_w),-(1));
}
}
if((int8_t(d2) > 1)) {
int32_t la1=a1;
(la1-=Mem::l(LevelBss::Lvl_ObjectPointsPtr_l));
(la1+=TablesBss::ObjRotated_vl);
Mem::wl(HiresData::Aud_NoiseX_w,Mem::l(la1));
Mem::ww(HiresData::Aud_NoiseVol_w,400);
Mem::ww(HiresData::Aud_SampleNum_w,14);
Mem::wb(HiresData::Aud_ChannelPick_b,1);
Mem::wb(HiresData::notifplaying,0);
Mem::wb(HiresData::backbeat,0xFF);
Mem::ww(HiresData::IDNUM,Mem::uw(a0));
Mem::wb(HiresData::PlayEcho,Mem::ub(NewaliencontrolData::ALIENECHO));
Hires::MakeSomeNoise();
int32_t td0=0;
int32_t td2=M68k::setw(d2,j_shr(int16_t(d2),2));
if((int16_t(td2) <= 0)) {
(td2=M68k::setw(td2,1));
}
int32_t td3=31;
Newanims::Anim_ExplodeIntoBits(td0,td2,td3,a0);
if((int8_t(d2) >= 40)) {
Macros::FREE_ENT(a0);
return ;
}
}
int32_t la1=a1;
(la1-=Mem::l(LevelBss::Lvl_ObjectPointsPtr_l));
(la1+=TablesBss::ObjRotated_vl);
Mem::wl(HiresData::Aud_NoiseX_w,Mem::l(la1));
Mem::ww(HiresData::Aud_NoiseVol_w,200);
Mem::ww(HiresData::Aud_SampleNum_w,Mem::uw(NewaliencontrolData::screamsound));
Mem::wb(HiresData::Aud_ChannelPick_b,1);
Mem::wb(HiresData::notifplaying,0);
Mem::wb(HiresData::backbeat,0xFF);
Mem::ww(HiresData::IDNUM,Mem::uw(a0));
Mem::wb(HiresData::PlayEcho,Mem::ub(NewaliencontrolData::ALIENECHO));
Hires::MakeSomeNoise();
Mem::ww(j_add(a0,Defs::EntT_Timer3_w),25);
Mem::ww(j_add(a0,Defs::EntT_ZoneID_w),Mem::uw(j_add(a0,Defs::ObjT_ZoneID_w)));
return ;
}
Mem::wb(j_add(a0,Defs::EntT_DamageTaken_b),0);
int32_t la1=a1;
(la1-=Mem::l(LevelBss::Lvl_ObjectPointsPtr_l));
(la1+=TablesBss::ObjRotated_vl);
Mem::wl(HiresData::Aud_NoiseX_w,Mem::l(la1));
Mem::ww(HiresData::Aud_NoiseVol_w,200);
Mem::ww(HiresData::Aud_SampleNum_w,Mem::uw(NewaliencontrolData::screamsound));
Mem::wb(HiresData::Aud_ChannelPick_b,1);
Mem::wb(HiresData::notifplaying,0);
Mem::ww(HiresData::IDNUM,Mem::uw(a0));
Mem::wb(HiresData::backbeat,0xFF);
Mem::wb(HiresData::PlayEcho,Mem::ub(NewaliencontrolData::ALIENECHO));
Hires::MakeSomeNoise();
}

void ai_DoTorch(int32_t a0){
int32_t d0=Mem::w(NewaliencontrolData::ALIENBRIGHT);
if((int16_t(d0) >= 0)) {
return ;
}
int32_t d1=Mem::uw(ObjectmoveData::newx);
int32_t d2=Mem::uw(ObjectmoveData::newz);
int32_t d3=Mem::w(j_add(a0,4));
(d3<<=7);
Mem::wl(AnimBss::Anim_BrightY_l,d3);
int32_t d4=Mem::uw(j_add(a0,Defs::EntT_CurrentAngle_w));
(d3=Mem::uw(j_add(a0,Defs::ObjT_ZoneID_w)));
Newanims::Anim_BrightenPointsAngle(d0,d1,d2,d3,d4);
}

void ai_DoWalkAnim(int32_t a0){
Ai::ai_DoAttackAnim(a0);
}

void ai_DoAttackAnim(int32_t a0){
int32_t a6=Mem::l(NewaliencontrolData::AlienAnimPtr_l);
int32_t a5=Mem::l(TablesBss::WorkspacePtr_l);
int32_t d1=0;
(d1=M68k::setb(d1,Mem::ub(j_add(a5,2))));
if((int8_t(d1) == 0)) {
(d1=0);
if((int8_t(Mem::b(AiBss::AI_VecObj_w)) != 1)) {
int32_t d0=Newaliencontrol::ViewpointToDraw(a0);
(d0=M68k::setw(d0,j_add(d0,d0)));
(d1=M68k::setw(0,d0));
}
}
(d1=M68k::muls(d1,Defs::A_OptLen));
(a6+=d1);
(d1=Mem::uw(j_add(a0,Defs::EntT_Timer2_w)));
if((Mem::b(j_add(a5,1)) >= 0)) {
(d1=M68k::setb(d1,Mem::ub(j_add(a5,1))));
}
(d1=M68k::muls(d1,Defs::A_FrameLen));
Mem::wb(j_add(a5,1),0xFF);
Mem::wb(AiBss::ai_DoAction_b,Mem::ub(a5));
Mem::wb(a5,0);
Mem::wb(AiBss::ai_FinishedAnim_b,Mem::ub(j_add(a5,3)));
Mem::wb(j_add(a5,3),0);
Mem::wl(j_add(a0,8),0);
Mem::wb(j_add(a0,9),Mem::ub(j_add(a6,int16_t(d1))));
int32_t d0=Mem::b(j_add(j_add(a6,int16_t(d1)),1));
if((d0 <= 0)) {
Mem::wb(j_add(a0,10),128);
(d0=-(d0));
}
(d0=M68k::setw(d0,(d0 - 1)));
Mem::wb(j_add(a0,11),d0);
Mem::ww(AiBss::ai_AnimFacing_w,0);
if((int8_t(Mem::b(AiBss::AI_VecObj_w)) == 1)) {
Mem::ww(AiBss::ai_AnimFacing_w,Mem::uw(j_add(j_add(a6,int16_t(d1)),2)));
}
Macros::FREE_ENT_2(a0,Defs::ENT_PREV);
int32_t d3=Mem::w(HiresData::AUXOBJ);
if((d3 >= 0)) {
(d0=Mem::b(j_add(j_add(a6,int16_t(d1)),8)));
if((d0 >= 0)) {
Mem::ww(j_add(j_add(a0,Defs::ObjT_ZoneID_w),Defs::ENT_PREV),Mem::uw(j_add(a0,Defs::ObjT_ZoneID_w)));
Mem::ww(j_add(j_add(a0,Defs::EntT_ZoneID_w),Defs::ENT_PREV),Mem::uw(j_add(a0,Defs::ObjT_ZoneID_w)));
Mem::ww(j_add(j_add(a0,4),Defs::ENT_PREV),Mem::uw(j_add(a0,4)));
Mem::wb(j_add(j_add(a0,Defs::ShotT_InUpperZone_b),Defs::ENT_PREV),Mem::ub(j_add(a0,Defs::ShotT_InUpperZone_b)));
int32_t d4=Mem::b(j_add(j_add(a6,int16_t(d1)),9));
int32_t d5=Mem::b(j_add(j_add(a6,int16_t(d1)),10));
(d4=j_add(d4,d4));
(d5=j_add(d5,d5));
Mem::ww(j_add(j_add(a0,Defs::ShotT_AuxOffsetX_w),Defs::ENT_PREV),d4);
Mem::ww(j_add(j_add(a0,Defs::ShotT_AuxOffsetY_w),Defs::ENT_PREV),d5);
int32_t a4=Mem::l(HiresData::GLF_DatabasePtr_l);
int32_t a2=a4;
(a4+=Defs::GLFT_ObjectDefAnims_l);
(a2+=Defs::GLFT_ObjectDefs);
int32_t d4b=M68k::setw(0,d3);
(d3=M68k::muls(d3,Defs::O_AnimSize));
(d4b=M68k::muls(d4b,Defs::ODefT_SizeOf_l));
(a2+=d4b);
(a4+=d3);
(d0=M68k::muls(d0,Defs::O_FrameStoreSize));
int32_t gfx=Mem::w(j_add(a2,Defs::ODefT_GFXType_w));
if((gfx < 1)) {
Mem::wl(j_add(j_add(a0,Defs::OBJ_PREV),Defs::ObjT_YPos_l),0);
Mem::wb(j_add(j_add(a0,Defs::OBJ_PREV),9),Mem::ub(j_add(a4,int16_t(d0))));
Mem::wb(j_add(j_add(a0,Defs::OBJ_PREV),11),Mem::ub(j_add(j_add(a4,int16_t(d0)),1)));
Mem::ww(j_add(j_add(a0,Defs::OBJ_PREV),6),Mem::uw(j_add(j_add(a4,int16_t(d0)),2)));
}
else if((gfx == 1)) {
Mem::wl(j_add(j_add(a0,Defs::OBJ_PREV),Defs::ObjT_YPos_l),0);
Mem::wb(j_add(j_add(a0,Defs::OBJ_PREV),9),Mem::ub(j_add(a4,int16_t(d0))));
Mem::wb(j_add(j_add(a0,Defs::OBJ_PREV),11),Mem::ub(j_add(j_add(a4,int16_t(d0)),1)));
Mem::ww(j_add(j_add(a0,Defs::OBJ_PREV),6),0xffff);
}
else {
Mem::wl(j_add(j_add(a0,Defs::OBJ_PREV),Defs::ObjT_YPos_l),0);
int32_t td3=Mem::b(j_add(a4,int16_t(d0)));
(td3=-(td3));
Mem::ww(j_add(j_add(a0,Defs::OBJ_PREV),Defs::ObjT_YPos_l),td3);
Mem::wb(j_add(j_add(a0,Defs::OBJ_PREV),11),Mem::ub(j_add(j_add(a4,int16_t(d0)),1)));
Mem::ww(j_add(j_add(a0,Defs::OBJ_PREV),6),Mem::uw(j_add(j_add(a4,int16_t(d0)),2)));
}
}
}
Mem::ww(j_add(a0,6),-(1));
int32_t vec=int8_t(Mem::b(AiBss::AI_VecObj_w));
if((vec == 1)) {
return ;
}
if((vec > 1)) {
Mem::ww(j_add(a0,6),Mem::uw(j_add(j_add(a6,int16_t(d1)),2)));
(d1=Mem::ub(AiBss::AI_VecObj_w));
Mem::wb(j_add(a0,10),(Mem::ub(j_add(a0,10)) | d1));
return ;
}
Mem::ww(j_add(a0,6),Mem::uw(j_add(j_add(a6,int16_t(d1)),2)));
}

int32_t ai_CheckAttackOnGround(int32_t a0){
int32_t a3=Mem::l(PlayerBss::Plr1_ZonePtr_l);
int32_t d1=0;
(d1=M68k::setb(d1,Mem::ub(j_add(a3,Defs::ZoneT_ControlPoint_w))));
if((Mem::b(PlayerBss::Plr1_StoodInTop_b) != 0)) {
(d1=M68k::setb(d1,Mem::ub(j_add(j_add(a3,Defs::ZoneT_ControlPoint_w),1))));
}
int32_t d3=M68k::setw(0,d1);
int32_t d0=Mem::uw(j_add(a0,Defs::EntT_CurrentControlPoint_w));
if((int16_t(d1) == int16_t(d0))) {
return M68k::setb(d0,0xFF);
}
(d0=Objectmove::GetNextCPt(d0,d1));
if((int16_t(d3) == int16_t(d0))) {
return M68k::setb(d0,0xFF);
}
return M68k::setb(d0,0);
}

void ai_GetRoomCPT(int32_t a0){
int32_t a2=Mem::l(ObjectmoveData::Obj_ZonePtr_l);
int32_t d0=0;
(d0=M68k::setb(d0,Mem::ub(j_add(a2,Defs::ZoneT_ControlPoint_w))));
if((Mem::b(j_add(a0,Defs::ShotT_InUpperZone_b)) != 0)) {
(d0=M68k::setb(d0,Mem::ub(j_add(j_add(a2,Defs::ZoneT_ControlPoint_w),1))));
}
Mem::ww(j_add(a0,Defs::EntT_CurrentControlPoint_w),d0);
}

int32_t ai_CalcSqrt(int32_t d2){
if((d2 == 0)) {
return d2;
}
int32_t d0=31;
while(((d2 & j_shl(1,(d0 & 31))) == 0)){
(d0=M68k::setw(d0,(d0 - 1)));
if((int16_t(d0) == -(1))) {
break;
}
}
(d0=M68k::setw(d0,j_shr(int16_t(d0),1)));
int32_t d3=0;
(d3|=j_shl(1,(d0 & 31)));
(d0=d3);
int32_t d1=M68k::setw(0,d0);
(d1=M68k::muls(d1,d1));
(d1-=d2);
(d1>>=1);
(d1=M68k::divs(d1,d0));
(d0=M68k::setw(d0,(d0 - d1)));
if((int16_t(d0) <= 0)) {
(d0=M68k::setw(d0,1));
}
(d1=M68k::setw(d1,d0));
(d1=M68k::muls(d1,d1));
(d1-=d2);
(d1>>=1);
(d1=M68k::divs(d1,d0));
(d0=M68k::setw(d0,(d0 - d1)));
if((int16_t(d0) <= 0)) {
(d0=M68k::setw(d0,1));
}
(d1=M68k::setw(d1,d0));
(d1=M68k::muls(d1,d1));
(d1-=d2);
(d1>>=1);
(d1=M68k::divs(d1,d0));
(d0=M68k::setw(d0,(d0 - d1)));
if((int16_t(d0) <= 0)) {
(d0=M68k::setw(d0,1));
}
(d2=int16_t(d0));
return d2;
}

}