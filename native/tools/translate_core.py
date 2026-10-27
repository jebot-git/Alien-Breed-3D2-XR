#!/usr/bin/env python3
"""Offline migration helper for the literal original-code reference.
The product builds checked-in C++; Python/Java are not runtime dependencies.
Unsupported runtime services fail explicitly until replaced by native hosts.
"""
from pathlib import Path
import json,re,sys
import javalang as J
from javalang import tree as T
# javalang 0.13 drops unary operators before casts (e.g. -(short)reg).
# Preserve them explicitly; otherwise original neg.w, bobbing and lighting invert.
import inspect,textwrap
parser_source=textwrap.dedent(inspect.getsource(J.parser.Parser.parse_expression_3))
parser_source=parser_source.replace("return tree.Cast(type=cast_target,\n                                 expression=expression)","cast = tree.Cast(type=cast_target, expression=expression)\n                cast.prefix_operators = prefix_operators\n                return cast")
if "cast.prefix_operators" not in parser_source:raise RuntimeError("Review changed parser before migration")
parser_scope=dict(vars(J.parser));exec(parser_source,parser_scope)
J.parser.Parser.parse_expression_3=parser_scope['parse_expression_3']
ROOT=Path(__file__).resolve().parents[2]
SOURCE=Path(sys.argv[1]) if len(sys.argv)>1 else ROOT.parent/'Alien-Breed-3D2-Java/src'
OUT=ROOT/'native/src/core';OUT.mkdir(parents=True,exist_ok=True)
constants=json.loads((ROOT/'artifacts/native-oracle/constants-0.json').read_text())
classes={}
for p in SOURCE.rglob('*.java'):
 try:tree=J.parse.parse(p.read_text())
 except Exception:continue
 for cls in tree.types:
  if isinstance(cls,T.ClassDeclaration):classes[cls.name]=(tree,cls,p)
# Preserve the corrected GPU boundary discovered during the source audit.
import subprocess
hires=subprocess.check_output(['git','show','reference/java-host-audit:upstream/faithful/src/ab3d2/Hires.java'],cwd=ROOT,text=True)
ht=J.parse.parse(hires);classes['Hires']=(ht,ht.types[0],Path('reference/java-host-audit/Hires.java'))
selected={'ScreenC','DrawC','ZoneEdgePvs','TablesData','Plr1control','Plr2control','Vid','SysTimer','Ai','SystemC','Hires','M68k','Macros','Fall','Objectmove','Orderzones','Newanims','Newaliencontrol','Newplayershoot','Player','Transform','Sys','Music','Inventory','Message','DevMacros','DevInst','GameProgress','GameC'}
only_methods={'ScreenC':{'Vid_LoadMainPalette','LoadRGB32','hostColor'},'DrawC':{'Draw_CalcPropTextSplit','Draw_IsPrintable'}}
fields={};methods={};imports={}
for name,(tree,cls,p) in classes.items():
 fields[name]={d.name:f for f in cls.fields for d in f.declarators}
 methods[name]={m.name:m for m in cls.methods}
 imports[name]={}
 for i in tree.imports:
  if i.static:
   bits=i.path.split('.');owner=bits[-1] if i.wildcard else bits[-2]
   if i.wildcard:
    for n in list(fields.get(owner,{}))+list(methods.get(owner,{})):imports[name][n]=owner
   else:imports[name][bits[-1]]=owner
# Resolve wildcard imports only after all declarations have been indexed.
for name,(tree,cls,p) in classes.items():
 for i in tree.imports:
  if i.static and i.wildcard:
   owner=i.path.split('.')[-1]
   for n in list(fields.get(owner,{}))+list(methods.get(owner,{})):imports[name][n]=owner
primitive={'int':'int32_t','long':'int64_t','short':'int16_t','byte':'int8_t','char':'char16_t','boolean':'bool','float':'float','double':'double','void':'void'}
def typ(t,extra=0):
 if t is None:return 'void'
 n=t.name
 while getattr(t,'sub_type',None):t=t.sub_type;n=t.name
 base=primitive.get(n,{'String':'std::string','Runnable':'std::function<void()>','Display':'DisplayHandle*','StringBuilder':'JStringBuilder','PutCh':'std::function<void(int32_t)>'}.get(n,'int32_t'))
 for _ in range(len(t.dimensions or [])+extra):base='std::vector<'+base+'>'
 return base

def cname(q):
 if not q:return ''
 bits=q.split('.')
 for i,b in enumerate(bits):
  if b in classes or b in ['CustomChips','DosLib']:return b+'::'+'::'.join(bits[i+1:]) if i+1<len(bits) else b
 return q

class Emitter:
 def __init__(self,cls,method):
  self.cls=cls;self.method=method;self.locals={p.name for p in method.parameters}
  for _,n in method:
   if isinstance(n,(T.LocalVariableDeclaration,T.VariableDeclaration)):self.locals.update(x.name for x in n.declarators)
  self.called=set()
 def ident(self,n):
  if n in self.locals:return n
  if n in fields[self.cls]:return self.cls+'::'+n
  if n in imports[self.cls]:return imports[self.cls][n]+'::'+n
  return n
 def expr(self,n):
  if n is None:return ''
  if isinstance(n,str):return n
  if isinstance(n,list):return ','.join(self.expr(x) for x in n)
  result=self.raw(n)
  for selector in getattr(n,'selectors',[]) or []:
   if isinstance(selector,T.ArraySelector):result+='['+self.expr(selector.index)+']'
   elif isinstance(selector,T.MemberReference):result+='.'+selector.member
   elif isinstance(selector,T.MethodInvocation):result=('j_equals('+result+','+self.expr(selector.arguments)+')') if selector.member=='equals' else result+'.'+('at' if selector.member=='charAt' else selector.member)+'('+self.expr(selector.arguments)+')'
   else:raise ValueError(('selector',type(selector)))
  for op in reversed(getattr(n,'prefix_operators',[]) or []):result=op+'('+result+')'
  for op in getattr(n,'postfix_operators',[]) or []:result='('+result+')'+op
  return result
 def raw(self,n):
  if isinstance(n,T.Literal):
   v=n.value
   if v=='null':return 'nullptr'
   if re.match(r'^0x[\da-f]+$',v,re.I) and int(v,16)>0x7fffffff:return 'int32_t('+v+'u)'
   return re.sub(r'(?<=\d)[lL]$','LL',v.replace('_','') if not v.startswith(('\"',"'")) else v)
  if isinstance(n,T.MemberReference):
   q=n.qualifier
   if n.member=='length':return 'int32_t('+(self.ident(q) if '.' not in q else cname(q))+'.size())'
   return (cname(q)+'::'+n.member if q and cname(q).split('::')[0] in (set(classes)|{'CustomChips','DosLib'}) else q+'.'+n.member) if q else self.ident(n.member)
  if isinstance(n,T.BinaryOperation):
   a,b=self.expr(n.operandl),self.expr(n.operandr)
   if n.operator in ['<<','>>','>>>']:return {'<<':'j_shl','>>':'j_shr','>>>':'j_ushr'}[n.operator]+'('+a+','+b+')'
   if n.operator in ['/','%']:return ('j_div' if n.operator=='/' else 'j_mod')+'('+a+','+b+')'
   if n.operator=='+':return 'j_add('+a+','+b+')'
   return '('+a+' '+n.operator+' '+b+')'
  if isinstance(n,T.Cast):return typ(n.type)+'('+self.expr(n.expression)+')'
  if isinstance(n,T.Assignment):
   if n.type=='>>>=':return '('+self.expr(n.expressionl)+'=j_ushr('+self.expr(n.expressionl)+','+self.expr(n.value)+'))'
   return '('+self.expr(n.expressionl)+n.type+self.expr(n.value)+')'
  if isinstance(n,T.TernaryExpression):return '('+self.expr(n.condition)+'?'+self.expr(n.if_true)+':'+self.expr(n.if_false)+')'
  if isinstance(n,T.MethodInvocation):
   q=n.qualifier;m=n.member;args=[self.expr(x) for x in n.arguments];owner=cname(q) if q else (self.cls if m in methods[self.cls] else imports[self.cls].get(m,''))
   if m=='charAt' and q:return self.ident(q)+'.at('+','.join(args)+')'
   if m=='equals' and q:return 'j_equals('+self.ident(q)+','+','.join(args)+')'
   if q in ['System.out','System.err']:return 'j_log('+','.join(args)+')'
   if q=='System':return {'arraycopy':'j_arraycopy','getProperty':'j_property','nanoTime':'j_nanoTime','currentTimeMillis':'j_currentTimeMillis'}.get(m,'j_unported')+'('+','.join(args)+')'
   if q=='Boolean' and m=='getBoolean':return 'false'
   if q in ['Integer','Long'] and m in ['getInteger','getLong']:return args[-1] if len(args)>1 else '0'
   if q=='Integer' and m in ['toHexString','toString']:return 'std::to_string('+','.join(args)+')'
   if q=='Math':return {'min':'j_min','max':'j_max','abs':'j_abs'}.get(m,'std::'+m)+'('+','.join(args)+')'
   if q in ['java.util.Arrays','Arrays']:return 'j_'+m+'('+','.join(args)+')'
   if q=='Thread':return 'j_thread()'
   if q=='String' and m=='format':return args[0]
   if m=='run' and q.endswith('frameSync'):return self.ident('frameSync')+'()'
   if q in self.locals and m=='shouldClose':return q+'->shouldClose()'
   if q and owner.split('::')[0] not in (set(classes)|{'CustomChips','DosLib'}):
    return self.ident(q)+'.'+m+'('+','.join(args)+')'
   self.called.add((owner,m));return (owner+'::' if owner else '')+(m+'_fn' if m in fields.get(owner,{}) else m)+'('+','.join(args)+')'
  if isinstance(n,T.ArrayInitializer):return '{'+','.join(self.expr(x) for x in n.initializers)+'}'
  if isinstance(n,T.ArrayCreator):
   base=typ(n.type)
   if n.initializer:return 'std::vector<'+base+'>'+self.expr(n.initializer)
   if len(n.dimensions)!=1:raise ValueError('multidimensional allocation')
   return 'std::vector<'+base+'>('+self.expr(n.dimensions[0])+')'
  if isinstance(n,T.LambdaExpression):
   params=[getattr(x,'name',getattr(x,'member',str(x))) for x in n.parameters]
   return '[&]('+','.join('int32_t '+x for x in params)+'){'+(self.sequence(n.body) if isinstance(n.body,list) else 'return '+self.expr(n.body)+';')+'}'
  if isinstance(n,T.MethodReference):return cname(n.expression.member)+'::'+n.method.member
  if isinstance(n,T.ClassCreator) and n.type.name=='StringBuilder' :return 'JStringBuilder()'
  if isinstance(n,T.ClassCreator):return 'std::runtime_error('+self.expr(n.arguments[0]) +')' if n.arguments else 'std::runtime_error("original engine error")'
  raise ValueError(('expression',type(n).__name__))
 def known(self,n):
  if isinstance(n,T.MemberReference) and n.member=='headless':return '!' not in (n.prefix_operators or [])
  if isinstance(n,T.Literal) and n.value in ['true','false']:return n.value=='true'
  if isinstance(n,T.BinaryOperation) and n.operator in ['&&','||']:
   a,b=self.known(n.operandl),self.known(n.operandr)
   if n.operator=='&&':return False if a is False or b is False else True if a is True and b is True else None
   return True if a is True or b is True else False if a is False and b is False else None
  return None
 def sequence(self,seq):
  result=''
  for n in seq or []:
   result+=self.stmt(n)
   if isinstance(n,T.IfStatement) and self.known(n.condition) is True and isinstance(n.then_statement,T.ReturnStatement):break
  return result
 def loop(self,node,prefix,body,suffix=''):
  if not node.label:return prefix+body+suffix
  # An extra scope makes labeled continues exit all body locals legally in C++.
  return prefix+'{\n'+body+'\n'+node.label+'_continue:;\n}'+suffix+'\n'+node.label+'_end:;\n'
 def stmt(self,n):
  if n is None:return ''
  if isinstance(n,list):return self.sequence(n)
  if isinstance(n,T.BlockStatement):return '{\n'+self.sequence(n.statements)+'}\n'
  if isinstance(n,T.StatementExpression):return self.expr(n.expression)+';\n'
  if isinstance(n,(T.LocalVariableDeclaration,T.VariableDeclaration)):
   return ''.join(('const ' if 'final' in n.modifiers else '')+typ(n.type,len(d.dimensions or []))+' '+d.name+('='+self.expr(d.initializer) if d.initializer else '{}')+';\n' for d in n.declarators)
  if isinstance(n,T.IfStatement):
   known=self.known(n.condition)
   if known is not None:return self.stmt(n.then_statement if known else n.else_statement)
   return 'if('+self.expr(n.condition)+') '+self.stmt(n.then_statement)+('else '+self.stmt(n.else_statement) if n.else_statement else '')
  if isinstance(n,T.WhileStatement):return self.loop(n,'while('+self.expr(n.condition)+')',self.stmt(n.body))
  if isinstance(n,T.DoStatement):return self.loop(n,'do ',self.stmt(n.body),'while('+self.expr(n.condition)+');\n')
  if isinstance(n,T.ReturnStatement):return 'return '+self.expr(n.expression)+';\n'
  if isinstance(n,T.BreakStatement):return ('goto '+n.goto+'_end;\n') if n.goto else 'break;\n'
  if isinstance(n,T.ContinueStatement):return ('goto '+n.goto+'_continue;\n') if n.goto else 'continue;\n'
  if isinstance(n,T.ThrowStatement):return 'throw '+self.expr(n.expression)+';\n'
  if isinstance(n,T.ForStatement):
   c=n.control
   if isinstance(c,T.EnhancedForControl):return 'for('+typ(c.var.type)+' '+c.var.declarators[0].name+':'+self.expr(c.iterable)+')'+self.stmt(n.body)
   if isinstance(c.init,T.VariableDeclaration):init=self.stmt(c.init).strip().removesuffix(';')
   else:init=self.expr(c.init)
   return self.loop(n,'for('+init+';'+self.expr(c.condition)+';'+self.expr(c.update)+')',self.stmt(n.body))
  if isinstance(n,T.SwitchStatement):
   out='switch('+self.expr(n.expression)+'){\n'
   for c in n.cases:
    out+=''.join('case '+self.expr(x)+':\n' for x in c.case) if c.case else 'default:\n'
    out+='{'+self.sequence(c.statements)+'}\n'
   return out+'}\n'
  if isinstance(n,T.TryStatement):return 'try{'+self.sequence(n.block)+'}'+''.join('catch(const std::exception& '+c.parameter.name+'){'+self.sequence(c.block)+'}' for c in n.catches)
  if isinstance(n,T.Statement):return ';\n'
  raise ValueError(('statement',type(n).__name__))

header=['// Native C++ translation of original-game routines; see SOURCE_AUDIT.txt.','#pragma once','#include "host.hpp"','#include "audio_bridge.hpp"']
# Data-label values come from the original source layout, independent of a JVM at runtime.
for name in classes:header.append('namespace '+name+' {}')
for name,(tree,cls,p) in classes.items():
 if name=='Mem':continue
 header.append('namespace '+name+' {')
 for f in cls.fields:
  for d in f.declarators:
   key=tree.package.name+'.'+name+'.'+d.name
   if key in constants and isinstance(constants[key],(int,float,bool)):
    value=constants[key];v=str(value).lower() if isinstance(value,bool) else str(value)
    header.append(('inline constexpr ' if 'final' in f.modifiers else 'inline ')+typ(f.type,len(d.dimensions or []))+' '+d.name+'='+v+';')
   elif (name in selected or f.type.name=='boolean') and (isinstance(f.type,T.BasicType) or f.type.name in ['String','Runnable']):
    try:
     dummy=T.MethodDeclaration(parameters=[],body=[]);em=Emitter(name,dummy)
     v=em.expr(d.initializer) if d.initializer else '{}'
     header.append(('inline constexpr ' if 'final' in f.modifiers and isinstance(f.type,T.BasicType) and not f.type.dimensions and not d.dimensions else 'inline ')+typ(f.type,len(d.dimensions or []))+' '+d.name+'='+v+';')
    except Exception:pass
 for m in cls.methods:
  signature=typ(m.return_type)+' '+(m.name+'_fn' if m.name in fields[name] else m.name)+'('+','.join(typ(p.type)+('&' if p.type.dimensions else '')+' '+p.name for p in m.parameters)+')'
  overrides={('ScreenC','hostDisplay'):'return nullptr;',('ExecLib','CopyMem'):'Mem::copy(source,dest,size);',('ExecLib','RawDoFmt'):'j_rawDoFmt(a0,a1,sink);',('Audio','ensureStarted'):'return ab3d2::audio_bridge::ensureStarted ? ab3d2::audio_bridge::ensureStarted() : false;',('Audio','needsBuffer'):'return ab3d2::audio_bridge::needsBuffer ? ab3d2::audio_bridge::needsBuffer() : false;',('Audio','stop'):'if(ab3d2::audio_bridge::stop)ab3d2::audio_bridge::stop();',('Audio','queueFromPaula'):'if(ab3d2::audio_bridge::queueFromPaula)ab3d2::audio_bridge::queueFromPaula();',('Audio','captureFrame'):'if(ab3d2::audio_bridge::captureFrame)ab3d2::audio_bridge::captureFrame();',('Res','Res_FreeLevelData'):'/* Runtime owns the native memory image. */return;',('Res','Res_ReleaseScreenMemory'):'/* Native GPU presentation owns targets. */return;'}
  if (name,m.name) in overrides:header.append('inline '+signature+'{'+overrides[(name,m.name)]+'}')
  elif name in selected and (name not in only_methods or m.name in only_methods[name]):header.append(signature+';')
  else:header.append('inline '+signature+'{return j_unported<'+typ(m.return_type)+'>("'+name+'.'+m.name+'");}')
 header.append('}')
(OUT/'original.hpp').write_text('\n'.join(header)+'\n')
failures=[]
for name in sorted(selected):
 if name not in classes:continue
 tree,cls,p=classes[name];code=['#include "original.hpp"','namespace '+name+' {']
 for m in cls.methods:
  if name in only_methods and m.name not in only_methods[name]:continue
  signature=typ(m.return_type)+' '+(m.name+'_fn' if m.name in fields[name] else m.name)+'('+','.join(typ(p.type)+('&' if p.type.dimensions else '')+' '+p.name for p in m.parameters)+')'
  if m.name.startswith('dbg') or name=='DevInst':body='return;' if not m.return_type else 'return {};'
  else:
   try:body=Emitter(name,m).sequence(m.body)
   except Exception as e:
    failures.append((name,m.name,str(e)));body='return j_unported<'+typ(m.return_type)+'>("'+name+'.'+m.name+'");'
  code.append(signature+'{\n'+body+'}\n')
 code.append('}');(OUT/(name+'.cpp')).write_text('\n'.join(code))
(OUT/'migration-report.json').write_text(json.dumps(failures,indent=2))
print('Emitted',len(selected),'native modules;',len(failures),'methods need explicit migration:')
for f in failures:print(*f)

for generated in OUT.glob('*'):
 if generated.suffix in ['.cpp','.hpp']:
  text=generated.read_text()
  for word in ['template','operator','delete','register','typename','union','friend','alignas','constexpr','thread_local']:
   if word=='constexpr':continue
   text=re.sub(r'\b'+word+r'\b','original_'+word,text)
  generated.write_text(text)

pending=[('Hires','game_main_loop')];visited=set();external=set()
while pending:
 owner,method=pending.pop()
 if (owner,method) in visited:continue
 visited.add((owner,method))
 if owner not in classes or method not in methods[owner]:external.add((owner,method));continue
 if owner not in selected:external.add((owner,method));continue
 if owner=='DevInst' or method.startswith('dbg'):continue
 emitter=Emitter(owner,methods[owner][method])
 try:emitter.sequence(methods[owner][method].body)
 except Exception:continue
 pending.extend(emitter.called)
(OUT/'host-services.json').write_text(json.dumps(sorted(external),indent=2))
print('External services from original native game loop:',len(external))
for service in sorted(external):print(*service)
