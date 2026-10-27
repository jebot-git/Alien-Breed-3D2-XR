#include "original.hpp"
namespace ScreenC {
int32_t hostColor(int32_t idx){
return ScreenC::hostPalette[(idx & 0xFF)];
}

void Vid_LoadMainPalette(){
Mem::wl(VidBss::Vid_LoadRGB32Struct_vl,(j_shl(256,16) | 0));
int32_t c=0;
int64_t gun{};
if((Mem::ub(VidData::Vid_GammaLevel_b) > 0)) {
int32_t gamma=j_add(VidData::Vid_GammaIncTables_vb,j_shl(((Mem::ub(VidData::Vid_GammaLevel_b) - 1) & 7),8));
for(;(c < 768);++(c)){
(gun=j_add((int64_t(Mem::ub(j_add(gamma,Mem::uw(j_add(DrawData::draw_Palette_vw,(c * 2)))))) * Mem::uw(VidData::Vid_ContrastAdjust_w)),Mem::w(VidData::Vid_BrightnessOffset_w)));
(gun=((gun < 0)?0:((gun > 65535)?65535:gun)));
Mem::wl(j_add(VidBss::Vid_LoadRGB32Struct_vl,(j_add(c,1) * 4)),int32_t((j_shl(gun,16) | gun)));
}
}
else {
for(;(c < 768);++(c)){
(gun=j_add((int64_t(Mem::uw(j_add(DrawData::draw_Palette_vw,(c * 2)))) * Mem::uw(VidData::Vid_ContrastAdjust_w)),Mem::w(VidData::Vid_BrightnessOffset_w)));
(gun=((gun < 0)?0:((gun > 65535)?65535:gun)));
Mem::wl(j_add(VidBss::Vid_LoadRGB32Struct_vl,(j_add(c,1) * 4)),int32_t((j_shl(gun,16) | gun)));
}
}
Mem::wl(j_add(VidBss::Vid_LoadRGB32Struct_vl,(j_add(c,1) * 4)),0);
ScreenC::LoadRGB32();
}

void LoadRGB32(){
for(int32_t i=0;(i < 256);(i)++){
int32_t base=j_add(j_add(VidBss::Vid_LoadRGB32Struct_vl,4),((i * 3) * 4));
int32_t r=(j_ushr(Mem::l(base),24) & 0xFF);
int32_t g=(j_ushr(Mem::l(j_add(base,4)),24) & 0xFF);
int32_t b=(j_ushr(Mem::l(j_add(base,8)),24) & 0xFF);
(ScreenC::hostPalette[i]=(((int32_t(0xFF000000u) | j_shl(r,16)) | j_shl(g,8)) | b));
}
}

}