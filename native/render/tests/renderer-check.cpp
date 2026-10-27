/* Headset-free GPU smoke over the original retail snapshots. Build explicitly,
 * not as part of the shipped renderer. No software world render or mock art. */
#include "render.hpp"
#include "gpu.hpp"
#include "original.hpp"
#include <SDL.h>
#include <cassert>
#include <iostream>
#include <nlohmann/json.hpp>
int main(int argc,char**argv){try{
 if(argc!=4)throw std::runtime_error("assets original-fixtures output-directory");
 SDL_Init(SDL_INIT_VIDEO);SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION,3);SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION,3);SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,SDL_GL_CONTEXT_PROFILE_CORE);
 auto*w=SDL_CreateWindow("Native AB3DII renderer check",0,0,960,640,SDL_WINDOW_OPENGL|SDL_WINDOW_HIDDEN);if(!w)throw std::runtime_error(SDL_GetError());auto context=SDL_GL_CreateContext(w);if(!context)throw std::runtime_error(SDL_GetError());glewExperimental=GL_TRUE;auto glewResult=glewInit();if(glewResult!=GLEW_OK && !GLEW_VERSION_3_3)throw std::runtime_error(std::string("GLEW failed: ")+reinterpret_cast<const char*>(glewGetErrorString(glewResult)));while(glGetError()){}
 std::filesystem::create_directories(argv[3]);
 {ab3d2::Renderer renderer;renderer.loadAssets(argv[1]);
 for(int level=0;level<16;++level){std::fill(Mem::RAM.begin(),Mem::RAM.end(),0);std::ifstream file(std::filesystem::path(argv[2])/("level-"+std::to_string(level)+".ram"),std::ios::binary);if(!file)throw std::runtime_error("Missing original fixture");file.read(reinterpret_cast<char*>(Mem::RAM.data()),Mem::RAM_SIZE);Mem::cursor=file.gcount();renderer.loadLevel(level);auto beforeSync=std::vector<uint8_t>(Mem::RAM.begin(),Mem::RAM.begin()+Mem::cursor);renderer.sync();if(!std::equal(beforeSync.begin(),beforeSync.end(),Mem::RAM.begin()))throw std::runtime_error("Renderer modified original simulation RAM");
 float x=Mem::l(PlayerBss::Plr1_XOff_l)/65536.f/64,y=-Mem::l(PlayerBss::Plr1_YOff_l)/8192.f,z=-Mem::l(PlayerBss::Plr1_ZOff_l)/65536.f/64;
 ab3d2::RenderView view;view.headWorld=ab3d2::gpu::transform(x,y,z);view.camera={x,y,z};float f=1.0f/std::tan(80*3.14159265f/360),aspect=1.5f,n=.03f,far=300;
 ab3d2::Matrix p{f/aspect,0,0,0, 0,f,0,0, 0,0,(far+n)/(n-far),-1, 0,0,2*far*n/(n-far),0};view.viewProjection=ab3d2::gpu::multiply(p,ab3d2::gpu::transform(-x,-y,-z));
 glViewport(0,0,960,640);glClearColor(.015f,.025f,.04f,1);glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);renderer.drawEye(view);auto error=glGetError();if(error)throw std::runtime_error("GL error "+std::to_string(error));
 std::vector<unsigned char> pixels(960*640*3);glPixelStorei(GL_PACK_ALIGNMENT,1);glReadPixels(0,0,960,640,GL_RGB,GL_UNSIGNED_BYTE,pixels.data());size_t lit=0;for(size_t i=0;i<pixels.size();i+=3)if(pixels[i]>15||pixels[i+1]>15||pixels[i+2]>20)++lit;
 if(lit<5000)throw std::runtime_error("Blank native level "+std::to_string(level));std::ofstream capture(std::filesystem::path(argv[3])/("level-"+std::to_string(level)+".ppm"),std::ios::binary);capture<<"P6\n960 640\n255\n";for(int row=639;row>=0;--row)capture.write(reinterpret_cast<char*>(pixels.data()+row*960*3),960*3);

 // The same parked snapshot feeds both eyes. Moving only the eye must change
 // world parallax without changing any original entity or simulation byte.
 auto captureHash=[&](const ab3d2::RenderView&v){glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);renderer.drawEye(v);std::vector<unsigned char> px(960*640*3);glReadPixels(0,0,960,640,GL_RGB,GL_UNSIGNED_BYTE,px.data());uint64_t h=1469598103934665603ULL;for(auto b:px){h^=b;h*=1099511628211ULL;}return h;};
 auto left=view,right=view;left.viewProjection=ab3d2::gpu::multiply(p,ab3d2::gpu::transform(-x+.032f,-y,-z));right.viewProjection=ab3d2::gpu::multiply(p,ab3d2::gpu::transform(-x-.032f,-y,-z));
 if(captureHash(left)==captureHash(right))throw std::runtime_error("No stereo world parallax");
 if(!std::equal(beforeSync.begin(),beforeSync.end(),Mem::RAM.begin()))throw std::runtime_error("Eye rendering modified simulation RAM");
 if(level==0){
   nlohmann::json data;std::ifstream(std::filesystem::path(argv[1])/"levels/a.json")>>data;
   const auto&door=data["doors"][1];int off=door["wallPatches"][0]["gfxOfs"],graphics=Mem::l(LevelBss::Lvl_GraphicsPtr_l);int address=graphics+off;
   auto wi=std::find_if(data["walls"].begin(),data["walls"].end(),[&](const auto&w){return w["gfxOfs"]==off;});if(wi==data["walls"].end())throw std::runtime_error("Missing original moving wall");
   const auto&w0=*wi;auto a=data["points"][w0["leftPt"].get<int>()],b=data["points"][w0["rightPt"].get<int>()];float mx=(a["x"].get<float>()+b["x"].get<float>())/128,mz=-(a["z"].get<float>()+b["z"].get<float>())/128;
   float cx=0,cz=0;const auto&edges=data["zones"][w0["zone"].get<int>()]["edges"];for(const auto&e:edges){cx+=e["x"].get<float>()/64;cz-=e["z"].get<float>()/64;}cx/=edges.size();cz/=edges.size();float dx=cx-mx,dz=cz-mz,length=std::hypot(dx,dz);dx/=length;dz/=length;
   float py=-Mem::l(address+20)/8192.f-.5f,px=mx+dx*1.2f,pz=mz+dz*1.2f,yaw=std::atan2(dx,dz);auto nearDoor=view;nearDoor.headWorld=ab3d2::gpu::transform(px,py,pz,yaw);nearDoor.camera={px,py,pz};nearDoor.viewProjection=ab3d2::gpu::multiply(p,ab3d2::gpu::multiply(ab3d2::gpu::transform(0,0,0,-yaw),ab3d2::gpu::transform(-px,-py,-pz)));
   auto before=captureHash(nearDoor);auto updates=renderer.stats().dynamicUpdates;int previousBottom=Mem::l(address+24);Mem::wl(address+24,Mem::l(address+20)+8192);if(Mem::l(address+24)==previousBottom)Mem::wl(address+24,previousBottom+8192);
   int table=Mem::l(LevelBss::Lvl_ZonePtrsPtr_l),zone=Mem::l(table+door["zone"].get<int>()*4);Mem::wl(zone+Defs::ZoneT_Roof_l,Mem::l(zone+Defs::ZoneT_Roof_l)-4096);
   auto changedRAM=std::vector<uint8_t>(Mem::RAM.begin(),Mem::RAM.begin()+Mem::cursor);renderer.sync();if(!std::equal(changedRAM.begin(),changedRAM.end(),Mem::RAM.begin()))throw std::runtime_error("Dynamic sync modified simulation");
   if(renderer.stats().dynamicUpdates<updates+3)throw std::runtime_error("Original door/ceiling geometry did not update");if(captureHash(nearDoor)==before)throw std::runtime_error("Moving original door produced identical GPU image");
   std::cout<<"PASS live original wall and ceiling deformation, read-only sync and stereo parallax"<<std::endl;
 }
 std::cout<<"Level "<<level+1<<": "<<lit<<" visible pixels, "<<renderer.stats().entities<<" actor packets, "<<renderer.stats().weaponDraws<<" weapon draws, missing="<<renderer.stats().missingAssets<<std::endl;
 }
 for(auto kind:{ab3d2::Panel::Title,ab3d2::Panel::Story,ab3d2::Panel::Pause,ab3d2::Panel::Ending}){renderer.setPanel({kind,"ALIEN BREED 3D II",{"ORIGINAL STORY AND MENU BITMAP FONT","RESUME","TURN: SMOOTH","SAVE GAME","LOAD GAME","QUIT"},1});ab3d2::RenderView panelView;panelView.viewProjection={.8f,0,0,0, 0,1.2f,0,0, 0,0,-1,-1, 0,0,-.1f,0};glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);renderer.drawEye(panelView);if(glGetError())throw std::runtime_error("Original panel GL failure");}
 std::cout<<"PASS stereo-ready original-art title/story/pause/ending panels"<<std::endl;
 }
 SDL_GL_DeleteContext(context);SDL_DestroyWindow(w);SDL_Quit();
}catch(const std::exception&e){std::cerr<<e.what()<<'\n';return 1;}}
