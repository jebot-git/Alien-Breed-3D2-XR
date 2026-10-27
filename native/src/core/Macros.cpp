#include "original.hpp"
namespace Macros {
void FREE_OBJ(int32_t aN){
Mem::ww(j_add(aN,Defs::ObjT_ZoneID_w),-(1));
}

void FREE_OBJ_2(int32_t aN,int32_t off){
Mem::ww(j_add(j_add(aN,Defs::ObjT_ZoneID_w),off),-(1));
}

void FREE_ENT(int32_t aN){
Mem::ww(j_add(aN,Defs::ObjT_ZoneID_w),-(1));
Mem::ww(j_add(aN,Defs::EntT_ZoneID_w),-(1));
}

void FREE_ENT_2(int32_t aN,int32_t off){
Mem::ww(j_add(j_add(aN,Defs::ObjT_ZoneID_w),off),-(1));
Mem::ww(j_add(j_add(aN,Defs::EntT_ZoneID_w),off),-(1));
}

void SET_MEM_BIT(int32_t bit,int32_t addr){
int32_t a=(j_add(addr,3) - j_shr(bit,3));
Mem::wb(a,(Mem::ub(a) | j_shl(1,(bit & 7))));
}

}