#include "audio.hpp"
#include "original.hpp"
#include <SDL.h>
#include <array>
#include <atomic>
#include <cmath>
#include <mutex>
#include <vector>
namespace ab3d2::audio {
namespace {
constexpr int SamplesPerBuffer=200,TargetQueued=4,PalClock=3546895;
struct Channel {int address=0,length=0;double position=0;bool active=false;};
struct Backend {
 std::mutex mutex;std::atomic<bool> enabled{false};SDL_AudioDeviceID device=0;SDL_AudioSpec obtained{};SDL_AudioStream*stream=nullptr;
 bool attempted=false,ownsSubsystem=false;int streamRate=0;std::array<Channel,4> channels{};Stats counters;
} backend;
int referencePeriod(){int period=CustomChips::audPER[3]>0?CustomChips::audPER[3]:CustomChips::audPER[1]>0?CustomChips::audPER[1]:443;return std::max(1,period);}
int referenceRate(int period){return std::clamp(PalClock/period,1000,48000);}
void consumeTriggers(){for(int ch=0;ch<4;++ch){auto&channel=backend.channels[ch];if(CustomChips::dmaTrig[ch]){channel.address=CustomChips::dmaLC[ch];channel.length=CustomChips::dmaLEN[ch];channel.position=0;channel.active=true;CustomChips::dmaTrig[ch]=false;++backend.counters.dmaTriggers;}if(!(CustomChips::dmacon&(1<<ch)))channel.active=false;}}
int sample(int ch,int refPeriod){auto&channel=backend.channels[ch];int volume=std::clamp(CustomChips::audVOL[ch],0,64),period=CustomChips::audPER[ch];if(!channel.active||volume==0||period<=0||channel.address<=0)return 0;
 int bytes=channel.length*2,index=int(channel.position);if(bytes<2||index>=bytes){channel.address=CustomChips::audLC[ch];channel.length=CustomChips::audLEN[ch];channel.position=0;index=0;bytes=channel.length*2;if(bytes<2||channel.address<=0)return 0;}
 int64_t at=int64_t(channel.address)+index;if(at<0||at>=Mem::RAM_SIZE)return 0;int value=int8_t(Mem::RAM[at]);channel.position+=double(refPeriod)/period;return value*volume/64;
}
std::array<int16_t,SamplesPerBuffer*2> mixBlock(int refPeriod){consumeTriggers();std::array<int16_t,SamplesPerBuffer*2> pcm{};for(int i=0;i<SamplesPerBuffer;++i){int left=(sample(0,refPeriod)+sample(3,refPeriod))*64,right=(sample(1,refPeriod)+sample(2,refPeriod))*64;pcm[i*2]=std::clamp(left,-32768,32767);pcm[i*2+1]=std::clamp(right,-32768,32767);backend.counters.peak=std::max({backend.counters.peak,std::abs(int(pcm[i*2])),std::abs(int(pcm[i*2+1]))});}return pcm;}
void closeDevice(){if(backend.stream)SDL_FreeAudioStream(backend.stream);backend.stream=nullptr;backend.streamRate=0;if(backend.device){SDL_ClearQueuedAudio(backend.device);SDL_CloseAudioDevice(backend.device);}backend.device=0;backend.attempted=false;if(backend.ownsSubsystem)SDL_QuitSubSystem(SDL_INIT_AUDIO);backend.ownsSubsystem=false;}
}
void setEnabled(bool enabled){backend.enabled.store(enabled);if(!enabled){std::lock_guard lock(backend.mutex);if(backend.device)SDL_ClearQueuedAudio(backend.device);}}
bool ensureStarted(){if(!backend.enabled.load())return false;std::lock_guard lock(backend.mutex);if(backend.device)return true;if(backend.attempted)return false;backend.attempted=true;
 if(!(SDL_WasInit(SDL_INIT_AUDIO)&SDL_INIT_AUDIO)){if(SDL_InitSubSystem(SDL_INIT_AUDIO)!=0)return false;backend.ownsSubsystem=true;}
 SDL_AudioSpec desired{};desired.freq=referenceRate(referencePeriod());desired.format=AUDIO_S16SYS;desired.channels=2;desired.samples=128;desired.callback=nullptr;
 backend.device=SDL_OpenAudioDevice(nullptr,0,&desired,&backend.obtained,0);if(!backend.device)backend.device=SDL_OpenAudioDevice(nullptr,0,&desired,&backend.obtained,SDL_AUDIO_ALLOW_FREQUENCY_CHANGE);if(!backend.device)return false;
 backend.counters.deviceRate=backend.obtained.freq;SDL_PauseAudioDevice(backend.device,0);return true;
}
bool needsBuffer(){if(!backend.enabled.load())return false;std::lock_guard lock(backend.mutex);if(!backend.device)return false;
 int period=referencePeriod(),rate=referenceRate(period);unsigned bytesPerFrame=backend.obtained.channels*(SDL_AUDIO_BITSIZE(backend.obtained.format)/8);unsigned oneBuffer=unsigned(std::ceil(double(SamplesPerBuffer)*backend.obtained.freq/rate))*bytesPerFrame;
 // Original OpenAL waits until a complete source buffer was consumed. This
 // threshold similarly refills from three remaining blocks back to four.
 return SDL_GetQueuedAudioSize(backend.device)<=oneBuffer*(TargetQueued-1);
}
void queueFromPaula(){if(!backend.enabled.load())return;std::lock_guard lock(backend.mutex);if(!backend.device)return;int period=referencePeriod(),rate=referenceRate(period);
 auto pcm=mixBlock(period);backend.counters.referencePeriod=period;backend.counters.referenceRate=rate;++backend.counters.buffers;backend.counters.inputFrames+=SamplesPerBuffer;
 // Keep each original 200-frame block intact at the normal Paula rate. SDL
 // handles hardware conversion internally; a stream is needed only if the
 // device interface rate differs or the original SFX period changes.
 if(rate==backend.obtained.freq&&backend.obtained.format==AUDIO_S16SYS&&backend.obtained.channels==2){if(SDL_QueueAudio(backend.device,pcm.data(),sizeof(pcm))!=0)++backend.counters.queueFailures;else backend.counters.outputFrames+=SamplesPerBuffer;return;}
 if(!backend.stream||backend.streamRate!=rate){if(backend.stream)SDL_FreeAudioStream(backend.stream);backend.stream=SDL_NewAudioStream(AUDIO_S16SYS,2,rate,backend.obtained.format,backend.obtained.channels,backend.obtained.freq);backend.streamRate=rate;if(!backend.stream){++backend.counters.queueFailures;return;}}
 if(SDL_AudioStreamPut(backend.stream,pcm.data(),sizeof(pcm))<0){++backend.counters.queueFailures;return;}
 for(int available;(available=SDL_AudioStreamAvailable(backend.stream))>0;){std::vector<unsigned char> converted(available);int bytes=SDL_AudioStreamGet(backend.stream,converted.data(),available);if(bytes<=0)break;if(SDL_QueueAudio(backend.device,converted.data(),bytes)!=0){++backend.counters.queueFailures;break;}backend.counters.outputFrames+=bytes/(backend.obtained.channels*(SDL_AUDIO_BITSIZE(backend.obtained.format)/8));}
}
void stop(){std::lock_guard lock(backend.mutex);closeDevice();}
Stats stats(){std::lock_guard lock(backend.mutex);auto result=backend.counters;result.enabled=backend.enabled.load();result.active=backend.device!=0;result.queuedBytes=backend.device?SDL_GetQueuedAudioSize(backend.device):0;return result;}
}
