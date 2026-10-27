#!/usr/bin/env python3
"""Refresh native scalar state bookkeeping; never called by the normal build."""
from pathlib import Path
import re,hashlib,json,sys,shutil,zlib,struct
ROOT=Path(__file__).resolve().parents[2]
header=(ROOT/'native/src/core/original.hpp').read_text();scope=None;fields=[]
for line in header.splitlines():
 m=re.fullmatch(r'namespace (\w+) \{',line)
 if m:scope=m[1]
 if line=='}':scope=None
 m=re.match(r'inline (int32_t|int64_t|int16_t|int8_t|char16_t|float|double|bool) (\w+)=',line)
 if scope and m:fields.append(scope+'::'+m[2])
host_arrays=['audLC','audLEN','audPER','audVOL','dmaLC','dmaLEN','dmaTrig']
fields.extend('CustomChips::'+a+'['+str(n)+']' for a in host_arrays for n in range(4))
fields.extend('CustomChips::'+a for a in ['dmacon','ciaaPra','joy0dat','joy1dat','mouseLeftPressed','mouseRightPressed','fire1Pressed'])
layout=hashlib.sha256('\n'.join(line for line in header.splitlines() if line.startswith('inline constexpr ')).encode()).hexdigest()
code=['#include "original.hpp"','#include "core_state.hpp"','#include <bit>','namespace ab3d2 {',
'''template<class T> uint64_t packScalar(T value){
 if constexpr(std::is_same_v<T,bool>)return value?1:0;
 else if constexpr(std::is_integral_v<T>)return uint64_t(std::make_unsigned_t<T>(value));
 else if constexpr(sizeof(T)==4)return std::bit_cast<uint32_t>(value);
 else return std::bit_cast<uint64_t>(value);
}
template<class T> void unpackScalar(T& value,uint64_t bits){
 if constexpr(std::is_integral_v<T>)value=T(bits);
 else if constexpr(sizeof(T)==4)value=std::bit_cast<T>(uint32_t(bits));
 else value=std::bit_cast<T>(bits);
}''', 'const char* coreLayoutId(){return "'+layout+'";}','std::vector<uint64_t> captureCoreGlobals(){return {']
code.extend('packScalar('+f+'),' for f in fields);code.extend(['};}','void restoreCoreGlobals(const std::vector<uint64_t>& values){','if(values.size()!='+str(len(fields))+')throw std::runtime_error("Incompatible native scalar state");','size_t i=0;'])
code.extend('unpackScalar('+f+',values[i++]);' for f in fields);code.extend(['}','}'])
(ROOT/'native/src/core/globals.cpp').write_text('\n'.join(code)+'\n')
print('Native state fields',len(fields),'layout',layout)
if '--stage-original-data' in sys.argv:
 out=ROOT/'assets/native';out.mkdir(parents=True,exist_ok=True)
 constants=json.loads((ROOT/'artifacts/native-oracle/constants-0.json').read_text())
 records=[]
 for level in range(16):
  data=(ROOT/f'artifacts/native-oracle/level-{level}.ram').read_bytes();shutil.copyfile(ROOT/f'artifacts/native-oracle/level-{level}.ram',out/f'level-{level}.ram')
  records.append(dict(level=level,file=f'level-{level}.ram',size=len(data),crc32=zlib.crc32(data),zones=struct.unpack_from('>H',data,constants['ab3d2.bss.LevelBss.Lvl_NumZones_w'])[0],chips=json.loads((ROOT/f'artifacts/native-oracle/chips-{level}.json').read_text())))
 (out/'manifest.json').write_text(json.dumps(dict(version=1,layout=layout,source='mheyer32/alienbreed3d2@86abb5c',reference='guillaumemonet/ab3d2-tkg-java@3090d9f',levels=records),indent=2)+'\n')
