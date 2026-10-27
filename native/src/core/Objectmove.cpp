#include "original.hpp"
namespace Objectmove {
void MoveObject(){
Mem::wl(ObjectmoveData::obj_ZoneBackupPtr_l,Mem::l(ObjectmoveData::Obj_ZonePtr_l));
Mem::ww(ObjectmoveData::obj_QuitLimit_w,50);
Mem::wl(ObjectmoveData::obj_RoomPathPtr_l,TablesBss::Obj_RoomPath_vw);
Mem::wb(ObjectmoveData::hitwall,0);
int32_t d0=Mem::uw(ObjectmoveData::newx);
(d0=M68k::setw(d0,(d0 - Mem::uw(ObjectmoveData::oldx))));
Mem::ww(ObjectmoveData::xdiff,d0);
(d0=Mem::uw(ObjectmoveData::newz));
(d0=M68k::setw(d0,(d0 - Mem::uw(ObjectmoveData::oldz))));
Mem::ww(ObjectmoveData::zdiff,d0);
if(((Mem::w(ObjectmoveData::xdiff) == 0) && (Mem::w(ObjectmoveData::zdiff) == 0))) {
return ;
}
Mem::wl(ObjectmoveData::wallhitheight,Mem::l(ObjectmoveData::newy));
int32_t a0=Mem::l(ObjectmoveData::Obj_ZonePtr_l);
int32_t a5{};
while(true){
{
(a5=a0);
(a0=j_add(a0,Mem::w(j_add(a5,Defs::ZoneT_EdgeListOffset_w))));
Mem::wl(HiresData::test,a0);
int32_t a1=Mem::l(LevelBss::Lvl_ZoneEdgePtr_l);
int32_t d1{};
int32_t d2{};
int32_t d3{};
int32_t d4{};
int32_t d5{};
int32_t d6{};
int32_t d7{};
int32_t a2{};
int32_t a4{};
int32_t a6{};
while(true){
{
(d0=Mem::w(a0));
(a0+=2);
if((d0 < 0)) {
break;
}
(d0=M68k::setw(d0,j_shl(d0,4)));
(a2=j_add(a1,int16_t(d0)));
(d0=int32_t(0xFF000000u));
Mem::wl(ObjectmoveData::LowerRoofHeight,d0);
Mem::wl(ObjectmoveData::UpperRoofHeight,d0);
Mem::wl(ObjectmoveData::LowerFloorHeight,d0);
Mem::wl(ObjectmoveData::UpperFloorHeight,d0);
(d1=0);
(d1=M68k::setw(d1,Mem::uw(j_add(a2,Defs::EdgeT_JoinZone_w))));
if((int16_t(d1) >= 0)) {
int32_t a4z=Mem::l(LevelBss::Lvl_ZonePtrsPtr_l);
(a4z=Mem::l(j_add(a4z,(int16_t(d1) * 4))));
(d1=Mem::l(j_add(a4z,Defs::ZoneT_Floor_l)));
Mem::wl(ObjectmoveData::LowerFloorHeight,d1);
(d2=Mem::l(j_add(a4z,Defs::ZoneT_Roof_l)));
Mem::wl(ObjectmoveData::LowerRoofHeight,d2);
(d1=Mem::l(j_add(a4z,Defs::ZoneT_UpperFloor_l)));
Mem::wl(ObjectmoveData::UpperFloorHeight,d1);
(d2=Mem::l(j_add(a4z,Defs::ZoneT_UpperRoof_l)));
(d1-=d2);
Mem::wl(ObjectmoveData::UpperRoofHeight,d2);
}
(a4=0);
(a6=0);
(d3=Mem::b(ObjectmoveData::Obj_AwayFromWall_b));
if((int8_t(d3) >= 0)) {
(d2=Mem::b(j_add(a2,Defs::EdgeT_Byte_12)));
(d4=Mem::b(j_add(a2,Defs::EdgeT_Byte_13)));
if((int8_t(d3) != 0)) {
(d2=M68k::setw(d2,j_shl(d2,(d3 & 63))));
(d4=M68k::setw(d4,j_shl(d4,(d3 & 63))));
}
(a4=int16_t(d2));
(a6=int16_t(d4));
}
(d0=Mem::uw(ObjectmoveData::newx));
(d1=Mem::uw(ObjectmoveData::newz));
(d0=M68k::setw(d0,(d0 - Mem::uw(a2))));
(d1=M68k::setw(d1,(d1 - Mem::uw(j_add(a2,Defs::EdgeT_ZPos_w)))));
(d0=M68k::setw(d0,(d0 - a4)));
(d1=M68k::setw(d1,(d1 - a6)));
(d2=Mem::uw(j_add(a2,Defs::EdgeT_XLen_w)));
(d2=M68k::setw(d2,(d2 - a4)));
(d2=M68k::setw(d2,(d2 - a6)));
(d1=M68k::muls(d1,d2));
(d5=Mem::uw(j_add(a2,Defs::EdgeT_ZLen_w)));
(d5=M68k::setw(d5,j_add(d5,a4)));
(d5=M68k::setw(d5,(d5 - a6)));
(d0=M68k::muls(d0,d5));
(d0-=d1);
if((d0 > 0)) {
(d3=Mem::uw(j_add(a2,Defs::EdgeT_Word_5)));
(d3=M68k::setw(d3,j_add(d3,Mem::uw(ObjectmoveData::Obj_ExtLen_w))));
(d0=M68k::divs(d0,d3));
if((int16_t(d0) < 32)) {
Mem::ww(j_add(a2,Defs::EdgeT_Flags_w),(Mem::uw(j_add(a2,Defs::EdgeT_Flags_w)) | Mem::uw(ObjectmoveData::wallflags)));
}
continue;
}
(d7=d0);
(d3=Mem::uw(j_add(a2,Defs::EdgeT_Word_5)));
(d3=M68k::setw(d3,j_add(d3,Mem::uw(ObjectmoveData::Obj_ExtLen_w))));
(d7=M68k::divs(d7,d3));
(d4=Mem::l(ObjectmoveData::newy));
(d4-=Mem::l(ObjectmoveData::oldy));
(d0=Mem::uw(ObjectmoveData::oldx));
(d1=Mem::uw(ObjectmoveData::oldz));
(d0=M68k::setw(d0,(d0 - Mem::uw(a2))));
(d1=M68k::setw(d1,(d1 - Mem::uw(j_add(a2,Defs::EdgeT_ZPos_w)))));
(d0=M68k::setw(d0,(d0 - a4)));
(d1=M68k::setw(d1,(d1 - a6)));
(d1=M68k::muls(d1,d2));
(d0=M68k::muls(d0,d5));
(d0-=d1);
(d0=M68k::divs(d0,d3));
(d0=M68k::setw(d0,(d0 - d7)));
if((int16_t(d0) <= 0)) {
(d0=1);
}
(d1=d4);
if((d1 != 0)) {
(d1=M68k::divs(d1,d0));
(d1=M68k::muls(d1,d7));
}
(d1+=Mem::l(ObjectmoveData::newy));
(d6=d1);
(d6+=Mem::l(ObjectmoveData::thingheight));
(d6-=Mem::l(ObjectmoveData::StepUpVal));
bool yeshit{};
if((d6 >= Mem::l(ObjectmoveData::LowerFloorHeight))) {
(yeshit=true);
}
else if((d1 > Mem::l(ObjectmoveData::LowerRoofHeight))) {
continue;
}
else if((d1 < Mem::l(ObjectmoveData::UpperRoofHeight))) {
(yeshit=true);
}
else if((d6 < Mem::l(ObjectmoveData::UpperFloorHeight))) {
continue;
}
else {
(yeshit=true);
}
Mem::wl(ObjectmoveData::wallhitheight,d1);
bool calcwherehit{};
if((Mem::b(ObjectmoveData::Obj_WallBounce_b) != 0)) {
Mem::ww(ObjectmoveData::WallXSize_w,d2);
Mem::ww(ObjectmoveData::WallZSize_w,d5);
Mem::ww(ObjectmoveData::WallLength_w,d3);
(calcwherehit=true);
}
else {
(calcwherehit=(Mem::b(ObjectmoveData::exitfirst) != 0));
}
if(calcwherehit) {
(d6=Mem::uw(ObjectmoveData::newx));
(d6=M68k::setw(d6,(d6 - Mem::uw(ObjectmoveData::oldx))));
(d6=M68k::muls(d6,d7));
(d6=M68k::divs(d6,d0));
(d6=M68k::setw(d6,j_add(d6,Mem::uw(ObjectmoveData::newx))));
(d1=Mem::uw(ObjectmoveData::newz));
(d1=M68k::setw(d1,(d1 - Mem::uw(ObjectmoveData::oldz))));
(d1=M68k::muls(d1,d7));
(d1=M68k::divs(d1,d0));
(d1=M68k::setw(d1,j_add(d1,Mem::uw(ObjectmoveData::newz))));
(d0=M68k::setw(d0,d6));
(d7=M68k::setw(d7,d1));
(d6=Mem::uw(ObjectmoveData::newx));
(d7=M68k::setw(d7,Mem::uw(ObjectmoveData::newz)));
(d6=M68k::setw(d6,(d6 - Mem::uw(ObjectmoveData::oldx))));
(d7=M68k::setw(d7,(d7 - Mem::uw(ObjectmoveData::oldz))));
(d4=Mem::uw(a2));
(d4=M68k::setw(d4,j_add(d4,a4)));
(d4=M68k::setw(d4,(d4 - Mem::uw(ObjectmoveData::oldx))));
(d7=M68k::muls(d7,d4));
(d4=Mem::uw(j_add(a2,Defs::EdgeT_ZPos_w)));
(d4=M68k::setw(d4,j_add(d4,a6)));
(d4=M68k::setw(d4,(d4 - Mem::uw(ObjectmoveData::oldz))));
(d6=M68k::muls(d6,d4));
(d7-=d6);
if((d7 > 0)) {
continue;
}
(d6=Mem::uw(ObjectmoveData::newx));
(d7=M68k::setw(d7,Mem::uw(ObjectmoveData::newz)));
(d6=M68k::setw(d6,(d6 - Mem::uw(ObjectmoveData::oldx))));
(d7=M68k::setw(d7,(d7 - Mem::uw(ObjectmoveData::oldz))));
(d4=Mem::uw(a2));
(d4=M68k::setw(d4,j_add(d4,a4)));
(d4=M68k::setw(d4,j_add(d4,d2)));
(d4=M68k::setw(d4,(d4 - Mem::uw(ObjectmoveData::oldx))));
(d7=M68k::muls(d7,d4));
(d4=Mem::uw(j_add(a2,Defs::EdgeT_ZPos_w)));
(d4=M68k::setw(d4,j_add(d4,a6)));
(d4=M68k::setw(d4,j_add(d4,d5)));
(d4=M68k::setw(d4,(d4 - Mem::uw(ObjectmoveData::oldz))));
(d6=M68k::muls(d6,d4));
(d7-=d6);
if((d7 < 0)) {
continue;
}
}
else {
(d6=M68k::setw(0,d7));
(d6=M68k::muls(d6,d5));
(d7=M68k::muls(d7,d2));
(d6=M68k::divs(d6,d3));
(d7=M68k::divs(d7,d3));
(d6=M68k::setw(d6,-(int16_t(d6))));
(d6=M68k::setw(d6,j_add(d6,Mem::uw(ObjectmoveData::newx))));
(d7=M68k::setw(d7,j_add(d7,Mem::uw(ObjectmoveData::newz))));
(d0=M68k::setw(d0,d6));
(d1=M68k::setw(d1,d7));
(d6=M68k::setw(d6,(d6 - Mem::uw(a2))));
(d7=M68k::setw(d7,(d7 - Mem::uw(j_add(a2,Defs::EdgeT_ZPos_w)))));
(d6=M68k::setw(d6,(d6 - a4)));
(d7=M68k::setw(d7,(d7 - a6)));
(d4=M68k::setw(0,d2));
if((int16_t(d4) < 0)) {
(d4=M68k::setw(d4,-(int16_t(d4))));
}
(d3=M68k::setw(d3,d5));
if((int16_t(d3) < 0)) {
(d3=M68k::setw(d3,-(int16_t(d3))));
}
if((int16_t(d3) > int16_t(d4))) {
if((int16_t(d7) <= 0)) {
(d6=M68k::setw(d6,d5));
if((int16_t(d6) > 4)) {
continue;
}
(d6=M68k::setw(d6,(d6 - 4)));
if((int16_t(d7) < int16_t(d6))) {
continue;
}
}
else {
(d6=M68k::setw(d6,d5));
if((int16_t(d6) < -(4))) {
continue;
}
(d6=M68k::setw(d6,j_add(d6,4)));
if((int16_t(d7) > int16_t(d6))) {
continue;
}
}
}
else {
if((int16_t(d6) <= 0)) {
(d7=M68k::setw(d7,d2));
if((int16_t(d7) > 4)) {
continue;
}
(d7=M68k::setw(d7,(d7 - 4)));
if((int16_t(d6) < int16_t(d7))) {
continue;
}
}
else {
(d7=M68k::setw(d7,d2));
if((int16_t(d7) < -(4))) {
continue;
}
(d7=M68k::setw(d7,j_add(d7,4)));
if((int16_t(d6) > int16_t(d7))) {
continue;
}
}
}
}
Mem::ww(ObjectmoveData::newx,d0);
Mem::ww(ObjectmoveData::newz,d1);
Mem::ww(j_add(a2,Defs::EdgeT_Flags_w),(Mem::uw(j_add(a2,Defs::EdgeT_Flags_w)) | Mem::uw(ObjectmoveData::wallflags)));
Mem::wb(ObjectmoveData::hitwall,0xFF);
if((Mem::b(ObjectmoveData::exitfirst) != 0)) {
int32_t rp=Mem::l(ObjectmoveData::obj_RoomPathPtr_l);
Mem::ww(rp,-(1));
return ;
}
}

checkwalls_continue:;
}
checkwalls_end:;
if((Mem::uw(ObjectmoveData::Obj_ExtLen_w) != 0)) {
if(((Mem::w(ObjectmoveData::xdiff) == 0) && (Mem::w(ObjectmoveData::zdiff) == 0))) {
int32_t rp=Mem::l(ObjectmoveData::obj_RoomPathPtr_l);
Mem::ww(rp,-(1));
return ;
}
(a0=j_add(a5,Mem::w(j_add(a5,Defs::ZoneT_EdgeListOffset_w))));
while(true){
{
(d0=Mem::w(a0));
(a0+=2);
if((d0 < 0)) {
if((d0 == -(2))) {
break;
}
continue;
}
(d0=M68k::setw(d0,j_shl(d0,4)));
(a2=j_add(a1,int16_t(d0)));
(d1=0);
(d1=M68k::setw(d1,Mem::uw(j_add(a2,Defs::EdgeT_JoinZone_w))));
if((int16_t(d1) >= 0)) {
int32_t a4z=Mem::l(LevelBss::Lvl_ZonePtrsPtr_l);
(a4z=Mem::l(j_add(a4z,(int16_t(d1) * 4))));
(d1=Mem::l(j_add(a4z,Defs::ZoneT_Floor_l)));
(d1-=Mem::l(j_add(a4z,Defs::ZoneT_Roof_l)));
bool wall1=false;
if((d1 > Mem::l(ObjectmoveData::thingheight))) {
(d0=Mem::l(ObjectmoveData::newy));
(d1=d0);
(d1+=Mem::l(ObjectmoveData::thingheight));
(d1-=Mem::l(j_add(a4z,Defs::ZoneT_Floor_l)));
bool botinside{};
if((d1 > 0)) {
(botinside=(d1 < Mem::l(ObjectmoveData::StepUpVal)));
}
else {
(d1=-(d1));
(botinside=(d1 < Mem::l(ObjectmoveData::StepDownVal)));
}
if(botinside) {
(d0-=Mem::l(j_add(a4z,Defs::ZoneT_Roof_l)));
if((d0 >= 0)) {
continue;
}
}
}
(d1=Mem::l(j_add(a4z,Defs::ZoneT_UpperFloor_l)));
(d1-=Mem::l(j_add(a4z,Defs::ZoneT_UpperRoof_l)));
if((d1 > Mem::l(ObjectmoveData::thingheight))) {
(d0=Mem::l(ObjectmoveData::newy));
(d1=d0);
(d1+=Mem::l(ObjectmoveData::thingheight));
(d1-=Mem::l(j_add(a4z,Defs::ZoneT_UpperFloor_l)));
bool botinside{};
if((d1 > 0)) {
(botinside=(d1 < Mem::l(ObjectmoveData::StepUpVal)));
}
else {
(d1=-(d1));
(botinside=(d1 < Mem::l(ObjectmoveData::StepDownVal)));
}
if(botinside) {
(d0-=Mem::l(j_add(a4z,Defs::ZoneT_UpperRoof_l)));
if((d0 >= 0)) {
continue;
}
}
}
}
(a4=0);
(a6=0);
(d3=Mem::b(ObjectmoveData::Obj_AwayFromWall_b));
if((int8_t(d3) >= 0)) {
(d2=Mem::b(j_add(a2,Defs::EdgeT_Byte_12)));
(d4=Mem::b(j_add(a2,Defs::EdgeT_Byte_13)));
if((int8_t(d3) != 0)) {
(d2=M68k::setw(d2,j_shl(d2,(d3 & 63))));
(d4=M68k::setw(d4,j_shl(d4,(d3 & 63))));
}
(a4=int16_t(d2));
(a6=int16_t(d4));
}
(d2=Mem::uw(j_add(a2,Defs::EdgeT_XLen_w)));
(d2=M68k::setw(d2,(d2 - a4)));
(d2=M68k::setw(d2,(d2 - a6)));
Mem::ww(ObjectmoveData::deltax,d2);
(d5=Mem::uw(j_add(a2,Defs::EdgeT_ZLen_w)));
(d5=M68k::setw(d5,j_add(d5,a4)));
(d5=M68k::setw(d5,(d5 - a6)));
(d0=Mem::uw(ObjectmoveData::newx));
(d1=Mem::uw(ObjectmoveData::newz));
(d0=M68k::setw(d0,(d0 - Mem::uw(a2))));
(d1=M68k::setw(d1,(d1 - Mem::uw(j_add(a2,Defs::EdgeT_ZPos_w)))));
(d0=M68k::setw(d0,(d0 - a4)));
(d1=M68k::setw(d1,(d1 - a6)));
(d1=M68k::muls(d1,Mem::w(ObjectmoveData::deltax)));
(d0=M68k::muls(d0,d5));
(d0-=d1);
if((d0 >= 0)) {
continue;
}
(d7=d0);
(d1=Mem::uw(ObjectmoveData::oldx));
(d3=Mem::uw(ObjectmoveData::newx));
(d3=M68k::setw(d3,(d3 - d1)));
(d1=M68k::setw(d1,(d1 - Mem::uw(a2))));
(d1=M68k::setw(d1,(d1 - a4)));
(d2=Mem::uw(j_add(a2,Defs::EdgeT_ZPos_w)));
(d2=M68k::setw(d2,j_add(d2,a6)));
(d2=M68k::setw(d2,(d2 - Mem::uw(ObjectmoveData::oldz))));
(d4=Mem::uw(ObjectmoveData::newz));
(d4=M68k::setw(d4,(d4 - Mem::uw(ObjectmoveData::oldz))));
(d1=M68k::muls(d1,d4));
(d2=M68k::muls(d2,d3));
(d1+=d2);
(d4=M68k::muls(d4,Mem::w(ObjectmoveData::deltax)));
(d3=M68k::muls(d3,d5));
(d4-=d3);
if((d4 == 0)) {
continue;
}
if((d4 > 0)) {
if((d1 < 0)) {
continue;
}
if((d4 < d1)) {
continue;
}
}
else {
if((d1 > 0)) {
continue;
}
if((d4 > d1)) {
continue;
}
}
(d0=Mem::uw(j_add(a2,Defs::EdgeT_Word_5)));
(d0=M68k::setw(d0,j_add(d0,Mem::uw(ObjectmoveData::Obj_ExtLen_w))));
(d7=M68k::divs(d7,d0));
(d7=M68k::setw(d7,(d7 - 3)));
(d6=M68k::setw(0,d7));
(d6=M68k::muls(d6,d5));
(d7=M68k::muls(d7,Mem::w(ObjectmoveData::deltax)));
(d6=M68k::divs(d6,d0));
(d7=M68k::divs(d7,d0));
(d6=M68k::setw(d6,-(int16_t(d6))));
(d6=M68k::setw(d6,j_add(d6,Mem::uw(ObjectmoveData::newx))));
(d7=M68k::setw(d7,j_add(d7,Mem::uw(ObjectmoveData::newz))));
(d0=Mem::uw(ObjectmoveData::oldx));
(d1=Mem::uw(ObjectmoveData::oldz));
(d0=M68k::setw(d0,(d0 - Mem::uw(a2))));
(d1=M68k::setw(d1,(d1 - Mem::uw(j_add(a2,Defs::EdgeT_ZPos_w)))));
(d0=M68k::setw(d0,(d0 - a4)));
(d1=M68k::setw(d1,(d1 - a6)));
(d1=M68k::muls(d1,Mem::w(ObjectmoveData::deltax)));
(d0=M68k::muls(d0,d5));
(d0-=d1);
if((d0 < 0)) {
continue;
}
(d0=M68k::setw(d0,d6));
(d1=M68k::setw(d1,d7));
Mem::ww(ObjectmoveData::newx,d0);
Mem::ww(ObjectmoveData::newz,d1);
Mem::ww(j_add(a2,Defs::EdgeT_Flags_w),(Mem::uw(j_add(a2,Defs::EdgeT_Flags_w)) | Mem::uw(ObjectmoveData::wallflags)));
Mem::wb(ObjectmoveData::hitwall,0xFF);
if((Mem::b(ObjectmoveData::exitfirst) != 0)) {
int32_t rp=Mem::l(ObjectmoveData::obj_RoomPathPtr_l);
Mem::ww(rp,-(1));
return ;
}
}

checkotherwalls_continue:;
}
checkotherwalls_end:;
}
(a0=j_add(a5,Mem::w(j_add(a5,Defs::ZoneT_EdgeListOffset_w))));
(a1=Mem::l(LevelBss::Lvl_ZoneEdgePtr_l));
while(true){
(d0=Mem::w(a0));
(a0+=2);
if((d0 < 0)) {
Mem::wl(ObjectmoveData::Obj_ZonePtr_l,a5);
int32_t rp=Mem::l(ObjectmoveData::obj_RoomPathPtr_l);
Mem::ww(rp,-(1));
return ;
}
(d0=M68k::setw(d0,j_shl(d0,4)));
(a2=j_add(a1,int16_t(d0)));
if((Mem::w(j_add(a2,Defs::EdgeT_JoinZone_w)) < 0)) {
continue;
}
(d1=0);
(d1=M68k::setw(d1,Mem::uw(j_add(a2,Defs::EdgeT_JoinZone_w))));
int32_t a4z=Mem::l(LevelBss::Lvl_ZonePtrsPtr_l);
(a4z=Mem::l(j_add(a4z,(int16_t(d1) * 4))));
Mem::wl(ObjectmoveData::LowerRoofHeight,Mem::l(j_add(a4z,Defs::ZoneT_Roof_l)));
(d0=Mem::uw(ObjectmoveData::newx));
(d1=Mem::uw(ObjectmoveData::newz));
(d0=M68k::setw(d0,(d0 - Mem::uw(a2))));
(d1=M68k::setw(d1,(d1 - Mem::uw(j_add(a2,Defs::EdgeT_ZPos_w)))));
(d1=M68k::muls(d1,Mem::w(j_add(a2,Defs::EdgeT_XLen_w))));
(d0=M68k::muls(d0,Mem::w(j_add(a2,Defs::EdgeT_ZLen_w))));
(d3=0);
(d3=M68k::setw(d3,Mem::uw(j_add(a2,Defs::EdgeT_JoinZone_w))));
int32_t a3=Mem::l(LevelBss::Lvl_ZonePtrsPtr_l);
(a3=Mem::l(j_add(a3,(int16_t(d3) * 4))));
(d0-=d1);
if((d0 >= 0)) {
continue;
}
Mem::wl(ObjectmoveData::billy,d0);
(d6=Mem::uw(ObjectmoveData::newx));
(d7=Mem::uw(ObjectmoveData::newz));
(d6=M68k::setw(d6,(d6 - Mem::uw(ObjectmoveData::oldx))));
(d7=M68k::setw(d7,(d7 - Mem::uw(ObjectmoveData::oldz))));
(d4=Mem::uw(a2));
(d4=M68k::setw(d4,(d4 - Mem::uw(ObjectmoveData::oldx))));
(d7=M68k::muls(d7,d4));
(d4=Mem::uw(j_add(a2,Defs::EdgeT_ZPos_w)));
(d4=M68k::setw(d4,(d4 - Mem::uw(ObjectmoveData::oldz))));
(d6=M68k::muls(d6,d4));
(d7-=d6);
if((d7 > 0)) {
continue;
}
(d6=Mem::uw(ObjectmoveData::newx));
(d7=Mem::uw(ObjectmoveData::newz));
(d6=M68k::setw(d6,(d6 - Mem::uw(ObjectmoveData::oldx))));
(d7=M68k::setw(d7,(d7 - Mem::uw(ObjectmoveData::oldz))));
(d4=Mem::uw(a2));
(d4=M68k::setw(d4,j_add(d4,Mem::uw(j_add(a2,Defs::EdgeT_XLen_w)))));
(d4=M68k::setw(d4,(d4 - Mem::uw(ObjectmoveData::oldx))));
(d7=M68k::muls(d7,d4));
(d4=Mem::uw(j_add(a2,Defs::EdgeT_ZPos_w)));
(d4=M68k::setw(d4,j_add(d4,Mem::uw(j_add(a2,Defs::EdgeT_ZLen_w)))));
(d4=M68k::setw(d4,(d4 - Mem::uw(ObjectmoveData::oldz))));
(d6=M68k::muls(d6,d4));
(d7-=d6);
if((d7 < 0)) {
continue;
}
(d7=Mem::l(ObjectmoveData::billy));
(d7=M68k::divs(d7,Mem::w(j_add(a2,Defs::EdgeT_Word_5))));
(d0=Mem::uw(ObjectmoveData::oldx));
(d1=Mem::uw(ObjectmoveData::oldz));
(d0=M68k::setw(d0,(d0 - Mem::uw(a2))));
(d1=M68k::setw(d1,(d1 - Mem::uw(j_add(a2,Defs::EdgeT_ZPos_w)))));
(d1=M68k::muls(d1,Mem::w(j_add(a2,Defs::EdgeT_XLen_w))));
(d0=M68k::muls(d0,Mem::w(j_add(a2,Defs::EdgeT_ZLen_w))));
(d0-=d1);
(d0=M68k::divs(d0,Mem::w(j_add(a2,Defs::EdgeT_Word_5))));
(d0=M68k::setw(d0,(d0 - d7)));
if((int16_t(d0) <= 0)) {
(d0=1);
}
(d4=Mem::l(ObjectmoveData::newy));
(d4-=Mem::l(ObjectmoveData::oldy));
(d4=M68k::divs(d4,d0));
(d4=M68k::muls(d4,d7));
(d4+=Mem::l(ObjectmoveData::newy));
Mem::wb(ObjectmoveData::StoodInTop,((d4 < Mem::l(ObjectmoveData::LowerRoofHeight))?0xFF:0));
(a5=a3);
int32_t rp=Mem::l(ObjectmoveData::obj_RoomPathPtr_l);
Mem::ww(rp,Mem::uw(a3));
(rp+=2);
Mem::wl(ObjectmoveData::obj_RoomPathPtr_l,rp);
(a0=a3);
Mem::wl(ObjectmoveData::Obj_ZonePtr_l,a5);
(d0=Mem::uw(ObjectmoveData::obj_QuitLimit_w));
(d0=M68k::setw(d0,(d0 - 1)));
if((int16_t(d0) == 0)) {
Mem::ww(ObjectmoveData::newx,Mem::uw(ObjectmoveData::oldx));
Mem::ww(ObjectmoveData::newz,Mem::uw(ObjectmoveData::oldz));
Mem::wl(ObjectmoveData::newy,Mem::l(ObjectmoveData::oldy));
Mem::wl(ObjectmoveData::Obj_ZonePtr_l,Mem::l(ObjectmoveData::obj_ZoneBackupPtr_l));
Mem::wb(ObjectmoveData::hitwall,0xFF);
return ;
}
Mem::ww(ObjectmoveData::obj_QuitLimit_w,d0);
goto gobackanddoitallagain_continue;
}
}

gobackanddoitallagain_continue:;
}
gobackanddoitallagain_end:;
}

int32_t sqrtNewton(int32_t d2,int32_t iterations){
int32_t d0=31;
while(((d2 & j_shl(1,(d0 & 31))) == 0)){
(d0=M68k::setw(d0,(d0 - 1)));
if((int16_t(d0) == -(1))) {
break;
}
}
(d0=M68k::setw(d0,j_shr(int16_t(d0),1)));
int32_t d3=j_shl(1,(d0 & 31));
(d0=d3);
for(int32_t i=0;(i < iterations);(i)++){
int32_t d1=M68k::setw(0,d0);
(d1=M68k::muls(d1,d1));
(d1-=d2);
(d1>>=1);
(d1=M68k::divs(d1,d0));
(d0=M68k::setw(d0,(d0 - d1)));
if((int16_t(d0) <= 0)) {
(d0=M68k::setw(d0,1));
}
}
return d0;
}

void HeadTowards(){
int32_t d1=Mem::uw(ObjectmoveData::newx);
(d1=M68k::setw(d1,(d1 - Mem::uw(ObjectmoveData::oldx))));
Mem::ww(ObjectmoveData::xdiff,d1);
int32_t d2=Mem::uw(ObjectmoveData::newz);
(d2=M68k::setw(d2,(d2 - Mem::uw(ObjectmoveData::oldz))));
Mem::ww(ObjectmoveData::zdiff,d2);
(d1=M68k::muls(d1,d1));
(d2=M68k::muls(d2,d2));
Mem::ww(ObjectmoveData::distaway,0);
(d2+=d1);
if((d2 == 0)) {
return ;
}
int32_t d0=Objectmove::sqrtNewton(d2,2);
Mem::ww(ObjectmoveData::distaway,d0);
Mem::wb(ObjectmoveData::GotThere,((int16_t(d0) <= Mem::w(ObjectmoveData::Range))?0xFF:0));
if((int16_t(d0) <= Mem::w(ObjectmoveData::Range))) {
(d1=Mem::uw(ObjectmoveData::xdiff));
(d2=Mem::uw(ObjectmoveData::zdiff));
(d1=M68k::muls(d1,Mem::w(ObjectmoveData::Range)));
(d2=M68k::muls(d2,Mem::w(ObjectmoveData::Range)));
(d1=M68k::divs(d1,d0));
(d2=M68k::divs(d2,d0));
(d1=M68k::setw(d1,-(int16_t(d1))));
(d2=M68k::setw(d2,-(int16_t(d2))));
Mem::ww(ObjectmoveData::newx,j_add(Mem::uw(ObjectmoveData::newx),d1));
Mem::ww(ObjectmoveData::newz,j_add(Mem::uw(ObjectmoveData::newz),d2));
return ;
}
int32_t d3=Mem::uw(ObjectmoveData::speed);
(d3=M68k::setw(d3,j_add(d3,Mem::uw(ObjectmoveData::Range))));
if((int16_t(d3) >= int16_t(d0))) {
(d3=M68k::setw(d3,d0));
Mem::wb(ObjectmoveData::GotThere,0xFF);
}
(d3=M68k::setw(d3,(d3 - Mem::uw(ObjectmoveData::Range))));
(d1=Mem::uw(ObjectmoveData::xdiff));
(d1=M68k::muls(d1,d3));
(d1=M68k::divs(d1,d0));
(d2=Mem::uw(ObjectmoveData::zdiff));
(d2=M68k::muls(d2,d3));
(d2=M68k::divs(d2,d0));
(d1=M68k::setw(d1,j_add(d1,Mem::uw(ObjectmoveData::oldx))));
Mem::ww(ObjectmoveData::newx,d1);
(d2=M68k::setw(d2,j_add(d2,Mem::uw(ObjectmoveData::oldz))));
Mem::ww(ObjectmoveData::newz,d2);
}

void CalcDist(){
int32_t d1=Mem::uw(ObjectmoveData::newx);
(d1=M68k::setw(d1,(d1 - Mem::uw(ObjectmoveData::oldx))));
Mem::ww(ObjectmoveData::xdiff,d1);
int32_t d2=Mem::uw(ObjectmoveData::newz);
(d2=M68k::setw(d2,(d2 - Mem::uw(ObjectmoveData::oldz))));
Mem::ww(ObjectmoveData::zdiff,d2);
(d1=M68k::muls(d1,d1));
(d2=M68k::muls(d2,d2));
Mem::ww(ObjectmoveData::distaway,0);
(d2+=d1);
if((d2 == 0)) {
return ;
}
int32_t d0=Objectmove::sqrtNewton(d2,2);
Mem::ww(ObjectmoveData::distaway,d0);
}

void HeadTowardsAng(){
int32_t d1=Mem::uw(ObjectmoveData::newx);
(d1=M68k::setw(d1,(d1 - Mem::uw(ObjectmoveData::oldx))));
Mem::ww(ObjectmoveData::xdiff,d1);
int32_t d2=Mem::uw(ObjectmoveData::newz);
(d2=M68k::setw(d2,(d2 - Mem::uw(ObjectmoveData::oldz))));
Mem::ww(ObjectmoveData::zdiff,d2);
(d1=M68k::muls(d1,d1));
(d2=M68k::muls(d2,d2));
int32_t d0=0;
(d2+=d1);
Mem::wb(ObjectmoveData::GotThere,((d2 == 0)?0xFF:0));
if((d2 != 0)) {
(d0=Objectmove::sqrtNewton(d2,3));
Mem::wb(ObjectmoveData::GotThere,((int16_t(d0) <= Mem::w(ObjectmoveData::Range))?0xFF:0));
if((int16_t(d0) <= Mem::w(ObjectmoveData::Range))) {
Mem::ww(ObjectmoveData::newx,Mem::uw(ObjectmoveData::oldx));
Mem::ww(ObjectmoveData::newz,Mem::uw(ObjectmoveData::oldz));
}
else {
int32_t d3=Mem::uw(ObjectmoveData::speed);
(d3=M68k::setw(d3,j_add(d3,Mem::uw(ObjectmoveData::Range))));
if((int16_t(d3) >= int16_t(d0))) {
(d3=M68k::setw(d3,d0));
Mem::wb(ObjectmoveData::GotThere,0xFF);
}
(d3=M68k::setw(d3,(d3 - Mem::uw(ObjectmoveData::Range))));
(d1=Mem::uw(ObjectmoveData::xdiff));
(d1=M68k::muls(d1,d3));
(d1=M68k::divs(d1,d0));
(d2=Mem::uw(ObjectmoveData::zdiff));
(d2=M68k::muls(d2,d3));
(d2=M68k::divs(d2,d0));
(d1=M68k::setw(d1,j_add(d1,Mem::uw(ObjectmoveData::oldx))));
Mem::ww(ObjectmoveData::newx,d1);
(d2=M68k::setw(d2,j_add(d2,Mem::uw(ObjectmoveData::oldz))));
Mem::ww(ObjectmoveData::newz,d2);
}
}
if((int16_t(d0) == 0)) {
return ;
}
(d0=M68k::setw(d0,j_add(d0,1)));
(d1=Mem::uw(ObjectmoveData::xdiff));
(d1=M68k::swap(d1));
(d1=(d1 & int32_t(0xFFFF0000u)));
(d1>>=1);
(d1=M68k::divs(d1,d0));
Mem::ww(ObjectmoveData::SinRet,d1);
(d1=Mem::uw(ObjectmoveData::zdiff));
(d1=M68k::swap(d1));
(d1=(d1 & int32_t(0xFFFF0000u)));
(d1>>=1);
(d1=M68k::divs(d1,d0));
Mem::ww(ObjectmoveData::CosRet,d1);
(d0=Mem::uw(ObjectmoveData::SinRet));
int32_t d2a=0;
int32_t a2=TablesData::SinCosTable_vw;
int32_t a3=j_add(a2,TablesData::COSINE_OFS);
int32_t d5=3;
int32_t d6=TablesData::COSINE_OFS;
do {
int32_t d3=Mem::w(j_add(a2,(int16_t(d2a) * 2)));
int32_t d4=Mem::w(j_add(a3,(int16_t(d2a) * 2)));
(d4=M68k::muls(d4,d0));
(d3=M68k::muls(d3,d1));
(d4-=d3);
if((d4 >= 0)) {
(d2a=M68k::setw(d2a,j_add(d2a,d6)));
(d2a=M68k::setw(d2a,j_add(d2a,d6)));
}
(d2a=M68k::setw(d2a,(d2a - d6)));
(d2a=M68k::setw(d2a,(d2a & 4095)));
(d6=M68k::setw(d6,j_shr(int16_t(d6),1)));
(d5=M68k::setw(d5,(d5 - 1)));
}
while((int16_t(d5) != -(1)));
(d2a=M68k::setw(d2a,j_add(d2a,d2a)));
Mem::ww(ObjectmoveData::AngRet,d2a);
}

void CheckHit(int32_t d2){
int32_t d0=Mem::uw(ObjectmoveData::newx);
(d0=M68k::setw(d0,(d0 - Mem::uw(ObjectmoveData::oldx))));
int32_t d1=Mem::uw(ObjectmoveData::newz);
(d1=M68k::setw(d1,(d1 - Mem::uw(ObjectmoveData::oldz))));
(d1=M68k::muls(d1,d1));
(d0=M68k::muls(d0,d0));
(d1+=d0);
Mem::wb(ObjectmoveData::hitwall,((d1 < d2)?0xFF:0));
}

int32_t GetNextCPt(int32_t d0,int32_t d1){
Mem::wb(ObjectmoveData::ONLYSEE,0);
if((int16_t(d0) == int16_t(d1))) {
return d0;
}
(d0=M68k::muls(d0,100));
(d1=int16_t(d1));
(d0+=d1);
int32_t a0=Mem::l(HiresData::Lvl_WalkLinksPtr_l);
if((Mem::b(AiBss::AI_FlyABit_w) != 0)) {
(a0=Mem::l(HiresData::Lvl_FlyLinksPtr_l));
}
(d0=M68k::setb(d0,Mem::ub(j_add(a0,int16_t(d0)))));
(d1=M68k::setb(d1,d0));
(d0=M68k::setb(d0,(d0 & 0x7f)));
(d1=M68k::setb(d1,(d1 & 0x80)));
Mem::wb(ObjectmoveData::ONLYSEE,((int8_t(d1) != 0)?0xFF:0));
(d0=M68k::setw(d0,int8_t(d0)));
return d0;
}

void CanItBeSeenAng(){
int32_t d0=Mem::uw(ObjectmoveData::Facedir);
int32_t a0=TablesData::SinCosTable_vw;
(a0+=int16_t(d0));
(d0=Mem::uw(a0));
int32_t d1=Mem::uw(j_add(a0,TablesData::COSINE_OFS));
int32_t d2=Mem::uw(ObjectmoveData::Targetx);
(d2=M68k::setw(d2,(d2 - Mem::uw(ObjectmoveData::Viewerx))));
int32_t d3=Mem::uw(ObjectmoveData::Targetz);
(d3=M68k::setw(d3,(d3 - Mem::uw(ObjectmoveData::Viewerz))));
(d2=M68k::muls(d2,d1));
(d3=M68k::muls(d3,d0));
(d2-=d3);
if((d2 <= 0)) {
Mem::wb(ObjectmoveData::CanSee,0);
return ;
}
int32_t a0t=Mem::l(ObjectmoveData::Obj_ToZonePtr_l);
(d0=Mem::uw(a0t));
(a0=Mem::l(ObjectmoveData::Obj_FromZonePtr_l));
(a0+=Defs::ZoneT_PotVisibleZoneList_vw);
Objectmove::inList(a0,d0);
}

void CanItBeSeen(){
int32_t a1=Mem::l(ObjectmoveData::Obj_ToZonePtr_l);
int32_t d0=Mem::uw(a1);
int32_t a0=Mem::l(ObjectmoveData::Obj_FromZonePtr_l);
if((a0 == a1)) {
Mem::wb(ObjectmoveData::CanSee,0xFF);
int32_t td0=Mem::ub(ObjectmoveData::ViewerTop);
int32_t td1=Mem::ub(ObjectmoveData::TargetTop);
if((((td0 ^ td1) & 0xFF) != 0)) {
Mem::wb(ObjectmoveData::CanSee,0);
}
return ;
}
(a0+=Defs::ZoneT_PotVisibleZoneList_vw);
Objectmove::inList(a0,d0);
}

void inList(int32_t a0,int32_t d0){
int32_t a1{};
int32_t d1{};
int32_t d2{};
while(true){
(d1=Mem::w(a0));
if((d1 < 0)) {
Mem::wb(ObjectmoveData::CanSee,0);
return ;
}
(a1=Mem::l(LevelBss::Lvl_ZoneGraphAddsPtr_l));
(a1=Mem::l(j_add(a1,(int16_t(d1) * 8))));
(a1+=Mem::l(LevelBss::Lvl_GraphicsPtr_l));
(a0+=Defs::PVST_SizeOf_l);
if((Mem::w(a1) == int16_t(d0))) {
break;
}
}
Mem::wb(ObjectmoveData::CanSee,0xFF);
int32_t a2=Mem::l(LevelBss::Lvl_PointsPtr_l);
(d1=Mem::uw(ObjectmoveData::Targetx));
(d2=Mem::uw(ObjectmoveData::Targetz));
(d1=M68k::setw(d1,(d1 - Mem::uw(ObjectmoveData::Viewerx))));
(d2=M68k::setw(d2,(d2 - Mem::uw(ObjectmoveData::Viewerz))));
int32_t d3=0;
(d3=M68k::setw(d3,Mem::uw((a0 - 6))));
if((int16_t(d3) >= 0)) {
(a1=Mem::l(LevelBss::Lvl_ClipsPtr_l));
(a1=j_add(a1,(d3 * 2)));
Mem::wl(ObjectmoveData::clipstocheck,a1);
while(true){
if((Mem::w(a1) < 0)) {
break;
}
int32_t dd0=Mem::w(a1);
if((dd0 >= 0)) {
(d3=Mem::l(j_add(a2,(int16_t(dd0) * 4))));
int32_t d4=int16_t(d3);
(d4=M68k::setw(d4,(d4 - Mem::uw(ObjectmoveData::Viewerz))));
(d3=M68k::swap(d3));
(d3=M68k::setw(d3,(d3 - Mem::uw(ObjectmoveData::Viewerx))));
(d3=M68k::muls(d3,d2));
(d4=M68k::muls(d4,d1));
(d4-=d3);
if((d4 <= 0)) {
Mem::wb(ObjectmoveData::CanSee,0);
return ;
}
}
(a1+=2);
}
(a1+=2);
while(true){
if((Mem::w(a1) < 0)) {
break;
}
int32_t dd0=Mem::w(a1);
if((dd0 >= 0)) {
(d3=Mem::l(j_add(a2,(int16_t(dd0) * 4))));
int32_t d4=int16_t(d3);
(d4=M68k::setw(d4,(d4 - Mem::uw(ObjectmoveData::Viewerz))));
(d3=M68k::swap(d3));
(d3=M68k::setw(d3,(d3 - Mem::uw(ObjectmoveData::Viewerx))));
(d3=M68k::muls(d3,d2));
(d4=M68k::muls(d4,d1));
(d4-=d3);
if((d4 >= 0)) {
Mem::wb(ObjectmoveData::CanSee,0);
return ;
}
}
(a1+=2);
}
}
int32_t d0v=Mem::uw(ObjectmoveData::Targetx);
int32_t d1v=Mem::uw(ObjectmoveData::Targetz);
(d0v=M68k::setw(d0v,(d0v - Mem::uw(ObjectmoveData::Viewerx))));
(d1v=M68k::setw(d1v,(d1v - Mem::uw(ObjectmoveData::Viewerz))));
int32_t a5=Mem::l(ObjectmoveData::Obj_FromZonePtr_l);
(a1=Mem::l(LevelBss::Lvl_ZoneEdgePtr_l));
(d2=Mem::ub(ObjectmoveData::ViewerTop));
int32_t d7=Mem::uw(ObjectmoveData::Targety);
(d7=M68k::setw(d7,(d7 - Mem::uw(ObjectmoveData::Viewery))));
while(true){
{
int32_t a0e=j_add(a5,Mem::w(j_add(a5,Defs::ZoneT_EdgeListOffset_w)));
while(true){
int32_t d5=Mem::w(a0e);
(a0e+=2);
if((d5 < 0)) {
Mem::wb(ObjectmoveData::CanSee,0);
return ;
}
(d5=M68k::setw(d5,j_shl(d5,4)));
(a2=j_add(a1,int16_t(d5)));
(d3=Mem::uw(a2));
int32_t d4=Mem::uw(j_add(a2,Defs::EdgeT_ZPos_w));
(d3=M68k::setw(d3,(d3 - Mem::uw(ObjectmoveData::Viewerx))));
(d4=M68k::setw(d4,(d4 - Mem::uw(ObjectmoveData::Viewerz))));
(d5=M68k::setw(d5,d3));
int32_t d6=M68k::setw(0,d4);
(d3=M68k::muls(d3,d1v));
(d4=M68k::muls(d4,d0v));
(d4-=d3);
if((d4 <= 0)) {
continue;
}
(d5=M68k::setw(d5,j_add(d5,Mem::uw(j_add(a2,Defs::EdgeT_XLen_w)))));
(d6=M68k::setw(d6,j_add(d6,Mem::uw(j_add(a2,Defs::EdgeT_ZLen_w)))));
(d6=M68k::muls(d6,d0v));
(d5=M68k::muls(d5,d1v));
(d6-=d5);
if((d6 >= 0)) {
continue;
}
if((Mem::w(j_add(a2,Defs::EdgeT_JoinZone_w)) < 0)) {
Mem::wb(ObjectmoveData::CanSee,0);
return ;
}
(d3=Mem::uw(ObjectmoveData::Targetx));
(d4=Mem::uw(ObjectmoveData::Targetz));
(d3=M68k::setw(d3,(d3 - Mem::uw(a2))));
(d4=M68k::setw(d4,(d4 - Mem::uw(j_add(a2,Defs::EdgeT_ZPos_w)))));
(d4=M68k::muls(d4,Mem::w(j_add(a2,Defs::EdgeT_XLen_w))));
(d3=M68k::muls(d3,Mem::w(j_add(a2,Defs::EdgeT_ZLen_w))));
(d4-=d3);
(d5=Mem::uw(ObjectmoveData::Viewerx));
(d6=Mem::uw(ObjectmoveData::Viewerz));
(d5=M68k::setw(d5,(d5 - Mem::uw(a2))));
(d6=M68k::setw(d6,(d6 - Mem::uw(j_add(a2,Defs::EdgeT_ZPos_w)))));
(d6=M68k::muls(d6,Mem::w(j_add(a2,Defs::EdgeT_XLen_w))));
(d5=M68k::muls(d5,Mem::w(j_add(a2,Defs::EdgeT_ZLen_w))));
(d5-=d6);
(d4=M68k::divs(d4,Mem::w(j_add(a2,Defs::EdgeT_Word_5))));
(d5=M68k::divs(d5,Mem::w(j_add(a2,Defs::EdgeT_Word_5))));
(d4=M68k::setw(d4,j_add(d4,d5)));
if((int16_t(d4) != 0)) {
(d5=M68k::muls(d5,d7));
(d5=M68k::divs(d5,d4));
}
(d5=M68k::setw(d5,j_add(d5,Mem::uw(ObjectmoveData::Viewery))));
(d5=int16_t(d5));
(d5<<=7);
if((int8_t(d2) != 0)) {
if((d5 < Mem::l(j_add(a5,Defs::ZoneT_UpperRoof_l)))) {
Mem::wb(ObjectmoveData::CanSee,0);
return ;
}
if((d5 > Mem::l(j_add(a5,Defs::ZoneT_UpperFloor_l)))) {
Mem::wb(ObjectmoveData::CanSee,0);
return ;
}
}
else {
if((d5 < Mem::l(j_add(a5,Defs::ZoneT_Roof_l)))) {
Mem::wb(ObjectmoveData::CanSee,0);
return ;
}
if((d5 > Mem::l(j_add(a5,Defs::ZoneT_Floor_l)))) {
Mem::wb(ObjectmoveData::CanSee,0);
return ;
}
}
Mem::wb(ObjectmoveData::donessomething,0xFF);
(d3=0);
(d3=M68k::setw(d3,Mem::uw(j_add(a2,Defs::EdgeT_JoinZone_w))));
int32_t a3=Mem::l(LevelBss::Lvl_ZonePtrsPtr_l);
(a5=Mem::l(j_add(a3,(int16_t(d3) * 4))));
(d2=M68k::setb(d2,0));
if((d5 > Mem::l(j_add(a5,Defs::ZoneT_Floor_l)))) {
Mem::wb(ObjectmoveData::CanSee,0);
return ;
}
if((d5 <= Mem::l(j_add(a5,Defs::ZoneT_Roof_l)))) {
(d2=M68k::setb(d2,0xFF));
if((d5 > Mem::l(j_add(a5,Defs::ZoneT_UpperFloor_l)))) {
Mem::wb(ObjectmoveData::CanSee,0);
return ;
}
if((d5 < Mem::l(j_add(a5,Defs::ZoneT_UpperRoof_l)))) {
Mem::wb(ObjectmoveData::CanSee,0);
return ;
}
}
if((a5 != Mem::l(ObjectmoveData::Obj_ToZonePtr_l))) {
goto GoThroughZones_continue;
}
int32_t td3=Mem::ub(ObjectmoveData::TargetTop);
if((((td3 ^ d2) & 0xFF) != 0)) {
Mem::wb(ObjectmoveData::CanSee,0);
return ;
}
return ;
}
}

GoThroughZones_continue:;
}
GoThroughZones_end:;
}

int32_t GetRand(){
int32_t d0=Mem::uw(ObjectmoveData::Rand1);
(d0=((j_shl(d0,3) | j_ushr(d0,13)) & 0xFFFF));
(d0=(j_add(d0,0x2343) & 0xFFFF));
Mem::ww(ObjectmoveData::Rand1,d0);
return d0;
}

void GoInDirection(int32_t d0){
int32_t a0=TablesData::SinCosTable_vw;
(a0+=int16_t(d0));
int32_t d1=Mem::w(a0);
int32_t d2=Mem::w(j_add(a0,TablesData::COSINE_OFS));
(d1=M68k::muls(d1,Mem::w(ObjectmoveData::speed)));
(d1+=d1);
(d2=M68k::muls(d2,Mem::w(ObjectmoveData::speed)));
(d2+=d2);
(d1=M68k::swap(d1));
(d2=M68k::swap(d2));
(d1=M68k::setw(d1,j_add(d1,Mem::uw(ObjectmoveData::oldx))));
(d2=M68k::setw(d2,j_add(d2,Mem::uw(ObjectmoveData::oldz))));
Mem::ww(ObjectmoveData::newx,d1);
Mem::ww(ObjectmoveData::newz,d2);
}

void Obj_DoCollision(int32_t a2){
int32_t a0=Mem::l(LevelBss::Lvl_ObjectDataPtr_l);
int32_t d0=Mem::uw(HiresData::CollId);
(d0=M68k::setw(d0,j_shl(d0,6)));
Mem::ww(ObjectmoveData::tmp_zone_id_w,Mem::uw(j_add(j_add(a0,int16_t(d0)),Defs::ObjT_ZoneID_w)));
(d0=Mem::b(j_add(j_add(a0,int16_t(d0)),Defs::ObjT_TypeID_b)));
(a0-=Defs::ObjT_SizeOf_l);
int32_t a1=Mem::l(LevelBss::Lvl_ObjectPointsPtr_l);
int32_t d7=Mem::l(ObjectmoveData::Obj_CollideFlags_l);
int32_t d6=Mem::ub(ObjectmoveData::StoodInTop);
int32_t d4=Mem::l(ObjectmoveData::newy);
int32_t d5=d4;
(d5+=Mem::l(ObjectmoveData::thingheight));
(d4>>=7);
(d5>>=7);
Mem::wb(ObjectmoveData::hitwall,0);
int32_t d1{};
int32_t d2{};
int32_t d3{};
while(true){
(a0+=Defs::ObjT_SizeOf_l);
(d0=Mem::w(a0));
if((d0 < 0)) {
return ;
}
if((int16_t(d0) == Mem::w(HiresData::CollId))) {
continue;
}
if((Mem::w(j_add(a0,Defs::ObjT_ZoneID_w)) < 0)) {
continue;
}
(d1=Mem::uw(ObjectmoveData::tmp_zone_id_w));
if((int16_t(d1) != Mem::w(j_add(a0,Defs::ObjT_ZoneID_w)))) {
continue;
}
if((Mem::b(j_add(a0,Defs::EntT_HitPoints_b)) == 0)) {
continue;
}
(d1=Mem::ub(j_add(a0,Defs::ShotT_InUpperZone_b)));
if((((d1 ^ d6) & 0xFF) != 0)) {
continue;
}
(d3=0);
(d3=M68k::setb(d3,Mem::ub(j_add(a0,Defs::ObjT_TypeID_b))));
if((int8_t(d3) < 0)) {
continue;
}
if((int8_t(d3) != 0)) {
if((int8_t(d3) != 1)) {
continue;
}
int32_t a4=Mem::l(HiresData::GLF_DatabasePtr_l);
(a4+=Defs::GLFT_ObjectDefs);
(d1=0);
(d1=M68k::setb(d1,Mem::ub(j_add(a0,Defs::EntT_Type_b))));
(d1=M68k::muls(d1,Defs::ODefT_SizeOf_l));
int32_t beh=Mem::w(j_add(j_add(a4,int16_t(d1)),Defs::ODefT_Behaviour_w));
if((beh < 2)) {
continue;
}
if((beh == 2)) {
if((int8_t(Mem::b(j_add(a0,Defs::EntT_HitPoints_b))) <= 0)) {
continue;
}
}
}
(d1=Mem::uw(j_add(a0,Defs::ObjT_ZPos_l)));
(d1=M68k::setw(d1,(d1 - Mem::uw(j_add(j_add(a2,(int16_t(d3) * 8)),2)))));
if((int16_t(d5) < int16_t(d1))) {
continue;
}
(d1=M68k::setw(d1,j_add(d1,Mem::uw(j_add(j_add(a2,(int16_t(d3) * 8)),4)))));
if((int16_t(d4) > int16_t(d1))) {
continue;
}
(d1=Mem::uw(j_add(a1,(int16_t(d0) * 8))));
(d2=Mem::uw(j_add(j_add(a1,(int16_t(d0) * 8)),4)));
(d1=M68k::setw(d1,(d1 - Mem::uw(ObjectmoveData::newx))));
if((int16_t(d1) < 0)) {
(d1=M68k::setw(d1,-(int16_t(d1))));
}
(d2=M68k::setw(d2,(d2 - Mem::uw(ObjectmoveData::newz))));
if((int16_t(d2) < 0)) {
(d2=M68k::setw(d2,-(int16_t(d2))));
}
if((int16_t(d2) > int16_t(d1))) {
(d2=M68k::setw(d2,(d2 - 80)));
if((int16_t(d2) > 80)) {
continue;
}
Mem::wb(ObjectmoveData::hitwall,0xFF);
return ;
}
(d1=M68k::setw(d1,(d1 - 80)));
if((int16_t(d1) > 80)) {
continue;
}
(d1=Mem::uw(j_add(a1,(int16_t(d0) * 8))));
(d2=Mem::uw(j_add(j_add(a1,(int16_t(d0) * 8)),4)));
(d6=M68k::setw(d6,d1));
(d7=M68k::setw(d7,d2));
(d6=M68k::setw(d6,(d6 - Mem::uw(ObjectmoveData::newx))));
(d7=M68k::setw(d7,(d7 - Mem::uw(ObjectmoveData::newz))));
(d6=M68k::muls(d6,d6));
(d7=M68k::muls(d7,d7));
(d7+=d6);
(d1=M68k::setw(d1,(d1 - Mem::uw(ObjectmoveData::oldx))));
(d2=M68k::setw(d2,(d2 - Mem::uw(ObjectmoveData::oldz))));
(d1=M68k::muls(d1,d1));
(d2=M68k::muls(d2,d2));
(d2+=d1);
if((d7 > d2)) {
continue;
}
Mem::wb(ObjectmoveData::hitwall,0xFF);
return ;
}
}

int32_t CheckTeleport(){
Mem::wb(ObjectmoveData::OKTEL,0);
int32_t d0=Mem::uw(ObjectmoveData::FromZone);
int32_t a2=Mem::l(LevelBss::Lvl_ZonePtrsPtr_l);
(a2=Mem::l(j_add(a2,(int16_t(d0) * 4))));
if((Mem::w(j_add(a2,Defs::ZoneT_TelZone_w)) < 0)) {
return a2;
}
Mem::wl(ObjectmoveData::floortemp,Mem::l(j_add(a2,Defs::ZoneT_Floor_l)));
(d0=Mem::uw(j_add(a2,Defs::ZoneT_TelZone_w)));
int32_t a3=Mem::l(LevelBss::Lvl_ZonePtrsPtr_l);
(a3=Mem::l(j_add(a3,(int16_t(d0) * 4))));
(d0=Mem::l(j_add(a3,Defs::ZoneT_Floor_l)));
(d0-=Mem::l(ObjectmoveData::floortemp));
Mem::wl(ObjectmoveData::floortemp,d0);
Mem::wl(ObjectmoveData::newy,j_add(Mem::l(ObjectmoveData::newy),d0));
Mem::ww(ObjectmoveData::newx,Mem::uw(j_add(a2,Defs::ZoneT_TelX_w)));
Mem::ww(ObjectmoveData::newz,Mem::uw(j_add(a2,Defs::ZoneT_TelZ_w)));
Mem::wl(ObjectmoveData::Obj_CollideFlags_l,0b1111111111111111111);
Objectmove::Obj_DoCollision(a2);
(d0=Mem::l(ObjectmoveData::floortemp));
Mem::wl(ObjectmoveData::newy,(Mem::l(ObjectmoveData::newy) - d0));
bool hit=(Mem::b(ObjectmoveData::hitwall) != 0);
Mem::wb(ObjectmoveData::OKTEL,(hit?0:0xFF));
if(hit) {
return a2;
}
(d0=Mem::uw(j_add(a2,Defs::ZoneT_TelZone_w)));
(a2=Mem::l(LevelBss::Lvl_ZonePtrsPtr_l));
(a2=Mem::l(j_add(a2,(int16_t(d0) * 4))));
Mem::wl(ObjectmoveData::Obj_ZonePtr_l,a2);
return a2;
}

void FindCollisionPt(){
int32_t d0=Mem::uw(ObjectmoveData::Targetx);
int32_t d1=Mem::uw(ObjectmoveData::Targetz);
(d0=M68k::setw(d0,(d0 - Mem::uw(ObjectmoveData::Viewerx))));
(d1=M68k::setw(d1,(d1 - Mem::uw(ObjectmoveData::Viewerz))));
int32_t a5=Mem::l(ObjectmoveData::Obj_FromZonePtr_l);
int32_t a1=Mem::l(LevelBss::Lvl_ZoneEdgePtr_l);
int32_t d2=Mem::ub(ObjectmoveData::ViewerTop);
int32_t d7=Mem::uw(ObjectmoveData::Targety);
(d7=M68k::setw(d7,(d7 - Mem::uw(ObjectmoveData::Viewery))));
while(true){
{
int32_t a0=j_add(a5,Mem::w(j_add(a5,Defs::ZoneT_EdgeListOffset_w)));
while(true){
int32_t d5=Mem::w(a0);
(a0+=2);
if((d5 < 0)) {
Mem::wb(ObjectmoveData::CanSee,0);
return ;
}
(d5=M68k::setw(d5,j_shl(d5,4)));
int32_t a2=j_add(a1,int16_t(d5));
int32_t d3=Mem::uw(a2);
int32_t d4=Mem::uw(j_add(a2,Defs::EdgeT_ZPos_w));
(d3=M68k::setw(d3,(d3 - Mem::uw(ObjectmoveData::Viewerx))));
(d4=M68k::setw(d4,(d4 - Mem::uw(ObjectmoveData::Viewerz))));
(d5=M68k::setw(d5,d3));
int32_t d6=M68k::setw(0,d4);
(d3=M68k::muls(d3,d1));
(d4=M68k::muls(d4,d0));
(d4-=d3);
if((d4 <= 0)) {
continue;
}
(d5=M68k::setw(d5,j_add(d5,Mem::uw(j_add(a2,Defs::EdgeT_XLen_w)))));
(d6=M68k::setw(d6,j_add(d6,Mem::uw(j_add(a2,Defs::EdgeT_ZLen_w)))));
(d6=M68k::muls(d6,d0));
(d5=M68k::muls(d5,d1));
(d6-=d5);
if((d6 >= 0)) {
continue;
}
(d3=Mem::uw(ObjectmoveData::Targetx));
(d4=Mem::uw(ObjectmoveData::Targetz));
(d3=M68k::setw(d3,(d3 - Mem::uw(a2))));
(d4=M68k::setw(d4,(d4 - Mem::uw(j_add(a2,Defs::EdgeT_ZPos_w)))));
(d4=M68k::muls(d4,Mem::w(j_add(a2,Defs::EdgeT_XLen_w))));
(d3=M68k::muls(d3,Mem::w(j_add(a2,Defs::EdgeT_ZLen_w))));
(d4-=d3);
(d5=Mem::uw(ObjectmoveData::Viewerx));
(d6=Mem::uw(ObjectmoveData::Viewerz));
(d5=M68k::setw(d5,(d5 - Mem::uw(a2))));
(d6=M68k::setw(d6,(d6 - Mem::uw(j_add(a2,Defs::EdgeT_ZPos_w)))));
(d6=M68k::muls(d6,Mem::w(j_add(a2,Defs::EdgeT_XLen_w))));
(d5=M68k::muls(d5,Mem::w(j_add(a2,Defs::EdgeT_ZLen_w))));
(d5-=d6);
(d4=M68k::divs(d4,Mem::w(j_add(a2,Defs::EdgeT_Word_5))));
(d5=M68k::divs(d5,Mem::w(j_add(a2,Defs::EdgeT_Word_5))));
(d6=M68k::setw(d6,d5));
(d4=M68k::setw(d4,j_add(d4,d5)));
if((int16_t(d4) != 0)) {
(d5=M68k::muls(d5,d7));
(d5=M68k::divs(d5,d4));
}
(d5=M68k::setw(d5,j_add(d5,Mem::uw(ObjectmoveData::Viewery))));
(d5=int16_t(d5));
(d5<<=7);
(d3=0);
(d3=M68k::setw(d3,Mem::uw(j_add(a2,Defs::EdgeT_JoinZone_w))));
if((int16_t(d3) < 0)) {
return ;
}
int32_t a3=Mem::l(LevelBss::Lvl_ZonePtrsPtr_l);
(a5=Mem::l(j_add(a3,(int16_t(d3) * 4))));
(d2=M68k::setb(d2,0));
if((d5 > Mem::l(j_add(a5,Defs::ZoneT_Floor_l)))) {
return ;
}
if((d5 <= Mem::l(j_add(a5,Defs::ZoneT_Roof_l)))) {
(d2=M68k::setb(d2,0xFF));
if((d5 > Mem::l(j_add(a5,Defs::ZoneT_UpperFloor_l)))) {
return ;
}
if((d5 < Mem::l(j_add(a5,Defs::ZoneT_UpperRoof_l)))) {
return ;
}
}
goto GoThroughZones_continue;
}
}

GoThroughZones_continue:;
}
GoThroughZones_end:;
}

void FindCloseRoom(int32_t d0,int32_t a0){
int32_t d1=Mem::uw(j_add(a0,Defs::ObjT_ZPos_l));
(d1=int16_t(d1));
(d1<<=7);
Mem::wl(ObjectmoveData::oldy,d1);
Mem::wl(ObjectmoveData::newy,d1);
(d1=Mem::uw(a0));
int32_t a1=Mem::l(LevelBss::Lvl_ObjectPointsPtr_l);
(a1=j_add(a1,(int16_t(d1) * 8)));
Mem::ww(ObjectmoveData::oldx,Mem::uw(a1));
Mem::ww(ObjectmoveData::oldz,Mem::uw(j_add(a1,Defs::ObjT_ZPos_l)));
int32_t d2=Mem::uw(j_add(a0,Defs::ObjT_ZoneID_w));
int32_t a5=Mem::l(LevelBss::Lvl_ZonePtrsPtr_l);
(d2=Mem::l(j_add(a5,(int16_t(d2) * 4))));
Mem::wl(ObjectmoveData::Obj_ZonePtr_l,d2);
Mem::ww(ObjectmoveData::newx,Mem::uw(NewaliencontrolData::THISPLRxoff));
Mem::ww(ObjectmoveData::newz,Mem::uw(NewaliencontrolData::THISPLRzoff));
Mem::ww(ObjectmoveData::speed,d0);
Objectmove::HeadTowards();
(d0=Mem::uw(ObjectmoveData::newx));
(d0=M68k::setw(d0,(d0 - Mem::uw(ObjectmoveData::oldx))));
(d1=Mem::uw(ObjectmoveData::oldz));
(d1=M68k::setw(d1,(d1 - Mem::uw(ObjectmoveData::newz))));
Mem::ww(ObjectmoveData::xd,d1);
Mem::ww(ObjectmoveData::zd,d0);
Mem::wl(ObjectmoveData::StepUpVal,100000);
Mem::wl(ObjectmoveData::StepDownVal,100000);
Mem::ww(ObjectmoveData::thingheight,0);
Mem::wb(ObjectmoveData::exitfirst,0xFF);
(d1=M68k::setw(d1,j_add(d1,Mem::uw(ObjectmoveData::oldx))));
(d0=M68k::setw(d0,j_add(d0,Mem::uw(ObjectmoveData::oldz))));
Mem::ww(ObjectmoveData::newx,d1);
Mem::ww(ObjectmoveData::newz,d0);
Mem::wb(ObjectmoveData::Obj_WallBounce_b,0);
Objectmove::MoveObject();
int32_t a2=TablesBss::Obj_RoomPath_vw;
int32_t a3=ObjectmoveData::possclose;
Mem::ww(a3,Mem::uw(j_add(a0,Defs::ObjT_ZoneID_w)));
(a3+=2);
int32_t v{};
do {
(v=Mem::w(a2));
(a2+=2);
Mem::ww(a3,v);
(a3+=2);
}
while((v >= 0));
(a3-=2);
(d0=Mem::uw(ObjectmoveData::oldx));
(d0=M68k::setw(d0,(d0 - Mem::uw(ObjectmoveData::xd))));
(d1=Mem::uw(ObjectmoveData::oldz));
(d1=M68k::setw(d1,(d1 - Mem::uw(ObjectmoveData::zd))));
Mem::ww(ObjectmoveData::newx,d0);
Mem::ww(ObjectmoveData::newz,d1);
Mem::wb(ObjectmoveData::Obj_WallBounce_b,0);
Objectmove::MoveObject();
(a2=TablesBss::Obj_RoomPath_vw);
do {
(v=Mem::w(a2));
(a2+=2);
Mem::ww(a3,v);
(a3+=2);
}
while((v >= 0));
Mem::ww(a3,-(1));
int32_t d7=Mem::uw(j_add(a0,Defs::ObjT_ZoneID_w));
(a3=Mem::l(ZoneBss::Zone_EndOfListPtr_l));
while(true){
(a2=ObjectmoveData::possclose);
(a3-=2);
(d0=Mem::w(a3));
if((d0 < 0)) {
break;
}
while(true){
(d1=Mem::w(a2));
(a2+=2);
if((d1 < 0)) {
break;
}
if((int16_t(d1) == int16_t(d0))) {
(d7=M68k::setw(d7,d0));
break;
}
}
}
Mem::ww(j_add(a0,Defs::ObjT_ZoneID_w),d7);
}

}