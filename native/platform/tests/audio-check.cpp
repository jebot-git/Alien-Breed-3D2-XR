/* Include the production mixer to inspect exact PCM without exposing a debug
 * capture API or opening a real audio device. Queue checks use SDL dummy. */
#include "../audio.cpp"
#include <cassert>
#include <iostream>
using namespace ab3d2::audio;
static void clearFixture(){backend.channels={};CustomChips::audLC.fill(0);CustomChips::audLEN.fill(0);CustomChips::audPER.fill(0);CustomChips::audVOL.fill(0);CustomChips::dmaLC.fill(0);CustomChips::dmaLEN.fill(0);CustomChips::dmaTrig.fill(false);CustomChips::dmacon=0;}
static void channel(int ch,int value,int period=443){int at=10000+ch*1000;std::fill_n(Mem::RAM.data()+at,400,uint8_t(value));CustomChips::audLC[ch]=CustomChips::dmaLC[ch]=at;CustomChips::audLEN[ch]=CustomChips::dmaLEN[ch]=100;CustomChips::audVOL[ch]=64;CustomChips::audPER[ch]=period;CustomChips::dmaTrig[ch]=true;CustomChips::dmacon|=1<<ch;}
int main(){assert(!ensureStarted()&&!needsBuffer()&&!(SDL_WasInit(SDL_INIT_AUDIO)&SDL_INIT_AUDIO));clearFixture();channel(0,32);channel(1,-16);channel(2,-32);channel(3,16);auto memory=std::vector<uint8_t>(Mem::RAM.begin()+10000,Mem::RAM.begin()+14000);auto pcm=mixBlock(443);static_assert(pcm.size()==400);for(int i=0;i<200;++i){assert(pcm[i*2]==48*64&&pcm[i*2+1]==-48*64);}assert(std::equal(memory.begin(),memory.end(),Mem::RAM.begin()+10000));
 clearFixture();channel(0,0,886);for(int i=0;i<200;++i)Mem::RAM[10000+i]=i;pcm=mixBlock(443);for(int i=0;i<200;++i)assert(pcm[i*2]==int8_t(i/2)*64); // independent music period, no doubled playback
 clearFixture();channel(0,0);for(int i=0;i<4;++i)Mem::RAM[10000+i]=i+1;CustomChips::dmaLEN[0]=2;CustomChips::audLC[0]=10500;CustomChips::audLEN[0]=1;Mem::RAM[10500]=50;Mem::RAM[10501]=60;pcm=mixBlock(443);for(int i=0;i<4;++i)assert(pcm[i*2]==(i+1)*64);for(int i=4;i<200;++i)assert(pcm[i*2]==((i%2)?60:50)*64);CustomChips::dmacon=0;pcm=mixBlock(443);for(auto sample:pcm)assert(sample==0);
 clearFixture();channel(3,0);SDL_setenv("SDL_AUDIODRIVER","dummy",1);setEnabled(true);assert(ensureStarted());SDL_PauseAudioDevice(backend.device,1);auto before=stats();int guard=0;while(needsBuffer()&&guard++<8)queueFromPaula();auto queued=stats();assert(queued.active&&queued.referencePeriod==443&&queued.referenceRate==3546895/443);assert(queued.buffers-before.buffers==4);assert(queued.inputFrames-before.inputFrames==800);assert(queued.outputFrames-before.outputFrames==800);assert(queued.queuedBytes<=800*2*sizeof(int16_t)&&queued.queuedBytes>=600*2*sizeof(int16_t));assert(!queued.queueFailures);
 // Reset while parked must drop queued old-level PCM and reconstruct current
 // loop registers even after the original DMA trigger has been consumed.
 auto registers=CustomChips::audLC;assert(!CustomChips::dmaTrig[3]);ab3d2::audio::reset();assert(!stats().queuedBytes);assert(CustomChips::audLC==registers);assert(backend.channels[3].active&&backend.channels[3].position==0);ab3d2::audio::reset(false);assert(!backend.channels[3].active);ab3d2::audio::reset();queueFromPaula();assert(stats().queuedBytes>0);
 setEnabled(false);assert(!needsBuffer()&&!stats().queuedBytes);stop();assert(!stats().active);std::cout<<"PASS 200-frame original Paula blocks, signed stereo routing, independent periods, DMA latch/loop, silent default and exact SDL queued duration\n";
}
