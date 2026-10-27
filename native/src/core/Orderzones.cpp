#include "original.hpp"
namespace Orderzones {
void Zone_OrderZones(){
ZoneEdgePvs::Zone_CheckVisibleEdges();
int32_t d0=Mem::uw(HiresData::Plr_XOff_l);
(d0=M68k::swap(d0));
(d0=M68k::setw(d0,Mem::uw(HiresData::Plr_ZOff_l)));
(d0&=Mem::l(Orderzones::Zone_MovementMask_l));
if((d0 == Mem::l(Orderzones::zone_LastPosition_vw))) {
return ;
}
Mem::wl(Orderzones::zone_LastPosition_vw,d0);
Sys::Sys_MemFillLong(ZoneBss::zone_ToDrawTable_vw,0,100);
int32_t a1=Mem::l(LevelBss::Lvl_ListOfGraphRoomsPtr_l);
Mem::wl(Orderzones::tmp_ListOfGraphRoomsPtr_l,a1);
int32_t a3=ZoneBss::zone_ToDrawTable_vw;
int32_t a4=SystemBss::Sys_Workspace_vl;
int32_t a5=ZoneBss::zone_OrderTable_vw;
while(true){
(d0=Mem::w(a1));
if((d0 < 0)) {
break;
}
Mem::wb(j_add(a3,int16_t(d0)),0xFF);
Mem::wl(j_add(a4,(int16_t(d0) * 4)),Mem::l(j_add(a1,4)));
(a1+=8);
}
int32_t a0=Mem::l(Orderzones::tmp_ListOfGraphRoomsPtr_l);
int32_t a2=ZoneBss::zone_OrderTable_vw;
(d0=0);
int32_t d1=2;
while(true){
int32_t d2=Mem::w(a0);
if((d2 < 0)) {
break;
}
(a1=Mem::l(LevelBss::Lvl_ZoneGraphAddsPtr_l));
(a1=Mem::l(j_add(a1,(int16_t(d2) * 4))));
(a1+=Mem::l(LevelBss::Lvl_GraphicsPtr_l));
(a2+=8);
Mem::ww(j_add(a2,2),d2);
Mem::ww(a2,d0);
Mem::ww(j_add(a2,4),d1);
(d0+=1);
(d1+=1);
(a0+=8);
}
Mem::ww(j_add(a2,4),-(1));
Mem::ww(j_add(ZoneBss::zone_OrderTable_vw,4),1);
Mem::ww(ZoneBss::zone_OrderTable_vw,-(1));
Mem::ww(j_add(ZoneBss::zone_OrderTable_vw,2),-(1));
int32_t d5=2;
int32_t d7=100;
(a5=a2);
while(true){
Mem::ww(DevInst::dev_Reserved2_w,j_add(Mem::uw(DevInst::dev_Reserved2_w),1));
(a1=Mem::l(LevelBss::Lvl_ZoneEdgePtr_l));
(d0=Mem::uw(j_add(a5,2)));
int32_t a6=SystemBss::Sys_Workspace_vl;
(a6=j_add(a6,(int16_t(d0) * 4)));
int32_t d6=Mem::l(a6);
(a0=Mem::l(LevelBss::Lvl_ZonePtrsPtr_l));
(a0=Mem::l(j_add(a0,(int16_t(d0) * 4))));
(a0=j_add(a0,Mem::w(j_add(a0,Defs::ZoneT_EdgeListOffset_w))));
int32_t a4cur=a5;
(d0=Mem::w(a5));
if((d0 < 0)) {
break;
}
(a5=ZoneBss::zone_OrderTable_vw);
(a5=j_add(a5,(int16_t(d0) * 8)));
(d6=Orderzones::zone_InsertList(a0,a1,a4cur,a6,d6));
(d7=M68k::setw(d7,(d7 - 1)));
if((int16_t(d7) == -(1))) {
break;
}
}
(a5=ZoneBss::zone_OrderTable_vw);
(d0=Mem::w(j_add(a5,4)));
(a5=j_add(a5,(int16_t(d0) * 8)));
(a0=ZoneBss::Zone_FinalOrderTable_vw);
while(true){
Mem::ww(a0,Mem::uw(j_add(a5,2)));
(a0+=2);
(d0=Mem::w(j_add(a5,4)));
if((d0 < 0)) {
break;
}
(a5=ZoneBss::zone_OrderTable_vw);
(a5=j_add(a5,(int16_t(d0) * 8)));
}
Mem::wl(ZoneBss::Zone_EndOfListPtr_l,a0);
}

int32_t zone_InsertList(int32_t a0,int32_t a1,int32_t a4,int32_t a6,int32_t d6){
int32_t d7=0;
while(true){
int32_t d0=Mem::w(a0);
(a0+=2);
if((d0 < 0)) {
break;
}
(d0=M68k::setw(d0,j_shl(d0,4)));
int32_t d1=0;
(d1=M68k::setw(d1,Mem::uw(j_add(j_add(a1,int16_t(d0)),Defs::EdgeT_JoinZone_w))));
if((int16_t(d1) < 0)) {
(d7=M68k::setw(d7,j_add(d7,3)));
continue;
}
if(((d6 & j_shl(1,(d7 & 31))) == 0)) {
(d7=M68k::setw(d7,j_add(d7,3)));
continue;
}
(d7=M68k::setw(d7,j_add(d7,1)));
bool mustDo{};
if(((d6 & j_shl(1,(d7 & 31))) == 0)) {
(d6|=j_shl(1,(d7 & 31)));
int32_t d2=Mem::uw(HiresData::Plr_XOff_l);
int32_t d3=Mem::uw(HiresData::Plr_ZOff_l);
(d2=M68k::setw(d2,(d2 - Mem::uw(j_add(j_add(a1,int16_t(d0)),Defs::EdgeT_XPos_w)))));
(d3=M68k::setw(d3,(d3 - Mem::uw(j_add(j_add(a1,int16_t(d0)),Defs::EdgeT_ZPos_w)))));
(d2=M68k::muls(d2,Mem::w(j_add(j_add(a1,int16_t(d0)),Defs::EdgeT_ZLen_w))));
(d3=M68k::muls(d3,Mem::w(j_add(j_add(a1,int16_t(d0)),Defs::EdgeT_XLen_w))));
(d7=M68k::setw(d7,j_add(d7,1)));
(d2-=d3);
if((d2 <= 0)) {
(d7=M68k::setw(d7,j_add(d7,1)));
continue;
}
(d6|=j_shl(1,(d7 & 31)));
(mustDo=true);
}
else {
(d7=M68k::setw(d7,j_add(d7,1)));
if(((d6 & j_shl(1,(d7 & 31))) == 0)) {
(d7=M68k::setw(d7,j_add(d7,1)));
continue;
}
(mustDo=true);
}
if(mustDo) {
int32_t a3=ZoneBss::zone_OrderTable_vw;
(d0=Mem::w(a4));
bool isCloser=false;
if((d0 >= 0)) {
while(true){
if((int16_t(d1) == Mem::w(j_add(j_add(a3,(int16_t(d0) * 8)),2)))) {
(isCloser=true);
break;
}
(d0=Mem::w(j_add(a3,(int16_t(d0) * 8))));
if((d0 < 0)) {
break;
}
}
}
if(isCloser) {
int32_t d2=Mem::w(a4);
int32_t d5=Mem::uw(j_add(j_add(a3,(int16_t(d2) * 8)),4));
int32_t d3=Mem::w(j_add(a4,4));
if((d3 >= 0)) {
Mem::ww(j_add(a3,(int16_t(d3) * 8)),d2);
}
Mem::ww(j_add(j_add(a3,(int16_t(d2) * 8)),4),d3);
(d2=Mem::w(j_add(a3,(int16_t(d0) * 8))));
int32_t d4=Mem::uw(j_add(j_add(a3,(int16_t(d2) * 8)),4));
Mem::ww(j_add(a3,(int16_t(d5) * 8)),d2);
Mem::ww(j_add(j_add(a3,(int16_t(d5) * 8)),4),d4);
Mem::ww(j_add(a3,(int16_t(d4) * 8)),d5);
Mem::ww(j_add(j_add(a3,(int16_t(d2) * 8)),4),d5);
}
}
(d7=M68k::setw(d7,j_add(d7,1)));
}
Mem::wl(a6,d6);
return d6;
}

}