#include "render.hpp"
#include "gpu.hpp"
#include "original.hpp"
#include <nlohmann/json.hpp>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <map>
#include <optional>
#include <set>
#include <sstream>
#include <tuple>
using Json=nlohmann::json;
namespace ab3d2 {
namespace {
constexpr float Pi=3.14159265358979323846f;
Json json(const std::filesystem::path&p){std::ifstream f(p);if(!f)throw std::runtime_error("Missing original data "+p.string());Json j;f>>j;return j;}
void paste(gpu::Image&to,const gpu::Image&from,int x,int y){for(int row=0;row<from.height;++row)std::copy_n(from.pixels.data()+row*from.width*4,from.width*4,to.pixels.data()+((row+y)*to.width+x)*4);}
struct Region {int x=0,y=0,w=1,h=1;};
void region(gpu::Vertex&v,const Region&r,float from=0,float width=1,float palette=0){v.regionX=r.x;v.regionY=r.y;v.regionW=r.w;v.regionH=r.h;v.from=from;v.tileWidth=width;v.palette=palette;}
void quad(std::vector<gpu::Vertex>&v,const std::array<gpu::Vertex,4>&p){for(int i:{0,1,2,0,2,3})v.push_back(p[i]);}
bool valid(int p,int bytes=1){return p>0 && p<Mem::RAM_SIZE-bytes;}
std::string numbered(const char*prefix,int number,int digits,const char*suffix){char n[32];snprintf(n,sizeof(n),"%0*d",digits,number);return std::string(prefix)+n+suffix;}
}
struct Renderer::Impl {
    std::filesystem::path root;
    Json glf,level,font;
    Panel panel;
    RenderStats stats;
    unsigned shader=0,pointTexture=0,sceneTexture=0,paletteIndex=0;int sceneWidth=0,sceneHeight=0;float waterPhase=0,waterScroll=0,waterAngle=0;bool underwater=false;float waterY=0;std::set<int> waterZones;
    std::map<std::string,int> uniforms;
    std::map<std::string,gpu::Texture> textures;
    std::map<std::string,gpu::Mesh> models;
    std::map<std::string,std::vector<std::array<float,3>>> modelPoints;
    struct Mount {float x=0,y=0,distance=.2f;};
    std::map<int,Mount> weaponMounts;Mount weaponMount;
    gpu::Image mainPalette;std::map<std::tuple<int,int,int>,std::string> spritePaths;
    std::set<std::string> missing;
    std::vector<Region> wallRegions,floorRegions;
    gpu::Texture wallAtlas,wallPalette,floorAtlas,floorPalette;
    gpu::Mesh walls,floors,water,sky,laser,unitQuad,hudMesh,panelText;
    std::vector<gpu::Vertex> wallVertices,floorVertices,waterVertices;
    struct Wall {Json data;size_t first=0;int top=0,bottom=0,yoff=0,from=0,texture=-1;};
    struct Flat {int zone=0;bool upper=false,ceiling=false,moving=false;size_t first=0,count=0;float y=0;};
    std::vector<Wall> wallRecords;
    std::vector<Flat> flatRecords;
    struct Actor {float x=0,y=0,z=0,width=0,height=0;int model=0,frame=0,angle=0,zone=0,palette=0;bool vector=false,additive=false,flip=false;float bright=0;};
    std::vector<Actor> actors;
    Actor weapon;bool hasWeapon=false;
    int health=0,ammo=0,fuel=0,gun=0,playerAngle=0;
    std::string hudLabel;
    int levelIndex=-1,zoneCount=1;
    Impl(){shader=gpu::program();gpu::Image white;white.width=white.height=1;white.pixels={255,255,255,255};textures.emplace("#white",gpu::texture(white));++stats.textureUploads;white.pixels={0,0,0,255};textures.emplace("#black",gpu::texture(white));++stats.textureUploads;
        std::vector<gpu::Vertex> q;quad(q,{{{-.5f,.5f,0,0,0},{.5f,.5f,0,1,0},{.5f,-.5f,0,1,1},{-.5f,-.5f,0,0,1}}});unitQuad=gpu::mesh(q);++stats.meshUploads;
        white.pixels={255,28,3,255};textures.emplace("#aim-guide",gpu::texture(white));++stats.textureUploads;std::vector<gpu::Vertex> ray;
        for(int i=0;i<8;++i){float a=2*Pi*i/8,b=2*Pi*(i+1)/8,x0=.0015f*std::cos(a),y0=.0015f*std::sin(a),x1=.0015f*std::cos(b),y1=.0015f*std::sin(b);quad(ray,{{{x0,y0,0,0,0},{x1,y1,0,1,0},{x1,y1,-.28f,1,1},{x0,y0,-.28f,0,1}}});}
        quad(ray,{{{-.0015f,.0015f,0,0,0},{.0015f,.0015f,0,1,0},{.0015f,-.0015f,0,1,1},{-.0015f,-.0015f,0,0,1}}});laser=gpu::mesh(ray);++stats.meshUploads;}
    ~Impl(){clearLevel();gpu::destroy(sky);gpu::destroy(laser);if(sceneTexture)glDeleteTextures(1,&sceneTexture);if(paletteIndex)glDeleteTextures(1,&paletteIndex);for(auto&[key,m]:models)gpu::destroy(m);gpu::destroy(unitQuad);gpu::destroy(hudMesh);gpu::destroy(panelText);for(auto&[key,t]:textures)if(t.id)glDeleteTextures(1,&t.id);for(auto*t:{&wallAtlas,&wallPalette,&floorAtlas,&floorPalette})if(t->id)glDeleteTextures(1,&t->id);if(pointTexture)glDeleteTextures(1,&pointTexture);if(shader)glDeleteProgram(shader);}
    void clearLevel(){gpu::destroy(walls);gpu::destroy(floors);gpu::destroy(water);wallVertices.clear();floorVertices.clear();waterVertices.clear();wallRecords.clear();flatRecords.clear();waterZones.clear();actors.clear();hasWeapon=false;weaponMount={};underwater=false;}
    int loc(const char*n){auto i=uniforms.find(n);if(i!=uniforms.end())return i->second;return uniforms.emplace(n,glGetUniformLocation(shader,n)).first->second;}
    gpu::Texture& texture(const std::string&name){auto i=textures.find(name);if(i!=textures.end())return i->second;try{auto t=gpu::texture(gpu::png(root/name));++stats.textureUploads;return textures.emplace(name,t).first->second;}catch(const std::exception&){if(missing.insert(name).second){++stats.missingAssets;std::cerr<<"Native renderer missing original texture: "<<name<<"\n";}return textures.at("#white");}}
    void loadAtlases(){
        int count=glf.at("wallTextures").size(),height=0,width=1;std::vector<gpu::Image> images(count),palettes(count);wallRegions.resize(count);
        for(const auto&w:glf.at("wallTextures")){int id=w.at("index");std::string name=w.at("name");if(name.empty())continue;images[id]=gpu::png(root/("textures/walls/"+name+".idx.png"));palettes[id]=gpu::png(root/("textures/walls/"+name+".lut.png"));width=std::max(width,images[id].width);height+=images[id].height;}
        gpu::Image atlas{width,std::max(1,height),std::vector<unsigned char>(width*std::max(1,height)*4)},palette{32,count*32,std::vector<unsigned char>(32*count*32*4)};int y=0;
        for(int i=0;i<count;++i)if(images[i].width){wallRegions[i]={0,y,images[i].width,images[i].height};paste(atlas,images[i],0,y);paste(palette,palettes[i],0,i*32);y+=images[i].height;}
        wallAtlas=gpu::texture(atlas);wallPalette=gpu::texture(palette);stats.textureUploads+=2;
        gpu::Image floor{64,16*64,std::vector<unsigned char>(64*16*64*4)};for(int i=0;i<16;++i){auto image=gpu::png(root/numbered("textures/floors/floor_",i,2,".idx.png"));paste(floor,image,0,i*64);floorRegions.push_back({0,i*64,64,64});}
        floorAtlas=gpu::texture(floor);floorPalette=gpu::texture(gpu::png(root/"textures/floors/floor_shade.lut.png"));stats.textureUploads+=2;
    }
    void loadBackdropAndWater(){
        std::vector<gpu::Vertex> vertices;float radius=500,half=radius*std::tan(36.3f*Pi/180),extent=4;
        for(int i=0;i<64;++i){float a0=2*Pi*i/64,a1=2*Pi*(i+1)/64,u0=2.f*i/64,u1=2.f*(i+1)/64;float x0=std::sin(a0)*radius,z0=-std::cos(a0)*radius,x1=std::sin(a1)*radius,z1=-std::cos(a1)*radius;
            quad(vertices,{{{x0,half*extent,z0,u0,.5f-extent/2},{x1,half*extent,z1,u1,.5f-extent/2},{x1,-half*extent,z1,u1,.5f+extent/2},{x0,-half*extent,z0,u0,.5f+extent/2}}});}
        sky=gpu::mesh(vertices);++stats.meshUploads;texture("textures/sky/backdrop.png");texture("textures/water_waves.png");texture("textures/water_shade.lut.png");texture("textures/water_under.lut.png");
        mainPalette=gpu::png(root/"palette.png");auto&base=mainPalette;std::vector<unsigned char> indices(64*64*64);
        // One-time color -> original palette index cube. It lives in VRAM and
        // restores the original indexed water operation from the GPU color
        // target; no framebuffer pixels are ever read by the CPU.
        for(int b=0;b<64;++b)for(int g=0;g<64;++g)for(int r=0;r<64;++r){int best=0,distance=INT32_MAX;
            for(int n=0;n<256;++n){int dr=r*255/63-base.pixels[n*4],dg=g*255/63-base.pixels[n*4+1],db=b*255/63-base.pixels[n*4+2],d=dr*dr+dg*dg+db*db;if(d<distance){distance=d;best=n;}}
            indices[(b*64+g)*64+r]=best;}
        glGenTextures(1,&paletteIndex);glBindTexture(GL_TEXTURE_3D,paletteIndex);glPixelStorei(GL_UNPACK_ALIGNMENT,1);glTexImage3D(GL_TEXTURE_3D,0,GL_R8,64,64,64,0,GL_RED,GL_UNSIGNED_BYTE,indices.data());
        for(unsigned name:{GL_TEXTURE_MIN_FILTER,GL_TEXTURE_MAG_FILTER})glTexParameteri(GL_TEXTURE_3D,name,GL_NEAREST);for(unsigned name:{GL_TEXTURE_WRAP_S,GL_TEXTURE_WRAP_T,GL_TEXTURE_WRAP_R})glTexParameteri(GL_TEXTURE_3D,name,GL_CLAMP_TO_EDGE);++stats.textureUploads;
    }
    void copyScene(){
        int viewport[4],drawBuffer=0,readBuffer=0,oldRead=0,sourceBuffer=0;glGetIntegerv(GL_VIEWPORT,viewport);glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING,&drawBuffer);glGetIntegerv(GL_READ_FRAMEBUFFER_BINDING,&readBuffer);glGetIntegerv(GL_READ_BUFFER,&oldRead);glGetIntegerv(GL_DRAW_BUFFER0,&sourceBuffer);
        if(!sceneTexture)glGenTextures(1,&sceneTexture);glActiveTexture(GL_TEXTURE3);glBindTexture(GL_TEXTURE_2D,sceneTexture);glBindFramebuffer(GL_READ_FRAMEBUFFER,drawBuffer);glReadBuffer(sourceBuffer);
        if(sceneWidth!=viewport[2]||sceneHeight!=viewport[3]){sceneWidth=viewport[2];sceneHeight=viewport[3];glCopyTexImage2D(GL_TEXTURE_2D,0,GL_RGBA8,viewport[0],viewport[1],sceneWidth,sceneHeight,0);glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);}
        else glCopyTexSubImage2D(GL_TEXTURE_2D,0,0,0,viewport[0],viewport[1],sceneWidth,sceneHeight);
        glBindFramebuffer(GL_READ_FRAMEBUFFER,readBuffer);glReadBuffer(oldRead);glActiveTexture(GL_TEXTURE0);
        glUseProgram(shader);glUniform4f(loc("viewport"),viewport[0],viewport[1],viewport[2],viewport[3]);
    }
    gpu::Mesh* model(int index,int frame){
        if(index<0 || index>=int(glf.at("vectorModels").size()))return nullptr;
        std::string name=glf["vectorModels"][index].value("name","");if(name.empty())return nullptr;
        auto path=numbered(("models/"+name+"/frame_").c_str(),frame,3,".obj");auto known=models.find(path);if(known!=models.end())return &known->second;
        std::ifstream file(root/path);if(!file && frame!=0)return model(index,0);if(!file){if(missing.insert(path).second)++stats.missingAssets;return nullptr;}
        std::vector<std::array<float,3>> positions;std::vector<std::array<float,2>> uv;std::vector<gpu::Vertex> vertices;std::string line;
        while(std::getline(file,line)){std::istringstream row(line);std::string type;row>>type;if(type=="v"){std::array<float,3> p{};row>>p[0]>>p[1]>>p[2];positions.push_back(p);}else if(type=="vt"){std::array<float,2> p{};row>>p[0]>>p[1];uv.push_back(p);}else if(type=="f"){
            std::vector<gpu::Vertex> face;std::string item;while(row>>item){size_t slash=item.find('/');int pi=std::stoi(item)-1,ti=slash==std::string::npos?-1:std::stoi(item.substr(slash+1))-1;if(pi<0||pi>=int(positions.size()))continue;auto p=positions[pi];gpu::Vertex v{p[0],p[1],p[2],0,0};if(ti>=0&&ti<int(uv.size())){v.u=uv[ti][0];v.v=1-uv[ti][1];}face.push_back(v);}
            for(size_t k=1;k+1<face.size();++k){vertices.push_back(face[0]);vertices.push_back(face[k]);vertices.push_back(face[k+1]);}}}
        if(vertices.empty())return nullptr;
        modelPoints[path]=std::move(positions);
        auto m=gpu::mesh(vertices);++stats.meshUploads;return &models.emplace(path,m).first->second;
    }
    Mount calibratedMount(int selected){
        auto cached=weaponMounts.find(selected);if(cached!=weaponMounts.end())return cached->second;
        Mount result;if(selected<0||selected>=int(glf["guns"].size()))return result;
        auto&definition=glf["objects"][glf["guns"][selected]["gunObject"].get<int>()];
        if(!definition.value("isVector",false))return result;auto&rest=definition["actAnim"][0];
        int index=rest["gfx"],frame=rest["frame"];if(!model(index,frame))return result;
        std::string name=glf["vectorModels"][index].value("name","");auto path=numbered(("models/"+name+"/frame_").c_str(),frame,3,".obj");auto found=modelPoints.find(path);if(found==modelPoints.end())return result;
        // Hires starts heldAngle at playerAngle+4096; animObj then adds the
        // original actAnim word2 (2048 for shotgun, zero for other guns).
        // The held frames also contain original screen-composition offsets.
        // Calibrate from the actual muzzle ring, never firing flash geometry.
        float yaw=-rest["word2"].get<float>()*2*Pi/8192,c=std::cos(yaw),s=std::sin(yaw),front=1e9f;
        for(const auto&p:found->second)front=std::min(front,-s*p[0]+c*p[2]);
        float left=1e9f,right=-1e9f,bottom=1e9f,top=-1e9f;
        for(const auto&p:found->second)if(-s*p[0]+c*p[2]<front+.03126f){float x=c*p[0]+s*p[2];left=std::min(left,x);right=std::max(right,x);bottom=std::min(bottom,p[1]);top=std::max(top,p[1]);}
        result.x=-(left+right)*.11f;result.y=-(bottom+top)*.11f;result.distance=std::max(.03f,-front*.22f+.02f);
        weaponMounts.emplace(selected,result);return result;
    }
    void fillWall(Wall&w,int top,int bottom,int yoff,int from,int tex){
        auto&d=w.data;int a=d.at("leftPt"),b=d.at("rightPt");if(a<0||b<0||a>=int(level["points"].size())||b>=int(level["points"].size()))return;
        if(tex<0||tex>=int(wallRegions.size()))tex=0;auto r=wallRegions[tex];int tw=std::max(1,d.value("widthMask",63)+1),th=std::max(1,d.value("heightMask",63)+1);float u=float(d.value("wallLen",tw))/tw;
        float x0=level["points"][a]["x"].get<float>()/64,z0=-level["points"][a]["z"].get<float>()/64,x1=level["points"][b]["x"].get<float>()/64,z1=-level["points"][b]["z"].get<float>()/64;
        std::array<gpu::Vertex,4> p{{{x0,-top/32.f,z0,0,(top+yoff)/float(th)},{x1,-top/32.f,z1,u,(top+yoff)/float(th)},{x1,-bottom/32.f,z1,u,(bottom+yoff)/float(th)},{x0,-bottom/32.f,z0,0,(bottom+yoff)/float(th)}}};
        int pbr=d.value("whichPBR",16);for(int k=0;k<4;++k){bool upper=k<2;int nibble=upper?pbr>>4:pbr;int zi=(nibble&8)?d.value("otherZone",0):d.value("zone",0);int slot=(k==0||k==3)?d.value("whichLeft",0):d.value("whichRight",1);p[k].lightZone=zi;p[k].lightSlot=slot*4+(nibble&7);p[k].lightOffset=d.value("brightOffset",0);if(p[k].lightSlot<0||p[k].lightSlot>=40||zi<0||zi>=zoneCount)p[k].lightZone=-1;region(p[k],r,from,tw,tex);}
        int ids[]={0,1,2,0,2,3};for(int k=0;k<6;++k)wallVertices[w.first+k]=p[ids[k]];
        w.top=top;w.bottom=bottom;w.yoff=yoff;w.from=from;w.texture=tex;
    }
    void buildLevel(){
        std::set<std::tuple<int,bool,std::string>> emitted;
        for(const auto&d:level.at("walls")){if(std::abs(d.value("top",0)-d.value("bottom",0))>8192)continue;Wall w;w.data=d;w.first=wallVertices.size();wallVertices.resize(w.first+6);fillWall(w,d.value("top",0),d.value("bottom",0),d.value("yOffset",0),d.value("fromTile",0),d.value("texIndex",0)&32767);wallRecords.push_back(w);}
        walls=gpu::mesh(wallVertices,true);++stats.meshUploads;
        for(const auto&f:level.at("flats")){
            int z=f.value("zone",0);bool upper=f.value("upper",false);std::string kind=f.value("kind","floor");if(!emitted.emplace(z,upper,kind).second)continue;
            if(z<0||z>=int(level["zones"].size()))continue;const auto&zone=level["zones"][z];std::vector<std::array<float,2>> ring;
            for(const auto&e:zone.at("edges"))ring.push_back({e.at("x").get<float>(),e.at("z").get<float>()});if(ring.size()<3)continue;
            auto tri=gpu::triangulate(ring);if(tri.size()!=(ring.size()-2)*3)throw std::runtime_error("Original zone triangulation failed: "+std::to_string(z));
            bool isWater=kind=="water",ceiling=kind=="ceil";if(isWater)waterZones.insert(z);auto&v=isWater?waterVertices:floorVertices;Flat record{z,upper,ceiling,false,v.size(),tri.size(),-f.value("y",0)/128.f};int tile=((f.value("tile",0)%16)+16)%16;
            for(int i:tri){auto p=ring[i];gpu::Vertex vert{p[0]/64,record.y,-p[1]/64,p[0]/64,p[1]/64};vert.lightZone=z;vert.lightSlot=i*4+(upper?2:0)+(ceiling?1:0);if(vert.lightSlot>=40)vert.lightZone=-1;region(vert,floorRegions[tile],0,64,0);v.push_back(vert);}if(!isWater)flatRecords.push_back(record);
        }
        floors=gpu::mesh(floorVertices,true);water=gpu::mesh(waterVertices);stats.meshUploads+=2;
    }
    void pointLights(){
        int base=Mem::l(TablesBss::PointBrightsPtr_l);std::vector<float> values(zoneCount*40,300);
        for(int z=0;z<zoneCount;++z)for(int slot=0;slot<40;++slot){int at=base+(z*40+slot)*2;int raw=valid(at,2)?Mem::w(at):0;int value=int8_t(raw);unsigned high=uint16_t(raw)>>8;
            if(value>=0&&high){int anim=high&15,blend=(high>>4)+1;int p=AnimBss::Anim_BrightTable_vw+anim*2-2;if(anim>0&&valid(p,2)){int delta=int16_t((Mem::w(p)-value)*blend);value=int8_t(value+(delta>>4));}}
            int n=(value*397)>>8;if(n<0)n-=600;values[z*40+slot]=int16_t(n+300);}
        if(!pointTexture)glGenTextures(1,&pointTexture);glActiveTexture(GL_TEXTURE2);glBindTexture(GL_TEXTURE_2D,pointTexture);glBindBuffer(GL_PIXEL_UNPACK_BUFFER,0);glPixelStorei(GL_UNPACK_ALIGNMENT,1);glPixelStorei(GL_UNPACK_ROW_LENGTH,0);glPixelStorei(GL_UNPACK_SKIP_ROWS,0);glPixelStorei(GL_UNPACK_SKIP_PIXELS,0);
        glTexImage2D(GL_TEXTURE_2D,0,GL_R32F,40,zoneCount,0,GL_RED,GL_FLOAT,values.data());glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);glActiveTexture(GL_TEXTURE0);++stats.dynamicUpdates;
    }
    Actor actor(int address,int points){Actor a;int id=Mem::w(address);a.x=Mem::w(points+id*8)/64.f;a.z=-Mem::w(points+id*8+4)/64.f;a.y=-Mem::w(address+4)/64.f;a.zone=Mem::w(address+12);a.vector=Mem::ub(address+6)==255;a.width=Mem::ub(address+6)/32.f;a.height=Mem::ub(address+7)/32.f;a.model=Mem::uw(address+8);a.frame=a.vector?Mem::uw(address+10):Mem::ub(address+11);a.palette=Mem::ub(address+10)&127;a.flip=(Mem::ub(address+10)&128)!=0;a.additive=!a.vector&&a.palette>=6;a.angle=Mem::uw(address+30);a.bright=Mem::w(address+2);return a;}
    void synchronize(){
        if(levelIndex<0)return;pointLights();int graphics=Mem::l(LevelBss::Lvl_GraphicsPtr_l);bool wallChanged=false,floorChanged=false;
        if(valid(graphics))for(auto&w:wallRecords){int p=graphics+w.data.value("gfxOfs",0)+2;if(!valid(p,28))continue;int top=Mem::l(p+18)>>8,bottom=Mem::l(p+22)>>8,yoff=Mem::uw(p+10),from=Mem::uw(p+8)<<4,tex=Mem::uw(p+12)&32767;if(top!=w.top||bottom!=w.bottom||yoff!=w.yoff||from!=w.from||tex!=w.texture){fillWall(w,top,bottom,yoff,from,tex);wallChanged=true;}}
        if(wallChanged){gpu::update(walls,wallVertices);++stats.dynamicUpdates;}
        int zones=Mem::l(LevelBss::Lvl_ZonePtrsPtr_l);if(valid(zones))for(auto&f:flatRecords){int p=Mem::l(zones+f.zone*4);if(!valid(p,18))continue;int off=f.ceiling?(f.upper?14:6):(f.upper?10:2);float y=-Mem::l(p+off)/8192.f;if(std::abs(y-f.y)>.00001f){for(size_t i=f.first;i<f.first+f.count;++i)floorVertices[i].y=y;f.y=y;floorChanged=true;}}
        if(floorChanged){gpu::update(floors,floorVertices);++stats.dynamicUpdates;}
        actors.clear();int records=Mem::l(LevelBss::Lvl_ObjectDataPtr_l),points=Mem::l(LevelBss::Lvl_ObjectPointsPtr_l),player=Mem::l(PlayerBss::Plr1_ObjectPtr_l);int held=player+Defs::ENT_NEXT_2;
        auto collect=[&](int base,int limit,bool sentinel){if(!valid(base,64)||!valid(points))return;for(int i=0;i<limit;++i){int p=base+i*64;if(!valid(p,64))break;int id=Mem::w(p);if(id<0){if(sentinel)break;continue;}if(!valid(points+id*8,8)||Mem::w(p+12)<0||p==held)continue;int type=Mem::ub(p+16);if(type==4||type==5)continue;auto a=actor(p,points);if(!a.vector&&(a.width==0||a.height==0))continue;actors.push_back(a);if(a.vector)model(a.model,a.frame);else sprite(a);}};
        collect(records,2000,true);int alienShots=Mem::l(LevelBss::AI_AlienShotDataPtr_l),playerShots=Mem::l(PlayerBss::Plr_ShotDataPtr_l);if(alienShots!=records)collect(alienShots,20,false);if(playerShots!=records&&playerShots!=alienShots)collect(playerShots,20,false);
        hasWeapon=valid(held,64)&&Mem::w(held)>=0;if(hasWeapon){weapon=actor(held,points);hasWeapon=weapon.vector&&model(weapon.model,weapon.frame);}
        waterScroll=(uint32_t(Mem::l(HiresData::wateroff))&16383)/16384.f;waterAngle=Mem::uw(HiresData::wtan);int waterPointer=Mem::l(HiresData::draw_WaterFramePtr_l);waterPhase=uint32_t(Mem::l(HiresData::wateroff))&7;for(int i=0;i<8;++i)if(waterPointer&&Mem::l(HiresData::draw_WaterFramePtrs_vl+i*4)==waterPointer){waterPhase=i;break;}
        int playerZone=Mem::uw(PlayerBss::Plr1_Zone_w);underwater=waterZones.count(playerZone);if(underwater&&valid(zones+playerZone*4,4)){int zp=Mem::l(zones+playerZone*4);waterY=valid(zp,22)?-Mem::l(zp+18)/8192.f:0;}
        health=Mem::uw(PlayerBss::Plr1_Health_w);fuel=Mem::uw(PlayerBss::Plr1_JetpackFuel_w);gun=Mem::ub(PlayerBss::Plr1_GunSelected_b);playerAngle=Mem::uw(PlayerBss::Plr1_AngPos_w);int bullet=gun<int(glf["guns"].size())?glf["guns"][gun].value("bulletType",0):0;ammo=Mem::uw(PlayerBss::Plr1_AmmoCounts_vw+std::clamp(bullet,0,19)*2);
        weaponMount=hasWeapon?calibratedMount(gun):Mount{};
        std::string label="VITALITY "+std::to_string(health)+"   AMMO "+std::to_string(ammo)+"   FUEL "+std::to_string(fuel);if(gun<int(glf["guns"].size()))label+="   "+glf["guns"][gun].value("name","");if(label!=hudLabel){hudLabel=label;makeHud();}stats.entities=actors.size();
    }
    std::optional<gpu::Image> nativeSprite(const Actor&a,const std::string&sheet){
        if(a.model<0||a.model>=30||a.frame<0||a.frame>=32)return std::nullopt;
        int entry=DrawBss::Draw_ObjectPtrs_vl+a.model*16,glfBase=Mem::l(HiresData::GLF_DatabasePtr_l),record=glfBase+Defs::GLFT_FrameData_l+a.model*256+a.frame*8;
        if(!valid(entry,16)||!valid(record,8))return std::nullopt;int wad=Mem::l(entry),ptr=Mem::l(entry+4),pal=Mem::l(entry+12),width=Mem::uw(record+4)*2,height=Mem::uw(record+6)*2;
        if(!valid(wad)||!valid(ptr)||!valid(pal)||width<1||height<1||width>1024||height>1024)return std::nullopt;
        int columns=ptr+Mem::uw(record)*4,down=Mem::uw(record+2);if(!valid(columns,width*4))return std::nullopt;
        bool hqn=sheet=="GUARD"||sheet=="PRIEST"||sheet=="INSECT"||sheet=="TRICLAW"||sheet=="ASHNARG"||sheet=="ROBOTRIGHT"||sheet=="WORM"||sheet=="GLOBE";
        gpu::Image image{width,height,std::vector<unsigned char>(width*height*4)};
        for(int x=0;x<width;++x){uint32_t column=Mem::l(columns+x*4);if(!column)continue;unsigned format=column>>24;int data=wad+(column&0xffffff);
            for(int y=0;y<height;++y){int at=data+(down+y)*(hqn?1:2);if(!valid(at,hqn?1:2))continue;int index=hqn?Mem::ub(at):format<=2?(Mem::uw(at)>>(format*5))&31:0;if(!index)continue;
                int colorAt=hqn?pal+std::clamp(a.palette-2,0,3)*256+index:a.additive?pal+index*256:pal+index*2;if(!valid(colorAt))continue;unsigned color=Mem::ub(colorAt);auto out=image.pixels.data()+(y*width+x)*4;std::copy_n(mainPalette.pixels.data()+color*4,3,out);out[3]=255;
            }}
        // Fully transparent source frames (e.g. PICKUPS/28 story markers) are
        // intentionally invisible, not missing assets or white placeholders.
        return image;
    }
    gpu::Texture& sprite(const Actor&a){
        auto key=std::make_tuple(a.model,a.frame,a.palette);auto cached=spritePaths.find(key);if(cached!=spritePaths.end())return textures.at(cached->second);
        if(a.model<0||a.model>=int(glf["spriteSheets"].size()))return textures.at("#white");std::string sheet=glf["spriteSheets"][a.model].value("name","");std::string path=numbered(("textures/objects/"+sheet+"/frame_").c_str(),a.frame,2,".png");
        if(a.palette>=3&&a.palette<6)path=numbered(("textures/objects/"+sheet+"/frame_").c_str(),a.frame,2,("_p"+std::to_string(a.palette-2)+".png").c_str());
        if(std::filesystem::exists(root/path)){auto&result=texture(path);spritePaths.emplace(key,path);return result;}
        if(auto decoded=nativeSprite(a,sheet)){std::string generated="#native/"+sheet+"/"+std::to_string(a.frame)+"/"+std::to_string(a.palette);auto uploaded=gpu::texture(*decoded);++stats.textureUploads;textures.emplace(generated,uploaded);spritePaths.emplace(key,generated);return textures.at(generated);}
        return texture(path);
    }
    void text(std::vector<gpu::Vertex>&vertices,const std::string&value,float x,float y,float height){int columns=font.value("columns",16),first=font.value("firstChar",32),gw=font.value("glyphWidth",16),gh=font.value("glyphHeight",16);auto&t=texture("menu/endfont.png");for(unsigned char c:value){int glyph=int(c)-first;if(glyph<0||glyph>=int(font["widths"].size()))glyph='?'-first;float width=font["widths"][glyph].get<float>()*height/gh;float u=(glyph%columns)*gw/float(t.width),v=(glyph/columns)*gh/float(t.height),du=width/height*gh/t.width,dv=gh/float(t.height);quad(vertices,{{{x,y+height,-2.2f,u,v},{x+width,y+height,-2.2f,u+du,v},{x+width,y,-2.2f,u+du,v+dv},{x,y,-2.2f,u,v+dv}}});x+=width+height/16;}}
    void makeHud(){std::vector<gpu::Vertex> v;std::string name=gun<int(glf["guns"].size())?glf["guns"][gun].value("name",""):"";text(v,name,-.96f,-.65f,.05f);text(v,"VITALITY",-.96f,-.72f,.04f);text(v,"AMMO",-.25f,-.72f,.04f);text(v,"FUEL",.40f,-.72f,.04f);text(v,std::to_string(health),-.96f,-.81f,.085f);text(v,std::to_string(ammo),-.25f,-.81f,.085f);text(v,std::to_string(fuel),.40f,-.81f,.085f);gpu::destroy(hudMesh);hudMesh=gpu::mesh(v);++stats.meshUploads;}
    void makePanel(){std::vector<gpu::Vertex>v;text(v,panel.caption,-.9f,.65f,.06f);float step=panel.lines.size()>20?.048f:.062f,y=.48f;for(size_t i=0;i<panel.lines.size();++i){text(v,(int(i)==panel.selection?"> ":"  ")+panel.lines[i],-.97f,y,step*.72f);y-=step;}gpu::destroy(panelText);panelText=gpu::mesh(v);++stats.meshUploads;}
    void draw(const gpu::Mesh&m,const gpu::Texture&t,const Matrix&matrix,float scale,int mode=0,float shade=1,float opacity=1,const gpu::Texture*palette=nullptr){if(!m.count)return;glUseProgram(shader);glUniformMatrix4fv(loc("model"),1,GL_FALSE,matrix.data());glUniform1f(loc("scale"),scale);glUniform1i(loc("mode"),mode);glUniform1f(loc("shade"),shade);glUniform1f(loc("opacity"),opacity);glUniform4f(loc("tint"),1,1,1,1);glActiveTexture(GL_TEXTURE0);glBindTexture(GL_TEXTURE_2D,t.id);glActiveTexture(GL_TEXTURE1);glBindTexture(GL_TEXTURE_2D,palette?palette->id:0);glActiveTexture(GL_TEXTURE2);glBindTexture(GL_TEXTURE_2D,pointTexture);glActiveTexture(GL_TEXTURE3);glBindTexture(GL_TEXTURE_2D,sceneTexture);glActiveTexture(GL_TEXTURE4);glBindTexture(GL_TEXTURE_3D,paletteIndex);glActiveTexture(GL_TEXTURE5);glBindTexture(GL_TEXTURE_2D,texture("textures/water_waves.png").id);glActiveTexture(GL_TEXTURE0);glBindVertexArray(m.vao);glDrawArrays(GL_TRIANGLES,0,m.count);++stats.drawCalls;stats.triangles+=m.count/3;}
    void plane(const gpu::Texture&t,const Matrix&head,float x,float y,float z,float w,float h,float alpha=1){draw(unitQuad,t,gpu::multiply(head,gpu::transform(x,y,z,0,w,h,1)),1,0,1,alpha);}
    void eye(const RenderView&view){
        glUseProgram(shader);glUniformMatrix4fv(loc("vp"),1,GL_FALSE,view.viewProjection.data());glUniform1i(loc("image"),0);glUniform1i(loc("palette"),1);glUniform1i(loc("points"),2);glUniform1i(loc("scene"),3);glUniform1i(loc("paletteIndex"),4);glUniform1i(loc("waves"),5);glUniform1f(loc("waterPhase"),waterPhase);glUniform1f(loc("waterScroll"),waterScroll);glUniform1f(loc("waterAngle"),waterAngle);glUniform1f(loc("worldScale"),view.worldScale);glUniform3f(loc("camera"),view.headWorld[12],view.headWorld[13],view.headWorld[14]);glUniform3f(loc("forward"),-view.headWorld[8],-view.headWorld[9],-view.headWorld[10]);
        glDisable(GL_CULL_FACE);glDisable(GL_SCISSOR_TEST);glEnable(GL_DEPTH_TEST);glDepthMask(GL_TRUE);glDisable(GL_BLEND);
        if(panel.kind==Panel::Gameplay||panel.kind==Panel::Pause){
            glDisable(GL_DEPTH_TEST);glDepthMask(GL_FALSE);draw(sky,texture("textures/sky/backdrop.png"),gpu::transform(view.headWorld[12],view.headWorld[13],view.headWorld[14]),1,3);glDepthMask(GL_TRUE);glEnable(GL_DEPTH_TEST);
            draw(walls,wallAtlas,Identity,view.worldScale,1,1,1,&wallPalette);draw(floors,floorAtlas,Identity,view.worldScale,2,1,1,&floorPalette);
            for(const auto&a:actors){float shade=a.additive?1:std::clamp(1-a.bright/100.f,.15f,1.f);if(a.vector){auto*m=model(a.model,a.frame);if(m)draw(*m,texture("textures/texturemaps_atlas.png"),gpu::transform(a.x,a.y,a.z,(4096-a.angle)*2*Pi/8192,.5f,.5f,.5f),view.worldScale,0,shade);}else{auto&t=sprite(a);float yaw=std::atan2(view.headWorld[12]/view.worldScale-a.x,view.headWorld[14]/view.worldScale-a.z);auto matrix=gpu::transform(a.x,a.y,a.z,yaw,(a.flip?-1:1)*a.width,a.height,1);if(a.additive){glEnable(GL_BLEND);glBlendFunc(GL_SRC_ALPHA,GL_ONE);glDepthMask(GL_FALSE);}draw(unitQuad,t,matrix,view.worldScale,0,shade);if(a.additive){glDisable(GL_BLEND);glDepthMask(GL_TRUE);}}}
            if(water.count){copyScene();glDepthMask(GL_TRUE);draw(water,floorAtlas,Identity,view.worldScale,4,1,1,&texture("textures/water_shade.lut.png"));}
            if(hasWeapon){auto*m=model(weapon.model,weapon.frame);float yaw=(4096-weapon.angle+playerAngle)*2*Pi/8192;Matrix mount=view.trackedWeapon?view.weaponWorld:gpu::multiply(view.headWorld,gpu::transform(.12f,-.25f,-.32f));Matrix matrix=gpu::multiply(mount,gpu::transform(weaponMount.x,weaponMount.y,0,yaw,.22f,.22f,.22f));if(m){draw(*m,texture("textures/texturemaps_atlas.png"),matrix,1);++stats.weaponDraws;if(view.trackedWeapon&&panel.kind==Panel::Gameplay){
                // A physical 28 cm segment on the exact tracked -Z aim ray.
                // Begin just beyond conservative original-mesh muzzle bounds
                // so it is visible without disabling world/weapon depth.
                auto guide=gpu::multiply(view.weaponWorld,gpu::transform(0,0,-weaponMount.distance));draw(laser,texture("#aim-guide"),guide,1);
            }}}
        }
        if(underwater&&view.headWorld[13]<waterY*view.worldScale&&(panel.kind==Panel::Gameplay||panel.kind==Panel::Pause)){
            copyScene();glDisable(GL_DEPTH_TEST);glDepthMask(GL_FALSE);glUniformMatrix4fv(loc("vp"),1,GL_FALSE,Identity.data());draw(unitQuad,texture("#white"),gpu::transform(0,0,0,0,2,2,1),1,5,1,1,&texture("textures/water_under.lut.png"));glUniformMatrix4fv(loc("vp"),1,GL_FALSE,view.viewProjection.data());
        }
        glDisable(GL_DEPTH_TEST);glDepthMask(GL_FALSE);glEnable(GL_BLEND);glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
        if(panel.kind==Panel::Gameplay){plane(texture("#black"),view.headWorld,0,-.73f,-2.23f,2.1f,.30f,.80f);plane(texture("hud/bar.png"),view.headWorld,0,-.73f,-2.22f,2.05f,.14f,.20f);draw(hudMesh,texture("menu/endfont.png"),view.headWorld,1);}
        else {plane(texture("#black"),view.headWorld,0,0,-2.23f,2.24f,1.7f,.96f);if(panel.kind==Panel::Title)plane(texture("menu/background_rgba.png"),view.headWorld,0,0,-2.22f,2.05f,1.64f);draw(panelText,texture("menu/endfont.png"),view.headWorld,1);++stats.panelDraws;}
        glDepthMask(GL_TRUE);glDisable(GL_BLEND);glBindVertexArray(0);glUseProgram(0);glActiveTexture(GL_TEXTURE0);++stats.eyeFrames;
    }
};
Renderer::Renderer():impl(std::make_unique<Impl>()){}
Renderer::~Renderer()=default;
void Renderer::loadAssets(const std::filesystem::path&root){impl->root=root;impl->glf=json(root/"glf.json");impl->font=json(root/"menu/endfont.json");impl->loadAtlases();impl->loadBackdropAndWater();impl->texture("menu/endfont.png");impl->texture("hud/bar.png");impl->texture("menu/background_rgba.png");impl->texture("textures/texturemaps_atlas.png");}
void Renderer::loadLevel(int index){impl->clearLevel();impl->levelIndex=index;impl->level=json(impl->root/("levels/"+std::string(1,char('a'+index))+".json"));impl->zoneCount=impl->level.at("numZones");impl->buildLevel();}
void Renderer::sync(){impl->synchronize();}
void Renderer::setPanel(const Panel&panel){if(impl->panel.kind==panel.kind&&impl->panel.caption==panel.caption&&impl->panel.lines==panel.lines&&impl->panel.selection==panel.selection)return;impl->panel=panel;if(!impl->root.empty())impl->makePanel();}
void Renderer::drawEye(const RenderView&view){impl->eye(view);}
float Renderer::muzzleDistance()const{return impl->weaponMount.distance;}
const RenderStats&Renderer::stats()const{return impl->stats;}
}
