/* Exercise the native renderer after actual original gameplay initializes
 * graphics dimensions/frames. Zero-size sleeping records must stay hidden. */
#include "render.hpp"
#include "gpu.hpp"
#include "original.hpp"
#include <SDL.h>
#include <iostream>
int main(int argc,char**argv){try{
 if(argc!=5)throw std::runtime_error("assets fixture-directory level-index capture.ppm");int level=std::stoi(argv[3]);std::ifstream file(std::filesystem::path(argv[2])/("level-"+std::to_string(level)+".ram"),std::ios::binary);file.read(reinterpret_cast<char*>(Mem::RAM.data()),Mem::RAM_SIZE);Mem::cursor=file.gcount();if(!Mem::cursor)throw std::runtime_error("Missing original RAM fixture");
 SDL_Init(SDL_INIT_VIDEO);SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION,3);SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION,3);SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,SDL_GL_CONTEXT_PROFILE_CORE);auto*w=SDL_CreateWindow("Original animated actor GPU check",0,0,960,640,SDL_WINDOW_OPENGL|SDL_WINDOW_HIDDEN);if(!w)throw std::runtime_error(SDL_GetError());auto context=SDL_GL_CreateContext(w);glewExperimental=GL_TRUE;auto result=glewInit();if(result!=GLEW_OK&&!GLEW_VERSION_3_3)throw std::runtime_error("GL3.3 unavailable");while(glGetError()){}
 {ab3d2::Renderer renderer;renderer.loadAssets(argv[1]);renderer.loadLevel(level);renderer.sync();auto initialActors=renderer.stats().entities;Hires::headless=true;Hires::headlessStop=false;Hires::loopFrameLimit=80;int frame=0;
 auto key=[](int binding,bool value){Mem::wb(TablesBss::KeyMap_vb+Mem::ub(binding),value?255:0);};key(ControlloopData::forward_key,true);key(ControlloopData::fire_key,false);Hires::markVisibleAndWorry();
 Hires::frameSync=[&](){++frame;if(frame==80){auto parked=std::vector<uint8_t>(Mem::RAM.begin(),Mem::RAM.begin()+Mem::cursor);renderer.sync();
 float x=Mem::l(PlayerBss::Plr1_XOff_l)/65536.f/64,y=-Mem::l(PlayerBss::Plr1_YOff_l)/8192.f,z=-Mem::l(PlayerBss::Plr1_ZOff_l)/65536.f/64,yaw=-Mem::uw(PlayerBss::Plr1_AngPos_w)*6.28318530718f/8192;ab3d2::RenderView view;view.headWorld=ab3d2::gpu::transform(x,y,z,yaw);view.camera={x,y,z};float f=1/std::tan(80*3.14159265f/360),n=.03f,far=300;ab3d2::Matrix projection{f/1.5f,0,0,0,0,f,0,0,0,0,(far+n)/(n-far),-1,0,0,2*far*n/(n-far),0};view.viewProjection=ab3d2::gpu::multiply(projection,ab3d2::gpu::multiply(ab3d2::gpu::transform(0,0,0,-yaw),ab3d2::gpu::transform(-x,-y,-z)));
 glViewport(0,0,960,640);glClearColor(0,0,0,1);glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);renderer.drawEye(view);if(!std::equal(parked.begin(),parked.end(),Mem::RAM.begin()))throw std::runtime_error("Renderer changed animated original state");if(glGetError())throw std::runtime_error("Animated actor GL error");std::vector<unsigned char> px(960*640*3);glPixelStorei(GL_PACK_ALIGNMENT,1);glReadPixels(0,0,960,640,GL_RGB,GL_UNSIGNED_BYTE,px.data());std::ofstream capture(argv[4],std::ios::binary);capture<<"P6\n960 640\n255\n";for(int row=639;row>=0;--row)capture.write(reinterpret_cast<char*>(px.data()+row*960*3),960*3);
 std::cout<<"PASS level "<<level+1<<": "<<initialActors<<" initially drawable -> "<<renderer.stats().entities<<" after 80 original ticks, missing="<<renderer.stats().missingAssets<<", weapon="<<renderer.stats().weaponDraws<<"\n";
 }key(ControlloopData::forward_key,frame<40);key(ControlloopData::fire_key,frame>=40&&frame<70);};Hires::game_main_loop();if(frame!=80)throw std::runtime_error("Original loop did not complete 80 ticks");}
 SDL_GL_DeleteContext(context);SDL_DestroyWindow(w);SDL_Quit();
}catch(const std::exception&e){std::cerr<<e.what()<<'\n';return 1;}}
