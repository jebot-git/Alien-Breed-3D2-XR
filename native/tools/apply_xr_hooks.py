#!/usr/bin/env python3
"""Apply small, explicit native input hooks after an offline core refresh."""
from pathlib import Path
ROOT=Path(__file__).resolve().parents[2];core=ROOT/'native/src/core'
p=core/'Player.cpp';s=p.read_text()
if '// Native tracked input' not in s:
 s='#include "controls.hpp"\n// Native tracked input: original movement/friction/gravity/collision remain authoritative.\n'+s
 a='(a4=Mem::l(j_add(a0,Defs::PlrT_ZonePtr_l)));';assert a in s;s=s.replace(a,'ab3d2::controls::crouch(a0);\n'+a,1)
 a='if((Mem::b(PlayerBss::Plr_Decelerate_b) != 0)) {\nMem::wl(j_add(a0,Defs::PlrT_SnapXSpdVal_l)';assert a in s;s=s.replace(a,'ab3d2::controls::accelerate(a0,d6,d7);\n'+a,1)
 a='Mem::wl(j_add(a0,Defs::PlrT_SnapXOff_l),j_add(Mem::l(j_add(a0,Defs::PlrT_SnapXOff_l)),d6));';assert a in s;s=s.replace(a,'ab3d2::controls::roomMove(a0,d6,d7);\n'+a,1)
 a='''if((d0 > d1)) {
(d0-=1024);
}
else {
(d0+=1024);
}''';assert a in s;s=s.replace(a,'d0=ab3d2::controls::heightStep(a0,d0,d1);',1);p.write_text(s)
p=core/'Newplayershoot.cpp';s=p.read_text()
if '// Native tracked aim' not in s:
 s='#include "controls.hpp"\n// Native tracked aim: original ammunition, delays, spread, damage and effects remain authoritative.\n'+s
 a='void Plr1_Shot(){\n';assert a in s;s=s.replace(a,a+'ab3d2::controls::AimScope trackedAim;\n',1)
 a='int32_t v=Mem::ub(a1);';assert a in s;s=s.replace(a,'int32_t v=p1&&ab3d2::controls::aimed()?(ab3d2::controls::intersects(a0)?255:0):Mem::ub(a1);',1)
 a='int32_t d6b=M68k::setw(0,Mem::uw(j_add(a2,((d5 & 0xFFFF) * 2))));';assert a in s;s=s.replace(a,a+'\nif(p1&&ab3d2::controls::aimed())d6b=ab3d2::controls::distance(a0);',1)
 a='if((int16_t(d2v) > int16_t(d6b)))';assert a in s;s=s.replace(a,'if(!(p1&&ab3d2::controls::aimed())&&(int16_t(d2v) > int16_t(d6b)))',1)
 a='if((Mem::w(j_add(j_add(a5,Defs::BulT_IsHitScan_l),2)) == 0)) {'
 s=s.replace(a,'if(p==1&&ab3d2::controls::aimed())Mem::ww(NewanimsData::bulyspd,ab3d2::controls::verticalSpeed(Mem::uw(NewplayershootData::BulletSpd)));\n'+a,2)
 a='Mem::wl(ObjectmoveData::oldy,d0l);';assert a in s;s=s.replace(a,'if(p==1&&ab3d2::controls::aimed())d0l=ab3d2::controls::originY();\n'+a,1)
 a='Mem::wl(ObjectmoveData::newy,d1l);';assert a in s;s=s.replace(a,'if(p==1&&ab3d2::controls::aimed())d1l=Mem::l(ObjectmoveData::oldy)+ab3d2::controls::rayYStep();\n'+a,1)
 a='Newplayershoot::setupBulletMove(zonePtr);\nwhile(true){';assert a in s;s=s.replace(a,'Newplayershoot::setupBulletMove(zonePtr);\nwhile(!(p==1&&ab3d2::controls::verticalRay())){',1)
 a='if((int16_t(d0) >= (20 * 128))) (d0=M68k::setw(d0,(20 * 128)));\nif((int16_t(d0) <= (-(20) * 128))) (d0=M68k::setw(d0,(-(20) * 128)));';assert a in s;s=s.replace(a,'if(!(p==1&&ab3d2::controls::aimed())){\n'+a+'\n}',1)
 # Preserve projectile speed while directing its horizontal component along the tracked pitch.
 a='Mem::wl(j_add(a0,Defs::ShotT_VelocityZ_w),d2);';assert a in s;s=s.replace(a,a+'''\nif(p==1&&ab3d2::controls::aimed()){
 float horizontal=std::sqrt(std::max(0.f,1-ab3d2::controls::input.direction[1]*ab3d2::controls::input.direction[1]));
 Mem::wl(a0+Defs::ShotT_VelocityX_w,int(std::lround(Mem::l(a0+Defs::ShotT_VelocityX_w)*horizontal)));
 Mem::wl(a0+Defs::ShotT_VelocityZ_w,int(std::lround(Mem::l(a0+Defs::ShotT_VelocityZ_w)*horizontal)));
}''',1);p.write_text(s)
