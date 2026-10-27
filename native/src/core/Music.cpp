#include "original.hpp"
namespace Music {
void mt_init(){
int32_t a0=Mem::l(Music::mt_data);
int32_t a1=a0;
(a1+=0x3b8);
int32_t d0=0x7f;
int32_t d1=0;
int32_t d2{};
while(true){
{
(d2=d1);
(d0=M68k::setw(d0,(d0 - 1)));
while(true){
(d1=M68k::setb(d1,Mem::ub(a1)));
(a1+=1);
if((int8_t(d1) > int8_t(d2))) {
goto mt_loop_continue;
}
(d0=M68k::setw(d0,(d0 - 1)));
if((int16_t(d0) == -(1))) {
goto mt_loop_end;
}
}
}

mt_loop_continue:;
}
mt_loop_end:;
(d2=M68k::setb(d2,j_add(d2,1)));
(a1=Music::mt_samplestarts);
(d2<<=8);
(d2<<=2);
(d2+=0x43c);
(d2+=a0);
int32_t a2=d2;
(d0=0x1e);
do {
(d1=0);
(d1=M68k::setw(d1,Mem::uw(j_add(a0,42))));
if((int16_t(d1) != 0)) {
Mem::wl(a2,0);
Mem::wl(a1,a2);
(a1+=4);
}
else {
Mem::wl(a1,HiresData::nullsample);
(a1+=4);
}
(d1<<=1);
(a2+=d1);
(a0+=0x1e);
(d0=M68k::setw(d0,(d0 - 1)));
}
while((int16_t(d0) != -(1)));
CustomChips::ciaOr(0x2);
Mem::wb(Music::mt_speed,0x6);
CustomChips::write16(0xdff0a8,0);
CustomChips::write16(0xdff0b8,0);
CustomChips::write16(0xdff0c8,0);
CustomChips::write16(0xdff0d8,0);
Mem::wb(Music::mt_songpos,0);
Mem::wb(Music::mt_counter,0);
Mem::ww(Music::mt_pattpos,0);
}

void mt_end(){
CustomChips::write16(0xdff0a8,0);
CustomChips::write16(0xdff0b8,0);
CustomChips::write16(0xdff0c8,0);
CustomChips::write16(0xdff0d8,0);
CustomChips::write16(0xdff096,0xf);
}

void mt_music(){
int32_t a0=Mem::l(Music::mt_data);
Mem::wb(Music::mt_counter,j_add(Mem::ub(Music::mt_counter),1));
int32_t d0=Mem::ub(Music::mt_counter);
if((int8_t(d0) < int8_t(Mem::b(Music::mt_speed)))) {
int32_t a6=Music::mt_voice1;
int32_t a5=0xdff0a0;
Music::mt_checkcom(a5,a6);
if((Mem::b(HiresData::UseAllChannels) != 0)) {
(a6=Music::mt_voice2);
(a5=0xdff0b0);
Music::mt_checkcom(a5,a6);
(a6=Music::mt_voice3);
(a5=0xdff0c0);
Music::mt_checkcom(a5,a6);
(a6=Music::mt_voice4);
(a5=0xdff0d0);
Music::mt_checkcom(a5,a6);
}
Music::mt_endr();
return ;
}
Mem::wb(Music::mt_counter,0);
Music::mt_getnew();
}

void mt_arpeggio(int32_t a5,int32_t a6){
int32_t d0=0;
(d0=M68k::setb(d0,Mem::ub(Music::mt_counter)));
(d0=M68k::divs(d0,3));
(d0=M68k::swap(d0));
int32_t d2{};
if((int16_t(d0) == 0)) {
(d2=Mem::uw(j_add(a6,0x10)));
CustomChips::write16(j_add(a5,0x6),d2);
return ;
}
if((int16_t(d0) == 2)) {
(d0=0);
(d0=M68k::setb(d0,Mem::ub(j_add(a6,0x3))));
(d0=M68k::setb(d0,(d0 & 0xf)));
}
else {
(d0=0);
(d0=M68k::setb(d0,Mem::ub(j_add(a6,0x3))));
(d0=M68k::setb(d0,j_ushr((d0 & 0xFF),4)));
}
(d0=M68k::setw(d0,j_shl(d0,1)));
int32_t d1=0;
(d1=M68k::setw(d1,Mem::uw(j_add(a6,0x10))));
int32_t ta0=Music::mt_periods;
int32_t d7=0x24;
do {
(d2=Mem::uw(j_add(ta0,int16_t(d0))));
if((int16_t(d1) >= Mem::w(ta0))) {
CustomChips::write16(j_add(a5,0x6),d2);
return ;
}
(ta0+=2);
(d7=M68k::setw(d7,(d7 - 1)));
}
while((int16_t(d7) != -(1)));
}

void mt_getnew(){
int32_t a0=Mem::l(Music::mt_data);
int32_t a3=a0;
int32_t a2=a0;
(a3+=0xc);
(a2+=0x3b8);
(a0+=0x43c);
int32_t d0=0;
int32_t d1=0;
(d0=M68k::setb(d0,Mem::ub(Music::mt_songpos)));
(d1=M68k::setb(d1,Mem::ub(j_add(a2,int16_t(d0)))));
(d1<<=8);
(d1<<=2);
(d1+=Mem::w(Music::mt_pattpos));
Mem::ww(Music::mt_dmacon,0);
int32_t a5=0xdff0a0;
int32_t a6=Music::mt_voice1;
(d1=Music::mt_playvoice(a0,a3,d1,a5,a6));
if((Mem::b(HiresData::UseAllChannels) != 0)) {
(a5=0xdff0b0);
(a6=Music::mt_voice2);
(d1=Music::mt_playvoice(a0,a3,d1,a5,a6));
(a5=0xdff0c0);
(a6=Music::mt_voice3);
(d1=Music::mt_playvoice(a0,a3,d1,a5,a6));
(a5=0xdff0d0);
(a6=Music::mt_voice4);
(d1=Music::mt_playvoice(a0,a3,d1,a5,a6));
}
Music::mt_setdma();
}

int32_t mt_playvoice(int32_t a0,int32_t a3,int32_t d1,int32_t a5,int32_t a6){
Mem::wl(a6,Mem::l(j_add(a0,d1)));
(d1+=4);
int32_t d2=0;
(d2=M68k::setb(d2,Mem::ub(j_add(a6,0x2))));
(d2=M68k::setb(d2,(d2 & 0xf0)));
(d2=M68k::setb(d2,j_ushr((d2 & 0xFF),4)));
int32_t d0=Mem::ub(a6);
(d0=(d0 & 0xf0));
(d2=M68k::setb(d2,(d0 | d2)));
if((int8_t(d2) != 0)) {
int32_t d3=0;
int32_t a1=Music::mt_samplestarts;
int32_t d4=d2;
(d2-=1);
(d2<<=2);
(d4=M68k::mulu(d4,0x1e));
Mem::wl(j_add(a6,0x4),Mem::l(j_add(a1,d2)));
Mem::ww(j_add(a6,0x8),Mem::uw(j_add(a3,d4)));
Mem::ww(j_add(a6,0x12),Mem::uw(j_add(j_add(a3,d4),0x2)));
(d3=M68k::setw(d3,Mem::uw(j_add(j_add(a3,d4),0x4))));
if((int16_t(d3) != 0)) {
(d2=Mem::l(j_add(a6,0x4)));
(d3=M68k::setw(d3,j_shl(d3,1)));
(d2+=d3);
Mem::wl(j_add(a6,0xa),d2);
(d0=Mem::uw(j_add(j_add(a3,d4),0x4)));
(d0=M68k::setw(d0,j_add(d0,Mem::uw(j_add(j_add(a3,d4),0x6)))));
Mem::ww(j_add(a6,8),d0);
Mem::ww(j_add(a6,0xe),Mem::uw(j_add(j_add(a3,d4),0x6)));
(d0=Mem::uw(j_add(a6,0x12)));
CustomChips::write16(j_add(a5,0x8),d0);
}
else {
(d2=Mem::l(j_add(a6,0x4)));
(d2+=d3);
Mem::wl(j_add(a6,0xa),d2);
Mem::ww(j_add(a6,0xe),Mem::uw(j_add(j_add(a3,d4),0x6)));
(d0=Mem::uw(j_add(a6,0x12)));
CustomChips::write16(j_add(a5,0x8),d0);
}
}
(d0=Mem::uw(a6));
(d0=(d0 & 0xfff));
if((d0 != 0)) {
(d0=M68k::setb(d0,Mem::ub(j_add(a6,0x2))));
(d0=M68k::setb(d0,(d0 & 0xF)));
if((int8_t(d0) == 0x3)) {
Music::mt_setmyport(a6);
Music::mt_checkcom2(a5,a6);
return d1;
}
Mem::ww(j_add(a6,0x10),Mem::uw(a6));
Mem::ww(j_add(a6,0x10),(Mem::uw(j_add(a6,0x10)) & 0xfff));
(d0=Mem::uw(j_add(a6,0x14)));
CustomChips::write16(0xdff096,d0);
Mem::wb(j_add(a6,0x1b),0);
CustomChips::write32(a5,Mem::l(j_add(a6,0x4)));
CustomChips::write16(j_add(a5,0x4),Mem::uw(j_add(a6,0x8)));
(d0=Mem::uw(j_add(a6,0x10)));
(d0=(d0 & 0xfff));
CustomChips::write16(j_add(a5,0x6),d0);
(d0=Mem::uw(j_add(a6,0x14)));
Mem::ww(Music::mt_dmacon,(Mem::uw(Music::mt_dmacon) | d0));
}
Music::mt_checkcom2(a5,a6);
return d1;
}

void mt_setdma(){
int32_t d0=250;
do {
Mem::ww(HiresData::testchip,j_add(Mem::uw(HiresData::testchip),1));
(d0=M68k::setw(d0,(d0 - 1)));
}
while((int16_t(d0) != -(1)));
(d0=Mem::uw(Music::mt_dmacon));
(d0=M68k::setw(d0,(d0 | 0x8000)));
if((Mem::b(HiresData::UseAllChannels) == 0)) {
(d0=M68k::setw(d0,(d0 & 0b1111111111110001)));
}
CustomChips::write16(0xdff096,d0);
(d0=250);
do {
Mem::ww(HiresData::testchip,j_add(Mem::uw(HiresData::testchip),1));
(d0=M68k::setw(d0,(d0 - 1)));
}
while((int16_t(d0) != -(1)));
int32_t a5=0xdff000;
int32_t a6{};
if((Mem::b(HiresData::UseAllChannels) != 0)) {
(a6=Music::mt_voice4);
CustomChips::write32(j_add(a5,0xd0),Mem::l(j_add(a6,0xa)));
CustomChips::write16(j_add(a5,0xd4),Mem::uw(j_add(a6,0xe)));
(a6=Music::mt_voice3);
CustomChips::write32(j_add(a5,0xc0),Mem::l(j_add(a6,0xa)));
CustomChips::write16(j_add(a5,0xc4),Mem::uw(j_add(a6,0xe)));
(a6=Music::mt_voice2);
CustomChips::write32(j_add(a5,0xb0),Mem::l(j_add(a6,0xa)));
CustomChips::write16(j_add(a5,0xb4),Mem::uw(j_add(a6,0xe)));
}
(a6=Music::mt_voice1);
CustomChips::write32(j_add(a5,0xa0),Mem::l(j_add(a6,0xa)));
CustomChips::write16(j_add(a5,0xa4),Mem::uw(j_add(a6,0xe)));
Mem::ww(Music::mt_pattpos,j_add(Mem::uw(Music::mt_pattpos),0x10));
if((Mem::uw(Music::mt_pattpos) == 0x400)) {
Music::mt_nex();
return ;
}
Music::mt_endr();
}

void mt_nex(){
Mem::ww(Music::mt_pattpos,0);
Mem::wb(Music::mt_break,0);
Mem::wb(Music::mt_songpos,j_add(Mem::ub(Music::mt_songpos),1));
Mem::wb(Music::mt_songpos,(Mem::ub(Music::mt_songpos) & 0x7f));
Music::mt_endr();
}

void mt_endr(){
if((Mem::b(Music::mt_break) != 0)) {
Music::mt_nex();
return ;
}
}

void mt_setmyport(int32_t a6){
int32_t d2=Mem::uw(a6);
(d2=(d2 & 0xfff));
Mem::ww(j_add(a6,0x18),d2);
int32_t d0=Mem::uw(j_add(a6,0x10));
Mem::wb(j_add(a6,0x16),0);
if((int16_t(d2) == int16_t(d0))) {
Mem::ww(j_add(a6,0x18),0);
return ;
}
if((int16_t(d2) >= int16_t(d0))) {
return ;
}
Mem::wb(j_add(a6,0x16),0x1);
}

void mt_myport(int32_t a5,int32_t a6){
int32_t d0=Mem::ub(j_add(a6,0x3));
if((int8_t(d0) != 0)) {
Mem::wb(j_add(a6,0x17),d0);
Mem::wb(j_add(a6,0x3),0);
}
if((Mem::w(j_add(a6,0x18)) == 0)) {
return ;
}
(d0=0);
(d0=M68k::setb(d0,Mem::ub(j_add(a6,0x17))));
if((Mem::b(j_add(a6,0x16)) != 0)) {
Mem::ww(j_add(a6,0x10),(Mem::uw(j_add(a6,0x10)) - d0));
(d0=Mem::uw(j_add(a6,0x18)));
if((int16_t(d0) < Mem::w(j_add(a6,0x10)))) {
CustomChips::write16(j_add(a5,0x6),Mem::uw(j_add(a6,0x10)));
return ;
}
Mem::ww(j_add(a6,0x10),Mem::uw(j_add(a6,0x18)));
Mem::ww(j_add(a6,0x18),0);
CustomChips::write16(j_add(a5,0x6),Mem::uw(j_add(a6,0x10)));
return ;
}
Mem::ww(j_add(a6,0x10),j_add(Mem::uw(j_add(a6,0x10)),d0));
(d0=Mem::uw(j_add(a6,0x18)));
if((int16_t(d0) <= Mem::w(j_add(a6,0x10)))) {
Mem::ww(j_add(a6,0x10),Mem::uw(j_add(a6,0x18)));
Mem::ww(j_add(a6,0x18),0);
}
CustomChips::write16(j_add(a5,0x6),Mem::uw(j_add(a6,0x10)));
}

void mt_vib(int32_t a5,int32_t a6){
int32_t d0=Mem::ub(j_add(a6,0x3));
if((int8_t(d0) != 0)) {
Mem::wb(j_add(a6,0x1a),d0);
}
(d0=Mem::ub(j_add(a6,0x1b)));
int32_t a4=Music::mt_sin;
(d0=M68k::setw(d0,j_ushr((d0 & 0xFFFF),2)));
(d0=M68k::setw(d0,(d0 & 0x1f)));
int32_t d2=0;
(d2=M68k::setb(d2,Mem::ub(j_add(a4,int16_t(d0)))));
(d0=M68k::setb(d0,Mem::ub(j_add(a6,0x1a))));
(d0=M68k::setw(d0,(d0 & 0xf)));
(d2=M68k::mulu(d2,d0));
(d2=M68k::setw(d2,j_ushr((d2 & 0xFFFF),6)));
(d0=M68k::setw(d0,Mem::uw(j_add(a6,0x10))));
if((Mem::b(j_add(a6,0x1b)) < 0)) {
(d0=M68k::setw(d0,(d0 - d2)));
}
else {
(d0=M68k::setw(d0,j_add(d0,d2)));
}
CustomChips::write16(j_add(a5,0x6),d0);
(d0=M68k::setb(d0,Mem::ub(j_add(a6,0x1a))));
(d0=M68k::setw(d0,j_ushr((d0 & 0xFFFF),2)));
(d0=M68k::setw(d0,(d0 & 0x3c)));
Mem::wb(j_add(a6,0x1b),j_add(Mem::ub(j_add(a6,0x1b)),d0));
}

void mt_checkcom(int32_t a5,int32_t a6){
int32_t d0=Mem::uw(j_add(a6,0x2));
(d0=(d0 & 0xfff));
if((d0 == 0)) {
CustomChips::write16(j_add(a5,0x6),Mem::uw(j_add(a6,0x10)));
return ;
}
(d0=M68k::setb(d0,Mem::ub(j_add(a6,0x2))));
(d0=M68k::setb(d0,(d0 & 0xf)));
if((int8_t(d0) == 0)) {
Music::mt_arpeggio(a5,a6);
return ;
}
if((int8_t(d0) == 0x1)) {
Music::mt_portup(a5,a6);
return ;
}
if((int8_t(d0) == 0x2)) {
Music::mt_portdown(a5,a6);
return ;
}
if((int8_t(d0) == 0x3)) {
Music::mt_myport(a5,a6);
return ;
}
if((int8_t(d0) == 0x4)) {
Music::mt_vib(a5,a6);
return ;
}
CustomChips::write16(j_add(a5,0x6),Mem::uw(j_add(a6,0x10)));
if((int8_t(d0) == 0xa)) {
Music::mt_volslide(a5,a6);
}
}

void mt_volslide(int32_t a5,int32_t a6){
int32_t d0=0;
(d0=M68k::setb(d0,Mem::ub(j_add(a6,0x3))));
(d0=M68k::setb(d0,j_ushr((d0 & 0xFF),4)));
if((int8_t(d0) == 0)) {
(d0=0);
(d0=M68k::setb(d0,Mem::ub(j_add(a6,0x3))));
(d0=M68k::setb(d0,(d0 & 0xf)));
Mem::ww(j_add(a6,0x12),(Mem::uw(j_add(a6,0x12)) - d0));
if((Mem::w(j_add(a6,0x12)) < 0)) {
Mem::ww(j_add(a6,0x12),0);
}
CustomChips::write16(j_add(a5,0x8),Mem::uw(j_add(a6,0x12)));
return ;
}
Mem::ww(j_add(a6,0x12),j_add(Mem::uw(j_add(a6,0x12)),d0));
if((Mem::w(j_add(a6,0x12)) >= 0x40)) {
Mem::ww(j_add(a6,0x12),0x40);
}
CustomChips::write16(j_add(a5,0x8),Mem::uw(j_add(a6,0x12)));
}

void mt_portup(int32_t a5,int32_t a6){
int32_t d0=0;
(d0=M68k::setb(d0,Mem::ub(j_add(a6,0x3))));
Mem::ww(j_add(a6,0x10),(Mem::uw(j_add(a6,0x10)) - d0));
(d0=M68k::setw(d0,Mem::uw(j_add(a6,0x10))));
(d0=M68k::setw(d0,(d0 & 0xfff)));
if((int16_t(d0) < 0x71)) {
Mem::ww(j_add(a6,0x10),(Mem::uw(j_add(a6,0x10)) & 0xf000));
Mem::ww(j_add(a6,0x10),(Mem::uw(j_add(a6,0x10)) | 0x71));
}
(d0=M68k::setw(d0,Mem::uw(j_add(a6,0x10))));
(d0=M68k::setw(d0,(d0 & 0xfff)));
CustomChips::write16(j_add(a5,0x6),d0);
}

void mt_portdown(int32_t a5,int32_t a6){
int32_t d0=0;
(d0=M68k::setb(d0,Mem::ub(j_add(a6,0x3))));
Mem::ww(j_add(a6,0x10),j_add(Mem::uw(j_add(a6,0x10)),d0));
(d0=M68k::setw(d0,Mem::uw(j_add(a6,0x10))));
(d0=M68k::setw(d0,(d0 & 0xfff)));
if((int16_t(d0) >= 0x358)) {
Mem::ww(j_add(a6,0x10),(Mem::uw(j_add(a6,0x10)) & 0xf000));
Mem::ww(j_add(a6,0x10),(Mem::uw(j_add(a6,0x10)) | 0x358));
}
(d0=M68k::setw(d0,Mem::uw(j_add(a6,0x10))));
(d0=M68k::setw(d0,(d0 & 0xfff)));
CustomChips::write16(j_add(a5,0x6),d0);
}

void mt_checkcom2(int32_t a5,int32_t a6){
int32_t d0=Mem::ub(j_add(a6,0x2));
(d0=(d0 & 0xf));
if((int8_t(d0) == 0xe)) {
(d0=Mem::ub(j_add(a6,0x3)));
(d0=j_shl((d0 & 0x1),1));
CustomChips::ciaAnd(0xfd);
CustomChips::ciaOr(d0);
return ;
}
if((int8_t(d0) == 0xd)) {
Mem::wb(Music::mt_break,~(Mem::ub(Music::mt_break)));
return ;
}
if((int8_t(d0) == 0xb)) {
Mem::wb(Music::reachedend,0xFF);
(d0=Mem::ub(j_add(a6,0x3)));
(d0=M68k::setb(d0,(d0 - 1)));
Mem::wb(Music::mt_songpos,d0);
Mem::wb(Music::mt_break,~(Mem::ub(Music::mt_break)));
return ;
}
if((int8_t(d0) == 0xc)) {
if((int8_t(Mem::b(j_add(a6,0x3))) > 0x40)) {
Mem::wb(j_add(a6,0x3),0x40);
}
(d0=Mem::ub(j_add(a6,0x3)));
CustomChips::write16(j_add(a5,0x8),d0);
return ;
}
if((int8_t(d0) == 0xf)) {
if((int8_t(Mem::b(j_add(a6,0x3))) > 0x1f)) {
Mem::wb(j_add(a6,0x3),0x1f);
}
(d0=Mem::ub(j_add(a6,0x3)));
if((int8_t(d0) != 0)) {
Mem::wb(Music::mt_speed,d0);
Mem::wb(Music::mt_counter,0);
}
}
}

}