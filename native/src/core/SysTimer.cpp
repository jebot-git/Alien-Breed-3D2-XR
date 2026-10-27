#include "original.hpp"
namespace SysTimer {
int32_t readEClock(int32_t dest){
int64_t ticks=j_div((j_div(j_nanoTime(),1000LL) * SysTimer::ECLOCK_RATE),1000000LL);
Mem::wl(dest,int32_t(j_ushr(ticks,32)));
Mem::wl(j_add(dest,4),int32_t(ticks));
return SysTimer::ECLOCK_RATE;
}

void GetSysTime(int32_t dest){
int64_t nanos=j_nanoTime();
Mem::wl(j_add(dest,SysTimer::TV_SECS),int32_t(j_div(nanos,1000000000LL)));
Mem::wl(j_add(dest,SysTimer::TV_MICRO),int32_t(j_mod(j_div(nanos,1000LL),1000000LL)));
}

void SubTime(int32_t dest,int32_t src){
int64_t destMicro=(Mem::l(j_add(dest,SysTimer::TV_MICRO)) & 0xFFFFFFFFL);
int64_t srcMicro=(Mem::l(j_add(src,SysTimer::TV_MICRO)) & 0xFFFFFFFFL);
int64_t destSecs=(Mem::l(j_add(dest,SysTimer::TV_SECS)) & 0xFFFFFFFFL);
int64_t srcSecs=(Mem::l(j_add(src,SysTimer::TV_SECS)) & 0xFFFFFFFFL);
if((destMicro < srcMicro)) {
(destSecs-=1);
(destMicro+=1000000LL);
}
(destMicro-=srcMicro);
(destSecs-=srcSecs);
Mem::wl(j_add(dest,SysTimer::TV_SECS),int32_t(destSecs));
Mem::wl(j_add(dest,SysTimer::TV_MICRO),int32_t(destMicro));
}

}