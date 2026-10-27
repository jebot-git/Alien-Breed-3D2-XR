#include "original.hpp"
#include <nlohmann/json.hpp>
#include <iostream>
using Json=nlohmann::json;
int main(int argc,char**argv){
    try{
        if(argc!=3)throw std::runtime_error("Pass original level state and expected reference frames");
        std::ifstream input(argv[1],std::ios::binary);if(!input)throw std::runtime_error("Missing original game data");
        input.read(reinterpret_cast<char*>(Mem::RAM.data()),Mem::RAM_SIZE);Mem::cursor=input.gcount();
        std::ifstream expectedFile(argv[2]);Json expected;expectedFile>>expected;
        Hires::headless=true;Hires::headlessStop=false;Hires::loopFrameLimit=80;
        int frame=0;
        auto key=[](int binding,bool value){Mem::wb(TablesBss::KeyMap_vb+Mem::ub(binding),value?255:0);};
        key(ControlloopData::forward_key,true);key(ControlloopData::fire_key,false);
        Hires::markVisibleAndWorry();
        Hires::frameSync=[&](){
            ++frame;
            int gun=Mem::l(PlayerBss::Plr1_ObjectPtr_l)+Defs::ENT_NEXT_2;
            Json state={{"x",Mem::l(PlayerBss::Plr1_XOff_l)},{"y",Mem::l(PlayerBss::Plr1_YOff_l)},
                {"z",Mem::l(PlayerBss::Plr1_ZOff_l)},{"height",Mem::l(PlayerBss::Plr1_Height_l)},
                {"angle",Mem::uw(PlayerBss::Plr1_AngPos_w)},{"zone",Mem::uw(PlayerBss::Plr1_Zone_w)},
                {"health",Mem::uw(PlayerBss::Plr1_Health_w)},{"gun",Mem::ub(PlayerBss::Plr1_GunSelected_b)}};
            for(auto it=state.begin();it!=state.end();++it)if(it.value()!=expected.at(frame).at(it.key())){
                std::ofstream dump("artifacts/native-after-one.ram",std::ios::binary);dump.write(reinterpret_cast<char*>(Mem::RAM.data()),Mem::cursor);dump.close();
                std::cerr<<state.dump()<<" vs "<<expected.at(frame).dump()<<"\n";
                throw std::runtime_error("Frame "+std::to_string(frame)+" "+it.key()+": native "+it.value().dump()+", reference "+expected.at(frame).at(it.key()).dump());
            }
            if(Mem::uw(gun+8)!=expected.at(frame).at("held").at("model") || Mem::uw(gun+10)!=expected.at(frame).at("held").at("frame"))throw std::runtime_error("Original weapon animation differs at frame "+std::to_string(frame));
            int records=Mem::l(LevelBss::Lvl_ObjectDataPtr_l),points=Mem::l(LevelBss::Lvl_ObjectPointsPtr_l);
            const auto& actors=expected.at(frame).at("entities");
            for(size_t i=0;i<actors.size();i++){
                int p=records+int(i)*Defs::ObjT_SizeOf_l,id=Mem::w(p);
                Json actor={{"address",p},{"id",id},{"type",Mem::ub(p+Defs::ObjT_TypeID_b)},
                    {"definition",Mem::ub(p+Defs::EntT_Type_b)},{"x",Mem::w(points+id*8)},
                    {"z",Mem::w(points+id*8+4)},{"height",Mem::w(p+4)},{"zone",Mem::w(p+Defs::ObjT_ZoneID_w)},
                    {"model",Mem::uw(p+8)},{"frame",Mem::uw(p+10)},{"angle",Mem::uw(p+Defs::EntT_CurrentAngle_w)},
                    {"hitPoints",Mem::ub(p+Defs::EntT_HitPoints_b)},{"upper",Mem::b(p+Defs::ShotT_InUpperZone_b)!=0}};
                if(actor!=actors.at(i))throw std::runtime_error("Actor "+std::to_string(i)+" diverged on tick "+std::to_string(frame)+": "+actor.dump()+" vs "+actors.at(i).dump());
            }
            key(ControlloopData::forward_key,frame<40);key(ControlloopData::fire_key,frame>=40&&frame<70);
        };
        Hires::game_main_loop();
        if(frame!=80)throw std::runtime_error("Native loop ended early");
        std::cout<<"PASS 80 native original ticks: movement, collision, pickups, health, gun state and original polygon animation match reference\n";
    }catch(const std::exception& error){std::cerr<<error.what()<<"\n";return 1;}
}
