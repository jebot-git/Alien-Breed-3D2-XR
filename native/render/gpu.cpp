#include "gpu.hpp"
#include <png.h>
#include <cmath>
#include <cstring>
#include <stdexcept>
namespace ab3d2::gpu {
Image png(const std::filesystem::path &path){
    png_image file{};file.version=PNG_IMAGE_VERSION;
    if(!png_image_begin_read_from_file(&file,path.c_str()))throw std::runtime_error("Cannot read original PNG: "+path.string());
    file.format=PNG_FORMAT_RGBA;Image result;result.width=file.width;result.height=file.height;result.pixels.resize(PNG_IMAGE_SIZE(file));
    if(!png_image_finish_read(&file,nullptr,result.pixels.data(),0,nullptr)){std::string error=file.message;png_image_free(&file);throw std::runtime_error(error+": "+path.string());}
    png_image_free(&file);return result;
}
Texture texture(const Image &image,bool repeat){
    Texture result;result.width=image.width;result.height=image.height;glGenTextures(1,&result.id);glBindTexture(GL_TEXTURE_2D,result.id);
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER,0);glPixelStorei(GL_UNPACK_ALIGNMENT,1);glPixelStorei(GL_UNPACK_ROW_LENGTH,0);
    glPixelStorei(GL_UNPACK_SKIP_ROWS,0);glPixelStorei(GL_UNPACK_SKIP_PIXELS,0);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA8,image.width,image.height,0,GL_RGBA,GL_UNSIGNED_BYTE,image.pixels.data());
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,repeat?GL_REPEAT:GL_CLAMP_TO_EDGE);glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,repeat?GL_REPEAT:GL_CLAMP_TO_EDGE);
    return result;
}
Mesh mesh(const std::vector<Vertex>&vertices,bool dynamic){
    Mesh m;m.count=vertices.size();glGenVertexArrays(1,&m.vao);glGenBuffers(1,&m.vbo);glBindVertexArray(m.vao);glBindBuffer(GL_ARRAY_BUFFER,m.vbo);
    glBufferData(GL_ARRAY_BUFFER,vertices.size()*sizeof(Vertex),vertices.data(),dynamic?GL_DYNAMIC_DRAW:GL_STATIC_DRAW);
    int sizes[]={3,2,3,4,3};size_t offsets[]={0,3,5,8,12};
    for(unsigned i=0;i<5;++i){glEnableVertexAttribArray(i);glVertexAttribPointer(i,sizes[i],GL_FLOAT,GL_FALSE,sizeof(Vertex),reinterpret_cast<void*>(offsets[i]*sizeof(float)));}
    glBindVertexArray(0);return m;
}
void update(const Mesh&m,const std::vector<Vertex>&v){glBindBuffer(GL_ARRAY_BUFFER,m.vbo);glBufferSubData(GL_ARRAY_BUFFER,0,v.size()*sizeof(Vertex),v.data());}
void destroy(Mesh&m){if(m.vbo)glDeleteBuffers(1,&m.vbo);if(m.vao)glDeleteVertexArrays(1,&m.vao);m={};}
unsigned program(){
    const char*vs=R"(#version 330 core
layout(location=0)in vec3 position;layout(location=1)in vec2 texcoord;layout(location=2)in vec3 lightSource;
layout(location=3)in vec4 region;layout(location=4)in vec3 tile;
uniform mat4 vp,model;uniform float scale;uniform int mode;uniform sampler2D points;
out vec2 uv;out float bright;out vec3 world;flat out vec4 rect;flat out vec3 subtile;
void main(){vec4 p=model*vec4(position,1);p.xyz*=scale;world=p.xyz;gl_Position=vp*p;uv=texcoord;rect=region;subtile=tile;bright=0;
if(lightSource.x>=0){float raw=abs(texelFetch(points,ivec2(int(lightSource.y),int(lightSource.x)),0).r)-300+lightSource.z;
bright=mode==1?2*(mod(raw+128,256)-128):raw;}})";
    const char*fs=R"(#version 330 core
in vec2 uv;in float bright;in vec3 world;flat in vec4 rect;flat in vec3 subtile;out vec4 color;
uniform sampler2D image,palette;uniform int mode;uniform float shade,opacity,worldScale;uniform vec4 tint;uniform vec3 camera,forward;
void main(){vec4 sampleColor;float depth=max(0,dot(world-camera,forward))/max(.001,worldScale);
if(mode==1||mode==2){ivec2 at=ivec2(rect.xy+vec2(mod(floor(fract(uv.x)*subtile.y)+subtile.x,rect.z),floor(fract(uv.y)*rect.w)));
float index=floor(texelFetch(image,at,0).r*255+.5);float bank=mode==1?min(31,ceil(clamp(mod(bright+128,256)-128+floor(depth*.5),0,64)*.5)):clamp(floor(bright+floor(depth*.125)),0,30);
ivec2 size=textureSize(palette,0);sampleColor=texelFetch(palette,ivec2(int(index),int(bank+subtile.z*32)),0);
}else sampleColor=texture(image,uv);
if(sampleColor.a<.02)discard;color=vec4(sampleColor.rgb*shade,sampleColor.a*opacity)*tint;})";
    auto compile=[](unsigned kind,const char*source){unsigned s=glCreateShader(kind);glShaderSource(s,1,&source,nullptr);glCompileShader(s);int ok;glGetShaderiv(s,GL_COMPILE_STATUS,&ok);if(!ok){char log[4096]{};glGetShaderInfoLog(s,sizeof(log),nullptr,log);glDeleteShader(s);throw std::runtime_error(std::string("Native renderer shader: ")+log);}return s;};
    auto v=compile(GL_VERTEX_SHADER,vs),f=compile(GL_FRAGMENT_SHADER,fs);unsigned p=glCreateProgram();glAttachShader(p,v);glAttachShader(p,f);glLinkProgram(p);glDeleteShader(v);glDeleteShader(f);int ok;glGetProgramiv(p,GL_LINK_STATUS,&ok);if(!ok){char log[4096]{};glGetProgramInfoLog(p,sizeof(log),nullptr,log);glDeleteProgram(p);throw std::runtime_error(std::string("Native renderer link: ")+log);}return p;
}
Matrix multiply(const Matrix&a,const Matrix&b){Matrix m{};for(int c=0;c<4;++c)for(int r=0;r<4;++r)for(int k=0;k<4;++k)m[c*4+r]+=a[k*4+r]*b[c*4+k];return m;}
Matrix transform(float x,float y,float z,float yaw,float sx,float sy,float sz){float c=std::cos(yaw),s=std::sin(yaw);return {c*sx,0,-s*sx,0, 0,sy,0,0, s*sz,0,c*sz,0, x,y,z,1};}
std::vector<int> triangulate(const std::vector<std::array<float,2>>&p){
    std::vector<int> ring,tri;float area=0;for(size_t i=0,j=p.size()-1;i<p.size();j=i++)area+=p[j][0]*p[i][1]-p[i][0]*p[j][1];
    if(p.size()<3)return tri;for(size_t i=0;i<p.size();++i)ring.push_back(area>0?int(i):int(p.size()-1-i));
    auto cross=[&](int a,int b,int c){return (p[b][0]-p[a][0])*(p[c][1]-p[a][1])-(p[b][1]-p[a][1])*(p[c][0]-p[a][0]);};
    for(int guard=0;ring.size()>2&&guard<int(p.size()*p.size());++guard){bool clipped=false;
        for(size_t i=0;i<ring.size();++i){int a=ring[(i+ring.size()-1)%ring.size()],b=ring[i],c=ring[(i+1)%ring.size()];if(cross(a,b,c)<1e-6)continue;bool contains=false;
            for(int x:ring)if(x!=a&&x!=b&&x!=c&&cross(a,b,x)>=-1e-6&&cross(b,c,x)>=-1e-6&&cross(c,a,x)>=-1e-6){contains=true;break;}
            if(contains)continue;tri.insert(tri.end(),{a,b,c});ring.erase(ring.begin()+i);clipped=true;break;}
        if(!clipped){for(size_t i=0;i<ring.size();++i){int a=ring[(i+ring.size()-1)%ring.size()],b=ring[i],c=ring[(i+1)%ring.size()];if(std::abs(cross(a,b,c))<1e-6){ring.erase(ring.begin()+i);clipped=true;break;}}if(!clipped)break;}}
    return tri;
}
}
