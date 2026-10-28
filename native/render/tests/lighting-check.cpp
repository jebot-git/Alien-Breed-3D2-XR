/* Offline source-oracle input/output, independent of SDL/OpenGL/gameplay writes.
 * lighting-reference.py runs the preserved LightRings source over these inputs.
 * Java is exclusively an optional development oracle, never a product dependency. */
#include "lighting.hpp"
#include "original.hpp"
#include <fstream>
#include <iostream>
#include <set>
#include <tuple>
using Json=nlohmann::json;
static void word(std::ostream&out,int v){for(int shift:{24,16,8,0})out.put(uint32_t(v)>>shift);}
int main(int argc,char**argv){try{
 if(argc!=5&&argc!=6)throw std::runtime_error("assets snapshots oracle-input native-output [assembly-pairs]");
 std::ofstream input(argv[3],std::ios::binary),actual(argv[4],std::ios::binary);std::ofstream asmPairs;if(argc==6)asmPairs.open(argv[5],std::ios::binary);word(input,16);size_t cases=0;std::array<int8_t,1792>guff{};std::ifstream guffFile(std::filesystem::path(argv[1])/"tables/guff.bin",std::ios::binary);guffFile.read(reinterpret_cast<char*>(guff.data()),guff.size());if(guffFile.gcount()!=guff.size())throw std::runtime_error("Missing original guff light table");
 for(int li=0;li<16;++li){Json level;std::ifstream(std::filesystem::path(argv[1])/"levels"/(std::string(1,'a'+li)+".json"))>>level;
  std::ifstream memory(std::filesystem::path(argv[2])/("level-"+std::to_string(li)+".ram"),std::ios::binary);memory.read(reinterpret_cast<char*>(Mem::RAM.data()),Mem::RAM_SIZE);if(memory.gcount()<1000000)throw std::runtime_error("Missing original RAM fixture");
  int zones=level["numZones"],base=Mem::l(TablesBss::PointBrightsPtr_l),pointsBase=Mem::l(LevelBss::Lvl_PointsPtr_l);
  std::vector<float> brightness(zones*40);for(int i=0;i<zones*40;++i){int raw=Mem::w(base+i*2),value=int8_t(raw);unsigned high=uint16_t(raw)>>8;if(value>=0&&high){int anim=high&15,blend=(high>>4)+1;if(anim)value=int8_t(value+(int16_t((Mem::w(AnimBss::Anim_BrightTable_vw+anim*2-2)-value)*blend)>>4));}int n=(value*397)>>8;if(n<0)n-=600;brightness[i]=int16_t(n+300);}
  std::vector<std::array<int,2>> points(level["points"].size());for(size_t i=0;i<points.size();++i)points[i]={Mem::w(pointsBase+i*4),Mem::w(pointsBase+i*4+2)};
  std::array<int16_t,5120>sine{};for(size_t i=0;i<sine.size();++i)sine[i]=Mem::w(TablesData::SinCosTable_vw+i*2);
  std::set<std::tuple<int,int,int,bool>> positions;
  for(int z=0;z<zones;++z){auto&e=level["zones"][z]["edges"];if(e.empty())continue;int64_t x=0,pz=0;for(auto&edge:e){x+=edge["x"].get<int>();pz+=edge["z"].get<int>();}for(bool upper:{false,true})positions.emplace(x/int(e.size()),pz/int(e.size()),z,upper);}
  for(auto&o:level["objects"]){int z=o.value("zone",-1);if(z<0||z>=zones)continue;for(bool upper:{false,true})positions.emplace(o.value("x",0),o.value("z",0),z,upper);}
  word(input,points.size());for(auto&p:points){word(input,p[0]);word(input,p[1]);}
  word(input,zones);for(auto&z:level["zones"]){for(auto&p:z["borderPointsRaw"])word(input,p);word(input,z["edgeList"].size());for(auto&e:z["edgeList"])word(input,e);}
  word(input,level["edges"].size());for(auto&e:level["edges"]){word(input,e["dx"]);word(input,e["dz"]);word(input,e["join"]);}
  for(auto v:brightness)word(input,int(v));for(auto v:sine)word(input,v);
  word(input,positions.size());for(auto[x,z,zone,upper]:positions){word(input,x);word(input,z);word(input,zone);word(input,upper);auto r=ab3d2::lighting::rings(level,brightness,points,sine,x,z,zone,upper);actual.write(reinterpret_cast<char*>(r.data()),r.size());if(argc==6){auto raw=ab3d2::lighting::rings(level,brightness,points,sine,x,z,zone,upper,false,true);asmPairs.write(reinterpret_cast<char*>(raw.data()),raw.size());asmPairs.write(reinterpret_cast<char*>(r.data()),r.size());}auto poly=ab3d2::lighting::polygon(r);for(auto v:poly)actual.put(int(v));auto zoneOnly=ab3d2::lighting::rings(level,brightness,points,sine,x,z,zone,upper,true);actual.write(reinterpret_cast<char*>(zoneOnly.data()),zoneOnly.size());for(int bright:{-100,-16,0,16,64,255}){auto levels=ab3d2::lighting::sprite(zoneOnly,((x+z)*2)&8191,bright,upper,guff);for(auto v:levels)actual.put(int(v));}++cases;}
 }
 std::cout<<"Native original lighting: "<<cases<<" positions across all 16 retail levels, full and sprite-only rings\n";
}catch(const std::exception&e){std::cerr<<e.what()<<'\n';return 1;}}
