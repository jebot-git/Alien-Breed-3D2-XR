#pragma once
#include <array>
#include <algorithm>
#include <cstdint>
#include <vector>
#include <nlohmann/json.hpp>
namespace ab3d2::lighting {
// Read-only port of original Objdrawhires CalcBrightsInZone, CalcBrightRings,
// TweenBrights and the flat polygon angle table. No original scratch RAM is used.
using Rings=std::array<int8_t,64>;
using PolyTable=std::array<float,256>;
inline int divs(int dividend,int divisor){divisor=int16_t(divisor);if(!divisor)return dividend;int q=dividend/divisor;if(q<-32768||q>32767)return dividend;return int16_t(q);}
inline int sector(int ox,int oz,int nx,int nz,const std::array<int16_t,5120>&sine){
 int x=int16_t(nx-ox),z=int16_t(nz-oz);int square=int32_t(uint32_t(x*x)+uint32_t(z*z));if(!square)return -1;
 int bit=31;while(bit>=0&&!(uint32_t(square)&(1u<<bit)))--bit;
 int root=1<<((bit>>1)&31);
 for(int i=0;i<3;++i){int delta=int32_t(uint32_t(root*root)-uint32_t(square))>>1;root=int16_t(root-divs(delta,root));if(root<=0)root=1;}
 root=int16_t(root+1);if(!root)return -1;
 int sinRet=int16_t(divs(int32_t(uint32_t(x)<<16)>>1,root)),cosRet=int16_t(divs(int32_t(uint32_t(z)<<16)>>1,root));
 int angle=0,step=2048;
 for(int i=0;i<4;++i){int s=sine[angle&4095],c=sine[(angle&4095)+1024];int cross=int32_t(uint32_t(c*sinRet)-uint32_t(s*cosRet));if(cross>=0)angle=int16_t(angle+2*step);angle=(angle-step)&4095;step>>=1;}
 return ((-(angle*2)&8191)>>9)&15;
}
inline int8_t pointValue(int v){if(v<0){v=int16_t(v+332);v=int16_t(v>>2);v=int16_t(-v);v=int16_t(v+332);}v=int16_t(v-300);if(v<0)v=0;return int8_t(v+(int8_t(v)>>1));}
inline void tween(Rings&r,int base){
 int current=0;while(current<16&&r[base+current]==-128)++current;if(current==16)return;int start=current,previous=current;
 do{do{current=(current+1)&15;}while(r[base+current]==-128);int first=uint8_t(r[base+previous]),last=uint8_t(r[base+current]),gap=(current-previous+16)%16;if(!gap)gap=16;
  int accumulator=first<<16,step=(last-first)*65536;if(step)step=((step>>7)*(16384/gap))>>7;
  for(int i=0;i<gap;++i){r[base+previous]=int8_t(accumulator>>16);accumulator+=step;previous=(previous+1)&15;}previous=current;
 }while(current!=start);
}
inline Rings rings(const nlohmann::json&level,const std::vector<float>&brightness,const std::vector<std::array<int,2>>&points,const std::array<int16_t,5120>&sine,int x,int z,int zone,bool upper=false,bool zoneOnly=false){
 Rings r;r.fill(-128);auto&zones=level["zones"];
 auto fill=[&](int zi,int base){if(zi<0||zi>=int(zones.size()))return;
  // The original scans past ten border words into the next zone until -1;
  // its brightness pointer crosses zone boundaries in exactly the same way.
  for(int i=0;i<int(zones.size())*10;++i){int list=zi+i/10;if(list>=int(zones.size()))break;auto&border=zones[list]["borderPointsRaw"];if(i%10>=int(border.size()))break;int p=border[i%10];if(p<0)break;if(p>=int(points.size()))continue;int s=sector(x,z,points[p][0],points[p][1],sine);if(s<0)continue;int flat=zi*40+i*4+(upper?2:0);if(flat+1>=int(brightness.size()))break;r[base+s]=pointValue(int(brightness[flat]));r[base+s+16]=pointValue(int(brightness[flat+1]));}
 };
 fill(zone,0);if(zoneOnly)return r;
 if(zone>=0&&zone<int(zones.size()))for(const auto&value:zones[zone]["edgeList"]){int ei=value;if(ei<0)break;if(ei>=int(level["edges"].size()))continue;auto&e=level["edges"][ei];int join=e.value("join",-1);if(join>=0)fill(join,32);else{int s=sector(x,z,int16_t(x-e["dz"].get<int>()),int16_t(z+e["dx"].get<int>()),sine);if(s>=0)r[32+s]=r[48+s]=48;}}
 for(int b:{0,16,32,48})tween(r,b);
 for(int i=0;i<16;++i){int bottom=int8_t(((48-int(r[32+i]))>>1)-r[i]),top=int8_t(((48-int(r[48+i]))>>1)-r[16+i]);r[i]=int8_t(-std::min(0,bottom));r[16+i]=int8_t(-std::min(0,top));}return r;
}
inline PolyTable polygon(const Rings&r){
 PolyTable result{};for(int column=0,sector=8;column<16;++column,sector=(sector-1)&15){
  int bottom=std::max(0,int(r[sector])),top=std::max(0,int(r[16+sector]));
  for(int i=0;i<8;++i)result[(3+i)*16+column]=bottom+((top-bottom)*i>>3);
  int opposite=std::max(0,int(r[sector^8]));for(int i=0;i<4;++i)result[(3-i)*16+column]=bottom+((opposite-bottom)*i>>4);
  opposite=std::max(0,int(r[16+(sector^8)]));for(int i=0;i<4;++i)result[(11+i)*16+column]=top+((opposite-top)*i>>4);
 }return result;
} inline constexpr int BRIGHTS[]{
            3, 8, 9, 10, 11, 12, 15, 16, 17, 18, 19, 21, 22, 23, 24, 25, 26, 27,
            29, 30, 31, 32, 33, 36, 37, 38, 39, 40, 45 };
 inline constexpr int BRIGHTS2[]{
            3, 12, 11, 10, 9, 8, 19, 18, 17, 16, 15, 27, 26, 25, 24, 23, 22, 21,
            33, 32, 31, 30, 29, 40, 39, 38, 37, 36, 45 };
 inline constexpr int XZ_ANGS[]{
            0, 23, 10, 20, 16, 16, 20, 10, 23, 0, 20, -10, 16, -16, 10, -20,
            0, -23, -10, -20, -16, -16, -20, -10, -23, 0, -20, 10, -16, 16, -10, 20 };
 inline constexpr int WILLYBRIGHT[]{
            30, 30, 30, 30, 30, 30, 30,
            30, 20, 20, 20, 20, 20, 30,
            30, 20, 6, 3, 6, 20, 30,
            30, 20, 6, 0, 6, 20, 30,
            30, 20, 6, 6, 6, 20, 30,
            30, 20, 20, 20, 20, 20, 30,
            30, 30, 30, 30, 30, 30, 30 };
 inline constexpr int MAP_TO_ANG[]{ 3, 2, 0, 1, 4, 5, 7, 6, 12, 13, 15, 14, 11, 10, 8, 9 };

inline int roughAngle(int x,int z){z=-z;int index=0;if(x<0){index+=8;x=-x;}if(z<0){index+=4;z=-z;}if(x<z){index+=2;std::swap(x,z);}if((x>>1)<z)++index;return MAP_TO_ANG[index&15];}
inline std::array<float,29> sprite(const Rings&r,int viewAngle,int bright,bool flip,const std::array<int8_t,1792>&guff){
 int strongestBottom=0,strongestTop=0,sumX=0,sumZ=0;
 for(int i=0;i<16;++i){int top=uint8_t(r[16+i]),bottom=uint8_t(r[i]);if(top!=128){int v=int16_t(48-top);if(int8_t(v)>int8_t(strongestTop))strongestTop=v&255;sumX+=int16_t(XZ_ANGS[i*2])*int16_t(v);sumZ+=int16_t(XZ_ANGS[i*2+1])*int16_t(v);}if(bottom!=128){int v=int16_t(48-bottom);if(int8_t(v)>=int8_t(strongestBottom))strongestBottom=v&255;sumX+=int16_t(XZ_ANGS[i*2])*int16_t(v);sumZ+=int16_t(XZ_ANGS[i*2+1])*int16_t(v);}}
 int vertical=7,strongest=strongestTop;if(strongestTop!=strongestBottom){strongest=std::max(strongestTop,strongestBottom);int numerator=uint16_t((strongestTop<<4)-1);vertical=uint16_t(divs(numerator,int16_t(strongestBottom+strongestTop)));}
 int ambient=int16_t(48-strongest),direction=((((-viewAngle+4096)&8191)>>9)-3+roughAngle(sumX,sumZ))&15;std::array<int,49> cells{};int k=0;
 for(int across=0;across<7;++across)for(int down=0;down<7;++down){int at=int16_t(vertical)*112+across*16+((direction+down)&15);int value=at>=0&&at<int(guff.size())?guff[at]:0;cells[k]=int8_t(value+ambient);int added=int16_t(bright+WILLYBRIGHT[k]);cells[k]=int16_t(cells[k]+std::max(0,added));++k;}
 std::array<float,29> levels{};for(int i=0;i<29;++i)levels[i]=std::clamp(cells[(flip?BRIGHTS2:BRIGHTS)[i]],0,31);return levels;
}

}
