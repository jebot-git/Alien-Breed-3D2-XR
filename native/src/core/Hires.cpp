#include "original.hpp"
namespace Hires {
void draw_FloorLine(int32_t d0,int32_t a3){
int32_t a0=Mem::l(DrawBss::Draw_FloorTexturesPtr_l);
(a0+=int16_t(Mem::uw(HiresData::whichtile)));
int32_t d1=Mem::uw(HiresData::lighttype);
Mem::wl(HiresData::draw_Distance_l,d0);
int32_t d2=d0;
(d2=j_shr(d2,2));
(d2=j_shr(d2,8));
(d1=M68k::setw(d1,j_add(d1,5)));
(d1=M68k::setw(d1,j_add(d1,d2)));
if((int16_t(d1) < 0)) {
(d1=0);
}
if((int16_t(d1) > 28)) {
(d1=M68k::setw(d1,28));
}
int32_t a1=Mem::l(DrawBss::Draw_TexturePalettePtr_l);
(a1+=(256 * 32));
(a1+=int16_t(Hires::FLOORBRIGHT[int16_t(d1)]));
Hires::pastfloorbright(d0,a0,a1,a3);
}

void pastfloorbright(int32_t d0,int32_t a0,int32_t a1,int32_t a3){
int32_t d1=M68k::muls(d0,Mem::w(HireswallData::Vis_CosVal_w));
int32_t d2=M68k::muls(d0,Mem::w(HireswallData::Vis_SinVal_w));
(d2=-(d2));
(d2=j_shr(d2,2));
(d1=j_shr(d1,2));
int32_t d3=Mem::uw(HiresData::scaleval);
if((int16_t(d3) != 0)) {
if((int16_t(d3) > 0)) {
(d1=j_shl(d1,(int16_t(d3) & 31)));
(d2=j_shl(d2,(int16_t(d3) & 31)));
}
else {
int32_t sh=(-(int16_t(d3)) & 31);
(d1=j_shr(d1,sh));
(d2=j_shr(d2,sh));
}
}
(d3=d1);
int32_t d6=d3;
int32_t d5=d3;
(d6=j_shr(d6,1));
(d3=j_add(d3,d6));
(d3=j_shr(d3,1));
int32_t d4=d2;
(d6=d4);
(d6=j_shr(d6,1));
(d6=j_add(d6,d4));
(d6=j_shr(d6,1));
(d4=j_add(d4,d3));
(d4=-(d4));
(d5=(d5 - d6));
(d4=j_add(d4,Mem::l(HiresData::sxoff)));
(d5=j_add(d5,Mem::l(HiresData::szoff)));
if((Mem::b(VidBss::Vid_FullScreen_b) != 0)) {
(d6=M68k::setw(0,Mem::uw(HiresData::leftedge)));
if((int16_t(d6) != 0)) {
(d6=M68k::muls(d6,1229));
(d6=j_shr(d6,8));
(d6=j_shr(d6,3));
int32_t sa4=d1;
int32_t sa5=d2;
(d1=(d1 * d6));
(d1=j_shr(d1,7));
(d4=j_add(d4,d1));
(d2=(d2 * d6));
(d2=j_shr(d2,7));
(d5=j_add(d5,d2));
(d1=sa4);
(d2=sa5);
(d6=M68k::setw(d6,Mem::uw(HiresData::leftedge)));
}
Mem::ww(HiresData::startsmoothx,d4);
Mem::ww(HiresData::startsmoothz,d5);
(d4=j_shr(d4,8));
(d5=j_shl(d5,8));
(d5=M68k::setw(d5,d4));
(d1=j_shr(d1,6));
(d2=j_shr(d2,6));
(d1=(d1 * 77));
(d2=(d2 * 77));
(d1=j_shr(d1,8));
(d2=j_shr(d2,8));
}
else {
(d6=M68k::setw(0,Mem::uw(HiresData::leftedge)));
if((int16_t(d6) != 0)) {
int32_t sa4=d1;
int32_t sa5=d2;
(d1=(d1 * d6));
(d1=j_shr(d1,7));
(d4=j_add(d4,d1));
(d2=(d2 * d6));
(d2=j_shr(d2,7));
(d5=j_add(d5,d2));
(d1=sa4);
(d2=sa5);
(d6=M68k::setw(d6,Mem::uw(HiresData::leftedge)));
}
Mem::ww(HiresData::startsmoothx,d4);
Mem::ww(HiresData::startsmoothz,d5);
(d4=j_shr(d4,8));
(d5=j_shl(d5,8));
(d5=M68k::setw(d5,d4));
(d1=j_shr(d1,7));
(d2=j_shr(d2,7));
}
(d2=j_shl(d2,8));
(d1=j_shr(d1,8));
(d2=M68k::setw(d2,d1));
(d1=0x3fff3fff);
(d5=(d5 & d1));
int32_t a2=int16_t(d6);
(d3=M68k::setw(d3,Mem::uw(HiresData::rightedge)));
(a3=j_add(a3,a2));
int32_t d7=M68k::setw(0,d3);
(d7=M68k::setw(d7,(d7 - a2)));
if((Mem::b(HiresData::draw_UseWater_b) != 0)) {
Hires::draw_WaterSurface(d1,d2,d5,d7,a3);
return ;
}
DrawFloor::draw_GoraudFloor(d1,d2,d5,d7,a0,a1,a3);
}

void draw_WaterSurface(int32_t d1,int32_t d2,int32_t d5,int32_t d7,int32_t a3){
int32_t d4=d1;
(d5=j_add(d5,Mem::l(HiresData::wateroff)));
int32_t a1=Mem::l(DrawBss::Draw_TexturePalettePtr_l);
(a1+=(256 * 16));
int32_t d0=Mem::l(HiresData::draw_Distance_l);
(d0=(d0 & 0x3f00));
(d0=M68k::setw(d0,j_add(d0,d0)));
if((int16_t(d0) >= (5 * 512))) {
(d0=M68k::setw(d0,(5 * 512)));
}
(a1+=int16_t(d0));
(d0=Mem::l(HiresData::draw_Distance_l));
(d0=M68k::setw(d0,j_shl((d0 & 0xFFFF),7)));
(d0=M68k::setw(d0,j_add(d0,Mem::uw(HiresData::wtan))));
(d0=M68k::setw(d0,(d0 & 8191)));
int32_t a0=TablesData::SinCosTable_vw;
(d0=M68k::setw(d0,Mem::uw(j_add(a0,(d0 & 0xFFFF)))));
(d0=int16_t(d0));
int32_t d3=Mem::l(HiresData::draw_Distance_l);
(d3=M68k::setw(d3,j_add(d3,300)));
(d0=M68k::divs(d0,d3));
(d0=M68k::setw(d0,j_shr(int16_t(d0),5)));
(d0=M68k::setw(d0,j_add(d0,4)));
if((int16_t(d0) >= int16_t(Mem::uw(HiresData::disttobot)))) {
(d0=M68k::setw(d0,Mem::uw(HiresData::disttobot)));
(d0=M68k::setw(d0,(d0 - 1)));
}
if((Mem::b(VidBss::Vid_DoubleHeight_b) != 0)) {
(d0=M68k::setb(d0,(d0 & 0xFE)));
}
(d0=M68k::muls(d0,Hires::SCREEN_WIDTH));
if((int16_t(Mem::uw(HiresData::above)) != 0)) {
(d0=-(d0));
}
int32_t a6=d0;
(a0=Mem::l(HiresData::draw_WaterFramePtr_l));
(d3=M68k::setw(d3,Mem::uw(HiresData::startsmoothx)));
(d7=M68k::setw(d7,(d7 - 1)));
while((int16_t(d7) != -(1))){
(d3=M68k::setw(d3,d5));
int32_t d6=d5;
(d3=M68k::setw(d3,j_ushr((d3 & 0xFFFF),8)));
(d6=M68k::swap(d6));
(d6=M68k::setb(d6,d3));
(d0=M68k::setw(d0,Mem::uw(j_add(a0,(int16_t(d6) * 4)))));
(d0=M68k::setw(d0,j_add(d0,d0)));
(d5+=d2);
(d0=M68k::setb(d0,Mem::ub(j_add(a3,int16_t(a6)))));
(d5&=d4);
Mem::wb(a3,Mem::ub(j_add(a1,(d0 & 0xFFFF))));
(a3+=1);
(d7=M68k::setw(d7,(d7 - 1)));
}
}

int32_t pastFlats(int32_t a0){
int32_t d0{};
int32_t d1{};
int32_t d3{};
int32_t d6{};
int32_t d7{};
int32_t a2{};
int32_t a4{};
int32_t a6{};
(a0+=2);
Mem::ww(HiresData::linedir,Hires::SCREEN_WIDTH);
(a6=Mem::l(VidBss::Vid_FastBufferPtr_l));
(a6=j_add(a6,Mem::l(HireswallData::BIGMIDDLEY)));
(d6=M68k::setw(0,Mem::uw(a0)));
(a0+=2);
(d6=M68k::setw(d6,j_add(d6,Mem::uw(HiresData::SMALLIT))));
Mem::ww(HiresData::scaleval,d6);
(d6=M68k::setw(d6,Mem::uw(a0)));
(a0+=2);
Mem::ww(HiresData::whichtile,d6);
(d6=M68k::setw(d6,Mem::uw(a0)));
(a0+=2);
(d6=M68k::setw(d6,j_add(d6,Mem::uw(HiresData::Zone_Bright_w))));
Mem::ww(HiresData::lighttype,d6);
(d6=M68k::setw(d6,Mem::uw(HiresData::above)));
if((int16_t(d6) != 0)) {
Mem::ww(HiresData::linedir,-(Hires::SCREEN_WIDTH));
(a6=(a6 - Hires::SCREEN_WIDTH));
}
(d6=M68k::setw(0,Mem::uw(HiresData::Plr_XOff_l)));
(d7=M68k::setw(0,Mem::uw(HiresData::Plr_ZOff_l)));
(d7=M68k::setw(d7,j_add(d7,Mem::uw(HiresData::xwobxoff))));
(d6=M68k::setw(d6,j_add(d6,Mem::uw(HiresData::xwobzoff))));
(d6=M68k::swap(d6));
(d7=M68k::swap(d7));
(d6=M68k::setw(d6,0));
(d7=M68k::setw(d7,0));
(d6=j_shr(d6,1));
(d7=j_shr(d7,1));
(d3=M68k::setw(0,Mem::uw(HiresData::scaleval)));
if((int16_t(d3) != 0)) {
if((int16_t(d3) > 0)) {
(d6=j_shl(d6,(int16_t(d3) & 31)));
(d7=j_shl(d7,(int16_t(d3) & 31)));
}
else {
int32_t sh=(-(int16_t(d3)) & 31);
(d6=j_shr(d6,sh));
(d7=j_shr(d7,sh));
}
}
Mem::wl(HiresData::sxoff,d6);
Mem::wl(HiresData::szoff,d7);
if((Mem::b(HiresData::drawit) == 0)) {
return a0;
}
int32_t savedA0=a0;
(a4=TablesBss::LeftSideTable_vw);
(d1=M68k::setw(0,Mem::uw(HiresData::top)));
if((Mem::b(VidBss::Vid_DoubleHeight_b) != 0)) {
int32_t dlin=M68k::setw(0,Mem::uw(HiresData::linedir));
Mem::ww(HiresData::linedir,j_add(Mem::uw(HiresData::linedir),dlin));
if((int16_t(Mem::uw(HiresData::above)) != 0)) {
(d7=M68k::setw(0,Mem::uw(HireswallData::Vid_CentreY_w)));
if(((d7 & 1) == 0)) {
(a6=(a6 - Hires::SCREEN_WIDTH));
}
(d7=M68k::setw(d7,(d7 - 1)));
(d7=M68k::setw(d7,(d7 - d1)));
Mem::ww(HiresData::disttobot,d7);
(d7=M68k::setw(0,Mem::uw(HiresData::bottom)));
(d3=M68k::setw(0,Mem::uw(HireswallData::Vid_CentreY_w)));
int32_t d4=M68k::setw(0,d3);
(d3=M68k::setw(d3,(d3 - Mem::uw(HireswallData::draw_TopClip_w))));
(d4=M68k::setw(d4,(d4 - Mem::uw(HireswallData::draw_BottomClip_w))));
if((int16_t(d1) >= int16_t(d3))) return savedA0;
if((int16_t(d7) < int16_t(d4))) return savedA0;
if((int16_t(d1) < int16_t(d4))) (d1=M68k::setw(d1,d4));
if((int16_t(d7) >= int16_t(d3))) (d7=M68k::setw(d7,d3));
}
else {
(d7=M68k::setw(0,Mem::uw(HireswallData::Vid_BottomY_w)));
int32_t d4=M68k::setw(0,Mem::uw(HireswallData::Vid_CentreY_w));
if(((d4 & 1) != 0)) {
(a6=j_add(a6,Hires::SCREEN_WIDTH));
}
(d7=M68k::setw(d7,(d7 - d4)));
(d7=M68k::setw(d7,(d7 - 1)));
(d7=M68k::setw(d7,(d7 - d1)));
Mem::ww(HiresData::disttobot,d7);
(d7=M68k::setw(0,Mem::uw(HiresData::bottom)));
(d4=M68k::setw(0,Mem::uw(HireswallData::draw_BottomClip_w)));
(d4=M68k::setw(d4,(d4 - Mem::uw(HireswallData::Vid_CentreY_w))));
if((int16_t(d1) >= int16_t(d4))) return savedA0;
(d3=M68k::setw(0,Mem::uw(HireswallData::draw_TopClip_w)));
(d3=M68k::setw(d3,(d3 - Mem::uw(HireswallData::Vid_CentreY_w))));
if((int16_t(d1) < int16_t(d3))) (d1=M68k::setw(d1,d3));
if((int16_t(d7) <= int16_t(d3))) return savedA0;
if((int16_t(d7) >= int16_t(d4))) (d7=M68k::setw(d7,d4));
}
(a4=j_add(a4,(int16_t(d1) * 2)));
(d7=M68k::setw(d7,j_add(d7,1)));
(d7=M68k::setw(d7,(d7 - d1)));
(d7=M68k::setw(d7,j_shr(int16_t(d7),1)));
if((int16_t(d7) <= 0)) return savedA0;
(d1=M68k::setw(d1,j_shr(int16_t(d1),1)));
(d0=M68k::setw(0,Mem::uw(HiresData::View2FloorDist)));
if((Mem::b(VidBss::Vid_FullScreen_b) != 0)) {
(d0=M68k::muls(d0,107));
}
else {
(d0=int16_t(d0));
(d0=j_shl(d0,6));
}
(a2=d0);
(d0=M68k::setw(d0,d1));
if((int16_t(d0) == 0)) (d0=1);
(d0=M68k::setw(d0,j_add(d0,d0)));
(d1=M68k::muls(Mem::uw(HiresData::linedir),d1));
(a6=j_add(a6,d1));
Mem::ww(HiresData::tonextline,4);
}
else {
if((int16_t(Mem::uw(HiresData::above)) != 0)) {
(d7=M68k::setw(0,Mem::uw(HireswallData::Vid_CentreY_w)));
(d7=M68k::setw(d7,(d7 - 1)));
(d7=M68k::setw(d7,(d7 - d1)));
Mem::ww(HiresData::disttobot,d7);
(d7=M68k::setw(0,Mem::uw(HiresData::bottom)));
(d3=M68k::setw(0,Mem::uw(HireswallData::Vid_CentreY_w)));
int32_t d4=M68k::setw(0,d3);
(d3=M68k::setw(d3,(d3 - Mem::uw(HireswallData::draw_TopClip_w))));
(d4=M68k::setw(d4,(d4 - Mem::uw(HireswallData::draw_BottomClip_w))));
if((int16_t(d1) >= int16_t(d3))) return savedA0;
if((int16_t(d7) < int16_t(d4))) return savedA0;
if((int16_t(d1) < int16_t(d4))) (d1=M68k::setw(d1,d4));
if((int16_t(d7) >= int16_t(d3))) (d7=M68k::setw(d7,d3));
}
else {
(d7=M68k::setw(0,Mem::uw(HireswallData::Vid_BottomY_w)));
(d7=M68k::setw(d7,(d7 - Mem::uw(HireswallData::Vid_CentreY_w))));
(d7=M68k::setw(d7,(d7 - 1)));
(d7=M68k::setw(d7,(d7 - d1)));
Mem::ww(HiresData::disttobot,d7);
(d7=M68k::setw(0,Mem::uw(HiresData::bottom)));
int32_t d4=M68k::setw(0,Mem::uw(HireswallData::draw_BottomClip_w));
(d4=M68k::setw(d4,(d4 - Mem::uw(HireswallData::Vid_CentreY_w))));
if((int16_t(d1) >= int16_t(d4))) return savedA0;
(d3=M68k::setw(0,Mem::uw(HireswallData::draw_TopClip_w)));
(d3=M68k::setw(d3,(d3 - Mem::uw(HireswallData::Vid_CentreY_w))));
if((int16_t(d1) < int16_t(d3))) (d1=M68k::setw(d1,d3));
if((int16_t(d7) <= int16_t(d3))) return savedA0;
if((int16_t(d7) >= int16_t(d4))) (d7=M68k::setw(d7,d4));
}
(a4=j_add(a4,(int16_t(d1) * 2)));
(d0=M68k::setw(0,Mem::uw(HiresData::View2FloorDist)));
if((Mem::b(VidBss::Vid_FullScreen_b) != 0)) {
(d0=M68k::muls(d0,107));
}
else {
(d0=int16_t(d0));
(d0=j_shl(d0,6));
}
(a2=d0);
(d7=M68k::setw(d7,(d7 - d1)));
if((int16_t(d7) <= 0)) return savedA0;
(d0=M68k::setw(d0,d1));
if((int16_t(d0) == 0)) (d0=1);
(d1=M68k::muls(Mem::uw(HiresData::linedir),d1));
(a6=j_add(a6,d1));
Mem::ww(HiresData::tonextline,2);
}
bool gour=(Mem::b(HiresData::draw_UseGouraudFlats_b) != 0);
bool clip=(Mem::b(HiresData::anyclipping) != 0);
while(true){
int32_t d2{};
bool drawLine=true;
if(!(gour)) {
if(clip) {
int32_t d3c=M68k::setw(0,Mem::uw(HireswallData::Draw_LeftClip_w));
int32_t d4c=M68k::setw(0,Mem::uw(HireswallData::Draw_RightClip_w));
(d2=M68k::setw(0,Mem::uw(j_add(a4,(TablesBss::RightSideTable_vw - TablesBss::LeftSideTable_vw)))));
(d2=M68k::setw(d2,j_add(d2,1)));
if((int16_t(d2) <= int16_t(d3c))) {
(drawLine=false);
}
else {
if((int16_t(d2) > int16_t(d4c))) (d2=M68k::setw(d2,d4c));
(d1=M68k::setw(0,Mem::uw(a4)));
if((int16_t(d1) >= int16_t(d4c))) {
(drawLine=false);
}
else {
if((int16_t(d1) < int16_t(d3c))) (d1=M68k::setw(d1,d3c));
if((int16_t(d2) <= int16_t(d1))) {
(drawLine=false);
}
else {
Mem::ww(HiresData::leftedge,d1);
Mem::ww(HiresData::rightedge,d2);
}
}
}
}
else {
(d2=M68k::setw(0,Mem::uw(j_add(a4,(TablesBss::RightSideTable_vw - TablesBss::LeftSideTable_vw)))));
(d2=M68k::setw(d2,j_add(d2,1)));
(d1=M68k::setw(0,Mem::uw(a4)));
Mem::ww(HiresData::leftedge,d1);
Mem::ww(HiresData::rightedge,d2);
}
if(drawLine) {
int32_t a3=a6;
int32_t zt=a2;
(zt=j_ushr(zt,4));
(zt=M68k::mulu(zt,Mem::uw(j_add(HiresData::OneOverN_vw,((d0 & 0xFFFF) * 2)))));
(zt=j_ushr(zt,8));
Hires::draw_FloorLine(zt,a3);
}
}
else {
if(clip) {
int32_t d3c=M68k::setw(0,Mem::uw(HireswallData::Draw_LeftClip_w));
int32_t d4c=M68k::setw(0,Mem::uw(HireswallData::Draw_RightClip_w));
(d2=M68k::setw(0,Mem::uw(j_add(a4,(TablesBss::RightSideTable_vw - TablesBss::LeftSideTable_vw)))));
int32_t d5g=M68k::setw(0,d2);
(d5g=M68k::setw(d5g,(d5g - Mem::uw(a4))));
(d5g=M68k::setw(d5g,j_add(d5g,1)));
int32_t d6g=0;
(d2=M68k::setw(d2,j_add(d2,1)));
if((int16_t(d2) <= int16_t(d3c))) {
(drawLine=false);
}
else {
if((int16_t(d2) > int16_t(d4c))) (d2=M68k::setw(d2,d4c));
(d1=M68k::setw(0,Mem::uw(a4)));
if((int16_t(d1) >= int16_t(d4c))) {
(drawLine=false);
}
else {
if((int16_t(d1) < int16_t(d3c))) {
(d6g=M68k::setw(d6g,d3c));
(d6g=M68k::setw(d6g,(d6g - 1)));
(d6g=M68k::setw(d6g,(d6g - d1)));
(d1=M68k::setw(d1,d3c));
}
if((int16_t(d2) <= int16_t(d1))) {
(drawLine=false);
}
else {
Mem::ww(HiresData::leftedge,d1);
Mem::ww(HiresData::rightedge,d2);
int32_t d2d=a2;
(d2d=j_ushr(d2d,4));
(d2d=M68k::mulu(d2d,Mem::uw(j_add(HiresData::OneOverN_vw,((d0 & 0xFFFF) * 2)))));
(d2d=j_ushr(d2d,8));
Mem::wl(HiresData::draw_Distance_l,d2d);
(d2d=j_shr(d2d,7));
(d2d=j_shr(d2d,2));
int32_t d1b=0;
int32_t d3b=0;
(d1b=M68k::setw(d1b,Mem::uw(j_add(a4,(TablesBss::LeftBrightTable_vw - TablesBss::LeftSideTable_vw)))));
(d1b=M68k::setw(d1b,j_add(d1b,d2d)));
if((int16_t(d1b) < 0)) (d1b=0);
if((int16_t(d1b) > 30)) (d1b=M68k::setw(d1b,30));
(d3b=M68k::setw(d3b,Mem::uw(j_add(a4,(TablesBss::RightBrightTable_vw - TablesBss::LeftSideTable_vw)))));
(d3b=M68k::setw(d3b,j_add(d3b,d2d)));
if((int16_t(d3b) < 0)) (d3b=0);
if((int16_t(d3b) > 30)) (d3b=M68k::setw(d3b,30));
(d3b=M68k::setw(d3b,(d3b - d1b)));
(d1b=M68k::setw(d1b,j_shl((d1b & 0xFFFF),8)));
Mem::ww(HiresData::leftbright,d1b);
(d3b=M68k::swap(d3b));
if((d3b > 0)) {
(d3b=j_shr(d3b,6));
(d3b=M68k::divs(d3b,d5g));
}
else {
(d3b=-(d3b));
(d3b=j_shr(d3b,6));
(d3b=M68k::divs(d3b,d5g));
(d3b=M68k::setw(d3b,-(int16_t(d3b))));
}
(d6g=M68k::muls(d6g,d3b));
(d6g=M68k::setw(d6g,j_add(d6g,(256 * 4))));
(d6g=M68k::setw(d6g,j_shr(int16_t(d6g),2)));
(d6g=M68k::setb(d6g,0));
(d6g=M68k::setw(d6g,j_add(d6g,Mem::uw(HiresData::leftbright))));
if((int16_t(d6g) < 0)) (d6g=0);
Mem::ww(HiresData::leftbright,d6g);
(d3b=int16_t(d3b));
(d3b=j_shr(d3b,2));
Mem::ww(HiresData::brightspd,d3b);
int32_t a3=a6;
int32_t z=Mem::l(HiresData::draw_Distance_l);
int32_t a1g=j_add(Mem::l(DrawBss::Draw_TexturePalettePtr_l),(256 * 32));
int32_t a0g=j_add(Mem::l(DrawBss::Draw_FloorTexturesPtr_l),int16_t(Mem::uw(HiresData::whichtile)));
Hires::pastfloorbright(z,a0g,a1g,a3);
}
}
}
}
else {
(d2=M68k::setw(0,Mem::uw(j_add(a4,(TablesBss::RightSideTable_vw - TablesBss::LeftSideTable_vw)))));
(d2=M68k::setw(d2,j_add(d2,1)));
(d1=M68k::setw(0,Mem::uw(a4)));
Mem::ww(HiresData::leftedge,d1);
Mem::ww(HiresData::rightedge,d2);
(d2=M68k::setw(d2,(d2 - d1)));
int32_t d6g=a2;
(d6g=j_shr(d6g,4));
(d6g=M68k::mulu(d6g,Mem::uw(j_add(HiresData::OneOverN_vw,((d0 & 0xFFFF) * 2)))));
(d6g=j_shr(d6g,8));
int32_t d5g=d6g;
(d5g=j_shr(d5g,7));
(d5g=j_shr(d5g,2));
int32_t d1b=0;
int32_t d3b=0;
(d1b=M68k::setw(d1b,Mem::uw(j_add(a4,(TablesBss::LeftBrightTable_vw - TablesBss::LeftSideTable_vw)))));
(d1b=M68k::setw(d1b,j_add(d1b,d5g)));
if((int16_t(d1b) < 0)) (d1b=0);
if((int16_t(d1b) > 30)) (d1b=M68k::setw(d1b,30));
(d3b=M68k::setw(d3b,Mem::uw(j_add(a4,(TablesBss::RightBrightTable_vw - TablesBss::LeftSideTable_vw)))));
(d3b=M68k::setw(d3b,j_add(d3b,d5g)));
if((int16_t(d3b) < 0)) (d3b=0);
if((int16_t(d3b) > 30)) (d3b=M68k::setw(d3b,30));
(d3b=M68k::setw(d3b,(d3b - d1b)));
(d1b=M68k::setw(d1b,j_shl((d1b & 0xFFFF),8)));
Mem::ww(HiresData::leftbright,d1b);
(d3b=M68k::swap(d3b));
(d2=int16_t(d2));
(d3b=j_div(d3b,d2));
(d3b=j_shr(d3b,8));
Mem::ww(HiresData::brightspd,d3b);
int32_t a3=a6;
int32_t z=d6g;
Mem::wl(HiresData::draw_Distance_l,z);
int32_t a1g=j_add(Mem::l(DrawBss::Draw_TexturePalettePtr_l),(256 * 32));
int32_t a0g=j_add(Mem::l(DrawBss::Draw_FloorTexturesPtr_l),int16_t(Mem::uw(HiresData::whichtile)));
Hires::pastfloorbright(z,a0g,a1g,a3);
(drawLine=false);
}
}
Mem::ww(HiresData::disttobot,(Mem::uw(HiresData::disttobot) - 1));
(d3=M68k::setw(0,Mem::uw(HiresData::linedir)));
(a6=j_add(a6,int16_t(d3)));
(d3=M68k::setw(d3,Mem::uw(HiresData::tonextline)));
(a4=j_add(a4,int16_t(d3)));
(d3=M68k::setw(d3,j_shr(int16_t(d3),1)));
(d0=M68k::setw(d0,j_add(d0,d3)));
(d7=M68k::setw(d7,(d7 - 1)));
if((int16_t(d7) > 0)) continue;
break;
}
return savedA0;
}

int32_t sideLoopSimple(int32_t a0){
int32_t d0=0;
int32_t d1{};
int32_t d2=0;
int32_t d3{};
int32_t d4{};
int32_t d5{};
int32_t d6{};
int32_t d7{};
int32_t a1=TablesBss::Rotated_vl;
int32_t a2=TablesBss::OnScreen_vl;
int32_t a3{};
(d7=M68k::setw(0,Mem::uw(a0)));
(a0+=2);
while(true){
(d6=M68k::setw(0,Mem::uw(HiresData::minz)));
(d1=M68k::setw(0,Mem::uw(a0)));
(a0+=2);
(d3=M68k::setw(0,Mem::uw(a0)));
(d1=M68k::setw(d1,(d1 & 0xFFF)));
(d3=M68k::setw(d3,(d3 & 0xFFF)));
(d4=M68k::setw(0,Mem::uw(j_add(j_add(a1,((d1 & 0xFFFF) * 8)),6))));
bool walk=true;
(a3=TablesBss::RightSideTable_vw);
if((int16_t(d4) > int16_t(d6))) {
(d5=M68k::setw(0,Mem::uw(j_add(j_add(a1,((d3 & 0xFFFF) * 8)),6))));
if((int16_t(d5) > int16_t(d6))) {
(d0=M68k::setw(0,Mem::uw(j_add(a2,((d1 & 0xFFFF) * 2)))));
(d2=M68k::setw(0,Mem::uw(j_add(a2,((d3 & 0xFFFF) * 2)))));
(d1=Mem::l(HiresData::ypos));
(d3=d1);
(d1=M68k::divs(d1,d4));
(d3=M68k::divs(d3,d5));
}
else {
(d5=M68k::setw(d5,(d5 - d4)));
(d2=Mem::l(j_add(a1,((d3 & 0xFFFF) * 8))));
(d2=(d2 - Mem::l(j_add(a1,((d1 & 0xFFFF) * 8)))));
(d6=M68k::setw(d6,(d6 - d4)));
(d2=j_shr(d2,7));
(d2=M68k::muls(d2,d6));
(d2=M68k::divs(d2,d5));
(d2=int16_t(d2));
(d2=j_shl(d2,7));
(d2=j_add(d2,Mem::l(j_add(a1,((d1 & 0xFFFF) * 8)))));
(d5=M68k::setw(d5,Mem::uw(HiresData::minz)));
(d0=M68k::setw(0,Mem::uw(j_add(a2,((d1 & 0xFFFF) * 2)))));
(d2=M68k::divs(d2,d5));
(d2=M68k::setw(d2,j_add(d2,Mem::uw(HiresData::Vid_CentreX_w))));
(d1=Mem::l(HiresData::ypos));
(d1=M68k::divs(d1,d4));
(d3=M68k::setw(d3,Mem::uw(HiresData::bottomline)));
}
}
else {
(d5=M68k::setw(0,Mem::uw(j_add(j_add(a1,((d3 & 0xFFFF) * 8)),6))));
if((int16_t(d5) <= int16_t(d6))) {
(walk=false);
}
else {
(d4=M68k::setw(d4,(d4 - d5)));
(d0=Mem::l(j_add(a1,((d1 & 0xFFFF) * 8))));
(d0=(d0 - Mem::l(j_add(a1,((d3 & 0xFFFF) * 8)))));
(d0=j_shr(d0,7));
(d6=M68k::setw(d6,(d6 - d5)));
(d0=M68k::muls(d0,d6));
(d0=M68k::divs(d0,d4));
(d0=int16_t(d0));
(d0=j_shl(d0,7));
(d0=j_add(d0,Mem::l(j_add(a1,((d3 & 0xFFFF) * 8)))));
(d4=M68k::setw(d4,Mem::uw(HiresData::minz)));
(d2=M68k::setw(0,Mem::uw(j_add(a2,((d3 & 0xFFFF) * 2)))));
(d0=M68k::divs(d0,d4));
(d0=M68k::setw(d0,j_add(d0,Mem::uw(HiresData::Vid_CentreX_w))));
(d3=Mem::l(HiresData::ypos));
(d3=M68k::divs(d3,d5));
(d1=M68k::setw(d1,Mem::uw(HiresData::bottomline)));
}
}
if(walk) {
(a3=TablesBss::RightSideTable_vw);
if((int16_t(d3) == int16_t(d1))) {
(walk=false);
}
else {
Mem::wb(HiresData::drawit,0xFF);
bool onright=(int16_t(d3) > int16_t(d1));
if(!(onright)) {
(a3=TablesBss::LeftSideTable_vw);
int32_t t=d1;
(d1=d3);
(d3=t);
(t=d0);
(d0=d2);
(d2=t);
}
(a3=j_add(a3,((d1 & 0xFFFF) * 2)));
if((int16_t(d1) < int16_t(Mem::uw(HiresData::top)))) {
Mem::ww(HiresData::top,d1);
}
if((int16_t(d3) > int16_t(Mem::uw(HiresData::bottom)))) {
Mem::ww(HiresData::bottom,d3);
}
(d3=M68k::setw(d3,(d3 - d1)));
(d2=M68k::setw(d2,(d2 - d0)));
if(!(onright)) {
if((int16_t(d2) < 0)) {
(d2=M68k::setw(d2,-(int16_t(d2))));
(d2=int16_t(d2));
(d2=M68k::divs(d2,d3));
(d6=M68k::setw(0,d2));
(d2=M68k::swap(d2));
(d4=M68k::setw(0,d3));
(d5=M68k::setw(0,d3));
(d5=M68k::setw(d5,(d5 - 1)));
(d1=M68k::setw(0,d6));
(d1=M68k::setw(d1,j_add(d1,1)));
while(true){
(d4=M68k::setw(d4,(d4 - d2)));
if((int16_t(d4) >= 0)) {
(d0=M68k::setw(d0,(d0 - d6)));
Mem::ww(a3,d0);
(a3+=2);
}
else {
(d0=M68k::setw(d0,(d0 - d1)));
(d4=M68k::setw(d4,j_add(d4,d3)));
Mem::ww(a3,d0);
(a3+=2);
}
(d5=M68k::setw(d5,(d5 - 1)));
if((int16_t(d5) == -(1))) break;
}
}
else {
(d2=int16_t(d2));
(d2=M68k::divs(d2,d3));
(d6=M68k::setw(0,d2));
(d2=M68k::swap(d2));
(d4=M68k::setw(0,d3));
(d5=M68k::setw(0,d3));
(d5=M68k::setw(d5,(d5 - 1)));
(d1=M68k::setw(0,d6));
(d1=M68k::setw(d1,j_add(d1,1)));
while(true){
Mem::ww(a3,d0);
(a3+=2);
(d4=M68k::setw(d4,(d4 - d2)));
if((int16_t(d4) >= 0)) {
(d0=M68k::setw(d0,j_add(d0,d6)));
}
else {
(d0=M68k::setw(d0,j_add(d0,d1)));
(d4=M68k::setw(d4,j_add(d4,d3)));
}
(d5=M68k::setw(d5,(d5 - 1)));
if((int16_t(d5) == -(1))) break;
}
}
}
else {
if((int16_t(d2) < 0)) {
(d2=M68k::setw(d2,-(int16_t(d2))));
(d2=int16_t(d2));
(d2=M68k::divs(d2,d3));
(d6=M68k::setw(0,d2));
(d2=M68k::swap(d2));
(d4=M68k::setw(0,d3));
(d5=M68k::setw(0,d3));
(d5=M68k::setw(d5,(d5 - 1)));
(d1=M68k::setw(0,d6));
(d1=M68k::setw(d1,j_add(d1,1)));
while(true){
Mem::ww(a3,d0);
(a3+=2);
(d4=M68k::setw(d4,(d4 - d2)));
if((int16_t(d4) >= 0)) {
(d0=M68k::setw(d0,(d0 - d6)));
}
else {
(d0=M68k::setw(d0,(d0 - d1)));
(d4=M68k::setw(d4,j_add(d4,d3)));
}
(d5=M68k::setw(d5,(d5 - 1)));
if((int16_t(d5) == -(1))) break;
}
}
else {
(d2=int16_t(d2));
(d2=M68k::divs(d2,d3));
(d6=M68k::setw(0,d2));
(d2=M68k::swap(d2));
(d4=M68k::setw(0,d3));
(d5=M68k::setw(0,d3));
(d5=M68k::setw(d5,(d5 - 1)));
(d1=M68k::setw(0,d6));
(d1=M68k::setw(d1,j_add(d1,1)));
while(true){
(d4=M68k::setw(d4,(d4 - d2)));
if((int16_t(d4) >= 0)) {
(d0=M68k::setw(d0,j_add(d0,d6)));
Mem::ww(a3,d0);
(a3+=2);
}
else {
(d0=M68k::setw(d0,j_add(d0,d1)));
(d4=M68k::setw(d4,j_add(d4,d3)));
Mem::ww(a3,d0);
(a3+=2);
}
(d5=M68k::setw(d5,(d5 - 1)));
if((int16_t(d5) == -(1))) break;
}
}
}
}
}
(d7=M68k::setw(d7,(d7 - 1)));
if((int16_t(d7) == -(1))) break;
}
return a0;
}

int32_t sideLoopGouraud(int32_t a0){
int32_t d0=0;
int32_t d1{};
int32_t d2=0;
int32_t d3{};
int32_t d4{};
int32_t d5{};
int32_t d6{};
int32_t d7{};
int32_t a1=TablesBss::Rotated_vl;
int32_t a2=TablesBss::OnScreen_vl;
int32_t a3{};
(d7=M68k::setw(0,Mem::uw(a0)));
(a0+=2);
while(true){
(d6=M68k::setw(0,Mem::uw(HiresData::minz)));
(d1=M68k::setw(0,Mem::uw(a0)));
(a0+=2);
(d3=M68k::setw(0,Mem::uw(a0)));
(d4=M68k::setw(0,d1));
(d5=M68k::setw(0,d3));
(d1=M68k::setw(d1,(d1 & 0x0FFF)));
(d3=M68k::setw(d3,(d3 & 0x0FFF)));
(d4=M68k::setw(d4,((j_shl((d4 & 0xFFFF),4) | j_ushr((d4 & 0xFFFF),12)) & 0xFFFF)));
(d5=M68k::setw(d5,((j_shl((d5 & 0xFFFF),4) | j_ushr((d5 & 0xFFFF),12)) & 0xFFFF)));
(d4=M68k::setw(d4,(d4 & 0xF)));
(d5=M68k::setw(d5,(d5 & 0xF)));
int32_t a4f=Mem::l(HiresData::FloorPtBrightsPtr_l);
(d4=M68k::setw(d4,Mem::uw(j_add(a4f,((d4 & 0xFFFF) * 8)))));
if((int16_t(d4) < 0)) (d4=M68k::setw(d4,-(int16_t(d4))));
(d4=M68k::setw(d4,(d4 - 300)));
Mem::ww(HiresData::fbr,d4);
(d4=M68k::setw(d4,Mem::uw(j_add(a4f,((d5 & 0xFFFF) * 8)))));
if((int16_t(d4) < 0)) (d4=M68k::setw(d4,-(int16_t(d4))));
(d4=M68k::setw(d4,(d4 - 300)));
Mem::ww(HiresData::sbr,d4);
(d4=M68k::setw(d4,Mem::uw(j_add(j_add(a1,((d1 & 0xFFFF) * 8)),6))));
bool walk=true;
if((int16_t(d4) > int16_t(d6))) {
(d5=M68k::setw(0,Mem::uw(j_add(j_add(a1,((d3 & 0xFFFF) * 8)),6))));
if((int16_t(d5) > int16_t(d6))) {
(d0=M68k::setw(0,Mem::uw(j_add(a2,((d1 & 0xFFFF) * 2)))));
(d2=M68k::setw(0,Mem::uw(j_add(a2,((d3 & 0xFFFF) * 2)))));
(d1=Mem::l(HiresData::ypos));
(d3=d1);
(d1=M68k::divs(d1,d4));
(d3=M68k::divs(d3,d5));
}
else {
(d5=M68k::setw(d5,(d5 - d4)));
(d2=M68k::setw(0,Mem::uw(HiresData::sbr)));
(d2=M68k::setw(d2,(d2 - Mem::uw(HiresData::fbr))));
(d6=M68k::setw(d6,(d6 - d4)));
(d2=M68k::muls(d2,d6));
(d2=M68k::divs(d2,d5));
(d2=M68k::setw(d2,j_add(d2,Mem::uw(HiresData::fbr))));
Mem::ww(HiresData::sbr,d2);
(d2=Mem::l(j_add(a1,((d3 & 0xFFFF) * 8))));
(d2=(d2 - Mem::l(j_add(a1,((d1 & 0xFFFF) * 8)))));
(d2=j_shr(d2,7));
(d2=M68k::muls(d2,d6));
(d2=M68k::divs(d2,d5));
(d2=int16_t(d2));
(d2=j_shl(d2,7));
(d2=j_add(d2,Mem::l(j_add(a1,((d1 & 0xFFFF) * 8)))));
(d5=M68k::setw(d5,Mem::uw(HiresData::minz)));
(d0=M68k::setw(0,Mem::uw(j_add(a2,((d1 & 0xFFFF) * 2)))));
(d2=M68k::divs(d2,d5));
(d2=M68k::setw(d2,j_add(d2,Mem::uw(HiresData::Vid_CentreX_w))));
(d1=Mem::l(HiresData::ypos));
(d1=M68k::divs(d1,d4));
(d3=M68k::setw(d3,Mem::uw(HiresData::bottomline)));
}
}
else {
(d5=M68k::setw(0,Mem::uw(j_add(j_add(a1,((d3 & 0xFFFF) * 8)),6))));
if((int16_t(d5) <= int16_t(d6))) {
(walk=false);
}
else {
(d4=M68k::setw(d4,(d4 - d5)));
(d0=M68k::setw(0,Mem::uw(HiresData::fbr)));
(d0=M68k::setw(d0,(d0 - Mem::uw(HiresData::sbr))));
(d6=M68k::setw(d6,(d6 - d5)));
(d0=M68k::muls(d0,d6));
(d0=M68k::divs(d0,d4));
(d0=M68k::setw(d0,j_add(d0,Mem::uw(HiresData::sbr))));
Mem::ww(HiresData::fbr,d0);
(d0=Mem::l(j_add(a1,((d1 & 0xFFFF) * 8))));
(d0=(d0 - Mem::l(j_add(a1,((d3 & 0xFFFF) * 8)))));
(d0=j_shr(d0,7));
(d0=M68k::muls(d0,d6));
(d0=M68k::divs(d0,d4));
(d0=int16_t(d0));
(d0=j_shl(d0,7));
(d0=j_add(d0,Mem::l(j_add(a1,((d3 & 0xFFFF) * 8)))));
(d4=M68k::setw(d4,Mem::uw(HiresData::minz)));
(d2=M68k::setw(0,Mem::uw(j_add(a2,((d3 & 0xFFFF) * 2)))));
(d0=M68k::divs(d0,d4));
(d0=M68k::setw(d0,j_add(d0,Mem::uw(HiresData::Vid_CentreX_w))));
(d3=Mem::l(HiresData::ypos));
(d3=M68k::divs(d3,d5));
(d1=M68k::setw(d1,Mem::uw(HiresData::bottomline)));
}
}
if(walk) {
if((int16_t(d3) == int16_t(d1))) {
(walk=false);
}
else {
Mem::wb(HiresData::drawit,0xFF);
bool onright=(int16_t(d3) > int16_t(d1));
if(!(onright)) {
int32_t t=d1;
(d1=d3);
(d3=t);
(t=d0);
(d0=d2);
(d2=t);
(a3=j_add(TablesBss::LeftSideTable_vw,((d1 & 0xFFFF) * 2)));
}
else {
(a3=j_add(TablesBss::RightSideTable_vw,((d1 & 0xFFFF) * 2)));
}
int32_t a4=(onright?j_add(a3,(TablesBss::RightBrightTable_vw - TablesBss::RightSideTable_vw)):j_add(a3,(TablesBss::LeftBrightTable_vw - TablesBss::LeftSideTable_vw)));
if((int16_t(d1) < int16_t(Mem::uw(HiresData::top)))) Mem::ww(HiresData::top,d1);
if((int16_t(d3) > int16_t(Mem::uw(HiresData::bottom)))) Mem::ww(HiresData::bottom,d3);
(d3=M68k::setw(d3,(d3 - d1)));
(d2=M68k::setw(d2,(d2 - d0)));
int32_t brStart=(onright?Mem::uw(HiresData::fbr):Mem::uw(HiresData::sbr));
int32_t brOther=(onright?Mem::uw(HiresData::sbr):Mem::uw(HiresData::fbr));
bool leftGoing=(int16_t(d2) < 0);
if(leftGoing) (d2=M68k::setw(d2,-(int16_t(d2))));
(d2=int16_t(d2));
(d2=M68k::divs(d2,d3));
(d6=M68k::setw(0,d2));
(d2=M68k::swap(d2));
int32_t a5=int16_t(d2);
(d4=M68k::setw(0,d3));
(d5=M68k::setw(0,d3));
(d5=M68k::setw(d5,(d5 - 1)));
(d1=M68k::setw(0,d6));
(d1=M68k::setw(d1,j_add(d1,1)));
int32_t a6=int16_t(d1);
(d1=M68k::setw(0,brStart));
(d2=M68k::setw(d2,brOther));
(d2=M68k::setw(d2,(d2 - d1)));
(d2=int16_t(d2));
(d2=M68k::setw(d2,j_shl((d2 & 0xFFFF),8)));
(d2=M68k::setw(d2,j_shl((d2 & 0xFFFF),2)));
(d2=M68k::divs(d2,d3));
(d2=int16_t(d2));
(d2=j_shl(d2,6));
(d1=M68k::swap(d1));
if((!(onright) && !(leftGoing))) {
while(true){
Mem::ww(a3,d0);
(a3+=2);
(d1=M68k::swap(d1));
Mem::ww(a4,d1);
(a4+=2);
(d1=M68k::swap(d1));
(d1=j_add(d1,d2));
(d4=M68k::setw(d4,(d4 - a5)));
if((int16_t(d4) >= 0)) {
(d0=M68k::setw(d0,j_add(d0,d6)));
}
else {
(d0=M68k::setw(d0,j_add(d0,a6)));
(d4=M68k::setw(d4,j_add(d4,d3)));
}
(d5=M68k::setw(d5,(d5 - 1)));
if((int16_t(d5) == -(1))) break;
}
}
else if((!(onright) && leftGoing)) {
while(true){
(d1=M68k::swap(d1));
Mem::ww(a4,d1);
(a4+=2);
(d1=M68k::swap(d1));
(d1=j_add(d1,d2));
(d4=M68k::setw(d4,(d4 - a5)));
if((int16_t(d4) >= 0)) {
(d0=M68k::setw(d0,(d0 - d6)));
Mem::ww(a3,d0);
(a3+=2);
}
else {
(d0=M68k::setw(d0,(d0 - a6)));
(d4=M68k::setw(d4,j_add(d4,d3)));
Mem::ww(a3,d0);
(a3+=2);
}
(d5=M68k::setw(d5,(d5 - 1)));
if((int16_t(d5) == -(1))) break;
}
}
else if((onright && !(leftGoing))) {
while(true){
(d1=M68k::swap(d1));
Mem::ww(a4,d1);
(a4+=2);
(d1=M68k::swap(d1));
(d1=j_add(d1,d2));
(d4=M68k::setw(d4,(d4 - a5)));
if((int16_t(d4) >= 0)) {
(d0=M68k::setw(d0,j_add(d0,d6)));
Mem::ww(a3,d0);
(a3+=2);
}
else {
(d0=M68k::setw(d0,j_add(d0,a6)));
(d4=M68k::setw(d4,j_add(d4,d3)));
Mem::ww(a3,d0);
(a3+=2);
}
(d5=M68k::setw(d5,(d5 - 1)));
if((int16_t(d5) == -(1))) break;
}
}
else {
while(true){
(d1=M68k::swap(d1));
Mem::ww(a4,d1);
(a4+=2);
(d1=M68k::swap(d1));
(d1=j_add(d1,d2));
Mem::ww(a3,d0);
(a3+=2);
(d4=M68k::setw(d4,(d4 - a5)));
if((int16_t(d4) >= 0)) {
(d0=M68k::setw(d0,(d0 - d6)));
}
else {
(d0=M68k::setw(d0,(d0 - a6)));
(d4=M68k::setw(d4,j_add(d4,d3)));
}
(d5=M68k::setw(d5,(d5 - 1)));
if((int16_t(d5) == -(1))) break;
}
}
}
}
(d7=M68k::setw(d7,(d7 - 1)));
if((int16_t(d7) == -(1))) break;
}
return a0;
}

int32_t Draw_Flats(int32_t a0,int32_t d0){
int32_t d1=0;
int32_t d3=0;
int32_t d4=0;
int32_t d5=0;
int32_t d6=0;
int32_t d7=0;
int32_t a1{};
int32_t a2{};
const int32_t ENTRY=0;
const int32_t DONTDRAWRETURN=1;
const int32_t CHECKFORWATER=2;
const int32_t ABOVEPLAYER=3;
const int32_t BELOW=4;
const int32_t NOTBELOW=5;
const int32_t SOMEFLOORTODRAW=6;
int32_t lbl=ENTRY;
while(true){
switch(lbl){
case ENTRY:
{{
Mem::ww(HiresData::above,0);
(d6=M68k::setw(d6,Mem::uw(a0)));
(a0+=2);
if(Hires::dbgGeomHit(Mem::w(DrawBss::Draw_CurrentZone_w))) {
j_log("GEOM zone=%d FLAT type=%d y=%d (monde %.2f)%n",Mem::w(DrawBss::Draw_CurrentZone_w),d0,int16_t(d6),j_div(int16_t(d6),128.0));
}
if((Mem::b(HiresData::draw_UseWater_b) != 0)) {
if((Mem::b(HiresData::DOANYWATER) == 0)) {
(lbl=DONTDRAWRETURN);
continue;
}
}
(d7=M68k::setw(d7,d6));
(d7=int16_t(d7));
(d7=j_shl(d7,6));
if((d7 < Mem::l(DrawBss::Draw_TopOfRoom_l))) {
(lbl=CHECKFORWATER);
continue;
}
if((d7 > Mem::l(DrawBss::Draw_BottomOfRoom_l))) {
(lbl=DONTDRAWRETURN);
continue;
}
(d7=M68k::setw(d7,Mem::uw(HireswallData::Draw_LeftClip_w)));
if((int16_t(d7) >= Mem::w(HireswallData::Draw_RightClip_w))) {
(lbl=DONTDRAWRETURN);
continue;
}
(d6=M68k::setw(d6,(d6 - Mem::uw(HiresData::flooryoff))));
if((int16_t(d6) > 0)) {
(lbl=BELOW);
continue;
}
if((int16_t(d6) < 0)) {
(lbl=ABOVEPLAYER);
continue;
}
if((Mem::b(HiresData::draw_UseWater_b) != 0)) {
(a1=Mem::l(HiresData::ZonePtr_l));
(d7=M68k::setw(d7,Mem::uw(a1)));
if((int16_t(d7) == Mem::w(DrawBss::Draw_CurrentZone_w))) {
Mem::wb(HiresData::fillscrnwater,0xFF);
}
}
(lbl=DONTDRAWRETURN);
continue;
}
}
case DONTDRAWRETURN:
{{
(d6=M68k::setw(d6,Mem::uw(a0)));
(a0+=2);
(a0=j_add(j_add(a0,10),(int16_t(d6) * 2)));
return a0;
}
}
case CHECKFORWATER:
{{
if((Mem::b(HiresData::draw_UseWater_b) != 0)) {
(a1=Mem::l(HiresData::ZonePtr_l));
(d7=M68k::setw(d7,Mem::uw(a1)));
if((int16_t(d7) == Mem::w(DrawBss::Draw_CurrentZone_w))) {
Mem::wb(HiresData::fillscrnwater,0x0F);
}
}
(d6=M68k::setw(d6,Mem::uw(a0)));
(a0+=2);
(a0=j_add(j_add(a0,10),(int16_t(d6) * 2)));
return a0;
}
}
case ABOVEPLAYER:
{{
if((Mem::b(HiresData::draw_UseWater_b) != 0)) {
(a1=Mem::l(HiresData::ZonePtr_l));
(d7=M68k::setw(d7,Mem::uw(a1)));
if((int16_t(d7) == Mem::w(DrawBss::Draw_CurrentZone_w))) {
Mem::wb(HiresData::fillscrnwater,0x0F);
}
}
if(((d0 & 2) == 0)) {
(lbl=DONTDRAWRETURN);
continue;
}
(d7=M68k::setw(d7,Mem::uw(HireswallData::Vid_CentreY_w)));
(d7=M68k::setw(d7,(d7 - Mem::uw(HireswallData::draw_TopClip_w))));
if((int16_t(d7) <= 0)) {
(lbl=DONTDRAWRETURN);
continue;
}
(d0=M68k::setw(d0,1));
Mem::ww(HiresData::above,d0);
(d6=M68k::setw(d6,-(int16_t(d6))));
(lbl=NOTBELOW);
continue;
}
}
case BELOW:
{{
(d7=M68k::setw(d7,Mem::uw(HireswallData::draw_BottomClip_w)));
(d7=M68k::setw(d7,(d7 - Mem::uw(HireswallData::Vid_CentreY_w))));
if((int16_t(d7) <= 0)) {
(lbl=DONTDRAWRETURN);
continue;
}
(lbl=NOTBELOW);
continue;
}
}
case NOTBELOW:
{{
if(((d0 & 1) == 0)) {
(lbl=DONTDRAWRETURN);
continue;
}
Mem::ww(HiresData::View2FloorDist,d6);
(d5=M68k::setw(d5,d6));
(d5=int16_t(d5));
(d5=j_shl(d5,6));
Mem::wl(HiresData::ypos,d5);
(d6=M68k::mulu(d6,Mem::uw(j_add(HiresData::OneOverN_vw,((d7 & 0xFFFF) * 2)))));
(d6=j_ushr(d6,8));
if((d6 == 0)) {
(lbl=DONTDRAWRETURN);
continue;
}
if((d6 > 32767)) {
(lbl=DONTDRAWRETURN);
continue;
}
Mem::ww(HiresData::minz,d6);
Mem::ww(HiresData::bottomline,d7);
int32_t savedA0=a0;
(d7=M68k::setw(d7,Mem::uw(a0)));
(a0+=2);
(a1=TablesBss::Rotated_vl);
(a2=TablesBss::OnScreen_vl);
(d4=0);
(d5=0);
(d6=0);
Mem::wb(HiresData::anyclipping,0);
while(true){
(d0=M68k::setw(d0,Mem::uw(a0)));
(a0+=2);
(d0=M68k::setw(d0,(d0 & 0xFFF)));
(d1=M68k::setw(d1,Mem::uw(j_add(j_add(a1,((d0 & 0xFFFF) * 8)),6))));
if((int16_t(d1) <= 0)) {
(d5=M68k::setb(d5,0xFF));
Mem::wb(HiresData::anyclipping,0xFF);
}
else {
(d3=M68k::setw(d3,Mem::uw(j_add(a2,((d0 & 0xFFFF) * 2)))));
if((int16_t(d3) <= Mem::w(HireswallData::Draw_LeftClip_w))) {
(d4=M68k::setb(d4,0xFF));
Mem::wb(HiresData::anyclipping,0xFF);
}
else if((int16_t(d3) >= Mem::w(HireswallData::Draw_RightClip_w))) {
(d6=M68k::setb(d6,0xFF));
Mem::wb(HiresData::anyclipping,0xFF);
}
else {
(d5=M68k::setb(d5,0xFF));
}
}
(d7=M68k::setw(d7,(d7 - 1)));
if((int16_t(d7) == -(1))) break;
}
(a0=savedA0);
if(((d5 & 0xFF) != 0)) {
(lbl=SOMEFLOORTODRAW);
continue;
}
(d6=M68k::setb(d6,((d6 ^ d4) & 0xFF)));
if(((d6 & 0xFF) != 0)) {
(lbl=DONTDRAWRETURN);
continue;
}
(lbl=SOMEFLOORTODRAW);
continue;
}
}
case SOMEFLOORTODRAW:
{{
if(DevMacros::DEV_TEST(DevInst::Dev_DebugFlags_l,DevMacros::DEV_SKIP_FLATS)) {
(lbl=DONTDRAWRETURN);
continue;
}
Mem::ww(DevInst::dev_VisibleFlats_w,j_add(Mem::uw(DevInst::dev_VisibleFlats_w),1));
int32_t a0Edge{};
if((Mem::b(HiresData::draw_UseGouraudFlats_b) != 0)) {
Mem::ww(HiresData::top,300);
Mem::ww(HiresData::bottom,-(1));
Mem::ww(HiresData::drawit,0);
(a0Edge=Hires::sideLoopGouraud(a0));
}
else {
Mem::ww(HiresData::top,300);
Mem::ww(HiresData::bottom,-(1));
Mem::ww(HiresData::drawit,0);
(a0Edge=Hires::sideLoopSimple(a0));
}
return Hires::pastFlats(a0Edge);
}
}
default:
{throw std::runtime_error(j_add("Draw_Flats label ",lbl));
}
}
}
}

void MakeSomeNoise(){
int32_t d0=0;
int32_t d1=0;
int32_t d2=0;
int32_t d3=0;
int32_t d4=0;
int32_t d5=0;
int32_t d6=0;
int32_t a1{};
int32_t a2{};
int32_t a3{};
if((Mem::b(HiresData::notifplaying) != 0)) {
(d0=M68k::setw(0,Mem::uw(HiresData::IDNUM)));
if(((d0 & 0xFFFF) != 0xFFFF)) {
(d1=M68k::setw(0,7));
(a3=HiresData::CHANNELDATA);
while(true){
if((Mem::b(a3) == 0)) {
if((int16_t(Mem::uw(j_add(a3,32))) == int16_t(d0))) return ;
}
(a3+=4);
(d1=M68k::setw(d1,(d1 - 1)));
if((int16_t(d1) == -(1))) break;
}
}
}
(d1=M68k::setw(0,Mem::uw(HiresData::Aud_NoiseX_w)));
(d1=M68k::muls(d1,d1));
(d2=M68k::setw(0,Mem::uw(HiresData::Aud_NoiseZ_w)));
(d2=M68k::muls(d2,d2));
(d3=M68k::setw(0,Mem::uw(HiresData::Aud_NoiseVol_w)));
Mem::ww(HiresData::noiseloud,32767);
(d0=1);
(d2=j_add(d1,d2));
if((d2 != 0)) {
(d0=M68k::setw(0,31));
while(true){
if(((d2 & j_shl(1,(d0 & 31))) != 0)) break;
(d0=M68k::setw(d0,(d0 - 1)));
if((int16_t(d0) == -(1))) break;
}
(d0=M68k::setw(d0,j_shr(int16_t(d0),1)));
(d3=j_shl(1,(d0 & 31)));
(d0=d3);
for(int32_t it=0;(it < 2);(it)++){
(d3=M68k::setw(0,d0));
(d3=M68k::muls(d3,d3));
(d3=(d3 - d2));
(d3=j_shr(d3,1));
(d3=M68k::divs(d3,d0));
(d0=M68k::setw(d0,(d0 - d3)));
if(!((int16_t(d0) > 0))) (d0=M68k::setw(d0,1));
}
(d3=M68k::setw(0,Mem::uw(HiresData::Aud_NoiseVol_w)));
(d3=int16_t(d3));
(d3=j_shl(d3,6));
if((d3 > 32767)) (d3=32767);
(d0=M68k::setw(d0,j_shr(int16_t(d0),2)));
(d0=M68k::setw(d0,j_add(d0,1)));
(d3=M68k::divs(d3,d0));
}
Mem::ww(HiresData::noiseloud,d3);
if((int16_t(d3) > 64)) (d3=M68k::setw(d3,64));
(d4=M68k::setw(0,d3));
if((Mem::b(HiresData::Aud_Stereo_b) == 0)) {
Hires::makeNoiseMono(d3,d4,d0);
return ;
}
(d2=M68k::setw(0,d3));
(d2=M68k::muls(d2,Mem::uw(HiresData::Aud_NoiseX_w)));
(d0=M68k::setw(d0,j_shl((d0 & 0xFFFF),2)));
(d2=M68k::divs(d2,d0));
if((int16_t(d2) > 0)) {
(d3=M68k::setw(d3,(d3 - d2)));
if((int16_t(d3) < 0)) (d3=M68k::setw(d3,0));
}
else {
(d4=M68k::setw(d4,j_add(d4,d2)));
if((int16_t(d4) < 0)) (d4=M68k::setw(d4,0));
}
Mem::wb(HiresData::Aud_NeedLeft_b,0xFF);
Mem::wl(HiresData::RIGHTOFFSET,0);
Mem::wl(HiresData::LEFTOFFSET,0);
if((int8_t(d4) > int8_t(d3))) {
Mem::wl(HiresData::RIGHTOFFSET,4);
Mem::wb(HiresData::Aud_NeedRight_b,0xFF);
(d2=M68k::setw(0,d4));
(d2=M68k::setw(d2,(d2 - d3)));
Mem::wb(HiresData::Aud_NeedLeft_b,((int16_t(d2) < 32)?0xFF:0));
}
else if((int8_t(d4) < int8_t(d3))) {
Mem::wl(HiresData::LEFTOFFSET,4);
Mem::wb(HiresData::Aud_NeedLeft_b,0xFF);
(d2=M68k::setw(0,d3));
(d2=M68k::setw(d2,(d2 - d4)));
Mem::wb(HiresData::Aud_NeedRight_b,((int16_t(d2) < 32)?0xFF:0));
}
(a2=0);
(d5=0);
(d2=M68k::setw(0,32767));
(d0=M68k::setw(0,Mem::uw(HiresData::IDNUM)));
(a3=HiresData::LEFTCHANDATA);
(d1=M68k::setw(0,3));
bool foundLeft=false;
while(true){
if((Mem::b(a3) == 0)) {
if((int16_t(Mem::uw(j_add(a3,32))) == int16_t(d0))) {
(d6=M68k::setw(0,d5));
(foundLeft=true);
break;
}
if((int16_t(d2) >= int16_t(Mem::uw(j_add(a3,2))))) {
(d2=M68k::setw(d2,Mem::uw(j_add(a3,2))));
(a2=a3);
(d6=M68k::setw(0,d5));
}
}
(a3+=4);
(d5=M68k::setw(d5,j_add(d5,1)));
(d1=M68k::setw(d1,(d1 - 1)));
if((int16_t(d1) == -(1))) break;
}
if(!(foundLeft)) (a3=a2);
(d5=a3);
if((d5 == 0)) return ;
if((int16_t(d2) < int16_t(Mem::uw(HiresData::noiseloud)))) {
Hires::makeNoiseChannel(a3,d0);
(d5=M68k::setw(0,Mem::uw(HiresData::Aud_SampleNum_w)));
(a3=TablesBss::Aud_SampleList_vl);
(a1=j_add(Mem::l(j_add(a3,((d5 & 0xFFFF) * 8))),Mem::l(HiresData::LEFTOFFSET)));
(a2=j_add(Mem::l(j_add(j_add(a3,((d5 & 0xFFFF) * 8)),4)),Mem::l(HiresData::LEFTOFFSET)));
Mem::wb(HiresData::NoiseMade0LEFT,((d6 == 0)?0xFF:0));
if((d6 == 0)) Hires::writeLeftChan(0,d5,d3,d4,a1,a2);
else {
Mem::wb(HiresData::NoiseMade1LEFT,((d6 < 2)?0xFF:0));
if((d6 < 2)) Hires::writeLeftChan(1,d5,d3,d4,a1,a2);
else {
Mem::wb(HiresData::NoiseMade2LEFT,((d6 == 2)?0xFF:0));
if((d6 == 2)) Hires::writeLeftChan(2,d5,d3,d4,a1,a2);
else {
Mem::wb(HiresData::NoiseMade3LEFT,0xFF);
Hires::writeLeftChan(3,d5,d3,d4,a1,a2);
}
}
}
}
(a2=0);
(d5=0);
(d2=M68k::setw(0,10000));
(d0=M68k::setw(0,Mem::uw(HiresData::IDNUM)));
(a3=HiresData::RIGHTCHANDATA);
(d1=M68k::setw(0,3));
bool foundRight=false;
while(true){
if((Mem::b(a3) == 0)) {
if((int16_t(Mem::uw(j_add(a3,32))) == int16_t(d0))) {
(d6=M68k::setw(0,d5));
(foundRight=true);
break;
}
if((int16_t(d2) >= int16_t(Mem::uw(j_add(a3,2))))) {
(d2=M68k::setw(d2,Mem::uw(j_add(a3,2))));
(a2=a3);
(d6=M68k::setw(0,d5));
}
}
(a3+=4);
(d5=M68k::setw(d5,j_add(d5,1)));
(d1=M68k::setw(d1,(d1 - 1)));
if((int16_t(d1) == -(1))) break;
}
if(!(foundRight)) (a3=a2);
(d5=a3);
if((d5 == 0)) return ;
if((int16_t(d2) > int16_t(Mem::uw(HiresData::noiseloud)))) return ;
Hires::makeNoiseChannel(a3,d0);
(d5=M68k::setw(0,Mem::uw(HiresData::Aud_SampleNum_w)));
(a3=TablesBss::Aud_SampleList_vl);
(a1=j_add(Mem::l(j_add(a3,((d5 & 0xFFFF) * 8))),Mem::l(HiresData::RIGHTOFFSET)));
(a2=j_add(Mem::l(j_add(j_add(a3,((d5 & 0xFFFF) * 8)),4)),Mem::l(HiresData::RIGHTOFFSET)));
Mem::wb(HiresData::NoiseMade0RIGHT,((d6 == 0)?0xFF:0));
if((d6 == 0)) Hires::writeRightChan(0,d5,d3,d4,a1,a2);
else {
Mem::wb(HiresData::NoiseMade1RIGHT,((d6 < 2)?0xFF:0));
if((d6 < 2)) Hires::writeRightChan(1,d5,d3,d4,a1,a2);
else {
Mem::wb(HiresData::NoiseMade2RIGHT,((d6 == 2)?0xFF:0));
if((d6 == 2)) Hires::writeRightChan(2,d5,d3,d4,a1,a2);
else {
Mem::wb(HiresData::NoiseMade3RIGHT,0xFF);
Hires::writeRightChan(3,d5,d3,d4,a1,a2);
}
}
}
}

int32_t makeNoiseChannel(int32_t a3,int32_t d0){
if(((d0 & 0xFFFF) == 0xFFFF)) (d0=M68k::setw(d0,0xFFFE));
Mem::ww(j_add(a3,32),d0);
Mem::ww(j_add(a3,2),Mem::uw(HiresData::noiseloud));
return d0;
}

bool sampleAddrOK(int32_t addr){
return ((addr >= 0) && (addr < (int32_t(Mem::RAM.size()) - 256)));
}

std::vector<int32_t> guardSample(int32_t a1,int32_t a2,int32_t sampleNum){
if((!(Hires::sampleAddrOK(a1)) || !(Hires::sampleAddrOK(a2)))) {
if(!(Hires::dbgBadSampleLogged)) {
j_log(j_add(j_add(j_add(j_add(j_add(j_add("[audio] échantillon hors RAM ignoré : Aud_SampleNum=",sampleNum)," pos="),a1)," fin="),a2)," (canal silencé)"));
(Hires::dbgBadSampleLogged=true);
}
return std::vector<int32_t>{TablesBss::Aud_EmptyBuffer_vl,TablesBss::Aud_EmptyBufferEnd};
}
return std::vector<int32_t>{a1,a2};
}

void writeLeftChan(int32_t chan,int32_t d5,int32_t d3,int32_t d4,int32_t a1,int32_t a2){
std::vector<int32_t> g=Hires::guardSample(a1,a2,d5);
(a1=g[0]);
(a2=g[1]);
int32_t t=j_add(HiresData::LEFTPLAYEDTAB,(chan * 3));
Mem::wb(t,d5);
Mem::wb(j_add(t,1),d3);
Mem::wb(j_add(t,2),d4);
switch(chan){
case 0:
{Mem::wl(HiresData::pos0LEFT,a1);
Mem::wl(HiresData::Samp0endLEFT,a2);
Mem::wb(HiresData::vol0left,d3);
break;
}
case 1:
{Mem::wb(HiresData::vol1left,d3);
Mem::wl(HiresData::pos1LEFT,a1);
Mem::wl(HiresData::Samp1endLEFT,a2);
break;
}
case 2:
{Mem::wl(HiresData::pos2LEFT,a1);
Mem::wl(HiresData::Samp2endLEFT,a2);
Mem::wb(HiresData::vol2left,d3);
break;
}
default:
{Mem::wb(HiresData::vol3left,d3);
Mem::wl(HiresData::pos3LEFT,a1);
Mem::wl(HiresData::Samp3endLEFT,a2);
break;
}
}
}

void writeRightChan(int32_t chan,int32_t d5,int32_t d3,int32_t d4,int32_t a1,int32_t a2){
std::vector<int32_t> g=Hires::guardSample(a1,a2,d5);
(a1=g[0]);
(a2=g[1]);
int32_t t=j_add(HiresData::RIGHTPLAYEDTAB,(chan * 3));
Mem::wb(t,d5);
Mem::wb(j_add(t,1),d3);
Mem::wb(j_add(t,2),d4);
switch(chan){
case 0:
{Mem::wl(HiresData::pos0RIGHT,a1);
Mem::wl(HiresData::Samp0endRIGHT,a2);
Mem::wb(HiresData::vol0right,d4);
break;
}
case 1:
{Mem::wb(HiresData::vol1right,d3);
Mem::wl(HiresData::pos1RIGHT,a1);
Mem::wl(HiresData::Samp1endRIGHT,a2);
break;
}
case 2:
{Mem::wl(HiresData::pos2RIGHT,a1);
Mem::wl(HiresData::Samp2endRIGHT,a2);
Mem::wb(HiresData::vol2right,d3);
break;
}
default:
{Mem::wb(HiresData::vol3right,d4);
Mem::wl(HiresData::pos3RIGHT,a1);
Mem::wl(HiresData::Samp3endRIGHT,a2);
break;
}
}
}

void makeNoiseMono(int32_t d3,int32_t d4,int32_t d0prev){
int32_t a2=0;
int32_t d5=-(1);
int32_t d2=M68k::setw(0,32767);
int32_t d0=M68k::setw(0,Mem::uw(HiresData::IDNUM));
int32_t a3=HiresData::CHANNELDATA;
int32_t d1=M68k::setw(0,7);
int32_t d6=-(1);
bool foundMine=false;
while(true){
if((Mem::b(a3) == 0)) {
if((int16_t(Mem::uw(j_add(a3,32))) == int16_t(d0))) {
(foundMine=true);
break;
}
if((int16_t(Mem::uw(j_add(a3,2))) >= int16_t(d2))) {
(d2=M68k::setw(d2,Mem::uw(j_add(a3,2))));
(a2=a3);
(d6=M68k::setw(d5,j_add(d5,1)));
}
}
(a3+=4);
(d5=M68k::setw(d5,j_add(d5,1)));
(d1=M68k::setw(d1,(d1 - 1)));
if((int16_t(d1) == -(1))) break;
}
if(foundMine) {
(d2=M68k::setw(d2,Mem::uw(j_add(a3,2))));
(d6=M68k::setw(d5,j_add(d5,1)));
}
else {
(a3=a2);
}
if((int16_t(d6) < 0)) return ;
if((int16_t(d2) > int16_t(Mem::uw(HiresData::noiseloud)))) return ;
Hires::makeNoiseChannel(a3,d0);
(d5=M68k::setw(0,Mem::uw(HiresData::Aud_SampleNum_w)));
(a3=TablesBss::Aud_SampleList_vl);
int32_t a1=Mem::l(j_add(a3,((d5 & 0xFFFF) * 8)));
(a2=Mem::l(j_add(j_add(a3,((d5 & 0xFFFF) * 8)),4)));
switch(int8_t(d6)){
case 0:
{Mem::wb(HiresData::NoiseMade0LEFT,0xFF);
Hires::writeLeftChan(0,d5,d3,d4,a1,a2);
break;
}
case 1:
{Mem::wb(HiresData::NoiseMade1LEFT,0xFF);
Hires::writeLeftChan(1,d5,d3,d4,a1,a2);
break;
}
case 2:
{Mem::wb(HiresData::NoiseMade2LEFT,0xFF);
Hires::writeLeftChan(2,d5,d3,d4,a1,a2);
break;
}
case 3:
{Mem::wb(HiresData::NoiseMade3LEFT,0xFF);
Hires::writeLeftChan(3,d5,d3,d4,a1,a2);
break;
}
case 4:
{Mem::wb(HiresData::NoiseMade0RIGHT,0xFF);
Hires::writeRightChan(0,d5,d3,d4,a1,a2);
break;
}
case 5:
{Mem::wb(HiresData::NoiseMade1RIGHT,0xFF);
Hires::writeRightChan(1,d5,d3,d4,a1,a2);
break;
}
case 6:
{Mem::wb(HiresData::NoiseMade2RIGHT,0xFF);
Hires::writeRightChan(2,d5,d3,d4,a1,a2);
break;
}
default:
{Mem::wb(HiresData::NoiseMade3RIGHT,0xFF);
Hires::writeRightChan(3,d5,d3,d4,a1,a2);
break;
}
}
}

void startup(){
int32_t d0=SystemC::Sys_Init();
if((d0 == 0)) {
Hires::startup_fail();
return ;
}
Mem::wb(PlayerBss::Plr1_Mouse_b,~(Mem::b(PlayerBss::Plr1_Mouse_b)));
Mem::wb(PlayerBss::Plr2_Mouse_b,~(Mem::b(PlayerBss::Plr2_Mouse_b)));
Mem::ww(PlayerBss::Plr1_Energy_w,191);
Mem::ww(PlayerBss::Plr2_Energy_w,191);
Mem::ww(ZoneBss::Zone_OrderTable_Barrier_w,~(Mem::w(ZoneBss::Zone_OrderTable_Barrier_w)));
Mem::wb(HiresData::draw_GouraudFlatsSelected_b,0xFF);
DevInst::Dev_Init();
Mem::wb(PlayerBss::Plr1_Keys_b,0);
Mem::wb(PlayerBss::Plr1_Path_b,0);
Mem::wb(PlayerBss::Plr1_Mouse_b,0xFF);
Mem::wb(PlayerBss::Plr1_Joystick_b,0);
Mem::wb(PlayerBss::Plr2_Keys_b,0);
Mem::wb(PlayerBss::Plr2_Path_b,0);
Mem::wb(PlayerBss::Plr2_Mouse_b,0xFF);
Mem::wb(PlayerBss::Plr2_Joystick_b,0);
int32_t a0=TablesBss::ConstantTable_vl;
(d0=1);
int32_t d1=8191;
do {
int32_t d2=(16384 * 64);
(d2=j_div(d2,d0));
int32_t d3=((64 * 64) * 65536);
(d3=j_div(d3,d2));
Mem::wl(a0,d3);
(a0+=4);
(d2=j_shr(d2,1));
(d2=(d2 - (40 * 64)));
(d2=(d2 * d3));
(d2=j_shr(d2,6));
Mem::wl(a0,d2);
(a0+=4);
(d0+=1);
}
while((--(d1) != -(1)));
Controlloop::Game_Start();
Hires::startup_fail();
}

void startup_fail(){
SystemC::Sys_Done();
}

void Game_Begin(){
if((Mem::b(PlayerBss::Plr_MultiplayerType_b) == Hires::PLR_SINGLE)) {
ScreenC::Game_ShowIntroText();
}
Controlloop::SETPLAYERS();
Res::Res_LoadLevelData();
DevInst::Dev_DataReset();
Message::Msg_Init();
GameProgress::Game_LevelBegin();
int32_t a0=Mem::l(LevelBss::Lvl_GraphicsPtr_l);
int32_t a1=j_add(Mem::l(j_add(a0,Defs::TLGT_DoorDataOffset_l)),a0);
Mem::wl(LevelBss::Lvl_DoorDataPtr_l,a1);
(a1=j_add(Mem::l(j_add(a0,Defs::TLGT_LiftDataOffset_l)),a0));
Mem::wl(LevelBss::Lvl_LiftDataPtr_l,a1);
(a1=j_add(Mem::l(j_add(a0,Defs::TLGT_SwitchDataOffset_l)),a0));
Mem::wl(LevelBss::Lvl_SwitchDataPtr_l,a1);
(a1=j_add(Mem::l(j_add(a0,Defs::TLGT_ZoneGraphAddsOffset_l)),a0));
Mem::wl(LevelBss::Lvl_ZoneGraphAddsPtr_l,a1);
(a0=j_add(a0,int16_t(Defs::TLGT_ZoneAddsOffset_l)));
Mem::wl(LevelBss::Lvl_ZonePtrsPtr_l,a0);
int32_t a4=Mem::l(LevelBss::Lvl_DataPtr_l);
(a1=j_add(a4,(Defs::LVLT_MESSAGE_LENGTH * Defs::LVLT_MESSAGE_COUNT)));
int32_t a2=j_add(a1,Defs::TLBT_SizeOf_l);
Mem::wl(LevelBss::Lvl_ControlPointCoordsPtr_l,a2);
Mem::ww(LevelBss::Lvl_NumControlPoints_w,Mem::uw(j_add(a1,Defs::TLBT_NumControlPoints_w)));
Mem::ww(LevelBss::Lvl_NumPoints_w,Mem::uw(j_add(a1,Defs::TLBT_NumPoints_w)));
(a2=j_add(Mem::l(j_add(a1,Defs::TLBT_PointsOffset_l)),a4));
Mem::wl(LevelBss::Lvl_PointsPtr_l,a2);
int32_t d0=Mem::uw(j_add(a1,Defs::TLBT_NumPoints_w));
(a2=j_add(j_add(a2,4),(d0 * 4)));
Mem::wl(TablesBss::PointBrightsPtr_l,a2);
(d0=Mem::uw(j_add(a1,Defs::TLBT_NumZones_w)));
(d0=j_add(d0,1));
Mem::ww(LevelBss::Lvl_NumZones_w,d0);
(d0=M68k::muls(d0,80));
(a2=j_add(a2,d0));
Mem::wl(LevelBss::Lvl_ZoneBorderPointsPtr_l,a2);
(a2=Mem::l(j_add(a1,Defs::TLBT_FloorLineOffset_l)));
(d0=Mem::l(j_add(a1,Defs::TLBT_ObjectDataOffset_l)));
(d0=(d0 - a2));
Mem::wl(LevelBss::Lvl_EdgeCount_l,d0);
(a2=j_add(a2,a4));
Mem::wl(LevelBss::Lvl_ZoneEdgePtr_l,a2);
Mem::ww(HiresData::Lvl_ExitZoneID_w,Mem::w((a2 - 2)));
(a2=j_add(Mem::l(j_add(a1,Defs::TLBT_ObjectDataOffset_l)),a4));
Mem::wl(LevelBss::Lvl_ObjectDataPtr_l,a2);
if(j_equals("1",j_property("dumpRawObj"))) {
int32_t o=(a2 - 64);
for(int32_t n=0;(n < 130);(n)++){
(o+=64);
if((Mem::w(o) < 0)) break;
if(((Mem::ub(j_add(o,16)) == 1) && (Mem::ub(j_add(o,54)) == 9))) {
JStringBuilder sb=JStringBuilder();
for(int32_t b=0;(b < 64);(b)++)sb.append(' ').append(b).append('=').append(Mem::ub(j_add(o,b)));
j_log(sb);
}
}
}
(a2=j_add(Mem::l(j_add(a1,Defs::TLBT_ShotDataOffset_l)),a4));
Mem::wl(PlayerBss::Plr_ShotDataPtr_l,a2);
(a2=j_add(Mem::l(j_add(a1,Defs::TLBT_AlienShotDataOffset_l)),a4));
Mem::wl(LevelBss::AI_AlienShotDataPtr_l,a2);
(a2=j_add(a2,(Defs::ShotT_SizeOf_l * Defs::NUM_ALIEN_SHOT_DATA)));
Mem::wl(AiBss::AI_OtherAlienDataPtrs_vl,a2);
(a2=j_add(Mem::l(j_add(a1,Defs::TLBT_ObjectPointsOffset_l)),a4));
Mem::wl(LevelBss::Lvl_ObjectPointsPtr_l,a2);
(a2=j_add(Mem::l(j_add(a1,Defs::TLBT_Plr1ObjectOffset_l)),a4));
Mem::wl(PlayerBss::Plr1_ObjectPtr_l,a2);
(a2=j_add(Mem::l(j_add(a1,Defs::TLBT_Plr2ObjectOffset_l)),a4));
Mem::wl(PlayerBss::Plr2_ObjectPtr_l,a2);
Mem::ww(LevelBss::Lvl_NumObjectPoints_w,Mem::uw(j_add(a1,Defs::TLBT_NumObjects_w)));
(a2=Mem::l(LevelBss::Lvl_ClipsPtr_l));
(d0=0);
int32_t d7=Mem::uw(j_add(a1,Defs::TLBT_NumZones_w));
Mem::ww(NewanimsData::Zone_Count_w,d7);
do {
int32_t a3=j_add(Mem::l(a0),a4);
Mem::wl(a0,a3);
(a0+=4);
(a3=j_add(a3,Defs::ZoneT_PotVisibleZoneList_vw));
while((Mem::w(a3) >= 0)){
if((Mem::w(j_add(a3,Defs::PVST_ClipID_w)) >= 0)) {
int32_t d1=j_shr(d0,1);
Mem::ww(j_add(a3,Defs::PVST_ClipID_w),d1);
while((Mem::w(j_add(a2,d0)) != -(2))){
(d0+=2);
}
(d0+=2);
}
(a3+=Defs::PVST_SizeOf_l);
}
}
while((--(d7) != -(1)));
(a2=j_add(a2,d0));
Mem::wl(LevelBss::Lvl_ConnectTablePtr_l,a2);
if(!(DevMacros::DEV_TEST(DevInst::Dev_DebugFlags_l,DevMacros::DEV_SKIP_PVS_AMEND))) {
if((Mem::l(LevelBss::Lvl_ErrataPtr_l) != 0)) {
ZoneErrata::Zone_ApplyPVSErrata(Mem::l(LevelBss::Lvl_ErrataPtr_l));
}
}
ZoneEdgePvs::Zone_InitEdgePVS();
Mem::wb(PlayerBss::Plr1_StoodInTop_b,0);
Mem::wl(PlayerBss::Plr1_SnapHeight_l,Hires::PLR_STAND_HEIGHT);
Mem::wl(HiresData::pos1LEFT,TablesBss::Aud_EmptyBuffer_vl);
Mem::wl(HiresData::pos2LEFT,TablesBss::Aud_EmptyBuffer_vl);
Mem::wl(HiresData::pos1RIGHT,TablesBss::Aud_EmptyBuffer_vl);
Mem::wl(HiresData::pos2RIGHT,TablesBss::Aud_EmptyBuffer_vl);
Mem::wl(HiresData::pos0LEFT,TablesBss::Aud_EmptyBuffer_vl);
Mem::wl(HiresData::pos3LEFT,TablesBss::Aud_EmptyBuffer_vl);
Mem::wl(HiresData::pos0RIGHT,TablesBss::Aud_EmptyBuffer_vl);
Mem::wl(HiresData::pos3RIGHT,TablesBss::Aud_EmptyBuffer_vl);
Mem::wl(HiresData::Samp0endLEFT,TablesBss::Aud_EmptyBufferEnd);
Mem::wl(HiresData::Samp1endLEFT,TablesBss::Aud_EmptyBufferEnd);
Mem::wl(HiresData::Samp0endRIGHT,TablesBss::Aud_EmptyBufferEnd);
Mem::wl(HiresData::Samp1endRIGHT,TablesBss::Aud_EmptyBufferEnd);
Mem::wl(HiresData::Samp2endLEFT,TablesBss::Aud_EmptyBufferEnd);
Mem::wl(HiresData::Samp3endLEFT,TablesBss::Aud_EmptyBufferEnd);
Mem::wl(HiresData::Samp2endRIGHT,TablesBss::Aud_EmptyBufferEnd);
Mem::wl(HiresData::Samp3endRIGHT,TablesBss::Aud_EmptyBufferEnd);
CustomChips::ciaBset(1);
Player::Plr_Initialise();
CustomChips::write32(0xdff0a0,HiresData::Aud_Null1_vw);
CustomChips::write16(0xdff0a4,100);
CustomChips::write16(0xdff0a6,443);
CustomChips::write16(0xdff0a8,63);
CustomChips::write32(0xdff0b0,HiresData::Aud_Null2_vw);
CustomChips::write16(0xdff0b4,100);
CustomChips::write16(0xdff0b6,443);
CustomChips::write16(0xdff0b8,63);
CustomChips::write32(0xdff0c0,HiresData::Aud_Null4_vw);
CustomChips::write16(0xdff0c4,100);
CustomChips::write16(0xdff0c6,443);
CustomChips::write16(0xdff0c8,63);
CustomChips::write32(0xdff0d0,HiresData::Aud_Null3_vw);
CustomChips::write16(0xdff0d4,100);
CustomChips::write16(0xdff0d6,443);
CustomChips::write16(0xdff0d8,63);
int32_t aTab=HiresData::tab;
(d7=64);
int32_t d6=0;
do {
int32_t aPre=HiresData::pretab;
int32_t d5=255;
do {
(d0=Mem::b(aPre));
(aPre)++;
(d0=M68k::muls(d0,d6));
(d0=j_shr(d0,6));
Mem::wb(aTab,d0);
(aTab)++;
}
while((--(d5) != -(1)));
(d6+=1);
}
while((--(d7) != -(1)));
CustomChips::write16(0xdff096,Hires::DMAF_AUDIO);
CustomChips::write16(0xdff096,((Hires::DMAF_SETCLR | Hires::DMAF_MASTER) | Hires::DMAF_AUDIO));
Mem::ww(NewanimsData::Conditions,0);
if((Mem::b(PlayerBss::Plr_MultiplayerType_b) != Hires::PLR_SINGLE)) {
Mem::ww(NewanimsData::Conditions,0xFFF);
}
Mem::wb(j_add(TablesBss::KeyMap_vb,RawKeyMacros::RAWKEY_ESC),0);
Mem::wl(Music::mt_data,Mem::l(HiresData::Lvl_MusicPtr_l));
Mem::wb(HiresData::UseAllChannels,0);
Mem::wb(HiresData::CHANNELDATA,0xFF);
Music::mt_init();
Mem::wb(HiresData::CHANNELDATA,0xFF);
Mem::wb(j_add(HiresData::CHANNELDATA,8),0xFF);
Mem::wl(HiresData::pos0LEFT,Mem::l(j_add(TablesBss::Aud_SampleList_vl,(6 * 8))));
Mem::wl(HiresData::Samp0endLEFT,Mem::l(j_add(j_add(TablesBss::Aud_SampleList_vl,(6 * 8)),4)));
Mem::wl(PlayerBss::Plr1_SnapTargHeight_l,Hires::PLR_STAND_HEIGHT);
Mem::wl(PlayerBss::Plr1_SnapHeight_l,Hires::PLR_STAND_HEIGHT);
Mem::wl(PlayerBss::Plr2_SnapTargHeight_l,Hires::PLR_STAND_HEIGHT);
Mem::wl(PlayerBss::Plr2_SnapHeight_l,Hires::PLR_STAND_HEIGHT);
SystemC::Sys_ClearKeyboard();
Mem::wb(HiresData::Game_MasterQuit_b,0);
Mem::wb(HiresData::Game_SlaveQuit_b,((Mem::b(PlayerBss::Plr_MultiplayerType_b) == Hires::PLR_SINGLE)?0xFF:0));
Mem::wl(HiresData::hitcol,0);
Mem::wb(PlayerBss::Plr1_Ducked_b,0);
Mem::wb(PlayerBss::Plr2_Ducked_b,0);
Mem::wb(PlayerBss::plr1_TmpDucked_b,0);
Mem::wb(PlayerBss::plr2_TmpDucked_b,0);
Mem::wb(HiresData::Game_Running_b,0xFF);
Mem::wb(HiresData::dosounds,0xFF);
Ai::AI_InitAlienWorkspace();
(a0=TablesBss::Lvl_CompactMap_vl);
Mem::wl(HiresData::LastZonePtr_l,a0);
Sys::Sys_MemFillLong(a0,0,256);
Mem::ww(HiresData::Vid_CentreX_w,j_div(Hires::SMALL_WIDTH,2));
Mem::ww(HiresData::Vid_RightX_w,Hires::SMALL_WIDTH);
Mem::ww(HireswallData::Vid_BottomY_w,Hires::SMALL_HEIGHT);
Mem::ww(HireswallData::TOTHEMIDDLE,j_div(Hires::SMALL_HEIGHT,2));
Mem::wb(VidBss::Vid_FullScreen_b,0);
DrawC::Draw_ResetGameDisplay();
Mem::wb(j_add(PlayerBss::Plr1_Weapons_vb,1),0xFF);
Mem::wb(j_add(PlayerBss::Plr2_Weapons_vb,1),0xFF);
Mem::ww(HiresData::timetodamage,100);
(d0=299);
(a0=AiBss::AI_Damaged_vw);
do {
Mem::ww(a0,0);
(a0+=2);
}
while((--(d0) != -(1)));
(d0=0);
Mem::ww(HireswallData::STOPOFFSET,d0);
(d0=-(d0));
(d0=int16_t(j_add(d0,Mem::w(HireswallData::TOTHEMIDDLE))));
Mem::ww(HireswallData::SMIDDLEY,d0);
(d0=M68k::muls(d0,Hires::SCREEN_WIDTH));
Mem::wl(HireswallData::SBIGMIDDLEY,d0);
Mem::ww(PlayerBss::Plr1_AimSpeed_l,0);
Mem::ww(PlayerBss::Plr2_AimSpeed_l,0);
Mem::wl(VidBss::Vid_DisplayScreenPtr_l,Mem::l(VidBss::Vid_Screen1Ptr_l));
Mem::wl(VidBss::Vid_DrawScreenPtr_l,Mem::l(VidBss::Vid_Screen2Ptr_l));
Mem::wl(SystemBss::Sys_FrameNumber_l,0);
SystemC::Sys_MarkTime(SystemBss::Sys_PrevFrameTimeECV_q);
Mem::wb(PlayerBss::Plr2_Fire_b,0);
Mem::wb(PlayerBss::Plr2_TmpFire_b,0);
Mem::wb(PlayerBss::Plr2_Used_b,0);
Mem::wb(PlayerBss::Plr2_TmpSpcTap_b,0);
Mem::wb(PlayerBss::plr1_Dead_b,0);
Mem::wb(PlayerBss::plr2_Dead_b,0);
(a0=Mem::l(PlayerBss::Plr1_ObjectPtr_l));
(a1=Mem::l(PlayerBss::Plr2_ObjectPtr_l));
Mem::ww(j_add(a0,Defs::EntT_ImpactX_w),0);
Mem::ww(j_add(a0,Defs::EntT_ImpactY_w),0);
Mem::ww(j_add(a0,Defs::EntT_ImpactZ_w),0);
Mem::ww(j_add(a1,Defs::EntT_ImpactX_w),0);
Mem::ww(j_add(a1,Defs::EntT_ImpactY_w),0);
Mem::ww(j_add(a1,Defs::EntT_ImpactZ_w),0);
Mem::wl(PlayerBss::Plr1_SnapXSpdVal_l,0);
Mem::wl(PlayerBss::Plr1_SnapZSpdVal_l,0);
Mem::wl(PlayerBss::Plr1_SnapYVel_l,0);
Mem::wl(PlayerBss::Plr2_SnapXSpdVal_l,0);
Mem::wl(PlayerBss::Plr2_SnapZSpdVal_l,0);
Mem::wl(PlayerBss::Plr2_SnapYVel_l,0);
if((Mem::b(VidBss::Vid_FullScreen_b) != 0)) {
Mem::ww(HiresData::View_KeyLook_w,6);
(d0=j_div(Hires::FS_HEIGHT,2));
Mem::ww(HiresData::View_LookMin_w,d0);
(d0=-(d0));
Mem::ww(HiresData::View_LookMax_w,d0);
}
else {
Mem::ww(HiresData::View_KeyLook_w,4);
(d0=j_div(Hires::SMALL_HEIGHT,2));
Mem::ww(HiresData::View_LookMin_w,d0);
(d0=-(d0));
Mem::ww(HiresData::View_LookMax_w,d0);
}
if((Mem::b(VidBss::Vid_DoubleHeight_b) != 0)) {
Mem::wb(HiresData::LASTDH,0xFF);
Hires::startCopper();
ScreenC::vid_SetupDoubleheightCopperlist();
}
Hires::game_main_loop();
}

void game_main_loop(){
int32_t a2=AiBss::AI_AlienTeamWorkspace_vl;
while(true){
Hires::dbgAiTrace();
Hires::dbgPlayerTrace();
if(Hires::dbgWalk) {
Mem::wb(j_add(TablesBss::KeyMap_vb,Mem::ub(ControlloopData::forward_key)),0xFF);
}
if(((Hires::loopFrameLimit >= 0) && ((Hires::loopFrameLimit)-- == 0))) return ;
if((Hires::headless && Hires::headlessStop)) return ;
if((Hires::loopFrameLimit < 0)) {
DisplayHandle* d=ScreenC::hostDisplay();
if(((d != nullptr) && d->shouldClose())) return ;
}
{
Hires::VBlankInterrupt();
}
if((((Mem::b(PlayerBss::Plr_MultiplayerType_b) == Hires::PLR_MASTER) && (Mem::b(PlayerBss::plr2_Dead_b) == 0)) && !((int16_t(Mem::w(PlayerBss::Plr2_Health_w)) > 0)))) {
Mem::wb(PlayerBss::plr2_Dead_b,0xFF);
int32_t d0=Objectmove::GetRand();
(d0=M68k::swap(d0));
(d0=M68k::setw(d0,0));
(d0=M68k::swap(d0));
(d0=M68k::divs(d0,9));
(d0=M68k::swap(d0));
(d0=M68k::muls(d0,Defs::GAME_DM_VICTORY_MESSAGE_LENGTH));
(d0=j_add(d0,TextData::Game_TwoPlayerVictoryMessages_vb));
int32_t aMsg=d0;
Message::Msg_PushLine(aMsg,Defs::GAME_DM_VICTORY_MESSAGE_LENGTH);
int32_t a0=Mem::l(PlayerBss::Plr2_ObjectPtr_l);
int32_t a6=j_add(Mem::l(HiresData::GLF_DatabasePtr_l),Defs::GLFT_Player2Graphic_w);
int32_t d7=Mem::w(a6);
int32_t d1=d7;
(a6=j_add(Mem::l(HiresData::GLF_DatabasePtr_l),Defs::GLFT_AlienDefs_l));
(d1=M68k::muls(d1,Defs::AlienT_SizeOf_l));
(a6=j_add(a6,d1));
Mem::wb(AnimBss::Anim_SplatType_w,Mem::b(j_add(j_add(a6,Defs::AlienT_SplatType_w),1)));
int32_t a1=Mem::l(PlayerBss::Plr2_ZonePtr_l);
Mem::ww(j_add(a0,Defs::ObjT_ZoneID_w),Mem::w(a1));
Mem::ww(ObjectmoveData::newx,Mem::w(PlayerBss::Plr2_TmpXOff_l));
Mem::ww(ObjectmoveData::newz,Mem::w(PlayerBss::Plr2_TmpZOff_l));
int32_t d2=7;
Newanims::Anim_ExplodeIntoBits(0,d2,0,a0);
Macros::FREE_OBJ(a0);
}
if((((Mem::b(PlayerBss::Plr_MultiplayerType_b) == Hires::PLR_SLAVE) && (Mem::b(PlayerBss::plr1_Dead_b) == 0)) && !((int16_t(Mem::w(PlayerBss::Plr1_Health_w)) > 0)))) {
Mem::wb(PlayerBss::plr1_Dead_b,0xFF);
int32_t d0=Objectmove::GetRand();
(d0=M68k::swap(d0));
(d0=M68k::setw(d0,0));
(d0=M68k::swap(d0));
(d0=M68k::divs(d0,9));
(d0=M68k::swap(d0));
(d0=M68k::muls(d0,Defs::GAME_DM_VICTORY_MESSAGE_LENGTH));
(d0=j_add(d0,TextData::Game_TwoPlayerVictoryMessages_vb));
Message::Msg_PushLine(d0,Defs::GAME_DM_VICTORY_MESSAGE_LENGTH);
int32_t a0=Mem::l(PlayerBss::Plr1_ObjectPtr_l);
int32_t a6=j_add(Mem::l(HiresData::GLF_DatabasePtr_l),Defs::GLFT_Player1Graphic_w);
int32_t d7=Mem::w(a6);
int32_t d1=d7;
(a6=j_add(Mem::l(HiresData::GLF_DatabasePtr_l),Defs::GLFT_AlienDefs_l));
(d1=M68k::muls(d1,Defs::AlienT_SizeOf_l));
(a6=j_add(a6,d1));
Mem::wb(AnimBss::Anim_SplatType_w,Mem::b(j_add(j_add(a6,Defs::AlienT_SplatType_w),1)));
int32_t a1=Mem::l(PlayerBss::Plr1_ZonePtr_l);
Mem::ww(j_add(a0,Defs::ObjT_ZoneID_w),Mem::w(a1));
Mem::ww(ObjectmoveData::newx,Mem::w(PlayerBss::Plr1_TmpXOff_l));
Mem::ww(ObjectmoveData::newz,Mem::w(PlayerBss::Plr1_TmpZOff_l));
Newanims::Anim_ExplodeIntoBits(0,7,0,a0);
Macros::FREE_OBJ(a0);
}
Mem::wb(HiresData::draw_RenderMap_b,Mem::b(HiresData::MAPON));
if((Mem::b(j_add(TablesBss::KeyMap_vb,RawKeyMacros::RAWKEY_NUM_ENTER)) != 0)) {
if(!(Hires::fsToggleHeld)) {
Mem::wb(VidBss::Vid_FullScreenTemp_b,((Mem::b(VidBss::Vid_FullScreenTemp_b) == 0)?0xFF:0));
(Hires::fsToggleHeld=true);
}
}
else {
(Hires::fsToggleHeld=false);
}
if((((Mem::b(VidBss::Vid_FullScreenTemp_b) ^ Mem::b(VidBss::Vid_FullScreen_b)) & 0xFF) != 0)) {
Mem::wb(VidBss::Vid_FullScreen_b,Mem::b(VidBss::Vid_FullScreenTemp_b));
Hires::SetupRenderbufferSize();
ScreenC::vid_SetupDoubleheightCopperlist();
}
if(((Mem::b(PlayerBss::Plr_MultiplayerType_b) == Hires::PLR_SINGLE) && (Mem::b(j_add(TablesBss::KeyMap_vb,RawKeyMacros::RAWKEY_P)) != 0))) {
Mem::wb(HiresData::Game_Running_b,0);
do {
if((Mem::b(PlayerBss::Plr1_Joystick_b) != 0)) Cd32joy::_ReadJoy1();
}
while((Mem::b(j_add(TablesBss::KeyMap_vb,RawKeyMacros::RAWKEY_P)) != 0));
Pauseopts::Game_Pause();
Mem::wb(HiresData::Game_Running_b,0xFF);
}
Mem::wb(HiresData::READCONTROLS,0xFF);
if((Mem::b(PlayerBss::Plr_MultiplayerType_b) != Hires::PLR_SINGLE)) {
int32_t d0=((Mem::b(HiresData::Game_SlavePaused_b) | Mem::b(HiresData::Game_MasterPaused_b)) & 0xFF);
if((d0 != 0)) {
Mem::wb(HiresData::Game_Running_b,0);
do {
if((Mem::b(PlayerBss::Plr_MultiplayerType_b) == Hires::PLR_SLAVE)) {
if((Mem::b(PlayerBss::Plr2_Joystick_b) != 0)) Cd32joy::_ReadJoy2();
}
else if((Mem::b(PlayerBss::Plr1_Joystick_b) != 0)) {
Cd32joy::_ReadJoy1();
}
}
while((Mem::b(j_add(TablesBss::KeyMap_vb,RawKeyMacros::RAWKEY_P)) != 0));
Pauseopts::Game_Pause();
if((Mem::b(PlayerBss::Plr_MultiplayerType_b) == Hires::PLR_MASTER)) SerialNightmare::SENDFIRST(0);
else SerialNightmare::RECFIRST(0);
Mem::wb(HiresData::Game_SlavePaused_b,0);
Mem::wb(HiresData::Game_MasterPaused_b,0);
Mem::wb(HiresData::Game_Running_b,0xFF);
}
}
int32_t fpsLimit=Mem::w(Hires::SystemBss_Sys_FPSLimit_w());
int32_t swp=Mem::l(VidBss::Vid_DrawScreenPtr_l);
Mem::wl(VidBss::Vid_DrawScreenPtr_l,Mem::l(VidBss::Vid_DisplayScreenPtr_l));
Mem::wl(VidBss::Vid_DisplayScreenPtr_l,swp);
if((Mem::b(PlayerBss::Plr_MultiplayerType_b) == Hires::PLR_SLAVE)) {
Mem::wb(PlayerBss::plr_GunSelected_b,Mem::b(PlayerBss::Plr2_GunSelected_b));
}
else {
Mem::wb(PlayerBss::plr_GunSelected_b,Mem::b(PlayerBss::Plr1_GunSelected_b));
}
SystemC::Sys_FrameLap();
DevInst::Dev_PrintStats();
DevInst::Dev_MarkFrameBegin();
int32_t d0=Mem::l(HireswallData::SMIDDLEY);
int32_t d1=Mem::l(j_add(HireswallData::SMIDDLEY,4));
Mem::wl(HireswallData::Vid_CentreY_w,d0);
Mem::wl(j_add(HireswallData::Vid_CentreY_w,4),d1);
int32_t wp=Mem::l(HiresData::draw_LastWaterFramePtr_l);
Mem::wl(HiresData::draw_WaterFramePtr_l,Mem::l(wp));
(wp+=4);
if((wp >= HiresData::draw_EndWaterFramePtrs_l)) {
(wp=HiresData::draw_WaterFramePtrs_vl);
}
Mem::wl(HiresData::draw_LastWaterFramePtr_l,wp);
Mem::ww(HiresData::wtan,TablesData::AMOD_I(M68k::setw(Mem::w(HiresData::wtan),j_add(Mem::w(HiresData::wtan),640))));
Mem::wl(HiresData::wateroff,(j_add(Mem::l(HiresData::wateroff),1) & 0x3fff3fff));
Mem::wl(PlayerBss::plr1_OldX_l,Mem::l(PlayerBss::Plr1_XOff_l));
Mem::wl(PlayerBss::plr1_OldZ_l,Mem::l(PlayerBss::Plr1_ZOff_l));
Mem::wl(PlayerBss::plr2_OldX_l,Mem::l(PlayerBss::Plr2_XOff_l));
Mem::wl(PlayerBss::plr2_OldZ_l,Mem::l(PlayerBss::Plr2_ZOff_l));
int32_t mpt=Mem::b(PlayerBss::Plr_MultiplayerType_b);
if((mpt == Hires::PLR_SLAVE)) {
Hires::loop_SlaveBlock(a2);
}
else if((mpt == Hires::PLR_SINGLE)) {
int32_t gd0=Mem::ub(PlayerBss::plr_GunSelected_b);
int32_t a6=j_add(Mem::l(HiresData::GLF_DatabasePtr_l),Defs::GLFT_ShootDefs_l);
(gd0=Mem::w(j_add(a6,(gd0 * 8))));
(a6=PlayerBss::Plr1_AmmoCounts_vw);
(gd0=Mem::w(j_add(a6,(gd0 * 2))));
Mem::ww(DrawBss::draw_DisplayAmmoCount_w,gd0);
Mem::ww(DrawBss::draw_DisplayEnergyCount_w,Mem::w(PlayerBss::Plr1_Health_w));
Hires::loop_FrameClampAndSnapshot1();
Hires::Plr1_Control(a2);
int32_t a0=Mem::l(PlayerBss::Plr1_ZonePtr_l);
Mem::wl(HiresData::Zone_SplitHeight_l,Mem::l(j_add(a0,Defs::ZoneT_Roof_l)));
Mem::ww(NewaliencontrolData::THISPLRxoff,Mem::w(PlayerBss::Plr1_TmpXOff_l));
Mem::ww(NewaliencontrolData::THISPLRzoff,Mem::w(PlayerBss::Plr1_TmpZOff_l));
Mem::wl(PlayerBss::Plr2_TmpYOff_l,0x60000);
(a0=Mem::l(PlayerBss::Plr2_ObjectPtr_l));
Macros::FREE_ENT(a0);
Mem::wb(j_add(a0,Defs::ObjT_SeePlayer_b),0);
Mem::wl(PlayerBss::Plr2_ZonePtr_l,HiresData::BollocksRoom);
}
else {
Hires::loop_MasterBlock(a2);
}
int32_t potVis=((mpt == Hires::PLR_SLAVE)?Mem::l(PlayerBss::Plr2_PotVisibleZoneListPtr_l):Mem::l(PlayerBss::Plr1_PotVisibleZoneListPtr_l));
Hires::computeZoneBrightness(potVis);
int32_t a0=Mem::l(PlayerBss::Plr1_ZonePtr_l);
int32_t a1=TablesBss::CurrentPointBrights_vl;
int32_t a2b=Mem::l(Hires::LevelBss_Lvl_ZoneBorderPointsPtr_l());
int32_t wd0=Mem::w(a0);
(wd0=M68k::muls(wd0,10));
(a2b=j_add(a2b,(int16_t(wd0) * 2)));
(a1=j_add(a1,(int16_t(wd0) * 8)));
int32_t wd7=9;
int32_t sumIdx=0;
int32_t sumBr=0;
do {
int32_t v=Mem::w(a2b);
(a2b+=2);
if((v < 0)) break;
(sumIdx+=1);
int32_t br=Mem::w(a1);
(a1+=2);
if((br < 0)) (br=-(int16_t(br)));
(sumBr=M68k::setw(sumBr,j_add(sumBr,br)));
}
while((--(wd7) != -(1)));
int32_t avg=sumBr;
(avg=j_div(avg,((sumIdx == 0)?1:sumIdx)));
(avg=M68k::setw(avg,(avg - 300)));
Mem::ww(PlayerBss::Plr1_RoomBright_w,avg);
if((mpt != Hires::PLR_SINGLE)) {
Mem::wl(ObjectmoveData::Obj_FromZonePtr_l,Mem::l(PlayerBss::Plr1_ZonePtr_l));
Mem::wl(ObjectmoveData::Obj_ToZonePtr_l,Mem::l(PlayerBss::Plr2_ZonePtr_l));
Mem::ww(ObjectmoveData::Viewerx,Mem::w(PlayerBss::Plr1_TmpXOff_l));
Mem::ww(ObjectmoveData::Viewerz,Mem::w(PlayerBss::Plr1_TmpZOff_l));
Mem::ww(ObjectmoveData::Viewery,j_shr(Mem::l(PlayerBss::Plr1_TmpYOff_l),7));
Mem::ww(ObjectmoveData::Targetx,Mem::w(PlayerBss::Plr2_TmpXOff_l));
Mem::ww(ObjectmoveData::Targetz,Mem::w(PlayerBss::Plr2_TmpZOff_l));
Mem::ww(ObjectmoveData::Targety,j_shr(Mem::l(PlayerBss::Plr2_TmpYOff_l),7));
Mem::wb(ObjectmoveData::ViewerTop,Mem::b(PlayerBss::Plr1_StoodInTop_b));
Mem::wb(ObjectmoveData::TargetTop,Mem::b(PlayerBss::Plr2_StoodInTop_b));
Objectmove::CanItBeSeen();
int32_t o1=Mem::l(PlayerBss::Plr1_ObjectPtr_l);
Mem::wb(j_add(o1,Defs::ObjT_SeePlayer_b),(Mem::b(ObjectmoveData::CanSee) & 2));
int32_t o2=Mem::l(PlayerBss::Plr2_ObjectPtr_l);
Mem::wb(j_add(o2,Defs::ObjT_SeePlayer_b),(Mem::b(ObjectmoveData::CanSee) & 1));
}
Hires::loop_HoldAndDiffs();
if((mpt == Hires::PLR_SLAVE)) Hires::Plr2_Use();
else Hires::Plr1_Use();
{
if((mpt == Hires::PLR_SLAVE)) {
Hires::loop_DrawPlayer2();
}
else {
Hires::loop_DrawPlayer1();
}
}
int32_t d5=((Mem::b(PlayerBss::plr1_Teleported_b) | Mem::b(PlayerBss::plr2_Teleported_b)) & 0xFF);
Mem::wb(C2pData::C2P_Teleporting_b,d5);
Mem::wb(C2pData::C2P_NeedsInit_b,(Mem::b(C2pData::C2P_NeedsInit_b) | d5));
Mem::wb(PlayerBss::plr1_Teleported_b,0);
Mem::wb(PlayerBss::plr1_Teleported_b,0);
SystemC::Sys_EvalFPS();
DevInst::Dev_MarkDrawDone();
DevInst::Dev_DrawGraph();
if((Mem::b(VidData::Vid_UpdatePalette_b) == 0)) {
ScreenC::Vid_LoadMainPalette();
}
if((Mem::l(GameBss::Game_ProgressSignal_l) != 0)) {
GameProgress::Game_UpdatePlayerProgress();
}
{
if((Hires::frameSync != nullptr)) Hires::frameSync();
}
Hires::loop_ScreenSizeKeys();
Hires::markVisibleAndWorry();
(a2=AiBss::AI_AlienTeamWorkspace_vl);
if((Mem::b(j_add(TablesBss::KeyMap_vb,RawKeyMacros::RAWKEY_ESC)) != 0)) {
if((mpt == Hires::PLR_SLAVE)) Mem::wb(HiresData::Game_SlaveQuit_b,0xFF);
else Mem::wb(HiresData::Game_MasterQuit_b,0xFF);
}
if(((Mem::b(HiresData::Game_MasterQuit_b) != 0) && (Mem::b(HiresData::Game_SlaveQuit_b) != 0))) {
Hires::endnomusic();
return ;
}
if((mpt == Hires::PLR_SINGLE)) {
int32_t zp=Mem::l(PlayerBss::Plr1_ZonePtr_l);
if((Mem::w(zp) == Mem::w(HiresData::Lvl_ExitZoneID_w))) {
int32_t tv=j_add(Mem::uw(C2pData::Game_TeleportFrame_w),2);
Mem::ww(C2pData::Game_TeleportFrame_w,tv);
if((tv >= 9)) {
Hires::endlevel();
return ;
}
}
}
if(!((int16_t(Mem::w(PlayerBss::Plr1_Health_w)) > 0))) {
Hires::endlevel();
return ;
}
if(!((int16_t(Mem::w(PlayerBss::Plr2_Health_w)) > 0))) {
Hires::endlevel();
return ;
}
}
}

int32_t SystemBss_Sys_FPSLimit_w(){
return SystemBss::Sys_FPSLimit_w;
}

int32_t LevelBss_Lvl_ZoneBorderPointsPtr_l(){
return LevelBss::Lvl_ZoneBorderPointsPtr_l;
}

void WaitTOF(){
{
Mem::wl(HiresData::Vid_VBLCount_l,j_add(Mem::l(HiresData::Vid_VBLCount_l),1));
return ;
}
Vbl::waitNext();
Hires::VBlankInterrupt();
}

void loop_FrameClampAndSnapshot1(){
Mem::ww(AnimBss::Anim_TempFrames_w,Mem::w(AnimBss::Anim_FramesToDraw_w));
if((int16_t(Mem::w(AnimBss::Anim_TempFrames_w)) >= 15)) Mem::ww(AnimBss::Anim_TempFrames_w,15);
Mem::ww(AnimBss::Anim_FramesToDraw_w,0);
Mem::wl(PlayerBss::Plr1_TmpXOff_l,Mem::l(PlayerBss::Plr1_SnapXOff_l));
Mem::wl(PlayerBss::Plr1_TmpZOff_l,Mem::l(PlayerBss::Plr1_SnapZOff_l));
Mem::wl(PlayerBss::Plr1_TmpYOff_l,Mem::l(PlayerBss::Plr1_SnapYOff_l));
Mem::wl(PlayerBss::plr1_TmpHeight_l,Mem::l(PlayerBss::Plr1_SnapHeight_l));
Mem::ww(PlayerBss::Plr1_TmpAngPos_w,Mem::w(PlayerBss::Plr1_SnapAngPos_w));
Mem::ww(PlayerBss::plr1_TmpBobble_w,Mem::w(PlayerBss::Plr1_Bobble_w));
Mem::wb(PlayerBss::Plr1_TmpClicked_b,Mem::b(PlayerBss::Plr1_Clicked_b));
Mem::wb(PlayerBss::Plr1_TmpFire_b,Mem::b(PlayerBss::Plr1_Fire_b));
Mem::wb(PlayerBss::Plr1_Clicked_b,0);
Mem::wb(PlayerBss::Plr1_TmpSpcTap_b,Mem::b(PlayerBss::Plr1_Used_b));
Mem::wb(PlayerBss::Plr1_Used_b,0);
Mem::wb(PlayerBss::plr1_TmpDucked_b,Mem::b(PlayerBss::Plr1_Ducked_b));
Mem::wb(PlayerBss::Plr1_TmpGunSelected_b,Mem::b(PlayerBss::Plr1_GunSelected_b));
}

void loop_HoldAndDiffs(){
int32_t d0=Mem::w(AnimBss::Anim_TempFrames_w);
Mem::ww(PlayerBss::plr1_TmpHoldDown_w,j_add(Mem::w(PlayerBss::plr1_TmpHoldDown_w),d0));
if((int16_t(Mem::w(PlayerBss::plr1_TmpHoldDown_w)) >= 30)) Mem::ww(PlayerBss::plr1_TmpHoldDown_w,30);
if((Mem::b(PlayerBss::Plr1_TmpFire_b) == 0)) {
int32_t v=int16_t((Mem::w(PlayerBss::plr1_TmpHoldDown_w) - d0));
if((v < 0)) (v=0);
Mem::ww(PlayerBss::plr1_TmpHoldDown_w,v);
}
Mem::ww(PlayerBss::plr2_TmpHoldDown_w,j_add(Mem::w(PlayerBss::plr2_TmpHoldDown_w),d0));
if((int16_t(Mem::w(PlayerBss::plr2_TmpHoldDown_w)) >= 30)) Mem::ww(PlayerBss::plr2_TmpHoldDown_w,30);
if((Mem::b(PlayerBss::Plr2_TmpFire_b) == 0)) {
int32_t v=int16_t((Mem::w(PlayerBss::plr2_TmpHoldDown_w) - d0));
if((v < 0)) (v=0);
Mem::ww(PlayerBss::plr2_TmpHoldDown_w,v);
}
int32_t d1=Mem::w(AnimBss::Anim_TempFrames_w);
if(!((int16_t(d1) > 0))) (d1=1);
int32_t dd=int16_t((Mem::w(PlayerBss::Plr1_XOff_l) - Mem::w(PlayerBss::plr1_OldX_l)));
(dd=M68k::setw(dd,j_shl(dd,4)));
(dd=int16_t(dd));
(dd=j_div(dd,d1));
Mem::ww(HiresData::XDiff_w,dd);
(dd=int16_t((Mem::w(PlayerBss::Plr2_XOff_l) - Mem::w(PlayerBss::plr2_OldX_l))));
(dd=M68k::setw(dd,j_shl(dd,4)));
(dd=int16_t(dd));
(dd=j_div(dd,d1));
(dd=int16_t((Mem::w(PlayerBss::Plr1_ZOff_l) - Mem::w(PlayerBss::plr1_OldZ_l))));
(dd=M68k::setw(dd,j_shl(dd,4)));
(dd=int16_t(dd));
(dd=j_div(dd,d1));
Mem::ww(HiresData::ZDiff_w,dd);
(dd=int16_t((Mem::w(PlayerBss::Plr2_ZOff_l) - Mem::w(PlayerBss::plr2_OldZ_l))));
(dd=M68k::setw(dd,j_shl(dd,4)));
(dd=int16_t(dd));
(dd=j_div(dd,d1));
}

void loop_DrawPlayer1(){
Mem::ww(HiresData::scaleval,0);
Mem::wl(HiresData::Plr_XOff_l,Mem::l(PlayerBss::Plr1_XOff_l));
Mem::wl(HiresData::Plr_YOff_l,Mem::l(PlayerBss::Plr1_YOff_l));
Mem::wl(HiresData::Plr_ZOff_l,Mem::l(PlayerBss::Plr1_ZOff_l));
Mem::ww(HiresData::Vis_AngPos_w,Mem::w(PlayerBss::Plr1_AngPos_w));
Mem::ww(HireswallData::Vis_CosVal_w,Mem::w(PlayerBss::Plr1_CosVal_w));
Mem::ww(HireswallData::Vis_SinVal_w,Mem::w(PlayerBss::Plr1_SinVal_w));
Mem::wl(LevelBss::Lvl_ListOfGraphRoomsPtr_l,Mem::l(PlayerBss::Plr1_PotVisibleZoneListPtr_l));
Mem::wl(LevelBss::PointsToRotatePtr_l,Mem::l(PlayerBss::plr1_PointsToRotatePtr_l));
Mem::wb(HiresData::PLREcho,Mem::b(PlayerBss::Plr1_Echo_b));
Mem::wl(HiresData::ZonePtr_l,Mem::l(PlayerBss::Plr1_ZonePtr_l));
int32_t d5=Mem::ub(ControlloopData::look_behind_key);
if((Mem::b(j_add(TablesBss::KeyMap_vb,d5)) != 0)) {
int32_t a0=Mem::l(PlayerBss::Plr1_ObjectPtr_l);
Macros::FREE_OBJ_2(a0,Defs::ENT_NEXT_2);
Mem::ww(HiresData::Vis_AngPos_w,(Mem::w(HiresData::Vis_AngPos_w) ^ TablesData::SINE_SIZE));
Mem::ww(HireswallData::Vis_CosVal_w,-(Mem::w(HireswallData::Vis_CosVal_w)));
Mem::ww(HireswallData::Vis_SinVal_w,-(Mem::w(HireswallData::Vis_SinVal_w)));
}
if((Mem::b(ControlloopData::Prefs_ShowWeapon_b) != 0)) {
Macros::FREE_OBJ_2(Mem::l(PlayerBss::Plr1_ObjectPtr_l),Defs::ENT_NEXT_2);
}
Orderzones::Zone_OrderZones();
Newanims::objmoveanim();
Mem::wb(HiresData::DOANYWATER,0xFF);
Mem::wl(HiresData::Plr_YOff_l,Mem::l(PlayerBss::Plr1_YOff_l));
Hires::loop_SetClips();
Hires::DrawDisplay();
}

void loop_DrawPlayer2(){
Mem::ww(HiresData::scaleval,0);
Mem::wl(HiresData::Plr_XOff_l,Mem::l(PlayerBss::Plr2_XOff_l));
Mem::wl(HiresData::Plr_YOff_l,Mem::l(PlayerBss::Plr2_YOff_l));
Mem::wl(HiresData::Plr_ZOff_l,Mem::l(PlayerBss::Plr2_ZOff_l));
Mem::ww(HiresData::Vis_AngPos_w,Mem::w(PlayerBss::Plr2_AngPos_w));
Mem::ww(HireswallData::Vis_CosVal_w,Mem::w(PlayerBss::Plr2_CosVal_w));
Mem::ww(HireswallData::Vis_SinVal_w,Mem::w(PlayerBss::Plr2_SinVal_w));
Mem::wl(LevelBss::Lvl_ListOfGraphRoomsPtr_l,Mem::l(PlayerBss::Plr2_PotVisibleZoneListPtr_l));
Mem::wl(LevelBss::PointsToRotatePtr_l,Mem::l(PlayerBss::plr2_PointsToRotatePtr_l));
Mem::wb(HiresData::PLREcho,Mem::b(PlayerBss::Plr2_Echo_b));
Mem::wl(HiresData::ZonePtr_l,Mem::l(PlayerBss::Plr2_ZonePtr_l));
int32_t d5=Mem::ub(ControlloopData::look_behind_key);
if((Mem::b(j_add(TablesBss::KeyMap_vb,d5)) != 0)) {
int32_t a0=Mem::l(PlayerBss::Plr1_ObjectPtr_l);
Macros::FREE_OBJ_2(a0,Defs::ENT_NEXT_2);
Mem::ww(HiresData::Vis_AngPos_w,(Mem::w(HiresData::Vis_AngPos_w) ^ TablesData::SINE_SIZE));
Mem::ww(HireswallData::Vis_CosVal_w,-(Mem::w(HireswallData::Vis_CosVal_w)));
Mem::ww(HireswallData::Vis_SinVal_w,-(Mem::w(HireswallData::Vis_SinVal_w)));
}
if((Mem::b(ControlloopData::Prefs_ShowWeapon_b) != 0)) {
Macros::FREE_OBJ_2(Mem::l(PlayerBss::Plr1_ObjectPtr_l),Defs::ENT_NEXT_2);
}
Orderzones::Zone_OrderZones();
Newanims::objmoveanim();
Hires::loop_SetClips();
Mem::wb(HiresData::DOANYWATER,0xFF);
Hires::DrawDisplay();
}

void loop_SetClips(){
int32_t d0=Mem::w(VidBss::Vid_LetterBoxMarginHeight_w);
Mem::ww(HireswallData::Draw_LeftClip_w,0);
Mem::ww(HireswallData::Draw_RightClip_w,Mem::w(HiresData::Vid_RightX_w));
Mem::ww(HireswallData::draw_TopClip_w,j_add(0,d0));
Mem::ww(HireswallData::draw_BottomClip_w,int16_t((Mem::w(HireswallData::Vid_BottomY_w) - d0)));
}

void computeZoneBrightness(int32_t listPtr){
int32_t a1=ZoneBss::Zone_BrightTable_vl;
int32_t a2=Mem::l(LevelBss::Lvl_ZonePtrsPtr_l);
int32_t a0=listPtr;
int32_t a5=a0;
int32_t d0{};
while(((d0=Mem::w(a0)) >= 0)){
(a0+=8);
int32_t a3=Mem::l(j_add(a2,(int16_t(d0) * 4)));
int32_t d2=Mem::w(j_add(a3,Defs::ZoneT_Brightness_w));
if((d2 >= 0)) {
int32_t d3=j_ushr((d2 & 0xFFFF),8);
if((int8_t(d3) != 0)) {
(d2=Mem::w((j_add(AnimBss::Anim_BrightTable_vw,(int16_t(d3) * 2)) - 2)));
}
}
(d2=M68k::muls(d2,410));
(d2=j_shr(d2,8));
Mem::ww(j_add(a1,(int16_t(d0) * 4)),d2);
(d2=Mem::w(j_add(a3,Defs::ZoneT_UpperBrightness_w)));
if((d2 >= 0)) {
int32_t d3=j_ushr((d2 & 0xFFFF),8);
if((int8_t(d3) != 0)) {
(d2=Mem::w((j_add(AnimBss::Anim_BrightTable_vw,(int16_t(d3) * 2)) - 2)));
}
}
(d2=M68k::muls(d2,410));
(d2=j_shr(d2,8));
Mem::ww(j_add(j_add(a1,(int16_t(d0) * 4)),2),d2);
}
int32_t a2p=Mem::l(TablesBss::PointBrightsPtr_l);
int32_t a3=TablesBss::CurrentPointBrights_vl;
while(((d0=Mem::w(a5)) >= 0)){
(a5+=8);
(d0=M68k::muls(d0,40));
int32_t d7=39;
do {
int32_t d2=Mem::w(j_add(a2p,(int16_t(d0) * 2)));
if(!((int8_t(d2) < 0))) {
int32_t d3=j_ushr((d2 & 0xFFFF),8);
if((int8_t(d3) != 0)) {
int32_t d4=d3;
(d3=(d3 & 0xf));
(d4=j_ushr((d4 & 0xFFFF),4));
(d4=j_add(d4,1));
(d3=Mem::w((j_add(AnimBss::Anim_BrightTable_vw,(int16_t(d3) * 2)) - 2)));
(d2=M68k::extw(d2));
(d3=M68k::setw(d3,(d3 - d2)));
(d3=M68k::muls(d3,d4));
(d3=M68k::asrw(d3,4));
(d2=M68k::setw(d2,j_add(d2,d3)));
}
}
(d2=M68k::extw(d2));
(d2=M68k::muls(d2,397));
(d2=j_shr(d2,8));
if(!((int16_t(d2) >= 0))) (d2=M68k::setw(d2,(d2 - 600)));
(d2=M68k::setw(d2,j_add(d2,300)));
Mem::ww(j_add(a3,(int16_t(d0) * 2)),d2);
(d0=j_add(d0,1));
}
while((--(d7) != -(1)));
}
}

void markVisibleAndWorry(){
int32_t a0=Mem::l(PlayerBss::Plr2_ZonePtr_l);
int32_t a1=SystemBss::Sys_Workspace_vl;
for(int32_t i=0;(i < 32);(i+=4))Mem::wl(j_add(a1,i),0);
int32_t d0{};
int32_t d1{};
if((Mem::b(PlayerBss::Plr_MultiplayerType_b) != Hires::PLR_SINGLE)) {
(a0=j_add(a0,Defs::ZoneT_PotVisibleZoneList_vw));
while(((d0=Mem::w(a0)) >= 0)){
(a0+=Defs::PVST_SizeOf_l);
(d1=d0);
(d0=M68k::asrw(d0,3));
int32_t adr=j_add(a1,int16_t(d0));
Mem::wb(adr,(Mem::ub(adr) | j_shl(1,(d1 & 7))));
}
}
(a0=Mem::l(PlayerBss::Plr1_ZonePtr_l));
(a0=j_add(a0,Defs::ZoneT_PotVisibleZoneList_vw));
while(((d0=Mem::w(a0)) >= 0)){
(a0+=Defs::PVST_SizeOf_l);
(d1=d0);
(d0=M68k::asrw(d0,3));
int32_t adr=j_add(a1,int16_t(d0));
Mem::wb(adr,(Mem::ub(adr) | j_shl(1,(d1 & 7))));
}
int32_t d7=0b000001;
int32_t a2=AiBss::AI_AlienTeamWorkspace_vl;
(a0=Mem::l(Hires::PlayerBss_Lvl_ObjectDataPtr_l()));
(a0=(a0 - Defs::ObjT_SizeOf_l));
while(true){
(a0+=Defs::ObjT_SizeOf_l);
(d0=Mem::w(a0));
if((d0 < 0)) break;
(d0=Mem::w(j_add(a0,Defs::ObjT_ZoneID_w)));
if((d0 < 0)) continue;
(d1=d0);
(d0=M68k::asrw(d0,3));
bool worry=((Mem::ub(j_add(a1,int16_t(d0))) & j_shl(1,(d1 & 7))) != 0);
if(!(worry)) {
int32_t typ=Mem::ub(j_add(a0,Defs::ObjT_TypeID_b));
if(((d7 & j_shl(1,(typ & 31))) == 0)) continue;
int32_t team=Mem::b(j_add(a0,Defs::EntT_TeamNumber_b));
if((team < 0)) continue;
(team=M68k::setw(team,j_shl(team,4)));
if((int16_t(Mem::w(j_add(j_add(a2,int16_t(team)),Ai::AI_WorkT_SeenBy_w))) < 0)) continue;
}
Mem::wb(j_add(a0,Defs::ShotT_Worry_b),(Mem::b(j_add(a0,Defs::ShotT_Worry_b)) | 127));
}
}

int32_t PlayerBss_Lvl_ObjectDataPtr_l(){
return LevelBss::Lvl_ObjectDataPtr_l;
}

void loop_ScreenSizeKeys(){
int32_t a5=TablesBss::KeyMap_vb;
if((Mem::b(j_add(a5,RawKeyMacros::RAWKEY_NUM_MINUS)) != 0)) {
int32_t d0=100;
if((Mem::b(VidBss::Vid_FullScreen_b) == 0)) (d0=60);
if(!((int16_t(d0) < Mem::w(VidBss::Vid_LetterBoxMarginHeight_w)))) {
Mem::ww(VidBss::Vid_LetterBoxMarginHeight_w,j_add(Mem::w(VidBss::Vid_LetterBoxMarginHeight_w),2));
Mem::wb(C2pData::C2P_NeedsSetParam_b,0xFF);
DrawC::Draw_ResetGameDisplay();
ScreenC::vid_SetupDoubleheightCopperlist();
}
}
if((Mem::b(j_add(a5,RawKeyMacros::RAWKEY_NUM_PLUS)) != 0)) {
if((int16_t(Mem::w(VidBss::Vid_LetterBoxMarginHeight_w)) > 0)) {
Mem::ww(VidBss::Vid_LetterBoxMarginHeight_w,(Mem::w(VidBss::Vid_LetterBoxMarginHeight_w) - 2));
Mem::wb(C2pData::C2P_NeedsSetParam_b,0xFF);
ScreenC::vid_SetupDoubleheightCopperlist();
}
}
if((Mem::b(j_add(a5,RawKeyMacros::RAWKEY_F9)) != 0)) {
Mem::wb(j_add(a5,RawKeyMacros::RAWKEY_F9),0);
if((Mem::b(HiresData::LASTDH) == 0)) {
Mem::wb(HiresData::LASTDH,0xFF);
Mem::wb(VidBss::Vid_DoubleHeight_b,~(Mem::b(VidBss::Vid_DoubleHeight_b)));
Mem::wb(C2pData::C2P_NeedsInit_b,0xFF);
Hires::SetupRenderbufferSize();
ScreenC::vid_SetupDoubleheightCopperlist();
}
}
else {
Mem::wb(HiresData::LASTDH,0);
}
if((Mem::b(j_add(a5,RawKeyMacros::RAWKEY_F8)) != 0)) {
Mem::wb(j_add(a5,RawKeyMacros::RAWKEY_F8),0);
if((Mem::b(HiresData::LASTDW) == 0)) {
Mem::wb(DrawBss::Draw_ForceSimpleWalls_b,~(Mem::b(DrawBss::Draw_ForceSimpleWalls_b)));
}
}
else {
Mem::wb(HiresData::LASTDW,0);
}
}

void loop_MasterBlock(int32_t a2){
Mem::wb(HiresData::Game_MasterPaused_b,((Mem::b(j_add(TablesBss::KeyMap_vb,RawKeyMacros::RAWKEY_P)) != 0)?0xFF:0));
Mem::ww(DrawBss::draw_DisplayEnergyCount_w,Mem::w(PlayerBss::Plr1_Health_w));
int32_t gd0=Mem::ub(PlayerBss::plr_GunSelected_b);
int32_t a6=j_add(Mem::l(HiresData::GLF_DatabasePtr_l),Defs::GLFT_ShootDefs_l);
(gd0=Mem::w(j_add(a6,(gd0 * 8))));
(a6=PlayerBss::Plr1_AmmoCounts_vw);
(gd0=Mem::w(j_add(a6,(gd0 * 2))));
Mem::ww(DrawBss::draw_DisplayAmmoCount_w,gd0);
SerialNightmare::SENDFIRST(0);
Hires::loop_FrameClampAndSnapshot1();
int32_t r{};
(r=SerialNightmare::SENDFIRST(Mem::l(PlayerBss::Plr1_AimSpeed_l)));
Mem::wl(PlayerBss::Plr2_AimSpeed_l,r);
(r=SerialNightmare::SENDFIRST(Mem::l(PlayerBss::Plr1_TmpXOff_l)));
Mem::wl(PlayerBss::Plr2_TmpXOff_l,r);
(r=SerialNightmare::SENDFIRST(Mem::l(PlayerBss::Plr1_TmpZOff_l)));
Mem::wl(PlayerBss::Plr2_TmpZOff_l,r);
(r=SerialNightmare::SENDFIRST(Mem::l(PlayerBss::Plr1_TmpYOff_l)));
Mem::wl(PlayerBss::Plr2_TmpYOff_l,r);
(r=SerialNightmare::SENDFIRST(Mem::l(PlayerBss::plr1_TmpHeight_l)));
Mem::wl(PlayerBss::plr2_TmpHeight_l,r);
int32_t send=(j_shl((Mem::w(PlayerBss::Plr1_TmpAngPos_w) & 0xFFFF),16) | (Mem::w(PlayerBss::plr1_TmpBobble_w) & 0xFFFF));
(r=SerialNightmare::SENDFIRST(send));
Mem::ww(PlayerBss::plr2_TmpBobble_w,(r & 0xFFFF));
Mem::ww(PlayerBss::Plr2_TmpAngPos_w,(j_ushr(r,16) & 0xFFFF));
(send=((j_shl((Mem::w(AnimBss::Anim_TempFrames_w) & 0xFFFF),16) | (j_shl(Mem::ub(PlayerBss::Plr1_TmpSpcTap_b),8) & 0xFF00)) | Mem::ub(PlayerBss::Plr1_TmpClicked_b)));
(r=SerialNightmare::SENDFIRST(send));
Mem::wb(PlayerBss::Plr2_TmpClicked_b,(r & 0xFF));
Mem::wb(PlayerBss::Plr2_TmpSpcTap_b,(j_shr(r,8) & 0xFF));
(send=((j_shl((Mem::w(ObjectmoveData::Rand1) & 0xFFFF),16) | (j_shl((Mem::ub(PlayerBss::plr1_TmpDucked_b) | Mem::ub(PlayerBss::Plr1_Squished_b)),8) & 0xFF00)) | Mem::ub(PlayerBss::Plr1_TmpGunSelected_b)));
(r=SerialNightmare::SENDFIRST(send));
Mem::wb(PlayerBss::Plr2_TmpGunSelected_b,(r & 0xFF));
Mem::wb(PlayerBss::plr2_TmpDucked_b,(j_shr(r,8) & 0xFF));
Mem::wb(HiresData::Game_SlaveQuit_b,((Mem::b(HiresData::Game_SlaveQuit_b) | Mem::b(HiresData::Game_MasterQuit_b)) & 0xFF));
Mem::wb(HiresData::Game_SlavePaused_b,((Mem::b(HiresData::Game_SlavePaused_b) | Mem::b(HiresData::Game_MasterPaused_b)) & 0xFF));
(send=(j_shl((j_shl(Mem::ub(PlayerBss::Plr1_TmpFire_b),8) | Mem::ub(HiresData::Game_MasterQuit_b)),16) | Mem::ub(HiresData::Game_MasterPaused_b)));
(r=SerialNightmare::SENDFIRST(send));
Mem::wb(HiresData::Game_MasterPaused_b,((Mem::b(HiresData::Game_MasterPaused_b) | (r & 0xFF)) & 0xFF));
Mem::wb(HiresData::Game_SlavePaused_b,((Mem::b(HiresData::Game_SlavePaused_b) | (r & 0xFF)) & 0xFF));
int32_t hi=(j_ushr(r,16) & 0xFFFF);
Mem::wb(HiresData::Game_SlaveQuit_b,((Mem::b(HiresData::Game_SlaveQuit_b) | (hi & 0xFF)) & 0xFF));
Mem::wb(HiresData::Game_MasterQuit_b,((Mem::b(HiresData::Game_MasterQuit_b) | (hi & 0xFF)) & 0xFF));
Mem::wb(PlayerBss::Plr2_TmpFire_b,(j_shr(hi,8) & 0xFF));
(r=SerialNightmare::SENDFIRST((Mem::w(PlayerBss::Plr1_Health_w) & 0xFFFF)));
Mem::ww(PlayerBss::Plr2_Health_w,(r & 0xFFFF));
Hires::Plr1_Control(a2);
Hires::Plr2_Control(a2);
int32_t a0=Mem::l(PlayerBss::Plr1_ZonePtr_l);
Mem::wl(HiresData::Zone_SplitHeight_l,Mem::l(j_add(a0,Defs::ZoneT_Roof_l)));
Mem::ww(NewaliencontrolData::THISPLRxoff,Mem::w(PlayerBss::Plr1_TmpXOff_l));
Mem::ww(NewaliencontrolData::THISPLRzoff,Mem::w(PlayerBss::Plr1_TmpZOff_l));
}

void loop_SlaveBlock(int32_t a2){
Mem::wb(HiresData::Game_SlavePaused_b,((Mem::b(j_add(TablesBss::KeyMap_vb,RawKeyMacros::RAWKEY_P)) != 0)?0xFF:0));
int32_t gd0=Mem::ub(PlayerBss::plr_GunSelected_b);
int32_t a6=j_add(Mem::l(HiresData::GLF_DatabasePtr_l),Defs::GLFT_ShootDefs_l);
(gd0=Mem::w(j_add(a6,(gd0 * 8))));
(a6=PlayerBss::Plr2_AmmoCounts_vw);
(gd0=Mem::w(j_add(a6,(gd0 * 2))));
Mem::ww(DrawBss::draw_DisplayAmmoCount_w,gd0);
Mem::ww(DrawBss::draw_DisplayEnergyCount_w,Mem::w(PlayerBss::Plr2_Health_w));
SerialNightmare::RECFIRST(0);
Mem::wl(PlayerBss::Plr2_TmpXOff_l,Mem::l(PlayerBss::Plr2_SnapXOff_l));
Mem::wl(PlayerBss::Plr2_TmpZOff_l,Mem::l(PlayerBss::Plr2_SnapZOff_l));
Mem::wl(PlayerBss::Plr2_TmpYOff_l,Mem::l(PlayerBss::Plr2_SnapYOff_l));
Mem::wl(PlayerBss::plr2_TmpHeight_l,Mem::l(PlayerBss::Plr2_SnapHeight_l));
Mem::ww(PlayerBss::Plr2_TmpAngPos_w,Mem::w(PlayerBss::Plr2_SnapAngPos_w));
Mem::ww(PlayerBss::plr2_TmpBobble_w,Mem::w(PlayerBss::Plr2_Bobble_w));
Mem::wb(PlayerBss::Plr2_TmpClicked_b,Mem::b(PlayerBss::Plr2_Clicked_b));
Mem::wb(PlayerBss::Plr2_Clicked_b,0);
Mem::wb(PlayerBss::Plr2_TmpFire_b,Mem::b(PlayerBss::Plr2_Fire_b));
Mem::wb(PlayerBss::Plr2_TmpSpcTap_b,Mem::b(PlayerBss::Plr2_Used_b));
Mem::wb(PlayerBss::Plr2_Used_b,0);
Mem::wb(PlayerBss::plr2_TmpDucked_b,Mem::b(PlayerBss::Plr2_Ducked_b));
Mem::wb(PlayerBss::Plr2_TmpGunSelected_b,Mem::b(PlayerBss::Plr2_GunSelected_b));
int32_t r{};
(r=SerialNightmare::RECFIRST(Mem::l(PlayerBss::Plr2_AimSpeed_l)));
Mem::wl(PlayerBss::Plr1_AimSpeed_l,r);
(r=SerialNightmare::RECFIRST(Mem::l(PlayerBss::Plr2_TmpXOff_l)));
Mem::wl(PlayerBss::Plr1_TmpXOff_l,r);
(r=SerialNightmare::RECFIRST(Mem::l(PlayerBss::Plr2_TmpZOff_l)));
Mem::wl(PlayerBss::Plr1_TmpZOff_l,r);
(r=SerialNightmare::RECFIRST(Mem::l(PlayerBss::Plr2_TmpYOff_l)));
Mem::wl(PlayerBss::Plr1_TmpYOff_l,r);
(r=SerialNightmare::RECFIRST(Mem::l(PlayerBss::plr2_TmpHeight_l)));
Mem::wl(PlayerBss::plr1_TmpHeight_l,r);
int32_t send=(j_shl((Mem::w(PlayerBss::Plr2_TmpAngPos_w) & 0xFFFF),16) | (Mem::w(PlayerBss::plr2_TmpBobble_w) & 0xFFFF));
(r=SerialNightmare::RECFIRST(send));
Mem::ww(PlayerBss::plr1_TmpBobble_w,(r & 0xFFFF));
Mem::ww(PlayerBss::Plr1_TmpAngPos_w,(j_ushr(r,16) & 0xFFFF));
(send=((j_shl(Mem::ub(PlayerBss::Plr2_TmpSpcTap_b),8) & 0xFF00) | Mem::ub(PlayerBss::Plr2_TmpClicked_b)));
(r=SerialNightmare::RECFIRST(send));
Mem::wb(PlayerBss::Plr1_TmpClicked_b,(r & 0xFF));
Mem::wb(PlayerBss::Plr1_TmpSpcTap_b,(j_shr(r,8) & 0xFF));
Mem::ww(AnimBss::Anim_TempFrames_w,(j_ushr(r,16) & 0xFFFF));
(send=((j_shl((Mem::ub(PlayerBss::plr2_TmpDucked_b) | Mem::ub(PlayerBss::Plr2_Squished_b)),8) & 0xFF00) | Mem::ub(PlayerBss::Plr2_TmpGunSelected_b)));
(r=SerialNightmare::RECFIRST(send));
Mem::wb(PlayerBss::Plr1_TmpGunSelected_b,(r & 0xFF));
Mem::wb(PlayerBss::plr1_TmpDucked_b,(j_shr(r,8) & 0xFF));
Mem::ww(ObjectmoveData::Rand1,(j_ushr(r,16) & 0xFFFF));
Mem::wb(HiresData::Game_MasterQuit_b,((Mem::b(HiresData::Game_MasterQuit_b) | Mem::b(HiresData::Game_SlaveQuit_b)) & 0xFF));
Mem::wb(HiresData::Game_MasterPaused_b,((Mem::b(HiresData::Game_MasterPaused_b) | Mem::b(HiresData::Game_SlavePaused_b)) & 0xFF));
(send=(j_shl((j_shl(Mem::ub(PlayerBss::Plr2_TmpFire_b),8) | Mem::ub(HiresData::Game_SlaveQuit_b)),16) | Mem::ub(HiresData::Game_SlavePaused_b)));
(r=SerialNightmare::RECFIRST(send));
Mem::wb(HiresData::Game_MasterPaused_b,((Mem::b(HiresData::Game_MasterPaused_b) | (r & 0xFF)) & 0xFF));
Mem::wb(HiresData::Game_SlavePaused_b,((Mem::b(HiresData::Game_SlavePaused_b) | (r & 0xFF)) & 0xFF));
int32_t hi=(j_ushr(r,16) & 0xFFFF);
Mem::wb(HiresData::Game_SlaveQuit_b,((Mem::b(HiresData::Game_SlaveQuit_b) | (hi & 0xFF)) & 0xFF));
Mem::wb(HiresData::Game_MasterQuit_b,((Mem::b(HiresData::Game_MasterQuit_b) | (hi & 0xFF)) & 0xFF));
Mem::wb(PlayerBss::Plr1_TmpFire_b,(j_shr(hi,8) & 0xFF));
(r=SerialNightmare::RECFIRST((Mem::w(PlayerBss::Plr2_Health_w) & 0xFFFF)));
Mem::ww(PlayerBss::Plr1_Health_w,(r & 0xFFFF));
Hires::Plr1_Control(a2);
Hires::Plr2_Control(a2);
if(Controlloop::coopMode) {
Mem::ww(NewaliencontrolData::THISPLRxoff,Mem::w(PlayerBss::Plr1_TmpXOff_l));
Mem::ww(NewaliencontrolData::THISPLRzoff,Mem::w(PlayerBss::Plr1_TmpZOff_l));
}
else {
Mem::ww(NewaliencontrolData::THISPLRxoff,Mem::w(PlayerBss::Plr2_TmpXOff_l));
Mem::ww(NewaliencontrolData::THISPLRzoff,Mem::w(PlayerBss::Plr2_TmpZOff_l));
}
int32_t a0=Mem::l(PlayerBss::Plr2_ZonePtr_l);
Mem::wl(HiresData::Zone_SplitHeight_l,Mem::l(j_add(a0,Defs::ZoneT_Roof_l)));
}

void endlevel(){
(Hires::presentationPhase=((Mem::w(PlayerBss::Plr1_Health_w) > 0)?1:2));
Mem::wb(HiresData::dosounds,0);
Mem::wb(HiresData::Game_Running_b,0);
Mem::ww(DrawBss::draw_DisplayEnergyCount_w,Mem::w(PlayerBss::Plr1_Health_w));
if((Mem::b(PlayerBss::Plr_MultiplayerType_b) == Hires::PLR_SLAVE)) {
Mem::ww(DrawBss::draw_DisplayEnergyCount_w,Mem::w(PlayerBss::Plr2_Health_w));
}
if((int16_t(Mem::w(DrawBss::draw_DisplayEnergyCount_w)) > 0)) {
GameProgress::Game_LevelWon();
CustomChips::write16(j_add(0xdff000,0x096),0xf);
if((Mem::b(PlayerBss::Plr_MultiplayerType_b) == Hires::PLR_SINGLE)) {
Mem::ww(ControlloopData::Game_LevelCounter_w,j_add(Mem::w(ControlloopData::Game_LevelCounter_w),1));
Mem::wb(ControlloopData::Game_FinishedLevel_b,0xFF);
}
Hires::playEndMusic(HiresData::welldone);
if(((Mem::b(PlayerBss::Plr_MultiplayerType_b) == Hires::PLR_SINGLE) && (Mem::w(ControlloopData::Game_LevelCounter_w) == Defs::NUM_LEVELS))) {
Mem::ww(ControlloopData::Game_LevelCounter_w,0);
}
}
else {
Mem::ww(DrawBss::draw_DisplayEnergyCount_w,0);
GameProgress::Game_LevelFailed();
Hires::playEndMusic(HiresData::gameover);
}
CustomChips::write16(j_add(0xdff000,0x096),0xf);
Hires::closeeverything();
}

void playEndMusic(int32_t musicData){
Mem::wl(Music::mt_data,musicData);
Mem::wb(HiresData::UseAllChannels,0xFF);
Mem::wb(Music::reachedend,0);
Music::mt_init();
const int64_t frameNs=20000000LL;
int64_t next=j_add(j_nanoTime(),frameNs);
for(int32_t g=0;((Mem::b(Music::reachedend) == 0) && (g < Hires::MUSIC_END_LOOP_CAP));(g)++){
DisplayHandle* d=ScreenC::hostDisplay();
if(((d != nullptr) && d->shouldClose())) {
break;
}
Hires::pumpAudioToHost();
{
if(Hires::headlessStop) break;
if((Hires::frameSync != nullptr)) Hires::frameSync();
}
Music::mt_music();
continue;
int64_t sleepNs=(next - j_nanoTime());
if((sleepNs > 0)) {
try{j_thread();
}catch(const std::exception& ie){j_thread().interrupt();
break;
}(next+=frameNs);
}
else {
(next=j_add(j_nanoTime(),frameNs));
}
}
}

void endnomusic(){
Mem::wb(HiresData::Game_Running_b,0);
Hires::closeeverything();
}

void closeeverything(){
Audio::stop();
Music::mt_end();
Res::Res_FreeLevelData();
Res::Res_ReleaseScreenMemory();
if((Mem::w(VidBss::Vid_isRTG) == 0)) {
Mem::ww(VidBss::Vid_ScreenBufferIndex_w,0);
}
}

void SetupRenderbufferSize(){
if((Mem::b(HiresData::LASTDH) != 0)) {
Hires::startCopper();
return ;
}
if((Mem::b(VidBss::Vid_FullScreen_b) == 0)) {
Mem::ww(HiresData::View_KeyLook_w,4);
int32_t d0=j_div(Hires::SMALL_HEIGHT,2);
Mem::ww(HiresData::View_LookMin_w,d0);
(d0=-(d0));
Mem::ww(HiresData::View_LookMax_w,d0);
(d0=Mem::w(HireswallData::STOPOFFSET));
(d0=M68k::muls(d0,2));
(d0=M68k::divs(d0,3));
Mem::ww(HireswallData::STOPOFFSET,d0);
}
else {
Mem::ww(HiresData::View_KeyLook_w,6);
int32_t d0=j_div(Hires::FS_HEIGHT,2);
Mem::ww(HiresData::View_LookMin_w,d0);
(d0=-(d0));
Mem::ww(HiresData::View_LookMax_w,d0);
(d0=Mem::w(HireswallData::STOPOFFSET));
int32_t d1=d0;
(d1=M68k::asrw(d1,1));
(d0=int16_t(j_add(d0,d1)));
Mem::ww(HireswallData::STOPOFFSET,d0);
}
Hires::startCopper();
}

void startCopper(){
if((Mem::w(VidBss::Vid_LetterBoxMarginHeight_w) >= 100)) {
Mem::ww(VidBss::Vid_LetterBoxMarginHeight_w,100);
}
int32_t d0{};
if((Mem::b(VidBss::Vid_FullScreen_b) != 0)) {
(d0=Hires::FS_WIDTH);
if((Mem::b(VidBss::Vid_DoubleWidth_b) != 0)) {
(d0=j_ushr((d0 & 0xFFFF),1));
}
Mem::ww(HiresData::Vid_RightX_w,d0);
(d0=j_ushr((d0 & 0xFFFF),1));
Mem::ww(HiresData::Vid_CentreX_w,d0);
Mem::ww(HireswallData::Vid_BottomY_w,Hires::FS_HEIGHT);
Mem::ww(HireswallData::TOTHEMIDDLE,j_div(Hires::FS_HEIGHT,2));
}
else {
(d0=Hires::SMALL_WIDTH);
if((Mem::b(VidBss::Vid_DoubleWidth_b) != 0)) {
(d0=j_ushr((d0 & 0xFFFF),1));
}
Mem::ww(HiresData::Vid_RightX_w,d0);
(d0=j_ushr((d0 & 0xFFFF),1));
Mem::ww(HiresData::Vid_CentreX_w,d0);
Mem::ww(HireswallData::Vid_BottomY_w,Hires::SMALL_HEIGHT);
Mem::ww(HireswallData::TOTHEMIDDLE,j_div(Hires::SMALL_HEIGHT,2));
}
DrawC::Draw_ResetGameDisplay();
}

void DrawDisplay(){
Mem::wb(HiresData::fillscrnwater,0);
int32_t a0=TablesData::SinCosTable_vw;
int32_t d0=Mem::w(HiresData::Vis_AngPos_w);
int32_t d6=Mem::w(j_add(a0,d0));
(a0=j_add(a0,int16_t(TablesData::COSINE_OFS)));
int32_t d7=Mem::w(j_add(a0,d0));
Mem::ww(HireswallData::Vis_SinVal_w,d6);
Mem::ww(HireswallData::Vis_CosVal_w,d7);
(d0=j_shr(Mem::l(HiresData::Plr_YOff_l),8));
int32_t d1=d0;
(d1=(j_add(d1,(256 - 32)) & 255));
Mem::ww(HireswallData::draw_WallYOffset_w,d1);
(d0=j_shr(Mem::l(HiresData::Plr_YOff_l),6));
Mem::ww(HiresData::flooryoff,d0);
(d6=Mem::w(HiresData::Plr_XOff_l));
int32_t d3=M68k::asrw(d6,1);
(d6=int16_t(j_add(d6,d3)));
(d6=M68k::asrw(d6,1));
Mem::ww(HiresData::xoff34,d6);
(d6=Mem::w(HiresData::Plr_ZOff_l));
(d3=M68k::asrw(d6,1));
(d6=int16_t(j_add(d6,d3)));
(d6=M68k::asrw(d6,1));
Mem::ww(HiresData::zoff34,d6);
Transform::RotateLevelPts();
Transform::RotateObjectPts();
Transform::CalcPLR1InLine();
if((Mem::b(PlayerBss::Plr_MultiplayerType_b) == Hires::PLR_SINGLE)) {
(a0=Mem::l(PlayerBss::Plr2_ObjectPtr_l));
Macros::FREE_ENT(a0);
}
else {
Transform::CalcPLR2InLine(0);
}
return ;
}

void nowaterfull(){
CustomChips::ciaBset(1);
}

void Plr1_Control(int32_t a2){
int32_t d2=Mem::l(PlayerBss::Plr1_XOff_l);
Mem::wl(ObjectmoveData::oldx,d2);
int32_t d3=Mem::l(PlayerBss::Plr1_ZOff_l);
Mem::wl(ObjectmoveData::oldz,d3);
int32_t d0=Mem::l(PlayerBss::Plr1_TmpXOff_l);
Mem::wl(PlayerBss::Plr1_XOff_l,d0);
Mem::wl(ObjectmoveData::newx,d0);
int32_t d1=Mem::l(PlayerBss::Plr1_TmpZOff_l);
Mem::wl(ObjectmoveData::newz,d1);
Mem::wl(PlayerBss::Plr1_ZOff_l,d1);
Mem::wl(PlayerBss::Plr1_Height_l,Mem::l(PlayerBss::plr1_TmpHeight_l));
(d0=(d0 - d2));
(d1=(d1 - d3));
Mem::wl(ObjectmoveData::xdiff,d0);
Mem::wl(ObjectmoveData::zdiff,d1);
(d0=Mem::w(PlayerBss::Plr1_TmpAngPos_w));
Mem::ww(PlayerBss::Plr1_AngPos_w,d0);
int32_t a1=TablesData::SinCosTable_vw;
Mem::ww(PlayerBss::Plr1_SinVal_w,Mem::w(j_add(a1,d0)));
(d0=M68k::setw(d0,j_add(d0,TablesData::COSINE_OFS)));
(d0=TablesData::AMOD_A(d0));
Mem::ww(PlayerBss::Plr1_CosVal_w,Mem::w(j_add(a1,(d0 & 0xFFFF))));
(d0=Mem::l(PlayerBss::Plr1_TmpYOff_l));
(d1=Mem::w(PlayerBss::plr1_TmpBobble_w));
(d1=Mem::w(j_add(a1,d1)));
(d3=d1);
if(!((int16_t(d1) <= 0))) {
(d1=M68k::setw(d1,-(int16_t(d1))));
}
(d1=M68k::setw(d1,j_add(int16_t(d1),16384)));
(d1=M68k::asrw(d1,4));
if(((Mem::b(PlayerBss::Plr1_Ducked_b) == 0) && (Mem::b(PlayerBss::Plr1_Squished_b) == 0))) {
(d1=M68k::setw(d1,j_add(int16_t(d1),int16_t(d1))));
}
(d1=int16_t(d1));
Mem::wl(PlayerBss::plr1_BobbleY_l,d1);
int32_t d4=Mem::l(PlayerBss::Plr1_Height_l);
(d4=(d4 - d1));
(d0=j_add(d0,d1));
if((Mem::b(PlayerBss::Plr_MultiplayerType_b) != Hires::PLR_SLAVE)) {
(d3=M68k::asrw(d3,6));
(d3=int16_t(d3));
Mem::wl(HiresData::xwobble,d3);
(d1=M68k::muls(Mem::w(PlayerBss::Plr1_SinVal_w),d3));
(d2=M68k::muls(Mem::w(PlayerBss::Plr1_CosVal_w),d3));
(d1=M68k::swap(d1));
(d2=M68k::swap(d2));
(d1=M68k::asrw(d1,6));
Mem::ww(HiresData::xwobxoff,d1);
(d2=M68k::asrw(d2,6));
(d2=M68k::setw(d2,-(int16_t(d2))));
Mem::ww(HiresData::xwobzoff,d2);
}
Mem::wl(PlayerBss::Plr1_YOff_l,d0);
Mem::wl(ObjectmoveData::newy,d0);
Mem::wl(ObjectmoveData::oldy,d0);
Mem::wl(ObjectmoveData::thingheight,d4);
Mem::wl(ObjectmoveData::StepUpVal,(40 * 256));
if(((Mem::b(PlayerBss::Plr1_Squished_b) != 0) || (Mem::b(PlayerBss::Plr1_Ducked_b) != 0))) {
Mem::wl(ObjectmoveData::StepUpVal,(10 * 256));
}
Mem::wl(ObjectmoveData::StepDownVal,0x1000000);
int32_t a0=Mem::l(PlayerBss::Plr1_ZonePtr_l);
(d0=Mem::w(j_add(a0,Defs::ZoneT_TelZone_w)));
bool cantmove=false;
if((d0 >= 0)) {
Mem::ww(ObjectmoveData::newx,Mem::w(j_add(a0,Defs::ZoneT_TelX_w)));
Mem::ww(ObjectmoveData::newz,Mem::w(j_add(a0,Defs::ZoneT_TelZ_w)));
(a0=Mem::l(PlayerBss::Plr1_ObjectPtr_l));
Mem::ww(HiresData::CollId,Mem::w(a0));
Mem::wl(ObjectmoveData::Obj_CollideFlags_l,0b111111111111111111);
Objectmove::Obj_DoCollision(a2);
if((Mem::b(ObjectmoveData::hitwall) != 0)) {
Mem::ww(ObjectmoveData::newx,Mem::w(PlayerBss::Plr1_XOff_l));
Mem::ww(ObjectmoveData::newz,Mem::w(PlayerBss::Plr1_ZOff_l));
}
else {
Mem::wb(PlayerBss::plr1_Teleported_b,0xFF);
(a0=Mem::l(PlayerBss::Plr1_ZonePtr_l));
(d0=Mem::w(j_add(a0,Defs::ZoneT_TelZone_w)));
Mem::ww(PlayerBss::Plr1_XOff_l,Mem::w(j_add(a0,Defs::ZoneT_TelX_w)));
Mem::ww(PlayerBss::Plr1_ZOff_l,Mem::w(j_add(a0,Defs::ZoneT_TelZ_w)));
(d1=Mem::l(PlayerBss::Plr1_YOff_l));
(d1=(d1 - Mem::l(j_add(a0,Defs::ZoneT_Floor_l))));
(a0=Mem::l(LevelBss::Lvl_ZonePtrsPtr_l));
(a0=Mem::l(j_add(a0,(int16_t(d0) * 4))));
Mem::wl(PlayerBss::Plr1_ZonePtr_l,a0);
(d1=j_add(d1,Mem::l(j_add(a0,Defs::ZoneT_Floor_l))));
Mem::wl(PlayerBss::Plr1_SnapYOff_l,d1);
Mem::wl(PlayerBss::Plr1_YOff_l,d1);
Mem::wl(PlayerBss::Plr1_SnapTYOff_l,d1);
Mem::wl(PlayerBss::Plr1_SnapXOff_l,Mem::l(PlayerBss::Plr1_XOff_l));
Mem::wl(PlayerBss::Plr1_SnapZOff_l,Mem::l(PlayerBss::Plr1_ZOff_l));
Mem::ww(HiresData::Aud_NoiseX_w,0);
Mem::ww(HiresData::Aud_NoiseZ_w,0);
Mem::ww(HiresData::Aud_SampleNum_w,26);
Mem::ww(HiresData::Aud_NoiseVol_w,100);
Mem::ww(HiresData::IDNUM,0xfff9);
Hires::MakeSomeNoise();
(cantmove=true);
}
}
if(!(cantmove)) {
Mem::wl(ObjectmoveData::Obj_ZonePtr_l,Mem::l(PlayerBss::Plr1_ZonePtr_l));
Mem::ww(ObjectmoveData::wallflags,0b100000000);
Mem::wb(ObjectmoveData::StoodInTop,Mem::b(PlayerBss::Plr1_StoodInTop_b));
Mem::wl(ObjectmoveData::Obj_CollideFlags_l,0b1011111110111000011);
(a0=Mem::l(PlayerBss::Plr1_ObjectPtr_l));
Mem::ww(HiresData::CollId,Mem::w(a0));
Objectmove::Obj_DoCollision(a2);
if((Mem::b(ObjectmoveData::hitwall) != 0)) {
Mem::ww(PlayerBss::Plr1_XOff_l,Mem::w(ObjectmoveData::oldx));
Mem::ww(PlayerBss::Plr1_ZOff_l,Mem::w(ObjectmoveData::oldz));
Mem::wl(PlayerBss::Plr1_SnapXOff_l,Mem::l(PlayerBss::Plr1_XOff_l));
Mem::wl(PlayerBss::Plr1_SnapZOff_l,Mem::l(PlayerBss::Plr1_ZOff_l));
}
else {
Mem::ww(ObjectmoveData::Obj_ExtLen_w,40);
Mem::wb(ObjectmoveData::Obj_AwayFromWall_b,0);
Mem::wb(ObjectmoveData::exitfirst,0);
Mem::wb(ObjectmoveData::Obj_WallBounce_b,0);
Objectmove::MoveObject();
Mem::wb(PlayerBss::Plr1_StoodInTop_b,Mem::b(ObjectmoveData::StoodInTop));
Mem::wl(PlayerBss::Plr1_ZonePtr_l,Mem::l(ObjectmoveData::Obj_ZonePtr_l));
Mem::ww(PlayerBss::Plr1_XOff_l,Mem::w(ObjectmoveData::newx));
Mem::ww(PlayerBss::Plr1_ZOff_l,Mem::w(ObjectmoveData::newz));
Mem::wl(PlayerBss::Plr1_SnapXOff_l,Mem::l(PlayerBss::Plr1_XOff_l));
Mem::wl(PlayerBss::Plr1_SnapZOff_l,Mem::l(PlayerBss::Plr1_ZOff_l));
}
}
(a0=Mem::l(PlayerBss::Plr1_ZonePtr_l));
(d0=Mem::l(j_add(a0,Defs::ZoneT_Floor_l)));
if((Mem::b(PlayerBss::Plr1_StoodInTop_b) != 0)) {
(d0=Mem::l(j_add(a0,Defs::ZoneT_UpperFloor_l)));
}
(a0=j_add(a0,Defs::ZoneT_Points_w));
(d0=(d0 - Mem::l(PlayerBss::Plr1_Height_l)));
Mem::wl(PlayerBss::Plr1_SnapTYOff_l,d0);
Mem::ww(NewanimsData::tmpangpos,Mem::w(PlayerBss::Plr1_TmpAngPos_w));
(d1=Mem::w(a0));
(a0+=2);
(d1=int16_t(d1));
(d1=j_add(d1,Mem::l(PlayerBss::Plr1_ZonePtr_l)));
Mem::wl(PlayerBss::plr1_PointsToRotatePtr_l,d1);
int32_t back=Mem::b(a0);
(a0+=1);
if(((back != 0) && (Mem::b(PlayerBss::Plr_MultiplayerType_b) != Hires::PLR_SLAVE))) {
(a0=Newanims::Draw_SkyBackdrop(a0));
}
Mem::wb(PlayerBss::Plr1_Echo_b,Mem::b(a0));
(a0+=1);
(a0=j_add(a0,10));
Mem::wl(PlayerBss::Plr1_PotVisibleZoneListPtr_l,a0);
}

void Plr2_Control(int32_t a2){
int32_t d2=Mem::l(PlayerBss::Plr2_XOff_l);
Mem::wl(ObjectmoveData::oldx,d2);
int32_t d3=Mem::l(PlayerBss::Plr2_ZOff_l);
Mem::wl(ObjectmoveData::oldz,d3);
int32_t d0=Mem::l(PlayerBss::Plr2_TmpXOff_l);
Mem::wl(PlayerBss::Plr2_XOff_l,d0);
Mem::wl(ObjectmoveData::newx,d0);
int32_t d1=Mem::l(PlayerBss::Plr2_TmpZOff_l);
Mem::wl(ObjectmoveData::newz,d1);
Mem::wl(PlayerBss::Plr2_ZOff_l,d1);
Mem::wl(PlayerBss::Plr2_Height_l,Mem::l(PlayerBss::plr2_TmpHeight_l));
(d0=(d0 - d2));
(d1=(d1 - d3));
Mem::wl(ObjectmoveData::xdiff,d0);
Mem::wl(ObjectmoveData::zdiff,d1);
(d0=Mem::w(PlayerBss::Plr2_TmpAngPos_w));
Mem::ww(PlayerBss::Plr2_AngPos_w,d0);
int32_t a1=TablesData::SinCosTable_vw;
Mem::ww(PlayerBss::Plr2_SinVal_w,Mem::w(j_add(a1,d0)));
(d0=M68k::setw(d0,j_add(d0,TablesData::COSINE_OFS)));
(d0=TablesData::AMOD_A(d0));
Mem::ww(PlayerBss::Plr2_CosVal_w,Mem::w(j_add(a1,(d0 & 0xFFFF))));
(d0=Mem::l(PlayerBss::Plr2_TmpYOff_l));
(d1=Mem::w(PlayerBss::plr2_TmpBobble_w));
(d1=Mem::w(j_add(a1,d1)));
(d3=d1);
if(!((int16_t(d1) <= 0))) {
(d1=M68k::setw(d1,-(int16_t(d1))));
}
(d1=M68k::setw(d1,j_add(int16_t(d1),16384)));
(d1=M68k::asrw(d1,4));
if(((Mem::b(PlayerBss::Plr2_Ducked_b) == 0) && (Mem::b(PlayerBss::Plr2_Squished_b) == 0))) {
(d1=M68k::setw(d1,j_add(int16_t(d1),int16_t(d1))));
}
(d1=int16_t(d1));
Mem::wl(PlayerBss::plr2_BobbleY_l,d1);
int32_t d4=Mem::l(PlayerBss::Plr2_Height_l);
(d4=(d4 - d1));
(d0=j_add(d0,d1));
if((Mem::b(PlayerBss::Plr_MultiplayerType_b) == Hires::PLR_SLAVE)) {
(d3=M68k::asrw(d3,6));
(d3=int16_t(d3));
Mem::wl(HiresData::xwobble,d3);
(d1=M68k::muls(Mem::w(PlayerBss::Plr2_SinVal_w),d3));
(d2=M68k::muls(Mem::w(PlayerBss::Plr2_CosVal_w),d3));
(d1=M68k::swap(d1));
(d2=M68k::swap(d2));
(d1=M68k::asrw(d1,6));
Mem::ww(HiresData::xwobxoff,d1);
(d2=M68k::asrw(d2,6));
(d2=M68k::setw(d2,-(int16_t(d2))));
Mem::ww(HiresData::xwobzoff,d2);
}
Mem::wl(PlayerBss::Plr2_YOff_l,d0);
Mem::wl(ObjectmoveData::newy,d0);
Mem::wl(ObjectmoveData::oldy,d0);
Mem::wl(ObjectmoveData::thingheight,d4);
Mem::wl(ObjectmoveData::StepUpVal,(40 * 256));
if(((Mem::b(PlayerBss::Plr2_Squished_b) != 0) || (Mem::b(PlayerBss::Plr2_Ducked_b) != 0))) {
Mem::wl(ObjectmoveData::StepUpVal,(10 * 256));
}
Mem::wl(ObjectmoveData::StepDownVal,0x1000000);
int32_t a0=Mem::l(PlayerBss::Plr2_ZonePtr_l);
(d0=Mem::w(j_add(a0,Defs::ZoneT_TelZone_w)));
bool cantmove=false;
if((d0 >= 0)) {
Mem::ww(ObjectmoveData::newx,Mem::w(j_add(a0,Defs::ZoneT_TelX_w)));
Mem::ww(ObjectmoveData::newz,Mem::w(j_add(a0,Defs::ZoneT_TelZ_w)));
(a0=Mem::l(PlayerBss::Plr2_ObjectPtr_l));
Mem::ww(HiresData::CollId,Mem::w(a0));
Mem::wl(ObjectmoveData::Obj_CollideFlags_l,0b111111111111111111);
Objectmove::Obj_DoCollision(a2);
if((Mem::b(ObjectmoveData::hitwall) != 0)) {
Mem::ww(ObjectmoveData::newx,Mem::w(PlayerBss::Plr2_XOff_l));
Mem::ww(ObjectmoveData::newz,Mem::w(PlayerBss::Plr2_ZOff_l));
}
else {
Mem::wb(PlayerBss::plr2_Teleported_b,0xFF);
(a0=Mem::l(PlayerBss::Plr2_ZonePtr_l));
(d0=Mem::w(j_add(a0,Defs::ZoneT_TelZone_w)));
Mem::ww(PlayerBss::Plr2_XOff_l,Mem::w(j_add(a0,Defs::ZoneT_TelX_w)));
Mem::ww(PlayerBss::Plr2_ZOff_l,Mem::w(j_add(a0,Defs::ZoneT_TelZ_w)));
(d1=Mem::l(PlayerBss::Plr2_YOff_l));
(d1=(d1 - Mem::l(j_add(a0,Defs::ZoneT_Floor_l))));
(a0=Mem::l(LevelBss::Lvl_ZonePtrsPtr_l));
(a0=Mem::l(j_add(a0,(int16_t(d0) * 4))));
Mem::wl(PlayerBss::Plr2_ZonePtr_l,a0);
(d1=j_add(d1,Mem::l(j_add(a0,Defs::ZoneT_Floor_l))));
Mem::wl(PlayerBss::Plr2_SnapYOff_l,d1);
Mem::wl(PlayerBss::Plr2_YOff_l,d1);
Mem::wl(PlayerBss::Plr2_SnapTYOff_l,d1);
Mem::wl(PlayerBss::Plr2_SnapXOff_l,Mem::l(PlayerBss::Plr2_XOff_l));
Mem::wl(PlayerBss::Plr2_SnapZOff_l,Mem::l(PlayerBss::Plr2_ZOff_l));
Mem::ww(HiresData::Aud_NoiseX_w,0);
Mem::ww(HiresData::Aud_NoiseZ_w,0);
Mem::ww(HiresData::Aud_SampleNum_w,26);
Mem::ww(HiresData::Aud_NoiseVol_w,100);
Mem::ww(HiresData::IDNUM,0xfff9);
Hires::MakeSomeNoise();
(cantmove=true);
}
}
if(!(cantmove)) {
Mem::wl(ObjectmoveData::Obj_ZonePtr_l,Mem::l(PlayerBss::Plr2_ZonePtr_l));
Mem::ww(ObjectmoveData::wallflags,0b100000000000);
Mem::wb(ObjectmoveData::StoodInTop,Mem::b(PlayerBss::Plr2_StoodInTop_b));
Mem::wl(ObjectmoveData::Obj_CollideFlags_l,0b1011111010111100011);
(a0=Mem::l(PlayerBss::Plr2_ObjectPtr_l));
Mem::ww(HiresData::CollId,Mem::w(a0));
Objectmove::Obj_DoCollision(a2);
if((Mem::b(ObjectmoveData::hitwall) != 0)) {
Mem::ww(PlayerBss::Plr2_XOff_l,Mem::w(ObjectmoveData::oldx));
Mem::ww(PlayerBss::Plr2_ZOff_l,Mem::w(ObjectmoveData::oldz));
Mem::wl(PlayerBss::Plr2_SnapXOff_l,Mem::l(PlayerBss::Plr2_XOff_l));
Mem::wl(PlayerBss::Plr2_SnapZOff_l,Mem::l(PlayerBss::Plr2_ZOff_l));
}
else {
Mem::ww(ObjectmoveData::Obj_ExtLen_w,40);
Mem::wb(ObjectmoveData::Obj_AwayFromWall_b,0);
Mem::wb(ObjectmoveData::exitfirst,0);
Mem::wb(ObjectmoveData::Obj_WallBounce_b,0);
Objectmove::MoveObject();
Mem::wb(PlayerBss::Plr2_StoodInTop_b,Mem::b(ObjectmoveData::StoodInTop));
Mem::wl(PlayerBss::Plr2_ZonePtr_l,Mem::l(ObjectmoveData::Obj_ZonePtr_l));
Mem::ww(PlayerBss::Plr2_XOff_l,Mem::w(ObjectmoveData::newx));
Mem::ww(PlayerBss::Plr2_ZOff_l,Mem::w(ObjectmoveData::newz));
Mem::wl(PlayerBss::Plr2_SnapXOff_l,Mem::l(PlayerBss::Plr2_XOff_l));
Mem::wl(PlayerBss::Plr2_SnapZOff_l,Mem::l(PlayerBss::Plr2_ZOff_l));
}
}
(a0=Mem::l(PlayerBss::Plr2_ZonePtr_l));
(d0=Mem::l(j_add(a0,Defs::ZoneT_Floor_l)));
if((Mem::b(PlayerBss::Plr2_StoodInTop_b) != 0)) {
(d0=Mem::l(j_add(a0,Defs::ZoneT_UpperFloor_l)));
}
(a0=j_add(a0,Defs::ZoneT_Points_w));
(d0=(d0 - Mem::l(PlayerBss::Plr2_Height_l)));
Mem::wl(PlayerBss::Plr2_SnapTYOff_l,d0);
Mem::ww(NewanimsData::tmpangpos,Mem::w(PlayerBss::Plr2_TmpAngPos_w));
(d1=Mem::w(a0));
(a0+=2);
(d1=int16_t(d1));
(d1=j_add(d1,Mem::l(PlayerBss::Plr2_ZonePtr_l)));
Mem::wl(PlayerBss::plr2_PointsToRotatePtr_l,d1);
int32_t back=Mem::b(a0);
(a0+=1);
if(((back != 0) && (Mem::b(PlayerBss::Plr_MultiplayerType_b) == Hires::PLR_SLAVE))) {
(a0=Newanims::Draw_SkyBackdrop(a0));
}
Mem::wb(PlayerBss::Plr2_Echo_b,Mem::b(a0));
(a0+=1);
(a0=j_add(a0,10));
Mem::wl(PlayerBss::Plr2_PotVisibleZoneListPtr_l,a0);
}

void Plr1_Use(){
int32_t a0=Mem::l(PlayerBss::Plr1_ObjectPtr_l);
Mem::wb(j_add(a0,Defs::ObjT_TypeID_b),Defs::OBJ_TYPE_PLAYER1);
int32_t a1=Mem::l(LevelBss::Lvl_ObjectPointsPtr_l);
if((TablesBss::ObjRotated_vl == 0)) {
}
int32_t d0=Mem::w(a0);
Mem::wl(j_add(a1,(int16_t(d0) * 8)),Mem::l(PlayerBss::Plr1_XOff_l));
Mem::wl(j_add(j_add(a1,(int16_t(d0) * 8)),4),Mem::l(PlayerBss::Plr1_ZOff_l));
(a1=Mem::l(PlayerBss::Plr1_ZonePtr_l));
int32_t d2=Mem::ub(j_add(a0,Defs::EntT_DamageTaken_b));
if((d2 != 0)) {
int32_t d4=0;
int32_t d3=Mem::w(j_add(a0,Defs::EntT_ImpactX_w));
if((d3 != 0)) (d4=d2);
Mem::ww(PlayerBss::Plr1_SnapXSpdVal_l,j_add(Mem::w(PlayerBss::Plr1_SnapXSpdVal_l),d3));
(d3=Mem::w(j_add(a0,Defs::EntT_ImpactZ_w)));
if((d3 != 0)) (d4=d2);
Mem::ww(PlayerBss::Plr1_SnapZSpdVal_l,j_add(Mem::w(PlayerBss::Plr1_SnapZSpdVal_l),d3));
(d3=Mem::w(j_add(a0,Defs::EntT_ImpactY_w)));
(d3=int16_t(d3));
(d3=j_shl(d3,8));
Mem::wl(PlayerBss::Plr1_SnapYVel_l,j_add(Mem::l(PlayerBss::Plr1_SnapYVel_l),d3));
Mem::ww(j_add(a0,Defs::EntT_ImpactX_w),0);
Mem::ww(j_add(a0,Defs::EntT_ImpactY_w),0);
Mem::ww(j_add(a0,Defs::EntT_ImpactZ_w),0);
(d0=Objectmove::GetRand());
(d0=M68k::muls(d0,d4));
(d0=j_shr(d0,8));
(d0=j_shr(d0,4));
Mem::ww(PlayerBss::Plr1_SnapAngSpd_w,j_add(Mem::w(PlayerBss::Plr1_SnapAngSpd_w),d0));
Mem::wl(HiresData::hitcol,(7 * 2116));
Mem::ww(PlayerBss::Plr1_Health_w,(Mem::w(PlayerBss::Plr1_Health_w) - d2));
Mem::ww(HiresData::IDNUM,0xfffa);
Mem::ww(HiresData::Aud_SampleNum_w,19);
Mem::wb(HiresData::notifplaying,0);
Mem::ww(HiresData::Aud_NoiseX_w,0);
Mem::ww(HiresData::Aud_NoiseZ_w,0);
Mem::ww(HiresData::Aud_NoiseVol_w,60);
Hires::MakeSomeNoise();
}
Mem::wb(j_add(a0,Defs::EntT_DamageTaken_b),0);
Mem::wb(j_add(a0,Defs::EntT_HitPoints_b),10);
Mem::ww(j_add(a0,Defs::EntT_CurrentAngle_w),Mem::w(PlayerBss::Plr1_TmpAngPos_w));
Mem::wb(j_add(a0,Defs::ShotT_InUpperZone_b),Mem::b(PlayerBss::Plr1_StoodInTop_b));
Mem::ww(j_add(a0,Defs::ObjT_ZoneID_w),Mem::w(a1));
(d2=Mem::w(a1));
(a1=ZoneBss::Zone_BrightTable_vl);
(d2=Mem::l(j_add(a1,(int16_t(d2) * 4))));
if((Mem::b(PlayerBss::Plr1_StoodInTop_b) == 0)) {
(d2=M68k::swap(d2));
}
Mem::ww(j_add(a0,2),d2);
(d0=Mem::l(PlayerBss::Plr1_TmpYOff_l));
int32_t d1=Mem::l(PlayerBss::plr1_TmpHeight_l);
(d1=j_shr(d1,1));
(d0=j_add(d0,d1));
(d0=j_shr(d0,7));
Mem::ww(j_add(a0,4),d0);
if(!((int16_t(Mem::w(PlayerBss::Plr1_Health_w)) > 0))) {
Macros::FREE_OBJ(a0);
}
(a0=Mem::l(PlayerBss::Plr2_ObjectPtr_l));
Mem::wb(j_add(a0,Defs::ObjT_TypeID_b),Defs::OBJ_TYPE_PLAYER2);
(d0=Mem::w(PlayerBss::Plr2_TmpAngPos_w));
(d0=TablesData::AMOD_A(d0));
Mem::ww(j_add(a0,Defs::EntT_CurrentAngle_w),d0);
(a1=Mem::l(LevelBss::Lvl_ObjectPointsPtr_l));
(d0=Mem::w(a0));
Mem::wl(j_add(a1,(int16_t(d0) * 8)),Mem::l(PlayerBss::Plr2_XOff_l));
Mem::wl(j_add(j_add(a1,(int16_t(d0) * 8)),4),Mem::l(PlayerBss::Plr2_ZOff_l));
(a1=Mem::l(PlayerBss::Plr2_ZonePtr_l));
(d2=Mem::ub(j_add(a0,Defs::EntT_DamageTaken_b)));
if((d2 != 0)) {
int32_t d3=Mem::w(j_add(a0,Defs::EntT_ImpactX_w));
Mem::ww(PlayerBss::Plr2_SnapXSpdVal_l,j_add(Mem::w(PlayerBss::Plr2_SnapXSpdVal_l),d3));
(d3=Mem::w(j_add(a0,Defs::EntT_ImpactZ_w)));
Mem::ww(PlayerBss::Plr2_SnapZSpdVal_l,j_add(Mem::w(PlayerBss::Plr2_SnapZSpdVal_l),d3));
(d3=Mem::w(j_add(a0,Defs::EntT_ImpactY_w)));
(d3=int16_t(d3));
(d3=j_shl(d3,8));
Mem::wl(PlayerBss::Plr2_SnapYVel_l,j_add(Mem::l(PlayerBss::Plr2_SnapYVel_l),d3));
Mem::ww(j_add(a0,Defs::EntT_ImpactX_w),0);
Mem::ww(j_add(a0,Defs::EntT_ImpactY_w),0);
Mem::ww(j_add(a0,Defs::EntT_ImpactZ_w),0);
Mem::ww(PlayerBss::Plr2_Health_w,(Mem::w(PlayerBss::Plr2_Health_w) - d2));
}
Mem::wb(j_add(a0,Defs::EntT_DamageTaken_b),0);
Mem::wb(j_add(a0,Defs::EntT_HitPoints_b),10);
Mem::wb(j_add(a0,Defs::ShotT_InUpperZone_b),Mem::b(PlayerBss::Plr2_StoodInTop_b));
Mem::ww(j_add(a0,Defs::ObjT_ZoneID_w),Mem::w(a1));
(d2=Mem::w(a1));
(a1=ZoneBss::Zone_BrightTable_vl);
(d2=Mem::l(j_add(a1,(int16_t(d2) * 4))));
if((Mem::b(PlayerBss::Plr2_StoodInTop_b) == 0)) {
(d2=M68k::swap(d2));
}
Mem::ww(j_add(a0,2),d2);
(d0=Mem::l(PlayerBss::Plr2_TmpYOff_l));
(d1=Mem::l(PlayerBss::plr2_TmpHeight_l));
(d1=j_shr(d1,1));
(d0=j_add(d0,d1));
(d0=j_shr(d0,7));
Mem::ww(j_add(a0,4),d0);
(d0=Newaliencontrol::ViewpointToDraw(a0));
(d0=j_add(d0,d0));
Hires::plr_Use_AnimSetup(a0,d0,Defs::GLFT_Player2Graphic_w);
if(!((int16_t(Mem::w(PlayerBss::Plr2_Health_w)) > 0))) {
Macros::FREE_OBJ(a0);
}
(a0=Mem::l(PlayerBss::Plr1_ObjectPtr_l));
if(!((int16_t(Mem::w(PlayerBss::Plr1_Health_w)) > 0))) {
Macros::FREE_OBJ_2(a0,Defs::ENT_NEXT_2);
return ;
}
(a1=Mem::l(PlayerBss::Plr1_ZonePtr_l));
(d0=Mem::w(j_add(a0,Defs::EntT_CurrentAngle_w)));
(d0=M68k::setw(d0,j_add(d0,TablesData::SINE_SIZE)));
(d0=TablesData::AMOD_A(d0));
Mem::ww(j_add(j_add(a0,Defs::EntT_CurrentAngle_w),Defs::ENT_NEXT_2),d0);
Mem::ww(j_add(j_add(a0,Defs::ObjT_ZoneID_w),Defs::ENT_NEXT_2),Mem::w(a1));
Mem::ww(j_add(j_add(a0,Defs::EntT_ZoneID_w),Defs::ENT_NEXT_2),Mem::w(a1));
(d0=Mem::ub(PlayerBss::Plr1_TmpGunSelected_b));
(a1=j_add(Mem::l(HiresData::GLF_DatabasePtr_l),Defs::GLFT_GunObjects_l));
(d0=Mem::w(j_add(a1,(int16_t(d0) * 2))));
Mem::wb(j_add(j_add(a0,Defs::EntT_Type_b),Defs::ENT_NEXT_2),d0);
Mem::wb(j_add(j_add(a0,Defs::ObjT_TypeID_b),Defs::ENT_NEXT_2),Defs::OBJ_TYPE_OBJECT);
(d0=Mem::w(a0));
(d1=Mem::w(j_add(a0,Defs::ENT_NEXT_2)));
(a1=Mem::l(LevelBss::Lvl_ObjectPointsPtr_l));
Mem::wl(j_add(a1,(int16_t(d1) * 8)),Mem::l(j_add(a1,(int16_t(d0) * 8))));
Mem::wl(j_add(j_add(a1,(int16_t(d1) * 8)),4),Mem::l(j_add(j_add(a1,(int16_t(d0) * 8)),4)));
Mem::wb(j_add(j_add(a0,Defs::EntT_WhichAnim_b),Defs::ENT_NEXT_2),0xFF);
(d0=Mem::l(PlayerBss::Plr1_TmpYOff_l));
(d1=Mem::l(PlayerBss::plr1_TmpHeight_l));
(d1=j_shr(d1,2));
(d1=j_add(d1,(10 * 128)));
(d0=j_add(d0,d1));
(d0=j_shr(d0,7));
Mem::ww(j_add(j_add(a0,4),Defs::ENT_NEXT_2),d0);
(d1=Mem::l(PlayerBss::plr1_BobbleY_l));
(d1=j_shr(d1,8));
(d0=d1);
(d0=j_shr(d0,1));
(d1=j_add(d1,d0));
Mem::ww(j_add(j_add(a0,4),Defs::ENT_NEXT_2),j_add(Mem::w(j_add(j_add(a0,4),Defs::ENT_NEXT_2)),d1));
Mem::wb(j_add(j_add(a0,Defs::ShotT_InUpperZone_b),Defs::ENT_NEXT_2),Mem::b(j_add(a0,Defs::ShotT_InUpperZone_b)));
}

void plr_Use_AnimSetup(int32_t a0,int32_t d0,int32_t graphicOfs){
int32_t a6=j_add(Mem::l(HiresData::GLF_DatabasePtr_l),graphicOfs);
int32_t d7=Mem::w(a6);
int32_t d1=d7;
(a6=j_add(Mem::l(HiresData::GLF_DatabasePtr_l),Defs::GLFT_AlienDefs_l));
(d1=M68k::muls(d1,Defs::AlienT_SizeOf_l));
(a6=j_add(a6,d1));
Mem::wb(AiBss::AI_VecObj_w,Mem::b(j_add(j_add(a6,Defs::AlienT_GFXType_w),1)));
if((Mem::w(j_add(a6,Defs::AlienT_GFXType_w)) == 1)) {
(d0=0);
}
(a6=j_add(Mem::l(HiresData::GLF_DatabasePtr_l),Defs::GLFT_AlienAnims_l));
(d1=d7);
(d1=M68k::muls(d1,Defs::A_AnimLen));
(a6=j_add(a6,d1));
(d0=M68k::muls(d0,Defs::A_OptLen));
(a6=j_add(a6,int16_t(d0)));
(d1=Mem::w(j_add(a0,Defs::EntT_Timer2_w)));
int32_t d2=d1;
(d1=M68k::muls(d1,Defs::A_FrameLen));
(d2=M68k::setw(d2,j_add(d2,1)));
int32_t d3=d2;
(d3=M68k::muls(d3,Defs::A_FrameLen));
if((int8_t(Mem::b(j_add(a6,int16_t(d3)))) < 0)) {
(d2=M68k::setw(d2,0));
}
Mem::ww(j_add(a0,Defs::EntT_Timer2_w),d2);
(d1=d2);
(d1=M68k::muls(d1,Defs::A_FrameLen));
Mem::wl(j_add(a0,8),0);
Mem::wb(j_add(a0,9),Mem::b(j_add(a6,int16_t(d1))));
(d0=Mem::b(j_add(j_add(a6,int16_t(d1)),1)));
(d0=int16_t(d0));
if(!((int16_t(d0) > 0))) {
Mem::wb(j_add(a0,10),128);
(d0=M68k::setw(d0,-(int16_t(d0))));
}
(d0=M68k::setw(d0,(int16_t(d0) - 1)));
Mem::wb(j_add(a0,11),d0);
Mem::ww(j_add(a0,6),-(1));
int32_t vec=Mem::b(AiBss::AI_VecObj_w);
if((vec == 1)) {
}
else if((vec > 1)) {
Mem::ww(j_add(a0,6),Mem::w(j_add(j_add(a6,int16_t(d1)),2)));
int32_t dl=Mem::b(AiBss::AI_VecObj_w);
Mem::wb(j_add(a0,10),(Mem::b(j_add(a0,10)) | dl));
}
else {
Mem::ww(j_add(a0,6),Mem::w(j_add(j_add(a6,int16_t(d1)),2)));
}
}

void Plr2_Use(){
int32_t a0=Mem::l(PlayerBss::Plr2_ObjectPtr_l);
Mem::wb(j_add(a0,Defs::ObjT_TypeID_b),Defs::OBJ_TYPE_PLAYER2);
int32_t a1=Mem::l(LevelBss::Lvl_ObjectPointsPtr_l);
int32_t d0=Mem::w(a0);
Mem::wl(j_add(a1,(int16_t(d0) * 8)),Mem::l(PlayerBss::Plr2_XOff_l));
Mem::wl(j_add(j_add(a1,(int16_t(d0) * 8)),4),Mem::l(PlayerBss::Plr2_ZOff_l));
(a1=Mem::l(PlayerBss::Plr2_ZonePtr_l));
int32_t d2=Mem::ub(j_add(a0,Defs::EntT_DamageTaken_b));
if((d2 != 0)) {
int32_t d4=0;
int32_t d3=Mem::w(j_add(a0,Defs::EntT_ImpactX_w));
if((d3 != 0)) (d4=d2);
Mem::ww(PlayerBss::Plr2_SnapXSpdVal_l,j_add(Mem::w(PlayerBss::Plr2_SnapXSpdVal_l),d3));
(d3=Mem::w(j_add(a0,Defs::EntT_ImpactZ_w)));
if((d3 != 0)) (d4=d2);
Mem::ww(PlayerBss::Plr2_SnapZSpdVal_l,j_add(Mem::w(PlayerBss::Plr2_SnapZSpdVal_l),d3));
(d0=Objectmove::GetRand());
(d0=M68k::muls(d0,d4));
(d0=j_shr(d0,8));
(d0=j_shr(d0,4));
Mem::ww(PlayerBss::Plr2_SnapAngSpd_w,j_add(Mem::w(PlayerBss::Plr2_SnapAngSpd_w),d0));
Mem::wl(HiresData::hitcol,(7 * 2116));
Mem::ww(PlayerBss::Plr2_Health_w,(Mem::w(PlayerBss::Plr2_Health_w) - d2));
Mem::ww(HiresData::Aud_SampleNum_w,19);
Mem::wb(HiresData::notifplaying,0);
Mem::ww(HiresData::IDNUM,0xfffa);
Mem::ww(HiresData::Aud_NoiseX_w,0);
Mem::ww(HiresData::Aud_NoiseZ_w,0);
Mem::ww(HiresData::Aud_NoiseVol_w,60);
Hires::MakeSomeNoise();
}
Mem::wb(j_add(a0,Defs::EntT_DamageTaken_b),0);
Mem::wb(j_add(a0,Defs::EntT_HitPoints_b),10);
Mem::ww(j_add(a0,Defs::EntT_CurrentAngle_w),Mem::w(PlayerBss::Plr2_TmpAngPos_w));
Mem::wb(j_add(a0,Defs::ShotT_InUpperZone_b),Mem::b(PlayerBss::Plr2_StoodInTop_b));
Mem::ww(j_add(a0,Defs::ObjT_ZoneID_w),Mem::w(a1));
(d2=Mem::w(a1));
(a1=ZoneBss::Zone_BrightTable_vl);
(d2=Mem::l(j_add(a1,(int16_t(d2) * 4))));
if((Mem::b(PlayerBss::Plr2_StoodInTop_b) == 0)) {
(d2=M68k::swap(d2));
}
Mem::ww(j_add(a0,2),d2);
(d0=Mem::l(PlayerBss::Plr2_YOff_l));
int32_t d1=Mem::l(PlayerBss::plr2_TmpHeight_l);
(d1=j_shr(d1,1));
(d0=j_add(d0,d1));
(d0=j_shr(d0,7));
Mem::ww(j_add(a0,4),d0);
if(!((int16_t(Mem::w(PlayerBss::Plr2_Health_w)) > 0))) {
Macros::FREE_OBJ(a0);
}
(a0=Mem::l(PlayerBss::Plr1_ObjectPtr_l));
Mem::wb(j_add(a0,Defs::ObjT_TypeID_b),Defs::OBJ_TYPE_PLAYER1);
(d0=Mem::w(PlayerBss::Plr1_AngPos_w));
(d0=TablesData::AMOD_A(d0));
Mem::ww(j_add(a0,Defs::EntT_CurrentAngle_w),d0);
(a1=Mem::l(LevelBss::Lvl_ObjectPointsPtr_l));
(d0=Mem::w(a0));
Mem::wl(j_add(a1,(int16_t(d0) * 8)),Mem::l(PlayerBss::Plr1_XOff_l));
Mem::wl(j_add(j_add(a1,(int16_t(d0) * 8)),4),Mem::l(PlayerBss::Plr1_ZOff_l));
(a1=Mem::l(PlayerBss::Plr1_ZonePtr_l));
(d2=Mem::ub(j_add(a0,Defs::EntT_DamageTaken_b)));
if((d2 != 0)) {
int32_t d3=Mem::w(j_add(a0,Defs::EntT_ImpactX_w));
Mem::ww(PlayerBss::Plr1_SnapXSpdVal_l,j_add(Mem::w(PlayerBss::Plr1_SnapXSpdVal_l),d3));
(d3=Mem::w(j_add(a0,Defs::EntT_ImpactZ_w)));
Mem::ww(PlayerBss::Plr1_SnapZSpdVal_l,j_add(Mem::w(PlayerBss::Plr1_SnapZSpdVal_l),d3));
Mem::ww(PlayerBss::Plr1_Health_w,(Mem::w(PlayerBss::Plr1_Health_w) - d2));
}
Mem::wb(j_add(a0,Defs::EntT_DamageTaken_b),0);
Mem::wb(j_add(a0,Defs::EntT_HitPoints_b),10);
Mem::wb(j_add(a0,Defs::ShotT_InUpperZone_b),Mem::b(PlayerBss::Plr1_StoodInTop_b));
Mem::ww(j_add(a0,Defs::ObjT_ZoneID_w),Mem::w(a1));
(d2=Mem::w(a1));
(a1=ZoneBss::Zone_BrightTable_vl);
(d2=Mem::l(j_add(a1,(int16_t(d2) * 4))));
if((Mem::b(PlayerBss::Plr1_StoodInTop_b) == 0)) {
(d2=M68k::swap(d2));
}
Mem::ww(j_add(a0,2),d2);
(d0=Mem::l(PlayerBss::Plr1_TmpYOff_l));
(d1=Mem::l(PlayerBss::plr1_TmpHeight_l));
(d1=j_shr(d1,1));
(d0=j_add(d0,d1));
(d0=j_shr(d0,7));
Mem::ww(j_add(a0,4),d0);
(d0=Newaliencontrol::ViewpointToDraw(a0));
(d0=j_add(d0,d0));
Hires::plr_Use_AnimSetup(a0,d0,Defs::GLFT_Player1Graphic_w);
if(!((int16_t(Mem::w(PlayerBss::Plr1_Health_w)) > 0))) {
Macros::FREE_OBJ(a0);
}
(a0=Mem::l(PlayerBss::Plr2_ObjectPtr_l));
if(!((int16_t(Mem::w(PlayerBss::Plr2_Health_w)) > 0))) {
Macros::FREE_OBJ_2(a0,Defs::ENT_NEXT);
return ;
}
(a1=Mem::l(PlayerBss::Plr2_ZonePtr_l));
(d0=Mem::w(j_add(a0,Defs::EntT_CurrentAngle_w)));
(d0=M68k::setw(d0,j_add(d0,TablesData::SINE_SIZE)));
(d0=TablesData::AMOD_A(d0));
Mem::ww(j_add(j_add(a0,Defs::EntT_CurrentAngle_w),Defs::ENT_NEXT),d0);
Mem::ww(j_add(j_add(a0,Defs::ObjT_ZoneID_w),Defs::ENT_NEXT),Mem::w(a1));
Mem::ww(j_add(j_add(a0,Defs::EntT_ZoneID_w),Defs::ENT_NEXT),Mem::w(a1));
(d0=Mem::ub(PlayerBss::Plr2_TmpGunSelected_b));
(a1=j_add(Mem::l(HiresData::GLF_DatabasePtr_l),Defs::GLFT_GunObjects_l));
(d0=Mem::w(j_add(a1,(int16_t(d0) * 2))));
Mem::wb(j_add(j_add(a0,Defs::EntT_Type_b),Defs::ENT_NEXT),d0);
Mem::wb(j_add(j_add(a0,Defs::ObjT_TypeID_b),Defs::ENT_NEXT),Defs::OBJ_TYPE_OBJECT);
(d0=Mem::w(a0));
(d1=Mem::w(j_add(a0,Defs::ENT_NEXT)));
(a1=Mem::l(LevelBss::Lvl_ObjectPointsPtr_l));
Mem::wl(j_add(a1,(int16_t(d1) * 8)),Mem::l(j_add(a1,(int16_t(d0) * 8))));
Mem::wl(j_add(j_add(a1,(int16_t(d1) * 8)),4),Mem::l(j_add(j_add(a1,(int16_t(d0) * 8)),4)));
Mem::wb(j_add(j_add(a0,Defs::EntT_WhichAnim_b),Defs::ENT_NEXT),0xFF);
(d0=Mem::l(PlayerBss::Plr2_TmpYOff_l));
(d1=Mem::l(PlayerBss::plr2_TmpHeight_l));
(d1=j_shr(d1,2));
(d1=j_add(d1,(10 * 128)));
(d0=j_add(d0,d1));
(d0=j_shr(d0,7));
Mem::ww(j_add(j_add(a0,4),Defs::ENT_NEXT),d0);
(d1=Mem::l(PlayerBss::plr2_BobbleY_l));
(d1=j_shr(d1,8));
(d0=d1);
(d0=j_shr(d0,1));
(d1=j_add(d1,d0));
Mem::ww(j_add(j_add(a0,4),Defs::ENT_NEXT),j_add(Mem::w(j_add(j_add(a0,4),Defs::ENT_NEXT)),d1));
Mem::wb(j_add(j_add(a0,Defs::ShotT_InUpperZone_b),Defs::ENT_NEXT),Mem::b(j_add(a0,Defs::ShotT_InUpperZone_b)));
}

void DOALLANIMS(){
Mem::wb(HiresData::thistime,(Mem::ub(HiresData::thistime) - 1));
if((int8_t(Mem::b(HiresData::thistime)) > 0)) {
return ;
}
Mem::wb(HiresData::thistime,5);
int32_t a5=TablesBss::ObjectWorkspace_vl;
int32_t a0=Mem::l(LevelBss::Lvl_ObjectDataPtr_l);
while((int16_t(Mem::w(a0)) >= 0)){
int32_t d0=Mem::w(j_add(a0,Defs::ObjT_ZoneID_w));
if((d0 >= 0)) {
Mem::ww(j_add(a0,Defs::EntT_ZoneID_w),d0);
if((Mem::b(j_add(a0,Defs::ShotT_Worry_b)) != 0)) {
if((int8_t(Mem::ub(j_add(a0,Defs::ObjT_TypeID_b))) < 1)) {
Hires::doAlienAnim(a0,a5);
}
}
}
(a0+=Defs::ENT_NEXT);
(a5+=8);
}
}

void doAlienAnim(int32_t a0,int32_t a5){
int32_t d0=Mem::ub(j_add(a0,Defs::EntT_WhichAnim_b));
if((int8_t(d0) > 3)) return ;
switch(d0){
case 1:
{(d0=8);
break;
}
case 2:
{(d0=9);
break;
}
case 3:
{(d0=10);
break;
}
default:
{(d0=0);
break;
}
}
Mem::wb(j_add(a5,2),d0);
int32_t a6=j_add(Mem::l(HiresData::GLF_DatabasePtr_l),Defs::GLFT_AlienAnims_l);
int32_t type=Mem::ub(j_add(a0,Defs::EntT_Type_b));
(a6+=(Defs::A_AnimLen * type));
(a6+=(Defs::A_OptLen * d0));
int32_t d1=Mem::uw(j_add(a0,Defs::EntT_Timer2_w));
int32_t d2=d1;
int32_t frame=(Defs::A_FrameLen * d1);
(d0=Mem::ub(j_add(j_add(a6,5),frame)));
if((d0 != 0)) {
Mem::ww(HiresData::Aud_SampleNum_w,(d0 - 1));
Mem::wb(HiresData::notifplaying,0);
Mem::ww(HiresData::IDNUM,Mem::uw(a0));
Mem::ww(HiresData::Aud_NoiseVol_w,80);
int32_t a1=j_add(TablesBss::ObjRotated_vl,(Mem::uw(a0) * 8));
Mem::wl(HiresData::Aud_NoiseX_w,Mem::l(a1));
Hires::MakeSomeNoise();
}
(d0=Mem::ub(j_add(j_add(a6,6),frame)));
if((d0 != 0)) {
Mem::wb(a5,j_add(Mem::ub(a5),1));
Mem::wb(j_add(a5,1),d2);
}
(d2=(j_add(d2,1) & 0xFFFF));
(d0=Mem::ub(j_add(j_add(a6,7),frame)));
if((d0 != 0)) {
int32_t d3=(d0 & 63);
(d0=j_ushr((d0 & 0xFFFF),6));
bool storeval{};
if((d0 < 2)) {
(storeval=true);
}
else if((d0 == 2)) {
int32_t rnd=Objectmove::GetRand();
int32_t rem=j_mod(rnd,d3);
(d3=(rem & 0xFFFF));
(storeval=true);
}
else {
Mem::wb(j_add(a5,4),(Mem::ub(j_add(a5,4)) - 1));
if(((Mem::ub(j_add(a5,4)) & 0xFF) == 0)) {
(storeval=false);
}
else {
(d2=(d3 & 0xFFFF));
(storeval=false);
}
}
if(storeval) {
Mem::wb(j_add(a5,4),d3);
}
}
int32_t d3f=(Defs::A_FrameLen * d2);
if((int8_t(Mem::b(j_add(a6,d3f))) < 0)) {
Mem::wb(j_add(a5,3),0xFF);
(d2=0);
}
Mem::ww(j_add(a0,Defs::EntT_Timer2_w),d2);
}

void floorDamage(int32_t zonePtrL,int32_t stoodTopB,int32_t snapYOffL,int32_t snapTYOffL,int32_t objPtrL){
int32_t a0=Mem::l(zonePtrL);
int32_t d2=Mem::l(j_add(a0,Defs::ZoneT_Water_l));
int32_t d0=Mem::w(j_add(a0,Defs::ZoneT_FloorNoise_w));
if((Mem::b(stoodTopB) != 0)) {
(d0=Mem::w(j_add(a0,Defs::ZoneT_UpperFloorNoise_w)));
}
bool apply{};
if((d2 < Mem::l(snapYOffL))) {
(apply=true);
}
else {
(apply=(Mem::l(snapTYOffL) <= Mem::l(snapYOffL)));
}
if(apply) {
int32_t fa=j_add(Mem::l(HiresData::GLF_DatabasePtr_l),Defs::GLFT_FloorData_l);
(d0=Mem::w(j_add(fa,((d0 & 0xFFFF) * 4))));
int32_t obj=Mem::l(objPtrL);
Mem::wb(j_add(obj,Defs::EntT_DamageTaken_b),j_add(Mem::ub(j_add(obj,Defs::EntT_DamageTaken_b)),d0));
}
}

void dosomething(){
Mem::ww(AnimBss::Anim_FramesToDraw_w,j_add(Mem::w(AnimBss::Anim_FramesToDraw_w),1));
Hires::DOALLANIMS();
Mem::ww(HiresData::timetodamage,(Mem::w(HiresData::timetodamage) - 1));
if((int16_t(Mem::w(HiresData::timetodamage)) <= 0)) {
Mem::ww(HiresData::timetodamage,100);
Hires::floorDamage(PlayerBss::Plr1_ZonePtr_l,PlayerBss::Plr1_StoodInTop_b,PlayerBss::Plr1_SnapYOff_l,PlayerBss::Plr1_SnapTYOff_l,PlayerBss::Plr1_ObjectPtr_l);
Hires::floorDamage(PlayerBss::Plr2_ZonePtr_l,PlayerBss::Plr2_StoodInTop_b,PlayerBss::Plr2_SnapYOff_l,PlayerBss::Plr2_SnapTYOff_l,PlayerBss::Plr2_ObjectPtr_l);
}
int32_t a5=TablesBss::KeyMap_vb;
if((Mem::b(j_add(a5,RawKeyMacros::RAWKEY_F3)) != 0)) {
if((Mem::b(HiresData::lasttogsound) == 0)) {
Mem::wb(HiresData::lasttogsound,0xFF);
int32_t d0=(j_add(Mem::w(Pauseopts::TOPPOPT),1) & 3);
Mem::ww(Pauseopts::TOPPOPT,d0);
Mem::wb(HiresData::Aud_Stereo_b,Mem::ub(j_add(HiresData::STEROPT,(d0 * 2))));
int32_t d1=Mem::ub(j_add(j_add(HiresData::STEROPT,(d0 * 2)),1));
int32_t aMsg=j_add(TextData::Game_SoundOptionsText_vb,(d0 * Defs::OPTS_MESSAGE_LENGTH));
Message::Msg_PushLine(aMsg,(Defs::OPTS_MESSAGE_LENGTH | Defs::MSG_TAG_OPTIONS));
Mem::wb(j_add(ControlloopData::Prefsfile,1),d1);
int32_t chv=((d1 == '4')?0xFF:0);
Mem::wb(j_add(HiresData::CHANNELDATA,8),chv);
Mem::wb(j_add(HiresData::CHANNELDATA,12),chv);
Mem::wb(j_add(HiresData::CHANNELDATA,24),chv);
Mem::wb(j_add(HiresData::CHANNELDATA,28),chv);
Mem::wb(j_add(HiresData::CHANNELDATA,8),0xFF);
Mem::wb(HiresData::CHANNELDATA,0xFF);
CustomChips::write16(j_add(0xdff000,0x096),0xf);
CustomChips::write32(0xdff0a0,HiresData::Aud_Null1_vw);
CustomChips::write16(0xdff0a4,100);
CustomChips::write16(0xdff0a6,443);
CustomChips::write16(0xdff0a8,63);
CustomChips::write32(0xdff0b0,HiresData::Aud_Null2_vw);
CustomChips::write16(0xdff0b4,100);
CustomChips::write16(0xdff0b6,443);
CustomChips::write16(0xdff0b8,63);
CustomChips::write32(0xdff0c0,HiresData::Aud_Null4_vw);
CustomChips::write16(0xdff0c4,100);
CustomChips::write16(0xdff0c6,443);
CustomChips::write16(0xdff0c8,63);
CustomChips::write32(0xdff0d0,HiresData::Aud_Null3_vw);
CustomChips::write16(0xdff0d4,100);
CustomChips::write16(0xdff0d6,443);
CustomChips::write16(0xdff0d8,63);
Mem::wl(HiresData::pos0LEFT,TablesBss::Aud_EmptyBuffer_vl);
Mem::wl(HiresData::pos1LEFT,TablesBss::Aud_EmptyBuffer_vl);
Mem::wl(HiresData::pos2LEFT,TablesBss::Aud_EmptyBuffer_vl);
Mem::wl(HiresData::pos3LEFT,TablesBss::Aud_EmptyBuffer_vl);
Mem::wl(HiresData::pos0RIGHT,TablesBss::Aud_EmptyBuffer_vl);
Mem::wl(HiresData::pos1RIGHT,TablesBss::Aud_EmptyBuffer_vl);
Mem::wl(HiresData::pos2RIGHT,TablesBss::Aud_EmptyBuffer_vl);
Mem::wl(HiresData::pos3RIGHT,TablesBss::Aud_EmptyBuffer_vl);
Mem::wl(HiresData::Samp0endLEFT,TablesBss::Aud_EmptyBufferEnd);
Mem::wl(HiresData::Samp1endLEFT,TablesBss::Aud_EmptyBufferEnd);
Mem::wl(HiresData::Samp2endLEFT,TablesBss::Aud_EmptyBufferEnd);
Mem::wl(HiresData::Samp3endLEFT,TablesBss::Aud_EmptyBufferEnd);
Mem::wl(HiresData::Samp0endRIGHT,TablesBss::Aud_EmptyBufferEnd);
Mem::wl(HiresData::Samp1endRIGHT,TablesBss::Aud_EmptyBufferEnd);
Mem::wl(HiresData::Samp2endRIGHT,TablesBss::Aud_EmptyBufferEnd);
Mem::wl(HiresData::Samp3endRIGHT,TablesBss::Aud_EmptyBufferEnd);
}
}
else {
Mem::wb(HiresData::lasttogsound,0);
}
if((Mem::b(j_add(a5,RawKeyMacros::RAWKEY_F4)) != 0)) {
if((Mem::b(HiresData::OLDLTOG) == 0)) {
Mem::wb(HiresData::OLDLTOG,0xFF);
int32_t d0=TextData::Game_LightingOptionsText_vb;
Mem::wb(NewanimsData::Anim_LightingEnabled_b,~(Mem::b(NewanimsData::Anim_LightingEnabled_b)));
if((Mem::b(NewanimsData::Anim_LightingEnabled_b) != 0)) {
(d0+=Defs::OPTS_MESSAGE_LENGTH);
}
Message::Msg_PushLine(d0,(Defs::OPTS_MESSAGE_LENGTH | Defs::MSG_TAG_OPTIONS));
}
}
else {
Mem::wb(HiresData::OLDLTOG,0);
}
if((Mem::b(HiresData::draw_RenderMap_b) == 0)) {
Vid::Vid_CheckSettingsAdjust(a5);
}
if((Mem::b(j_add(a5,RawKeyMacros::RAWKEY_F6)) != 0)) {
if((Mem::b(HiresData::OLDGOOD) == 0)) {
Mem::wb(HiresData::OLDGOOD,0xFF);
int32_t d0=TextData::Game_DrawHighQualityText_vb;
Mem::wb(HireswallData::Draw_GoodRender_b,~(Mem::b(HireswallData::Draw_GoodRender_b)));
if((Mem::b(HireswallData::Draw_GoodRender_b) == 0)) {
(d0=TextData::Game_DrawLowQualityText_vb);
}
Message::Msg_PushLine(d0,(Defs::OPTS_MESSAGE_LENGTH | Defs::MSG_TAG_OPTIONS));
}
}
else {
Mem::wb(HiresData::OLDGOOD,0);
}
if((Mem::b(j_add(a5,RawKeyMacros::RAWKEY_TAB)) != 0)) {
if((Mem::b(HiresData::tabheld) == 0)) {
Mem::wb(HiresData::MAPON,~(Mem::b(HiresData::MAPON)));
Mem::wb(HiresData::tabheld,0xFF);
}
}
else {
Mem::wb(HiresData::tabheld,0);
}
Hires::loop_MapScroll(a5);
Music::mt_music();
int32_t ap=Mem::l(HiresData::alanptr);
Mem::wl(HiresData::alframe,Mem::l(ap));
(ap+=4);
int32_t endalan=j_add(HiresData::alan,(32 * 4));
if((ap >= endalan)) (ap=HiresData::alan);
Mem::wl(HiresData::alanptr,ap);
if((Mem::b(HiresData::READCONTROLS) != 0)) {
if((Mem::b(PlayerBss::Plr_MultiplayerType_b) == Hires::PLR_SLAVE)) {
Hires::doPlayer2Controls();
}
else {
Hires::doPlayer1Controls();
}
}
if(((Mem::b(HiresData::dosounds) != 0) && (Mem::b(j_add(ControlloopData::Prefsfile,1)) == '4'))) {
int32_t d0=0;
if((Mem::b(HiresData::NoiseMade0LEFT) != 0)) (d0=1);
if((Mem::b(HiresData::NoiseMade0RIGHT) != 0)) (d0|=2);
if((Mem::b(HiresData::NoiseMade1RIGHT) != 0)) (d0|=4);
if((Mem::b(HiresData::NoiseMade1LEFT) != 0)) (d0|=8);
(d0&=0xfffe);
CustomChips::write16(j_add(0xdff000,0x096),d0);
}
Hires::JUSTSOUNDS();
}

void doPlayer1Controls(){
if((int16_t(Mem::w(PlayerBss::Plr1_Health_w)) > 0)) {
if((Mem::b(PlayerBss::Plr1_Mouse_b) != 0)) Plr1control::Plr1_MouseControl();
if((Mem::b(PlayerBss::Plr1_Keys_b) != 0)) Plr1control::Plr1_KeyboardControl();
if((Mem::b(PlayerBss::Plr1_Joystick_b) != 0)) Plr1control::Plr1_JoystickControl();
return ;
}
Mem::wl(HiresData::hitcol,(7 * 2116));
Macros::FREE_OBJ_2(Mem::l(PlayerBss::Plr1_ObjectPtr_l),Defs::ENT_NEXT_2);
Mem::wb(PlayerBss::Plr1_Fire_b,0);
Mem::wb(PlayerBss::Plr1_Clicked_b,0);
Mem::ww(PlayerBss::Plr_AddToBobble_w,0);
Mem::wl(PlayerBss::Plr1_SnapHeight_l,Hires::PLR_CROUCH_HEIGHT);
Hires::deadViewSetup();
Plr1control::Plr1_Fall();
Hires::applyDeadFriction(PlayerBss::Plr1_SnapXSpdVal_l,PlayerBss::Plr1_SnapZSpdVal_l,PlayerBss::Plr1_SnapXOff_l,PlayerBss::Plr1_SnapZOff_l,PlayerBss::Plr1_SnapAngSpd_w,PlayerBss::Plr1_SnapAngPos_w);
}

void doPlayer2Controls(){
if((int16_t(Mem::w(PlayerBss::Plr2_Health_w)) > 0)) {
if((Mem::b(PlayerBss::Plr2_Mouse_b) != 0)) Plr2control::Plr2_MouseControl();
if((Mem::b(PlayerBss::Plr2_Keys_b) != 0)) Plr2control::Plr2_KeyboardControl();
if((Mem::b(PlayerBss::Plr2_Joystick_b) != 0)) Plr2control::Plr2_JoystickControl();
return ;
}
Mem::wl(HiresData::hitcol,(7 * 2116));
Macros::FREE_OBJ_2(Mem::l(PlayerBss::Plr1_ObjectPtr_l),Defs::ENT_NEXT_2);
Mem::wb(PlayerBss::Plr2_Fire_b,0);
Mem::ww(PlayerBss::Plr_AddToBobble_w,0);
Mem::wl(PlayerBss::Plr2_SnapHeight_l,Hires::PLR_CROUCH_HEIGHT);
Hires::deadViewSetup();
Plr2control::Plr2_Fall();
Hires::applyDeadFriction(PlayerBss::Plr2_SnapXSpdVal_l,PlayerBss::Plr2_SnapZSpdVal_l,PlayerBss::Plr2_SnapXOff_l,PlayerBss::Plr2_SnapZOff_l,PlayerBss::Plr2_SnapAngSpd_w,PlayerBss::Plr2_SnapAngPos_w);
}

void deadViewSetup(){
int32_t d0=Mem::w(HiresData::View_LookMax_w);
Mem::ww(HireswallData::STOPOFFSET,d0);
(d0=-(d0));
(d0=int16_t(j_add(d0,Mem::w(HireswallData::TOTHEMIDDLE))));
Mem::ww(HireswallData::SMIDDLEY,d0);
Mem::wl(HireswallData::SBIGMIDDLEY,(d0 * Hires::SCREEN_WIDTH));
}

void applyDeadFriction(int32_t xSpd,int32_t zSpd,int32_t xOff,int32_t zOff,int32_t angSpd,int32_t angPos){
int32_t d6=Mem::l(xSpd);
int32_t d7=Mem::l(zSpd);
if((Mem::b(PlayerBss::Plr_Decelerate_b) != 0)) {
(d6=-(d6));
(d6=((d6 > 0)?j_add(j_shr(d6,3),1):j_shr(d6,3)));
(d7=-(d7));
(d7=((d7 > 0)?j_add(j_shr(d7,3),1):j_shr(d7,3)));
Mem::wl(xSpd,j_add(Mem::l(xSpd),d6));
Mem::wl(zSpd,j_add(Mem::l(zSpd),d7));
}
(d6=Mem::l(xSpd));
(d7=Mem::l(zSpd));
Mem::wl(xOff,j_add(Mem::l(xOff),d6));
Mem::wl(zOff,j_add(Mem::l(zOff),d7));
int32_t d3=Mem::w(angSpd);
if((Mem::b(PlayerBss::Plr_Decelerate_b) != 0)) {
(d3=j_shr(d3,2));
if((d3 < 0)) (d3+=1);
}
Mem::ww(angSpd,d3);
int32_t ap=j_add(j_add(Mem::w(angPos),d3),d3);
Mem::ww(angPos,TablesData::AMOD_A(ap));
}

void loop_MapScroll(int32_t a5){
bool up=(Mem::b(j_add(a5,RawKeyMacros::RAWKEY_NUM_8)) != 0);
bool down=(Mem::b(j_add(a5,RawKeyMacros::RAWKEY_NUM_2)) != 0);
bool left=(Mem::b(j_add(a5,RawKeyMacros::RAWKEY_NUM_4)) != 0);
bool right=(Mem::b(j_add(a5,RawKeyMacros::RAWKEY_NUM_6)) != 0);
bool ul=(Mem::b(j_add(a5,RawKeyMacros::RAWKEY_NUM_7)) != 0);
bool ur=(Mem::b(j_add(a5,RawKeyMacros::RAWKEY_NUM_9)) != 0);
bool dl=(Mem::b(j_add(a5,RawKeyMacros::RAWKEY_NUM_1)) != 0);
bool dr=(Mem::b(j_add(a5,RawKeyMacros::RAWKEY_NUM_3)) != 0);
bool d0=((up || ul) || ur);
bool d1=((down || dl) || dr);
bool d2=((left || ul) || dl);
bool d3=((right || dr) || ur);
int32_t zoom=j_add(Mem::w(DrawMap::Draw_MapZoomLevel_w),2);
int32_t step=j_shl(1,(zoom & 31));
if(d0) Mem::ww(DrawMap::draw_MapZOffset_w,(Mem::w(DrawMap::draw_MapZOffset_w) - step));
if(d1) Mem::ww(DrawMap::draw_MapZOffset_w,j_add(Mem::w(DrawMap::draw_MapZOffset_w),step));
if(d2) Mem::ww(DrawMap::draw_MapXOffset_w,j_add(Mem::w(DrawMap::draw_MapXOffset_w),step));
if(d3) Mem::ww(DrawMap::draw_MapXOffset_w,(Mem::w(DrawMap::draw_MapXOffset_w) - step));
if((Mem::b(j_add(a5,RawKeyMacros::RAWKEY_NUM_5)) != 0)) {
Mem::ww(DrawMap::draw_MapXOffset_w,0);
Mem::ww(DrawMap::draw_MapZOffset_w,0);
}
}

void mixPaulaChan(int32_t posA,int32_t posB,int32_t volAsym,int32_t volBsym,int32_t paulaVolReg,int32_t aubufFrontSym,int32_t aubufBackSym,int32_t paulaLCReg){
int32_t a3=Mem::l(aubufFrontSym);
CustomChips::write32(paulaLCReg,a3);
Mem::wl(aubufFrontSym,Mem::l(aubufBackSym));
Mem::wl(aubufBackSym,a3);
int32_t a0=posA;
int32_t a1=posB;
int32_t a2=HiresData::tab;
int32_t d0v=Mem::ub(volAsym);
int32_t d1v=Mem::ub(volBsym);
bool swapped=(d0v < d1v);
if(!(swapped)) {
if((d0v != 0)) {
(a2+=j_shl(j_div(j_shl(d1v,6),d0v),8));
CustomChips::write16(paulaVolReg,d0v);
}
}
else {
int32_t t=a0;
(a0=a1);
(a1=t);
(a2+=j_shl(j_div(j_shl(d0v,6),d1v),8));
CustomChips::write16(paulaVolReg,d1v);
}
for(int32_t i=0;(i < 50);(i)++){
int32_t dd=Mem::l(a0);
(a0+=4);
int32_t b1=Mem::ub((a1)++);
int32_t b2=Mem::ub((a1)++);
int32_t b3=Mem::ub((a1)++);
int32_t b4=Mem::ub((a1)++);
int32_t d5=(((j_shl(Mem::ub(j_add(a2,b1)),24) | j_shl(Mem::ub(j_add(a2,b2)),16)) | j_shl(Mem::ub(j_add(a2,b3)),8)) | Mem::ub(j_add(a2,b4)));
Mem::wl(a3,j_add(dd,d5));
(a3+=4);
}
if(swapped) {
int32_t t=a0;
(a0=a1);
(a1=t);
}
(Hires::mpcA0=a0);
(Hires::mpcA1=a1);
}

int32_t wrapSampEnd(int32_t pos,int32_t sampEndSym,int32_t volSym,int32_t chanData32,int32_t chanData2){
if((pos >= Mem::l(sampEndSym))) {
(pos=TablesBss::Aud_EmptyBuffer_vl);
Mem::wl(sampEndSym,TablesBss::Aud_EmptyBufferEnd);
Mem::wb(volSym,0);
Mem::ww(chanData32,0);
Mem::ww(chanData2,0);
}
return pos;
}

void newsampbitl(){
CustomChips::write16(0xdff09c,0x200);
if(((Hires::dbgTestSfx >= 0) || Hires::dbgForceFire)) {
int32_t m=j_max(j_max(j_max(Mem::ub(HiresData::vol0left),Mem::ub(HiresData::vol0right)),j_max(Mem::ub(HiresData::vol1left),Mem::ub(HiresData::vol1right))),j_max(j_max(Mem::ub(HiresData::vol2left),Mem::ub(HiresData::vol2right)),j_max(Mem::ub(HiresData::vol3left),Mem::ub(HiresData::vol3right))));
if((m > Hires::dbgMaxSoftVol)) (Hires::dbgMaxSoftVol=m);
int32_t pv=j_max(CustomChips::audVOL[1],j_max(CustomChips::audVOL[2],CustomChips::audVOL[3]));
if((pv > Hires::dbgMaxSfxPaulaVol)) (Hires::dbgMaxSfxPaulaVol=pv);
}
if((Mem::b(HiresData::CHANNELDATA) == 0)) {
Hires::mixPaulaChan(Mem::l(HiresData::pos0LEFT),Mem::l(HiresData::pos2LEFT),HiresData::vol0left,HiresData::vol2left,0xdff0a8,HiresData::Aupt0,HiresData::Auback0,0xdff0a0);
Mem::wl(HiresData::pos0LEFT,Hires::wrapSampEnd(Hires::mpcA0,HiresData::Samp0endLEFT,HiresData::vol0left,j_add(HiresData::LEFTCHANDATA,32),j_add(HiresData::LEFTCHANDATA,2)));
Mem::wl(HiresData::pos2LEFT,Hires::wrapSampEnd(Hires::mpcA1,HiresData::Samp2endLEFT,HiresData::vol2left,j_add(j_add(HiresData::LEFTCHANDATA,32),8),j_add(j_add(HiresData::LEFTCHANDATA,2),8)));
}
if((Mem::b(j_add(HiresData::CHANNELDATA,16)) == 0)) {
Hires::mixPaulaChan(Mem::l(HiresData::pos0RIGHT),Mem::l(HiresData::pos2RIGHT),HiresData::vol0right,HiresData::vol2right,0xdff0b8,HiresData::Aupt1,HiresData::Auback1,0xdff0b0);
Mem::wl(HiresData::pos0RIGHT,Hires::wrapSampEnd(Hires::mpcA0,HiresData::Samp0endRIGHT,HiresData::vol0right,j_add(HiresData::RIGHTCHANDATA,32),j_add(HiresData::RIGHTCHANDATA,2)));
Mem::wl(HiresData::pos2RIGHT,Hires::wrapSampEnd(Hires::mpcA1,HiresData::Samp2endRIGHT,HiresData::vol2right,j_add(j_add(HiresData::RIGHTCHANDATA,32),8),j_add(j_add(HiresData::RIGHTCHANDATA,2),8)));
}
Hires::mixPaulaChan(Mem::l(HiresData::pos1LEFT),Mem::l(HiresData::pos3LEFT),HiresData::vol1left,HiresData::vol3left,0xdff0d8,HiresData::Aupt2,HiresData::Auback2,0xdff0d0);
Mem::wl(HiresData::pos1LEFT,Hires::wrapSampEnd(Hires::mpcA0,HiresData::Samp1endLEFT,HiresData::vol1left,j_add(j_add(HiresData::LEFTCHANDATA,32),4),j_add(j_add(HiresData::LEFTCHANDATA,2),4)));
Mem::wl(HiresData::pos3LEFT,Hires::wrapSampEnd(Hires::mpcA1,HiresData::Samp3endLEFT,HiresData::vol3left,j_add(j_add(HiresData::LEFTCHANDATA,32),12),j_add(j_add(HiresData::LEFTCHANDATA,2),12)));
Hires::mixPaulaChan(Mem::l(HiresData::pos1RIGHT),Mem::l(HiresData::pos3RIGHT),HiresData::vol1right,HiresData::vol3right,0xdff0c8,HiresData::Aupt3,HiresData::Auback3,0xdff0c0);
Mem::wl(HiresData::pos1RIGHT,Hires::wrapSampEnd(Hires::mpcA0,HiresData::Samp1endRIGHT,HiresData::vol1right,j_add(j_add(HiresData::RIGHTCHANDATA,32),4),j_add(j_add(HiresData::RIGHTCHANDATA,2),4)));
Mem::wl(HiresData::pos3RIGHT,Hires::wrapSampEnd(Hires::mpcA1,HiresData::Samp3endRIGHT,HiresData::vol3right,j_add(j_add(HiresData::RIGHTCHANDATA,32),12),j_add(j_add(HiresData::RIGHTCHANDATA,2),12)));
CustomChips::write16(0xdff096,0x820f);
}

void resetSoftAudioChannels(){
int32_t e=TablesBss::Aud_EmptyBuffer_vl;
int32_t ee=TablesBss::Aud_EmptyBufferEnd;
Mem::wl(HiresData::pos0LEFT,e);
Mem::wl(HiresData::pos1LEFT,e);
Mem::wl(HiresData::pos2LEFT,e);
Mem::wl(HiresData::pos3LEFT,e);
Mem::wl(HiresData::pos0RIGHT,e);
Mem::wl(HiresData::pos1RIGHT,e);
Mem::wl(HiresData::pos2RIGHT,e);
Mem::wl(HiresData::pos3RIGHT,e);
Mem::wl(HiresData::Samp0endLEFT,ee);
Mem::wl(HiresData::Samp1endLEFT,ee);
Mem::wl(HiresData::Samp2endLEFT,ee);
Mem::wl(HiresData::Samp3endLEFT,ee);
Mem::wl(HiresData::Samp0endRIGHT,ee);
Mem::wl(HiresData::Samp1endRIGHT,ee);
Mem::wl(HiresData::Samp2endRIGHT,ee);
Mem::wl(HiresData::Samp3endRIGHT,ee);
}

void JUSTSOUNDS(){
if((Mem::b(HiresData::dosounds) == 0)) return ;
Hires::pumpAudioToHost();
}

void pumpAudioToHost(){
try{if(Audio::dbgCapture) {
Hires::newsampbitl();
Audio::captureFrame();
return ;
}
if(!(Audio::ensureStarted())) return ;
int32_t guard=0;
while((Audio::needsBuffer() && ((guard)++ < 8))){
Hires::newsampbitl();
Audio::queueFromPaula();
}
}catch(const std::exception& t){if(!(Hires::dbgAudioCrashLogged)) {
j_log(j_add("[audio] exception de mixage capturée (canaux réinitialisés, jeu poursuivi) : ",t));
(Hires::dbgAudioCrashLogged=true);
}
Hires::resetSoftAudioChannels();
}}

bool dbgGeomHit(int32_t zone){
return {};}

void dbgPlayerTrace(){
return;}

void dbgAiTrace(){
return;}

void VBlankInterrupt(){
if((Hires::dbgTestMsg && (Mem::l(HiresData::Vid_VBLCount_l) == 10))) {
int32_t s=TablesBss::ObjectWorkspace_vl;
std::string t="PORTAGE JAVA - MESSAGE DE TEST 123";
for(int32_t i=0;(i < t.length());(i)++)Mem::wb(j_add(s,i),t.at(i));
Mem::wb(j_add(s,t.length()),0);
Message::Msg_PushLine(s,t.length());
}
if(Hires::dbgSwitchTest) {
(CustomChips::mouseRightPressed=(j_mod(Mem::l(HiresData::Vid_VBLCount_l),8) < 4));
}
if(Hires::dbgWeaponTest) {
int64_t vbl=Mem::l(HiresData::Vid_VBLCount_l);
int32_t gun=int32_t(j_mod(j_div(vbl,Hires::DBG_FRAMES_PER_GUN),Defs::NUM_GUN_DEFS));
if((j_mod(vbl,Hires::DBG_FRAMES_PER_GUN) == 0)) Mem::ww(PlayerBss::Plr1_TimeToShoot_w,0);
Mem::wb(PlayerBss::Plr1_GunSelected_b,gun);
Mem::ww(PlayerBss::Plr1_Health_w,200);
Mem::ww(PlayerBss::Plr2_Health_w,200);
(CustomChips::mouseLeftPressed=(j_mod(vbl,Hires::DBG_FRAMES_PER_GUN) < 2));
}
if(Hires::dbgForceFire) (CustomChips::mouseLeftPressed=true);
if(Hires::dbgForceWalk) Mem::wb(j_add(TablesBss::KeyMap_vb,RawKeyMacros::RAWKEY_W),0xFF);
Mem::wl(HiresData::Vid_VBLCount_l,j_add(Mem::l(HiresData::Vid_VBLCount_l),1));
Mem::ww(AnimBss::Anim_Timer_w,(Mem::w(AnimBss::Anim_Timer_w) - 1));
if(((Hires::dbgTestSfx >= 0) && (j_mod(Mem::l(HiresData::Vid_VBLCount_l),50) == 10))) {
Mem::ww(HiresData::Aud_SampleNum_w,Hires::dbgTestSfx);
Mem::ww(HiresData::IDNUM,0x1234);
Mem::wb(HiresData::notifplaying,0xFF);
Mem::wl(HiresData::Aud_NoiseX_w,0);
Mem::wb(HiresData::PlayEcho,0);
Mem::wb(HiresData::Aud_ChannelPick_b,1);
Mem::ww(HiresData::Aud_NoiseVol_w,300);
Hires::MakeSomeNoise();
}
if((Mem::b(HiresData::Game_Running_b) != 0)) {
Hires::dosomething();
}
else {
Hires::JUSTSOUNDS();
}
}

void OtherInter(){
throw std::runtime_error("hires.s::OtherInter (interruption, couche hôte)");
}

void key_interrupt(){
throw std::runtime_error("hires.s::key_interrupt (interruption clavier, couche hôte)");
}

}