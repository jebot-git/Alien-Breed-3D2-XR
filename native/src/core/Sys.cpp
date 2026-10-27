#include "original.hpp"
namespace Sys {
void Sys_MemFillLong(int32_t a0,int32_t d0,int32_t d1){
(d1=M68k::setw(d1,j_ushr((d1 & 0xFFFF),2)));
(d1=M68k::setw(d1,(d1 - 1)));
do {
Mem::wl(a0,d0);
(a0+=4);
Mem::wl(a0,d0);
(a0+=4);
Mem::wl(a0,d0);
(a0+=4);
Mem::wl(a0,d0);
(a0+=4);
(d1=M68k::setw(d1,(d1 - 1)));
}
while((int16_t(d1) != -(1)));
}

void Sys_CopyMemMove16(int32_t d0,int32_t a0,int32_t a1){
(a0=(j_add(a0,15) & int32_t(0xFFFFFFF0u)));
(a1=(j_add(a1,15) & int32_t(0xFFFFFFF0u)));
(d0=j_ushr(d0,6));
(d0-=1);
do {
Mem::copy(a0,a1,16);
(a0+=16);
(a1+=16);
Mem::copy(a0,a1,16);
(a0+=16);
(a1+=16);
Mem::copy(a0,a1,16);
(a0+=16);
(a1+=16);
Mem::copy(a0,a1,16);
(a0+=16);
(a1+=16);
(d0=M68k::setw(d0,(d0 - 1)));
}
while((int16_t(d0) != -(1)));
}

void Sys_FatalError(int32_t a0,int32_t a1){
(Sys::putch_a3=SystemBss::sys_ErrorBuffer_vb);
Mem::wb(SystemBss::sys_ErrorHeight_b,j_add(Sys::SYS_ALERT_Y_SPACE,2));
Sys::startline();
ExecLib::RawDoFmt(a0,a1,Sys::putch);
throw std::runtime_error("original engine error");
}

void putch(int32_t d0){
if((int8_t(d0) == 0)) {
Mem::ww(Sys::putch_a3,0);
return ;
}
if((int8_t(d0) == 10)) {
Mem::wb(Sys::putch_a3,0);
(Sys::putch_a3+=1);
Mem::wb(Sys::putch_a3,1);
(Sys::putch_a3+=1);
Sys::startline();
return ;
}
Mem::wb(Sys::putch_a3,d0);
(Sys::putch_a3+=1);
}

void startline(){
Mem::ww(Sys::putch_a3,10);
(Sys::putch_a3+=2);
Mem::wb(Sys::putch_a3,Mem::ub(SystemBss::sys_ErrorHeight_b));
(Sys::putch_a3+=1);
Mem::wb(SystemBss::sys_ErrorHeight_b,j_add(Mem::ub(SystemBss::sys_ErrorHeight_b),Sys::SYS_ALERT_Y_SPACE));
}

void Sys_DisplayError(){
int32_t d1=0;
(d1=((d1 & ~(0xFF)) | Mem::ub(SystemBss::sys_ErrorHeight_b)));
if((d1 == 0)) {
return ;
}
int32_t d0=IntuitionLib::RECOVERY_ALERT;
int32_t a0=SystemBss::sys_ErrorBuffer_vb;
IntuitionLib::DisplayAlert(d0,a0,d1);
}

int32_t Sys_AllocVec(int32_t d0,int32_t d1){
Mem::wl(Sys::allocVecArgs,d0);
Mem::wl(j_add(Sys::allocVecArgs,4),d1);
int32_t r=ExecLib::AllocVec(d0,d1);
if((r != 0)) {
return r;
}
Sys::Sys_FatalError(Sys::errorfmt,Sys::allocVecArgs);
return 0;
}

void gameQuitAfterFatal(){
Controlloop::Game_Quit();
Sys::Sys_DisplayError();
}

}