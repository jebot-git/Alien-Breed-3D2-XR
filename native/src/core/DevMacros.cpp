#include "original.hpp"
namespace DevMacros {
bool DEV_TEST(int32_t flagsAddr,int32_t bit){
return ((Mem::ub((j_add(flagsAddr,3) - j_shr(bit,3))) & j_shl(1,(bit & 7))) != 0);
}

void DEV_ENABLE(int32_t flagsAddr,int32_t bit){
int32_t a=(j_add(flagsAddr,3) - j_shr(bit,3));
Mem::wb(a,(Mem::ub(a) | j_shl(1,(bit & 7))));
}

void DEV_DISABLE(int32_t flagsAddr,int32_t bit){
int32_t a=(j_add(flagsAddr,3) - j_shr(bit,3));
Mem::wb(a,(Mem::ub(a) & ~(j_shl(1,(bit & 7)))));
}

void DEV_TOGGLE(int32_t flagsAddr,int32_t bit){
int32_t a=(j_add(flagsAddr,3) - j_shr(bit,3));
Mem::wb(a,(Mem::ub(a) ^ j_shl(1,(bit & 7))));
}

}