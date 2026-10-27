#include "original.hpp"
namespace DrawC {
bool Draw_IsPrintable(int32_t charCode){
(charCode&=0xFF);
return (((charCode > 0x20) && (charCode < 0x7F)) || (charCode > 0xA0));
}

int32_t Draw_CalcPropTextSplit(std::vector<int32_t>& nextTextPtr,int32_t txtLength,int32_t fitWidth){
if(((txtLength * DrawC::DRAW_MSG_CHAR_W) <= fitWidth)) {
(nextTextPtr[0]=0);
return txtLength;
}
int32_t textPtr=nextTextPtr[0];
int32_t lastNonPrintingPtr=0;
int32_t width=0;
int32_t charsLeft=txtLength;
int32_t charCode=0;
while((((charsLeft != 0) && (width < fitWidth)) && ((charCode=Mem::ub(textPtr)) != 0))){
if(!(DrawC::Draw_IsPrintable(charCode))) {
(lastNonPrintingPtr=textPtr);
}
(width+=j_shr(Mem::ub(j_add(DrawData::draw_GlyphSpacing_vb,charCode)),4));
--(charsLeft);
++(textPtr);
}
if((width > fitWidth)) {
--(textPtr);
(charCode=Mem::ub(textPtr));
++(charsLeft);
}
if((((lastNonPrintingPtr != 0) && (charsLeft > 1)) && DrawC::Draw_IsPrintable(charCode))) {
(textPtr=j_add(lastNonPrintingPtr,1));
}
(width=((textPtr - nextTextPtr[0]) & 0xFFFF));
if(((charCode == 0) || (charsLeft == 0))) {
(textPtr=0);
}
if((textPtr != 0)) {
while(((charsLeft > 0) && !(DrawC::Draw_IsPrintable(Mem::ub(textPtr))))){
++(textPtr);
--(charsLeft);
}
}
(nextTextPtr[0]=textPtr);
return width;
}

}