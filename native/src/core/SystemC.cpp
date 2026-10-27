#include "original.hpp"
namespace SystemC {
bool Sys_CheckTimeGE(int32_t now,int32_t mark){
int64_t nowHi=(Mem::l(now) & 0xFFFFFFFFL);
int64_t markHi=(Mem::l(mark) & 0xFFFFFFFFL);
int64_t nowLo=(Mem::l(j_add(now,4)) & 0xFFFFFFFFL);
int64_t markLo=(Mem::l(j_add(mark,4)) & 0xFFFFFFFFL);
return ((nowHi > markHi) || ((nowHi == markHi) && (nowLo >= markLo)));
}

void Sys_AddTime(int32_t mark,int32_t ticks){
int64_t v=(j_shl(int64_t(Mem::l(mark)),32) | (Mem::l(j_add(mark,4)) & 0xFFFFFFFFL));
(v+=(ticks & 0xFFFFFFFFL));
Mem::wl(mark,int32_t(j_ushr(v,32)));
Mem::wl(j_add(mark,4),int32_t(v));
}

int32_t Sys_MarkTime(int32_t dest){
return SysTimer::readEClock(dest);
}

int64_t Sys_TimeDiff(int32_t start,int32_t end){
int64_t end64=(j_shl(int64_t(Mem::l(end)),32) | (Mem::l(j_add(end,4)) & 0xFFFFFFFFL));
int64_t start64=(j_shl(int64_t(Mem::l(start)),32) | (Mem::l(j_add(start,4)) & 0xFFFFFFFFL));
int64_t diff=(end64 - start64);
return diff;
}

void Sys_FrameLap(){
SysTimer::readEClock(SystemBss::Sys_FrameTimeECV_q);
int32_t frameTime=(Mem::l(j_add(SystemBss::Sys_FrameTimeECV_q,4)) - Mem::l(j_add(SystemBss::Sys_PrevFrameTimeECV_q,4)));
Mem::wl(SystemBss::Sys_PrevFrameTimeECV_q,Mem::l(SystemBss::Sys_FrameTimeECV_q));
Mem::wl(j_add(SystemBss::Sys_PrevFrameTimeECV_q,4),Mem::l(j_add(SystemBss::Sys_FrameTimeECV_q,4)));
Mem::wl(j_add(SystemBss::Sys_FrameTimes_vl,(4 * (Mem::l(SystemBss::Sys_FrameNumber_l) & 7))),frameTime);
Mem::wl(SystemBss::Sys_FrameNumber_l,j_add(Mem::l(SystemBss::Sys_FrameNumber_l),1));
}

void Sys_EvalFPS(){
if((Mem::b(ControlloopData::Prefs_DisplayFPS_b) == 0)) {
return ;
}
int64_t avg=0;
for(int32_t x=0;(x < 8);++(x)){
(avg=(j_add(avg,(Mem::l(j_add(SystemBss::Sys_FrameTimes_vl,(4 * x))) & 0xFFFFFFFFL)) & 0xFFFFFFFFL));
}
(avg=j_ushr(((avg * (Mem::l(SystemBss::Sys_ECVToMsFactor_l) & 0xFFFFFFFFL)) & 0xFFFFFFFFL),19));
if((avg == 0)) {
return ;
}
int32_t fps10x=(j_div(10000,int32_t((avg & 0xFFFF))) & 0xFFFF);
Mem::ww(SystemBss::Sys_FPSFracAvg_w,j_mod(fps10x,10));
Mem::ww(SystemBss::Sys_FPSIntAvg_w,j_div(fps10x,10));
}

void Sys_ReadMouse(){
int32_t joy=(CustomChips::joy0dat & 0xFFFF);
int32_t diffY=int16_t(j_ushr(joy,8));
(diffY=int16_t((diffY - int16_t(SystemC::oldMouseY))));
if((diffY >= 127)) {
(diffY=int16_t((diffY - 255)));
}
else if((diffY < -(127))) {
(diffY=int16_t(j_add(diffY,255)));
}
(SystemC::oldMouseY=((SystemC::oldMouseY & 0xff00) | (j_add(diffY,SystemC::oldMouseY) & 0xff)));
Mem::ww(HiresData::Sys_MouseY,j_add(Mem::uw(HiresData::Sys_MouseY),diffY));
int32_t counterX=(joy & 0xff);
int32_t diffX=int16_t((counterX - SystemC::oldCounterX));
if((diffX >= 127)) {
(diffX=int16_t((diffX - 255)));
}
else if((diffX < -(127))) {
(diffX=int16_t(j_add(diffX,255)));
}
int32_t newMouseX=int16_t(j_add(diffX,SystemC::oldCounterX));
(SystemC::oldCounterX=(newMouseX & 0xff));
(SystemC::oldMouseX2=(j_add(SystemC::oldMouseX2,diffX) & 2047));
Mem::ww(HiresData::Vis_AngPos_w,j_add(Mem::uw(HiresData::Vis_AngPos_w),j_shl(diffX,2)));
}

void Sys_ClearKeyboard(){
Sys::Sys_MemFillLong(TablesBss::KeyMap_vb,0,j_div(256,4));
}

int32_t Sys_Init(){
Mem::wb(SystemBss::Sys_Move16_b,0xFF);
Mem::wb(VidBss::Vid_FullScreenTemp_b,0xFF);
Mem::wb(SystemBss::Sys_CPU_68060_b,0);
(SystemC::Sys_EClockRate=SystemC::Sys_MarkTime(SystemBss::Sys_PrevFrameTimeECV_q));
Mem::wl(SystemBss::Sys_ECVToMsFactor_l,int32_t(j_div(j_shl(1000LL,16),(SystemC::Sys_EClockRate & 0xFFFFFFFFL))));
if((DrawC::Draw_Init() == 0)) {
SystemC::sys_ReleaseHardware();
return 0;
}
GameC::Game_Init();
return 1;
}

void Sys_Done(){
DrawC::Draw_Shutdown();
SystemC::sys_ReleaseHardware();
GameC::Game_Done();
}

int32_t Sys_OpenLibs(){
return 1;
}

void Sys_CloseLibs(){
}

void sys_ReleaseHardware(){
}

void Sys_ShowFPS(){
if((Mem::b(ControlloopData::Prefs_DisplayFPS_b) == 0)) {
return ;
}
}

}