#include "original.hpp"
namespace M68k {
int32_t swap(int32_t d){
return (j_shl(d,16) | j_ushr(d,16));
}

int32_t setw(int32_t reg,int32_t v){
return ((reg & int32_t(0xFFFF0000u)) | (v & 0xFFFF));
}

int32_t setb(int32_t reg,int32_t v){
return ((reg & int32_t(0xFFFFFF00u)) | (v & 0xFF));
}

int32_t w(int32_t reg){
return int16_t(reg);
}

int32_t uw(int32_t reg){
return (reg & 0xFFFF);
}

int32_t b(int32_t reg){
return int8_t(reg);
}

int32_t ub(int32_t reg){
return (reg & 0xFF);
}

int32_t extw(int32_t reg){
return ((reg & int32_t(0xFFFF0000u)) | (int8_t(reg) & 0xFFFF));
}

int32_t extl(int32_t reg){
return int16_t(reg);
}

int32_t muls(int32_t dN,int32_t src){
return (int16_t(dN) * int16_t(src));
}

int32_t mulu(int32_t dN,int32_t src){
return ((dN & 0xFFFF) * (src & 0xFFFF));
}

int32_t divs(int32_t dN,int32_t src){
int32_t divisor=int16_t(src);
int32_t q=j_div(dN,divisor);
int32_t r=j_mod(dN,divisor);
if(((q < -(32768)) || (q > 32767))) {
return dN;
}
return (j_shl(r,16) | (q & 0xFFFF));
}

int32_t divu(int32_t dN,int32_t src){
int64_t dividend=(dN & 0xFFFFFFFFL);
int32_t divisor=(src & 0xFFFF);
if((divisor == 0)) {
throw std::runtime_error("divu par zéro");
}
int64_t q=j_div(dividend,divisor);
int64_t r=j_mod(dividend,divisor);
if((q > 0xFFFF)) {
return dN;
}
return int32_t((j_shl(r,16) | q));
}

int32_t asrw(int32_t reg,int32_t n){
return M68k::setw(reg,j_shr(int16_t(reg),n));
}

int32_t lsrw(int32_t reg,int32_t n){
return M68k::setw(reg,j_ushr((reg & 0xFFFF),n));
}

int32_t lslw(int32_t reg,int32_t n){
return M68k::setw(reg,j_shl((reg & 0xFFFF),n));
}

int32_t addw(int32_t reg,int32_t v){
return M68k::setw(reg,j_add(reg,v));
}

int32_t subw(int32_t reg,int32_t v){
return M68k::setw(reg,(reg - v));
}

int32_t negw(int32_t reg){
return M68k::setw(reg,-(int16_t(reg)));
}

}