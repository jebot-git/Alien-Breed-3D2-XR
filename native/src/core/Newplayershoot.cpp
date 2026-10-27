#include "original.hpp"
namespace Newplayershoot {
void Plr1_Shot(){
Newplayershoot::plrShot(1);
}

void Plr2_Shot(){
Newplayershoot::plrShot(2);
}

void plrShot(int32_t p){
bool p1=(p == 1);
int32_t timeToShoot=(p1?PlayerBss::Plr1_TimeToShoot_w:PlayerBss::Plr2_TimeToShoot_w);
int32_t tmpGunSel=(p1?PlayerBss::Plr1_TmpGunSelected_b:PlayerBss::Plr2_TmpGunSelected_b);
int32_t ammoCounts=(p1?PlayerBss::Plr1_AmmoCounts_vw:PlayerBss::Plr2_AmmoCounts_vw);
int32_t tmpFire=(p1?PlayerBss::Plr1_TmpFire_b:PlayerBss::Plr2_TmpFire_b);
int32_t angPos=(p1?PlayerBss::Plr1_AngPos_w:PlayerBss::Plr2_AngPos_w);
int32_t xoff=(p1?PlayerBss::Plr1_XOff_l:PlayerBss::Plr2_XOff_l);
int32_t zoff=(p1?PlayerBss::Plr1_ZOff_l:PlayerBss::Plr2_ZOff_l);
int32_t yoff=(p1?PlayerBss::Plr1_YOff_l:PlayerBss::Plr2_YOff_l);
int32_t stoodInTop=(p1?PlayerBss::Plr1_StoodInTop_b:PlayerBss::Plr2_StoodInTop_b);
int32_t zonePtr=(p1?PlayerBss::Plr1_ZonePtr_l:PlayerBss::Plr2_ZonePtr_l);
int32_t obsInLine=(p1?PlayerBss::Plr1_ObsInLine_vb:PlayerBss::Plr2_ObsInLine_vb);
int32_t objDist=(p1?PlayerBss::Plr1_ObjectDistances_vw:PlayerBss::Plr2_ObjectDistances_vw);
int32_t height=(p1?PlayerBss::Plr1_Height_l:PlayerBss::Plr2_Height_l);
int32_t noiseVol=(p1?PlayerBss::Plr1_NoiseVol_w:PlayerBss::Plr2_NoiseVol_w);
int32_t aimSpeed=(p1?PlayerBss::Plr1_AimSpeed_l:PlayerBss::Plr2_AimSpeed_l);
int32_t sinVal=(p1?PlayerBss::Plr1_SinVal_w:PlayerBss::Plr2_SinVal_w);
int32_t cosVal=(p1?PlayerBss::Plr1_CosVal_w:PlayerBss::Plr2_CosVal_w);
int32_t objectPtr=(p1?PlayerBss::Plr1_ObjectPtr_l:PlayerBss::Plr2_ObjectPtr_l);
int32_t gunFrame=(p1?PlayerBss::Plr1_GunFrame_w:PlayerBss::Plr2_GunFrame_w);
int32_t d7mask=(p1?0b100011:0b10011);
if((int16_t(Mem::uw(timeToShoot)) != 0)) {
Mem::ww(timeToShoot,(Mem::uw(timeToShoot) - Mem::uw(AnimBss::Anim_TempFrames_w)));
if((int16_t(Mem::uw(timeToShoot)) < 0)) Mem::ww(timeToShoot,0);
return ;
}
int32_t d0=M68k::setb(0,Mem::ub(tmpGunSel));
Mem::wb(NewplayershootData::tempgun,d0);
int32_t a6=j_add(Mem::l(HiresData::GLF_DatabasePtr_l),Defs::GLFT_ShootDefs_l);
int32_t a5=j_add(a6,(Defs::GLFT_BulletDefs_l - Defs::GLFT_ShootDefs_l));
(a6=j_add(a6,((d0 & 0xFFFF) * 8)));
(d0=M68k::setw(0,Mem::uw(j_add(a6,Defs::ShootT_BulType_w))));
Mem::ww(NewplayershootData::BULTYPE,d0);
Mem::ww(NewplayershootData::AmmoInMyGun,Mem::uw(j_add(ammoCounts,((d0 & 0xFFFF) * 2))));
(d0=M68k::muls(d0,Defs::BulT_SizeOf_l));
(a5=j_add(a5,int16_t(d0)));
Mem::ww(NewplayershootData::BulletSpd,Mem::uw(j_add(j_add(a5,Defs::BulT_Speed_l),2)));
if((Mem::b(tmpFire) == 0)) return ;
(d0=M68k::setw(0,Mem::uw(angPos)));
Mem::ww(NewplayershootData::tempangpos,d0);
int32_t a0t=j_add(TablesData::SinCosTable_vw,(d0 & 0xFFFF));
Mem::ww(NewplayershootData::tempxdir,Mem::uw(a0t));
Mem::ww(NewplayershootData::tempzdir,Mem::uw(j_add(a0t,TablesData::COSINE_OFS)));
Mem::ww(NewanimsData::tempxoff,Mem::uw(xoff));
Mem::ww(NewanimsData::tempzoff,Mem::uw(zoff));
Mem::wl(NewplayershootData::tempyoff,Mem::l(yoff));
Mem::wl(NewplayershootData::tempyoff,j_add(Mem::l(NewplayershootData::tempyoff),(10 * 128)));
Mem::wb(NewplayershootData::tempStoodInTop,Mem::ub(stoodInTop));
Mem::wl(NewanimsData::tempRoompt,Mem::l(zonePtr));
int32_t d7=d7mask;
(d0=M68k::setw(0,-(1)));
Mem::wl(NewplayershootData::targetydiff,0);
int32_t d1=0x7fff;
int32_t a1=obsInLine;
int32_t a0=Mem::l(LevelBss::Lvl_ObjectDataPtr_l);
int32_t a2=objDist;
int32_t a4=0;
while(true){
if((int16_t(Mem::uw(a0)) < 0)) break;
bool skip=false;
if((Mem::ub(j_add(a0,Defs::ObjT_TypeID_b)) == Defs::OBJ_TYPE_AUX)) {
(skip=true);
}
else {
int32_t v=Mem::ub(a1);
(a1+=1);
if((v == 0)) (skip=true);
else {
bool los=(p1?((Mem::ub(j_add(a0,Defs::ObjT_SeePlayer_b)) & 1) != 0):((Mem::ub(j_add(a0,17)) & 2) != 0));
if(!(los)) (skip=true);
else if((int16_t(Mem::uw(j_add(a0,Defs::ObjT_ZoneID_w))) < 0)) (skip=true);
else {
int32_t d6=Mem::ub(j_add(a0,Defs::ObjT_TypeID_b));
if(((d7 & j_shl(1,(d6 & 31))) == 0)) (skip=true);
else if((Mem::b(j_add(a0,Defs::EntT_HitPoints_b)) == 0)) (skip=true);
else {
int32_t d5=M68k::setw(0,Mem::uw(a0));
int32_t d6b=M68k::setw(0,Mem::uw(j_add(a2,((d5 & 0xFFFF) * 2))));
int32_t d2v=M68k::setw(0,Mem::uw(j_add(a0,4)));
(d2v=int16_t(d2v));
(d2v=j_shl(d2v,7));
(d2v=(d2v - Mem::l(yoff)));
int32_t d3=d2v;
if((d2v < 0)) (d2v=-(d2v));
(d2v=M68k::muls(d2v,93));
(d2v=j_shr(d2v,8));
(d2v=j_shr(d2v,4));
if((int16_t(d2v) > int16_t(d6b))) (skip=true);
else if((int16_t(d1) < int16_t(d6b))) (skip=true);
else {
(d1=M68k::setw(d1,d6b));
(a4=a0);
Mem::wl(NewplayershootData::targetydiff,d3);
(d0=M68k::setw(d0,d5));
}
}
}
}
}
(a0+=Defs::ENT_NEXT);
}
Mem::ww(NewplayershootData::targdist,d1);
int32_t d5=Mem::l(NewplayershootData::targetydiff);
(d5=(d5 - Mem::l(height)));
(d5=j_add(d5,(18 * 256)));
Mem::ww(NewanimsData::closedist,d1);
int32_t d2=M68k::setw(0,Mem::uw(NewplayershootData::BulletSpd));
(d1=M68k::setw(d1,j_shr(int16_t(d1),(d2 & 31))));
if((int16_t(d1) <= 0)) (d1=M68k::setw(d1,1));
(d5=M68k::divs(d5,d1));
Mem::ww(NewanimsData::bulyspd,d5);
(d2=M68k::setw(0,Mem::uw(NewplayershootData::AmmoInMyGun)));
(d1=M68k::setw(0,Mem::uw(j_add(a6,Defs::ShootT_BulCount_w))));
if((int16_t(d2) < int16_t(d1))) {
(a2=Mem::l(objectPtr));
(d0=M68k::setw(0,Mem::uw(a2)));
(a2=TablesBss::ObjRotated_vl);
Mem::wl(HiresData::Aud_NoiseX_w,Mem::l(j_add(a2,((d0 & 0xFFFF) * 8))));
Mem::ww(HiresData::Aud_NoiseVol_w,(p1?100:300));
Mem::ww(noiseVol,100);
Mem::ww(HiresData::Aud_SampleNum_w,12);
Mem::wb(HiresData::notifplaying,0);
Mem::wb(HiresData::IDNUM,0xFB);
Hires::MakeSomeNoise();
return ;
}
if((Hires::dbgWeaponTest && (Mem::ub(NewplayershootData::tempgun) != Newplayershoot::dbgLastTestGun))) {
(Newplayershoot::dbgLastTestGun=Mem::ub(NewplayershootData::tempgun));
int32_t glf=Mem::l(HiresData::GLF_DatabasePtr_l);
JStringBuilder nm=JStringBuilder();
for(int32_t k=0;(k < 20);(k)++){
int32_t c=Mem::ub(j_add(j_add(j_add(glf,Defs::GLFT_GunNames_l),(Newplayershoot::dbgLastTestGun * 20)),k));
if((c == 0)) break;
nm.append(char16_t(c));
}
bool hitscan=(Mem::w(j_add(j_add(a5,Defs::BulT_IsHitScan_l),2)) != 0);
j_log(j_add(j_add(j_add(j_add(j_add(j_add(j_add(j_add(j_add(j_add(j_add(j_add(j_add(j_add("[arme ",Newplayershoot::dbgLastTestGun),"] \""),nm),"\" BulType="),Mem::uw(NewplayershootData::BULTYPE))," ammo="),Mem::uw(NewplayershootData::AmmoInMyGun))," BulCount="),Mem::uw(j_add(a6,Defs::ShootT_BulCount_w)))," "),(hitscan?"HITSCAN":"PROJECTILE"))," SFX="),Mem::uw(j_add(a6,Defs::ShootT_SFX_w)))," → TIRE"));
}
if(p1) {
if((Mem::ub(PlayerBss::Plr_MultiplayerType_b) != Hires::PLR_SLAVE)) {
Mem::ww(j_add(j_add(Mem::l(PlayerBss::Plr1_ObjectPtr_l),Defs::ENT_NEXT_2),Defs::EntT_Timer1_w),1);
}
}
else {
if((Mem::ub(PlayerBss::Plr_MultiplayerType_b) == Hires::PLR_SLAVE)) {
Mem::ww(j_add(j_add(Mem::l(PlayerBss::Plr1_ObjectPtr_l),Defs::ENT_NEXT_2),Defs::EntT_Timer1_w),1);
}
}
Mem::ww(timeToShoot,Mem::uw(j_add(a6,Defs::ShootT_Delay_w)));
Mem::wb(gunFrame,Mem::ub(NewplayershootData::MaxFrame));
(d2=M68k::setw(d2,(d2 - d1)));
(a2=ammoCounts);
(a2=j_add(a2,int16_t(Mem::uw(NewplayershootData::BULTYPE))));
(a2=j_add(a2,int16_t(Mem::uw(NewplayershootData::BULTYPE))));
Mem::ww(a2,d2);
(a2=Mem::l(objectPtr));
(d2=M68k::setw(0,Mem::uw(a2)));
(a2=TablesBss::ObjRotated_vl);
Mem::wl(HiresData::Aud_NoiseX_w,Mem::l(j_add(a2,((d2 & 0xFFFF) * 8))));
Mem::ww(noiseVol,100);
Mem::ww(HiresData::Aud_NoiseVol_w,300);
Mem::ww(HiresData::Aud_SampleNum_w,Mem::uw(j_add(a6,Defs::ShootT_SFX_w)));
Mem::wb(HiresData::Aud_ChannelPick_b,2);
Mem::wb(HiresData::notifplaying,0);
Mem::wb(HiresData::IDNUM,0xFB);
Hires::MakeSomeNoise();
if((int16_t(d0) < 0)) {
Newplayershoot::nothingToShoot(p,a5,a6,xoff,zoff,yoff,sinVal,cosVal,zonePtr);
return ;
}
bool doAim{};
if(p1) {
if(((Mem::b(PlayerBss::Plr1_Mouse_b) != 0) && (Mem::b(ControlloopData::Prefs_NoAutoAim_b) != 0))) (doAim=true);
else (doAim=(Mem::l(j_add(a5,Defs::BulT_Gravity_l)) != 0));
}
else {
(doAim=(Mem::l(j_add(a5,Defs::BulT_Gravity_l)) != 0));
}
if(doAim) {
int32_t dd2=M68k::setw(0,Mem::uw(aimSpeed));
int32_t dd1=M68k::setw(0,8);
(dd1=M68k::setw(dd1,(dd1 - Mem::uw(NewplayershootData::BulletSpd))));
(dd2=M68k::setw(dd2,j_shr(int16_t(dd2),(dd1 & 31))));
Mem::ww(NewanimsData::bulyspd,dd2);
}
if((Mem::w(j_add(j_add(a5,Defs::BulT_IsHitScan_l),2)) == 0)) {
Newplayershoot::fireProjectile(p,a5,a6);
return ;
}
(d7=M68k::setw(0,Mem::uw(j_add(a6,Defs::ShootT_BulCount_w))));
while(true){
int32_t rt=Objectmove::GetRand();
int32_t ta1=Mem::l(LevelBss::Lvl_ObjectPointsPtr_l);
int32_t td1=M68k::setw(0,Mem::uw(a4));
(ta1=j_add(ta1,((td1 & 0xFFFF) * 8)));
(rt=M68k::setw(rt,(rt & 0x7fff)));
(td1=M68k::setw(0,Mem::uw(ta1)));
(td1=M68k::setw(td1,(td1 - Mem::uw(xoff))));
(td1=M68k::muls(td1,td1));
int32_t td2=M68k::setw(0,Mem::uw(j_add(ta1,4)));
(td2=M68k::setw(td2,(td2 - Mem::uw(zoff))));
(td2=M68k::muls(td2,td2));
(td1=j_add(td1,td2));
(td1=j_shr(td1,6));
(rt=int16_t(rt));
(rt=j_shl(rt,1));
if((rt > td1)) Newplayershoot::hitscanSucceeded(d0,a4,a5);
else Newplayershoot::hitscanFailed(p,a4,a0,xoff,zoff,yoff,zonePtr);
(d7=M68k::setw(d7,(d7 - 1)));
if(!((int16_t(d7) > 0))) break;
}
}

void nothingToShoot(int32_t p,int32_t a5,int32_t a6,int32_t xoff,int32_t zoff,int32_t yoff,int32_t sinVal,int32_t cosVal,int32_t zonePtr){
int32_t d0=M68k::setw(0,Mem::uw(((p == 1)?PlayerBss::Plr1_AimSpeed_l:PlayerBss::Plr2_AimSpeed_l)));
int32_t d1=M68k::setw(0,8);
(d1=M68k::setw(d1,(d1 - Mem::uw(NewplayershootData::BulletSpd))));
(d0=M68k::setw(d0,j_shr(int16_t(d0),(d1 & 31))));
Mem::ww(NewanimsData::bulyspd,d0);
if((Mem::w(j_add(j_add(a5,Defs::BulT_IsHitScan_l),2)) == 0)) {
Newplayershoot::fireProjectile(p,a5,a6);
return ;
}
Mem::ww(NewanimsData::bulyspd,0);
Mem::ww(ObjectmoveData::oldx,Mem::uw(xoff));
Mem::ww(ObjectmoveData::oldz,Mem::uw(zoff));
(d0=M68k::setw(0,Mem::uw(sinVal)));
(d0=M68k::setw(d0,j_shr(int16_t(d0),7)));
(d0=M68k::setw(d0,j_add(d0,Mem::uw(ObjectmoveData::oldx))));
Mem::ww(ObjectmoveData::newx,d0);
(d0=M68k::setw(0,Mem::uw(cosVal)));
(d0=M68k::setw(d0,j_shr(int16_t(d0),7)));
(d0=M68k::setw(d0,j_add(d0,Mem::uw(ObjectmoveData::oldz))));
Mem::ww(ObjectmoveData::newz,d0);
int32_t d0l=Mem::l(yoff);
(d0l=j_add(d0l,(10 * 128)));
Mem::wl(ObjectmoveData::oldy,d0l);
int32_t d1l=d0l;
(d0l=Objectmove::GetRand());
(d0l=M68k::setw(d0l,(d0l & 0xfff)));
(d0l=M68k::setw(d0l,(d0l - 0x800)));
(d0l=int16_t(d0l));
(d1l=j_add(d1l,d0l));
Mem::wl(ObjectmoveData::newy,d1l);
Newplayershoot::setupBulletMove(zonePtr);
while(true){
Objectmove::MoveObject();
if((Mem::b(ObjectmoveData::hitwall) != 0)) break;
Newplayershoot::advanceMove();
}
int32_t a0=Mem::l(PlayerBss::Plr_ShotDataPtr_l);
(d1=M68k::setw(0,(Defs::NUM_PLR_SHOT_DATA - 1)));
while(true){
if((int16_t(Mem::uw(j_add(a0,Defs::ObjT_ZoneID_w))) < 0)) break;
(a0+=Defs::ObjT_SizeOf_l);
(d1=M68k::setw(d1,(d1 - 1)));
if((int16_t(d1) == -(1))) return ;
}
int32_t a1=Mem::l(LevelBss::Lvl_ObjectPointsPtr_l);
int32_t d2=M68k::setw(0,Mem::uw(a0));
Mem::ww(j_add(a1,((d2 & 0xFFFF) * 8)),Mem::uw(ObjectmoveData::newx));
Mem::ww(j_add(j_add(a1,((d2 & 0xFFFF) * 8)),4),Mem::uw(ObjectmoveData::newz));
Mem::wb(j_add(a0,Defs::ShotT_Status_b),1);
Mem::ww(j_add(a0,Defs::ShotT_Gravity_w),0);
Mem::wb(j_add(a0,Defs::ShotT_Size_b),Mem::ub(j_add(NewplayershootData::BULTYPE,1)));
Mem::wb(j_add(a0,Defs::ShotT_Anim_b),0);
(a1=Mem::l(ObjectmoveData::Obj_ZonePtr_l));
Mem::ww(j_add(a0,Defs::ObjT_ZoneID_w),Mem::uw(a1));
Mem::wb(j_add(a0,Defs::ShotT_Worry_b),0xFF);
int32_t d0w=Mem::l(ObjectmoveData::wallhitheight);
Mem::wl(j_add(a0,Defs::ShotT_AccYPos_w),d0w);
(d0w=j_shr(d0w,7));
Mem::ww(j_add(a0,4),d0w);
}

void fireProjectile(int32_t p,int32_t a5,int32_t a6){
int32_t d7=((p == 1)?0b100011:0b10011);
Mem::wb(((p == 1)?PlayerBss::Plr1_GunFrame_w:PlayerBss::Plr2_GunFrame_w),Mem::ub(NewplayershootData::MaxFrame));
int32_t d5=M68k::setw(0,Mem::uw(j_add(a6,Defs::ShootT_BulCount_w)));
int32_t d6=M68k::setw(0,d5);
(d6=M68k::setw(d6,(d6 - 1)));
(d6=M68k::setw(d6,j_shl((d6 & 0xFFFF),7)));
(d6=M68k::setw(d6,-(int16_t(d6))));
(d6=M68k::setw(d6,j_add(d6,Mem::uw(NewplayershootData::tempangpos))));
(d6=M68k::setw(d6,(d6 & TablesData::SINTAB_MASK_ADR)));
while(true){
int32_t a0=Mem::l(PlayerBss::Plr_ShotDataPtr_l);
int32_t d1=M68k::setw(0,(Defs::NUM_PLR_SHOT_DATA - 1));
while(true){
if((int16_t(Mem::uw(j_add(a0,Defs::ObjT_ZoneID_w))) < 0)) break;
(a0+=Defs::ObjT_SizeOf_l);
(d1=M68k::setw(d1,(d1 - 1)));
if((int16_t(d1) == -(1))) return ;
}
Mem::ww(j_add(a0,Defs::ShotT_Gravity_w),Mem::uw(j_add(j_add(a5,Defs::BulT_Gravity_l),2)));
Mem::wb(j_add(a0,Defs::ShotT_Flags_w),Mem::ub(j_add(j_add(a5,Defs::BulT_BounceHoriz_l),3)));
Mem::wb(j_add(j_add(a0,Defs::ShotT_Flags_w),1),Mem::ub(j_add(j_add(a5,Defs::BulT_BounceVert_l),3)));
int32_t d0=M68k::setw(0,Mem::uw(NewanimsData::bulyspd));
if((int16_t(d0) >= (20 * 128))) (d0=M68k::setw(d0,(20 * 128)));
if((int16_t(d0) <= (-(20) * 128))) (d0=M68k::setw(d0,(-(20) * 128)));
Mem::ww(NewanimsData::bulyspd,d0);
Mem::wb(j_add(a0,Defs::ShotT_Size_b),Mem::ub(j_add(NewplayershootData::BULTYPE,1)));
Mem::wb(j_add(a0,Defs::ShotT_Power_w),Mem::ub(j_add(j_add(a5,Defs::BulT_HitDamage_l),3)));
int32_t a1=Mem::l(LevelBss::Lvl_ObjectPointsPtr_l);
int32_t d1b=M68k::setw(0,Mem::uw(a0));
(a1=j_add(a1,((d1b & 0xFFFF) * 8)));
Mem::ww(a1,Mem::uw(NewanimsData::tempxoff));
Mem::ww(j_add(a1,4),Mem::uw(NewanimsData::tempzoff));
int32_t as1=TablesData::SinCosTable_vw;
(d0=M68k::setw(0,Mem::uw(j_add(as1,(d6 & 0xFFFF)))));
(d0=int16_t(d0));
(as1=j_add(as1,TablesData::COSINE_OFS));
int32_t d2=M68k::setw(0,Mem::uw(j_add(as1,(d6 & 0xFFFF))));
(d2=int16_t(d2));
(d6=M68k::setw(d6,j_add(d6,256)));
(d6=M68k::setw(d6,(d6 & TablesData::SINTAB_MASK_ADR)));
(d1b=M68k::setw(0,Mem::uw(NewplayershootData::BulletSpd)));
(d0=j_shl(d0,(d1b & 31)));
Mem::wl(j_add(a0,Defs::ShotT_VelocityX_w),d0);
(d2=int16_t(d2));
(d2=j_shl(d2,(d1b & 31)));
Mem::wb(j_add(a0,Defs::ObjT_TypeID_b),Defs::OBJ_TYPE_PROJECTILE);
Mem::wl(j_add(a0,Defs::ShotT_VelocityZ_w),d2);
Mem::ww(j_add(a0,Defs::ShotT_VelocityY_w),Mem::uw(NewanimsData::bulyspd));
Mem::wb(j_add(a0,Defs::ShotT_InUpperZone_b),Mem::ub(NewplayershootData::tempStoodInTop));
Mem::ww(j_add(a0,Defs::ShotT_Lifetime_w),0);
Mem::wl(j_add(a0,Defs::EntT_EnemyFlags_l),d7);
int32_t a2=Mem::l(NewanimsData::tempRoompt);
Mem::ww(j_add(a0,Defs::ObjT_ZoneID_w),Mem::uw(a2));
(d0=Mem::l(NewplayershootData::tempyoff));
(d0=j_add(d0,(20 * 128)));
Mem::wl(j_add(a0,Defs::ShotT_AccYPos_w),d0);
Mem::wb(j_add(a0,Defs::ShotT_Worry_b),0xFF);
(d0=j_shr(d0,7));
Mem::ww(j_add(a0,4),d0);
(d5=M68k::setw(d5,(d5 - 1)));
if(!((int16_t(d5) > 0))) return ;
}
}

void hitscanSucceeded(int32_t d0,int32_t a4,int32_t a5){
int32_t a0=Mem::l(PlayerBss::Plr_ShotDataPtr_l);
int32_t d1=M68k::setw(0,(Defs::NUM_PLR_SHOT_DATA - 1));
while(true){
if((int16_t(Mem::uw(j_add(a0,Defs::ObjT_ZoneID_w))) < 0)) break;
(a0+=Defs::ObjT_SizeOf_l);
(d1=M68k::setw(d1,(d1 - 1)));
if((int16_t(d1) == -(1))) return ;
}
Mem::wb(j_add(a0,Defs::ObjT_TypeID_b),Defs::OBJ_TYPE_PROJECTILE);
int32_t a1=Mem::l(LevelBss::Lvl_ObjectPointsPtr_l);
int32_t d2=M68k::setw(0,Mem::uw(a0));
Mem::wl(j_add(a1,((d2 & 0xFFFF) * 8)),Mem::l(j_add(a1,((d0 & 0xFFFF) * 8))));
Mem::wl(j_add(j_add(a1,((d2 & 0xFFFF) * 8)),4),Mem::l(j_add(j_add(a1,((d0 & 0xFFFF) * 8)),4)));
Mem::wb(j_add(a0,Defs::ShotT_Status_b),1);
Mem::ww(j_add(a0,Defs::ShotT_Gravity_w),0);
Mem::wb(j_add(a0,Defs::ShotT_Size_b),Mem::ub(j_add(NewplayershootData::BULTYPE,1)));
Mem::wb(j_add(a0,Defs::ShotT_Anim_b),0);
int32_t d1b=M68k::setw(0,Mem::uw(j_add(a4,4)));
(d1b=int16_t(d1b));
(d1b=j_shl(d1b,7));
Mem::wl(j_add(a0,Defs::ShotT_AccYPos_w),d1b);
Mem::ww(j_add(a0,Defs::ObjT_ZoneID_w),Mem::uw(j_add(a4,Defs::ObjT_ZoneID_w)));
Mem::wb(j_add(a0,Defs::ShotT_Worry_b),0xFF);
Mem::ww(j_add(a0,4),Mem::uw(j_add(a4,4)));
int32_t dmg=M68k::setw(0,Mem::uw(j_add(j_add(a5,Defs::BulT_HitDamage_l),2)));
Mem::wb(j_add(a4,Defs::EntT_DamageTaken_b),j_add(Mem::ub(j_add(a4,Defs::EntT_DamageTaken_b)),dmg));
int32_t dd1=M68k::setw(0,Mem::uw(NewplayershootData::tempxdir));
(dd1=int16_t(dd1));
(dd1=j_shl(dd1,3));
(dd1=M68k::swap(dd1));
Mem::ww(j_add(a4,Defs::EntT_ImpactX_w),dd1);
(dd1=M68k::setw(0,Mem::uw(NewplayershootData::tempzdir)));
(dd1=int16_t(dd1));
(dd1=j_shl(dd1,3));
(dd1=M68k::swap(dd1));
Mem::ww(j_add(a4,Defs::EntT_ImpactZ_w),dd1);
}

void hitscanFailed(int32_t p,int32_t a4,int32_t a0term,int32_t xoff,int32_t zoff,int32_t yoff,int32_t zonePtr){
Mem::ww(ObjectmoveData::oldx,Mem::uw(xoff));
Mem::ww(ObjectmoveData::oldz,Mem::uw(zoff));
int32_t d1=Mem::l(yoff);
(d1=j_add(d1,(10 * 128)));
Mem::wl(ObjectmoveData::oldy,d1);
int32_t d0=M68k::setw(0,Mem::uw(a4));
int32_t a1=Mem::l(LevelBss::Lvl_ObjectPointsPtr_l);
int32_t d2=M68k::setw(0,Mem::uw(j_add(a1,((d0 & 0xFFFF) * 8))));
(d2=M68k::setw(d2,(d2 - Mem::uw(ObjectmoveData::oldx))));
(d2=M68k::setw(d2,j_shr(int16_t(d2),1)));
(d2=M68k::setw(d2,j_add(d2,Mem::uw(ObjectmoveData::oldx))));
Mem::ww(ObjectmoveData::newx,d2);
(d2=M68k::setw(0,Mem::uw(j_add(j_add(a1,((d0 & 0xFFFF) * 8)),4))));
(d2=M68k::setw(d2,(d2 - Mem::uw(ObjectmoveData::oldz))));
(d2=M68k::setw(d2,j_shr(int16_t(d2),1)));
(d2=M68k::setw(d2,j_add(d2,Mem::uw(ObjectmoveData::oldz))));
Mem::ww(ObjectmoveData::newz,d2);
(d2=M68k::setw(0,Mem::uw(j_add(a0term,4))));
(d2=int16_t(d2));
(d2=j_shl(d2,7));
Mem::wl(ObjectmoveData::newy,d2);
Newplayershoot::setupBulletMove(zonePtr);
while(true){
Objectmove::MoveObject();
if((Mem::b(ObjectmoveData::hitwall) != 0)) break;
Newplayershoot::advanceMove();
}
int32_t a0=Mem::l(PlayerBss::Plr_ShotDataPtr_l);
(d1=M68k::setw(0,(Defs::NUM_PLR_SHOT_DATA - 1)));
while(true){
if((int16_t(Mem::uw(j_add(a0,Defs::ObjT_ZoneID_w))) < 0)) break;
(a0+=Defs::ObjT_SizeOf_l);
(d1=M68k::setw(d1,(d1 - 1)));
if((int16_t(d1) == -(1))) return ;
}
Mem::wb(j_add(a0,Defs::ObjT_TypeID_b),Defs::OBJ_TYPE_PROJECTILE);
(a1=Mem::l(LevelBss::Lvl_ObjectPointsPtr_l));
(d2=M68k::setw(0,Mem::uw(a0)));
Mem::ww(j_add(a1,((d2 & 0xFFFF) * 8)),Mem::uw(ObjectmoveData::newx));
Mem::ww(j_add(j_add(a1,((d2 & 0xFFFF) * 8)),4),Mem::uw(ObjectmoveData::newz));
Mem::wb(j_add(a0,Defs::ShotT_Status_b),1);
Mem::ww(j_add(a0,Defs::ShotT_Gravity_w),0);
Mem::wb(j_add(a0,Defs::ShotT_Size_b),Mem::ub(j_add(NewplayershootData::BULTYPE,1)));
Mem::wb(j_add(a0,Defs::ShotT_Anim_b),0);
(a1=Mem::l(ObjectmoveData::Obj_ZonePtr_l));
Mem::ww(j_add(a0,Defs::ObjT_ZoneID_w),Mem::uw(a1));
Mem::wb(j_add(a0,Defs::ShotT_Worry_b),0xFF);
(d1=Mem::l(ObjectmoveData::newy));
Mem::wl(j_add(a0,Defs::ShotT_AccYPos_w),d1);
(d1=j_shr(d1,7));
Mem::ww(j_add(a0,4),d1);
}

void setupBulletMove(int32_t zonePtr){
Mem::wb(ObjectmoveData::exitfirst,0xFF);
Mem::wb(ObjectmoveData::Obj_WallBounce_b,0);
Mem::ww(ObjectmoveData::Obj_ExtLen_w,0);
Mem::wb(ObjectmoveData::Obj_AwayFromWall_b,0xFF);
Mem::ww(ObjectmoveData::wallflags,0b0000010000000000);
Mem::wl(ObjectmoveData::StepUpVal,0);
Mem::wl(ObjectmoveData::StepDownVal,0x1000000);
Mem::wl(ObjectmoveData::thingheight,0);
Mem::wl(ObjectmoveData::Obj_ZonePtr_l,Mem::l(zonePtr));
}

void advanceMove(){
int32_t d0=M68k::setw(0,Mem::uw(ObjectmoveData::newx));
(d0=M68k::setw(d0,(d0 - Mem::uw(ObjectmoveData::oldx))));
Mem::ww(ObjectmoveData::oldx,j_add(Mem::uw(ObjectmoveData::oldx),d0));
Mem::ww(ObjectmoveData::newx,j_add(Mem::uw(ObjectmoveData::newx),d0));
(d0=M68k::setw(0,Mem::uw(ObjectmoveData::newz)));
(d0=M68k::setw(d0,(d0 - Mem::uw(ObjectmoveData::oldz))));
Mem::ww(ObjectmoveData::oldz,j_add(Mem::uw(ObjectmoveData::oldz),d0));
Mem::ww(ObjectmoveData::newz,j_add(Mem::uw(ObjectmoveData::newz),d0));
int32_t d0l=Mem::l(ObjectmoveData::newy);
(d0l=(d0l - Mem::l(ObjectmoveData::oldy)));
Mem::wl(ObjectmoveData::oldy,j_add(Mem::l(ObjectmoveData::oldy),d0l));
Mem::wl(ObjectmoveData::newy,j_add(Mem::l(ObjectmoveData::newy),d0l));
}

}