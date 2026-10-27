#include "original.hpp"
#include <iostream>
static void require(bool result,const char* message){if(!result)throw std::runtime_error(message);}
int main(){try{
 require(M68k::negw(0x12340002)==int32_t(0x1234fffe),"neg.w lost its sign/cast ordering");
 require(M68k::negw(0x56788000)==int32_t(0x56788000),"neg.w overflow must preserve 16 bits");
 require(M68k::setw(0x1234abcd,0xfedc)==int32_t(0x1234fedc),"word write changed upper register");
 require(M68k::swap(int32_t(0x89abcdefu))==int32_t(0xcdef89abu),"swap register halves");
 require(M68k::muls(0xfffe,3)==-6,"signed word multiply");
 require(M68k::mulu(65535,65535)==int32_t(0xfffe0001u),"unsigned multiply wraps 32 bits");
 require(M68k::divs(7,3)==0x10002,"signed quotient/remainder packing");
 require(M68k::divs(-7,3)==-2,"signed negative quotient/remainder");
 require(M68k::divs(INT32_MIN,-1)==INT32_MIN,"division overflow must not trap host CPU");
 require(j_shl(1,32)==1 && j_shl(-1,31)==INT32_MIN,"32-bit shift masks/wrap");
 require(j_shr(int16_t(-1234),17)==-1 && j_ushr(int16_t(-1),16)==65535,"word operands promote before shifting");
 require(j_mod(INT32_MIN,-1)==0,"overflow remainder must not trap");
 bool trapped=false;try{M68k::divs(1,0);}catch(const std::runtime_error&){trapped=true;}require(trapped,"division by zero was not a native exception");
 Mem::wl(4096,int32_t(0x89abcdefu));require(Mem::ub(4096)==0x89 && Mem::l(4096)==int32_t(0x89abcdefu),"original RAM must remain big endian");
 std::string format="%04d %s";for(size_t i=0;i<=format.size();i++)Mem::wb(5000+i,i<format.size()?format[i]:0);
 Mem::ww(5100,-7);Mem::wl(5102,5200);Mem::wb(5200,'O');Mem::wb(5201,'K');Mem::wb(5202,0);
 std::string out;j_rawDoFmt(5000,5100,[&](int c){if(c)out+=char(c);});require(out=="-007 OK","original native text formatting");
 std::cout<<"PASS native 680x0 arithmetic, promotion, traps, RAM and formatter\n";return 0;
}catch(const std::exception& error){std::cerr<<error.what()<<"\n";return 1;}}
