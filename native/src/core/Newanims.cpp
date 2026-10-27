#include "original.hpp"
namespace Newanims {
void Anim_BrightenPointsAngle(int32_t d0,int32_t d1,int32_t d2,int32_t d3,int32_t d4){
if((Mem::b(NewanimsData::Anim_LightingEnabled_b) == 0)) return ;
int32_t a6=j_add(TablesData::SinCosTable_vw,(d4 & 0xFFFF));
Newanims::brightenCore(Newanims::BPA,d0,d1,d2,d3,a6);
}

void anim_BrightenPoints(int32_t d0,int32_t d1,int32_t d2,int32_t d3){
if((Mem::b(NewanimsData::Anim_LightingEnabled_b) == 0)) return ;
if((int16_t(d0) > 0)) {
Newanims::darkenPoints(d0,d1,d2,d3);
return ;
}
Newanims::brightenCore(Newanims::BP,d0,d1,d2,d3,0);
}

void brightenCore(int32_t lbl,int32_t d0,int32_t d1,int32_t d2,int32_t d3,int32_t a6){
int32_t d4=0;
int32_t d5=0;
int32_t d6{};
int32_t d7=0;
int32_t a0{};
int32_t a1{};
int32_t a2{};
int32_t a3{};
int32_t a4{};
int32_t a5{};
int32_t zp=Mem::l(LevelBss::Lvl_ZonePtrsPtr_l);
(a0=Mem::l(j_add(zp,((d3 & 0xFFFF) * 4))));
(a2=TablesBss::CurrentPointBrights_vl);
(a3=Mem::l(LevelBss::Lvl_PointsPtr_l));
(a4=Mem::l(LevelBss::Lvl_ZoneBorderPointsPtr_l));
(a1=j_add(a0,Defs::ZoneT_PotVisibleZoneList_vw));
(a5=0);
while(true){
switch(lbl){
case BP:
case BPA:
{{
(d4=Mem::w(a1));
if((d4 < 0)) return ;
(a0=Mem::l(j_add(zp,((d4 & 0xFFFF) * 4))));
(a1+=Defs::PVST_SizeOf_l);
if((lbl == Newanims::BP)) (d7=9);
else (d3=9);
(d4=M68k::muls(d4,20));
(a5=j_add(a4,int16_t(d4)));
(a2=j_add(TablesBss::CurrentPointBrights_vl,((d4 & 0xFFFF) * 4)));
(lbl=((lbl == Newanims::BP)?Newanims::RPL:Newanims::RPLA));
continue;
}
}
case RPL:
{{
(d4=Mem::w(a5));
(a5+=2);
if((d4 < 0)) {
(lbl=Newanims::BP);
continue;
}
int32_t idx=(d4 & 0xFFFF);
(d5=M68k::setw(d5,Mem::uw(j_add(a3,(idx * 4)))));
(d6=M68k::setw(0,Mem::uw(j_add(j_add(a3,(idx * 4)),2))));
(d5=M68k::setw(d5,(d5 - d1)));
if((int16_t(d5) <= 0)) (d5=M68k::setw(d5,-(int16_t(d5))));
(d6=M68k::setw(d6,(d6 - d2)));
if((int16_t(d6) <= 0)) (d6=M68k::setw(d6,-(int16_t(d6))));
(d5=M68k::setw(d5,j_add(d5,d6)));
Newanims::applyBright(a0,a2,d0,d5);
(a2+=8);
(d7=M68k::setw(d7,(d7 - 1)));
if((int16_t(d7) != -(1))) {
(lbl=Newanims::RPL);
continue;
}
(lbl=Newanims::BP);
continue;
}
}
case RPLA:
{{
(d4=Mem::w(a5));
(a5+=2);
if((d4 < 0)) {
(lbl=Newanims::BPA);
continue;
}
int32_t idx=(d4 & 0xFFFF);
(d5=M68k::setw(d5,Mem::uw(j_add(j_add(a3,(idx * 4)),2))));
(d4=M68k::setw(d4,Mem::uw(j_add(a3,(idx * 4)))));
(d4=M68k::setw(d4,(d4 - d1)));
(d6=M68k::setw(0,d4));
if((int16_t(d4) <= 0)) (d4=M68k::setw(d4,-(int16_t(d4))));
(d5=M68k::setw(d5,(d5 - d2)));
(d7=M68k::setw(0,d5));
if((int16_t(d5) <= 0)) (d5=M68k::setw(d5,-(int16_t(d5))));
int32_t p0=d0;
int32_t p1=d1;
int32_t p2=d2;
int32_t p3=d3;
int32_t p4=d4;
int32_t p5=d5;
(d0=M68k::setw(0,Mem::uw(a6)));
(d1=M68k::setw(0,Mem::uw(j_add(a6,TablesData::COSINE_OFS))));
(d1=M68k::muls(d1,d7));
(d0=M68k::muls(d0,d6));
(d1=j_add(d1,d0));
if((d1 <= 0)) {
(d0=p0);
(d1=p1);
(d2=p2);
(d3=p3);
(d4=p4);
(d5=p5);
(a2+=8);
(d7=M68k::setw(d7,(d7 - 1)));
if((int16_t(d7) != -(1))) {
(lbl=Newanims::RPLA);
continue;
}
(lbl=Newanims::BPA);
continue;
}
(d5=d1);
(d5=-(d5));
(d5=j_add(d5,(30 * 65536)));
if((d5 < 0)) (d5=0);
(d0=M68k::setw(0,Mem::uw(a6)));
(d1=M68k::setw(0,Mem::uw(j_add(a6,TablesData::COSINE_OFS))));
(d7=M68k::muls(d7,d0));
(d6=M68k::muls(d6,d1));
(d7=(d7 - d6));
if((d7 <= 0)) (d7=-(d7));
(d7=j_add(d7,d5));
(d7=j_shl(d7,2));
(d7=M68k::swap(d7));
(d0=p0);
(d1=p1);
(d2=p2);
(d3=p3);
(d4=p4);
(d5=p5);
(d5=M68k::setw(d5,j_add(d5,d7)));
(d5=M68k::setw(d5,j_add(d5,d4)));
Newanims::applyBright(a0,a2,d0,d5);
(a2+=8);
(d3=M68k::setw(d3,(d3 - 1)));
if((int16_t(d3) != -(1))) {
(lbl=Newanims::RPLA);
continue;
}
(lbl=Newanims::BP);
continue;
}
}
default:
{return ;
}
}
}
}

void applyBright(int32_t a0,int32_t a2,int32_t d0,int32_t d5){
int32_t y=Mem::l(AnimBss::Anim_BrightY_l);
if((!((y > Mem::l(j_add(a0,Defs::ZoneT_Floor_l)))) && !((y < Mem::l(j_add(a0,Defs::ZoneT_Roof_l)))))) {
Newanims::brightOne(j_add(a2,2),Mem::l(j_add(a0,Defs::ZoneT_Roof_l)),true,d0,d5);
Newanims::brightOne(a2,Mem::l(j_add(a0,Defs::ZoneT_Floor_l)),false,d0,d5);
}
(y=Mem::l(AnimBss::Anim_BrightY_l));
if((!((y > Mem::l(j_add(a0,Defs::ZoneT_UpperFloor_l)))) && !((y < Mem::l(j_add(a0,Defs::ZoneT_UpperRoof_l)))))) {
Newanims::brightOne(j_add(a2,4),Mem::l(j_add(a0,Defs::ZoneT_UpperFloor_l)),false,d0,d5);
Newanims::brightOne(j_add(a2,6),Mem::l(j_add(a0,Defs::ZoneT_UpperRoof_l)),true,d0,d5);
}
}

void brightOne(int32_t a2off,int32_t yval,bool negd4,int32_t d0,int32_t d5){
int32_t d6=M68k::setw(0,d5);
int32_t d4=(yval - Mem::l(AnimBss::Anim_BrightY_l));
if(negd4) {
if((d4 > 0)) return ;
(d4=-(d4));
}
else {
if((d4 < 0)) return ;
}
(d4=j_shr(d4,7));
(d6=M68k::setw(d6,j_add(d6,d4)));
(d6=M68k::setw(d6,j_shr(int16_t(d6),5)));
(d6=M68k::setw(d6,j_add(d6,d0)));
if((int16_t(d6) >= 0)) return ;
int32_t v=Mem::w(a2off);
if((v < 0)) Mem::ww(a2off,-(v));
(d6=M68k::setw(d6,j_add(d6,Mem::uw(a2off))));
if((int16_t(d6) < 300)) (d6=M68k::setw(d6,300));
Mem::ww(a2off,d6);
}

void darkenPoints(int32_t d0,int32_t d1,int32_t d2,int32_t d3){
int32_t zp=Mem::l(LevelBss::Lvl_ZonePtrsPtr_l);
int32_t a0=Mem::l(j_add(zp,((d3 & 0xFFFF) * 4)));
int32_t a2=TablesBss::CurrentPointBrights_vl;
int32_t a3=Mem::l(LevelBss::Lvl_PointsPtr_l);
int32_t a1=j_add(a0,int16_t(Mem::uw(j_add(a0,Defs::ZoneT_Points_w))));
while(true){
int32_t d4=Mem::w(a1);
(a1+=2);
if((d4 < 0)) return ;
int32_t idx=(d4 & 0xFFFF);
int32_t d5=M68k::setw(0,Mem::uw(j_add(a3,(idx * 4))));
int32_t d6=M68k::setw(0,Mem::uw(j_add(j_add(a3,(idx * 4)),2)));
(d5=M68k::setw(d5,(d5 - d1)));
if((int16_t(d5) <= 0)) (d5=M68k::setw(d5,-(int16_t(d5))));
(d6=M68k::setw(d6,(d6 - d2)));
if((int16_t(d6) <= 0)) (d6=M68k::setw(d6,-(int16_t(d6))));
(d6=M68k::setw(d6,j_add(d6,d5)));
(d6=M68k::setw(d6,j_shr(int16_t(d6),5)));
(d6=M68k::setw(d6,j_add(d6,d0)));
if((int16_t(d6) <= 0)) continue;
Mem::ww(j_add(a2,(idx * 4)),j_add(Mem::uw(j_add(a2,(idx * 4))),d6));
Mem::ww(j_add(j_add(a2,(idx * 4)),2),j_add(Mem::uw(j_add(j_add(a2,(idx * 4)),2)),d6));
}
}

void Flash(int32_t d0,int32_t d1){
if((int16_t(d1) <= -(20))) (d1=M68k::setw(d1,-(20)));
int32_t a1=TablesBss::CurrentPointBrights_vl;
int32_t zp=Mem::l(LevelBss::Lvl_ZonePtrsPtr_l);
int32_t a0=Mem::l(j_add(zp,((d0 & 0xFFFF) * 4)));
int32_t savedA0=a0;
(a0=j_add(a0,int16_t(Mem::uw(j_add(a0,Defs::ZoneT_Points_w)))));
while(true){
int32_t d2=Mem::w(a0);
(a0+=2);
if((d2 < 0)) break;
int32_t i=(d2 & 0xFFFF);
Mem::ww(j_add(a1,(i * 4)),j_add(Mem::uw(j_add(a1,(i * 4))),d1));
Mem::ww(j_add(j_add(a1,(i * 4)),2),j_add(Mem::uw(j_add(j_add(a1,(i * 4)),2)),d1));
}
(a0=savedA0);
(a1=ZoneBss::Zone_BrightTable_vl);
Mem::ww(j_add(a1,((d0 & 0xFFFF) * 4)),j_add(Mem::uw(j_add(a1,((d0 & 0xFFFF) * 4))),d1));
Mem::ww(j_add(j_add(a1,((d0 & 0xFFFF) * 4)),2),j_add(Mem::uw(j_add(j_add(a1,((d0 & 0xFFFF) * 4)),2)),d1));
(a0=j_add(a0,Defs::ZoneT_PotVisibleZoneList_vw));
while(true){
int32_t dz=Mem::w(a0);
if((dz < 0)) break;
Mem::ww(j_add(a1,((dz & 0xFFFF) * 4)),j_add(Mem::uw(j_add(a1,((dz & 0xFFFF) * 4))),d1));
Mem::ww(j_add(j_add(a1,((dz & 0xFFFF) * 4)),2),j_add(Mem::uw(j_add(j_add(a1,((dz & 0xFFFF) * 4)),2)),d1));
(a0+=8);
}
}

void Anim_ExplodeIntoBits(int32_t d0,int32_t d2,int32_t d3,int32_t a0){
int32_t d1{};
int32_t d4{};
Mem::ww(NewanimsData::anim_ExpRadius_w,d3);
if((int16_t(d2) > 7)) (d2=M68k::setw(d2,7));
int32_t a5=Mem::l(LevelBss::AI_AlienShotDataPtr_l);
(d1=M68k::setw(0,(Defs::NUM_ALIEN_SHOT_DATA - 1)));
while(true){
if((int16_t(Mem::uw(j_add(a5,Defs::ObjT_ZoneID_w))) < 0)) break;
(a5+=Defs::ObjT_SizeOf_l);
(d1=M68k::setw(d1,(d1 - 1)));
if((int16_t(d1) == -(1))) return ;
}
while(true){
Mem::wb(j_add(a5,Defs::ShotT_Power_w),0);
int32_t a2=Mem::l(LevelBss::Lvl_ObjectPointsPtr_l);
(d3=M68k::setw(0,Mem::uw(a5)));
(a2=j_add(a2,((d3 & 0xFFFF) * 8)));
(d0=M68k::setw(0,Mem::uw(ObjectmoveData::newx)));
Mem::ww(a2,d0);
(d0=M68k::setw(0,Mem::uw(ObjectmoveData::newz)));
Mem::ww(j_add(a2,4),d0);
Mem::wb(j_add(a2,16),2);
(d0=Objectmove::GetRand());
(d0=M68k::setw(d0,(d0 & TablesData::SINTAB_MASK_ADR)));
int32_t a2s=j_add(TablesData::SinCosTable_vw,(d0 & 0xFFFF));
(d3=M68k::setw(0,Mem::uw(a2s)));
(d4=M68k::setw(0,Mem::uw(j_add(a2s,TablesData::COSINE_OFS))));
(d0=Objectmove::GetRand());
(d0=M68k::setw(d0,(d0 & 3)));
(d0=M68k::setw(d0,j_add(d0,1)));
(d3=int16_t(d3));
(d4=int16_t(d4));
(d3=j_shl(d3,(int16_t(d0) & 31)));
(d4=j_shl(d4,(int16_t(d0) & 31)));
(d0=Mem::l(j_add(a0,Defs::EntT_ImpactX_w)));
(d4=M68k::swap(d4));
(d0=M68k::setw(d0,j_shr(int16_t(d0),1)));
(d4=M68k::setw(d4,j_add(d4,d0)));
(d0=M68k::swap(d0));
Mem::ww(j_add(a5,Defs::ShotT_VelocityZ_w),d4);
(d3=M68k::swap(d3));
(d0=M68k::setw(d0,j_shr(int16_t(d0),1)));
(d3=M68k::setw(d3,j_add(d3,d0)));
Mem::ww(j_add(a5,Defs::ShotT_VelocityX_w),d3);
(d0=Objectmove::GetRand());
(d0=M68k::setw(d0,(d0 & 1023)));
(d0=M68k::setw(d0,j_add(d0,(2 * 128))));
(d0=M68k::setw(d0,-(int16_t(d0))));
Mem::ww(j_add(a5,Defs::ShotT_VelocityY_w),d0);
Mem::wl(j_add(a5,Defs::EntT_EnemyFlags_l),0);
Mem::ww(j_add(a5,Defs::ObjT_ZoneID_w),Mem::uw(j_add(a0,Defs::ObjT_ZoneID_w)));
(d0=M68k::setw(0,Mem::uw(j_add(a0,4))));
Mem::ww(j_add(a5,4),d0);
(d0=M68k::setw(d0,j_add(d0,6)));
(d0=int16_t(d0));
(d0=j_shl(d0,7));
Mem::wl(j_add(a5,Defs::ShotT_AccYPos_w),d0);
Mem::wb(j_add(a5,Defs::ShotT_Size_b),Mem::ub(AnimBss::Anim_SplatType_w));
Mem::ww(j_add(a5,Defs::ShotT_Flags_w),0);
Mem::ww(j_add(a5,Defs::ShotT_Lifetime_w),0);
Mem::wb(j_add(a5,Defs::ShotT_Status_b),0);
Mem::wb(j_add(a5,Defs::ShotT_InUpperZone_b),Mem::ub(j_add(a0,Defs::ShotT_InUpperZone_b)));
Mem::wb(j_add(a5,Defs::ShotT_Worry_b),0xFF);
(a5+=64);
(d2=M68k::setw(d2,(d2 - 1)));
if((int16_t(d2) < 0)) return ;
(d1=M68k::setw(d1,(d1 - 1)));
if((int16_t(d1) == -(1))) return ;
bool found=false;
while(true){
if((int16_t(Mem::uw(j_add(a5,Defs::ObjT_ZoneID_w))) < 0)) {
(found=true);
break;
}
(a5+=Defs::ObjT_SizeOf_l);
(d1=M68k::setw(d1,(d1 - 1)));
if((int16_t(d1) == -(1))) break;
}
if(!(found)) return ;
}
}

void brightanim(){
int32_t a1=AnimBss::Anim_BrightTable_vw;
int32_t a3=NewanimsData::anim_BrightessAnimPtrs_vl;
int32_t a4=NewanimsData::anim_BrightnessAnimStartPtrs_vl;
while(true){
int32_t d0=Mem::l(a3);
if((d0 < 0)) return ;
int32_t a2=d0;
(d0=M68k::setw(0,Mem::uw(a2)));
(a2+=2);
if((int16_t(d0) == NewanimsData::BRIGHT_ANIM_END)) {
(a2=Mem::l(a4));
(d0=M68k::setw(0,Mem::uw(a2)));
(a2+=2);
}
Mem::wl(a3,a2);
(a3+=4);
(a4+=4);
Mem::ww(a1,d0);
(a1+=2);
}
}

void BACKSFX(){
int32_t d0=M68k::setw(0,Mem::uw(AnimBss::Anim_TempFrames_w));
Mem::ww(AnimBss::anim_TimeToNoise_w,(Mem::uw(AnimBss::anim_TimeToNoise_w) - d0));
if((int16_t(Mem::uw(AnimBss::anim_TimeToNoise_w)) > 0)) return ;
(d0=Objectmove::GetRand());
(d0=M68k::setw(d0,j_ushr((d0 & 0xFFFF),3)));
(d0=M68k::setw(d0,(d0 & 127)));
(d0=M68k::setw(d0,j_add(d0,100)));
Mem::ww(AnimBss::anim_TimeToNoise_w,d0);
int32_t a0=Mem::l(HiresData::ZonePtr_l);
(a0=j_add(a0,int16_t(Mem::uw(AnimBss::anim_OddEven_w))));
(d0=M68k::setw(0,2));
(d0=M68k::setw(d0,(d0 - Mem::uw(AnimBss::anim_OddEven_w))));
Mem::ww(AnimBss::anim_OddEven_w,d0);
int32_t d1=M68k::setw(0,Mem::uw(j_add(a0,Defs::ZoneT_BackSFXMask_w)));
if((int16_t(d1) == 0)) return ;
(d0=Objectmove::GetRand());
(d0=M68k::setw(d0,j_ushr((d0 & 0xFFFF),3)));
do {
(d0=M68k::setw(d0,j_add(d0,1)));
(d0=M68k::setw(d0,(d0 & 15)));
}
while(((d1 & j_shl(1,(d0 & 15))) == 0));
(a0=Mem::l(HiresData::GLF_DatabasePtr_l));
(a0=j_add(a0,Defs::GLFT_AmbientSFX_l));
Mem::ww(HiresData::Aud_SampleNum_w,Mem::uw(j_add(a0,((d0 & 0xFFFF) * 2))));
Mem::ww(HiresData::IDNUM,0xFFF0);
Mem::wb(HiresData::notifplaying,0xFF);
Mem::wl(HiresData::Aud_NoiseX_w,0);
Mem::wb(HiresData::PlayEcho,0);
(d0=Objectmove::GetRand());
(d0=M68k::setw(d0,(d0 & 15)));
(d0=M68k::setw(d0,j_add(d0,32)));
Mem::ww(HiresData::Aud_NoiseVol_w,d0);
Hires::MakeSomeNoise();
}

int32_t DoWaterAnims(int32_t a0){
int32_t d0=M68k::setw(0,20);
while(true){
int32_t d1=Mem::l(a0);
(a0+=4);
int32_t d2=Mem::l(a0);
(a0+=4);
int32_t d3=Mem::l(a0);
int32_t d4=M68k::setw(0,Mem::uw(j_add(a0,4)));
int32_t d5=M68k::setw(0,d4);
(d5=M68k::muls(d5,Mem::uw(AnimBss::Anim_TempFrames_w)));
(d3=j_add(d3,d5));
if((d3 > d1)) {
if((d3 >= d2)) {
(d3=d2);
(d4=M68k::setw(d4,-(int16_t(d4))));
}
}
else {
(d3=d1);
(d4=M68k::setw(d4,-(int16_t(d4))));
}
Mem::wl(a0,d3);
(a0+=4);
Mem::ww(a0,d4);
(a0+=2);
(d1=d3);
while(true){
int32_t d2z=M68k::setw(0,Mem::uw(a0));
(a0+=2);
if((int16_t(d2z) < 0)) break;
int32_t a1=Mem::l(a0);
(a0+=4);
(a1=j_add(a1,Mem::l(LevelBss::Lvl_GraphicsPtr_l)));
int32_t d3b=j_shr(d1,6);
Mem::ww(j_add(a1,2),d3b);
int32_t a1z=Mem::l(LevelBss::Lvl_ZonePtrsPtr_l);
(a1z=Mem::l(j_add(a1z,((d2z & 0xFFFF) * 4))));
Mem::wl(j_add(a1z,Defs::ZoneT_Water_l),d1);
}
(d0=M68k::setw(d0,(d0 - 1)));
if((int16_t(d0) == -(1))) return a0;
}
}

void SwitchRoutine(){
int32_t a0=Mem::l(LevelBss::Lvl_SwitchDataPtr_l);
int32_t d0=M68k::setw(0,7);
int32_t a1=Mem::l(LevelBss::Lvl_PointsPtr_l);
int32_t lbl=Newanims::CHECKSWITCHES;
while(true){
switch(lbl){
case CHECKSWITCHES:
{{
if((Mem::b(PlayerBss::Plr1_TmpSpcTap_b) != 0)) {
Newanims::switchSpace(a0,a1,d0,PlayerBss::Plr1_TmpXOff_l,PlayerBss::Plr1_TmpZOff_l,false);
}
(lbl=Newanims::BACKTOP2);
continue;
}
}
case BACKTOP2:
{{
if((Mem::b(PlayerBss::Plr2_TmpSpcTap_b) != 0)) {
Newanims::switchSpace(a0,a1,d0,PlayerBss::Plr2_TmpXOff_l,PlayerBss::Plr2_TmpZOff_l,true);
}
(lbl=Newanims::BACKTOEND);
continue;
}
}
case BACKTOEND:
{{
if((Mem::b(j_add(a0,2)) == 0)) {
(lbl=Newanims::NOBUTT);
continue;
}
if((Mem::b(j_add(a0,10)) == 0)) {
(lbl=Newanims::NOBUTT);
continue;
}
int32_t d1=M68k::setw(0,Mem::uw(AnimBss::Anim_TempFrames_w));
(d1=M68k::setw(d1,j_add(d1,d1)));
(d1=M68k::setw(d1,j_add(d1,d1)));
Mem::wb(j_add(a0,3),(Mem::ub(j_add(a0,3)) - d1));
if((int8_t(Mem::ub(j_add(a0,3))) != 0)) {
(lbl=Newanims::NOBUTT);
continue;
}
Mem::wb(j_add(a0,10),0);
int32_t a3=j_add(Mem::l(j_add(a0,6)),Mem::l(LevelBss::Lvl_GraphicsPtr_l));
Mem::ww(j_add(a3,4),11);
int32_t d3=M68k::setw(0,Mem::uw(a3));
(d3=M68k::setw(d3,(d3 & 0b00000111100)));
Mem::ww(a3,d3);
(d3=M68k::setw(0,7));
(d3=M68k::setw(d3,(d3 - d0)));
(d3=M68k::setw(d3,j_add(d3,4)));
int32_t d4=M68k::setw(0,Mem::uw(NewanimsData::Conditions));
(d4=M68k::setw(d4,(d4 & ~(j_shl(1,(d3 & 15))))));
Mem::ww(NewanimsData::Conditions,d4);
Mem::ww(HiresData::Aud_NoiseX_w,0);
Mem::ww(HiresData::Aud_NoiseZ_w,0);
Mem::ww(HiresData::Aud_NoiseVol_w,50);
Mem::ww(HiresData::Aud_SampleNum_w,10);
Mem::wb(HiresData::Aud_ChannelPick_b,1);
Mem::wb(HiresData::notifplaying,0xFF);
Mem::ww(HiresData::IDNUM,0xFFFC);
Hires::MakeSomeNoise();
(lbl=Newanims::NOBUTT);
continue;
}
}
case NOBUTT:
{{
(a0=j_add(a0,14));
(d0=M68k::setw(d0,(d0 - 1)));
if((int16_t(d0) == -(1))) return ;
(lbl=Newanims::CHECKSWITCHES);
continue;
}
}
default:
{return ;
}
}
}
}

void switchSpace(int32_t a0,int32_t a1,int32_t d0,int32_t xoffSym,int32_t zoffSym,bool plr2){
int32_t d1=M68k::setw(0,Mem::uw(xoffSym));
int32_t d2=M68k::setw(0,Mem::uw(zoffSym));
int32_t d3=M68k::setw(0,Mem::uw(a0));
if((int16_t(d3) < 0)) return ;
(d3=M68k::setw(0,Mem::uw(j_add(a0,4))));
int32_t a2=j_add(a1,((d3 & 0xFFFF) * 4));
(d3=M68k::setw(0,Mem::uw(a2)));
(d3=M68k::setw(d3,j_add(d3,Mem::uw(j_add(a2,4)))));
(d3=M68k::setw(d3,j_shr(int16_t(d3),1)));
int32_t d4=M68k::setw(0,Mem::uw(j_add(a2,2)));
(d4=M68k::setw(d4,j_add(d4,Mem::uw(j_add(a2,6)))));
(d4=M68k::setw(d4,j_shr(int16_t(d4),1)));
(d3=M68k::setw(d3,(d3 - d1)));
(d3=M68k::muls(d3,d3));
(d4=M68k::setw(d4,(d4 - d2)));
(d4=M68k::muls(d4,d4));
(d4=j_add(d4,d3));
if((d4 >= (60 * 60))) return ;
int32_t a3=j_add(Mem::l(j_add(a0,6)),Mem::l(LevelBss::Lvl_GraphicsPtr_l));
Mem::ww(j_add(a3,4),11);
(d3=M68k::setw(0,Mem::uw(a3)));
(d3=M68k::setw(d3,(d3 & 0b00000111100)));
Mem::wb(j_add(a0,10),~(Mem::ub(j_add(a0,10))));
if((int8_t(Mem::ub(j_add(a0,10))) != 0)) {
(d3=M68k::setw(d3,(d3 | 2)));
}
Mem::ww(a3,d3);
(d3=M68k::setw(0,7));
(d3=M68k::setw(d3,(d3 - d0)));
(d3=M68k::setw(d3,j_add(d3,4)));
int32_t d4c=M68k::setw(0,Mem::uw(NewanimsData::Conditions));
(d4c=M68k::setw(d4c,(d4c ^ j_shl(1,(d3 & 15)))));
Mem::ww(NewanimsData::Conditions,d4c);
if(!(plr2)) Mem::wb(j_add(a0,3),0);
Mem::ww(HiresData::Aud_NoiseX_w,0);
Mem::ww(HiresData::Aud_NoiseZ_w,0);
Mem::ww(HiresData::Aud_NoiseVol_w,50);
Mem::ww(HiresData::Aud_SampleNum_w,10);
Mem::wb(HiresData::Aud_ChannelPick_b,1);
Mem::wb(HiresData::notifplaying,0xFF);
Mem::ww(HiresData::IDNUM,0xFFFC);
Hires::MakeSomeNoise();
}

void LiftRoutine(){
int32_t d0=0;
int32_t d1=0;
int32_t d2{};
int32_t d3=0;
int32_t d4=0;
int32_t d5=0;
int32_t d6{};
int32_t d7=0;
int32_t a0{};
int32_t a1{};
int32_t a3=0;
int32_t a5=0;
int32_t a6=TablesBss::anim_LiftHeightTable_vw;
Mem::ww(AnimBss::anim_CurrentLiftable_w,-(1));
(a0=Mem::l(LevelBss::Lvl_LiftDataPtr_l));
int32_t lbl=Newanims::DOALIFT;
while(true){
switch(lbl){
case DOALIFT:
{{
Mem::ww(AnimBss::anim_CurrentLiftable_w,j_add(Mem::uw(AnimBss::anim_CurrentLiftable_w),1));
(d0=M68k::setw(0,Mem::uw(a0)));
(a0+=2);
if((int16_t(d0) == 999)) {
Mem::ww(a6,999);
Mem::ww(AnimBss::anim_LiftOnlyLocks_w,0);
Newanims::DoWaterAnims(a0);
return ;
}
(d1=M68k::setw(0,Mem::uw(a0)));
(a0+=2);
Mem::ww(AnimBss::anim_OpeningSpeed_w,Mem::uw(a0));
(a0+=2);
Mem::ww(AnimBss::anim_OpeningSpeed_w,-(int16_t(Mem::uw(AnimBss::anim_OpeningSpeed_w))));
Mem::ww(AnimBss::anim_ClosingSpeed_w,Mem::uw(a0));
(a0+=2);
Mem::ww(AnimBss::anim_OpenDuration_w,Mem::uw(a0));
(a0+=2);
Mem::ww(AnimBss::anim_OpeningSoundFX_w,Mem::uw(a0));
(a0+=2);
Mem::ww(AnimBss::anim_ClosingSoundFX_w,Mem::uw(a0));
(a0+=2);
Mem::ww(AnimBss::anim_OpenedSoundFX_w,Mem::uw(a0));
(a0+=2);
Mem::ww(AnimBss::anim_ClosedSoundFX_w,Mem::uw(a0));
(a0+=2);
Mem::ww(AnimBss::anim_OpeningSoundFX_w,(Mem::uw(AnimBss::anim_OpeningSoundFX_w) - 1));
Mem::ww(AnimBss::anim_ClosingSoundFX_w,(Mem::uw(AnimBss::anim_ClosingSoundFX_w) - 1));
Mem::ww(AnimBss::anim_OpenedSoundFX_w,(Mem::uw(AnimBss::anim_OpenedSoundFX_w) - 1));
Mem::ww(AnimBss::anim_ClosedSoundFX_w,(Mem::uw(AnimBss::anim_ClosedSoundFX_w) - 1));
(d2=M68k::setw(0,Mem::uw(a0)));
(a0+=2);
(d3=M68k::setw(0,Mem::uw(a0)));
(a0+=2);
(d2=M68k::setw(d2,(d2 - Mem::uw(PlayerBss::Plr1_TmpXOff_l))));
(d3=M68k::setw(d3,(d3 - Mem::uw(PlayerBss::Plr1_TmpZOff_l))));
(d4=M68k::muls(Mem::w(HireswallData::Vis_CosVal_w),d2));
(d5=M68k::muls(Mem::w(HireswallData::Vis_SinVal_w),d3));
(d4=(d4 - d5));
(d4=j_add(d4,d4));
(d4=M68k::swap(d4));
Mem::ww(HiresData::Aud_NoiseX_w,d4);
(d4=M68k::muls(Mem::w(HireswallData::Vis_SinVal_w),d2));
(d5=M68k::muls(Mem::w(HireswallData::Vis_CosVal_w),d3));
(d4=(d4 - d5));
(d4=j_add(d4,d4));
(d4=M68k::swap(d4));
Mem::ww(HiresData::Aud_NoiseZ_w,d4);
(d3=M68k::setw(0,Mem::uw(a0)));
Mem::ww(a6,d3);
(a6+=2);
(d2=M68k::setw(0,Mem::uw(j_add(a0,2))));
(d7=M68k::setw(0,Mem::uw(j_add(a0,8))));
(a1=Mem::l(LevelBss::Lvl_ZonePtrsPtr_l));
(a1=Mem::l(j_add(a1,((d7 & 0xFFFF) * 4))));
Mem::wb(HiresData::PlayEcho,Mem::ub(j_add(a1,Defs::ZoneT_Echo_b)));
(d7=M68k::setw(d7,d2));
Mem::ww(AnimBss::anim_FloorMoveSpeed_w,d2);
(d2=M68k::muls(d2,Mem::uw(AnimBss::Anim_TempFrames_w)));
(d3=M68k::setw(d3,j_add(d3,d2)));
(d2=M68k::setw(d2,d7));
Mem::wb(NewanimsData::anim_LiftAtBottom_b,((int16_t(d0) <= int16_t(d3))?0xFF:0));
if((int16_t(d0) > int16_t(d3))) {
}
else {
if((int16_t(d2) != 0)) {
Mem::ww(HiresData::Aud_NoiseVol_w,50);
Mem::ww(HiresData::Aud_SampleNum_w,Mem::uw(AnimBss::anim_ClosedSoundFX_w));
if((int16_t(Mem::uw(AnimBss::anim_ClosedSoundFX_w)) >= 0)) {
Mem::wb(HiresData::Aud_ChannelPick_b,1);
Mem::wb(HiresData::notifplaying,0);
Mem::ww(HiresData::IDNUM,0xFFFD);
Hires::MakeSomeNoise();
}
}
(d2=0);
(d3=M68k::setw(d3,d0));
}
Mem::wb(NewanimsData::anim_LiftAtTop_b,((int16_t(d1) >= int16_t(d3))?0xFF:0));
if((int16_t(d1) < int16_t(d3))) {
}
else {
if((int16_t(d2) != 0)) {
Mem::ww(a6,0);
Mem::ww(HiresData::Aud_NoiseVol_w,50);
Mem::ww(HiresData::Aud_SampleNum_w,Mem::uw(AnimBss::anim_OpenedSoundFX_w));
if((int16_t(Mem::uw(AnimBss::anim_OpenedSoundFX_w)) >= 0)) {
Mem::wb(HiresData::Aud_ChannelPick_b,1);
Mem::wb(HiresData::notifplaying,0);
Mem::ww(HiresData::IDNUM,0xFFFD);
Hires::MakeSomeNoise();
}
}
(d2=0);
(d3=M68k::setw(d3,d1));
}
(d0=M68k::setw(d0,(d0 - d3)));
(d6=((int16_t(d0) < (15 * 16))?0xFF:0));
Mem::ww(a0,d3);
(a0+=2);
(a5=a0);
Mem::ww(a0,d2);
(a0+=2);
(d7=M68k::setw(d7,d2));
(a1=Mem::l(a0));
(a0+=4);
(a1=j_add(a1,Mem::l(LevelBss::Lvl_GraphicsPtr_l)));
(d3=M68k::setw(d3,j_shr(int16_t(d3),2)));
(d0=M68k::setw(d0,d3));
(d0=M68k::setw(d0,j_shl((d0 & 0xFFFF),2)));
Mem::ww(j_add(a1,2),d0);
(d0=M68k::setw(d0,d3));
(d3=int16_t(d3));
(d3=j_shl(d3,8));
(d5=M68k::setw(0,Mem::uw(a0)));
(a0+=2);
(a1=Mem::l(LevelBss::Lvl_ZonePtrsPtr_l));
(a1=Mem::l(j_add(a1,((d5 & 0xFFFF) * 4))));
(d5=M68k::setw(0,Mem::uw(a1)));
(a3=Mem::l(PlayerBss::Plr1_ZonePtr_l));
Mem::wl(j_add(a1,2),d3);
(d0=M68k::setw(d0,-(int16_t(d0))));
Mem::wb(PlayerBss::plr1_StoodOnLift_b,((int16_t(Mem::uw(a3)) == int16_t(d5))?0xFF:0));
if((int16_t(Mem::uw(a3)) == int16_t(d5))) {
Mem::ww(PlayerBss::Plr1_FloorSpd_w,Mem::uw(AnimBss::anim_FloorMoveSpeed_w));
}
(a3=Mem::l(PlayerBss::Plr2_ZonePtr_l));
Mem::wb(PlayerBss::plr2_StoodOnLift_b,((int16_t(Mem::uw(a3)) == int16_t(d5))?0xFF:0));
if((int16_t(Mem::uw(a3)) == int16_t(d5))) {
Mem::ww(PlayerBss::Plr2_FloorSpd_w,Mem::uw(AnimBss::anim_FloorMoveSpeed_w));
}
(a0+=2);
(d2=M68k::setw(0,Mem::uw(AnimBss::anim_CurrentLiftable_w)));
(d5=M68k::setw(0,Mem::uw(AnimBss::anim_LiftOnlyLocks_w)));
if(((d5 & j_shl(1,(d2 & 31))) == 0)) {
(a3=Mem::l(LevelBss::Lvl_ZoneEdgePtr_l));
(d4=M68k::setb(0,Mem::ub(a0)));
(a0+=1);
(d5=M68k::setb(0,Mem::ub(a0)));
(a0+=1);
if((Mem::b(NewanimsData::anim_LiftAtTop_b) != 0)) {
(Newanims::liftSpeed=d7);
(d1=Newanims::liftLowerMask(d5));
(d7=Newanims::liftSpeed);
}
else if((Mem::b(NewanimsData::anim_LiftAtBottom_b) != 0)) {
(Newanims::liftSpeed=d7);
(d1=Newanims::liftRaiseMask(d4));
(d7=Newanims::liftSpeed);
}
else {
(d1=M68k::setw(d1,0));
}
(lbl=Newanims::BACKFROMLIFT);
continue;
}
(d5=M68k::setw(0,Mem::uw(a0)));
(a0+=2);
(lbl=Newanims::LIFT_SIMPLE);
continue;
}
}
case BACKFROMLIFT:
{{
(d0=M68k::setw(d0,(d0 & 255)));
(a3=Mem::l(LevelBss::Lvl_ZoneEdgePtr_l));
while(true){
(d5=M68k::setw(0,Mem::uw(a0)));
(a0+=2);
if((int16_t(d5) < 0)) break;
(d5=M68k::setw(d5,j_shl((d5 & 0xFFFF),4)));
int32_t a4=j_add(a3,int16_t(d5));
(d4=M68k::setw(0,Mem::uw(j_add(a4,14))));
Mem::ww(j_add(a4,14),0x8000);
(d4=M68k::setw(d4,(d4 & d1)));
if((int16_t(d4) != 0)) {
Mem::ww(a5,d7);
Mem::ww(HiresData::Aud_NoiseVol_w,50);
Mem::ww(HiresData::Aud_SampleNum_w,Mem::uw(AnimBss::anim_ActionSoundFX_w));
if((int16_t(Mem::uw(AnimBss::anim_ActionSoundFX_w)) >= 0)) {
Mem::wb(HiresData::Aud_ChannelPick_b,1);
Mem::wb(HiresData::notifplaying,0xFF);
Mem::ww(HiresData::IDNUM,0xFFFE);
Hires::MakeSomeNoise();
}
}
(a1=Mem::l(a0));
(a0+=4);
(a1=j_add(a1,Mem::l(LevelBss::Lvl_GraphicsPtr_l)));
int32_t a2=Mem::l(a0);
(a0+=4);
(a2=j_add(a2,int16_t(d0)));
Mem::ww(j_add(a1,12),a2);
Mem::wl(j_add(a1,20),d3);
}
(lbl=Newanims::DOALIFT);
continue;
}
}
case LIFT_SIMPLE:
{{
(a3=Mem::l(LevelBss::Lvl_ZoneEdgePtr_l));
while(true){
(d5=M68k::setw(0,Mem::uw(a0)));
(a0+=2);
if((int16_t(d5) < 0)) break;
(d5=M68k::setw(d5,j_shl((d5 & 0xFFFF),4)));
int32_t a4=j_add(a3,int16_t(d5));
Mem::ww(j_add(a4,14),0);
(a1=Mem::l(a0));
(a0+=4);
(a1=j_add(a1,Mem::l(LevelBss::Lvl_GraphicsPtr_l)));
int32_t a2=Mem::l(a0);
(a0+=4);
(a2=j_add(a2,int16_t(d0)));
Mem::ww(j_add(a1,12),a2);
Mem::wl(j_add(a1,20),d3);
}
(lbl=Newanims::DOALIFT);
continue;
}
}
default:
{return ;
}
}
}
}

int32_t liftLowerMask(int32_t d5){
Mem::ww(AnimBss::anim_ActionSoundFX_w,Mem::uw(AnimBss::anim_ClosingSoundFX_w));
int32_t d1{};
if((int8_t(d5) < 1)) {
(d1=0);
if((Mem::b(PlayerBss::Plr1_TmpSpcTap_b) != 0)) {
(d1=M68k::setw(d1,0b100000000));
(Newanims::liftSpeed=M68k::setw(0,Mem::uw(AnimBss::anim_ClosingSpeed_w)));
if((Mem::b(PlayerBss::plr1_StoodOnLift_b) != 0)) {
return M68k::setw(d1,0x8000);
}
}
if((Mem::b(PlayerBss::Plr2_TmpSpcTap_b) != 0)) {
(d1=M68k::setw(d1,(d1 | 0b100000000000)));
(Newanims::liftSpeed=M68k::setw(0,Mem::uw(AnimBss::anim_ClosingSpeed_w)));
if((Mem::b(PlayerBss::plr2_StoodOnLift_b) != 0)) {
return M68k::setw(d1,0x8000);
}
}
return d1;
}
else if((int8_t(d5) == 1)) {
(Newanims::liftSpeed=M68k::setw(0,Mem::uw(AnimBss::anim_ClosingSpeed_w)));
if(((Mem::b(PlayerBss::plr1_StoodOnLift_b) != 0) || (Mem::b(PlayerBss::plr2_StoodOnLift_b) != 0))) {
return 0x8000;
}
return 0b100100000000;
}
else if((int8_t(d5) < 3)) {
(Newanims::liftSpeed=M68k::setw(0,Mem::uw(AnimBss::anim_ClosingSpeed_w)));
return 0x8000;
}
else {
return 0;
}
}

int32_t liftRaiseMask(int32_t d4){
Mem::ww(AnimBss::anim_ActionSoundFX_w,Mem::uw(AnimBss::anim_OpeningSoundFX_w));
int32_t d1{};
if((int8_t(d4) < 1)) {
(d1=0);
if((Mem::b(PlayerBss::Plr1_TmpSpcTap_b) != 0)) {
(d1=M68k::setw(d1,0b100000000));
(Newanims::liftSpeed=M68k::setw(0,Mem::uw(AnimBss::anim_OpeningSpeed_w)));
if((Mem::b(PlayerBss::plr1_StoodOnLift_b) != 0)) {
return M68k::setw(d1,0x8000);
}
}
if((Mem::b(PlayerBss::Plr2_TmpSpcTap_b) != 0)) {
(d1=M68k::setw(d1,(d1 | 0b100000000000)));
(Newanims::liftSpeed=M68k::setw(0,Mem::uw(AnimBss::anim_OpeningSpeed_w)));
if((Mem::b(PlayerBss::plr2_StoodOnLift_b) != 0)) {
return M68k::setw(d1,0x8000);
}
}
return d1;
}
else if((int8_t(d4) == 1)) {
(Newanims::liftSpeed=M68k::setw(0,Mem::uw(AnimBss::anim_OpeningSpeed_w)));
if(((Mem::b(PlayerBss::plr1_StoodOnLift_b) != 0) || (Mem::b(PlayerBss::plr2_StoodOnLift_b) != 0))) {
return 0x8000;
}
return 0b100100000000;
}
else if((int8_t(d4) < 3)) {
(Newanims::liftSpeed=M68k::setw(0,Mem::uw(AnimBss::anim_OpeningSpeed_w)));
return 0x8000;
}
else {
return 0;
}
}

void DoorRoutine(){
int32_t d0=0;
int32_t d1=0;
int32_t d2{};
int32_t d3=0;
int32_t d4=0;
int32_t d5=0;
int32_t d6{};
int32_t d7=0;
int32_t a0{};
int32_t a1{};
int32_t a3=0;
int32_t a5=0;
int32_t a6=TablesBss::anim_DoorOpenTimers_vw;
(a0=Mem::l(LevelBss::Lvl_DoorDataPtr_l));
Mem::ww(AnimBss::anim_CurrentLiftable_w,-(1));
int32_t lbl=Newanims::DOADOOR;
while(true){
switch(lbl){
case DOADOOR:
{{
Mem::ww(AnimBss::anim_CurrentLiftable_w,j_add(Mem::uw(AnimBss::anim_CurrentLiftable_w),1));
(d0=M68k::setw(0,Mem::uw(a0)));
(a0+=2);
if((int16_t(d0) == 999)) {
Mem::ww(a6,999);
Mem::ww(AnimBss::Anim_DoorAndLiftLocks_l,0);
return ;
}
(d1=M68k::setw(0,Mem::uw(a0)));
(a0+=2);
Mem::ww(AnimBss::anim_OpeningSpeed_w,Mem::uw(a0));
(a0+=2);
Mem::ww(AnimBss::anim_OpeningSpeed_w,-(int16_t(Mem::uw(AnimBss::anim_OpeningSpeed_w))));
Mem::ww(AnimBss::anim_ClosingSpeed_w,Mem::uw(a0));
(a0+=2);
Mem::ww(AnimBss::anim_OpenDuration_w,Mem::uw(a0));
(a0+=2);
Mem::ww(AnimBss::anim_OpeningSoundFX_w,Mem::uw(a0));
(a0+=2);
Mem::ww(AnimBss::anim_ClosingSoundFX_w,Mem::uw(a0));
(a0+=2);
Mem::ww(AnimBss::anim_OpenedSoundFX_w,Mem::uw(a0));
(a0+=2);
Mem::ww(AnimBss::anim_ClosedSoundFX_w,Mem::uw(a0));
(a0+=2);
Mem::ww(AnimBss::anim_OpeningSoundFX_w,(Mem::uw(AnimBss::anim_OpeningSoundFX_w) - 1));
Mem::ww(AnimBss::anim_ClosingSoundFX_w,(Mem::uw(AnimBss::anim_ClosingSoundFX_w) - 1));
Mem::ww(AnimBss::anim_OpenedSoundFX_w,(Mem::uw(AnimBss::anim_OpenedSoundFX_w) - 1));
Mem::ww(AnimBss::anim_ClosedSoundFX_w,(Mem::uw(AnimBss::anim_ClosedSoundFX_w) - 1));
(d2=M68k::setw(0,Mem::uw(a0)));
(a0+=2);
(d3=M68k::setw(0,Mem::uw(a0)));
(a0+=2);
(d2=M68k::setw(d2,(d2 - Mem::uw(PlayerBss::Plr1_TmpXOff_l))));
(d3=M68k::setw(d3,(d3 - Mem::uw(PlayerBss::Plr1_TmpZOff_l))));
(d4=M68k::muls(Mem::w(HireswallData::Vis_CosVal_w),d2));
(d5=M68k::muls(Mem::w(HireswallData::Vis_SinVal_w),d3));
(d4=(d4 - d5));
(d4=j_add(d4,d4));
(d4=M68k::swap(d4));
Mem::ww(HiresData::Aud_NoiseX_w,d4);
(d4=M68k::muls(Mem::w(HireswallData::Vis_SinVal_w),d2));
(d5=M68k::muls(Mem::w(HireswallData::Vis_CosVal_w),d3));
(d4=(d4 - d5));
(d4=j_add(d4,d4));
(d4=M68k::swap(d4));
Mem::ww(HiresData::Aud_NoiseZ_w,d4);
(d3=M68k::setw(0,Mem::uw(a0)));
(d2=M68k::setw(0,Mem::uw(j_add(a0,2))));
(d7=M68k::setw(0,Mem::uw(j_add(a0,8))));
(a1=Mem::l(LevelBss::Lvl_ZonePtrsPtr_l));
(a1=Mem::l(j_add(a1,((d7 & 0xFFFF) * 4))));
Mem::wb(HiresData::PlayEcho,Mem::ub(j_add(a1,Defs::ZoneT_Echo_b)));
(d2=M68k::muls(d2,Mem::uw(AnimBss::Anim_TempFrames_w)));
(d3=M68k::setw(d3,j_add(d3,d2)));
(d2=M68k::setw(0,Mem::uw(j_add(a0,2))));
Mem::wb(NewanimsData::anim_DoorClosed_b,((int16_t(d0) <= int16_t(d3))?0xFF:0));
if((int16_t(d0) > int16_t(d3))) {
}
else {
if((int16_t(d2) != 0)) {
Mem::ww(HiresData::Aud_NoiseVol_w,50);
Mem::ww(HiresData::Aud_SampleNum_w,Mem::uw(AnimBss::anim_ClosedSoundFX_w));
if((int16_t(Mem::uw(AnimBss::anim_ClosedSoundFX_w)) >= 0)) {
Mem::wb(HiresData::Aud_ChannelPick_b,1);
Mem::wb(HiresData::notifplaying,0);
Mem::ww(HiresData::IDNUM,0xFFFD);
Hires::MakeSomeNoise();
}
}
(d2=0);
(d0=M68k::setw(d0,d3));
}
Mem::wb(NewanimsData::anim_DoorOpen_b,((int16_t(d1) >= int16_t(d3))?0xFF:0));
if((int16_t(d1) < int16_t(d3))) {
}
else {
if((int16_t(d2) != 0)) {
Mem::ww(a6,0);
Mem::ww(HiresData::Aud_NoiseVol_w,50);
Mem::ww(HiresData::Aud_SampleNum_w,Mem::uw(AnimBss::anim_OpenedSoundFX_w));
if((int16_t(Mem::uw(AnimBss::anim_OpenedSoundFX_w)) >= 0)) {
Mem::wb(HiresData::Aud_ChannelPick_b,1);
Mem::wb(HiresData::notifplaying,0);
Mem::ww(HiresData::IDNUM,0xFFFD);
Hires::MakeSomeNoise();
}
}
(d3=M68k::setw(d3,d1));
(d2=0);
}
(d6=M68k::setw(0,Mem::uw(ZoneBss::Zone_CurrentDoorState_w)));
(d7=M68k::setw(0,Mem::uw(AnimBss::anim_CurrentLiftable_w)));
if((Mem::b(NewanimsData::anim_DoorClosed_b) != 0)) {
(d6=(d6 & ~(j_shl(1,(d7 & 31)))));
}
else {
(d6=(d6 | j_shl(1,(d7 & 31))));
}
Mem::ww(ZoneBss::Zone_CurrentDoorState_w,d6);
(d0=M68k::setw(d0,(d0 - d3)));
(d6=((int16_t(d0) >= (15 * 16))?0xFF:0));
Mem::ww(a0,d3);
(a0+=2);
(a5=a0);
Mem::ww(a0,d2);
(a0+=2);
(d7=M68k::setw(d7,d2));
(a1=Mem::l(a0));
(a0+=4);
(a1=j_add(a1,Mem::l(LevelBss::Lvl_GraphicsPtr_l)));
Mem::ww(j_add(a1,2),d3);
(d3=M68k::setw(d3,j_shr(int16_t(d3),2)));
(d0=M68k::setw(d0,d3));
(d3=M68k::muls(d3,256));
(a1=Mem::l(LevelBss::Lvl_ZonePtrsPtr_l));
(d5=M68k::setw(0,Mem::uw(a0)));
(a0+=2);
(a1=Mem::l(j_add(a1,((d5 & 0xFFFF) * 4))));
Mem::wl(j_add(a1,6),d3);
(d0=M68k::setw(d0,-(int16_t(d0))));
(d0=M68k::setw(d0,(d0 & 255)));
bool goBackUp=((int16_t(d5) == int16_t(Mem::uw(PlayerBss::Plr2_Zone_w))) || (int16_t(d5) == int16_t(Mem::uw(PlayerBss::Plr1_Zone_w))));
bool toBackfromtst=false;
if(goBackUp) {
if(((Mem::b(NewanimsData::anim_DoorOpen_b) == 0) && (int16_t(d2) >= 0))) {
(d7=M68k::setw(d7,-(16)));
(d1=M68k::setw(d1,0x8000));
(d2=M68k::setw(0,Mem::uw(a0)));
(a0+=2);
(d5=M68k::setw(0,Mem::uw(a0)));
(a0+=2);
(toBackfromtst=true);
}
}
if(!(toBackfromtst)) {
(a0+=2);
(d2=M68k::setw(0,Mem::uw(AnimBss::anim_CurrentLiftable_w)));
(d5=M68k::setw(0,Mem::uw(AnimBss::Anim_DoorAndLiftLocks_l)));
Newanims::dbgDoorLock(Mem::uw(AnimBss::anim_CurrentLiftable_w),d5);
if(((d5 & j_shl(1,(d2 & 31))) != 0)) {
(d5=M68k::setw(0,Mem::uw(a0)));
(a0+=2);
(lbl=Newanims::DOOR_SIMPLE);
continue;
}
(d5=M68k::setb(0,Mem::ub(a0)));
(a0+=1);
(d4=M68k::setb(0,Mem::ub(a0)));
(a0+=1);
if((Mem::b(NewanimsData::anim_DoorOpen_b) != 0)) {
(Newanims::liftSpeed=d7);
(d1=Newanims::doorCloseMask(a6));
(d7=Newanims::liftSpeed);
}
else if((Mem::b(NewanimsData::anim_DoorClosed_b) != 0)) {
(Newanims::liftSpeed=d7);
(d1=Newanims::doorOpenMask(d5));
(d7=Newanims::liftSpeed);
}
else {
(d1=M68k::setw(d1,0));
}
}
(lbl=Newanims::BACKFROMTST);
continue;
}
}
case BACKFROMTST:
{{
(a3=Mem::l(LevelBss::Lvl_ZoneEdgePtr_l));
while(true){
(d5=M68k::setw(0,Mem::uw(a0)));
(a0+=2);
if((int16_t(d5) < 0)) break;
(d5=M68k::setw(d5,j_shl((d5 & 0xFFFF),4)));
int32_t a4=j_add(a3,int16_t(d5));
(d4=M68k::setw(0,Mem::uw(j_add(a4,14))));
Mem::ww(j_add(a4,14),0x8000);
(d4=M68k::setw(d4,(d4 & d1)));
Newanims::dbgDoorTrigger(Mem::uw(AnimBss::anim_CurrentLiftable_w),d1,d4);
if((int16_t(d4) != 0)) {
Mem::ww(a5,d7);
Mem::ww(HiresData::Aud_NoiseVol_w,50);
Mem::ww(HiresData::Aud_SampleNum_w,Mem::uw(AnimBss::anim_ActionSoundFX_w));
if((int16_t(Mem::uw(AnimBss::anim_ActionSoundFX_w)) >= 0)) {
Mem::wb(HiresData::Aud_ChannelPick_b,1);
Mem::wb(HiresData::notifplaying,0);
Mem::ww(HiresData::IDNUM,0xFFFD);
Hires::MakeSomeNoise();
}
}
(a1=Mem::l(a0));
(a0+=4);
(a1=j_add(a1,Mem::l(LevelBss::Lvl_GraphicsPtr_l)));
int32_t a2=Mem::l(a0);
(a0+=4);
(a2=j_add(a2,int16_t(d0)));
Mem::ww(j_add(a1,12),a2);
Mem::wl(j_add(a1,24),d3);
}
(a6+=2);
(lbl=Newanims::DOADOOR);
continue;
}
}
case DOOR_SIMPLE:
{{
(a3=Mem::l(LevelBss::Lvl_ZoneEdgePtr_l));
while(true){
(d5=M68k::setw(0,Mem::uw(a0)));
(a0+=2);
if((int16_t(d5) < 0)) break;
(d5=M68k::setw(d5,j_shl((d5 & 0xFFFF),4)));
int32_t a4=j_add(a3,int16_t(d5));
Mem::ww(j_add(a4,Defs::EdgeT_Flags_w),0);
(a1=Mem::l(a0));
(a0+=4);
(a1=j_add(a1,Mem::l(LevelBss::Lvl_GraphicsPtr_l)));
int32_t a2=Mem::l(a0);
(a0+=4);
(a2=j_add(a2,int16_t(d0)));
Mem::ww(j_add(a1,12),a2);
Mem::wl(j_add(a1,24),d3);
}
(a6+=2);
(lbl=Newanims::DOADOOR);
continue;
}
}
default:
{return ;
}
}
}
}

void dbgDoorLock(int32_t porte,int32_t masque){
return;}

void dbgDoorTrigger(int32_t porte,int32_t attendu,int32_t touche){
return;}

int32_t doorOpenMask(int32_t d5){
Mem::ww(AnimBss::anim_ActionSoundFX_w,Mem::uw(AnimBss::anim_OpeningSoundFX_w));
if((int16_t(d5) < 1)) {
int32_t d1=0;
if((Mem::b(PlayerBss::Plr1_TmpSpcTap_b) != 0)) (d1=M68k::setw(d1,0b100000000));
if((Mem::b(PlayerBss::Plr2_TmpSpcTap_b) != 0)) (d1=M68k::setw(d1,(d1 | 0b100000000000)));
(Newanims::liftSpeed=M68k::setw(0,Mem::uw(AnimBss::anim_OpeningSpeed_w)));
return d1;
}
else if((int16_t(d5) == 1)) {
(Newanims::liftSpeed=M68k::setw(0,Mem::uw(AnimBss::anim_OpeningSpeed_w)));
return 0b100100000000;
}
else if((int16_t(d5) < 3)) {
(Newanims::liftSpeed=M68k::setw(0,Mem::uw(AnimBss::anim_OpeningSpeed_w)));
return 0b10000000000;
}
else if((int16_t(d5) == 3)) {
(Newanims::liftSpeed=M68k::setw(0,Mem::uw(AnimBss::anim_OpeningSpeed_w)));
return 0b1000000000;
}
else if((int16_t(d5) < 5)) {
(Newanims::liftSpeed=M68k::setw(0,Mem::uw(AnimBss::anim_OpeningSpeed_w)));
return 0x8000;
}
else {
return 0;
}
}

int32_t doorCloseMask(int32_t a6){
int32_t d1=M68k::setw(0,Mem::uw(AnimBss::Anim_TempFrames_w));
(d1=M68k::setw(d1,j_add(d1,Mem::uw(a6))));
Mem::ww(a6,d1);
int32_t d4=0;
if((int16_t(d1) < int16_t(Mem::uw(AnimBss::anim_OpenDuration_w)))) {
(d4=M68k::setw(0,1));
}
Mem::ww(AnimBss::anim_ActionSoundFX_w,Mem::uw(AnimBss::anim_ClosingSoundFX_w));
if((int16_t(d4) == 0)) {
(Newanims::liftSpeed=M68k::setw(0,Mem::uw(AnimBss::anim_ClosingSpeed_w)));
return 0x8000;
}
return 0;
}

void objmoveanim(){
int32_t d0=M68k::setw(0,Mem::uw(PlayerBss::Plr1_Zone_w));
int32_t a0=Mem::l(PlayerBss::Plr1_ZonePtr_l);
Mem::ww(PlayerBss::Plr1_Zone_w,Mem::uw(a0));
if((int16_t(Mem::uw(PlayerBss::Plr1_Zone_w)) != int16_t(d0))) {
Macros::SET_MEM_BIT(Defs::GAME_EVENTBIT_ZONE_CHANGE,GameBss::Game_ProgressSignal_l);
}
(a0=Mem::l(PlayerBss::Plr2_ZonePtr_l));
Mem::ww(PlayerBss::Plr2_Zone_w,Mem::uw(a0));
if((Mem::ub(PlayerBss::Plr_MultiplayerType_b) == Hires::PLR_SINGLE)) {
Mem::ww(PlayerBss::Plr2_Zone_w,-(5));
}
Mem::ww(PlayerBss::Plr1_NoiseVol_w,0);
Mem::ww(PlayerBss::Plr2_NoiseVol_w,0);
Mem::wl(AiBss::AI_BoredomPtr_l,AiBss::AI_BoredomSpace_vl);
Newanims::BACKSFX();
Newplayershoot::Plr1_Shot();
Newplayershoot::Plr2_Shot();
Newanims::ObjectHandler();
Newanims::DoorRoutine();
Mem::ww(PlayerBss::Plr1_FloorSpd_w,0);
Mem::ww(PlayerBss::Plr2_FloorSpd_w,0);
Newanims::LiftRoutine();
if((int16_t(Mem::uw(AnimBss::Anim_Timer_w)) <= 0)) {
Newanims::brightanim();
Mem::ww(AnimBss::Anim_Timer_w,5);
int32_t dr=Mem::l(NewanimsData::otherrip);
Mem::wl(NewanimsData::otherrip,Mem::l(NewanimsData::RipTear));
Mem::wl(NewanimsData::RipTear,dr);
}
}

void ObjectHandler(){
Mem::wl(TablesBss::WorkspacePtr_l,TablesBss::ObjectWorkspace_vl);
Mem::wl(AiBss::AI_DamagePtr_l,AiBss::AI_Damaged_vw);
int32_t a0=Mem::l(LevelBss::Lvl_ObjectDataPtr_l);
while(true){
if((int16_t(Mem::uw(a0)) < 0)) return ;
Mem::ww(j_add(a0,Defs::EntT_ZoneID_w),Mem::uw(j_add(a0,Defs::ObjT_ZoneID_w)));
if((int16_t(Mem::uw(j_add(a0,Defs::ObjT_ZoneID_w))) >= 0)) {
int32_t d0=Mem::ub(j_add(a0,Defs::ObjT_TypeID_b));
if((int8_t(d0) < 1)) {
if((int16_t(Mem::uw(j_add(a0,Defs::ObjT_ZoneID_w))) >= 0)) {
if((Mem::b(j_add(a0,Defs::EntT_HitPoints_b)) != 0)) {
Mem::wl(AnimBss::Anim_DoorAndLiftLocks_l,(Mem::l(AnimBss::Anim_DoorAndLiftLocks_l) | Mem::l(j_add(a0,Defs::EntT_DoorsAndLiftsHeld_l))));
}
if((Mem::b(j_add(a0,Defs::ShotT_Worry_b)) != 0)) {
Newaliencontrol::ItsAnAlien(a0);
if((int16_t(Mem::uw((j_add(a0,Defs::ObjT_ZoneID_w) - Defs::ObjT_SizeOf_l))) >= 0)) {
Mem::ww((j_add(a0,Defs::ObjT_ZoneID_w) - Defs::ObjT_SizeOf_l),Mem::uw(j_add(a0,Defs::ObjT_ZoneID_w)));
Mem::ww((j_add(a0,Defs::EntT_ZoneID_w) - Defs::ObjT_SizeOf_l),Mem::uw(j_add(a0,Defs::ObjT_ZoneID_w)));
}
}
}
}
else if((int8_t(d0) == 1)) {
if((int16_t(Mem::uw(j_add(a0,Defs::ObjT_ZoneID_w))) >= 0)) {
Newaliencontrol::ItsAnObject(a0);
}
}
else if((int8_t(d0) == 2)) {
Newanims::ItsABullet(a0);
}
}
(a0+=Defs::ObjT_SizeOf_l);
Mem::wl(TablesBss::WorkspacePtr_l,j_add(Mem::l(TablesBss::WorkspacePtr_l),8));
Mem::wl(AiBss::AI_DamagePtr_l,j_add(Mem::l(AiBss::AI_DamagePtr_l),2));
Mem::wl(AiBss::AI_BoredomPtr_l,j_add(Mem::l(AiBss::AI_BoredomPtr_l),8));
}
}

void ComputeBlast(int32_t d0,int32_t a0){
Mem::ww(AnimBss::anim_DoneFlames_w,0);
int32_t d6=M68k::setw(0,d0);
Mem::ww(AnimBss::anim_MaxDamage_w,d0);
int32_t d1=M68k::setw(0,d0);
(d6=int16_t(d6));
(d1=M68k::setw(d1,-(int16_t(d1))));
(d0=M68k::setw(0,Mem::uw(j_add(a0,Defs::ObjT_ZoneID_w))));
int32_t a2=Mem::l(LevelBss::Lvl_ZonePtrsPtr_l);
(a2=Mem::l(j_add(a2,((d0 & 0xFFFF) * 4))));
Mem::wl(AnimBss::anim_MiddleRoom_l,a2);
(a2=Mem::l(LevelBss::Lvl_ObjectDataPtr_l));
(a2-=Defs::ObjT_SizeOf_l);
(d6=int16_t(d6));
const int32_t savedA0=a0;
int32_t d2{};
int32_t d3{};
int32_t d4{};
int32_t d5{};
int32_t d7{};
while(true){
Mem::wl(ObjectmoveData::Obj_FromZonePtr_l,Mem::l(AnimBss::anim_MiddleRoom_l));
(a2+=Defs::ObjT_SizeOf_l);
(d0=M68k::setw(0,Mem::uw(a2)));
if((int16_t(d0) < 0)) break;
if((int16_t(Mem::uw(j_add(a2,Defs::ObjT_ZoneID_w))) < 0)) continue;
(d1=M68k::setb(0,Mem::ub(j_add(a2,Defs::ObjT_TypeID_b))));
bool checkAlien{};
if((int8_t(d1) == Defs::OBJ_TYPE_OBJECT)) continue;
else if((int8_t(d1) < Defs::OBJ_TYPE_OBJECT)) (checkAlien=true);
else if((int8_t(d1) == Defs::OBJ_TYPE_AUX)) continue;
else if((int8_t(d1) > Defs::OBJ_TYPE_AUX)) (checkAlien=true);
else {
(d7=M68k::setb(0,Mem::ub(j_add(a2,Defs::ShotT_Size_b))));
int32_t a3=Mem::l(HiresData::GLF_DatabasePtr_l);
(d7=M68k::muls(d7,Defs::BulT_SizeOf_l));
(a3=j_add(j_add(a3,Defs::GLFT_BulletDefs_l),d7));
if((Mem::l(j_add(a3,Defs::BulT_Gravity_l)) == 0)) continue;
(checkAlien=false);
}
if(checkAlien) {
if((Mem::b(j_add(a2,Defs::EntT_HitPoints_b)) == 0)) continue;
}
(d1=M68k::setw(0,Mem::uw(j_add(a2,Defs::ObjT_ZoneID_w))));
int32_t a3=Mem::l(LevelBss::Lvl_ZonePtrsPtr_l);
(a3=Mem::l(j_add(a3,((d1 & 0xFFFF) * 4))));
Mem::wl(ObjectmoveData::Obj_ToZonePtr_l,a3);
(a3=Mem::l(LevelBss::Lvl_ObjectPointsPtr_l));
Mem::ww(ObjectmoveData::Targetx,Mem::uw(j_add(a3,((d0 & 0xFFFF) * 8))));
Mem::ww(ObjectmoveData::Targetz,Mem::uw(j_add(j_add(a3,((d0 & 0xFFFF) * 8)),4)));
Mem::ww(ObjectmoveData::Targety,Mem::uw(j_add(a2,4)));
Mem::wb(ObjectmoveData::TargetTop,Mem::ub(j_add(a2,Defs::ShotT_InUpperZone_b)));
Objectmove::CanItBeSeen();
if((Mem::b(ObjectmoveData::CanSee) == 0)) continue;
(d0=M68k::setw(0,Mem::uw(ObjectmoveData::Targetx)));
(d0=M68k::setw(d0,(d0 - Mem::uw(ObjectmoveData::Viewerx))));
(d2=M68k::setw(0,d0));
(d1=M68k::setw(0,Mem::uw(ObjectmoveData::Targetz)));
(d1=M68k::setw(d1,(d1 - Mem::uw(ObjectmoveData::Viewerz))));
(d3=M68k::setw(0,d1));
(d2=M68k::muls(d2,d2));
(d3=M68k::muls(d3,d3));
(d4=M68k::setw(0,1));
(d2=j_add(d2,d3));
if((d2 != 0)) {
(d4=M68k::setw(0,31));
while(true){
if(((d2 & j_shl(1,(d4 & 31))) != 0)) break;
(d4=M68k::setw(d4,(d4 - 1)));
if((int16_t(d4) == -(1))) break;
}
(d4=M68k::setw(d4,j_shr(int16_t(d4),1)));
(d3=j_shl(1,(d4 & 31)));
(d4=d3);
(d3=M68k::setw(0,d4));
(d3=M68k::muls(d3,d3));
(d3=(d3 - d2));
(d3=j_shr(d3,1));
(d3=M68k::divs(d3,d4));
(d4=M68k::setw(d4,(d4 - d3)));
if(!((int16_t(d4) > 0))) (d4=M68k::setw(d4,1));
for(int32_t it=0;(it < 2);(it)++){
(d3=M68k::setw(0,d4));
if((it == 0)) (d3=M68k::muls(d3,d1));
else (d3=M68k::muls(d3,d3));
(d3=(d3 - d2));
(d3=j_shr(d3,1));
(d3=M68k::divs(d3,d4));
(d4=M68k::setw(d4,(d4 - d3)));
if(!((int16_t(d4) > 0))) (d4=M68k::setw(d4,1));
}
}
(d3=M68k::setw(0,d4));
(d7=M68k::setw(0,d3));
if((int16_t(d7) < 256)) (d7=M68k::setw(d7,256));
(d3=M68k::setw(d3,j_shr(int16_t(d3),3)));
(d3=M68k::setw(d3,(d3 - 4)));
if((int16_t(d3) < 0)) (d3=M68k::setw(d3,0));
if((int16_t(d3) > 64)) continue;
(d3=M68k::setw(d3,-(int16_t(d3))));
(d3=M68k::setw(d3,j_add(d3,64)));
(d5=M68k::setw(0,d6));
(d5=M68k::muls(d5,d3));
(d5=j_shr(d5,5));
if((int16_t(d5) >= int16_t(Mem::uw(AnimBss::anim_MaxDamage_w)))) (d5=M68k::setw(d5,Mem::uw(AnimBss::anim_MaxDamage_w)));
Mem::wb(j_add(a2,Defs::EntT_DamageTaken_b),j_add(Mem::ub(j_add(a2,Defs::EntT_DamageTaken_b)),d5));
(d0=int16_t(d0));
(d1=int16_t(d1));
(d0=(d0 * d6));
(d1=(d1 * d6));
(d0=M68k::divs(d0,d7));
(d1=M68k::divs(d1,d7));
(d2=M68k::setb(0,Mem::ub(j_add(a2,Defs::ObjT_TypeID_b))));
if((int8_t(d2) == 2)) {
Mem::ww(j_add(a2,Defs::ShotT_VelocityX_w),j_add(Mem::uw(j_add(a2,Defs::ShotT_VelocityX_w)),d0));
Mem::ww(j_add(a2,Defs::ShotT_VelocityZ_w),j_add(Mem::uw(j_add(a2,Defs::ShotT_VelocityZ_w)),d1));
int32_t dy=d6;
(dy=j_shl(dy,8));
(dy=j_shl(dy,4));
(dy=M68k::divs(dy,d7));
(dy=M68k::setw(dy,-(int16_t(dy))));
if((int16_t(dy) < (-(8) * 256))) (dy=M68k::setw(dy,(-(8) * 256)));
Mem::ww(j_add(a2,Defs::ShotT_VelocityY_w),j_add(Mem::uw(j_add(a2,Defs::ShotT_VelocityY_w)),dy));
}
else {
Mem::ww(j_add(a2,Defs::EntT_ImpactX_w),d0);
Mem::ww(j_add(a2,Defs::EntT_ImpactZ_w),d1);
int32_t dy=d6;
(dy=j_shl(dy,4));
(dy=M68k::divs(dy,d7));
(dy=M68k::setw(dy,-(int16_t(dy))));
if((int16_t(dy) < -(8))) (dy=M68k::setw(dy,-(8)));
Mem::ww(j_add(a2,Defs::EntT_ImpactY_w),dy);
}
}
(a0=savedA0);
(d0=M68k::setw(0,Mem::uw(a0)));
(a2=Mem::l(LevelBss::Lvl_ObjectPointsPtr_l));
(d1=M68k::setw(0,Mem::uw(j_add(a2,((d0 & 0xFFFF) * 8)))));
(d2=M68k::setw(0,Mem::uw(j_add(j_add(a2,((d0 & 0xFFFF) * 8)),4))));
Mem::ww(AnimBss::anim_MiddleX_w,d1);
Mem::ww(AnimBss::anim_MiddleZ_w,d2);
(d7=M68k::setw(0,9));
Mem::wb(ObjectmoveData::exitfirst,0);
Mem::wb(ObjectmoveData::Obj_WallBounce_b,0xFF);
(d0=M68k::setw(0,Mem::uw(j_add(a0,12))));
int32_t a3=Mem::l(LevelBss::Lvl_ZonePtrsPtr_l);
(a3=Mem::l(j_add(a3,((d0 & 0xFFFF) * 4))));
Mem::wl(AnimBss::anim_MiddleRoom_l,a3);
(a3=Mem::l(PlayerBss::Plr_ShotDataPtr_l));
(d0=M68k::setw(0,Mem::uw(j_add(a0,4))));
(d0=int16_t(d0));
(d0=j_shl(d0,7));
Mem::wl(ObjectmoveData::oldy,d0);
(d5=2);
Mem::ww(NewanimsData::NUMTOCHECK,(Defs::NUM_PLR_SHOT_DATA - 1));
(d6=M68k::setw(0,2));
while(true){
(d7=M68k::setw(0,1));
bool noMore=false;
while(true){
(d1=M68k::setw(0,Mem::uw(NewanimsData::NUMTOCHECK)));
bool found=false;
while(true){
if((int16_t(Mem::uw(j_add(a3,Defs::ObjT_ZoneID_w))) < 0)) {
(found=true);
break;
}
(a3+=Defs::ObjT_SizeOf_l);
(d1=M68k::setw(d1,(d1 - 1)));
if((int16_t(d1) == -(1))) break;
}
if(!(found)) return ;
Mem::wb(j_add(a3,16),2);
Mem::ww(NewanimsData::NUMTOCHECK,d1);
Mem::ww(AnimBss::anim_DoneFlames_w,j_add(Mem::uw(AnimBss::anim_DoneFlames_w),1));
(d1=M68k::setw(0,Mem::uw(AnimBss::anim_MiddleX_w)));
(d2=M68k::setw(0,Mem::uw(AnimBss::anim_MiddleZ_w)));
Mem::ww(ObjectmoveData::oldx,d1);
Mem::ww(ObjectmoveData::oldz,d2);
Mem::wb(ObjectmoveData::StoodInTop,Mem::ub(j_add(a0,Defs::ShotT_InUpperZone_b)));
(d0=Objectmove::GetRand());
(d0=M68k::extw(d0));
(d0=M68k::muls(d0,d5));
(d0=M68k::setw(d0,j_shr(int16_t(d0),1)));
if((int16_t(d0) == 0)) (d0=M68k::setw(d0,2));
(d1=M68k::setw(d1,j_add(d1,d0)));
(d0=Objectmove::GetRand());
(d0=M68k::extw(d0));
(d0=M68k::muls(d0,d5));
(d0=M68k::setw(d0,j_shr(int16_t(d0),1)));
if((int16_t(d0) == 0)) (d0=M68k::setw(d0,2));
(d2=M68k::setw(d2,j_add(d2,d0)));
int32_t d3f=Mem::l(ObjectmoveData::oldy);
(d0=Objectmove::GetRand());
(d0=M68k::muls(d0,d5));
(d0=j_shr(d0,3));
(d3f=j_add(d3f,d0));
Mem::wl(ObjectmoveData::newy,d3f);
Mem::ww(ObjectmoveData::newx,d1);
Mem::ww(ObjectmoveData::newz,d2);
Mem::wl(ObjectmoveData::Obj_ZonePtr_l,Mem::l(AnimBss::anim_MiddleRoom_l));
Mem::ww(ObjectmoveData::Obj_ExtLen_w,80);
Mem::wb(ObjectmoveData::Obj_AwayFromWall_b,1);
Objectmove::MoveObject();
int32_t a2f=Mem::l(ObjectmoveData::Obj_ZonePtr_l);
Mem::ww(j_add(a3,12),Mem::uw(a2f));
(d0=Mem::l(ObjectmoveData::newy));
int32_t dfloor=Mem::l(j_add(a2f,Defs::ZoneT_Floor_l));
int32_t droof=Mem::l(j_add(a2f,Defs::ZoneT_Roof_l));
if((Mem::b(j_add(a0,Defs::ShotT_InUpperZone_b)) != 0)) {
(dfloor=Mem::l(j_add(a2f,Defs::ZoneT_UpperFloor_l)));
(droof=Mem::l(j_add(a2f,Defs::ZoneT_UpperRoof_l)));
}
if((dfloor > d0)) (d0=dfloor);
if((droof < d0)) (d0=droof);
Mem::wl(j_add(a3,Defs::ShotT_AccYPos_w),d0);
(d0=j_shr(d0,7));
Mem::ww(j_add(a3,4),d0);
Mem::wb(j_add(a3,16),2);
Mem::wb(j_add(a3,Defs::ShotT_Anim_b),0);
Mem::wb(j_add(a3,Defs::ShotT_Status_b),0xFF);
Mem::wb(j_add(a3,Defs::ShotT_InUpperZone_b),Mem::ub(ObjectmoveData::StoodInTop));
Mem::wb(j_add(a3,Defs::ShotT_Size_b),Mem::ub(NewanimsData::BLOODYGREATBOMB));
Mem::wb(j_add(a3,Defs::ShotT_Worry_b),0xFF);
(d0=M68k::setw(0,Mem::uw(a3)));
(a2f=Mem::l(LevelBss::Lvl_ObjectPointsPtr_l));
Mem::ww(j_add(a2f,((d0 & 0xFFFF) * 8)),Mem::uw(ObjectmoveData::newx));
Mem::ww(j_add(j_add(a2f,((d0 & 0xFFFF) * 8)),4),Mem::uw(ObjectmoveData::newz));
(a3+=64);
Mem::ww(NewanimsData::NUMTOCHECK,(Mem::uw(NewanimsData::NUMTOCHECK) - 1));
if((int16_t(Mem::uw(NewanimsData::NUMTOCHECK)) < 0)) {
(noMore=true);
break;
}
(d7=M68k::setw(d7,(d7 - 1)));
if((int16_t(d7) == -(1))) break;
}
if(noMore) return ;
(d5=M68k::setw(d5,j_add(d5,2)));
(d6=M68k::setw(d6,(d6 - 1)));
if((int16_t(d6) == -(1))) return ;
}
}

void ItsABullet(int32_t a0){
Mem::wb(NewanimsData::timeout,0);
int32_t d0=M68k::setw(0,Mem::uw(j_add(a0,Defs::ObjT_ZoneID_w)));
Mem::ww(j_add(a0,Defs::EntT_ZoneID_w),d0);
if((int16_t(d0) < 0)) return ;
int32_t d1=M68k::setb(0,Mem::ub(j_add(a0,Defs::ShotT_Size_b)));
(d1=M68k::muls(d1,Defs::BulT_SizeOf_l));
int32_t a6=j_add(j_add(Mem::l(HiresData::GLF_DatabasePtr_l),Defs::GLFT_BulletDefs_l),d1);
if((Mem::b(j_add(a0,Defs::ShotT_Status_b)) == 0)) {
int32_t d2=M68k::setw(0,Mem::uw(j_add(a0,Defs::ShotT_Lifetime_w)));
if((int16_t(d2) >= 0)) {
int32_t dlt=Mem::l(j_add(a6,Defs::BulT_Lifetime_l));
if((dlt >= 0)) {
if((int16_t(dlt) >= int16_t(d2))) {
Mem::ww(j_add(a0,Defs::ShotT_Lifetime_w),j_add(Mem::uw(j_add(a0,Defs::ShotT_Lifetime_w)),Mem::uw(AnimBss::Anim_TempFrames_w)));
}
else {
Mem::wb(NewanimsData::timeout,0xFF);
}
}
}
}
Mem::ww(ObjectmoveData::Obj_ExtLen_w,0);
Mem::wb(ObjectmoveData::Obj_AwayFromWall_b,0xFF);
if((Mem::b(j_add(a0,Defs::ShotT_Status_b)) != 0)) {
int32_t a1=j_add(a6,Defs::BulT_PopData_vb);
(d1=M68k::setb(0,Mem::ub(j_add(a0,Defs::ShotT_Anim_b))));
int32_t d2=M68k::setw(0,d1);
(d1=M68k::setw(d1,j_add(d1,d1)));
(d1=M68k::setw(d1,j_add(d1,d2)));
(d1=M68k::setw(d1,j_add(d1,d1)));
Mem::wl(j_add(a0,8),0);
int32_t gt=Mem::l(j_add(a6,Defs::BulT_ImpactGraphicType_l));
int32_t idx=(d1 & 0xFFFF);
if((gt < 1)) {
Mem::wb(j_add(a0,9),Mem::ub(j_add(a1,idx)));
Mem::wb(j_add(a0,11),Mem::ub(j_add(j_add(a1,1),idx)));
Mem::ww(j_add(a0,6),Mem::uw(j_add(j_add(a1,2),idx)));
Mem::wb(NewanimsData::anim_Brightness_w,Mem::ub(j_add(j_add(a1,5),idx)));
}
else if((gt == 1)) {
int32_t dg=int16_t(int8_t(Mem::ub(j_add(a1,idx))));
(dg=-(dg));
Mem::ww(j_add(a0,8),dg);
Mem::wb(j_add(a0,11),Mem::ub(j_add(j_add(a1,1),idx)));
Mem::ww(j_add(a0,6),Mem::uw(j_add(j_add(a1,2),idx)));
Mem::wb(NewanimsData::anim_Brightness_w,Mem::ub(j_add(j_add(a1,5),idx)));
}
else {
Mem::wb(j_add(a0,9),Mem::ub(j_add(a1,idx)));
Mem::wb(j_add(a0,11),Mem::ub(j_add(j_add(a1,1),idx)));
Mem::wb(j_add(a0,10),6);
Mem::ww(j_add(a0,6),Mem::uw(j_add(j_add(a1,2),idx)));
Mem::wb(NewanimsData::anim_Brightness_w,Mem::ub(j_add(j_add(a1,5),idx)));
}
(d2=M68k::setw(d2,j_add(d2,1)));
if((int16_t(d2) > int16_t(Mem::uw(j_add(j_add(a6,Defs::BulT_PopFrames_l),2))))) {
Macros::FREE_ENT(a0);
Mem::wb(j_add(a0,Defs::ShotT_Status_b),0);
Mem::wb(j_add(a0,Defs::ShotT_Anim_b),0);
return ;
}
Mem::wb(j_add(a0,Defs::ShotT_Anim_b),d2);
int32_t db=M68k::setb(0,Mem::ub(NewanimsData::anim_Brightness_w));
if((int8_t(db) != 0)) {
(db=M68k::setw(db,-(int16_t(db))));
int32_t d2p=M68k::setw(0,Mem::uw(a0));
int32_t a2=Mem::l(LevelBss::Lvl_ObjectPointsPtr_l);
int32_t dx=M68k::setw(0,Mem::uw(j_add(a2,((d2p & 0xFFFF) * 8))));
int32_t dz=M68k::setw(0,Mem::uw(j_add(j_add(a2,((d2p & 0xFFFF) * 8)),4)));
int32_t dy=M68k::setw(0,Mem::uw(j_add(a0,4)));
(dy=int16_t(dy));
(dy=j_shl(dy,7));
Mem::wl(AnimBss::Anim_BrightY_l,dy);
int32_t dzone=M68k::setw(0,Mem::uw(j_add(a0,Defs::ObjT_ZoneID_w)));
Newanims::anim_BrightenPoints(db,dx,dz,dzone);
}
return ;
}
Mem::wb(NewanimsData::BLOODYGREATBOMB,Mem::ub(j_add(a0,Defs::ShotT_Size_b)));
int32_t a1=j_add(a6,Defs::BulT_AnimData_vb);
(d1=M68k::setb(0,Mem::ub(j_add(a0,Defs::ShotT_Anim_b))));
(d1=M68k::setw(d1,j_add(d1,d1)));
int32_t d2=M68k::setw(0,d1);
(d1=M68k::setw(d1,j_add(d1,d1)));
(d1=M68k::setw(d1,j_add(d1,d2)));
Mem::wl(j_add(a0,8),0);
int32_t gt=Mem::l(j_add(a6,Defs::BulT_GraphicType_l));
int32_t idx=(d1 & 0xFFFF);
if((gt < 1)) {
Mem::wb(j_add(a0,9),Mem::ub(j_add(a1,idx)));
Mem::wb(j_add(a0,11),Mem::ub(j_add(j_add(a1,1),idx)));
Mem::ww(j_add(a0,6),Mem::uw(j_add(j_add(a1,2),idx)));
Mem::wb(NewanimsData::anim_Brightness_w,Mem::ub(j_add(j_add(a1,5),idx)));
}
else if((gt == 1)) {
int32_t dg=int16_t(int8_t(Mem::ub(j_add(a1,idx))));
(dg=-(dg));
(d0=M68k::setw(d0,dg));
Mem::ww(j_add(a0,8),dg);
Mem::wb(j_add(a0,11),Mem::ub(j_add(j_add(a1,1),idx)));
Mem::ww(j_add(a0,6),Mem::uw(j_add(j_add(a1,2),idx)));
Mem::wb(NewanimsData::anim_Brightness_w,Mem::ub(j_add(j_add(a1,5),idx)));
}
else {
Mem::wb(j_add(a0,9),Mem::ub(j_add(a1,idx)));
Mem::wb(j_add(a0,11),Mem::ub(j_add(j_add(a1,1),idx)));
Mem::wb(j_add(a0,10),6);
Mem::ww(j_add(a0,6),Mem::uw(j_add(j_add(a1,2),idx)));
Mem::wb(NewanimsData::anim_Brightness_w,Mem::ub(j_add(j_add(a1,5),idx)));
}
(d2=M68k::setw(d2,j_add(d2,1)));
if((int16_t(d2) > int16_t(Mem::uw(j_add(j_add(a6,Defs::BulT_AnimFrames_l),2))))) {
(d2=M68k::setw(d2,0));
}
Mem::wb(j_add(a0,Defs::ShotT_Anim_b),d2);
int32_t a2=Mem::l(LevelBss::Lvl_ZonePtrsPtr_l);
(d0=Mem::l(j_add(a2,((d0 & 0xFFFF) * 4))));
Mem::wl(ObjectmoveData::Obj_ZonePtr_l,d0);
int32_t a3=Mem::l(ObjectmoveData::Obj_ZonePtr_l);
Mem::wb(HiresData::PlayEcho,Mem::ub(j_add(a3,Defs::ZoneT_Echo_b)));
if((Mem::b(j_add(a0,Defs::ShotT_InUpperZone_b)) != 0)) {
(a3=j_add(a3,8));
}
(d0=Mem::l(j_add(a3,6)));
(d0=(d0 - Mem::l(j_add(a0,Defs::ShotT_AccYPos_w))));
if((d0 >= (10 * 128))) {
if(((Mem::ub(j_add(j_add(a0,Defs::ShotT_Flags_w),1)) & 1) != 0)) {
Mem::ww(j_add(a0,Defs::ShotT_VelocityY_w),-(int16_t(Mem::uw(j_add(a0,Defs::ShotT_VelocityY_w)))));
int32_t dr=j_add(Mem::l(j_add(a3,6)),(10 * 128));
Mem::wl(j_add(a0,Defs::ShotT_AccYPos_w),dr);
if((Mem::l(j_add(a6,Defs::BulT_Gravity_l)) != 0)) {
Mem::wl(j_add(a0,Defs::ShotT_VelocityX_w),j_shr(Mem::l(j_add(a0,Defs::ShotT_VelocityX_w)),1));
Mem::wl(j_add(a0,Defs::ShotT_VelocityZ_w),j_shr(Mem::l(j_add(a0,Defs::ShotT_VelocityZ_w)),1));
}
}
else {
Mem::wb(j_add(a0,Defs::ShotT_Anim_b),0);
Mem::wb(j_add(a0,Defs::ShotT_Status_b),1);
Newanims::bulletImpactFX(a0,a6,true);
}
}
(d0=Mem::l(j_add(a3,2)));
(d0=(d0 - Mem::l(j_add(a0,Defs::ShotT_AccYPos_w))));
if((d0 <= (10 * 128))) {
bool bouncedUp=false;
if((Mem::l(j_add(a6,Defs::BulT_BounceVert_l)) != 0)) {
if((int16_t(Mem::uw(j_add(a0,Defs::ShotT_VelocityY_w))) >= 0)) {
int32_t dv=M68k::setw(0,Mem::uw(j_add(a0,Defs::ShotT_VelocityY_w)));
(dv=M68k::setw(dv,j_shr(int16_t(dv),1)));
(dv=M68k::setw(dv,-(int16_t(dv))));
Mem::ww(j_add(a0,Defs::ShotT_VelocityY_w),dv);
Mem::wl(j_add(a0,Defs::ShotT_AccYPos_w),(Mem::l(j_add(a3,2)) - (10 * 128)));
if((Mem::l(j_add(a6,Defs::BulT_Gravity_l)) != 0)) {
Mem::wl(j_add(a0,Defs::ShotT_VelocityX_w),j_shr(Mem::l(j_add(a0,Defs::ShotT_VelocityX_w)),1));
Mem::wl(j_add(a0,Defs::ShotT_VelocityZ_w),j_shr(Mem::l(j_add(a0,Defs::ShotT_VelocityZ_w)),1));
}
(bouncedUp=true);
}
else {
(bouncedUp=true);
}
}
if(!(bouncedUp)) {
Mem::wb(j_add(a0,Defs::ShotT_Anim_b),0);
Mem::wb(j_add(a0,Defs::ShotT_Status_b),1);
Newanims::bulletImpactFX(a0,a6,true);
}
}
(a1=Mem::l(LevelBss::Lvl_ObjectPointsPtr_l));
(d1=M68k::setw(0,Mem::uw(a0)));
(a1=j_add(a1,((d1 & 0xFFFF) * 8)));
(d2=Mem::l(a1));
Mem::wl(ObjectmoveData::oldx,d2);
int32_t d3=Mem::l(j_add(a0,Defs::ShotT_VelocityX_w));
int32_t d4=M68k::setw(0,d3);
(d3=M68k::swap(d3));
int32_t d5=M68k::setw(0,Mem::uw(AnimBss::Anim_TempFrames_w));
(d3=M68k::muls(d3,d5));
(d4=M68k::mulu(d4,d5));
(d3=M68k::swap(d3));
(d3=M68k::setw(d3,0));
(d3=j_add(d3,d4));
(d2=j_add(d2,d3));
Mem::wl(ObjectmoveData::newx,d2);
(d2=Mem::l(j_add(a1,4)));
Mem::wl(ObjectmoveData::oldz,d2);
(d3=Mem::l(j_add(a0,Defs::ShotT_VelocityZ_w)));
(d4=M68k::setw(0,d3));
(d3=M68k::swap(d3));
(d3=M68k::muls(d3,d5));
(d4=M68k::mulu(d4,d5));
(d3=M68k::swap(d3));
(d3=M68k::setw(d3,0));
(d3=j_add(d3,d4));
(d2=j_add(d2,d3));
Mem::wl(ObjectmoveData::newz,d2);
Mem::wl(ObjectmoveData::oldy,Mem::l(j_add(a0,Defs::ShotT_AccYPos_w)));
(d3=M68k::muls(Mem::uw(j_add(a0,Defs::ShotT_VelocityY_w)),Mem::uw(AnimBss::Anim_TempFrames_w)));
(d5=Mem::l(j_add(a6,Defs::BulT_Gravity_l)));
if((d5 != 0)) {
(d5=M68k::muls(d5,Mem::uw(AnimBss::Anim_TempFrames_w)));
(d3=j_add(d3,d5));
int32_t d6=M68k::setw(0,Mem::uw(j_add(a0,Defs::ShotT_VelocityY_w)));
(d6=int16_t(d6));
(d6=j_add(d6,d5));
if((d6 >= (10 * 256))) (d6=(10 * 256));
Mem::ww(j_add(a0,Defs::ShotT_VelocityY_w),d6);
}
(d4=Mem::l(j_add(a0,Defs::ShotT_AccYPos_w)));
(d4=j_add(d4,d3));
Mem::wl(j_add(a0,Defs::ShotT_AccYPos_w),d4);
(d4=(d4 - (5 * 128)));
Mem::wl(ObjectmoveData::newy,d4);
(d4=j_add(d4,(5 * 128)));
(d4=j_shr(d4,7));
Mem::ww(j_add(a0,4),d4);
Mem::wb(ObjectmoveData::Obj_WallBounce_b,((Mem::l(j_add(a6,Defs::BulT_BounceHoriz_l)) != 0)?0xFF:0));
Mem::wb(ObjectmoveData::exitfirst,((Mem::l(j_add(a6,Defs::BulT_BounceHoriz_l)) == 0)?0xFF:0));
Mem::wb(NewanimsData::MOVING,0);
Mem::wb(ObjectmoveData::hitwall,0);
Mem::wb(ObjectmoveData::StoodInTop,Mem::ub(j_add(a0,Defs::ShotT_InUpperZone_b)));
Mem::ww(ObjectmoveData::wallflags,0b0000010000000000);
Mem::wl(ObjectmoveData::StepUpVal,0);
Mem::wl(ObjectmoveData::StepDownVal,0x1000000);
Mem::wl(ObjectmoveData::thingheight,(10 * 128));
bool noMove=false;
if((int16_t(Mem::uw(ObjectmoveData::oldx)) == int16_t(Mem::uw(ObjectmoveData::newx)))) {
if((int16_t(Mem::uw(ObjectmoveData::oldz)) == int16_t(Mem::uw(ObjectmoveData::newz)))) {
(noMove=true);
}
}
if(!(noMove)) {
if(!((int16_t(Mem::uw(ObjectmoveData::oldx)) == int16_t(Mem::uw(ObjectmoveData::newx))))) {
}
if((int16_t(Mem::uw(ObjectmoveData::oldx)) == int16_t(Mem::uw(ObjectmoveData::newx)))) {
Mem::ww(ObjectmoveData::WallLength_w,1);
}
Mem::wb(NewanimsData::MOVING,0xFF);
Objectmove::MoveObject();
int32_t db=M68k::setb(0,Mem::ub(NewanimsData::anim_Brightness_w));
if((int8_t(db) != 0)) {
(db=M68k::setw(db,-(int16_t(db))));
int32_t dx=M68k::setw(0,Mem::uw(ObjectmoveData::newx));
int32_t dz=M68k::setw(0,Mem::uw(ObjectmoveData::newz));
Mem::wl(AnimBss::Anim_BrightY_l,Mem::l(ObjectmoveData::newy));
int32_t az=Mem::l(ObjectmoveData::Obj_ZonePtr_l);
int32_t dzone=M68k::setw(0,Mem::uw(az));
Newanims::anim_BrightenPoints(db,dx,dz,dzone);
}
}
Mem::wb(j_add(a0,Defs::ShotT_InUpperZone_b),Mem::ub(ObjectmoveData::StoodInTop));
bool hit=false;
if((Mem::b(ObjectmoveData::Obj_WallBounce_b) != 0)) {
if((Mem::b(ObjectmoveData::hitwall) != 0)) {
int32_t dv=M68k::muls(Mem::uw(j_add(a0,Defs::ShotT_VelocityZ_w)),Mem::uw(ObjectmoveData::WallXSize_w));
int32_t d1b=M68k::muls(Mem::uw(j_add(a0,Defs::ShotT_VelocityX_w)),Mem::uw(ObjectmoveData::WallZSize_w));
(dv=(dv - d1b));
(dv=M68k::divs(dv,Mem::uw(ObjectmoveData::WallLength_w)));
(d1b=M68k::setw(0,Mem::uw(j_add(a0,Defs::ShotT_VelocityX_w))));
int32_t d2b=M68k::setw(0,Mem::uw(ObjectmoveData::WallZSize_w));
(d2b=M68k::setw(d2b,j_add(d2b,d2b)));
(d2b=M68k::muls(d2b,dv));
(d2b=M68k::divs(d2b,Mem::uw(ObjectmoveData::WallLength_w)));
(d1b=M68k::setw(d1b,j_add(d1b,d2b)));
Mem::ww(j_add(a0,Defs::ShotT_VelocityX_w),d1b);
(d1b=M68k::setw(0,Mem::uw(j_add(a0,Defs::ShotT_VelocityZ_w))));
(d2b=M68k::setw(0,Mem::uw(ObjectmoveData::WallXSize_w)));
(d2b=M68k::setw(d2b,j_add(d2b,d2b)));
(d2b=M68k::muls(d2b,dv));
(d2b=M68k::divs(d2b,Mem::uw(ObjectmoveData::WallLength_w)));
(d1b=M68k::setw(d1b,(d1b - d2b)));
Mem::ww(j_add(a0,Defs::ShotT_VelocityZ_w),d1b);
if((Mem::l(j_add(a6,Defs::BulT_Gravity_l)) != 0)) {
Mem::wl(j_add(a0,Defs::ShotT_VelocityX_w),j_shr(Mem::l(j_add(a0,Defs::ShotT_VelocityX_w)),1));
Mem::wl(j_add(a0,Defs::ShotT_VelocityZ_w),j_shr(Mem::l(j_add(a0,Defs::ShotT_VelocityZ_w)),1));
}
}
if((Mem::b(NewanimsData::timeout) != 0)) (hit=true);
}
else {
if((Mem::b(ObjectmoveData::hitwall) != 0)) {
int32_t d4w=Mem::l(ObjectmoveData::wallhitheight);
Mem::wl(j_add(a0,Defs::ShotT_AccYPos_w),d4w);
(d4w=j_shr(d4w,7));
Mem::ww(j_add(a0,4),d4w);
(hit=true);
}
else {
if((Mem::b(NewanimsData::timeout) != 0)) (hit=true);
}
}
if(hit) {
Mem::wb(NewanimsData::timeout,0);
Mem::wb(j_add(a0,Defs::ShotT_Anim_b),0);
Mem::wb(j_add(a0,Defs::ShotT_Status_b),1);
Newanims::bulletImpactFX(a0,a6,true);
}
(a3=Mem::l(ObjectmoveData::Obj_ZonePtr_l));
Mem::ww(j_add(a0,Defs::ObjT_ZoneID_w),Mem::uw(a3));
Mem::ww(j_add(a0,Defs::EntT_ZoneID_w),Mem::uw(a3));
Mem::wl(a1,Mem::l(ObjectmoveData::newx));
Mem::wl(j_add(a1,4),Mem::l(ObjectmoveData::newz));
if((Mem::l(j_add(a0,Defs::EntT_EnemyFlags_l)) == 0)) return ;
(a3=Mem::l(LevelBss::Lvl_ObjectDataPtr_l));
(a1=Mem::l(LevelBss::Lvl_ObjectPointsPtr_l));
(d2=M68k::setw(0,Mem::uw(ObjectmoveData::newx)));
(d2=M68k::setw(d2,(d2 - Mem::uw(ObjectmoveData::oldx))));
Mem::ww(ObjectmoveData::xdiff,d2);
(d1=M68k::setw(0,Mem::uw(ObjectmoveData::newz)));
(d1=M68k::setw(d1,(d1 - Mem::uw(ObjectmoveData::oldz))));
Mem::ww(ObjectmoveData::zdiff,d1);
(d3=M68k::setw(0,d1));
(d4=M68k::setw(0,d2));
(d2=M68k::muls(d2,d2));
(d1=M68k::muls(d1,d1));
(d0=1);
(d2=j_add(d2,d1));
if((d2 != 0)) {
(d0=M68k::setw(0,31));
while(((d2 & j_shl(1,(d0 & 31))) == 0)){
(d0=M68k::setw(d0,(d0 - 1)));
if((int16_t(d0) == -(1))) break;
}
(d0=M68k::setw(d0,j_shr(int16_t(d0),1)));
(d3=j_shl(1,(d0 & 31)));
(d0=d3);
for(int32_t it=0;(it < 3);(it)++){
(d1=M68k::setw(0,d0));
(d1=M68k::muls(d1,d1));
(d1=(d1 - d2));
(d1=j_shr(d1,1));
(d1=M68k::divs(d1,d0));
(d0=M68k::setw(d0,(d0 - d1)));
if(!((int16_t(d0) > 0))) (d0=M68k::setw(d0,1));
}
}
Mem::ww(ObjectmoveData::Range,d0);
(d0=M68k::setw(d0,j_add(d0,80)));
(d0=M68k::muls(d0,d0));
Mem::wl(NewanimsData::sqrnum,d0);
while(true){
if((int16_t(Mem::uw(a3)) < 0)) break;
bool nasty=true;
if((int16_t(Mem::uw(j_add(a3,Defs::ObjT_ZoneID_w))) < 0)) (nasty=false);
else {
int32_t d1c=Mem::ub(j_add(a0,Defs::ShotT_InUpperZone_b));
int32_t d2c=Mem::ub(j_add(a3,Defs::ShotT_InUpperZone_b));
if((((d1c ^ d2c) & 0xFF) != 0)) (nasty=false);
else {
int32_t d1d=Mem::ub(j_add(a3,16));
int32_t d7=Mem::l(j_add(a0,Defs::EntT_EnemyFlags_l));
if(((d7 & j_shl(1,(d1d & 31))) == 0)) (nasty=false);
else {
if((d1d != 1)) {
}
else {
int32_t a4=j_add(Mem::l(HiresData::GLF_DatabasePtr_l),Defs::GLFT_ObjectDefs);
int32_t d1e=Mem::ub(j_add(a3,Defs::EntT_Type_b));
(d1e=M68k::muls(d1e,Defs::ODefT_SizeOf_l));
if((Mem::w(j_add(j_add(a4,(d1e & 0xFFFF)),Defs::ODefT_Behaviour_w)) != 2)) (nasty=false);
}
if((nasty && (Mem::b(j_add(a3,Defs::EntT_HitPoints_b)) == 0))) (nasty=false);
if(nasty) {
int32_t d2h=M68k::setw(0,Mem::uw(j_add(a3,4)));
int32_t d2v=M68k::setw(0,Mem::uw(j_add(a0,4)));
(d2v=M68k::setw(d2v,(d2v - d2h)));
if((int16_t(d2v) < 0)) (d2v=M68k::setw(d2v,-(int16_t(d2v))));
bool ignoreHeight=(Mem::b(NewanimsData::MOVING) == 0);
if((!(ignoreHeight) && (int16_t(d2v) > 50))) (nasty=false);
if(nasty) {
int32_t d1p=M68k::setw(0,Mem::uw(a3));
int32_t dpx=M68k::setw(0,Mem::uw(j_add(a1,((d1p & 0xFFFF) * 8))));
(d4=M68k::setw(0,dpx));
int32_t dpz=M68k::setw(0,Mem::uw(j_add(j_add(a1,((d1p & 0xFFFF) * 8)),4)));
(d5=M68k::setw(0,dpz));
(d4=M68k::setw(d4,(d4 - Mem::uw(ObjectmoveData::newx))));
(dpx=M68k::setw(dpx,(dpx - Mem::uw(ObjectmoveData::oldx))));
int32_t d6=M68k::setw(0,dpx);
(d5=M68k::setw(d5,(d5 - Mem::uw(ObjectmoveData::newz))));
(dpz=M68k::setw(dpz,(dpz - Mem::uw(ObjectmoveData::oldz))));
(d7=M68k::setw(0,dpz));
(d6=M68k::muls(d6,Mem::uw(ObjectmoveData::zdiff)));
(d7=M68k::muls(d7,Mem::uw(ObjectmoveData::xdiff)));
(d6=(d6 - d7));
if((d6 <= 0)) (d6=-(d6));
(d6=M68k::divs(d6,Mem::uw(ObjectmoveData::Range)));
int32_t d7t=M68k::setw(0,80);
if((int8_t(Mem::ub(j_add(a3,16))) > 1)) (d7t=M68k::setw(d7t,40));
if((int16_t(d6) > int16_t(d7t))) (nasty=false);
else {
(dpx=M68k::muls(dpx,dpx));
(dpz=M68k::muls(dpz,dpz));
(dpx=j_add(dpx,dpz));
if((dpx > Mem::l(NewanimsData::sqrnum))) (nasty=false);
else {
(d4=M68k::muls(d4,d4));
(d5=M68k::muls(d5,d5));
(d4=j_add(d4,d5));
if((d4 > Mem::l(NewanimsData::sqrnum))) (nasty=false);
else {
int32_t d6d=Mem::ub(j_add(a0,Defs::ShotT_Power_w));
Mem::wb(j_add(a3,Defs::EntT_DamageTaken_b),j_add(Mem::ub(j_add(a3,Defs::EntT_DamageTaken_b)),d6d));
Mem::ww(j_add(a3,Defs::EntT_ImpactX_w),Mem::uw(j_add(a0,Defs::ShotT_VelocityX_w)));
Mem::ww(j_add(a3,Defs::EntT_ImpactZ_w),Mem::uw(j_add(a0,Defs::ShotT_VelocityZ_w)));
Mem::wb(j_add(a0,Defs::ShotT_Anim_b),0);
Mem::wb(j_add(a0,Defs::ShotT_Status_b),1);
Newanims::bulletImpactFX(a0,a6,false);
return ;
}
}
}
}
}
}
}
}
(a3=j_add(a3,64));
}
}

void bulletImpactFX(int32_t a0,int32_t a6,bool setViewerTop){
int32_t d0=Mem::l(j_add(a6,Defs::BulT_ImpactSFX_l));
(d0=(d0 - 1));
if((d0 >= 0)) {
int32_t a1=TablesBss::ObjRotated_vl;
int32_t d1=M68k::setw(0,Mem::uw(a0));
Mem::wl(HiresData::Aud_NoiseX_w,Mem::l(j_add(a1,((d1 & 0xFFFF) * 8))));
Mem::ww(HiresData::Aud_NoiseVol_w,200);
Mem::ww(HiresData::Aud_SampleNum_w,d0);
Mem::ww(HiresData::IDNUM,d1);
Hires::MakeSomeNoise();
}
int32_t force=Mem::l(j_add(a6,Defs::BulT_ExplosiveForce_l));
if((force != 0)) {
Mem::ww(ObjectmoveData::Viewerx,Mem::uw(ObjectmoveData::newx));
Mem::ww(ObjectmoveData::Viewerz,Mem::uw(ObjectmoveData::newz));
Mem::ww(ObjectmoveData::Viewery,Mem::uw(j_add(a0,4)));
if(setViewerTop) Mem::wb(ObjectmoveData::ViewerTop,Mem::ub(j_add(a0,Defs::ShotT_InUpperZone_b)));
Newanims::ComputeBlast(force,a0);
}
}

int32_t Draw_SkyBackdrop(int32_t a0){
int32_t d0{};
int32_t d1{};
int32_t d2{};
int32_t d3{};
int32_t d4{};
int32_t d5{};
int32_t d6{};
int32_t d7{};
int32_t a1{};
int32_t a2{};
int32_t a3{};
int32_t a4{};
int32_t a5{};
const int32_t entryA0=a0;
(a5=Mem::l(LevelBss::Lvl_ListOfGraphRoomsPtr_l));
(d5=M68k::setw(0,Mem::uw(j_add(a5,Defs::PVST_Zone_w))));
(a5=ZoneBss::Zone_BackdropDisable_vb);
(d3=M68k::setw(0,d5));
(d5=M68k::setw(d5,j_ushr((d5 & 0xFFFF),3)));
(a5=j_add(a5,int16_t(d5)));
if(((Mem::ub(a5) & j_shl(1,(d3 & 7))) != 0)) return a0;
(d5=M68k::setw(0,Mem::uw(NewanimsData::tmpangpos)));
(d5=M68k::setw(d5,(d5 & 4095)));
(d5=M68k::muls(d5,Defs::SKY_BACKDROP_W));
(d5=j_shr(d5,8));
(d5=j_shr(d5,4));
(d5=M68k::muls(d5,Defs::SKY_BACKDROP_H));
if((Mem::b(VidBss::Vid_FullScreen_b) != 0)) {
(a0=Mem::l(VidBss::Vid_FastBufferPtr_l));
(a5=Mem::l(DrawBss::Draw_BackdropImagePtr_l));
(a3=a5);
(a3=j_add(a3,(Defs::SKY_BACKDROP_W * Defs::SKY_BACKDROP_H)));
(a5=j_add(a5,Defs::SKY_BACKDROP_H));
(a1=Mem::l(DrawBss::Draw_BackdropImagePtr_l));
(a1=j_add(a1,d5));
(a1=j_add(a1,Defs::SKY_BACKDROP_H));
(d7=M68k::setw(0,Mem::uw(HireswallData::Vid_CentreY_w)));
(d6=M68k::setw(0,d7));
(a1=(a1 - int16_t(d6)));
(a5=(a5 - int16_t(d6)));
(d7=M68k::setw(d7,j_shr(int16_t(d7),2)));
(d4=M68k::setw(0,(Hires::FS_WIDTH - 1)));
while(true){
(d3=M68k::setw(0,d7));
(a2=a0);
(a4=a1);
while(true){
(d0=Mem::l(a4));
(a4+=4);
Mem::wb(j_add(a2,(Hires::SCREEN_WIDTH * 3)),d0);
(d0=M68k::swap(d0));
Mem::wb(j_add(a2,Hires::SCREEN_WIDTH),d0);
(d0=j_ushr(d0,8));
Mem::wb(a2,d0);
(d0=M68k::swap(d0));
Mem::wb(j_add(a2,(Hires::SCREEN_WIDTH * 2)),d0);
(a2=j_add(a2,(Hires::SCREEN_WIDTH * 4)));
(d3=M68k::setw(d3,(d3 - 1)));
if((int16_t(d3) == -(1))) break;
}
(a1=j_add(a1,Defs::SKY_BACKDROP_H));
if(!((a3 > a1))) (a1=a5);
(a0+=1);
(d4=M68k::setw(d4,(d4 - 1)));
if((int16_t(d4) == -(1))) break;
}
return entryA0;
}
(a0=Mem::l(VidBss::Vid_FastBufferPtr_l));
(a5=Mem::l(DrawBss::Draw_BackdropImagePtr_l));
(a3=a5);
(a3=j_add(a3,(Defs::SKY_BACKDROP_W * Defs::SKY_BACKDROP_H)));
(a5=j_add(a5,Defs::SKY_BACKDROP_H));
(a1=Mem::l(DrawBss::Draw_BackdropImagePtr_l));
(a1=j_add(a1,d5));
(a1=j_add(a1,Defs::SKY_BACKDROP_H));
(d7=M68k::setw(0,Mem::uw(HireswallData::Vid_CentreY_w)));
(d6=M68k::setw(0,d7));
(d5=M68k::setw(0,d6));
(d5=M68k::setw(d5,j_shr(int16_t(d5),1)));
(d6=M68k::setw(d6,j_add(d6,d5)));
(a1=(a1 - int16_t(d6)));
(a5=(a5 - int16_t(d6)));
(d7=M68k::setw(d7,j_shr(int16_t(d7),2)));
(d1=M68k::setw(0,Defs::SKY_BACKDROP_H));
(d2=M68k::setw(0,Defs::SKY_BACKDROP_H));
(d5=M68k::setw(0,(Defs::SKY_BACKDROP_H * 2)));
(d4=M68k::setw(0,191));
while(true){
(d3=M68k::setw(0,d7));
(a2=a0);
(a4=a1);
while(true){
(d0=M68k::setw(0,Mem::uw(a4)));
(a4+=2);
Mem::wb(a2,d0);
(d0=M68k::setb(d0,Mem::ub(a4)));
(a4+=1);
Mem::wb(j_add(a2,Hires::SCREEN_WIDTH),d0);
(a4+=1);
(d0=M68k::setb(d0,Mem::ub(a4)));
(a4+=1);
Mem::wb(j_add(a2,(Hires::SCREEN_WIDTH * 2)),d0);
(d0=M68k::setb(d0,Mem::ub(a4)));
(a4+=1);
Mem::wb(j_add(a2,(Hires::SCREEN_WIDTH * 3)),d0);
(a2=j_add(a2,(Hires::SCREEN_WIDTH * 4)));
(d3=M68k::setw(d3,(d3 - 1)));
if((int16_t(d3) == -(1))) break;
}
(a1=j_add(a1,int16_t(d1)));
if(!((a3 > a1))) (a1=a5);
int32_t t=d1;
(d1=M68k::setw(d1,d2));
(d2=M68k::setw(d2,t));
(t=d2);
(d2=M68k::setw(d2,d5));
(d5=M68k::setw(d5,t));
(a0+=1);
(d4=M68k::setw(d4,(d4 - 1)));
if((int16_t(d4) == -(1))) break;
}
return entryA0;
}

}