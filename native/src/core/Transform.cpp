#include "original.hpp"
namespace Transform {
void RotateLevelPts(){
if((Mem::b(HiresData::draw_RenderMap_b) == 0)) {
Transform::xform_pvs_subset();
return ;
}
int32_t d6=Mem::uw(HireswallData::Vis_SinVal_w);
(d6=M68k::swap(d6));
(d6=M68k::setw(d6,Mem::uw(HireswallData::Vis_CosVal_w)));
int32_t a3=Mem::l(LevelBss::Lvl_PointsPtr_l);
int32_t a1=TablesBss::Rotated_vl;
int32_t a2=TablesBss::OnScreen_vl;
int32_t d4=Mem::w(HiresData::Plr_XOff_l);
int32_t d5=Mem::w(HiresData::Plr_ZOff_l);
int32_t d7=Mem::w(LevelBss::Lvl_NumPoints_w);
if((Mem::b(VidBss::Vid_FullScreen_b) != 0)) {
Transform::xform_all_fs(d4,d5,d6,d7,a1,a2,a3);
return ;
}
int32_t d0{};
int32_t d1{};
int32_t d2{};
int32_t d3{};
do {
(d0=Mem::w(a3));
(a3+=2);
(d0=M68k::setw(d0,(d0 - d4)));
(d2=d0);
(d1=Mem::w(a3));
(a3+=2);
(d1=M68k::setw(d1,(d1 - d5)));
(d2=M68k::muls(d2,d6));
(d6=M68k::swap(d6));
(d3=d1);
(d3=M68k::muls(d3,d6));
(d2-=d3);
(d2>>=8);
(d2+=Mem::l(HiresData::xwobble));
Mem::wl(a1,d2);
(a1+=4);
(d0=M68k::muls(d0,d6));
(d6=M68k::swap(d6));
(d1=M68k::muls(d1,d6));
(d1+=d0);
(d1>>=8);
(d1>>=7);
Mem::wl(a1,d1);
(a1+=4);
if((d1 > 0)) {
(d2=M68k::divs(d2,d1));
(d2=M68k::setw(d2,j_add(d2,Mem::w(HiresData::Vid_CentreX_w))));
}
else if((d2 > 0)) {
(d2=M68k::setw(d2,Mem::uw(HiresData::Vid_RightX_w)));
}
else {
(d2=M68k::setw(d2,0));
}
Mem::ww(a2,d2);
(a2+=2);
}
while((--(d7) != -(1)));
}

void xform_all_fs(int32_t d4,int32_t d5,int32_t d6,int32_t d7,int32_t a1,int32_t a2,int32_t a3){
int32_t d0{};
int32_t d1{};
int32_t d2{};
int32_t d3{};
do {
(d0=Mem::w(a3));
(a3+=2);
(d0=M68k::setw(d0,(d0 - d4)));
(d2=d0);
(d1=Mem::w(a3));
(a3+=2);
(d1=M68k::setw(d1,(d1 - d5)));
(d2=M68k::muls(d2,d6));
(d6=M68k::swap(d6));
(d3=d1);
(d3=M68k::muls(d3,d6));
(d2-=d3);
(d2>>=8);
(d2+=Mem::l(HiresData::xwobble));
Mem::wl(a1,d2);
(a1+=4);
(d0=M68k::muls(d0,d6));
(d6=M68k::swap(d6));
(d1=M68k::muls(d1,d6));
(d1+=d0);
(d1<<=2);
(d1=M68k::swap(d1));
(d1=M68k::muls(d1,1229));
(d1>>=8);
(d1>>=4);
Mem::wl(a1,d1);
(a1+=4);
if((d1 > 0)) {
(d2=M68k::divs(d2,d1));
(d2=M68k::setw(d2,j_add(d2,Mem::w(HiresData::Vid_CentreX_w))));
}
else if((d2 > 0)) {
(d2=M68k::setw(d2,Mem::uw(HiresData::Vid_RightX_w)));
}
else {
(d2=0);
}
Mem::ww(a2,d2);
(a2+=2);
}
while((--(d7) != -(1)));
}

void xform_pvs_subset(){
int32_t d6=Mem::uw(HireswallData::Vis_SinVal_w);
(d6=M68k::swap(d6));
(d6=M68k::setw(d6,Mem::uw(HireswallData::Vis_CosVal_w)));
int32_t a0=Mem::l(LevelBss::PointsToRotatePtr_l);
int32_t a3=Mem::l(LevelBss::Lvl_PointsPtr_l);
int32_t a1=TablesBss::Rotated_vl;
int32_t a2=TablesBss::OnScreen_vl;
int32_t d4=Mem::w(HiresData::Plr_XOff_l);
int32_t d5=Mem::w(HiresData::Plr_ZOff_l);
bool fullScreen=(Mem::b(VidBss::Vid_FullScreen_b) != 0);
int32_t d0{};
int32_t d1{};
int32_t d2{};
int32_t d3{};
int32_t d7{};
while(true){
(d7=Mem::w(a0));
(a0+=2);
if((d7 < 0)) {
if((d7 == ZoneBss::EDGE_POINT_ID_LIST_END)) {
return ;
}
(a0=ZoneBss::Zone_EdgePointIndexes_vw);
continue;
}
(d0=Mem::w(j_add(a3,(d7 * 4))));
(d0=M68k::setw(d0,(d0 - d4)));
(d2=d0);
(d1=Mem::w(j_add(j_add(a3,(d7 * 4)),2)));
(d1=M68k::setw(d1,(d1 - d5)));
(d2=M68k::muls(d2,d6));
(d6=M68k::swap(d6));
(d3=d1);
(d3=M68k::muls(d3,d6));
(d2-=d3);
(d2>>=8);
(d2+=Mem::l(HiresData::xwobble));
Mem::wl(j_add(a1,(d7 * 8)),d2);
(d0=M68k::muls(d0,d6));
(d6=M68k::swap(d6));
(d1=M68k::muls(d1,d6));
(d1+=d0);
if(!(fullScreen)) {
(d1>>=8);
(d1>>=7);
}
else {
(d1<<=2);
(d1=M68k::swap(d1));
(d1=M68k::muls(d1,1229));
(d1>>=8);
(d1>>=4);
}
Mem::wl(j_add(j_add(a1,(d7 * 8)),4),d1);
if((d1 > 0)) {
(d2=M68k::divs(d2,d1));
(d2=M68k::setw(d2,j_add(d2,Mem::w(HiresData::Vid_CentreX_w))));
}
else if((d2 > 0)) {
(d2=M68k::setw(d2,Mem::uw(HiresData::Vid_RightX_w)));
}
else {
(d2=M68k::setw(d2,0));
}
Mem::ww(j_add(a2,(d7 * 2)),d2);
}
}

void CalcPLR1InLine(){
int32_t d5=Mem::uw(PlayerBss::Plr1_SinVal_w);
int32_t d6=Mem::uw(PlayerBss::Plr1_CosVal_w);
int32_t a4=Mem::l(LevelBss::Lvl_ObjectDataPtr_l);
int32_t a0=Mem::l(LevelBss::Lvl_ObjectPointsPtr_l);
int32_t d7=Mem::w(LevelBss::Lvl_NumObjectPoints_w);
int32_t a2=PlayerBss::Plr1_ObsInLine_vb;
int32_t a3=PlayerBss::Plr1_ObjectDistances_vw;
int32_t d0{};
int32_t d1{};
int32_t d2{};
int32_t d3{};
while(true){
if((Mem::ub(j_add(a4,Defs::ObjT_TypeID_b)) == Defs::OBJ_TYPE_AUX)) {
(a4+=Defs::ObjT_SizeOf_l);
continue;
}
(d0=Mem::w(a0));
(d0=M68k::setw(d0,(d0 - Mem::w(PlayerBss::Plr1_XOff_l))));
(d1=Mem::w(j_add(a0,4)));
(a0+=8);
if((Mem::w(j_add(a4,Defs::ObjT_ZoneID_w)) < 0)) {
Mem::wb(a2,0);
(a2+=1);
Mem::ww(a3,0);
(a3+=2);
(a4+=Defs::ObjT_SizeOf_l);
if((--(d7) == -(1))) {
return ;
}
continue;
}
(d2=Mem::ub(j_add(a4,Defs::ObjT_TypeID_b)));
(d1=M68k::setw(d1,(d1 - Mem::w(PlayerBss::Plr1_ZOff_l))));
(d2=M68k::setw(d2,d0));
(d2=M68k::muls(d2,d6));
(d3=d1);
(d3=M68k::muls(d3,d5));
(d2-=d3);
(d2+=d2);
if((d2 <= 0)) {
(d2=-(d2));
}
(d2=M68k::swap(d2));
(d0=M68k::muls(d0,d5));
(d1=M68k::muls(d1,d6));
(d1+=d0);
(d1<<=2);
(d1=M68k::swap(d1));
(d3=0);
if((int16_t(d1) > 0)) {
(d2=M68k::setw(d2,j_shr(int16_t(d2),1)));
if((int16_t(d2) <= 80)) {
(d3=((d3 & ~(0xFF)) | 0xFF));
}
}
Mem::wb(a2,d3);
(a2+=1);
Mem::ww(a3,d1);
(a3+=2);
(a4+=Defs::ObjT_SizeOf_l);
if((--(d7) == -(1))) {
return ;
}
}
}

void CalcPLR2InLine(int32_t a6){
int32_t d5=Mem::uw(PlayerBss::Plr2_SinVal_w);
int32_t d6=Mem::uw(PlayerBss::Plr2_CosVal_w);
int32_t a4=Mem::l(LevelBss::Lvl_ObjectDataPtr_l);
int32_t a0=Mem::l(LevelBss::Lvl_ObjectPointsPtr_l);
int32_t d7=Mem::w(LevelBss::Lvl_NumObjectPoints_w);
int32_t a2=PlayerBss::Plr2_ObsInLine_vb;
int32_t a3=PlayerBss::Plr2_ObjectDistances_vw;
int32_t d0{};
int32_t d1{};
int32_t d2{};
int32_t d3{};
while(true){
if((Mem::ub(j_add(a4,Defs::ObjT_TypeID_b)) == Defs::OBJ_TYPE_AUX)) {
(a4+=Defs::ObjT_SizeOf_l);
continue;
}
(d0=Mem::w(a0));
(d0=M68k::setw(d0,(d0 - Mem::w(PlayerBss::Plr2_XOff_l))));
(d1=Mem::w(j_add(a0,4)));
(a0+=8);
if((Mem::w(j_add(a4,Defs::ObjT_ZoneID_w)) < 0)) {
Mem::ww(a3,0);
(a3+=2);
Mem::wb(a2,0);
(a2+=1);
(a4+=Defs::ObjT_SizeOf_l);
if((--(d7) == -(1))) {
return ;
}
continue;
}
(d2=Mem::ub(j_add(a4,Defs::ObjT_TypeID_b)));
(d1=M68k::setw(d1,(d1 - Mem::w(PlayerBss::Plr2_ZOff_l))));
(d2=M68k::setw(d2,d0));
(d2=M68k::muls(d2,d6));
(d3=d1);
(d3=M68k::muls(d3,d5));
(d2-=d3);
(d2+=d2);
if((d2 <= 0)) {
(d2=-(d2));
}
(d2=M68k::swap(d2));
(d0=M68k::muls(d0,d5));
(d1=M68k::muls(d1,d6));
(d1+=d0);
(d1<<=2);
(d1=M68k::swap(d1));
(d3=0);
if((int16_t(d1) > 0)) {
(d2=M68k::setw(d2,j_shr(int16_t(d2),1)));
if((int16_t(d2) <= Mem::w(a6))) {
(d3=((d3 & ~(0xFF)) | 0xFF));
}
}
Mem::wb(a2,d3);
(a2+=1);
Mem::ww(a3,d1);
(a3+=2);
(a4+=Defs::ObjT_SizeOf_l);
if((--(d7) == -(1))) {
return ;
}
}
}

void RotateObjectPts(){
int32_t d5=Mem::uw(HireswallData::Vis_SinVal_w);
int32_t d6=Mem::uw(HireswallData::Vis_CosVal_w);
int32_t a4=Mem::l(LevelBss::Lvl_ObjectDataPtr_l);
int32_t a0=Mem::l(LevelBss::Lvl_ObjectPointsPtr_l);
int32_t d7=Mem::w(LevelBss::Lvl_NumObjectPoints_w);
int32_t a1=TablesBss::ObjRotated_vl;
if((Mem::b(VidBss::Vid_FullScreen_b) != 0)) {
Transform::RotateObjectPtsFullScreen(d5,d6,d7,a0,a1,a4);
return ;
}
int32_t d0{};
int32_t d1{};
int32_t d2{};
int32_t d3{};
while(true){
if((Mem::ub(j_add(a4,Defs::ObjT_TypeID_b)) == Defs::OBJ_TYPE_AUX)) {
(a4+=Defs::ObjT_SizeOf_l);
continue;
}
(d0=Mem::w(a0));
(d0=M68k::setw(d0,(d0 - Mem::w(HiresData::Plr_XOff_l))));
(d1=Mem::w(j_add(a0,4)));
(a0+=8);
if((Mem::w(j_add(a4,Defs::ObjT_ZoneID_w)) < 0)) {
Mem::wl(a1,0);
(a1+=4);
Mem::wl(a1,0);
(a1+=4);
(a4+=Defs::ObjT_SizeOf_l);
if((--(d7) == -(1))) {
return ;
}
continue;
}
(d1=M68k::setw(d1,(d1 - Mem::w(HiresData::Plr_ZOff_l))));
(d2=d0);
(d2=M68k::muls(d2,d6));
(d3=d1);
(d3=M68k::muls(d3,d5));
(d2-=d3);
(d2+=d2);
(d2=M68k::swap(d2));
Mem::ww(a1,d2);
(a1+=2);
(d0=M68k::muls(d0,d5));
(d1=M68k::muls(d1,d6));
(d1+=d0);
(d1+=d1);
(d1=M68k::swap(d1));
(d3=0);
Mem::ww(a1,d1);
(a1+=2);
(d2=int16_t(d2));
(d2<<=7);
(d2+=Mem::l(HiresData::xwobble));
Mem::wl(a1,d2);
(a1+=4);
if((--(d7) == -(1))) {
return ;
}
}
}

void RotateObjectPtsFullScreen(int32_t d5,int32_t d6,int32_t d7,int32_t a0,int32_t a1,int32_t a4){
int32_t d0{};
int32_t d1{};
int32_t d2{};
int32_t d3{};
while(true){
if((Mem::ub(j_add(a4,Defs::ObjT_TypeID_b)) == Defs::OBJ_TYPE_AUX)) {
(a4+=Defs::ObjT_SizeOf_l);
continue;
}
(d0=Mem::w(a0));
(d0=M68k::setw(d0,(d0 - Mem::w(HiresData::Plr_XOff_l))));
(d1=Mem::w(j_add(a0,4)));
(a0+=8);
if((Mem::w(j_add(a4,Defs::ObjT_ZoneID_w)) < 0)) {
Mem::wl(a1,0);
(a1+=4);
Mem::wl(a1,0);
(a1+=4);
(a4+=Defs::ObjT_SizeOf_l);
if((--(d7) == -(1))) {
return ;
}
continue;
}
(d1=M68k::setw(d1,(d1 - Mem::w(HiresData::Plr_ZOff_l))));
(d2=d0);
(d2=M68k::muls(d2,d6));
(d3=d1);
(d3=M68k::muls(d3,d5));
(d2-=d3);
(d0=M68k::muls(d0,d5));
(d2+=d2);
(d2=M68k::swap(d2));
Mem::ww(a1,d2);
(a1+=2);
(d1=M68k::muls(d1,d6));
(d1+=d0);
(d1<<=2);
(d1=M68k::swap(d1));
(d1=int16_t(d1));
(d1=M68k::muls(d1,85));
(d3=Mem::l(HiresData::xwobble));
(d1>>=8);
Mem::ww(a1,d1);
(a1+=2);
(d2=int16_t(d2));
(d2<<=7);
(d2+=d3);
Mem::wl(a1,d2);
(a1+=4);
(d2-=d3);
(a4+=Defs::ObjT_SizeOf_l);
if((--(d7) == -(1))) {
return ;
}
}
}

}