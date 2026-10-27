#pragma once
#include <algorithm>
#include <array>
#include <atomic>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <functional>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <vector>
#include <map>
#include <set>
#include <fstream>
#include <sstream>
#include <thread>
struct DisplayHandle {bool shouldClose(){return false;}};
template<class R=int32_t> R j_unported(const std::string& name){throw std::runtime_error("Native service not migrated: "+name);}
template<class A,class B> constexpr auto j_min(A a,B b){using C=std::common_type_t<A,B>;return std::min(C(a),C(b));}
template<class A,class B> constexpr auto j_max(A a,B b){using C=std::common_type_t<A,B>;return std::max(C(a),C(b));}
template<class T> constexpr T j_abs(T a){return a<0?-a:a;}
inline std::string j_string(const std::string& v){return v;}
inline std::string j_string(const char* v){return v?v:"null";}
inline std::string j_string(const std::exception& v){return v.what();}
template<class T> requires (!std::is_base_of_v<std::exception,T>) std::string j_string(T v){if constexpr(requires {v.toString();})return v.toString();else return std::to_string(v);}
template<class A,class B> constexpr auto j_add(A a,B b){if constexpr(std::is_convertible_v<A,std::string>||std::is_convertible_v<B,std::string>)return j_string(a)+j_string(b);else return a+b;}
template<class T> using JPromote=std::conditional_t<std::is_integral_v<T> && (sizeof(T)<4),int32_t,T>;
template<class A,class B> constexpr auto j_shl(A a,B b){using P=JPromote<A>;using U=std::make_unsigned_t<P>;return P(U(P(a))<<(b&(sizeof(P)*8-1)));}
template<class A,class B> constexpr auto j_shr(A a,B b){using P=JPromote<A>;return P(a)>>(b&(sizeof(P)*8-1));}
template<class A,class B> constexpr auto j_ushr(A a,B b){using P=JPromote<A>;using U=std::make_unsigned_t<P>;return P(U(P(a))>>(b&(sizeof(P)*8-1)));}
template<class A,class B> constexpr auto j_div(A a,B b){
 using P=std::common_type_t<JPromote<A>,JPromote<B>>;P x=a,y=b;
 if constexpr(std::is_integral_v<P>){if(y==0)throw std::runtime_error("Original integer division by zero");if(x==std::numeric_limits<P>::min()&&y==-1)return x;}
 return P(x/y);
}
template<class A,class B> constexpr auto j_mod(A a,B b){
 using P=std::common_type_t<JPromote<A>,JPromote<B>>;P x=a,y=b;
 if constexpr(std::is_integral_v<P>){if(y==0)throw std::runtime_error("Original integer remainder by zero");if(x==std::numeric_limits<P>::min()&&y==-1)return P(0);return P(x%y);}else return std::fmod(x,y);
}
template<class... Args> int32_t j_log(Args&&...){return 0;}
inline const char* j_property(const std::string& name){return nullptr;}
inline const char* j_property(const std::string& name,const char* fallback){return fallback;}
inline int64_t j_nanoTime(){return std::chrono::steady_clock::now().time_since_epoch().count();}
inline int64_t j_currentTimeMillis(){return j_nanoTime()/1000000;}
struct ThreadHandle {void interrupt(){};};inline ThreadHandle j_thread(){return {};}
template<class T,class V> void j_fill(T& a,V v){std::fill(a.begin(),a.end(),v);}
template<class T,class V> void j_fill(T& a,int begin,int end,V v){std::fill(a.begin()+begin,a.begin()+end,v);}
template<class T,class U> void j_arraycopy(const T& a,int source,U& b,int target,int size){std::memmove(b.data()+target,a.data()+source,size*sizeof(a[0]));}
namespace Mem {
inline constexpr int RAM_SIZE=64<<20;
inline std::vector<uint8_t> RAM(RAM_SIZE);
inline int32_t cursor=4096;
inline void check(int32_t address,int size=1){if(address<0 || int64_t(address)+size>RAM_SIZE)throw std::out_of_range("Original RAM address "+std::to_string(address));}
inline int32_t ub(int32_t p){check(p);return RAM[p];}
inline int32_t b(int32_t p){return int8_t(ub(p));}
inline int32_t uw(int32_t p){check(p,2);return (RAM[p]<<8)|RAM[p+1];}
inline int32_t w(int32_t p){return int16_t(uw(p));}
inline int32_t l(int32_t p){check(p,4);return int32_t((uint32_t(uw(p))<<16)|uw(p+2));}
inline void wb(int32_t p,int32_t value){check(p);RAM[p]=uint8_t(value);}
inline void ww(int32_t p,int32_t value){check(p,2);RAM[p]=uint8_t(uint32_t(value)>>8);RAM[p+1]=uint8_t(value);}
inline void wl(int32_t p,int32_t value){ww(p,uint32_t(value)>>16);ww(p+2,value);}
inline int32_t align(int32_t alignment){return cursor=(cursor+alignment-1)&-alignment;}
inline int32_t alloc(int32_t size){int32_t p=cursor;check(p,size);cursor+=size;return p;}
inline int32_t allocAligned(int32_t size,int32_t alignment){align(alignment);return alloc(size);}
inline int32_t allocTop(){return cursor;}
}
template<class A,class B> bool j_equals(A a,B b){if constexpr(std::is_pointer_v<A>&&std::is_pointer_v<B>){return a&&b&&std::strcmp(a,b)==0;}else return a==b;}
namespace DosLib {
inline constexpr int MODE_OLDFILE=1005,MODE_READWRITE=1004;
inline int Open(int,int){return 0;}
inline int Read(int,int,int){return -1;}
inline int Write(int,int,int){return -1;}
inline void Close(int){}
}
namespace CustomChips {
inline std::array<int32_t,4> audLC{},audLEN{},audPER{},audVOL{},dmaLC{},dmaLEN{};
inline std::array<bool,4> dmaTrig{};
inline int32_t dmacon=0,ciaaPra=255,joy0dat=0,joy1dat=0;
inline bool mouseLeftPressed=false,mouseRightPressed=false,fire1Pressed=false;
inline bool ciaaPraBit6(){return !mouseLeftPressed;}inline bool ciaaPraBit7(){return !mouseRightPressed;}inline bool potinpBit2(){return true;}
inline void ciaAnd(int mask){ciaaPra&=mask;}inline void ciaOr(int mask){ciaaPra|=mask;}
inline void ciaBset(int bit){ciaaPra|=1<<bit;}inline void ciaBchg(int bit){ciaaPra^=1<<bit;}inline void ciaBclr(int bit){ciaaPra&=~(1<<bit);}
inline void write16(int address,int value){
 value&=65535;
 if(address==0xdff096){if(value&0x8000){for(int ch=0;ch<4;ch++)if((value&(1<<ch))&&!(dmacon&(1<<ch))){dmaLC[ch]=audLC[ch];dmaLEN[ch]=audLEN[ch];dmaTrig[ch]=true;}dmacon|=value&32767;}else dmacon&=~value;return;}
 int off=address-0xdff0a0;if(off<0||off>=64)return;int ch=off>>4;
 switch(off&15){case 0:audLC[ch]=(audLC[ch]&65535)|(value<<16);break;case 2:audLC[ch]=(audLC[ch]&int32_t(0xffff0000u))|value;break;case 4:audLEN[ch]=value;break;case 6:audPER[ch]=value;break;case 8:audVOL[ch]=value;break;}
}
inline void write32(int address,int value){write16(address,uint32_t(value)>>16);write16(address+2,value);}
}

struct JStringBuilder {
 std::string value;
 template<class T> JStringBuilder& append(T v){value+=j_string(v);return *this;}
 std::string toString()const{return value;}
};

namespace Mem {inline void copy(int source,int destination,int size){check(source,size);check(destination,size);std::memmove(RAM.data()+destination,RAM.data()+source,size);}}
namespace IntuitionLib {inline constexpr int RECOVERY_ALERT=0;}
// Native equivalent of exec.library RawDoFmt for original text/statistics paths.
inline void j_rawDoFmt(int32_t format,int32_t arguments,const std::function<void(int32_t)>& sink){
 auto next=[&](){return Mem::ub(format++);};
 for(int c;(c=next())!=0;){
  if(c!='%'){sink(c);continue;}c=next();if(c=='%'){sink('%');continue;}
  bool left=false,zero=false;if(c=='-'){left=true;c=next();}if(c=='0'){zero=true;c=next();}
  int width=0;while(c>='0'&&c<='9'){width=std::min(1024,width*10+c-'0');c=next();}
  bool lng=c=='l';if(lng)c=next();
  std::string value;
  if(c=='s'){
   int p=Mem::l(arguments);arguments+=4;
   if(p)for(int guard=0;guard<65536 && Mem::ub(p);guard++,p++)value+=char(Mem::ub(p));
  }else{
   uint32_t v=lng?uint32_t(Mem::l(arguments)):uint32_t(Mem::uw(arguments));arguments+=lng?4:2;
   if(c=='c')value=char(v&255);
   else if(c=='d')value=std::to_string(lng?int32_t(v):int32_t(int16_t(v)));
   else if(c=='u')value=std::to_string(v);
   else if(c=='x'||c=='X'){std::ostringstream s;if(c=='X')s<<std::uppercase;s<<std::hex<<v;value=s.str();}
   else {sink(c);continue;}
  }
  int padding=std::max(0,width-int(value.size()));
  if(!left){if(zero && !value.empty()&&value[0]=='-'){sink('-');value.erase(0,1);}while(padding-->0)sink(zero?'0':' ');}
  for(unsigned char ch:value)sink(ch);
  if(left)while(padding-->0)sink(' ');
 }
 sink(0);
}
