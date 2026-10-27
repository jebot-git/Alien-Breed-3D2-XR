#pragma once
#include <GL/glew.h>
#include <array>
#include <filesystem>
#include <vector>
#include "render.hpp"
namespace ab3d2::gpu {
struct Image {int width=0,height=0;std::vector<unsigned char> pixels;};
Image png(const std::filesystem::path &);
struct Texture {unsigned id=0;int width=0,height=0;};
Texture texture(const Image &,bool repeat=false);
struct Vertex {float x,y,z,u,v;float lightZone=-1,lightSlot=0,lightOffset=0;float regionX=0,regionY=0,regionW=1,regionH=1;float from=0,tileWidth=1,palette=0;};
struct Mesh {unsigned vao=0,vbo=0;int count=0;};
Mesh mesh(const std::vector<Vertex>&,bool dynamic=false);
void update(const Mesh &,const std::vector<Vertex>&);
void destroy(Mesh &);
unsigned program();
Matrix multiply(const Matrix&,const Matrix&);
Matrix transform(float x,float y,float z,float yaw=0,float sx=1,float sy=1,float sz=1);
std::vector<int> triangulate(const std::vector<std::array<float,2>>&);
}
