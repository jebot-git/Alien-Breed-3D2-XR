#!/usr/bin/env python3
"""Optional offline oracle: compile unchanged preserved source, never ship Java.

First run lighting-check.cpp with assets, snapshots, oracle-input, native-output.
Then run this script with oracle-input and native-output. AB3D2_TEST_JAVAC/JAVA
may select a development JDK; neither is needed to build/run the native game.
"""
import os
from pathlib import Path
import shutil
import subprocess
import sys
import tempfile

root = Path(__file__).resolve().parents[3]
with tempfile.TemporaryDirectory(prefix="ab3d2-light-oracle-") as tmp:
    tmp = Path(tmp)
    package = tmp / "ab3d2/rebirth"
    sim = package / "sim"
    sim.mkdir(parents=True)
    source = subprocess.check_output(
        ["git", "show", "reference/java-host-audit:src/ab3d2/rebirth/LightRings.java"], cwd=root)
    (package / "LightRings.java").write_bytes(source)
    (package / "SpriteLight.java").write_bytes(subprocess.check_output(
        ["git", "show", "reference/java-host-audit:src/ab3d2/rebirth/SpriteLight.java"], cwd=root))
    original = subprocess.check_output(
        ["git", "show", "reference/java-host-audit:upstream/faithful/src/ab3d2/Objdrawhires.java"], cwd=root).decode()
    start = original.index("        a0 = draw_AngleBrights_vl;", original.index("static void draw_PolygonModel"))
    end = original.index("        // GETREGS — restaure a0", start)
    # Execute the exact original point-and-polygon table block, unchanged.
    (package / "PolygonOracle.java").write_text("""package ab3d2.rebirth;
class PolygonOracle {
 static final int draw_AngleBrights_vl=0,draw_PointAndPolyBrights_vl=64;
 static class Mem {static byte[] bytes=new byte[320];static int ub(int at){return bytes[at]&255;}static void wb(int at,int value){bytes[at]=(byte)value;}}
 static int setw(int old,int value){return (old&0xffff0000)|(value&65535);}
 static int setb(int old,int value){return (old&0xffffff00)|(value&255);}
 static int swap(int value){return (value<<16)|(value>>>16);}
 static byte[] table(byte[] rings){System.arraycopy(rings,0,Mem.bytes,0,64);int a0,a1,d2,d3,d4,d5,d6,d7;
""" + original[start:end] + "return java.util.Arrays.copyOfRange(Mem.bytes,64,320);}}")
    (package / "Assets.java").write_text("""package ab3d2.rebirth;
import java.nio.file.*;
class Assets { static Path root;static Path path(String name){return root.resolve(name);}static boolean exists(String name){return Files.exists(path(name));} }
""")
    (package / "LevelData.java").write_text("""package ab3d2.rebirth;
import java.util.*;
class LevelData {
 static class Point { int x,z; Point(int x,int z){this.x=x;this.z=z;} }
 static class Edge { int dx,dz,join; Edge(int dx,int dz,int join){this.dx=dx;this.dz=dz;this.join=join;} }
 static class Zone { List<Integer> borderPointsRaw=new ArrayList<>(),edgeList=new ArrayList<>(); }
}
""")
    (package / "LightAnim.java").write_text("""package ab3d2.rebirth;
class LightAnim { int[] values; int upper; LightAnim(int[] v){values=v;}
 int pointBright(int zone,int slot){int i=zone*40+slot+upper;return i>=0&&i<values.length?values[i]:0;} }
""")
    (sim / "SinCos.java").write_text("""package ab3d2.rebirth.sim;
public class SinCos { public int[] values; public SinCos(int[] v){values=v;}
 public int sin(int byteAngle){return values[(byteAngle/2)&4095];}
 public int cos(int byteAngle){return values[((byteAngle/2)&4095)+1024];} }
""")
    (sim / "M68k.java").write_text("""package ab3d2.rebirth.sim;
public class M68k {
 public static int setw(int old,int value){return (old&0xffff0000)|(value&65535);}
 public static int muls(int a,int b){return (short)a*(short)b;}
 public static int divs(int a,int b){b=(short)b;int q=a/b;if(q<-32768||q>32767)return a;return ((a%b)<<16)|(q&65535);} }
""")
    (package / "Oracle.java").write_text("""package ab3d2.rebirth;
import java.io.*;import java.util.*;import java.lang.reflect.*;import ab3d2.rebirth.sim.*;
public class Oracle {
 public static void main(String[] args)throws Exception {
  Assets.root=java.nio.file.Path.of(args[2]);
  DataInputStream in=new DataInputStream(new BufferedInputStream(new FileInputStream(args[0])));
  OutputStream out=new BufferedOutputStream(new FileOutputStream(args[1]));
  Field ring=LightRings.class.getDeclaredField("ring");ring.setAccessible(true);
  int levels=in.readInt();for(int li=0;li<levels;li++){
   List<LevelData.Point> points=new ArrayList<>();int count=in.readInt();for(int i=0;i<count;i++)points.add(new LevelData.Point(in.readInt(),in.readInt()));
   Map<Integer,LevelData.Zone> zones=new HashMap<>();int zoneCount=in.readInt();for(int z=0;z<zoneCount;z++){LevelData.Zone zone=new LevelData.Zone();for(int i=0;i<10;i++)zone.borderPointsRaw.add(in.readInt());count=in.readInt();for(int i=0;i<count;i++)zone.edgeList.add(in.readInt());zones.put(z,zone);}
   List<LevelData.Edge> edges=new ArrayList<>();count=in.readInt();for(int i=0;i<count;i++)edges.add(new LevelData.Edge(in.readInt(),in.readInt(),in.readInt()));
   int[] values=new int[zoneCount*40];for(int i=0;i<values.length;i++)values[i]=in.readInt();LightAnim lights=new LightAnim(values);
   int[] table=new int[5120];for(int i=0;i<table.length;i++)table[i]=in.readInt();SinCos sine=new SinCos(table);
   count=in.readInt();for(int i=0;i<count;i++){int x=in.readInt(),z=in.readInt(),zone=in.readInt();lights.upper=in.readInt()*2;
    byte[] full=(byte[])ring.get(LightRings.compute(zones,points,edges,sine,lights,x,z,zone));out.write(full);out.write(PolygonOracle.table(full));
    LightRings sprite=LightRings.zoneOnly(zones,points,edges,sine,lights,x,z,zone);out.write((byte[])ring.get(sprite));
    for(int bright:new int[]{-100,-16,0,16,64,255})for(float value:SpriteLight.levels(sprite,((x+z)*2)&8191,bright,lights.upper!=0))out.write((int)value);}
  }out.close();in.close();
 }
}
""")
    javac = os.environ.get("AB3D2_TEST_JAVAC", shutil.which("javac") or "javac")
    java = os.environ.get("AB3D2_TEST_JAVA", shutil.which("java") or "java")
    subprocess.run([javac, "-d", str(tmp), *map(str, tmp.rglob("*.java"))], check=True)
    expected = tmp / "expected.bin"
    subprocess.run([java, "-cp", str(tmp), "ab3d2.rebirth.Oracle", sys.argv[1], str(expected), str(root / "assets")], check=True)
    wanted, actual = expected.read_bytes(), Path(sys.argv[2]).read_bytes()
    if wanted != actual:
        differences = [(i, a, b) for i, (a, b) in enumerate(zip(wanted, actual)) if a != b]
        raise SystemExit(f"Lighting mismatch: {len(differences)} bytes, first {differences[:12]}; lengths {len(wanted)}/{len(actual)}")
    print(f"PASS unchanged source oracle: {len(actual) // 558} original positions, all 16 levels, {len(actual)} ring, original flat-face table and indexed color-group bytes")
