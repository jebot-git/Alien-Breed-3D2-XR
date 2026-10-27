#include "original.hpp"
namespace Message {
bool Msg_Enabled(){
return (Mem::ub(ControlloopData::Prefs_ShowMessages_b) != 0);
}

bool Msg_SmallScreenNeedsRedraw(){
return ((Mem::ub(j_add(Message::msg_Buffer,Message::MB_redrawCount)) > 0) && (Mem::ub(j_add(Message::msg_Buffer,Message::MB_linesVis)) != 0));
}

int32_t msg_NextLineNumber(int32_t lineNumber){
if((Mem::ub(VidBss::Vid_FullScreen_b) != 0)) {
return (j_add(lineNumber,1) & Message::MSG_LINE_BUFFER_MASK);
}
return ((lineNumber < Message::MSG_MAX_LINES_SMALL)?j_add(lineNumber,1):0);
}

void msg_PushLineRaw(int32_t textPtr,int32_t lengthAndTag){
int32_t lineNumber=Message::msg_NextLineNumber(Mem::w(j_add(Message::msg_Buffer,Message::MB_lineNumber)));
Mem::wl(j_add(j_add(Message::msg_Buffer,Message::MB_lineTextPtrs),(lineNumber * 4)),textPtr);
Mem::ww(j_add(j_add(Message::msg_Buffer,Message::MB_lineLengths),(lineNumber * 2)),lengthAndTag);
Mem::ww(j_add(Message::msg_Buffer,Message::MB_lineNumber),lineNumber);
if((textPtr != 0)) {
Mem::wb(j_add(Message::msg_Buffer,Message::MB_linesVis),1);
}
}

void Msg_Init(){
Sys::Sys_MemFillLong(Message::msg_Buffer,0,j_div(Message::MSG_BUFFER_SIZEOF,4));
Mem::ww(j_add(Message::msg_Buffer,Message::MB_lineNumber),(Message::MSG_LINE_BUFFER_SIZE - 1));
Mem::wb(j_add(Message::msg_Buffer,Message::MB_redrawCount),1);
Mem::ww(j_add(Message::msg_Buffer,Message::MB_guaranteedFitFull),(j_div(Message::SCREEN_WIDTH,Message::MAX_PROP_CHAR_WIDTH) - 2));
Mem::ww(j_add(Message::msg_Buffer,Message::MB_guaranteedFitSmall),(j_div((Message::SCREEN_WIDTH - (Message::HUD_BORDER_WIDTH * 2)),Message::MAX_PROP_CHAR_WIDTH) - 2));
Mem::wl(j_add(Message::msg_Buffer,Message::MB_tickPeriod),j_div((SystemC::Sys_EClockRate * Message::MSG_SCROLL_PERIOD_MS),1000));
Mem::wl(j_add(Message::msg_Buffer,Message::MB_deduplicationPeriod),j_div((SystemC::Sys_EClockRate * Message::MSG_DEDUPLICATION_PERIOD_MS),1000));
int32_t levelTextPtr=Mem::l(LevelBss::Lvl_DataPtr_l);
if((levelTextPtr != 0)) {
for(int32_t i=0;(i < Message::MSG_MAX_CUSTOM);++(i),(levelTextPtr+=Message::MSG_MAX_LENGTH)){
if((DrawC::Draw_IsPrintable(Mem::ub((j_add(levelTextPtr,Message::MSG_SINGLE_LINE_LENGTH) - 1))) && DrawC::Draw_IsPrintable(Mem::ub(j_add(levelTextPtr,Message::MSG_SINGLE_LINE_LENGTH))))) {
Message::msg_NudgeString(j_add(levelTextPtr,Message::MSG_SINGLE_LINE_LENGTH),(Message::MSG_SINGLE_LINE_LENGTH - 1));
}
Message::msg_CompactString(levelTextPtr,Message::MSG_MAX_LENGTH);
}
}
}

void Msg_PushLine(int32_t textPtr,int32_t lengthAndTag){
if((Mem::ub(ControlloopData::Prefs_ShowMessages_b) == 0)) {
return ;
}
int32_t textLength=(lengthAndTag & Message::MSG_LENGTH_MASK);
int32_t maxFit=((Mem::ub(VidBss::Vid_FullScreen_b) != 0)?Mem::uw(j_add(Message::msg_Buffer,Message::MB_guaranteedFitFull)):Mem::uw(j_add(Message::msg_Buffer,Message::MB_guaranteedFitSmall)));
Mem::wb(j_add(Message::msg_Buffer,Message::MB_redrawCount),1);
if((textLength <= maxFit)) {
Message::msg_PushLineRaw(textPtr,lengthAndTag);
}
else {
std::vector<int32_t> nextTextPtr={textPtr};
int32_t lines=Message::MSG_MAX_LINES_SMALL;
int32_t textTag=(lengthAndTag & ~(Message::MSG_LENGTH_MASK));
(maxFit=((Mem::ub(VidBss::Vid_FullScreen_b) != 0)?(Message::SCREEN_WIDTH - (2 * Message::DRAW_MSG_CHAR_W)):(Message::SCREEN_WIDTH - (2 * j_add(Message::HUD_BORDER_WIDTH,Message::DRAW_MSG_CHAR_W)))));
do {
int32_t fitLength=DrawC::Draw_CalcPropTextSplit(nextTextPtr,textLength,maxFit);
Message::msg_PushLineRaw(textPtr,(fitLength | textTag));
(textPtr=nextTextPtr[0]);
(textLength-=fitLength);
}
while(((nextTextPtr[0] != 0) && ((lines)-- != 0)));
}
Mem::wl(j_add(Message::msg_Buffer,Message::MB_lastMessagePtr),0);
}

void Msg_PushLineDedupLast(int32_t textPtr,int32_t lengthAndTag){
if(((Mem::ub(ControlloopData::Prefs_ShowMessages_b) != 0) && ((textPtr != Mem::l(j_add(Message::msg_Buffer,Message::MB_lastMessagePtr))) || SystemC::Sys_CheckTimeGE(SystemBss::Sys_FrameTimeECV_q,j_add(Message::msg_Buffer,Message::MB_nextDuplicateTickECV))))) {
Mem::wl(j_add(Message::msg_Buffer,Message::MB_nextDuplicateTickECV),Mem::l(SystemBss::Sys_FrameTimeECV_q));
Mem::wl(j_add(j_add(Message::msg_Buffer,Message::MB_nextDuplicateTickECV),4),Mem::l(j_add(SystemBss::Sys_FrameTimeECV_q,4)));
SystemC::Sys_AddTime(j_add(Message::msg_Buffer,Message::MB_nextDuplicateTickECV),Mem::l(j_add(Message::msg_Buffer,Message::MB_deduplicationPeriod)));
Message::Msg_PushLine(textPtr,lengthAndTag);
Mem::wl(j_add(Message::msg_Buffer,Message::MB_lastMessagePtr),textPtr);
Mem::wb(j_add(Message::msg_Buffer,Message::MB_redrawCount),1);
}
}

void Msg_PullLast(){
}

void Msg_Tick(){
if(SystemC::Sys_CheckTimeGE(SystemBss::Sys_FrameTimeECV_q,j_add(Message::msg_Buffer,Message::MB_nextTickECV))) {
Mem::wl(j_add(Message::msg_Buffer,Message::MB_nextTickECV),Mem::l(SystemBss::Sys_FrameTimeECV_q));
Mem::wl(j_add(j_add(Message::msg_Buffer,Message::MB_nextTickECV),4),Mem::l(j_add(SystemBss::Sys_FrameTimeECV_q,4)));
SystemC::Sys_AddTime(j_add(Message::msg_Buffer,Message::MB_nextTickECV),Mem::l(j_add(Message::msg_Buffer,Message::MB_tickPeriod)));
Message::msg_PushLineRaw(0,0);
Mem::wb(j_add(Message::msg_Buffer,Message::MB_redrawCount),1);
}
}

void Msg_RenderFullsccreenBuffer(){
int32_t lastLine=Message::msg_NextLineNumber(Mem::w(j_add(Message::msg_Buffer,Message::MB_lineNumber)));
int32_t nextLine=lastLine;
int32_t yPos=(j_add(Mem::w(VidBss::Vid_LetterBoxMarginHeight_w),Message::DRAW_TEXT_MARGIN) & 0xFFFF);
do {
if((Mem::l(j_add(j_add(Message::msg_Buffer,Message::MB_lineTextPtrs),(nextLine * 4))) != 0)) {
int32_t len=Mem::uw(j_add(j_add(Message::msg_Buffer,Message::MB_lineLengths),(nextLine * 2)));
DrawC::Draw_ChunkyTextProp(Mem::l(VidBss::Vid_FastBufferPtr_l),Message::SCREEN_WIDTH,(len & Message::MSG_LENGTH_MASK),Mem::l(j_add(j_add(Message::msg_Buffer,Message::MB_lineTextPtrs),(nextLine * 4))),Message::DRAW_TEXT_MARGIN,yPos,Message::msg_TagPens[j_shr(len,Message::MSG_TAG_SHIFT)]);
(yPos=(j_add(j_add(yPos,Message::DRAW_MSG_CHAR_H),Message::DRAW_TEXT_Y_SPACING) & 0xFFFF));
}
(nextLine=Message::msg_NextLineNumber(nextLine));
}
while((nextLine != lastLine));
}

void Msg_RenderFullscreenRTG(int32_t bmBaseAddr,int32_t bmBytesPerRow){
int32_t lastLine=Message::msg_NextLineNumber(Mem::w(j_add(Message::msg_Buffer,Message::MB_lineNumber)));
int32_t nextLine=lastLine;
int32_t yPos=(j_add(Mem::w(VidBss::Vid_LetterBoxMarginHeight_w),Message::DRAW_TEXT_MARGIN) & 0xFFFF);
do {
if((Mem::l(j_add(j_add(Message::msg_Buffer,Message::MB_lineTextPtrs),(nextLine * 4))) != 0)) {
int32_t len=Mem::uw(j_add(j_add(Message::msg_Buffer,Message::MB_lineLengths),(nextLine * 2)));
DrawC::Draw_ChunkyTextProp(bmBaseAddr,bmBytesPerRow,(len & Message::MSG_LENGTH_MASK),Mem::l(j_add(j_add(Message::msg_Buffer,Message::MB_lineTextPtrs),(nextLine * 4))),Message::DRAW_TEXT_MARGIN,yPos,Message::msg_TagPens[j_shr(len,Message::MSG_TAG_SHIFT)]);
(yPos=(j_add(j_add(yPos,Message::DRAW_MSG_CHAR_H),Message::DRAW_TEXT_Y_SPACING) & 0xFFFF));
}
(nextLine=Message::msg_NextLineNumber(nextLine));
}
while((nextLine != lastLine));
}

void Msg_RenderSmallScreenRTG(int32_t bmBaseAddr,int32_t bmBytesPerRow){
int32_t lastLine=Message::msg_NextLineNumber(Mem::w(j_add(Message::msg_Buffer,Message::MB_lineNumber)));
int32_t nextLine=lastLine;
int32_t yPos=(j_add(j_add(Message::SMALL_HEIGHT,Mem::w(VidData::SMALL_YPOS)),Message::DRAW_TEXT_MARGIN) & 0xFFFF);
Mem::wb(j_add(Message::msg_Buffer,Message::MB_linesVis),0);
DrawC::Draw_ClearRect(Message::HUD_BORDER_WIDTH,yPos,((Message::SCREEN_WIDTH - Message::HUD_BORDER_WIDTH) - 1),((Mem::w(VidBss::Vid_ScreenHeight) - Message::HUD_BORDER_WIDTH) - 8));
do {
if((Mem::l(j_add(j_add(Message::msg_Buffer,Message::MB_lineTextPtrs),(nextLine * 4))) != 0)) {
int32_t len=Mem::uw(j_add(j_add(Message::msg_Buffer,Message::MB_lineLengths),(nextLine * 2)));
DrawC::Draw_ChunkyTextProp(bmBaseAddr,bmBytesPerRow,(len & Message::MSG_LENGTH_MASK),Mem::l(j_add(j_add(Message::msg_Buffer,Message::MB_lineTextPtrs),(nextLine * 4))),j_add(Message::DRAW_TEXT_MARGIN,Message::HUD_BORDER_WIDTH),yPos,Message::msg_TagPens[j_shr(len,Message::MSG_TAG_SHIFT)]);
(yPos=(j_add(j_add(yPos,Message::DRAW_MSG_CHAR_H),Message::DRAW_TEXT_Y_SPACING) & 0xFFFF));
Mem::wb(j_add(Message::msg_Buffer,Message::MB_linesVis),(j_add(Mem::ub(j_add(Message::msg_Buffer,Message::MB_linesVis)),1) & 0xFF));
}
(nextLine=Message::msg_NextLineNumber(nextLine));
}
while((nextLine != lastLine));
Mem::wb(j_add(Message::msg_Buffer,Message::MB_redrawCount),((Mem::ub(j_add(Message::msg_Buffer,Message::MB_redrawCount)) - 1) & 0xFF));
}

void Msg_RenderSmallScreenPlanar(int32_t plane){
int32_t lastLine=Message::msg_NextLineNumber(Mem::w(j_add(Message::msg_Buffer,Message::MB_lineNumber)));
int32_t nextLine=lastLine;
int32_t yPos=0;
Mem::wb(j_add(Message::msg_Buffer,Message::MB_linesVis),0);
Sys::Sys_MemFillLong(plane,0,(Message::SCREEN_WIDTH * 4));
do {
if((Mem::l(j_add(j_add(Message::msg_Buffer,Message::MB_lineTextPtrs),(nextLine * 4))) != 0)) {
int32_t len=Mem::uw(j_add(j_add(Message::msg_Buffer,Message::MB_lineLengths),(nextLine * 2)));
DrawC::Draw_PlanarTextProp(plane,(len & Message::MSG_LENGTH_MASK),Mem::l(j_add(j_add(Message::msg_Buffer,Message::MB_lineTextPtrs),(nextLine * 4))),j_add(Message::DRAW_TEXT_MARGIN,Message::HUD_BORDER_WIDTH),yPos);
(yPos=(j_add(j_add(yPos,Message::DRAW_MSG_CHAR_H),Message::DRAW_TEXT_Y_SPACING) & 0xFFFF));
Mem::wb(j_add(Message::msg_Buffer,Message::MB_linesVis),(j_add(Mem::ub(j_add(Message::msg_Buffer,Message::MB_linesVis)),1) & 0xFF));
}
(nextLine=Message::msg_NextLineNumber(nextLine));
}
while((nextLine != lastLine));
Mem::wb(j_add(Message::msg_Buffer,Message::MB_redrawCount),((Mem::ub(j_add(Message::msg_Buffer,Message::MB_redrawCount)) - 1) & 0xFF));
}

void msg_NudgeString(int32_t bufferPtr,int32_t bufferLen){
int32_t toPtr=j_add(bufferPtr,bufferLen);
int32_t fromPtr=(toPtr - 1);
while((fromPtr > bufferPtr)){
--(toPtr);
--(fromPtr);
Mem::wb(toPtr,Mem::ub(fromPtr));
}
Mem::wb(bufferPtr,' ');
}

int32_t msg_CompactString(int32_t bufferPtr,int32_t bufferLen){
int32_t readPtr=bufferPtr;
int32_t writePtr=bufferPtr;
int32_t lastPtr=j_add(bufferPtr,bufferLen);
bool skip=true;
int32_t n=(bufferLen & 0xFFFF);
while(((n)-- != 0)){
int32_t charCode=Mem::ub(readPtr);
(readPtr)++;
if(DrawC::Draw_IsPrintable(charCode)) {
(skip=false);
}
else if(!(skip)) {
(skip=true);
}
else {
continue;
}
Mem::wb(writePtr,charCode);
(writePtr)++;
}
if(skip) {
--(writePtr);
}
if((writePtr < lastPtr)) {
Mem::wb(writePtr,0);
}
return ((writePtr - bufferPtr) & 0xFFFF);
}

}