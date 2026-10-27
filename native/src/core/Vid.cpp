#include "original.hpp"
namespace Vid {
void Vid_CheckSettingsAdjust(int32_t a5){
Mem::wb(VidData::Vid_UpdatePalette_b,0);
if((Mem::b(j_add(a5,RawKeyMacros::RAWKEY_NUM_1)) != 0)) {
Mem::wb(j_add(a5,RawKeyMacros::RAWKEY_NUM_1),0);
if((Mem::w(VidData::Vid_BrightnessOffset_w) <= Vid::VID_BRIGHT_ADJ_MIN)) {
return ;
}
Mem::ww(VidData::Vid_BrightnessOffset_w,(Mem::w(VidData::Vid_BrightnessOffset_w) - Vid::VID_BRIGHT_ADJ_STEP));
Mem::wb(VidData::Vid_UpdatePalette_b,0xFF);
return ;
}
if((Mem::b(j_add(a5,RawKeyMacros::RAWKEY_NUM_2)) != 0)) {
Mem::wb(j_add(a5,RawKeyMacros::RAWKEY_NUM_2),0);
Mem::ww(VidData::Vid_BrightnessOffset_w,0);
Mem::wb(VidData::Vid_UpdatePalette_b,0xFF);
return ;
}
if((Mem::b(j_add(a5,RawKeyMacros::RAWKEY_NUM_3)) != 0)) {
Mem::wb(j_add(a5,RawKeyMacros::RAWKEY_NUM_3),0);
if((Mem::w(VidData::Vid_BrightnessOffset_w) >= Vid::VID_BRIGHT_ADJ_MAX)) {
return ;
}
Mem::ww(VidData::Vid_BrightnessOffset_w,j_add(Mem::w(VidData::Vid_BrightnessOffset_w),Vid::VID_BRIGHT_ADJ_STEP));
Mem::wb(VidData::Vid_UpdatePalette_b,0xFF);
return ;
}
if((Mem::b(j_add(a5,RawKeyMacros::RAWKEY_NUM_4)) != 0)) {
Mem::wb(j_add(a5,RawKeyMacros::RAWKEY_NUM_4),0);
if((Mem::w(VidData::Vid_ContrastAdjust_w) <= VidData::VID_CONTRAST_ADJ_MIN)) {
return ;
}
Mem::ww(VidData::Vid_ContrastAdjust_w,(Mem::w(VidData::Vid_ContrastAdjust_w) - VidData::VID_CONTRAST_ADJ_STEP));
Mem::wb(VidData::Vid_UpdatePalette_b,0xFF);
return ;
}
if((Mem::b(j_add(a5,RawKeyMacros::RAWKEY_NUM_5)) != 0)) {
Mem::wb(j_add(a5,RawKeyMacros::RAWKEY_NUM_5),0);
Mem::ww(VidData::Vid_ContrastAdjust_w,VidData::VID_CONTRAST_ADJ_DEF);
Mem::wb(VidData::Vid_UpdatePalette_b,0xFF);
return ;
}
if((Mem::b(j_add(a5,RawKeyMacros::RAWKEY_NUM_6)) != 0)) {
Mem::wb(j_add(a5,RawKeyMacros::RAWKEY_NUM_6),0);
if((Mem::w(VidData::Vid_ContrastAdjust_w) >= VidData::VID_CONTRAST_ADJ_MAX)) {
return ;
}
Mem::ww(VidData::Vid_ContrastAdjust_w,j_add(Mem::w(VidData::Vid_ContrastAdjust_w),VidData::VID_CONTRAST_ADJ_STEP));
Mem::wb(VidData::Vid_UpdatePalette_b,0xFF);
return ;
}
if((Mem::b(j_add(a5,RawKeyMacros::RAWKEY_NUM_7)) != 0)) {
Mem::wb(j_add(a5,RawKeyMacros::RAWKEY_NUM_7),0);
if((Mem::b(VidData::Vid_GammaLevel_b) == 0)) {
return ;
}
Mem::wb(VidData::Vid_GammaLevel_b,(Mem::ub(VidData::Vid_GammaLevel_b) - 1));
Mem::wb(VidData::Vid_UpdatePalette_b,0xFF);
return ;
}
if((Mem::b(j_add(a5,RawKeyMacros::RAWKEY_NUM_8)) != 0)) {
Mem::wb(j_add(a5,RawKeyMacros::RAWKEY_NUM_8),0);
Mem::wb(VidData::Vid_GammaLevel_b,0);
Mem::wb(VidData::Vid_UpdatePalette_b,0xFF);
return ;
}
if((Mem::b(j_add(a5,RawKeyMacros::RAWKEY_NUM_9)) != 0)) {
Mem::wb(j_add(a5,RawKeyMacros::RAWKEY_NUM_9),0);
if((int8_t(Mem::b(VidData::Vid_GammaLevel_b)) >= 8)) {
return ;
}
Mem::wb(VidData::Vid_GammaLevel_b,j_add(Mem::ub(VidData::Vid_GammaLevel_b),1));
Mem::wb(VidData::Vid_UpdatePalette_b,0xFF);
}
}

}