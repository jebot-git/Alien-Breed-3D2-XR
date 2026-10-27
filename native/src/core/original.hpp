// Native C++ translation of original-game routines; see SOURCE_AUDIT.txt.
#pragma once
#include "host.hpp"
namespace Ab3diipatchidr {}
namespace Assets {}
namespace Cd32joy {}
namespace Controlloop {}
namespace ControlloopData {}
namespace Defs {}
namespace Fall {}
namespace Hires {}
namespace HiresData {}
namespace Hiresgourwall {}
namespace Hireswall {}
namespace HireswallData {}
namespace M68k {}
namespace Macros {}
namespace Mem {}
namespace MenuNb {}
namespace Newaliencontrol {}
namespace NewaliencontrolData {}
namespace Newanims {}
namespace NewanimsData {}
namespace Newplayershoot {}
namespace NewplayershootData {}
namespace Objdrawhires {}
namespace ObjdrawhiresData {}
namespace Objectmove {}
namespace ObjectmoveData {}
namespace Orderzones {}
namespace Pauseopts {}
namespace Plr1control {}
namespace Plr2control {}
namespace SerialNightmare {}
namespace SystemInc {}
namespace AiBss {}
namespace AnimBss {}
namespace Bss {}
namespace DrawBss {}
namespace GameBss {}
namespace IoBss {}
namespace LevelBss {}
namespace MenunbBss {}
namespace PlayerBss {}
namespace SystemBss {}
namespace TablesBss {}
namespace VidBss {}
namespace ZoneBss {}
namespace DrawC {}
namespace GameC {}
namespace GamePreferences {}
namespace GameProgress {}
namespace MainC {}
namespace MenuC {}
namespace Message {}
namespace ScreenC {}
namespace SystemC {}
namespace ZoneDebug {}
namespace ZoneEdgePvs {}
namespace ZoneErrata {}
namespace ZoneLiftablePvs {}
namespace DataSections {}
namespace DrawData {}
namespace GameData {}
namespace LevelData {}
namespace MenunbData {}
namespace SystemData {}
namespace TablesData {}
namespace TextData {}
namespace TitlecopData {}
namespace Version {}
namespace VidData {}
namespace Adf {}
namespace AdfAssets {}
namespace Audio {}
namespace Display {}
namespace DisplayTest {}
namespace ExecLib {}
namespace FatalError {}
namespace FrameBridge {}
namespace GraphicsLib {}
namespace Input {}
namespace IntuitionLib {}
namespace LevelTest {}
namespace LowLevelLib {}
namespace Main {}
namespace SbDepack {}
namespace SerialLink {}
namespace SysTimer {}
namespace TwoPlayerTest {}
namespace Vbl {}
namespace Menunb {}
namespace Ai {}
namespace C2pData {}
namespace DevInst {}
namespace DevMacros {}
namespace DevMemtrack {}
namespace Draw {}
namespace FileIo {}
namespace Level {}
namespace Music {}
namespace Player {}
namespace RawKeyMacros {}
namespace Res {}
namespace Sys {}
namespace Transform {}
namespace Vid {}
namespace AdfCheck {}
namespace CheckLayout {}
namespace Depack {}
namespace SerialLinkTest {}
namespace SkyDump {}
namespace DrawFloor {}
namespace DrawFloor060 {}
namespace DrawMap {}
namespace DrawSetClip {}
namespace DrawWall {}
namespace DrawWall060 {}
namespace DrawZoneGraph {}
namespace Ab3diipatchidr {
inline void MakePatch(){return j_unported<void>("Ab3diipatchidr.MakePatch");}
inline int32_t NewFunction(){return j_unported<int32_t>("Ab3diipatchidr.NewFunction");}
}
namespace Assets {
inline bool lenient=true;
inline int32_t findRoot(){return j_unported<int32_t>("Assets.findRoot");}
inline int32_t incbin(std::string path){return j_unported<int32_t>("Assets.incbin");}
inline std::vector<int8_t> fromClasspath(std::string path){return j_unported<std::vector<int8_t>>("Assets.fromClasspath");}
inline std::vector<int8_t> bytes(std::string path){return j_unported<std::vector<int8_t>>("Assets.bytes");}
inline std::vector<int8_t> read(std::string amigaPath){return j_unported<std::vector<int8_t>>("Assets.read");}
inline int32_t resolve(std::string path){return j_unported<int32_t>("Assets.resolve");}
inline int32_t findByBasename(std::string base){return j_unported<int32_t>("Assets.findByBasename");}
inline int32_t findCaseInsensitive(int32_t dir,std::vector<std::string>& segments){return j_unported<int32_t>("Assets.findCaseInsensitive");}
}
namespace Cd32joy {
inline constexpr int32_t JP_TYPE_NOTAVAIL=0;
inline constexpr int32_t JP_TYPE_GAMECTLR=268435456;
inline constexpr int32_t JP_TYPE_MOUSE=536870912;
inline constexpr int32_t JP_TYPE_JOYSTK=805306368;
inline constexpr int32_t JP_TYPE_MASK=-268435456;
inline constexpr int32_t JPF_BUTTON_BLUE=8388608;
inline constexpr int32_t JPF_BUTTON_RED=4194304;
inline constexpr int32_t JPF_BUTTON_YELLOW=2097152;
inline constexpr int32_t JPF_BUTTON_GREEN=1048576;
inline constexpr int32_t JPF_BUTTON_FORWARD=524288;
inline constexpr int32_t JPF_BUTTON_REVERSE=262144;
inline constexpr int32_t JPF_BUTTON_PLAY=131072;
inline constexpr int32_t JPF_JOY_UP=8;
inline constexpr int32_t JPF_JOY_DOWN=4;
inline constexpr int32_t JPF_JOY_LEFT=2;
inline constexpr int32_t JPF_JOY_RIGHT=1;
inline int32_t button=0;
inline int32_t button1=0;
inline int32_t rj1_ducklast=0;
inline int32_t rj1_heldlast=0;
inline int32_t rj2_ducklast=0;
inline int32_t rj2_heldlast=0;
inline int32_t _InitLowLevel(){return j_unported<int32_t>("Cd32joy._InitLowLevel");}
inline void _CloseLowLevel(){return j_unported<void>("Cd32joy._CloseLowLevel");}
inline void sneKey(int32_t keyAddr,int32_t joy,int32_t jpfBit){return j_unported<void>("Cd32joy.sneKey");}
inline void _ReadJoy1(){return j_unported<void>("Cd32joy._ReadJoy1");}
inline void _ReadJoy2(){return j_unported<void>("Cd32joy._ReadJoy2");}
inline void gameCtrl1(int32_t d0){return j_unported<void>("Cd32joy.gameCtrl1");}
inline void gameCtrl2(int32_t d0){return j_unported<void>("Cd32joy.gameCtrl2");}
inline void joystick(){return j_unported<void>("Cd32joy.joystick");}
}
namespace Controlloop {
inline constexpr int32_t PLR_SINGLE=110;
inline constexpr int32_t PLR_MASTER=109;
inline constexpr int32_t PLR_SLAVE=115;
inline bool coopMode=false;
inline constexpr int32_t SAVE_SLOT_SIZE=70;
inline constexpr int32_t NUM_SAVE_SLOTS=6;
inline constexpr int32_t SAVE_FILE_SIZE=420;
inline void GETSTATS(){return j_unported<void>("Controlloop.GETSTATS");}
inline void SETPLAYERS(){return j_unported<void>("Controlloop.SETPLAYERS");}
inline void DEFAULTGAME(){return j_unported<void>("Controlloop.DEFAULTGAME");}
inline void TWOPLAYER(){return j_unported<void>("Controlloop.TWOPLAYER");}
inline void playgame(){return j_unported<void>("Controlloop.playgame");}
inline void game_SetMenuLevelName(int32_t a0,int32_t a1){return j_unported<void>("Controlloop.game_SetMenuLevelName");}
inline void Plr_InitMaster(){return j_unported<void>("Controlloop.Plr_InitMaster");}
inline void ensureMasterLink(){return j_unported<void>("Controlloop.ensureMasterLink");}
inline void ensureSlaveLink(){return j_unported<void>("Controlloop.ensureSlaveLink");}
inline void Plr_InitSlave(){return j_unported<void>("Controlloop.Plr_InitSlave");}
inline void Game_Start(){return j_unported<void>("Controlloop.Game_Start");}
inline int32_t Game_Quit(){return j_unported<int32_t>("Controlloop.Game_Quit");}
inline void game_ReadMainMenu(){return j_unported<void>("Controlloop.game_ReadMainMenu");}
inline void game_MasterMenu(){return j_unported<void>("Controlloop.game_MasterMenu");}
inline void setMasterModeLine(){return j_unported<void>("Controlloop.setMasterModeLine");}
inline void writeMenuLine(int32_t addr,std::string s){return j_unported<void>("Controlloop.writeMenuLine");}
inline void game_SlaveMenu(){return j_unported<void>("Controlloop.game_SlaveMenu");}
inline void setMasterLevelName(int32_t lvl){return j_unported<void>("Controlloop.setMasterLevelName");}
inline void refreshLevelName(){return j_unported<void>("Controlloop.refreshLevelName");}
inline void levelMenu(){return j_unported<void>("Controlloop.levelMenu");}
inline void levelMenu2(){return j_unported<void>("Controlloop.levelMenu2");}
inline void notB(int32_t addr){return j_unported<void>("Controlloop.notB");}
inline void customOptions(){return j_unported<void>("Controlloop.customOptions");}
inline void CHANGECONTROLS(){return j_unported<void>("Controlloop.CHANGECONTROLS");}
inline void CHANGECONTROLS2(){return j_unported<void>("Controlloop.CHANGECONTROLS2");}
inline void DEFGAME(int32_t d0){return j_unported<void>("Controlloop.DEFGAME");}
inline int32_t loadSaveFile(){return j_unported<int32_t>("Controlloop.loadSaveFile");}
inline void game_LoadPosition(){return j_unported<void>("Controlloop.game_LoadPosition");}
inline void game_SavePosition(){return j_unported<void>("Controlloop.game_SavePosition");}
inline void game_WaitForMenuKey(){return j_unported<void>("Controlloop.game_WaitForMenuKey");}
inline void game_SetMenuLevelNames(){return j_unported<void>("Controlloop.game_SetMenuLevelNames");}
inline void game_OpenMenu(int32_t a0){return j_unported<void>("Controlloop.game_OpenMenu");}
inline int32_t game_CheckMenu(int32_t a0){return j_unported<int32_t>("Controlloop.game_CheckMenu");}
}
namespace ControlloopData {
inline constexpr int32_t _a0=2311160;
inline constexpr int32_t Prefsfile=2311160;
inline constexpr int32_t Prefs_AssignableKeys_vb=2311164;
inline constexpr int32_t AssignableKeys_vb=2311164;
inline constexpr int32_t turn_left_key=2311164;
inline constexpr int32_t turn_right_key=2311165;
inline constexpr int32_t forward_key=2311166;
inline constexpr int32_t backward_key=2311167;
inline constexpr int32_t fire_key=2311168;
inline constexpr int32_t operate_key=2311169;
inline constexpr int32_t run_key=2311170;
inline constexpr int32_t force_sidestep_key=2311171;
inline constexpr int32_t sidestep_left_key=2311172;
inline constexpr int32_t sidestep_right_key=2311173;
inline constexpr int32_t duck_key=2311174;
inline constexpr int32_t look_behind_key=2311175;
inline constexpr int32_t jump_key=2311176;
inline constexpr int32_t look_up_key=2311177;
inline constexpr int32_t look_down_key=2311178;
inline constexpr int32_t centre_view_key=2311179;
inline constexpr int32_t next_weapon_key=2311180;
inline constexpr int32_t spare_key=2311181;
inline constexpr int32_t Prefs_FullScreen_b=2311182;
inline constexpr int32_t Prefs_PixelMode_b=2311183;
inline constexpr int32_t Prefs_VertMargin_b=2311184;
inline constexpr int32_t Prefs_SimpleLighting_b=2311185;
inline constexpr int32_t Prefs_FPSLimit_b=2311186;
inline constexpr int32_t Prefs_DynamicLights_b=2311187;
inline constexpr int32_t Prefs_RenderQuality_b=2311188;
inline constexpr int32_t Prefs_Unused_b=2311189;
inline constexpr int32_t Prefs_ContrastAdjust_AGA_w=2311190;
inline constexpr int32_t Prefs_ContrastAdjust_RTG_w=2311192;
inline constexpr int32_t Prefs_BrightnessOffset_AGA_w=2311194;
inline constexpr int32_t Prefs_BrightnessOffset_RTG_w=2311196;
inline constexpr int32_t Prefs_GammaLevel_AGA_b=2311198;
inline constexpr int32_t Prefs_GammaLevel_RTG_b=2311199;
inline constexpr int32_t Prefs_CustomOptionsBuffer_vb=2311200;
inline constexpr int32_t Prefs_OriginalMouse_b=2311200;
inline constexpr int32_t Prefs_AlwaysRun_b=2311201;
inline constexpr int32_t Prefs_ShowMessages_b=2311202;
inline constexpr int32_t Prefs_NoAutoAim_b=2311203;
inline constexpr int32_t Prefs_DisplayFPS_b=2311204;
inline constexpr int32_t Prefs_ShowWeapon_b=2311205;
inline constexpr int32_t Prefs_PlayMusic_b=2311206;
inline constexpr int32_t Prefs_CrossHairColour_b=2311207;
inline constexpr int32_t _a1=2311208;
inline constexpr int32_t PrefsfileEnd=2311208;
inline constexpr int32_t templeftkey=2311208;
inline constexpr int32_t temprightkey=2311209;
inline constexpr int32_t tempslkey=2311210;
inline constexpr int32_t tempsrkey=2311211;
inline constexpr int32_t _a2=2311212;
inline constexpr int32_t Lvl_DefFilename_vb=2311212;
inline constexpr int32_t Lvl_DefFilenameX_vb=2311229;
inline constexpr int32_t LOADEXT=2311242;
inline constexpr int32_t _a3=2311244;
inline constexpr int32_t DEFGAMEPOS=2311244;
inline constexpr int32_t DEFGAMELEN=2311248;
inline constexpr int32_t Game_ShouldQuit_b=2311252;
inline constexpr int32_t game_LevelSelected_w=2311254;
inline constexpr int32_t FADEAMOUNT=2311256;
inline constexpr int32_t FADEVAL=2311258;
inline constexpr int32_t Game_StoryFile_vb=2311260;
inline constexpr int32_t _a4=2311282;
inline constexpr int32_t Lvl_IntroTextPtr_l=2311282;
inline constexpr int32_t Game_LevelNumber_w=2311286;
inline constexpr int32_t Game_LevelCounter_w=2311288;
inline constexpr int32_t Game_FinishedLevel_b=2311290;
}
namespace Defs {
inline constexpr int32_t MAX_LEVEL_OBJ_DIST_COUNT=288;
inline constexpr int32_t MAX_OBJS_IN_LINE_COUNT=400;
inline constexpr int32_t LVL_OBJ_DEFINITION_SIZE=64;
inline constexpr int32_t NUM_LEVELS=16;
inline constexpr int32_t NUM_BULLET_DEFS=20;
inline constexpr int32_t NUM_GUN_DEFS=10;
inline constexpr int32_t NUM_ALIEN_DEFS=20;
inline constexpr int32_t NUM_OBJECT_DEFS=30;
inline constexpr int32_t NUM_SFX=64;
inline constexpr int32_t NUM_WALL_TEXTURES=16;
inline constexpr int32_t PlrT_ObjectPtr_l=0;
inline constexpr int32_t PlrT_XOff_l=4;
inline constexpr int32_t PlrT_YOff_l=8;
inline constexpr int32_t PlrT_ZOff_l=12;
inline constexpr int32_t PlrT_ZonePtr_l=16;
inline constexpr int32_t PlrT_Height_l=20;
inline constexpr int32_t PlrT_AimSpeed_l=24;
inline constexpr int32_t PlrT_SnapXOff_l=28;
inline constexpr int32_t PlrT_SnapYOff_l=32;
inline constexpr int32_t PlrT_SnapYVel_l=36;
inline constexpr int32_t PlrT_SnapZOff_l=40;
inline constexpr int32_t PlrT_SnapTYOff_l=44;
inline constexpr int32_t PlrT_SnapXSpdVal_l=48;
inline constexpr int32_t PlrT_SnapZSpdVal_l=52;
inline constexpr int32_t PlrT_SnapHeight_l=56;
inline constexpr int32_t PlrT_SnapTargHeight_l=60;
inline constexpr int32_t PlrT_TmpXOff_l=64;
inline constexpr int32_t PlrT_TmpZOff_l=68;
inline constexpr int32_t PlrT_TmpYOff_l=72;
inline constexpr int32_t PlrT_ListOfGraphRoomsPtr_l=76;
inline constexpr int32_t PlrT_PointsToRotatePtr_l=80;
inline constexpr int32_t PlrT_BobbleY_l=84;
inline constexpr int32_t PlrT_TmpHeight_l=88;
inline constexpr int32_t PlrT_OldX_l=92;
inline constexpr int32_t PlrT_OldZ_l=96;
inline constexpr int32_t PlrT_OldRoomPtr_l=100;
inline constexpr int32_t PlrT_SnapSquishedHeight_l=104;
inline constexpr int32_t PlrT_DefaultEnemyFlags_l=108;
inline constexpr int32_t PlrT_Energy_w=112;
inline constexpr int32_t PlrT_CosVal_w=114;
inline constexpr int32_t PlrT_SinVal_w=116;
inline constexpr int32_t PlrT_AngPos_w=118;
inline constexpr int32_t PlrT_Zone_w=120;
inline constexpr int32_t PlrT_FloorSpd_w=122;
inline constexpr int32_t PlrT_RoomBright_w=124;
inline constexpr int32_t PlrT_Bobble_w=126;
inline constexpr int32_t PlrT_SnapAngPos_w=128;
inline constexpr int32_t PlrT_SnapAngSpd_w=130;
inline constexpr int32_t PlrT_TmpAngPos_w=132;
inline constexpr int32_t PlrT_TimeToShoot_w=134;
inline constexpr int32_t PlrT_Health_w=136;
inline constexpr int32_t PlrT_JetpackFuel_w=138;
inline constexpr int32_t PlrT_AmmoCounts_vw=140;
inline constexpr int32_t PlrT_Shield_w=180;
inline constexpr int32_t PlrT_Jetpack_w=182;
inline constexpr int32_t PlrT_Weapons_vb=184;
inline constexpr int32_t PlrT_GunFrame_w=204;
inline constexpr int32_t PlrT_NoiseVol_w=206;
inline constexpr int32_t PlrT_TmpHoldDown_w=208;
inline constexpr int32_t PlrT_TmpBobble_w=210;
inline constexpr int32_t PlrT_SnapCosVal_w=212;
inline constexpr int32_t PlrT_SnapSinVal_w=214;
inline constexpr int32_t PlrT_WalkSFXTime_w=216;
inline constexpr int32_t PlrT_Keys_b=218;
inline constexpr int32_t PlrT_Path_b=219;
inline constexpr int32_t PlrT_Mouse_b=220;
inline constexpr int32_t PlrT_Joystick_b=221;
inline constexpr int32_t PlrT_GunSelected_b=222;
inline constexpr int32_t PlrT_StoodInTop_b=223;
inline constexpr int32_t PlrT_Ducked_b=224;
inline constexpr int32_t PlrT_Squished_b=225;
inline constexpr int32_t PlrT_Echo_b=226;
inline constexpr int32_t PlrT_Fire_b=227;
inline constexpr int32_t PlrT_Clicked_b=228;
inline constexpr int32_t PlrT_Used_b=229;
inline constexpr int32_t PlrT_TmpClicked_b=230;
inline constexpr int32_t PlrT_TmpSpcTap_b=231;
inline constexpr int32_t PlrT_TmpGunSelected_b=232;
inline constexpr int32_t PlrT_TmpFire_b=233;
inline constexpr int32_t PlrT_Teleported_b=234;
inline constexpr int32_t PlrT_Dead_b=235;
inline constexpr int32_t PlrT_TmpDucked_b=236;
inline constexpr int32_t PlrT_StoodOnLift_b=237;
inline constexpr int32_t PlrT_InvMouse_b=238;
inline constexpr int32_t PlrT_Reserved2_b=239;
inline constexpr int32_t PlrT_ObjectDistances_vw=240;
inline constexpr int32_t PlrT_ObjectsInLine_vb=816;
inline constexpr int32_t PlrT_SizeOf_l=1216;
inline constexpr int32_t BulT_IsHitScan_l=0;
inline constexpr int32_t BulT_Gravity_l=4;
inline constexpr int32_t BulT_Lifetime_l=8;
inline constexpr int32_t BulT_AmmoInClip_l=12;
inline constexpr int32_t BulT_BounceHoriz_l=16;
inline constexpr int32_t BulT_BounceVert_l=20;
inline constexpr int32_t BulT_HitDamage_l=24;
inline constexpr int32_t BulT_ExplosiveForce_l=28;
inline constexpr int32_t BulT_Speed_l=32;
inline constexpr int32_t BulT_AnimFrames_l=36;
inline constexpr int32_t BulT_PopFrames_l=40;
inline constexpr int32_t BulT_BounceSFX_l=44;
inline constexpr int32_t BulT_ImpactSFX_l=48;
inline constexpr int32_t BulT_GraphicType_l=52;
inline constexpr int32_t BulT_ImpactGraphicType_l=56;
inline constexpr int32_t BulT_AnimData_vb=60;
inline constexpr int32_t BulT_PopData_vb=180;
inline constexpr int32_t BulT_SizeOf_l=300;
inline constexpr int32_t ShootT_BulType_w=0;
inline constexpr int32_t ShootT_Delay_w=2;
inline constexpr int32_t ShootT_BulCount_w=4;
inline constexpr int32_t ShootT_SFX_w=6;
inline constexpr int32_t ShootT_SizeOf_l=8;
inline constexpr int32_t AlienT_GFXType_w=0;
inline constexpr int32_t AlienT_DefaultBehaviour_w=2;
inline constexpr int32_t AlienT_ReactionTime_w=4;
inline constexpr int32_t AlienT_DefaultSpeed_w=6;
inline constexpr int32_t AlienT_ResponseBehaviour_w=8;
inline constexpr int32_t AlienT_ResponseSpeed_w=10;
inline constexpr int32_t AlienT_ResponseTimeout_w=12;
inline constexpr int32_t AlienT_DamageToRetreat_w=14;
inline constexpr int32_t AlienT_DamageToFollowup_w=16;
inline constexpr int32_t AlienT_FollowupBehaviour_w=18;
inline constexpr int32_t AlienT_FollowupSpeed_w=20;
inline constexpr int32_t AlienT_FollowupTimeout_w=22;
inline constexpr int32_t AlienT_RetreatBehaviour_w=24;
inline constexpr int32_t AlienT_RetreatSpeed_w=26;
inline constexpr int32_t AlienT_RetreatTimeout_w=28;
inline constexpr int32_t AlienT_BulType_w=30;
inline constexpr int32_t AlienT_HitPoints_w=32;
inline constexpr int32_t AlienT_Height_w=34;
inline constexpr int32_t AlienT_Girth_w=36;
inline constexpr int32_t AlienT_SplatType_w=38;
inline constexpr int32_t AlienT_Auxilliary_w=40;
inline constexpr int32_t AlienT_SizeOf_l=42;
inline constexpr int32_t ODefT_Behaviour_w=0;
inline constexpr int32_t ODefT_GFXType_w=2;
inline constexpr int32_t ODefT_ActiveTimeout_w=4;
inline constexpr int32_t ODefT_HitPoints_w=6;
inline constexpr int32_t ODefT_ExplosiveForce_w=8;
inline constexpr int32_t ODefT_Impassible_w=10;
inline constexpr int32_t ODefT_DefaultAnimLen_w=12;
inline constexpr int32_t ODefT_CollideRadius_w=14;
inline constexpr int32_t ODefT_CollideHeight_w=16;
inline constexpr int32_t ODefT_FloorCeiling_w=18;
inline constexpr int32_t ODefT_LockToWall_w=20;
inline constexpr int32_t ODefT_ActiveAnimLen_w=22;
inline constexpr int32_t ODefT_SFX_w=24;
inline constexpr int32_t ODefT_SizeOf_l=40;
inline constexpr int32_t OBJ_TYPE_ALIEN=0;
inline constexpr int32_t OBJ_TYPE_OBJECT=1;
inline constexpr int32_t OBJ_TYPE_PROJECTILE=2;
inline constexpr int32_t OBJ_TYPE_AUX=3;
inline constexpr int32_t OBJ_TYPE_PLAYER1=4;
inline constexpr int32_t OBJ_TYPE_PLAYER2=5;
inline constexpr int32_t ObjT_XPos_l=0;
inline constexpr int32_t ObjT_ZPos_l=4;
inline constexpr int32_t ObjT_YPos_l=8;
inline constexpr int32_t ObjT_ZoneID_w=12;
inline constexpr int32_t ObjT_TypeID_b=16;
inline constexpr int32_t ObjT_SeePlayer_b=17;
inline constexpr int32_t ObjT_Header_SizeOf_l=18;
inline constexpr int32_t ObjT_SizeOf_l=64;
inline constexpr int32_t OBJ_PREV=-64;
inline constexpr int32_t OBJ_NEXT=64;
inline constexpr int32_t EntT_HitPoints_b=18;
inline constexpr int32_t EntT_DamageTaken_b=19;
inline constexpr int32_t EntT_CurrentMode_b=20;
inline constexpr int32_t EntT_TeamNumber_b=21;
inline constexpr int32_t EntT_CurrentSpeed_w=22;
inline constexpr int32_t EntT_DisplayText_w=24;
inline constexpr int32_t EntT_ZoneID_w=26;
inline constexpr int32_t EntT_CurrentControlPoint_w=28;
inline constexpr int32_t EntT_CurrentAngle_w=30;
inline constexpr int32_t EntT_TargetControlPoint_w=32;
inline constexpr int32_t EntT_Timer1_w=34;
inline constexpr int32_t EntT_EnemyFlags_l=36;
inline constexpr int32_t EntT_Timer2_w=40;
inline constexpr int32_t EntT_ImpactX_w=42;
inline constexpr int32_t EntT_ImpactZ_w=44;
inline constexpr int32_t EntT_ImpactY_w=46;
inline constexpr int32_t EntT_VelocityY_w=48;
inline constexpr int32_t EntT_DoorsAndLiftsHeld_l=50;
inline constexpr int32_t EntT_Timer3_w=52;
inline constexpr int32_t EntT_Timer4_w=54;
inline constexpr int32_t EntT_Type_b=54;
inline constexpr int32_t EntT_WhichAnim_b=55;
inline constexpr int32_t EntT_SizeOf_l=64;
inline constexpr int32_t ENT_TYPE_COLLECTABLE=0;
inline constexpr int32_t ENT_TYPE_ACTIVATABLE=1;
inline constexpr int32_t ENT_TYPE_DESTRUCTABLE=2;
inline constexpr int32_t ENT_TYPE_DECORATION=3;
inline constexpr int32_t ENT_PREV_2=-128;
inline constexpr int32_t ENT_PREV=-64;
inline constexpr int32_t ENT_NEXT=64;
inline constexpr int32_t ENT_NEXT_2=128;
inline constexpr int32_t ShotT_VelocityX_w=18;
inline constexpr int32_t ShotT_VelocityZ_w=22;
inline constexpr int32_t ShotT_Power_w=28;
inline constexpr int32_t ShotT_Status_b=30;
inline constexpr int32_t ShotT_Size_b=31;
inline constexpr int32_t ShotT_VelocityY_w=42;
inline constexpr int32_t ShotT_AccYPos_w=44;
inline constexpr int32_t ShotT_AuxOffsetX_w=44;
inline constexpr int32_t ShotT_AuxOffsetY_w=46;
inline constexpr int32_t ShotT_Anim_b=52;
inline constexpr int32_t ShotT_Gravity_w=54;
inline constexpr int32_t ShotT_Impact_w=56;
inline constexpr int32_t ShotT_Lifetime_w=58;
inline constexpr int32_t ShotT_Flags_w=60;
inline constexpr int32_t ShotT_Worry_b=62;
inline constexpr int32_t ShotT_InUpperZone_b=63;
inline constexpr int32_t ShotT_SizeOf_l=64;
inline constexpr int32_t ZoneT_ID_w=0;
inline constexpr int32_t ZoneT_Floor_l=2;
inline constexpr int32_t ZoneT_Roof_l=6;
inline constexpr int32_t ZoneT_UpperFloor_l=10;
inline constexpr int32_t ZoneT_UpperRoof_l=14;
inline constexpr int32_t ZoneT_Water_l=18;
inline constexpr int32_t ZoneT_Brightness_w=22;
inline constexpr int32_t ZoneT_UpperBrightness_w=24;
inline constexpr int32_t ZoneT_ControlPoint_w=26;
inline constexpr int32_t ZoneT_BackSFXMask_w=28;
inline constexpr int32_t ZoneT_Unused_w=30;
inline constexpr int32_t ZoneT_EdgeListOffset_w=32;
inline constexpr int32_t ZoneT_Points_w=34;
inline constexpr int32_t ZoneT_DrawBackdrop_b=36;
inline constexpr int32_t ZoneT_Echo_b=37;
inline constexpr int32_t ZoneT_TelZone_w=38;
inline constexpr int32_t ZoneT_TelX_w=40;
inline constexpr int32_t ZoneT_TelZ_w=42;
inline constexpr int32_t ZoneT_FloorNoise_w=44;
inline constexpr int32_t ZoneT_UpperFloorNoise_w=46;
inline constexpr int32_t ZoneT_PotVisibleZoneList_vw=48;
inline constexpr int32_t ZoneT_SizeOf_l=50;
inline constexpr int32_t ZPVSRecordT_ZoneID_w=0;
inline constexpr int32_t ZPVSRecordT_ClipID_w=2;
inline constexpr int32_t ZPVSRecordT_Word2_w=4;
inline constexpr int32_t ZPVSRecordT_Word3_w=6;
inline constexpr int32_t ZPVSRecordT_SizeOf_l=8;
inline constexpr int32_t EdgeT_XPos_w=0;
inline constexpr int32_t EdgeT_ZPos_w=2;
inline constexpr int32_t EdgeT_XLen_w=4;
inline constexpr int32_t EdgeT_ZLen_w=6;
inline constexpr int32_t EdgeT_JoinZone_w=8;
inline constexpr int32_t EdgeT_Word_5=10;
inline constexpr int32_t EdgeT_Byte_12=12;
inline constexpr int32_t EdgeT_Byte_13=13;
inline constexpr int32_t EdgeT_Flags_w=14;
inline constexpr int32_t EdgeT_SizeOf_l=16;
inline constexpr int32_t Vec2W_X=0;
inline constexpr int32_t Vec2W_Z=2;
inline constexpr int32_t Vec2W_SizeOf=4;
inline constexpr int32_t ZEdgeInfoT_EdgeID_w=0;
inline constexpr int32_t ZEdgeInfoT_StartPointID_w=2;
inline constexpr int32_t ZEdgeInfoT_EndPointID_w=4;
inline constexpr int32_t ZEdgeInfoT_Reserved_w=6;
inline constexpr int32_t ZEdgeInfoT_SizeOf_l=8;
inline constexpr int32_t ZEdgePVSHeaderT_ZoneID_w=0;
inline constexpr int32_t ZEdgePVSHeaderT_ListSize_w=2;
inline constexpr int32_t ZEdgePVSHeaderT_EdgeCount_w=4;
inline constexpr int32_t ZEdgePVSHeaderT_ZoneMaskOffset_w=6;
inline constexpr int32_t ZEdgePVSHeaderT_DoorMaskOffset_w=8;
inline constexpr int32_t ZEdgePVSHeaderT_LiftMaskOffset_w=10;
inline constexpr int32_t ZEdgePVSHeaderT_EdgeInfoList_v=12;
inline constexpr int32_t ZEdgePVSHeaderT_SizeOf_l=20;
inline constexpr int32_t ZDoorListMask_SizeOf=2;
inline constexpr int32_t PVST_Zone_w=0;
inline constexpr int32_t PVST_ClipID_w=2;
inline constexpr int32_t PVST_Word_2=4;
inline constexpr int32_t PVST_Word_3=6;
inline constexpr int32_t PVST_SizeOf_l=8;
inline constexpr int32_t NUM_PLR_SHOT_DATA=20;
inline constexpr int32_t NUM_ALIEN_SHOT_DATA=20;
inline constexpr int32_t O_FrameStoreSize=6;
inline constexpr int32_t O_AnimSize=120;
inline constexpr int32_t AmmoGiveLen=44;
inline constexpr int32_t GunGiveLen=24;
inline constexpr int32_t A_FrameLen=11;
inline constexpr int32_t A_OptLen=220;
inline constexpr int32_t A_AnimLen=2420;
inline constexpr int32_t GLFT_OBJ_NAME_LENGTH=20;
inline constexpr int32_t GLFT_GUN_NAME_LENGTH=20;
inline constexpr int32_t GLFT_BUL_NAME_LENGTH=20;
inline constexpr int32_t GLFT_LevelNames_l=64;
inline constexpr int32_t GLFT_ObjGfxNames_l=704;
inline constexpr int32_t GLFT_SFXFilenames_l=2624;
inline constexpr int32_t GLFT_FloorFilename_l=6464;
inline constexpr int32_t GLFT_TextureFilename_l=6528;
inline constexpr int32_t GLFT_GunGFXFilename_l=6720;
inline constexpr int32_t GLFT_StoryFilename_l=6784;
inline constexpr int32_t GLFT_BulletDefs_l=6848;
inline constexpr int32_t GLFT_BulletNames_l=12848;
inline constexpr int32_t GLFT_GunNames_l=13248;
inline constexpr int32_t GLFT_ShootDefs_l=13448;
inline constexpr int32_t GLFT_AlienNames_l=13528;
inline constexpr int32_t GLFT_AlienDefs_l=13928;
inline constexpr int32_t GLFT_FrameData_l=14768;
inline constexpr int32_t GLFT_ObjectNames_l=22448;
inline constexpr int32_t GLFT_ObjectDefs=23048;
inline constexpr int32_t GLFT_ObjectDefAnims_l=24248;
inline constexpr int32_t GLFT_ObjectActAnims_l=27848;
inline constexpr int32_t GLFT_AmmoGive_l=31448;
inline constexpr int32_t GLFT_GunGive_l=32768;
inline constexpr int32_t GLFT_AlienAnims_l=33488;
inline constexpr int32_t GLFT_VectorNames_l=81888;
inline constexpr int32_t GLFT_WallGFXNames_l=83808;
inline constexpr int32_t GLFT_WallHeights_l=84832;
inline constexpr int32_t GLFT_AlienBrights_l=84864;
inline constexpr int32_t GLFT_GunObjects_l=84904;
inline constexpr int32_t GLFT_Player1Graphic_w=84924;
inline constexpr int32_t GLFT_Player2Graphic_w=84926;
inline constexpr int32_t GLFT_FloorData_l=84928;
inline constexpr int32_t GLFT_AlienShootDefs_l=84992;
inline constexpr int32_t GLFT_AmbientSFX_l=85152;
inline constexpr int32_t GLFT_LevelMusic_l=85184;
inline constexpr int32_t GLFT_EchoTable_l=86208;
inline constexpr int32_t GLFT_SizeOf_l=86268;
inline constexpr int32_t NUM_INVENTORY_ITEMS=12;
inline constexpr int32_t NUM_INVENTORY_CONSUMABLES=22;
inline constexpr int32_t MAX_ACHIEVEMENTS=128;
inline constexpr int32_t InvCT_Health_w=0;
inline constexpr int32_t InvCT_JetpackFuel_w=2;
inline constexpr int32_t InvCT_AmmoCounts_vw=4;
inline constexpr int32_t InvCT_SizeOf_l=44;
inline constexpr int32_t InvIT_Shield_w=0;
inline constexpr int32_t InvIT_JetPack_w=2;
inline constexpr int32_t InvIT_Weapons_vw=4;
inline constexpr int32_t InvIT_SizeOf_l=24;
inline constexpr int32_t InvT_Consumables=0;
inline constexpr int32_t InvT_Items=44;
inline constexpr int32_t InvT_SizeOf_l=68;
inline constexpr int32_t GModT_MaxInv=0;
inline constexpr int32_t GModT_NumAchievements=44;
inline constexpr int32_t GModT_AchievementSize=46;
inline constexpr int32_t GModT_SizeOf_l=48;
inline constexpr int32_t GStatT_MaxInv=0;
inline constexpr int32_t GStatT_LevelBestTimes_vl=44;
inline constexpr int32_t GStatT_LevelPlayCounts_vw=108;
inline constexpr int32_t GStatT_LevelWonCounts_vw=140;
inline constexpr int32_t GStatT_LevelFailCounts_vw=172;
inline constexpr int32_t GStatT_LevelImprovedTimeCounts_vw=204;
inline constexpr int32_t GStatT_AlienKills_vw=236;
inline constexpr int32_t GStatT_TotalHealthCollected_w=276;
inline constexpr int32_t GStatT_TotalFuelCollected_w=280;
inline constexpr int32_t GStatT_TotalAmmoFound_vw=284;
inline constexpr int32_t GStatT_Achieved_vb=364;
inline constexpr int32_t GStatT_SizeOf_l=380;
inline constexpr int32_t AchievementT_Name_l=0;
inline constexpr int32_t AchievementT_RewardDesc_l=4;
inline constexpr int32_t AchievementT_RuleMask_w=8;
inline constexpr int32_t AchievementT_RuleId_w=10;
inline constexpr int32_t AchievementT_RuleParams_vb=12;
inline constexpr int32_t AchievementT_HealthCapBonus_w=20;
inline constexpr int32_t AchievementT_HealthBonus_w=22;
inline constexpr int32_t AchievementT_FuelCapBonus_w=24;
inline constexpr int32_t AchievementT_AmmoType_w=26;
inline constexpr int32_t AchievementT_AmmoTypeCapBonus_w=28;
inline constexpr int32_t AchievementT_AmmoTypeBonus_w=30;
inline constexpr int32_t AchievementT_SizeOf_l=32;
inline constexpr int32_t GAME_EVENTBIT_KILL=0;
inline constexpr int32_t GAME_EVENTBIT_ZONE_CHANGE=1;
inline constexpr int32_t GAME_EVENTBIT_LEVEL_START=2;
inline constexpr int32_t GAME_EVENTBIT_ADD_INVENTORY=3;
inline constexpr int32_t DR_Plr_SPC=0;
inline constexpr int32_t DR_Plr=1;
inline constexpr int32_t DR_Bul=2;
inline constexpr int32_t DR_Alien=3;
inline constexpr int32_t DR_Timeout=4;
inline constexpr int32_t DR_Never=5;
inline constexpr int32_t DL_Timeout=0;
inline constexpr int32_t DL_Never=1;
inline constexpr int32_t LVLT_MESSAGE_LENGTH=160;
inline constexpr int32_t LVLT_MESSAGE_COUNT=10;
inline constexpr int32_t LVL_EXPANDED_MAX_ZONE_COUNT=512;
inline constexpr int32_t LVL_MAX_ZONE_COUNT=256;
inline constexpr int32_t LVL_MAX_DOOR_ZONES=16;
inline constexpr int32_t LVL_MAX_LIFT_ZONES=16;
inline constexpr int32_t TBLT_Plr1_StartXPos_w=0;
inline constexpr int32_t TBLT_Plr1_StartZPos_w=2;
inline constexpr int32_t TBLT_Plr1_StartZoneID_w=4;
inline constexpr int32_t TBLT_Plr2_StartXPos_w=6;
inline constexpr int32_t TBLT_Plr2_StartZPos_w=8;
inline constexpr int32_t TBLT_Plr2_StartZoneID_w=10;
inline constexpr int32_t TLBT_NumControlPoints_w=12;
inline constexpr int32_t TLBT_NumPoints_w=14;
inline constexpr int32_t TLBT_NumZones_w=16;
inline constexpr int32_t TLBT_Unknown_w=18;
inline constexpr int32_t TLBT_NumObjects_w=20;
inline constexpr int32_t TLBT_PointsOffset_l=22;
inline constexpr int32_t TLBT_FloorLineOffset_l=26;
inline constexpr int32_t TLBT_ObjectDataOffset_l=30;
inline constexpr int32_t TLBT_ShotDataOffset_l=34;
inline constexpr int32_t TLBT_AlienShotDataOffset_l=38;
inline constexpr int32_t TLBT_ObjectPointsOffset_l=42;
inline constexpr int32_t TLBT_Plr1ObjectOffset_l=46;
inline constexpr int32_t TLBT_Plr2ObjectOffset_l=50;
inline constexpr int32_t TLBT_SizeOf_l=54;
inline constexpr int32_t TLGT_DoorDataOffset_l=0;
inline constexpr int32_t TLGT_LiftDataOffset_l=4;
inline constexpr int32_t TLGT_SwitchDataOffset_l=8;
inline constexpr int32_t TLGT_ZoneGraphAddsOffset_l=12;
inline constexpr int32_t TLGT_ZoneAddsOffset_l=16;
inline constexpr int32_t TLGT_SizeOf_l=20;
inline constexpr int32_t LvlT_Plr1_StartX_w=0;
inline constexpr int32_t LvlT_Plr1_StartZ_w=2;
inline constexpr int32_t LvlT_Plr1_Start_ZoneID_w=4;
inline constexpr int32_t LvlT_Plr2_StartX_w=6;
inline constexpr int32_t LvlT_Plr2_StartZ_w=8;
inline constexpr int32_t LvlT_Plr2_Start_ZoneID_w=10;
inline constexpr int32_t LvlT_NumControlPoints_w=12;
inline constexpr int32_t LvlT_NumPoints_w=14;
inline constexpr int32_t LvlT_NumZones_w=16;
inline constexpr int32_t LvlT_Unk_0_w=18;
inline constexpr int32_t LvlT_NumObjectPoints_w=20;
inline constexpr int32_t LvlT_OffsetToPoints_l=22;
inline constexpr int32_t LvlT_OffsetToFloorLines_l=26;
inline constexpr int32_t LvlT_OffsetToObjects_l=30;
inline constexpr int32_t LvlT_OffsetToPlayerShot_l=34;
inline constexpr int32_t LvlT_OffsetToAlienShot_l=38;
inline constexpr int32_t LvlT_OffsetToObjectPoints_l=42;
inline constexpr int32_t LvlT_OffsetToPlr1Obj_l=46;
inline constexpr int32_t LvlT_OffsetToPlr2Obj_l=50;
inline constexpr int32_t LvlT_ControlPointCoords_vw=54;
inline constexpr int32_t LvlT_SizeOf_l=54;
inline constexpr int32_t ZLiftableT_Bottom_w=0;
inline constexpr int32_t ZLiftableT_Top_w=2;
inline constexpr int32_t ZLiftableT_OpeningSpeed_w=4;
inline constexpr int32_t ZLiftableT_ClosingSpeed_w=6;
inline constexpr int32_t ZLiftableT_OpenDuration_w=8;
inline constexpr int32_t ZLiftableT_OpeningSoundFX_w=10;
inline constexpr int32_t ZLiftableT_ClosingSoundFX_w=12;
inline constexpr int32_t ZLiftableT_OpenedSoundFX_w=14;
inline constexpr int32_t ZLiftableT_ClosedSoundFX_w=16;
inline constexpr int32_t ZLiftableT_Word9_w=18;
inline constexpr int32_t ZLiftableT_Word10_w=20;
inline constexpr int32_t ZLiftableT_Word11_w=22;
inline constexpr int32_t ZLiftableT_Word12_w=24;
inline constexpr int32_t ZLiftableT_GraphicsPtrOffset_l=26;
inline constexpr int32_t ZLiftableT_ZoneID_w=30;
inline constexpr int32_t ZLiftableT_Word16_w=32;
inline constexpr int32_t ZLiftableT_RaiseCondition_b=34;
inline constexpr int32_t ZLiftableT_LowerCondition_b=35;
inline constexpr int32_t ZLiftableT_SizeOf_l=36;
inline constexpr int32_t GAME_DM_VICTORY_MESSAGE_LENGTH=80;
inline constexpr int32_t OPTS_MESSAGE_LENGTH=40;
inline constexpr int32_t MSG_TAG_NARRATIVE=0;
inline constexpr int32_t MSG_TAG_DEFAULT=16384;
inline constexpr int32_t MSG_TAG_OPTIONS=32768;
inline constexpr int32_t MSG_TAG_OTHER=49152;
inline constexpr int32_t SKY_BACKDROP_W=648;
inline constexpr int32_t SKY_BACKDROP_H=240;
inline constexpr int32_t WD_DWidth_l=0;
inline constexpr int32_t WD_LeftX_w=0;
inline constexpr int32_t WD_RightX_w=2;
inline constexpr int32_t WD_DBM_l=4;
inline constexpr int32_t WD_LeftBM_w=4;
inline constexpr int32_t WD_RightBM_w=6;
inline constexpr int32_t WD_DDist_l=8;
inline constexpr int32_t WD_LeftDist_w=8;
inline constexpr int32_t WD_RightDist_w=10;
inline constexpr int32_t WD_DTop_l=12;
inline constexpr int32_t WD_LeftTop_w=12;
inline constexpr int32_t WD_RightTop_w=14;
inline constexpr int32_t WD_DBot_l=16;
inline constexpr int32_t WD_LeftBot_w=16;
inline constexpr int32_t WD_RightBot_w=18;
inline constexpr int32_t WD_Unknown_0_w=20;
inline constexpr int32_t WD_Unknown_1_w=22;
inline constexpr int32_t WD_LeftBrightScaled_l=24;
inline constexpr int32_t WD_LeftBright_w=24;
inline constexpr int32_t WD_RightBright_w=26;
inline constexpr int32_t WD_DHorizBright_l=28;
inline constexpr int32_t WD_UpperLeftBrightScaled_l=32;
inline constexpr int32_t WD_UpperLeftBright_w=32;
inline constexpr int32_t WD_UpperRightBright_w=34;
inline constexpr int32_t WD_DUpperHorizBright_l=36;
inline constexpr int32_t WD_SizeOf_l=40;
}
namespace Fall {
}
namespace Hires {
inline constexpr int32_t CD32VER=0;
inline int32_t loopFrameLimit=-1;
inline bool fsToggleHeld=false;
inline bool headless=true;
inline bool headlessStop=false;
inline std::function<void()> frameSync=nullptr;
inline int32_t presentationPhase=0;
inline constexpr int32_t DMAF_AUDIO=15;
inline constexpr int32_t DMAF_SETCLR=32768;
inline constexpr int32_t DMAF_MASTER=512;
inline constexpr int32_t FS_HEIGHT_HACK=1;
inline constexpr int32_t DISPLAYMSGPORT_HACK=1;
inline constexpr int32_t SCREEN_TITLEBAR_HACK=1;
inline constexpr int32_t SCREEN_WIDTH=320;
inline constexpr int32_t SCREEN_HEIGHT=256;
inline constexpr int32_t FS_HEIGHT=240;
inline constexpr int32_t FS_HEIGHT_C2P_DIFF=8;
inline constexpr int32_t FS_WIDTH=320;
inline constexpr int32_t SMALL_WIDTH=192;
inline constexpr int32_t SMALL_HEIGHT=160;
inline constexpr int32_t VID_FAST_BUFFER_SIZE=81935;
inline constexpr int32_t maxscrdiv=8;
inline constexpr int32_t max3ddiv=5;
inline constexpr int32_t PLR_STAND_HEIGHT=12288;
inline constexpr int32_t PLR_CROUCH_HEIGHT=8192;
inline constexpr int32_t scrheight=80;
inline constexpr int32_t intreqrl=31;
inline constexpr int32_t PLR_MASTER=109;
inline constexpr int32_t PLR_SLAVE=115;
inline constexpr int32_t PLR_SINGLE=110;
inline constexpr int32_t QUIT_KEY=93;
inline std::vector<int32_t> FLOORBRIGHT={(512 * 0),(512 * 1),(512 * 2),(512 * 3),(512 * 4),(512 * 5),(512 * 6),(512 * 7),(512 * 8),(512 * 9),(512 * 10),(512 * 11),(512 * 12),(512 * 13),(512 * 14),(512 * 15),(512 * 16),(512 * 17),(512 * 18),(512 * 19),(512 * 20),(512 * 21),(512 * 22),(512 * 23),(512 * 24),(512 * 25),(512 * 26),(512 * 27),(512 * 28),(512 * 29),(512 * 30),(512 * 31)};
inline bool dbgBadSampleLogged=false;
inline constexpr int32_t MUSIC_END_LOOP_CAP=5000;
inline int32_t mpcA0=0;
inline int32_t mpcA1=0;
inline int32_t dbgMaxSoftVol=0;
inline int32_t dbgMaxSfxPaulaVol=0;
inline bool dbgAudioCrashLogged=false;
inline int32_t dbgGeomZone=-1;
inline int64_t dbgGeomFrame=-1;
inline bool dbgWalk=false;
inline int32_t dbgPlayerTraceEvery=0;
inline int64_t dbgPlayerFrame=0;
inline int32_t dbgAiAliens=-1;
inline int32_t dbgAiFrame=0;
inline int32_t dbgTestSfx=-1;
inline bool dbgForceFire=false;
inline bool dbgForceWalk=false;
inline bool dbgWeaponTest=false;
inline constexpr int32_t DBG_FRAMES_PER_GUN=8;
inline bool dbgSwitchTest=false;
inline bool dbgTestMsg=false;
void draw_FloorLine(int32_t d0,int32_t a3);
void pastfloorbright(int32_t d0,int32_t a0,int32_t a1,int32_t a3);
void draw_WaterSurface(int32_t d1,int32_t d2,int32_t d5,int32_t d7,int32_t a3);
int32_t pastFlats(int32_t a0);
int32_t sideLoopSimple(int32_t a0);
int32_t sideLoopGouraud(int32_t a0);
int32_t Draw_Flats(int32_t a0,int32_t d0);
void MakeSomeNoise();
int32_t makeNoiseChannel(int32_t a3,int32_t d0);
bool sampleAddrOK(int32_t addr);
std::vector<int32_t> guardSample(int32_t a1,int32_t a2,int32_t sampleNum);
void writeLeftChan(int32_t chan,int32_t d5,int32_t d3,int32_t d4,int32_t a1,int32_t a2);
void writeRightChan(int32_t chan,int32_t d5,int32_t d3,int32_t d4,int32_t a1,int32_t a2);
void makeNoiseMono(int32_t d3,int32_t d4,int32_t d0prev);
void startup();
void startup_fail();
void Game_Begin();
void game_main_loop();
int32_t SystemBss_Sys_FPSLimit_w();
int32_t LevelBss_Lvl_ZoneBorderPointsPtr_l();
void WaitTOF();
void loop_FrameClampAndSnapshot1();
void loop_HoldAndDiffs();
void loop_DrawPlayer1();
void loop_DrawPlayer2();
void loop_SetClips();
void computeZoneBrightness(int32_t listPtr);
void markVisibleAndWorry();
int32_t PlayerBss_Lvl_ObjectDataPtr_l();
void loop_ScreenSizeKeys();
void loop_MasterBlock(int32_t a2);
void loop_SlaveBlock(int32_t a2);
void endlevel();
void playEndMusic(int32_t musicData);
void endnomusic();
void closeeverything();
void SetupRenderbufferSize();
void startCopper();
void DrawDisplay();
void nowaterfull();
void Plr1_Control(int32_t a2);
void Plr2_Control(int32_t a2);
void Plr1_Use();
void plr_Use_AnimSetup(int32_t a0,int32_t d0,int32_t graphicOfs);
void Plr2_Use();
void DOALLANIMS();
void doAlienAnim(int32_t a0,int32_t a5);
void floorDamage(int32_t zonePtrL,int32_t stoodTopB,int32_t snapYOffL,int32_t snapTYOffL,int32_t objPtrL);
void dosomething();
void doPlayer1Controls();
void doPlayer2Controls();
void deadViewSetup();
void applyDeadFriction(int32_t xSpd,int32_t zSpd,int32_t xOff,int32_t zOff,int32_t angSpd,int32_t angPos);
void loop_MapScroll(int32_t a5);
void mixPaulaChan(int32_t posA,int32_t posB,int32_t volAsym,int32_t volBsym,int32_t paulaVolReg,int32_t aubufFrontSym,int32_t aubufBackSym,int32_t paulaLCReg);
int32_t wrapSampEnd(int32_t pos,int32_t sampEndSym,int32_t volSym,int32_t chanData32,int32_t chanData2);
void newsampbitl();
void resetSoftAudioChannels();
void JUSTSOUNDS();
void pumpAudioToHost();
bool dbgGeomHit(int32_t zone);
void dbgPlayerTrace();
void dbgAiTrace();
void VBlankInterrupt();
void OtherInter();
void key_interrupt();
}
namespace HiresData {
inline constexpr int32_t _a0=436836;
inline constexpr int32_t LastZonePtr_l=436836;
inline constexpr int32_t xwobble=436840;
inline constexpr int32_t xwobxoff=436844;
inline constexpr int32_t xwobzoff=436846;
inline constexpr int32_t CollId=436848;
inline constexpr int32_t View_KeyLook_w=436850;
inline constexpr int32_t View_LookMin_w=436852;
inline constexpr int32_t View_LookMax_w=436854;
inline constexpr int32_t Game_MasterQuit_b=436856;
inline constexpr int32_t Game_SlaveQuit_b=436857;
inline constexpr int32_t Game_MasterPaused_b=436858;
inline constexpr int32_t Game_SlavePaused_b=436859;
inline constexpr int32_t mang=436860;
inline constexpr int32_t Sys_OldMouseY=436862;
inline constexpr int32_t xmouse=436864;
inline constexpr int32_t Sys_MouseY=436866;
inline constexpr int32_t MAPON=436868;
inline constexpr int32_t draw_RenderMap_b=436870;
inline constexpr int32_t Game_Running_b=436872;
inline constexpr int32_t pretab=436874;
inline constexpr int32_t tab=437130;
inline constexpr int32_t test=453770;
inline constexpr int32_t _testPad=453774;
inline constexpr int32_t _a1=453896;
inline constexpr int32_t Plr_XOff_l=453896;
inline constexpr int32_t Plr_ZOff_l=453900;
inline constexpr int32_t Plr_YOff_l=453904;
inline constexpr int32_t flooryoff=453908;
inline constexpr int32_t XDiff_w=453910;
inline constexpr int32_t ZDiff_w=453912;
inline constexpr int32_t PlayEcho=453914;
inline constexpr int32_t _a2=453916;
inline constexpr int32_t ZonePtr_l=453916;
inline constexpr int32_t Lvl_WalkLinksPtr_l=453920;
inline constexpr int32_t Lvl_FlyLinksPtr_l=453924;
inline constexpr int32_t _anon0=453928;
inline constexpr int32_t Vid_CentreX_w=453932;
inline constexpr int32_t Vid_RightX_w=453934;
inline constexpr int32_t _a3=453936;
inline constexpr int32_t Lvl_CompactMapPtr_l=453936;
inline constexpr int32_t Lvl_BigMapPtr_l=453940;
inline constexpr int32_t Draw_CurrentZonePtr_l=453944;
inline constexpr int32_t Zone_SplitHeight_l=453952;
inline constexpr int32_t draw_WallID_w=453956;
inline constexpr int32_t SMALLIT=453958;
inline constexpr int32_t draw_GouraudFlatsSelected_b=453960;
inline constexpr int32_t lrs=453962;
inline constexpr int32_t Vis_AngPos_w=453964;
inline constexpr int32_t Zone_Bright_w=453966;
inline constexpr int32_t FloorPtBrightsPtr_l=453968;
inline constexpr int32_t draw_UseGouraudFlats_b=453972;
inline constexpr int32_t LASTDH=453974;
inline constexpr int32_t LASTDW=453975;
inline constexpr int32_t Lvl_ExitZoneID_w=453976;
inline constexpr int32_t timetodamage=453978;
inline constexpr int32_t dosounds=453980;
inline constexpr int32_t hitcol=453982;
inline constexpr int32_t Aud_Null1_vw=453986;
inline constexpr int32_t Aud_Null2_vw=454986;
inline constexpr int32_t Aud_Null3_vw=455986;
inline constexpr int32_t Aud_Null4_vw=456986;
inline constexpr int32_t READCONTROLS=457986;
inline constexpr int32_t Vid_VBLCount_l=457988;
inline constexpr int32_t Vid_VBLCountLast_l=457992;
inline constexpr int32_t BollocksRoom=457996;
inline constexpr int32_t _a4=458216;
inline constexpr int32_t leftbright=458216;
inline constexpr int32_t brightspd=458220;
inline constexpr int32_t draw_UseWater_b=458224;
inline constexpr int32_t OLDRET=458226;
inline constexpr int32_t Plr_OldCentre_b=458228;
inline constexpr int32_t OLDGOOD=458230;
inline constexpr int32_t tabheld=458232;
inline constexpr int32_t thistime=458234;
inline constexpr int32_t lasttogsound=458236;
inline constexpr int32_t OLDLTOG=458238;
inline constexpr int32_t alframe=458240;
inline constexpr int32_t alan=458244;
inline constexpr int32_t alanptr=458372;
inline constexpr int32_t STEROPT=458376;
inline constexpr int32_t AUXOBJ=458384;
inline constexpr int32_t backbeat=458386;
inline constexpr int32_t playnull0=458388;
inline constexpr int32_t playnull1=458390;
inline constexpr int32_t playnull2=458392;
inline constexpr int32_t playnull3=458394;
inline constexpr int32_t Aud_SampleNum_w=458396;
inline constexpr int32_t Aud_NoiseX_w=458398;
inline constexpr int32_t Aud_NoiseZ_w=458400;
inline constexpr int32_t Aud_NoiseVol_w=458402;
inline constexpr int32_t Aud_ChannelPick_b=458404;
inline constexpr int32_t IDNUM=458406;
inline constexpr int32_t Aud_NeedLeft_b=458408;
inline constexpr int32_t Aud_NeedRight_b=458409;
inline constexpr int32_t Aud_Stereo_b=458410;
inline constexpr int32_t _aAud=458412;
inline constexpr int32_t CHANNELDATA=458412;
inline constexpr int32_t LEFTCHANDATA=458412;
inline constexpr int32_t _lc1=458416;
inline constexpr int32_t _lc2=458420;
inline constexpr int32_t _lc3=458424;
inline constexpr int32_t RIGHTCHANDATA=458428;
inline constexpr int32_t _rc1=458432;
inline constexpr int32_t _rc2=458436;
inline constexpr int32_t _rc3=458440;
inline constexpr int32_t _chanPad=458444;
inline constexpr int32_t RIGHTPLAYEDTAB=458476;
inline constexpr int32_t LEFTPLAYEDTAB=458556;
inline constexpr int32_t SourceEcho=458636;
inline constexpr int32_t PLREcho=458638;
inline constexpr int32_t LEFTOFFSET=458640;
inline constexpr int32_t RIGHTOFFSET=458644;
inline constexpr int32_t _pathAlign=458648;
inline constexpr int32_t Path=458648;
inline constexpr int32_t endpath=458648;
inline constexpr int32_t pathpt=458648;
inline constexpr int32_t noiseloud=458652;
inline constexpr int32_t _audCh=458656;
inline constexpr int32_t Samp0endLEFT=458868;
inline constexpr int32_t Samp1endLEFT=458872;
inline constexpr int32_t Samp2endLEFT=458876;
inline constexpr int32_t Samp3endLEFT=458880;
inline constexpr int32_t Samp0endRIGHT=458884;
inline constexpr int32_t Samp1endRIGHT=458888;
inline constexpr int32_t Samp2endRIGHT=458892;
inline constexpr int32_t Samp3endRIGHT=458896;
inline constexpr int32_t pos0LEFT=458900;
inline constexpr int32_t pos1LEFT=458904;
inline constexpr int32_t pos2LEFT=458908;
inline constexpr int32_t pos3LEFT=458912;
inline constexpr int32_t pos0RIGHT=458916;
inline constexpr int32_t pos1RIGHT=458920;
inline constexpr int32_t pos2RIGHT=458924;
inline constexpr int32_t pos3RIGHT=458928;
inline constexpr int32_t vol0left=458656;
inline constexpr int32_t vol0right=458658;
inline constexpr int32_t vol1left=458660;
inline constexpr int32_t vol1right=458662;
inline constexpr int32_t vol2left=458664;
inline constexpr int32_t vol2right=458666;
inline constexpr int32_t vol3left=458668;
inline constexpr int32_t vol3right=458670;
inline constexpr int32_t Aupt0=458672;
inline constexpr int32_t Auback0=458676;
inline constexpr int32_t Aupt2=458680;
inline constexpr int32_t Auback2=458684;
inline constexpr int32_t Aupt3=458688;
inline constexpr int32_t Auback3=458692;
inline constexpr int32_t Aupt1=458696;
inline constexpr int32_t Auback1=458700;
inline constexpr int32_t NoiseMade0LEFT=458704;
inline constexpr int32_t NoiseMade1LEFT=458705;
inline constexpr int32_t NoiseMade2LEFT=458706;
inline constexpr int32_t NoiseMade3LEFT=458707;
inline constexpr int32_t NoiseMade0pLEFT=458708;
inline constexpr int32_t NoiseMade1pLEFT=458709;
inline constexpr int32_t NoiseMade2pLEFT=458710;
inline constexpr int32_t NoiseMade3pLEFT=458711;
inline constexpr int32_t NoiseMade0RIGHT=458712;
inline constexpr int32_t NoiseMade1RIGHT=458713;
inline constexpr int32_t NoiseMade2RIGHT=458714;
inline constexpr int32_t NoiseMade3RIGHT=458715;
inline constexpr int32_t NoiseMade0pRIGHT=458716;
inline constexpr int32_t NoiseMade1pRIGHT=458717;
inline constexpr int32_t NoiseMade2pRIGHT=458718;
inline constexpr int32_t NoiseMade3pRIGHT=458719;
inline constexpr int32_t saveinters=458720;
inline constexpr int32_t z=458722;
inline constexpr int32_t notifplaying=458724;
inline constexpr int32_t audpos1=458726;
inline constexpr int32_t audpos1b=458728;
inline constexpr int32_t audpos2=458730;
inline constexpr int32_t audpos2b=458732;
inline constexpr int32_t audpos3=458734;
inline constexpr int32_t audpos3b=458736;
inline constexpr int32_t audpos4=458738;
inline constexpr int32_t audpos4b=458740;
inline constexpr int32_t oktodisplay=458742;
inline constexpr int32_t maxbot=458743;
inline constexpr int32_t tstneg=458745;
inline constexpr int32_t UseAllChannels=458749;
inline constexpr int32_t Lvl_MusicPtr_l=458751;
inline constexpr int32_t tstchip=458755;
inline constexpr int32_t testchip=458759;
inline constexpr int32_t nullsample=458761;
inline constexpr int32_t gameover=458932;
inline constexpr int32_t welldone=489214;
inline constexpr int32_t GLF_DatabasePtr_l=458765;
inline constexpr int32_t GLF_DatabaseName_vb=517288;
inline constexpr int32_t DOANYWATER=458769;
inline constexpr int32_t fillscrnwater=458771;
inline constexpr int32_t DONTDOGUN=458773;
inline constexpr int32_t numsidestd=458775;
inline constexpr int32_t bottomline=458777;
inline constexpr int32_t CLRNOFLOOR=458779;
inline constexpr int32_t _flatAlign0=458784;
inline constexpr int32_t fbr=458784;
inline constexpr int32_t sbr=458786;
inline constexpr int32_t _flatAlign1=458788;
inline constexpr int32_t ypos=458788;
inline constexpr int32_t minz=458792;
inline constexpr int32_t top=458796;
inline constexpr int32_t bottom=458798;
inline constexpr int32_t nfloors=458800;
inline constexpr int32_t lighttype=458802;
inline constexpr int32_t above=458804;
inline constexpr int32_t linedir=458806;
inline constexpr int32_t View2FloorDist=458808;
inline constexpr int32_t movespd=458810;
inline constexpr int32_t largespd=458812;
inline constexpr int32_t disttobot=458816;
inline constexpr int32_t OneOverN_vw=517312;
inline constexpr int32_t tonextline=458818;
inline constexpr int32_t anyclipping=458820;
inline constexpr int32_t _refAlign=458824;
inline constexpr int32_t REFPTR=458824;
inline constexpr int32_t drawit=458828;
inline constexpr int32_t tstwhich=458830;
inline constexpr int32_t whichtile=458832;
inline constexpr int32_t leftedge=458834;
inline constexpr int32_t rightedge=458836;
inline constexpr int32_t _distAlign=458840;
inline constexpr int32_t draw_Distance_l=458840;
inline constexpr int32_t widthleft=458844;
inline constexpr int32_t scaleval=458846;
inline constexpr int32_t _sxAlign=458848;
inline constexpr int32_t sxoff=458848;
inline constexpr int32_t szoff=458852;
inline constexpr int32_t xoff34=458856;
inline constexpr int32_t zoff34=458858;
inline constexpr int32_t scosval=458860;
inline constexpr int32_t ssinval=458862;
inline constexpr int32_t draw_LastWaterFramePtr_l=518368;
inline constexpr int32_t draw_WaterFramePtrs_vl=518336;
inline constexpr int32_t draw_EndWaterFramePtrs_l=518368;
inline constexpr int32_t draw_WaterFramePtr_l=518372;
inline constexpr int32_t wateroff=518376;
inline constexpr int32_t wtan=518380;
inline constexpr int32_t startsmoothx=458864;
inline constexpr int32_t startsmoothz=458866;
inline int32_t makePretab(){return j_unported<int32_t>("HiresData.makePretab");}
inline int32_t makeBollocksRoom(){return j_unported<int32_t>("HiresData.makeBollocksRoom");}
inline int32_t allocAlanTable(){return j_unported<int32_t>("HiresData.allocAlanTable");}
inline int32_t allocSterOpt(){return j_unported<int32_t>("HiresData.allocSterOpt");}
}
namespace Hiresgourwall {
inline constexpr int32_t _a0=2311292;
inline constexpr int32_t draw_GouraudStep_l=2311292;
inline constexpr int32_t draw_GouraudStart_l=2311296;
inline int32_t Draw_ChunkPtr_l(){return j_unported<int32_t>("Hiresgourwall.Draw_ChunkPtr_l");}
inline int32_t Draw_PalettePtr_l(){return j_unported<int32_t>("Hiresgourwall.Draw_PalettePtr_l");}
inline int32_t Draw_WallTexturePtrs_vl(){return j_unported<int32_t>("Hiresgourwall.Draw_WallTexturePtrs_vl");}
inline void DoleftendGOUR(int32_t a0){return j_unported<void>("Hiresgourwall.DoleftendGOUR");}
inline void scrDrawLoop(int32_t a0,int32_t d7){return j_unported<void>("Hiresgourwall.scrDrawLoop");}
inline void scrdrawlopGB(int32_t a0,int32_t d7){return j_unported<void>("Hiresgourwall.scrdrawlopGB");}
inline void draw_WallGouraudShaded(int32_t a0in,int32_t d1,int32_t a2in,int32_t d3,int32_t d4,int32_t d5,int32_t d6,int32_t d7){return j_unported<void>("Hiresgourwall.draw_WallGouraudShaded");}
inline void calcAndDrawG(int32_t a1,int32_t d7){return j_unported<void>("Hiresgourwall.calcAndDrawG");}
inline void computeLoopFirstG(int32_t a1,int32_t d0,int32_t d1,int32_t d4,int32_t d7){return j_unported<void>("Hiresgourwall.computeLoopFirstG");}
inline void putInMapG(){return j_unported<void>("Hiresgourwall.putInMapG");}
inline void OTHERHALFG(int32_t a1,int32_t a0,int32_t d0,int32_t d1,int32_t d2,int32_t d3,int32_t d4,int32_t d5,int32_t d7){return j_unported<void>("Hiresgourwall.OTHERHALFG");}
inline void computeloop2G(int32_t a1,int32_t d0,int32_t d1,int32_t d4,int32_t d7){return j_unported<void>("Hiresgourwall.computeloop2G");}
inline void draw_ScreenWallStripGouraud(int32_t d2,int32_t d3,int32_t d4,int32_t d6,int32_t d7,int32_t a3,int32_t a4,int32_t a5){return j_unported<void>("Hiresgourwall.draw_ScreenWallStripGouraud");}
inline void gotoendG(int32_t d2,int32_t d3,int32_t d4,int32_t d5,int32_t d6,int32_t d7,int32_t a3,int32_t a4,int32_t a5){return j_unported<void>("Hiresgourwall.gotoendG");}
inline void doubwallGOUR(int32_t d2,int32_t d3,int32_t d4,int32_t d5,int32_t d6,int32_t d7,int32_t a3,int32_t a4,int32_t a5){return j_unported<void>("Hiresgourwall.doubwallGOUR");}
inline void ScreenWallstripdrawGOURB(int32_t d2,int32_t d3,int32_t d4,int32_t d6,int32_t d7,int32_t a3,int32_t a4,int32_t a5){return j_unported<void>("Hiresgourwall.ScreenWallstripdrawGOURB");}
inline void gotoendGB(int32_t d2,int32_t d3,int32_t d4,int32_t d5,int32_t d6,int32_t d7,int32_t a3,int32_t a4,int32_t a5){return j_unported<void>("Hiresgourwall.gotoendGB");}
inline void doubwallGOURBIG(int32_t d2,int32_t d3,int32_t d4,int32_t d5,int32_t d6,int32_t d7,int32_t a3,int32_t a4,int32_t a5){return j_unported<void>("Hiresgourwall.doubwallGOURBIG");}
inline void dispatchPackG(int32_t d0,int32_t d1,int32_t d2,int32_t d3,int32_t d4,int32_t d5,int32_t d6,int32_t d7,int32_t a2,int32_t a3,int32_t a4,int32_t a5){return j_unported<void>("Hiresgourwall.dispatchPackG");}
inline void drawwallPACK0G(int32_t d0,int32_t d1,int32_t d3,int32_t d4,int32_t d5,int32_t d6,int32_t d7,int32_t a2,int32_t a3,int32_t a4,int32_t a5){return j_unported<void>("Hiresgourwall.drawwallPACK0G");}
inline void drawwallPACK1G(int32_t d0,int32_t d1,int32_t d3,int32_t d4,int32_t d5,int32_t d6,int32_t d7,int32_t a2,int32_t a3,int32_t a4,int32_t a5){return j_unported<void>("Hiresgourwall.drawwallPACK1G");}
inline void drawwallPACK2G(int32_t d0,int32_t d1,int32_t d3,int32_t d4,int32_t d5,int32_t d6,int32_t d7,int32_t a2,int32_t a3,int32_t a4,int32_t a5){return j_unported<void>("Hiresgourwall.drawwallPACK2G");}
}
namespace Hireswall {
inline int32_t d5wall=0;
inline constexpr int32_t max3ddiv=5;
inline void Doleftend(int32_t a0){return j_unported<void>("Hireswall.Doleftend");}
inline void sometodraw(int32_t a0,int32_t d0,int32_t d1){return j_unported<void>("Hireswall.sometodraw");}
inline void screendivide(int32_t wd,int32_t d0,int32_t d1,int32_t d2,int32_t d3,int32_t d4,int32_t d5,int32_t d7){return j_unported<void>("Hireswall.screendivide");}
inline void scrdrawlop(int32_t a0,int32_t d7){return j_unported<void>("Hireswall.scrdrawlop");}
inline void screendivideFULL(int32_t a0,int32_t d7){return j_unported<void>("Hireswall.screendivideFULL");}
inline void scrdrawlopFULL(int32_t a0,int32_t d7,bool doub){return j_unported<void>("Hireswall.scrdrawlopFULL");}
inline void draw_ScreenWallStrip(int32_t d0,int32_t d2,int32_t d3,int32_t d4,int32_t d5,int32_t d6,int32_t a2,int32_t a3,int32_t a4,int32_t a5){return j_unported<void>("Hireswall.draw_ScreenWallStrip");}
inline void gotoend(int32_t d2,int32_t d3,int32_t d4,int32_t d5,int32_t d6,int32_t a2,int32_t a3,int32_t a4,int32_t a5){return j_unported<void>("Hireswall.gotoend");}
inline void doubwall(int32_t d2,int32_t d3,int32_t d4,int32_t d5,int32_t d6,int32_t a2,int32_t a3,int32_t a4,int32_t a5){return j_unported<void>("Hireswall.doubwall");}
inline void ScreenWallstripdrawBIG(int32_t d0,int32_t d2,int32_t d3,int32_t d4,int32_t d5,int32_t d6,int32_t a2,int32_t a3,int32_t a4,int32_t a5){return j_unported<void>("Hireswall.ScreenWallstripdrawBIG");}
inline void gotoendBIG(int32_t d2,int32_t d3,int32_t d4,int32_t d5,int32_t d6,int32_t a2,int32_t a3,int32_t a4,int32_t a5){return j_unported<void>("Hireswall.gotoendBIG");}
inline void doubwallBIG(int32_t d2,int32_t d3,int32_t d4,int32_t d5,int32_t d6,int32_t a2,int32_t a3,int32_t a4,int32_t a5){return j_unported<void>("Hireswall.doubwallBIG");}
inline void dispatchPack(int32_t d0,int32_t d1,int32_t d2,int32_t d3,int32_t d4,int32_t d6,int32_t d7,int32_t a2,int32_t a3,int32_t a4,int32_t a5){return j_unported<void>("Hireswall.dispatchPack");}
inline int32_t Draw_ChunkPtr_l(){return j_unported<int32_t>("Hireswall.Draw_ChunkPtr_l");}
inline int32_t Draw_PalettePtr_l(){return j_unported<int32_t>("Hireswall.Draw_PalettePtr_l");}
inline void draw_WallSimpleShaded(int32_t a0in,int32_t d1,int32_t a2in,int32_t d3,int32_t d4,int32_t d5,int32_t d6,int32_t d7){return j_unported<void>("Hireswall.draw_WallSimpleShaded");}
inline void calcAndDraw(int32_t a1,int32_t d7){return j_unported<void>("Hireswall.calcAndDraw");}
inline void computeLoopFirst(int32_t a1,int32_t d0,int32_t d1,int32_t d4,int32_t d7){return j_unported<void>("Hireswall.computeLoopFirst");}
inline void putInMap(){return j_unported<void>("Hireswall.putInMap");}
inline void OTHERHALF(int32_t a1,int32_t a0,int32_t d0,int32_t d1,int32_t d2,int32_t d3,int32_t d4,int32_t d5,int32_t d7){return j_unported<void>("Hireswall.OTHERHALF");}
inline void computeloop2(int32_t a1,int32_t d0,int32_t d1,int32_t d4,int32_t d7){return j_unported<void>("Hireswall.computeloop2");}
inline int32_t Draw_Wall(int32_t a0){return j_unported<int32_t>("Hireswall.Draw_Wall");}
inline bool cliptotestfirstbehind(int32_t a5,int32_t d0,int32_t d2){return j_unported<bool>("Hireswall.cliptotestfirstbehind");}
inline bool cliptotestsecbehind(int32_t a5,int32_t d0,int32_t d2){return j_unported<bool>("Hireswall.cliptotestsecbehind");}
inline bool pastclip(int32_t a5,int32_t d0,int32_t d2){return j_unported<bool>("Hireswall.pastclip");}
inline void cantTell(int32_t a5,int32_t d0,int32_t d2){return j_unported<void>("Hireswall.cantTell");}
inline int32_t d5current(){return j_unported<int32_t>("Hireswall.d5current");}
inline int32_t Draw_WallTexturePtrs_vl(){return j_unported<int32_t>("Hireswall.Draw_WallTexturePtrs_vl");}
inline int32_t max3ddiv_fn(){return j_unported<int32_t>("Hireswall.max3ddiv");}
}
namespace HireswallData {
inline constexpr int32_t _a0=2311300;
inline constexpr int32_t Draw_LeftClip_l=2311300;
inline constexpr int32_t Draw_LeftClip_w=2311302;
inline constexpr int32_t Draw_RightClip_l=2311304;
inline constexpr int32_t Draw_RightClip_w=2311306;
inline constexpr int32_t Draw_LeftClipAndLast_w=2311308;
inline constexpr int32_t draw_StripData_w=2311310;
inline constexpr int32_t draw_StripData_b=2311311;
inline constexpr int32_t _a1=2311312;
inline constexpr int32_t draw_LineOffsetBuffer_vl=2311312;
inline constexpr int32_t _a2=2312336;
inline constexpr int32_t Draw_PointBrightsPtr_l=2312336;
inline constexpr int32_t draw_WallTextureHeightMask_w=2312340;
inline constexpr int32_t draw_WallTextureHeightShift_w=2312342;
inline constexpr int32_t draw_WallTextureWidthMask_w=2312344;
inline constexpr int32_t Vis_SinVal_w=2312346;
inline constexpr int32_t Vis_CosVal_w=2312348;
inline constexpr int32_t draw_TopClip_w=2312350;
inline constexpr int32_t draw_BottomClip_w=2312352;
inline constexpr int32_t _a3=2312356;
inline constexpr int32_t draw_TopOfWall_l=2312356;
inline constexpr int32_t draw_BottomOfWall_l=2312360;
inline constexpr int32_t draw_LBR_w=2312364;
inline constexpr int32_t draw_TLBR_w=2312366;
inline constexpr int32_t draw_LeftWallBright_w=2312368;
inline constexpr int32_t draw_RightWallBright_w=2312370;
inline constexpr int32_t draw_LeftWallTopBright_w=2312372;
inline constexpr int32_t draw_RightWallTopBright_w=2312374;
inline constexpr int32_t draw_StripTop_w=2312376;
inline constexpr int32_t draw_StripBottom_w=2312378;
inline constexpr int32_t draw_WallLastStripX_w=2312380;
inline constexpr int32_t draw_FromTile_w=2312382;
inline constexpr int32_t draw_AngleBright_w=2312386;
inline constexpr int32_t draw_WallIterations_w=2312388;
inline constexpr int32_t draw_MultCount_w=2312390;
inline constexpr int32_t Draw_GoodRender_b=2312412;
inline constexpr int32_t draw_IterationTable_vw=2312416;
inline constexpr int32_t draw_BrightnessScaleTable_vw=2314464;
inline constexpr int32_t draw_TimesLargeThru_vl=2314626;
inline constexpr int32_t draw_TotalYOffset_w=2314946;
inline constexpr int32_t draw_WallYOffset_w=2314948;
inline constexpr int32_t draw_WallBrightOffset_w=2314950;
inline constexpr int32_t draw_WallLeftPoint_w=2314952;
inline constexpr int32_t draw_WallRightPoint_w=2314954;
inline constexpr int32_t draw_WhichPBR_w=2314956;
inline constexpr int32_t draw_WhichLeftPoint_w=2314958;
inline constexpr int32_t draw_WhichRightPoint_w=2314960;
inline constexpr int32_t draw_OtherZone_w=2314962;
inline constexpr int32_t _a4=2312392;
inline constexpr int32_t TOTHEMIDDLE=2312392;
inline constexpr int32_t Vid_BottomY_w=2312394;
inline constexpr int32_t Vid_CentreY_w=2312396;
inline constexpr int32_t TOPOFFSET=2312398;
inline constexpr int32_t BIGMIDDLEY=2312400;
inline constexpr int32_t SMIDDLEY=2312404;
inline constexpr int32_t STOPOFFSET=2312406;
inline constexpr int32_t SBIGMIDDLEY=2312408;
}
namespace M68k {
int32_t swap(int32_t d);
int32_t setw(int32_t reg,int32_t v);
int32_t setb(int32_t reg,int32_t v);
int32_t w(int32_t reg);
int32_t uw(int32_t reg);
int32_t b(int32_t reg);
int32_t ub(int32_t reg);
int32_t extw(int32_t reg);
int32_t extl(int32_t reg);
int32_t muls(int32_t dN,int32_t src);
int32_t mulu(int32_t dN,int32_t src);
int32_t divs(int32_t dN,int32_t src);
int32_t divu(int32_t dN,int32_t src);
int32_t asrw(int32_t reg,int32_t n);
int32_t lsrw(int32_t reg,int32_t n);
int32_t lslw(int32_t reg,int32_t n);
int32_t addw(int32_t reg,int32_t v);
int32_t subw(int32_t reg,int32_t v);
int32_t negw(int32_t reg);
}
namespace Macros {
void FREE_OBJ(int32_t aN);
void FREE_OBJ_2(int32_t aN,int32_t off);
void FREE_ENT(int32_t aN);
void FREE_ENT_2(int32_t aN,int32_t off);
void SET_MEM_BIT(int32_t bit,int32_t addr);
}
namespace MenuNb {
inline constexpr int32_t PS=10240;
inline int32_t slider_xpos=0;
inline int32_t mnu_waitFlag=0;
inline int32_t rorw1(int32_t v){return j_unported<int32_t>("MenuNb.rorw1");}
inline void mnu_initrnd(){return j_unported<void>("MenuNb.mnu_initrnd");}
inline void getrnd(){return j_unported<void>("MenuNb.getrnd");}
inline void mnu_copycredz(){return j_unported<void>("MenuNb.mnu_copycredz");}
inline void mnu_cls(){return j_unported<void>("MenuNb.mnu_cls");}
inline void mnu_printxy(int32_t a0,int32_t d0,int32_t d1){return j_unported<void>("MenuNb.mnu_printxy");}
inline void mnu_animcursor(){return j_unported<void>("MenuNb.mnu_animcursor");}
inline void mnu_vblint(){return j_unported<void>("MenuNb.mnu_vblint");}
inline void mnu_plot(){return j_unported<void>("MenuNb.mnu_plot");}
inline void mnu_openmenu(int32_t a0){return j_unported<void>("MenuNb.mnu_openmenu");}
inline void mnu_redraw(int32_t a0){return j_unported<void>("MenuNb.mnu_redraw");}
inline void mnu_update(int32_t a0){return j_unported<void>("MenuNb.mnu_update");}
inline void mnu_putcycler(int32_t d0,int32_t d1,int32_t a0){return j_unported<void>("MenuNb.mnu_putcycler");}
inline void mnu_putslider(int32_t d0,int32_t d1,int32_t d7,int32_t a0){return j_unported<void>("MenuNb.mnu_putslider");}
inline void mnu_docursor(){return j_unported<void>("MenuNb.mnu_docursor");}
inline int32_t mnu_waitmenu(){return j_unported<int32_t>("MenuNb.mnu_waitmenu");}
inline int32_t selection(){return j_unported<int32_t>("MenuNb.selection");}
inline int32_t mnu_getrawvalue(){return j_unported<int32_t>("MenuNb.mnu_getrawvalue");}
inline void MenuC_WaitTOF(){return j_unported<void>("MenuNb.MenuC_WaitTOF");}
}
namespace Newaliencontrol {
inline bool dbgCollect=false;
void ItsAnAlien(int32_t a0);
void ItsAnObject(int32_t a0);
int32_t worryHeight(int32_t a0,int32_t a2stats);
void GUNHELD(int32_t a0,int32_t a1);
void Collectable(int32_t a0,int32_t a1);
void Activatable(int32_t a0,int32_t a1);
void ACTIVATED(int32_t a0,int32_t a1,int32_t d0);
void Destructable(int32_t a0,int32_t a1);
void StillHere(int32_t a0,int32_t a1);
void Decoration(int32_t a0,int32_t a1);
void obj_SetInventoryPointers(int32_t a0);
int32_t Plr1_CollectItem(int32_t a0);
int32_t Plr2_CollectItem(int32_t a0);
int32_t Plr1_CheckObjectCollide(int32_t a0);
int32_t Plr2_CheckObjectCollide(int32_t a0);
void animObj(int32_t a0,int32_t a2,int32_t animTableOffset);
void DEFANIMOBJ(int32_t a0,int32_t a2);
void ACTANIMOBJ(int32_t a0,int32_t a2);
int32_t ViewpointToDraw(int32_t a0);
void RunAround(int32_t a0);
void SHOOTPLAYER1(int32_t a0,int32_t a1);
void FireAtPlayer1(int32_t a0);
void SHOOTPLAYER2(int32_t a0,int32_t a1);
void FireAtPlayer2(int32_t a0,int32_t a1);
}
namespace NewaliencontrolData {
inline constexpr int32_t _a0=2314964;
inline constexpr int32_t AlienAnimPtr_l=2314964;
inline constexpr int32_t ALIENBRIGHT=2314968;
inline constexpr int32_t ALIENECHO=2314970;
inline constexpr int32_t diststowall=2314972;
inline constexpr int32_t _dtw1=2314976;
inline constexpr int32_t _dtw2=2314980;
inline constexpr int32_t _a2=2314984;
inline constexpr int32_t obj_ConsumablePtr_l=2314984;
inline constexpr int32_t obj_ItemsPtr_l=2314988;
inline constexpr int32_t obj_StatPtr_l=2314992;
inline constexpr int32_t THISPLRxoff=2314996;
inline constexpr int32_t THISPLRzoff=2314998;
inline constexpr int32_t deadframe=2315000;
inline constexpr int32_t screamsound=2315004;
inline constexpr int32_t nasheight=2315006;
inline constexpr int32_t tempcos=2315008;
inline constexpr int32_t tempsin=2315010;
inline constexpr int32_t tempx=2315012;
inline constexpr int32_t tempz=2315014;
inline constexpr int32_t bbbb=2315016;
inline constexpr int32_t tsx=2315018;
inline constexpr int32_t tsz=2315020;
inline constexpr int32_t fsx=2315022;
inline constexpr int32_t fsz=2315024;
inline constexpr int32_t futurex=2315026;
inline constexpr int32_t futurez=2315028;
inline constexpr int32_t _a1=2315032;
inline constexpr int32_t backupZonePtr_l=2315032;
inline constexpr int32_t SHOTYOFF=2315036;
inline constexpr int32_t SHOTTYPE=2315040;
inline constexpr int32_t SHOTPOWER=2315042;
inline constexpr int32_t SHOTSPEED=2315044;
inline constexpr int32_t SHOTOFFMULT=2315046;
inline constexpr int32_t SHOTSHIFT=2315048;
inline constexpr int32_t SHOTINTOP=2315050;
}
namespace Newanims {
inline constexpr int32_t BP=0;
inline constexpr int32_t RPL=1;
inline constexpr int32_t BPA=2;
inline constexpr int32_t RPLA=3;
inline constexpr int32_t CHECKSWITCHES=0;
inline constexpr int32_t BACKTOP2=1;
inline constexpr int32_t BACKTOEND=2;
inline constexpr int32_t NOBUTT=3;
inline constexpr int32_t DOALIFT=0;
inline constexpr int32_t BACKFROMLIFT=1;
inline constexpr int32_t LIFT_SIMPLE=2;
inline int32_t liftSpeed=65532;
inline constexpr int32_t DOADOOR=0;
inline constexpr int32_t BACKFROMTST=1;
inline constexpr int32_t DOOR_SIMPLE=2;
inline bool dbgDoors=false;
void Anim_BrightenPointsAngle(int32_t d0,int32_t d1,int32_t d2,int32_t d3,int32_t d4);
void anim_BrightenPoints(int32_t d0,int32_t d1,int32_t d2,int32_t d3);
void brightenCore(int32_t lbl,int32_t d0,int32_t d1,int32_t d2,int32_t d3,int32_t a6);
void applyBright(int32_t a0,int32_t a2,int32_t d0,int32_t d5);
void brightOne(int32_t a2off,int32_t yval,bool negd4,int32_t d0,int32_t d5);
void darkenPoints(int32_t d0,int32_t d1,int32_t d2,int32_t d3);
void Flash(int32_t d0,int32_t d1);
void Anim_ExplodeIntoBits(int32_t d0,int32_t d2,int32_t d3,int32_t a0);
void brightanim();
void BACKSFX();
int32_t DoWaterAnims(int32_t a0);
void SwitchRoutine();
void switchSpace(int32_t a0,int32_t a1,int32_t d0,int32_t xoffSym,int32_t zoffSym,bool plr2);
void LiftRoutine();
int32_t liftLowerMask(int32_t d5);
int32_t liftRaiseMask(int32_t d4);
void DoorRoutine();
void dbgDoorLock(int32_t porte,int32_t masque);
void dbgDoorTrigger(int32_t porte,int32_t attendu,int32_t touche);
int32_t doorOpenMask(int32_t d5);
int32_t doorCloseMask(int32_t a6);
void objmoveanim();
void ObjectHandler();
void ComputeBlast(int32_t d0,int32_t a0);
void ItsABullet(int32_t a0);
void bulletImpactFX(int32_t a0,int32_t a6,bool setViewerTop);
int32_t Draw_SkyBackdrop(int32_t a0);
}
namespace NewanimsData {
inline constexpr int32_t _a0=2315052;
inline constexpr int32_t Anim_LightingEnabled_b=2315052;
inline constexpr int32_t anim_LiftAtTop_b=2315053;
inline constexpr int32_t anim_LiftAtBottom_b=2315054;
inline constexpr int32_t anim_DoorOpen_b=2315055;
inline constexpr int32_t anim_DoorClosed_b=2315056;
inline constexpr int32_t _a1=2315058;
inline constexpr int32_t anim_ExpRadius_w=2315058;
inline constexpr int32_t _a3=2315060;
inline constexpr int32_t tempxoff=2315060;
inline constexpr int32_t tempzoff=2315062;
inline constexpr int32_t tempRoompt=2315064;
inline constexpr int32_t bulyspd=2315068;
inline constexpr int32_t closedist=2315070;
inline constexpr int32_t _a2=2315072;
inline constexpr int32_t tmpangpos=2315072;
inline constexpr int32_t _a4=2315076;
inline constexpr int32_t timeout=2315076;
inline constexpr int32_t anim_Brightness_w=2315078;
inline constexpr int32_t BLOODYGREATBOMB=2315080;
inline constexpr int32_t _a5=2315082;
inline constexpr int32_t MOVING=2315082;
inline constexpr int32_t _a6=2315084;
inline constexpr int32_t tmpnewx=2315084;
inline constexpr int32_t tmpnewz=2315088;
inline constexpr int32_t hithit=2315092;
inline constexpr int32_t sqrnum=2315096;
inline constexpr int32_t allbars=2315100;
inline constexpr int32_t backrout=2315104;
inline constexpr int32_t NUMTOCHECK=2315904;
inline constexpr int32_t Zone_Count_w=2315906;
inline constexpr int32_t RipTear=2315908;
inline constexpr int32_t otherrip=2315912;
inline constexpr int32_t Conditions=2315916;
inline constexpr int32_t BRIGHT_ANIM_LIST_END=-1;
inline constexpr int32_t BRIGHT_ANIM_END=999;
inline constexpr int32_t anim_BrightessAnimPtrs_vl=2316524;
inline constexpr int32_t anim_BrightnessAnimStartPtrs_vl=2316556;
inline constexpr int32_t anim_BrightPulse1_vw=2315920;
inline constexpr int32_t anim_BrightPulse2_vw=2316002;
inline constexpr int32_t anim_BrightPulse3_vw=2316084;
inline constexpr int32_t anim_BrightPulse4_vw=2316166;
inline constexpr int32_t anim_BrightPulse5_vw=2316248;
inline constexpr int32_t anim_BrightFlicker1_vw=2316330;
inline constexpr int32_t anim_BrightFlicker2_vw=2316448;
inline std::vector<int32_t> seq(int32_t from,int32_t to){return j_unported<std::vector<int32_t>>("NewanimsData.seq");}
inline std::vector<int32_t> rep(int32_t n,int32_t v){return j_unported<std::vector<int32_t>>("NewanimsData.rep");}
inline std::vector<int32_t> end(){return j_unported<std::vector<int32_t>>("NewanimsData.end");}
inline int32_t emit(std::vector<int32_t>& parts){return j_unported<int32_t>("NewanimsData.emit");}
}
namespace Newplayershoot {
inline int32_t dbgLastTestGun=-1;
void Plr1_Shot();
void Plr2_Shot();
void plrShot(int32_t p);
void nothingToShoot(int32_t p,int32_t a5,int32_t a6,int32_t xoff,int32_t zoff,int32_t yoff,int32_t sinVal,int32_t cosVal,int32_t zonePtr);
void fireProjectile(int32_t p,int32_t a5,int32_t a6);
void hitscanSucceeded(int32_t d0,int32_t a4,int32_t a5);
void hitscanFailed(int32_t p,int32_t a4,int32_t a0term,int32_t xoff,int32_t zoff,int32_t yoff,int32_t zonePtr);
void setupBulletMove(int32_t zonePtr);
void advanceMove();
}
namespace NewplayershootData {
inline constexpr int32_t _a0=2316584;
inline constexpr int32_t targetydiff=2316584;
inline constexpr int32_t targdist=2316588;
inline constexpr int32_t tempangpos=2316590;
inline constexpr int32_t MaxFrame=2316592;
inline constexpr int32_t BULTYPE=2316594;
inline constexpr int32_t AmmoInMyGun=2316596;
inline constexpr int32_t _a1=2316600;
inline constexpr int32_t tempyoff=2316600;
inline constexpr int32_t BulletSpd=2316604;
inline constexpr int32_t tempStoodInTop=2316606;
inline constexpr int32_t tempxdir=2316608;
inline constexpr int32_t tempzdir=2316610;
inline constexpr int32_t tempgun=2316612;
inline constexpr int32_t tstfire=2316614;
}
namespace Objdrawhires {
inline constexpr int32_t DRAW_BITMAP_NEAR_PLANE=25;
inline constexpr int32_t DRAW_VECTOR_NEAR_PLANE=130;
inline constexpr int32_t DRAW_VECTOR_MAX_Z=16383;
inline bool warnedEmptyBrightRing=false;
inline bool dbgTex=false;
inline int32_t dbgTexModel=-1;
inline int32_t dbgForceFrame=-1;
inline bool dbgCheesy=false;
inline int32_t dbgCurModel=0;
inline constexpr int32_t POLYBOT_OFS=-7680;
inline int32_t Draw_Objects(int32_t a0){return j_unported<int32_t>("Objdrawhires.Draw_Objects");}
inline void draw_Object(int32_t d0){return j_unported<void>("Objdrawhires.draw_Object");}
inline int32_t draw_FindRoughAngle(int32_t d4,int32_t d5){return j_unported<int32_t>("Objdrawhires.draw_FindRoughAngle");}
inline int32_t draw_ResetAngleBrights(){return j_unported<int32_t>("Objdrawhires.draw_ResetAngleBrights");}
inline void draw_CalcBrightsInZone(int32_t d0,int32_t a2){return j_unported<void>("Objdrawhires.draw_CalcBrightsInZone");}
inline void draw_TweenBrights(int32_t a0){return j_unported<void>("Objdrawhires.draw_TweenBrights");}
inline void warnEmptyBrightRing(int32_t a0){return j_unported<void>("Objdrawhires.warnEmptyBrightRing");}
inline void draw_CalcBrightRings(){return j_unported<void>("Objdrawhires.draw_CalcBrightRings");}
inline void drawBitmap(int32_t a0,int32_t a1,int32_t d0,int32_t d1){return j_unported<void>("Objdrawhires.drawBitmap");}
inline void drawBitmapGlare(int32_t a0,int32_t a1){return j_unported<void>("Objdrawhires.drawBitmapGlare");}
inline void drawBitmapAdditive(int32_t d2,int32_t d3,int32_t d4,int32_t d5,int32_t d7,int32_t a1,int32_t a2){return j_unported<void>("Objdrawhires.drawBitmapAdditive");}
inline void drawBitmapLighted(int32_t d2,int32_t d3,int32_t d4,int32_t d5,int32_t d7,int32_t a1in,int32_t a2in){return j_unported<void>("Objdrawhires.drawBitmapLighted");}
inline void draw_PolygonModel(int32_t a0,int32_t a1,int32_t d0,int32_t d1){return j_unported<void>("Objdrawhires.draw_PolygonModel");}
inline void doapoly(int32_t a1){return j_unported<void>("Objdrawhires.doapoly");}
inline void fillPolyFlat(int32_t a0,int32_t a1,int32_t a2,int32_t a4,int32_t a6,int32_t d7){return j_unported<void>("Objdrawhires.fillPolyFlat");}
inline void fillPolyGlare(int32_t a0,int32_t a1,int32_t a2,int32_t a4,int32_t a6,int32_t d7){return j_unported<void>("Objdrawhires.fillPolyGlare");}
inline void fillPolyGouraud(int32_t a0,int32_t a1,int32_t a2,int32_t a4,int32_t a6,int32_t d7Col){return j_unported<void>("Objdrawhires.fillPolyGouraud");}
inline void fillPolyHoles(int32_t a0,int32_t a1,int32_t a2,int32_t a4,int32_t a6,int32_t d7){return j_unported<void>("Objdrawhires.fillPolyHoles");}
inline int32_t draw_PutInLines(int32_t a1,int32_t d7){return j_unported<int32_t>("Objdrawhires.draw_PutInLines");}
inline int32_t draw_PutInLinesGouraud(int32_t a1,int32_t d7){return j_unported<int32_t>("Objdrawhires.draw_PutInLinesGouraud");}
}
namespace ObjdrawhiresData {
inline constexpr int32_t _a0=2316616;
inline constexpr int32_t draw_TopY_3D_l=2316616;
inline constexpr int32_t draw_BottomY_3D_l=2316620;
inline constexpr int32_t _a1=2316624;
inline constexpr int32_t draw_ObjScaleCols_vw=2316624;
inline constexpr int32_t draw_BasePalPtr_l=2316786;
inline constexpr int32_t draw_WhichLightPal_b=2316790;
inline constexpr int32_t draw_FlipIt_b=2316791;
inline constexpr int32_t draw_LightIt_b=2316792;
inline constexpr int32_t draw_Additive_b=2316793;
inline constexpr int32_t draw_TempPtr_l=2316796;
inline constexpr int32_t polybright=2316800;
inline constexpr int32_t firstpt=2316804;
inline constexpr int32_t PolyAng=2316806;
inline constexpr int32_t tstdca=2316808;
inline constexpr int32_t offtopby=2316814;
inline constexpr int32_t LinesPtr=2316816;
inline constexpr int32_t PtsPtr=2316820;
inline constexpr int32_t draw_PreGouraud_b=2316824;
inline constexpr int32_t draw_Gouraud_b=2316825;
inline constexpr int32_t draw_PreHoles_b=2316826;
inline constexpr int32_t draw_Holes_b=2316827;
inline constexpr int32_t ontoscrGL=2316828;
inline constexpr int32_t ontoscrg=2317852;
inline constexpr int32_t ontoscrh=2318876;
inline constexpr int32_t GUARDBAND=8191;
inline int32_t newYOffsetTable(){return j_unported<int32_t>("ObjdrawhiresData.newYOffsetTable");}
}
namespace Objectmove {
void MoveObject();
int32_t sqrtNewton(int32_t d2,int32_t iterations);
void HeadTowards();
void CalcDist();
void HeadTowardsAng();
void CheckHit(int32_t d2);
int32_t GetNextCPt(int32_t d0,int32_t d1);
void CanItBeSeenAng();
void CanItBeSeen();
void inList(int32_t a0,int32_t d0);
int32_t GetRand();
void GoInDirection(int32_t d0);
void Obj_DoCollision(int32_t a2);
int32_t CheckTeleport();
void FindCollisionPt();
void FindCloseRoom(int32_t d0,int32_t a0);
}
namespace ObjectmoveData {
inline constexpr int32_t _a0=2319900;
inline constexpr int32_t obj_RoomPathPtr_l=2319900;
inline constexpr int32_t Obj_ExtLen_w=2319904;
inline constexpr int32_t WallXSize_w=2319906;
inline constexpr int32_t WallZSize_w=2319908;
inline constexpr int32_t WallLength_w=2319910;
inline constexpr int32_t obj_QuitLimit_w=2319912;
inline constexpr int32_t Obj_AwayFromWall_b=2319914;
inline constexpr int32_t Obj_WallBounce_b=2319915;
inline constexpr int32_t _a1=2319916;
inline constexpr int32_t oldx=2319916;
inline constexpr int32_t oldz=2319920;
inline constexpr int32_t oldy=2319924;
inline constexpr int32_t newx=2319928;
inline constexpr int32_t newz=2319932;
inline constexpr int32_t newy=2319936;
inline constexpr int32_t xdiff=2319940;
inline constexpr int32_t zdiff=2319944;
inline constexpr int32_t Obj_ZonePtr_l=2319948;
inline constexpr int32_t obj_ZoneBackupPtr_l=2319952;
inline constexpr int32_t deltax=2319956;
inline constexpr int32_t speed=2319958;
inline constexpr int32_t wallflags=2319960;
inline constexpr int32_t distaway=2319962;
inline constexpr int32_t thingheight=2319964;
inline constexpr int32_t StepUpVal=2319968;
inline constexpr int32_t StepDownVal=2319972;
inline constexpr int32_t wallhitheight=2319976;
inline constexpr int32_t LowerFloorHeight=2319980;
inline constexpr int32_t LowerRoofHeight=2319984;
inline constexpr int32_t UpperFloorHeight=2319988;
inline constexpr int32_t UpperRoofHeight=2319992;
inline constexpr int32_t billy=2319996;
inline constexpr int32_t StoodInTop=2320004;
inline constexpr int32_t hitwall=2320005;
inline constexpr int32_t exitfirst=2320006;
inline constexpr int32_t _e0=2320008;
inline constexpr int32_t counterer=2320008;
inline constexpr int32_t CosRet=2320010;
inline constexpr int32_t SinRet=2320012;
inline constexpr int32_t _a2=2320016;
inline constexpr int32_t AngRet=2320016;
inline constexpr int32_t Range=2320018;
inline constexpr int32_t GotThere=2320020;
inline constexpr int32_t shovex=2320022;
inline constexpr int32_t shovez=2320024;
inline constexpr int32_t canshove=2320026;
inline constexpr int32_t PLR2_pushx=2320028;
inline constexpr int32_t PLR2_pushz=2320032;
inline constexpr int32_t PLR2_opushx=2320036;
inline constexpr int32_t PLR2_opushz=2320040;
inline constexpr int32_t PLR1_pushx=2320044;
inline constexpr int32_t PLR1_pushz=2320048;
inline constexpr int32_t PLR1_opushx=2320052;
inline constexpr int32_t PLR1_opushz=2320056;
inline constexpr int32_t ONLYSEE=2320060;
inline constexpr int32_t _a3=2320064;
inline constexpr int32_t Obj_FromZonePtr_l=2320064;
inline constexpr int32_t Obj_ToZonePtr_l=2320068;
inline constexpr int32_t CanSee=2320072;
inline constexpr int32_t Facedir=2320074;
inline constexpr int32_t _a4=2320076;
inline constexpr int32_t Viewerx=2320076;
inline constexpr int32_t Viewerz=2320080;
inline constexpr int32_t Targetx=2320084;
inline constexpr int32_t Targetz=2320088;
inline constexpr int32_t ViewerTop=2320092;
inline constexpr int32_t TargetTop=2320093;
inline constexpr int32_t Viewery=2320094;
inline constexpr int32_t Targety=2320096;
inline constexpr int32_t _e1=2320098;
inline constexpr int32_t clipstocheck=2320098;
inline constexpr int32_t donessomething=2320102;
inline constexpr int32_t Rand1=2320104;
inline constexpr int32_t Obj_CollideFlags_l=2320106;
inline constexpr int32_t tmp_zone_id_w=2320110;
inline constexpr int32_t FromZone=2320112;
inline constexpr int32_t OKTEL=2320114;
inline constexpr int32_t floortemp=2320116;
inline constexpr int32_t xd=2320120;
inline constexpr int32_t zd=2320122;
inline constexpr int32_t possclose=2320124;
}
namespace Orderzones {
inline constexpr int32_t _a0=2320324;
inline constexpr int32_t Zone_MovementMask_l=2320324;
inline constexpr int32_t tmp_ListOfGraphRoomsPtr_l=2320328;
inline constexpr int32_t zone_LastPosition_vw=2320332;
void Zone_OrderZones();
int32_t zone_InsertList(int32_t a0,int32_t a1,int32_t a4,int32_t a6,int32_t d6);
}
namespace Pauseopts {
inline constexpr int32_t PLR_SLAVE=115;
inline constexpr int32_t PAUSETEXT=2320336;
inline constexpr int32_t ENDPAUSETEXT=2320416;
inline constexpr int32_t TOPPOPT=2320416;
inline void readPauseJoy(){return j_unported<void>("Pauseopts.readPauseJoy");}
inline void Game_Pause(){return j_unported<void>("Pauseopts.Game_Pause");}
}
namespace Plr1control {
void Plr1_ShowGunName();
void Plr1_MouseControl();
void Plr1_KeyboardControl();
void Plr1_JoystickControl();
void Plr1_FootstepFX();
void Plr1_Fall();
void Plr1_FollowPath();
}
namespace Plr2control {
void Plr2_ShowGunName();
void Plr2_MouseControl();
void Plr2_KeyboardControl();
void Plr2_JoystickControl();
void Plr2_FootstepFX();
void Plr2_Fall();
}
namespace SerialNightmare {
inline void SERSEND(int32_t d1){return j_unported<void>("SerialNightmare.SERSEND");}
inline int32_t SERREC(){return j_unported<int32_t>("SerialNightmare.SERREC");}
inline int32_t SENDFIRST(int32_t d0){return j_unported<int32_t>("SerialNightmare.SENDFIRST");}
inline int32_t RECFIRST(int32_t d0){return j_unported<int32_t>("SerialNightmare.RECFIRST");}
inline void INITSEND(){return j_unported<void>("SerialNightmare.INITSEND");}
inline void SENDLONG(int32_t d0){return j_unported<void>("SerialNightmare.SENDLONG");}
inline void SENDLAST(int32_t d0){return j_unported<void>("SerialNightmare.SENDLAST");}
inline void INITREC(){return j_unported<void>("SerialNightmare.INITREC");}
inline void RECEIVE(){return j_unported<void>("SerialNightmare.RECEIVE");}
inline void InitParSlave(){return j_unported<void>("SerialNightmare.InitParSlave");}
inline void InitParMaster(){return j_unported<void>("SerialNightmare.InitParMaster");}
inline int32_t ParSendFirst(int32_t d0){return j_unported<int32_t>("SerialNightmare.ParSendFirst");}
inline int32_t ParRecFirst(int32_t d0){return j_unported<int32_t>("SerialNightmare.ParRecFirst");}
}
namespace SystemInc {
inline constexpr int32_t fib_SIZEOF=260;
inline constexpr int32_t IOTV_SIZE=40;
}
namespace AiBss {
inline constexpr int32_t _align0=50076;
inline constexpr int32_t ai_AlienWorkspace_vl=50076;
inline constexpr int32_t AI_AlienTeamWorkspace_vl=54876;
inline constexpr int32_t AI_OtherAlienDataPtrs_vl=55356;
inline constexpr int32_t AI_Damaged_vw=55436;
inline constexpr int32_t AI_DamagePtr_l=56036;
inline constexpr int32_t AI_BoredomPtr_l=56040;
inline constexpr int32_t AI_BoredomSpace_vl=56044;
inline constexpr int32_t AI_FlyABit_w=58444;
inline constexpr int32_t AI_DefaultMode_w=58446;
inline constexpr int32_t AI_ResponseMode_w=58448;
inline constexpr int32_t AI_FollowupMode_w=58450;
inline constexpr int32_t AI_RetreatMode_w=58452;
inline constexpr int32_t AI_CurrentMode_w=58454;
inline constexpr int32_t AI_ProwlSpeed_w=58456;
inline constexpr int32_t AI_ResponseSpeed_w=58458;
inline constexpr int32_t AI_RetreatSpeed_w=58460;
inline constexpr int32_t AI_FollowupSpeed_w=58462;
inline constexpr int32_t AI_FollowupTimer_w=58464;
inline constexpr int32_t AI_ReactionTime_w=58466;
inline constexpr int32_t AI_VecObj_w=58468;
inline constexpr int32_t ai_MiddleCPT_w=58470;
inline constexpr int32_t ai_GetOut_w=58472;
inline constexpr int32_t ai_ToSide_w=58474;
inline constexpr int32_t ai_AnimFacing_w=58476;
inline constexpr int32_t ai_DoAction_b=58478;
inline constexpr int32_t ai_FinishedAnim_b=58479;
inline constexpr int32_t AI_NoEnemies_b=58480;
}
namespace AnimBss {
inline constexpr int32_t _align0=58484;
inline constexpr int32_t Anim_BrightY_l=58484;
inline constexpr int32_t anim_MiddleRoom_l=58488;
inline constexpr int32_t Anim_DoorAndLiftLocks_l=58492;
inline constexpr int32_t anim_LiftOnlyLocks_w=58494;
inline constexpr int32_t Anim_SplatType_w=58496;
inline constexpr int32_t anim_MiddleX_w=58498;
inline constexpr int32_t anim_MiddleZ_w=58500;
inline constexpr int32_t anim_DoneFlames_w=58502;
inline constexpr int32_t Anim_FramesToDraw_w=58504;
inline constexpr int32_t Anim_TempFrames_w=58506;
inline constexpr int32_t anim_TimeToNoise_w=58508;
inline constexpr int32_t anim_OddEven_w=58510;
inline constexpr int32_t anim_FloorMoveSpeed_w=58512;
inline constexpr int32_t Anim_BrightTable_vw=58514;
inline constexpr int32_t Anim_Timer_w=58554;
inline constexpr int32_t anim_CurrentLiftable_w=58556;
inline constexpr int32_t anim_OpeningSpeed_w=58558;
inline constexpr int32_t anim_ClosingSpeed_w=58560;
inline constexpr int32_t anim_OpenDuration_w=58562;
inline constexpr int32_t anim_OpeningSoundFX_w=58564;
inline constexpr int32_t anim_ClosingSoundFX_w=58566;
inline constexpr int32_t anim_OpenedSoundFX_w=58568;
inline constexpr int32_t anim_ClosedSoundFX_w=58570;
inline constexpr int32_t anim_ActionSoundFX_w=58572;
inline constexpr int32_t anim_MaxDamage_w=58574;
}
namespace Bss {
inline bool done=true;
inline void init(){return j_unported<void>("Bss.init");}
inline void touch(int32_t addr){return j_unported<void>("Bss.touch");}
}
namespace DrawBss {
inline constexpr int32_t _align0=61104;
inline constexpr int32_t DRAW_MAX_POLY_OBJECTS=40;
inline constexpr int32_t DRAW_MAX_OBJECTS=38;
inline constexpr int32_t draw_DepthTable_vl=61104;
inline constexpr int32_t draw_DepthTableEnd=61424;
inline constexpr int32_t Draw_TopOfRoom_l=61424;
inline constexpr int32_t Draw_BottomOfRoom_l=61428;
inline constexpr int32_t Draw_AfterWaterTop_l=61432;
inline constexpr int32_t Draw_AfterWaterBottom_l=61436;
inline constexpr int32_t Draw_BeforeWaterTop_l=61440;
inline constexpr int32_t Draw_BeforeWaterBottom_l=61444;
inline constexpr int32_t draw_BackupRoomPtr_l=61448;
inline constexpr int32_t draw_ObjectOnOff_l=61452;
inline constexpr int32_t draw_PointAndPolyBrights_vl=61456;
inline constexpr int32_t draw_PointerTablePtr_l=61712;
inline constexpr int32_t draw_StartOfObjPtr_l=61716;
inline constexpr int32_t Draw_PolyObjects_vl=61720;
inline constexpr int32_t draw_2DPointsProjected_vl=61880;
inline constexpr int32_t draw_3DPointsRotated_vl=63880;
inline constexpr int32_t Draw_WallTexturePtrs_vl=66880;
inline constexpr int32_t Draw_ObjectPtrs_vl=66944;
inline constexpr int32_t Draw_TextureMapsPtr_l=67552;
inline constexpr int32_t Draw_TexturePalettePtr_l=67556;
inline constexpr int32_t Draw_BackdropImagePtr_l=67560;
inline constexpr int32_t Draw_FloorTexturesPtr_l=67564;
inline constexpr int32_t Draw_PalettePtr_l=67568;
inline constexpr int32_t Draw_ChunkPtr_l=67572;
inline constexpr int32_t Draw_GlobalFloorTexturesPtr_l=67576;
inline constexpr int32_t Draw_LevelFloorTexturesPtr_l=67580;
inline constexpr int32_t Draw_GlobalWallTexturePtrs_vl=67584;
inline constexpr int32_t Draw_LevelWallTexturePtrs_vl=67648;
inline constexpr int32_t draw_AngleBrights_vl=67712;
inline constexpr int32_t draw_Pals_vl=67776;
inline constexpr int32_t draw_WADPtr_l=68168;
inline constexpr int32_t draw_PtrPtr_l=68172;
inline constexpr int32_t draw_PolyAngPtr_l=68176;
inline constexpr int32_t draw_PointAngPtr_l=68180;
inline constexpr int32_t toppt_l=68184;
inline constexpr int32_t midobj_l=68188;
inline constexpr int32_t boxbrights_vw=68192;
inline constexpr int32_t _pad0=68692;
inline constexpr int32_t draw_PolyBotTab_vw=71252;
inline constexpr int32_t _pad1=76372;
inline constexpr int32_t draw_PolyTopTab_vw=78932;
inline constexpr int32_t _pad2=84052;
inline constexpr int32_t draw_PartBuffer_vw=86612;
inline constexpr int32_t draw_PartBufferEnd=86868;
inline constexpr int32_t Draw_CurrentZone_w=86868;
inline constexpr int32_t Draw_ZoneClipL_w=86870;
inline constexpr int32_t Draw_ZoneClipR_w=86872;
inline constexpr int32_t draw_SortIt_w=86874;
inline constexpr int32_t draw_ObjectBright_w=86876;
inline constexpr int32_t draw_ObjectAng_w=86878;
inline constexpr int32_t draw_PolygonCentreY_w=86880;
inline constexpr int32_t draw_ObjClipT_w=86882;
inline constexpr int32_t draw_ObjClipB_w=86884;
inline constexpr int32_t draw_RightClipB_w=86886;
inline constexpr int32_t draw_LeftClipB_w=86888;
inline constexpr int32_t draw_AuxX_w=86890;
inline constexpr int32_t draw_AuxY_w=86892;
inline constexpr int32_t draw_BrightToAdd_w=86894;
inline constexpr int32_t draw_Obj_XPos_w=86896;
inline constexpr int32_t draw_Obj_ZPos_w=86898;
inline constexpr int32_t draw_NumPoints_w=86900;
inline constexpr int32_t draw_OffLeftBy_w=86902;
inline constexpr int32_t draw_Left_w=86904;
inline constexpr int32_t draw_Right_w=86906;
inline constexpr int32_t draw_DownStrip_w=86908;
inline constexpr int32_t draw_DisplayEnergyCount_w=86910;
inline constexpr int32_t draw_DisplayAmmoCount_w=86912;
inline constexpr int32_t draw_LastDisplayEnergyCount_w=86914;
inline constexpr int32_t draw_LastDisplayAmmoCount_w=86916;
inline constexpr int32_t draw_WhichDoing_b=86918;
inline constexpr int32_t draw_InUpperZone_b=86919;
inline constexpr int32_t Draw_DoUpper_b=86920;
inline constexpr int32_t Draw_InRootZone_b=86921;
inline constexpr int32_t Draw_ForceSimpleWalls_b=86922;
inline constexpr int32_t Draw_ForceZoneSkip_b=86923;
}
namespace GameBss {
inline constexpr int32_t _align0=235152;
inline constexpr int32_t Game_ProgressSignal_l=235152;
inline constexpr int32_t game_PlayerProgression=235156;
inline constexpr int32_t game_PlayerProgressionEnd=235536;
inline constexpr int32_t game_AchievementsDataPtr_l=235536;
inline constexpr int32_t game_BestLevelTimeBuffer_vb=235540;
}
namespace IoBss {
inline constexpr int32_t _align0=45264;
inline constexpr int32_t IO_MemType_l=45264;
inline constexpr int32_t IO_DOSFileHandle_l=45268;
inline constexpr int32_t io_EndOfQueue_l=45272;
inline constexpr int32_t io_BlockLength_l=45276;
inline constexpr int32_t io_BlockName_l=45280;
inline constexpr int32_t io_BlockStart_l=45284;
inline constexpr int32_t io_FileExtPointer_l=45288;
inline constexpr int32_t io_ObjectName_vb=45292;
inline constexpr int32_t io_Buffer_vb=45452;
inline constexpr int32_t io_FileInfoBlock_vb=45532;
}
namespace LevelBss {
inline constexpr int32_t _align0=49980;
inline constexpr int32_t PointsToRotatePtr_l=49980;
inline constexpr int32_t Lvl_DataPtr_l=49984;
inline constexpr int32_t Lvl_ZEdgePVSHeaderPtrsPtr_l=49988;
inline constexpr int32_t Lvl_ZoneBorderPointsPtr_l=49992;
inline constexpr int32_t Lvl_ConnectTablePtr_l=49996;
inline constexpr int32_t Lvl_ListOfGraphRoomsPtr_l=50000;
inline constexpr int32_t AI_AlienShotDataPtr_l=50004;
inline constexpr int32_t Lvl_ObjectPointsPtr_l=50008;
inline constexpr int32_t Lvl_ObjectDataPtr_l=50012;
inline constexpr int32_t Lvl_ZoneEdgePtr_l=50016;
inline constexpr int32_t Lvl_PointsPtr_l=50020;
inline constexpr int32_t Lvl_ZoneGraphAddsPtr_l=50024;
inline constexpr int32_t Lvl_ZonePtrsPtr_l=50028;
inline constexpr int32_t Lvl_LiftDataPtr_l=50032;
inline constexpr int32_t Lvl_DoorDataPtr_l=50036;
inline constexpr int32_t Lvl_SwitchDataPtr_l=50040;
inline constexpr int32_t Lvl_ControlPointCoordsPtr_l=50044;
inline constexpr int32_t Lvl_GraphicsPtr_l=50048;
inline constexpr int32_t Lvl_ClipsPtr_l=50052;
inline constexpr int32_t Lvl_ModPropertiesPtr_l=50056;
inline constexpr int32_t Lvl_ErrataPtr_l=50060;
inline constexpr int32_t Lvl_EdgeCount_l=50064;
inline constexpr int32_t Lvl_NumControlPoints_w=50068;
inline constexpr int32_t Lvl_NumPoints_w=50070;
inline constexpr int32_t Lvl_NumObjectPoints_w=50072;
inline constexpr int32_t Lvl_NumZones_w=50074;
}
namespace MenunbBss {
inline constexpr int32_t mnu_screen=2320418;
inline constexpr int32_t mnu_morescreen=2361378;
}
namespace PlayerBss {
inline constexpr int32_t _align0=58576;
inline constexpr int32_t Plr1_Data=58576;
inline constexpr int32_t Plr1_ObjectPtr_l=58576;
inline constexpr int32_t Plr1_Position_vl=58580;
inline constexpr int32_t Plr1_XOff_l=58580;
inline constexpr int32_t Plr1_YOff_l=58584;
inline constexpr int32_t Plr1_ZOff_l=58588;
inline constexpr int32_t Plr1_ZonePtr_l=58592;
inline constexpr int32_t Plr1_Height_l=58596;
inline constexpr int32_t Plr1_AimSpeed_l=58600;
inline constexpr int32_t Plr1_SnapXOff_l=58604;
inline constexpr int32_t Plr1_SnapYOff_l=58608;
inline constexpr int32_t Plr1_SnapYVel_l=58612;
inline constexpr int32_t Plr1_SnapZOff_l=58616;
inline constexpr int32_t Plr1_SnapTYOff_l=58620;
inline constexpr int32_t Plr1_SnapXSpdVal_l=58624;
inline constexpr int32_t Plr1_SnapZSpdVal_l=58628;
inline constexpr int32_t Plr1_SnapHeight_l=58632;
inline constexpr int32_t Plr1_SnapTargHeight_l=58636;
inline constexpr int32_t Plr1_TmpXOff_l=58640;
inline constexpr int32_t Plr1_TmpZOff_l=58644;
inline constexpr int32_t Plr1_TmpYOff_l=58648;
inline constexpr int32_t Plr1_PotVisibleZoneListPtr_l=58652;
inline constexpr int32_t plr1_PointsToRotatePtr_l=58656;
inline constexpr int32_t plr1_BobbleY_l=58660;
inline constexpr int32_t plr1_TmpHeight_l=58664;
inline constexpr int32_t plr1_OldX_l=58668;
inline constexpr int32_t plr1_OldZ_l=58672;
inline constexpr int32_t plr1_OldRoomPtr_l=58676;
inline constexpr int32_t plr1_SnapSquishedHeight_l=58680;
inline constexpr int32_t plr1_DefaultEnemyFlags_l=58684;
inline constexpr int32_t Plr1_Energy_w=58688;
inline constexpr int32_t Plr1_Direction_vw=58690;
inline constexpr int32_t Plr1_CosVal_w=58690;
inline constexpr int32_t Plr1_SinVal_w=58692;
inline constexpr int32_t Plr1_AngPos_w=58694;
inline constexpr int32_t Plr1_Zone_w=58696;
inline constexpr int32_t Plr1_FloorSpd_w=58698;
inline constexpr int32_t Plr1_RoomBright_w=58700;
inline constexpr int32_t Plr1_Bobble_w=58702;
inline constexpr int32_t Plr1_SnapAngPos_w=58704;
inline constexpr int32_t Plr1_SnapAngSpd_w=58706;
inline constexpr int32_t Plr1_TmpAngPos_w=58708;
inline constexpr int32_t Plr1_TimeToShoot_w=58710;
inline constexpr int32_t Plr1_Invetory_vw=58712;
inline constexpr int32_t Plr1_Health_w=58712;
inline constexpr int32_t Plr1_JetpackFuel_w=58714;
inline constexpr int32_t Plr1_AmmoCounts_vw=58716;
inline constexpr int32_t Plr1_Shield_w=58756;
inline constexpr int32_t Plr1_Jetpack_w=58758;
inline constexpr int32_t Plr1_Weapons_vb=58760;
inline constexpr int32_t Plr1_GunFrame_w=58780;
inline constexpr int32_t Plr1_NoiseVol_w=58782;
inline constexpr int32_t plr1_TmpHoldDown_w=58784;
inline constexpr int32_t plr1_TmpBobble_w=58786;
inline constexpr int32_t plr1_SnapCosVal_w=58788;
inline constexpr int32_t plr1_SnapSinVal_w=58790;
inline constexpr int32_t plr1_WalkSFXTime_w=58792;
inline constexpr int32_t Plr1_Keys_b=58794;
inline constexpr int32_t Plr1_Path_b=58795;
inline constexpr int32_t Plr1_Mouse_b=58796;
inline constexpr int32_t Plr1_Joystick_b=58797;
inline constexpr int32_t Plr1_GunSelected_b=58798;
inline constexpr int32_t Plr1_StoodInTop_b=58799;
inline constexpr int32_t Plr1_Ducked_b=58800;
inline constexpr int32_t Plr1_Squished_b=58801;
inline constexpr int32_t Plr1_Echo_b=58802;
inline constexpr int32_t Plr1_Fire_b=58803;
inline constexpr int32_t Plr1_Clicked_b=58804;
inline constexpr int32_t Plr1_Used_b=58805;
inline constexpr int32_t Plr1_TmpClicked_b=58806;
inline constexpr int32_t Plr1_TmpSpcTap_b=58807;
inline constexpr int32_t Plr1_TmpGunSelected_b=58808;
inline constexpr int32_t Plr1_TmpFire_b=58809;
inline constexpr int32_t plr1_Teleported_b=58810;
inline constexpr int32_t plr1_Dead_b=58811;
inline constexpr int32_t plr1_TmpDucked_b=58812;
inline constexpr int32_t plr1_StoodOnLift_b=58813;
inline constexpr int32_t plr1_Reserved1_b=58814;
inline constexpr int32_t plr1_Reserved2_b=58815;
inline constexpr int32_t Plr1_ObjectDistances_vw=58816;
inline constexpr int32_t Plr1_ObsInLine_vb=59392;
inline constexpr int32_t _align1=59792;
inline constexpr int32_t Plr2_Data=59792;
inline constexpr int32_t Plr2_ObjectPtr_l=59792;
inline constexpr int32_t Plr2_Position_vl=59796;
inline constexpr int32_t Plr2_XOff_l=59796;
inline constexpr int32_t Plr2_YOff_l=59800;
inline constexpr int32_t Plr2_ZOff_l=59804;
inline constexpr int32_t Plr2_ZonePtr_l=59808;
inline constexpr int32_t Plr2_Height_l=59812;
inline constexpr int32_t Plr2_AimSpeed_l=59816;
inline constexpr int32_t Plr2_SnapXOff_l=59820;
inline constexpr int32_t Plr2_SnapYOff_l=59824;
inline constexpr int32_t Plr2_SnapYVel_l=59828;
inline constexpr int32_t Plr2_SnapZOff_l=59832;
inline constexpr int32_t Plr2_SnapTYOff_l=59836;
inline constexpr int32_t Plr2_SnapXSpdVal_l=59840;
inline constexpr int32_t Plr2_SnapZSpdVal_l=59844;
inline constexpr int32_t Plr2_SnapHeight_l=59848;
inline constexpr int32_t Plr2_SnapTargHeight_l=59852;
inline constexpr int32_t Plr2_TmpXOff_l=59856;
inline constexpr int32_t Plr2_TmpZOff_l=59860;
inline constexpr int32_t Plr2_TmpYOff_l=59864;
inline constexpr int32_t Plr2_PotVisibleZoneListPtr_l=59868;
inline constexpr int32_t plr2_PointsToRotatePtr_l=59872;
inline constexpr int32_t plr2_BobbleY_l=59876;
inline constexpr int32_t plr2_TmpHeight_l=59880;
inline constexpr int32_t plr2_OldX_l=59884;
inline constexpr int32_t plr2_OldZ_l=59888;
inline constexpr int32_t plr2_OldRoomPtr_l=59892;
inline constexpr int32_t plr2_SnapSquishedHeight_l=59896;
inline constexpr int32_t plr2_DefaultEnemyFlags_l=59900;
inline constexpr int32_t Plr2_Energy_w=59904;
inline constexpr int32_t Plr2_CosVal_w=59906;
inline constexpr int32_t Plr2_SinVal_w=59908;
inline constexpr int32_t Plr2_AngPos_w=59910;
inline constexpr int32_t Plr2_Zone_w=59912;
inline constexpr int32_t Plr2_FloorSpd_w=59914;
inline constexpr int32_t Plr2_RoomBright_w=59916;
inline constexpr int32_t Plr2_Bobble_w=59918;
inline constexpr int32_t Plr2_SnapAngPos_w=59920;
inline constexpr int32_t Plr2_SnapAngSpd_w=59922;
inline constexpr int32_t Plr2_TmpAngPos_w=59924;
inline constexpr int32_t Plr2_TimeToShoot_w=59926;
inline constexpr int32_t Plr2_Invetory_vw=59928;
inline constexpr int32_t Plr2_Health_w=59928;
inline constexpr int32_t Plr2_JetpackFuel_w=59930;
inline constexpr int32_t Plr2_AmmoCounts_vw=59932;
inline constexpr int32_t Plr2_Shield_w=59972;
inline constexpr int32_t Plr2_Jetpack_w=59974;
inline constexpr int32_t Plr2_Weapons_vb=59976;
inline constexpr int32_t Plr2_GunFrame_w=59996;
inline constexpr int32_t Plr2_NoiseVol_w=59998;
inline constexpr int32_t plr2_TmpHoldDown_w=60000;
inline constexpr int32_t plr2_TmpBobble_w=60002;
inline constexpr int32_t plr2_SnapCosVal_w=60004;
inline constexpr int32_t plr2_SnapSinVal_w=60006;
inline constexpr int32_t plr2_WalkSFXTime_w=60008;
inline constexpr int32_t Plr2_Keys_b=60010;
inline constexpr int32_t Plr2_Path_b=60011;
inline constexpr int32_t Plr2_Mouse_b=60012;
inline constexpr int32_t Plr2_Joystick_b=60013;
inline constexpr int32_t Plr2_GunSelected_b=60014;
inline constexpr int32_t Plr2_StoodInTop_b=60015;
inline constexpr int32_t Plr2_Ducked_b=60016;
inline constexpr int32_t Plr2_Squished_b=60017;
inline constexpr int32_t Plr2_Echo_b=60018;
inline constexpr int32_t Plr2_Fire_b=60019;
inline constexpr int32_t Plr2_Clicked_b=60020;
inline constexpr int32_t Plr2_Used_b=60021;
inline constexpr int32_t Plr2_TmpClicked_b=60022;
inline constexpr int32_t Plr2_TmpSpcTap_b=60023;
inline constexpr int32_t Plr2_TmpGunSelected_b=60024;
inline constexpr int32_t Plr2_TmpFire_b=60025;
inline constexpr int32_t plr2_Teleported_b=60026;
inline constexpr int32_t plr2_Dead_b=60027;
inline constexpr int32_t plr2_TmpDucked_b=60028;
inline constexpr int32_t plr2_StoodOnLift_b=60029;
inline constexpr int32_t plr2_Reserved1_b=60030;
inline constexpr int32_t plr2_Reserved2_b=60031;
inline constexpr int32_t Plr2_ObjectDistances_vw=60032;
inline constexpr int32_t Plr2_ObsInLine_vb=60608;
inline constexpr int32_t _align2=61008;
inline constexpr int32_t Plr_ShotDataPtr_l=61008;
inline constexpr int32_t plr_JumpSpeed_l=61012;
inline constexpr int32_t plr_OldHeight_l=61016;
inline constexpr int32_t Plr_AddToBobble_w=61020;
inline constexpr int32_t plr_FallDamage_w=61022;
inline constexpr int32_t Plr_MultiplayerType_b=61024;
inline constexpr int32_t Plr_Decelerate_b=61025;
inline constexpr int32_t plr_CanJump_b=61026;
inline constexpr int32_t plr_GunSelected_b=61027;
inline constexpr int32_t plr_PrevNextWeaponKeyState_b=61028;
inline constexpr int32_t plr_PrevUseKeyState_b=61029;
inline constexpr int32_t Plr_Health_w=61030;
inline constexpr int32_t Plr_AmmoCounts_vw=61034;
inline constexpr int32_t Plr_Shield_w=61074;
inline constexpr int32_t Plr_Weapons_vw=61078;
inline constexpr int32_t Plr_TurnSpeed_w=61098;
inline constexpr int32_t BIGsmall=61100;
inline constexpr int32_t lastscr=61101;
}
namespace SystemBss {
inline constexpr int32_t _align0=4096;
inline constexpr int32_t _GfxBase=4096;
inline constexpr int32_t _IntuitionBase=4100;
inline constexpr int32_t _MiscBase=4104;
inline constexpr int32_t _PotgoBase=4108;
inline constexpr int32_t _TimerBase=4112;
inline constexpr int32_t Sys_Workspace_vl=4116;
inline constexpr int32_t Sys_SerialBuffer_vl=36884;
inline constexpr int32_t sys_OldWindowPtr=44884;
inline constexpr int32_t sys_RecoveryStack=44888;
inline constexpr int32_t sys_ErrorBuffer_vb=44892;
inline constexpr int32_t sys_ErrorHeight_b=45148;
inline constexpr int32_t _align1=45152;
inline constexpr int32_t Sys_FrameTimeECV_q=45152;
inline constexpr int32_t Sys_PrevFrameTimeECV_q=45160;
inline constexpr int32_t Sys_FrameTimes_vl=45168;
inline constexpr int32_t Sys_FrameNumber_l=45200;
inline constexpr int32_t Sys_ECVToMsFactor_l=45204;
inline constexpr int32_t Sys_FPSIntAvg_w=45208;
inline constexpr int32_t Sys_FPSFracAvg_w=45210;
inline constexpr int32_t Sys_FPSLimit_w=45212;
inline constexpr int32_t _align2=45216;
inline constexpr int32_t sys_TimerRequest=45216;
inline constexpr int32_t Sys_Move16_b=45256;
inline constexpr int32_t Sys_FPU_b=45257;
inline constexpr int32_t Sys_CPU_68060_b=45258;
inline constexpr int32_t Sys_C2P_Akiko_b=45259;
inline constexpr int32_t Sys_CPU_68030_b=45260;
inline constexpr int32_t _align3=45264;
}
namespace TablesBss {
inline constexpr int32_t _align0=93968;
inline constexpr int32_t Lvl_CompactMap_vl=93968;
inline constexpr int32_t Lvl_BigMap_vl=94996;
inline constexpr int32_t PointBrightsPtr_l=105236;
inline constexpr int32_t CurrentPointBrights_vl=105240;
inline constexpr int32_t ClipsTable_vl=125720;
inline constexpr int32_t EndOfClipPtr_l=125840;
inline constexpr int32_t Rotated_vl=125844;
inline constexpr int32_t ObjRotated_vl=132244;
inline constexpr int32_t OnScreen_vl=136244;
inline constexpr int32_t WorkspacePtr_l=142644;
inline constexpr int32_t ObjectWorkspace_vl=142648;
inline constexpr int32_t ConstantTable_vl=145048;
inline constexpr int32_t DataBuffer1_vl=210584;
inline constexpr int32_t DataBuffer2_vl=216984;
inline constexpr int32_t Storage_vl=223384;
inline constexpr int32_t Aud_EmptyBuffer_vl=225384;
inline constexpr int32_t Aud_EmptyBufferEnd=225784;
inline constexpr int32_t Aud_SampleList_vl=225784;
inline constexpr int32_t LeftSideTable_vw=226296;
inline constexpr int32_t RightSideTable_vw=228344;
inline constexpr int32_t LeftBrightTable_vw=230392;
inline constexpr int32_t RightBrightTable_vw=232440;
inline constexpr int32_t anim_LiftHeightTable_vw=234488;
inline constexpr int32_t anim_DoorOpenTimers_vw=234568;
inline constexpr int32_t Obj_RoomPath_vw=234648;
inline constexpr int32_t game_ModProps=234848;
inline constexpr int32_t KeyMap_vb=234896;
}
namespace VidBss {
inline constexpr int32_t _align0=45792;
inline constexpr int32_t Vid_C2PSetParamsPtr_l=45792;
inline constexpr int32_t Vid_C2PConvertPtr_l=45796;
inline constexpr int32_t Vid_FastBufferPtr_l=45800;
inline constexpr int32_t Vid_FastBufferAllocPtr_l=45804;
inline constexpr int32_t Vid_Screen1Ptr_l=45808;
inline constexpr int32_t Vid_Screen2Ptr_l=45812;
inline constexpr int32_t Vid_DrawScreenPtr_l=45816;
inline constexpr int32_t Vid_DisplayScreenPtr_l=45820;
inline constexpr int32_t Vid_ScreenBuffers_vl=45824;
inline constexpr int32_t Vid_MainScreen_l=45832;
inline constexpr int32_t Vid_MyRaster0_l=45836;
inline constexpr int32_t Vid_MyRaster1_l=45840;
inline constexpr int32_t Vid_DisplayMsgPort_l=45844;
inline constexpr int32_t vid_MainWindow_l=45848;
inline constexpr int32_t Vid_LoadRGB32Struct_vl=45852;
inline constexpr int32_t vid_LoadRGB32Data_vl=45856;
inline constexpr int32_t vid_LoadRGB32End_l=48928;
inline constexpr int32_t Vid_ScreenBufferIndex_w=48932;
inline constexpr int32_t Vid_LetterBoxMarginHeight_w=48934;
inline constexpr int32_t Vid_FullScreen_b=48936;
inline constexpr int32_t Vid_FullScreenTemp_b=48937;
inline constexpr int32_t Vid_DoubleHeight_b=48938;
inline constexpr int32_t Vid_DoubleWidth_b=48939;
inline constexpr int32_t Vid_WaitForDisplayMsg_b=48940;
inline constexpr int32_t Vid_ResolutionOption_b=48941;
inline constexpr int32_t mnu_palette=48942;
inline constexpr int32_t Vid_isRTG=49966;
inline constexpr int32_t Vid_ScreenHeight=49970;
inline constexpr int32_t Vid_ScreenWidth=49972;
inline constexpr int32_t Vid_ScreenMode=49974;
}
namespace ZoneBss {
inline constexpr int32_t _align0=86924;
inline constexpr int32_t Zone_BrightTable_vl=86924;
inline constexpr int32_t Zone_EndOfListPtr_l=88124;
inline constexpr int32_t zone_ToDrawTable_vw=88128;
inline constexpr int32_t zone_OrderTable_vw=89728;
inline constexpr int32_t Zone_OrderTable_Barrier_w=91328;
inline constexpr int32_t Zone_FinalOrderTable_vw=91330;
inline constexpr int32_t zone_FinalOrderTableBarrier_w=92930;
inline constexpr int32_t Zone_VisJoins_w=92932;
inline constexpr int32_t Zone_TotJoins_w=92934;
inline constexpr int32_t Zone_VisJoinMask_w=92936;
inline constexpr int32_t Zone_EdgePointIndexes_vw=92938;
inline constexpr int32_t Zone_DoorList_vw=93002;
inline constexpr int32_t Zone_LiftList_vw=93034;
inline constexpr int32_t Zone_CurrentDoorState_w=93066;
inline constexpr int32_t Zone_RenderDoorState_w=93068;
inline constexpr int32_t Zone_DoorMap_vb=93070;
inline constexpr int32_t Zone_LiftMap_vb=93102;
inline constexpr int32_t _align1=93136;
inline constexpr int32_t Zone_PVSList_vw=93136;
inline constexpr int32_t Zone_PVSMask_vb=93648;
inline constexpr int32_t _align2=93904;
inline constexpr int32_t EDGE_POINT_ID_LIST_END=-4;
inline constexpr int32_t ZONE_BACKDROP_DISABLE_SIZE=64;
inline constexpr int32_t Zone_BackdropDisable_vb=93904;
}
namespace DrawC {
inline constexpr int32_t DRAW_MSG_CHAR_W=8;
inline constexpr int32_t DRAW_MSG_CHAR_H=8;
inline constexpr int32_t SCREEN_WIDTH=320;
inline constexpr int32_t SCREEN_HEIGHT=256;
inline constexpr int32_t SCREEN_DEPTH=8;
inline constexpr int32_t SCREEN_DEPTH_EXP=3;
inline constexpr int32_t DISPLAY_COUNT_LIMIT=999;
inline constexpr int32_t DRAW_HUD_AMMO_COUNT_X=160;
inline constexpr int32_t DRAW_HUD_AMMO_COUNT_Y=-18;
inline constexpr int32_t DRAW_HUD_ENERGY_COUNT_X=272;
inline constexpr int32_t DRAW_HUD_ENERGY_COUNT_Y=-18;
inline constexpr int32_t DRAW_HUD_ITEM_SLOTS_X=24;
inline constexpr int32_t DRAW_HUD_ITEM_SLOTS_Y=-16;
inline constexpr int32_t DRAW_HUD_CHAR_W=8;
inline constexpr int32_t DRAW_HUD_CHAR_H=7;
inline constexpr int32_t DRAW_HUD_CHAR_SMALL_W=8;
inline constexpr int32_t DRAW_HUD_CHAR_SMALL_H=5;
inline constexpr int32_t DRAW_COUNT_W=24;
inline constexpr int32_t DRAW_NUM_WEAPON_SLOTS=10;
inline constexpr int32_t LOW_AMMO_COUNT_WARN_LIMIT=9;
inline constexpr int32_t LOW_ENERGY_COUNT_WARN_LIMIT=9;
inline constexpr int32_t MULTIPLAYER_SLAVE=115;
inline constexpr int32_t PLANE_PLANE_SIZE=10240;
inline constexpr int32_t draw_BorderDigitsGood=2443298;
inline constexpr int32_t draw_BorderDigitsWarn=2443858;
inline constexpr int32_t draw_BorderDigitsItem=2444418;
inline constexpr int32_t draw_BorderDigitsItemFound=2444818;
inline constexpr int32_t draw_BorderDigitsItemSelected=2445218;
inline constexpr int32_t draw_BorderDigitsBuffer=2445618;
inline constexpr int32_t draw_Border=2446018;
inline constexpr int32_t Vid_HostBitmap=2527938;
inline int32_t draw_LastItemList=1;
inline int32_t draw_LastItemSelected=0;
inline constexpr int32_t VID_FAST_BUFFER_SIZE=86015;
inline constexpr int32_t PLANESIZE=10240;
inline int32_t ror16(int32_t v,int32_t n){return j_unported<int32_t>("DrawC.ror16");}
bool Draw_IsPrintable(int32_t charCode);
inline int32_t Draw_CalcPropWidth(int32_t textPtr,int32_t maxLen){return j_unported<int32_t>("DrawC.Draw_CalcPropWidth");}
int32_t Draw_CalcPropTextSplit(std::vector<int32_t>& nextTextPtr,int32_t txtLength,int32_t fitWidth);
inline void draw_ChunkyGlyph(int32_t drawPtr,int32_t drawSpan,int32_t charCode,int32_t pen){return j_unported<void>("DrawC.draw_ChunkyGlyph");}
inline int32_t Draw_ChunkyText(int32_t drawPtr,int32_t drawSpan,int32_t maxLen,int32_t textPtr,int32_t xPos,int32_t yPos,int32_t pen){return j_unported<int32_t>("DrawC.Draw_ChunkyText");}
inline int32_t Draw_ChunkyTextProp(int32_t drawPtr,int32_t drawSpan,int32_t maxLen,int32_t textPtr,int32_t xPos,int32_t yPos,int32_t pen){return j_unported<int32_t>("DrawC.Draw_ChunkyTextProp");}
inline void draw_PlanarGlyph(int32_t drawPtr,int32_t xPos,int32_t charCode){return j_unported<void>("DrawC.draw_PlanarGlyph");}
inline int32_t Draw_PlanarTextProp(int32_t drawPtr,int32_t maxLen,int32_t textPtr,int32_t xPos,int32_t yPos){return j_unported<int32_t>("DrawC.Draw_PlanarTextProp");}
inline void draw_ValueToDigits(int32_t value,std::vector<int32_t>& digits){return j_unported<void>("DrawC.draw_ValueToDigits");}
inline void Draw_LineOfText(int32_t ptr,int32_t screenPointer,int32_t xxxx){return j_unported<void>("DrawC.Draw_LineOfText");}
inline void Draw_ClearRect(int32_t x1,int32_t y1,int32_t x2,int32_t y2){return j_unported<void>("DrawC.Draw_ClearRect");}
inline void draw_PlanarToChunky(int32_t chunkyPtr,std::vector<int32_t>& planePtrs,int32_t numPixels){return j_unported<void>("DrawC.draw_PlanarToChunky");}
inline void draw_ConvertBorderDigitsToChunky(int32_t chunkyPtr,int32_t planarBasePtr,int32_t width,int32_t height){return j_unported<void>("DrawC.draw_ConvertBorderDigitsToChunky");}
inline int32_t Draw_Init(){return j_unported<int32_t>("DrawC.Draw_Init");}
inline void Draw_Shutdown(){return j_unported<void>("DrawC.Draw_Shutdown");}
inline void Draw_ResetGameDisplay(){return j_unported<void>("DrawC.Draw_ResetGameDisplay");}
inline void Draw_RepairTextPlaneBorders(){return j_unported<void>("DrawC.Draw_RepairTextPlaneBorders");}
inline int32_t draw_ScreenXPos(int32_t xPos){return j_unported<int32_t>("DrawC.draw_ScreenXPos");}
inline int32_t draw_ScreenYPos(int32_t yPos){return j_unported<int32_t>("DrawC.draw_ScreenYPos");}
inline int32_t draw_PackItemSlots(int32_t itemSlots){return j_unported<int32_t>("DrawC.draw_PackItemSlots");}
inline void draw_ResetHUDCounters(){return j_unported<void>("DrawC.draw_ResetHUDCounters");}
inline void draw_RenderCounterDigit_RTG(int32_t drawPtr,int32_t glyphPtr,int32_t digit,int32_t span){return j_unported<void>("DrawC.draw_RenderCounterDigit_RTG");}
inline void draw_UpdateCounter_RTG(int32_t bmBaseAddress,int32_t bmBytesPerRow,int32_t count,int32_t limit,int32_t xPos,int32_t yPos){return j_unported<void>("DrawC.draw_UpdateCounter_RTG");}
inline void draw_RenderItemDigit_RTG(int32_t drawPtr,int32_t glyphPtr,int32_t digit,int32_t span){return j_unported<void>("DrawC.draw_RenderItemDigit_RTG");}
inline void draw_UpdateItems_RTG(int32_t bmBaseAddress,int32_t bmBytesPerRow,int32_t itemSlots,int32_t itemSelected,int32_t xPos,int32_t yPos){return j_unported<void>("DrawC.draw_UpdateItems_RTG");}
inline void Draw_UpdateBorder_RTG(int32_t bmBaseAddress,int32_t bmBytesPerRow){return j_unported<void>("DrawC.Draw_UpdateBorder_RTG");}
inline void draw_RenderItemDigit_Planar(int32_t offset,int32_t glyphPtr,int32_t digit,int32_t bytesPerRow){return j_unported<void>("DrawC.draw_RenderItemDigit_Planar");}
inline void draw_UpdateItems_Planar(int32_t planes,int32_t bytesPerRow,int32_t itemSlots,int32_t itemSelected,int32_t xPos,int32_t yPos){return j_unported<void>("DrawC.draw_UpdateItems_Planar");}
inline void draw_RenderCounterDigit_Planar(int32_t offset,int32_t glyphPtr,int32_t digit,int32_t bytesPerRow){return j_unported<void>("DrawC.draw_RenderCounterDigit_Planar");}
inline void draw_UpdateCounter_Planar(int32_t planes,int32_t bytesPerRow,int32_t count,int32_t limit,int32_t xPos,int32_t yPos){return j_unported<void>("DrawC.draw_UpdateCounter_Planar");}
inline void Draw_UpdateBorder_Planar(){return j_unported<void>("DrawC.Draw_UpdateBorder_Planar");}
}
namespace GameC {
inline constexpr int32_t TRUE=1;
inline constexpr int32_t FALSE=0;
inline constexpr int32_t GAME_MODE_SINGLE_PLAYER=110;
inline constexpr int32_t GAME_DEFAULT_AMMO_LIMIT=10000;
inline constexpr int32_t GAME_DEFAULT_HEALTH_LIMIT=10000;
inline constexpr int32_t GAME_DEFAULT_FUEL_LIMIT=250;
int32_t Game_CheckInventoryLimits(int32_t inventory,int32_t consumables,int32_t items);
int32_t addSaturated(int32_t a,int32_t b,int32_t limit);
void Game_AddToInventory(int32_t inventory,int32_t consumables,int32_t items);
void Game_ApplyInventoryLimits(int32_t inventory);
void Game_Init();
void Game_Done();
void game_LoadModProperties();
void game_FreeAchievementsData();
}
namespace GamePreferences {
inline int32_t Prefs_OrderZoneSensitivity=4;
inline void game_ApplyPreferences(){return j_unported<void>("GamePreferences.game_ApplyPreferences");}
inline void game_LoadPreferences(){return j_unported<void>("GamePreferences.game_LoadPreferences");}
inline void game_SavePreferences(){return j_unported<void>("GamePreferences.game_SavePreferences");}
inline void Cfg_ParsePreferencesFile(int32_t file){return j_unported<void>("GamePreferences.Cfg_ParsePreferencesFile");}
inline void Cfg_WritePreferencesFile(int32_t file){return j_unported<void>("GamePreferences.Cfg_WritePreferencesFile");}
}
namespace GameProgress {
inline constexpr int32_t TRUE=1;
inline constexpr int32_t FALSE=0;
inline constexpr int32_t DOSFALSE=0;
inline constexpr int32_t game_LevelBegin=2609858;
inline constexpr int32_t game_LevelEnd=2609866;
inline constexpr int32_t lvlBegin_data=2609874;
inline constexpr int32_t lvlBegin_fmt=2609884;
inline std::vector<int32_t> game_AchievementRuleMask={j_shl(1,Defs::GAME_EVENTBIT_KILL),j_shl(1,Defs::GAME_EVENTBIT_KILL),j_shl(1,Defs::GAME_EVENTBIT_ZONE_CHANGE),j_shl(1,Defs::GAME_EVENTBIT_LEVEL_START),j_shl(1,Defs::GAME_EVENTBIT_LEVEL_START),j_shl(1,Defs::GAME_EVENTBIT_ADD_INVENTORY)};
void game_LoadPlayerProgression();
void game_SavePlayerProgression();
bool game_CheckAchieved(int32_t i);
void game_MarkAchieved(int32_t i);
bool game_AchievementRuleKillCount(int32_t achievement);
bool game_AchievementRuleStuffCollected(int32_t achievement);
bool game_AchievementRuleGroupKillCount(int32_t achievement);
bool game_AchievementRuleZoneFound(int32_t achievement);
bool game_AchievementRuleLevelTimeImproved(int32_t achievement);
bool game_AchievementRuleTimesDied(int32_t achievement);
bool callRule(int32_t ruleId,int32_t achievement);
void game_ApplyAchievementReward(int32_t achievement);
void Game_UpdatePlayerProgress();
void Game_LevelBegin();
void Game_LevelWon();
void Game_LevelFailed();
}
namespace MainC {
inline constexpr int32_t INVALID_ID=-1;
inline constexpr int32_t OPT_SCREENMODE=0;
inline constexpr int32_t OPT_COUNT=1;
inline int32_t CyberGfxBase=0;
inline int32_t run(std::vector<std::string>& argv){return j_unported<int32_t>("MainC.run");}
inline bool SystemC_Sys_OpenLibs(){return j_unported<bool>("MainC.SystemC_Sys_OpenLibs");}
inline void Sys_CloseLibs(){return j_unported<void>("MainC.Sys_CloseLibs");}
inline int32_t ReadArgs(std::string original_template,std::vector<int32_t>& options){return j_unported<int32_t>("MainC.ReadArgs");}
inline void FreeArgs(int32_t args){return j_unported<void>("MainC.FreeArgs");}
inline void PutStr(std::string s){return j_unported<void>("MainC.PutStr");}
inline int32_t IsCyberModeID(int32_t modeID){return j_unported<int32_t>("MainC.IsCyberModeID");}
inline void startup(){return j_unported<void>("MainC.startup");}
}
namespace MenuC {
inline constexpr int32_t SCREEN_WIDTH=320;
inline constexpr int32_t SCREEN_HEIGHT=256;
inline constexpr int32_t ROWSIZE=40;
inline constexpr int32_t PLANESIZE=10240;
inline constexpr int32_t mnu_speed=1;
inline constexpr int32_t mnu_size=256;
inline bool mnu_Active=false;
inline constexpr int32_t mnu_fadespeed=16;
inline void mnu_createpalette(){return j_unported<void>("MenuC.mnu_createpalette");}
inline void mnu_init(){return j_unported<void>("MenuC.mnu_init");}
inline void mnu_setscreen(){return j_unported<void>("MenuC.mnu_setscreen");}
inline void mnu_clearscreen(int32_t fade){return j_unported<void>("MenuC.mnu_clearscreen");}
inline bool mnu_isActive(){return j_unported<bool>("MenuC.mnu_isActive");}
inline void mnu_movescreen(){return j_unported<void>("MenuC.mnu_movescreen");}
inline void mnu_fade(int32_t fadeFactor){return j_unported<void>("MenuC.mnu_fade");}
inline void mnu_fadein(){return j_unported<void>("MenuC.mnu_fadein");}
inline void mnu_fadeout(){return j_unported<void>("MenuC.mnu_fadeout");}
inline void mnu_dofire(){return j_unported<void>("MenuC.mnu_dofire");}
inline void fireBlit(int32_t aBase,int32_t bBase,int32_t cBase,int32_t dBase,int32_t ash){return j_unported<void>("MenuC.fireBlit");}
inline void WaitTOF(){return j_unported<void>("MenuC.WaitTOF");}
}
namespace Message {
inline constexpr int32_t MSG_LINE_BUFFER_EXP=3;
inline constexpr int32_t MSG_LINE_BUFFER_SIZE=8;
inline constexpr int32_t MSG_LINE_BUFFER_MASK=7;
inline constexpr int32_t MSG_LENGTH_MASK=16383;
inline constexpr int32_t MSG_TAG_SHIFT=14;
inline constexpr int32_t MSG_SINGLE_LINE_LENGTH=80;
inline constexpr int32_t MSG_MAX_LENGTH=160;
inline constexpr int32_t MSG_MAX_CUSTOM=10;
inline constexpr int32_t MSG_SCROLL_PERIOD_MS=2000;
inline constexpr int32_t MSG_DEDUPLICATION_PERIOD_MS=2000;
inline constexpr int32_t MSG_MAX_LINES_SMALL=4;
inline constexpr int32_t SCREEN_WIDTH=320;
inline constexpr int32_t SMALL_HEIGHT=160;
inline constexpr int32_t HUD_BORDER_WIDTH=16;
inline constexpr int32_t MAX_PROP_CHAR_WIDTH=7;
inline constexpr int32_t DRAW_MSG_CHAR_W=8;
inline constexpr int32_t DRAW_MSG_CHAR_H=8;
inline constexpr int32_t DRAW_TEXT_MARGIN=4;
inline constexpr int32_t DRAW_TEXT_Y_SPACING=2;
inline constexpr int32_t MB_nextTickECV=0;
inline constexpr int32_t MB_nextDuplicateTickECV=8;
inline constexpr int32_t MB_tickPeriod=16;
inline constexpr int32_t MB_deduplicationPeriod=20;
inline constexpr int32_t MB_lineTextPtrs=24;
inline constexpr int32_t MB_lineLengths=56;
inline constexpr int32_t MB_lastMessagePtr=72;
inline constexpr int32_t MB_lineNumber=76;
inline constexpr int32_t MB_guaranteedFitFull=78;
inline constexpr int32_t MB_guaranteedFitSmall=80;
inline constexpr int32_t MB_redrawCount=82;
inline constexpr int32_t MB_linesVis=83;
inline constexpr int32_t MSG_BUFFER_SIZEOF=84;
inline constexpr int32_t msg_Buffer=2609919;
inline std::vector<int32_t> msg_TagPens={255,254,125,252};
bool Msg_Enabled();
bool Msg_SmallScreenNeedsRedraw();
int32_t msg_NextLineNumber(int32_t lineNumber);
void msg_PushLineRaw(int32_t textPtr,int32_t lengthAndTag);
void Msg_Init();
void Msg_PushLine(int32_t textPtr,int32_t lengthAndTag);
void Msg_PushLineDedupLast(int32_t textPtr,int32_t lengthAndTag);
void Msg_PullLast();
void Msg_Tick();
void Msg_RenderFullsccreenBuffer();
void Msg_RenderFullscreenRTG(int32_t bmBaseAddr,int32_t bmBytesPerRow);
void Msg_RenderSmallScreenRTG(int32_t bmBaseAddr,int32_t bmBytesPerRow);
void Msg_RenderSmallScreenPlanar(int32_t plane);
void msg_NudgeString(int32_t bufferPtr,int32_t bufferLen);
int32_t msg_CompactString(int32_t bufferPtr,int32_t bufferLen);
}
namespace ScreenC {
inline constexpr int32_t SCREEN_WIDTH=320;
inline constexpr int32_t SCREEN_HEIGHT=256;
inline constexpr int32_t HOST_SCREEN_MODE=167936;
inline int32_t hostScale=3;
inline std::vector<int32_t> hostPalette=std::vector<int32_t>(256);
inline std::vector<int32_t> presentBuffer={};
inline constexpr int32_t Vid_ShimmerBuffer=2610003;
inline int32_t dbgForceTeleFrame=-1;
inline constexpr int32_t SMALL_WIDTH=192;
inline constexpr int32_t SMALL_HEIGHT=160;
inline constexpr int32_t SMALL_XPOS=64;
inline constexpr int32_t C2P_FS_HEIGHT=232;
inline constexpr int32_t INTRO_W=640;
inline constexpr int32_t introScratch=2691923;
int32_t hostColor(int32_t idx);
inline void setHostScale(int32_t scale){return j_unported<void>("ScreenC.setHostScale");}
inline DisplayHandle* hostDisplay(){return nullptr;}
inline void saveScreenshot(std::string path){return j_unported<void>("ScreenC.saveScreenshot");}
void Vid_LoadMainPalette();
void LoadRGB32();
inline void Vid_OpenMainScreen(){return j_unported<void>("ScreenC.Vid_OpenMainScreen");}
inline void Vid_CloseMainScreen(){return j_unported<void>("ScreenC.Vid_CloseMainScreen");}
inline void vid_SetupDoubleheightCopperlist(){return j_unported<void>("ScreenC.vid_SetupDoubleheightCopperlist");}
inline int32_t GetScreenMode(){return j_unported<int32_t>("ScreenC.GetScreenMode");}
inline void Vid_Present(){return j_unported<void>("ScreenC.Vid_Present");}
inline void applyTeleportShimmer(int32_t srcChunky,int32_t dstChunky,int32_t frame){return j_unported<void>("ScreenC.applyTeleportShimmer");}
inline int32_t clampIdx(int32_t idx,int32_t base,int32_t total){return j_unported<int32_t>("ScreenC.clampIdx");}
inline void Game_ShowIntroText(){return j_unported<void>("ScreenC.Game_ShowIntroText");}
inline bool renderIntroScratch(int32_t lvl){return j_unported<bool>("ScreenC.renderIntroScratch");}
inline void buildIntroArgb(int32_t fade){return j_unported<void>("ScreenC.buildIntroArgb");}
inline void introPresentLoop(){return j_unported<void>("ScreenC.introPresentLoop");}
inline void dumpIntroText(int32_t level,std::string path){return j_unported<void>("ScreenC.dumpIntroText");}
inline void saveLastPresent(std::string path){return j_unported<void>("ScreenC.saveLastPresent");}
inline void Vid_PresentMenu(){return j_unported<void>("ScreenC.Vid_PresentMenu");}
}
namespace SystemC {
inline int32_t oldMouseY=0;
inline int32_t oldCounterX=0;
inline int32_t oldMouseX2=0;
inline int32_t Sys_EClockRate=709379;
bool Sys_CheckTimeGE(int32_t now,int32_t mark);
void Sys_AddTime(int32_t mark,int32_t ticks);
int32_t Sys_MarkTime(int32_t dest);
int64_t Sys_TimeDiff(int32_t start,int32_t end);
void Sys_FrameLap();
void Sys_EvalFPS();
void Sys_ReadMouse();
void Sys_ClearKeyboard();
int32_t Sys_Init();
void Sys_Done();
int32_t Sys_OpenLibs();
void Sys_CloseLibs();
void sys_ReleaseHardware();
void Sys_ShowFPS();
}
namespace ZoneDebug {
inline void ZDbg_Init(){return j_unported<void>("ZoneDebug.ZDbg_Init");}
inline void ZDbg_First(){return j_unported<void>("ZoneDebug.ZDbg_First");}
inline void ZDbg_SkipEdge(){return j_unported<void>("ZoneDebug.ZDbg_SkipEdge");}
inline void ZDbg_Enter(){return j_unported<void>("ZoneDebug.ZDbg_Enter");}
inline void ZDbg_Skip(){return j_unported<void>("ZoneDebug.ZDbg_Skip");}
inline void ZDbg_Done(){return j_unported<void>("ZoneDebug.ZDbg_Done");}
inline void ZDbg_LeftClip(){return j_unported<void>("ZoneDebug.ZDbg_LeftClip");}
inline void ZDbg_RightClip(){return j_unported<void>("ZoneDebug.ZDbg_RightClip");}
inline void ZDbg_DumpZone(int32_t zonePtr){return j_unported<void>("ZoneDebug.ZDbg_DumpZone");}
}
namespace ZoneEdgePvs {
inline constexpr int32_t ZONE_ID_LIST_END=-1;
inline constexpr int32_t NOT_A_DOOR=-1;
inline constexpr int32_t EDGE_POINT_ID_LIST_END=-4;
inline constexpr int32_t PVSCF_DOOR=1;
inline constexpr int32_t PVSCF_LIFT=2;
inline constexpr int32_t DISABLED_HEIGHT=5000;
inline constexpr int32_t SINTAB_SIZE=8192;
inline constexpr int32_t FOV=1800;
inline constexpr int32_t MEMF_ANY=0;
inline constexpr int32_t MULTIPLAYER_SLAVE=115;
inline constexpr int32_t ZVIS_ID_BITS=5;
inline constexpr int32_t ZVIS_NONE=0;
inline constexpr int32_t ZVIS_COND=32;
inline constexpr int32_t ZVIS_DOOR=64;
inline constexpr int32_t ZVIS_DIRECT=128;
inline constexpr int32_t NO_PATH=0;
inline constexpr int32_t LOWER_TO_LOWER=1;
inline constexpr int32_t LOWER_TO_UPPER=2;
inline constexpr int32_t UPPER_TO_LOWER=4;
inline constexpr int32_t UPPER_TO_UPPER=8;
inline constexpr int32_t BIT_FRONT=1;
inline constexpr int32_t BIT_LEFT=2;
inline constexpr int32_t BIT_RIGHT=4;
inline constexpr int32_t POS_X=0;
inline constexpr int32_t POS_Z=4;
inline constexpr int32_t ZPVSCOUNT_numZones=0;
inline constexpr int32_t ZPVSCOUNT_numJoins=2;
inline constexpr int32_t ZPVSCOUNT_features=4;
inline constexpr int32_t ZPVSCOUNT_dataSize=6;
inline constexpr int32_t ZPVSCOUNT_SIZEOF=8;
inline constexpr int32_t ZLP_Floor=0;
inline constexpr int32_t ZLP_Roof=4;
inline int32_t Zone_PVSFieldOfView=1800;
inline int32_t zre_rootZonePtr=3312122;
inline int32_t zre_FullPVSListPtr=4116;
inline int32_t zre_EdgePVSList=3449774;
inline int32_t zre_DoorMaskList=3449854;
inline int32_t zre_RecursionDepth=0;
inline int32_t zre_MaxRecursionDepth=20;
inline int32_t zre_OperationCount=4916;
inline constexpr int32_t zre_ViewPoint1=2855763;
inline constexpr int32_t zre_ViewPoint2=2855767;
inline constexpr int32_t zone_ViewPoint=2855771;
inline constexpr int32_t zone_PerpDir=2855775;
inline constexpr int32_t zone_LeftFOVDir=2855779;
inline constexpr int32_t zone_RightFOVDir=2855783;
inline constexpr int32_t scratch_endPoint=2855787;
inline constexpr int32_t scratch_end=2855791;
int32_t edgeAddr(int32_t edgeID);
int32_t zoneAddr(int32_t zoneID);
int32_t headerPtr(int32_t zoneID);
int32_t zeiAddr(int32_t edgePVSPtr,int32_t i,int32_t field);
bool Zone_IsValidZoneID(int32_t id);
bool Zone_IsValidEdgeID(int32_t id);
bool Zone_IsDoor(int32_t zoneID);
int32_t Zone_GetEdgeList(int32_t zonePtr);
int32_t Zone_SideOfEdge(int32_t edgePtr,int32_t coordPtr);
int32_t sideOfDirection(int32_t org,int32_t dir,int32_t point);
int32_t sinw(int32_t a);
int32_t cosw(int32_t a);
int32_t heightOf(int32_t level);
bool zone_HasUpper(int32_t zone);
int32_t zone_GetLowerLevel(int32_t zone);
int32_t zone_GetUpperLevel(int32_t zone);
bool zone_LevelOverlap(int32_t z1,int32_t z2);
int32_t zone_MakePVSZoneIDList(int32_t zonePtr,int32_t bufferPtr);
int32_t zone_CountJoiningEdges(int32_t zonePtr);
void zone_CountPVS(int32_t zonePtr,int32_t pvsCountPtr);
int64_t zone_CalcEdgePVSDataSize(int32_t pvsCountBufferPtr);
int32_t zone_AllocEdgePVS(int32_t pvsCountBufferPtr);
void zone_CalcZEdgePVSHeaderOffsets(int32_t currentEdgePVSPtr,int32_t features);
void zone_FillZEdgePVSHeaders(int32_t currentEdgePVSPtr,int32_t pvsCountBufferPtr);
int32_t zone_GetIndexInPVSList(int32_t zoneID);
int32_t zone_GetInitialDoorMask(int32_t zoneID);
void zone_RecurseEdgePVS(int32_t indexInPVS,int32_t doorMask);
void zone_FillZEdgePVSListData();
int32_t zone_GetPointIndex(int32_t p);
void zone_FillEdgePointIndexes();
void Zone_InitEdgePVS();
void Zone_FreeEdgePVS();
void Zone_UpdateVectors();
void zone_ClearEdgePVSBuffer(int32_t size);
void zone_MergeEdgePVS(int32_t zoneMaskPtr,int32_t doorListMaskPtr,int32_t size);
void zone_MarkVisibleViaEdges(int32_t size);
void Zone_CheckVisibleEdges();
void Zone_SetupEdgeClipping();
int32_t Zone_DetermineCrossing(int32_t from,int32_t to);
}
namespace ZoneErrata {
inline constexpr int32_t ZONE_ID_LIST_END=-1;
inline constexpr int32_t ZONE_ID_REMOVED_MANUAL=-2;
inline constexpr int32_t ZONE_ID_REMOVED_AUTO=-3;
inline constexpr int32_t PVS_TRAVERSE_LIMIT=100;
inline constexpr int32_t EDGE_TRAVERSE_LIMIT=16;
inline constexpr bool TRUE=true;
inline constexpr bool FALSE=false;
inline int32_t zone_GetCurrentPVSBuffer(){return j_unported<int32_t>("ZoneErrata.zone_GetCurrentPVSBuffer");}
inline int32_t zone_GetVisitedPVSBuffer(){return j_unported<int32_t>("ZoneErrata.zone_GetVisitedPVSBuffer");}
inline bool Zone_IsValidZoneID(int32_t id){return j_unported<bool>("ZoneErrata.Zone_IsValidZoneID");}
inline bool Zone_IsValidEdgeID(int32_t id){return j_unported<bool>("ZoneErrata.Zone_IsValidEdgeID");}
inline int32_t Zone_GetEdgeList(int32_t zonePtr){return j_unported<int32_t>("ZoneErrata.Zone_GetEdgeList");}
inline void zone_InitCurrentPVS(int32_t zonePtr,int32_t removeListPtr){return j_unported<void>("ZoneErrata.zone_InitCurrentPVS");}
inline bool zone_CheckInCurrentPVSList(int32_t zoneID){return j_unported<bool>("ZoneErrata.zone_CheckInCurrentPVSList");}
inline bool zone_CheckIsNotInVisitedPVSList(int32_t zoneID,int32_t endPtr){return j_unported<bool>("ZoneErrata.zone_CheckIsNotInVisitedPVSList");}
inline int32_t zone_GetVisitedZoneID(int32_t zoneID){return j_unported<int32_t>("ZoneErrata.zone_GetVisitedZoneID");}
inline void zone_BuildVisitedPVS(int32_t zonePtr){return j_unported<void>("ZoneErrata.zone_BuildVisitedPVS");}
inline void zone_RebuildCurrentPVS(int32_t zonePtr){return j_unported<void>("ZoneErrata.zone_RebuildCurrentPVS");}
inline void Zone_ApplyPVSErrata(int32_t zonePVSErrataPtr){return j_unported<void>("ZoneErrata.Zone_ApplyPVSErrata");}
}
namespace ZoneLiftablePvs {
inline constexpr int32_t NOT_A_DOOR=-1;
inline constexpr int32_t END_OF_DOOR_LIST=999;
inline constexpr int32_t END_OF_DOOR_WALL_LIST=-1;
inline constexpr int32_t ZONE_ID_LIST_END=-1;
inline int32_t zone_NumDoorDefs=11;
inline bool Zone_IsValidZoneID(int32_t id){return j_unported<bool>("ZoneLiftablePvs.Zone_IsValidZoneID");}
inline bool Zone_IsDoor(int32_t zoneID){return j_unported<bool>("ZoneLiftablePvs.Zone_IsDoor");}
inline void zone_DumpLiftable(int32_t liftable,int32_t index,int32_t type){return j_unported<void>("ZoneLiftablePvs.zone_DumpLiftable");}
inline void Zone_InitDoorList(){return j_unported<void>("ZoneLiftablePvs.Zone_InitDoorList");}
inline int32_t Zone_GetDoorID(int32_t zoneID){return j_unported<int32_t>("ZoneLiftablePvs.Zone_GetDoorID");}
}
namespace DataSections {
inline bool done=true;
inline void init(){return j_unported<void>("DataSections.init");}
inline void touch(int32_t addr){return j_unported<void>("DataSections.touch");}
}
namespace DrawData {
inline constexpr int32_t draw_TeleportShimmerFXData_vb=235956;
inline constexpr int32_t draw_WaterFrames_vb=244148;
inline constexpr int32_t draw_Palette_vw=309684;
inline constexpr int32_t draw_EndFont0_vb=311220;
inline constexpr int32_t draw_CharWidths0_vb=314292;
inline constexpr int32_t ENDFONT1=314388;
inline constexpr int32_t CHARWIDTHS1=314388;
inline constexpr int32_t ENDFONT2=314388;
inline constexpr int32_t CHARWIDTHS2=314388;
inline constexpr int32_t draw_FontPtrs_vl=314388;
inline constexpr int32_t draw_BorderChars_vb=314412;
inline constexpr int32_t draw_ScrollChars_vb=316732;
inline constexpr int32_t draw_GlyphSpacing_vb=318780;
inline constexpr int32_t draw_Digits_vb=319036;
inline constexpr int32_t draw_BackdropImageName_vb=319116;
inline constexpr int32_t draw_BorderPacked_vb=319144;
inline constexpr int32_t draw_Brights_vw=401080;
inline constexpr int32_t draw_Brights2_vw=401138;
inline constexpr int32_t willy=401196;
inline constexpr int32_t willybright=401294;
inline constexpr int32_t draw_XZAngs_vw=401392;
inline constexpr int32_t guff=401456;
inline constexpr int32_t ontoscr=403248;
}
namespace GameData {
inline constexpr int32_t game_PropertiesFile_vb=434652;
inline constexpr int32_t game_PreferencesFile_vb=434676;
inline constexpr int32_t game_ProgressFile_vb=434690;
inline constexpr int32_t Game_SavedGamesName_vb=434705;
inline constexpr int32_t game_Version_vb=434718;
}
namespace LevelData {
inline constexpr int32_t Lvl_BinFilename_vb=404272;
inline constexpr int32_t Lvl_BinFilenameX_vb=404289;
inline constexpr int32_t Lvl_GfxFilename_vb=404302;
inline constexpr int32_t Lvl_GfxFilenameX_vb=404319;
inline constexpr int32_t Lvl_ClipsFilename_vb=404338;
inline constexpr int32_t Lvl_ClipsFilenameX_vb=404355;
inline constexpr int32_t Lvl_MapFilename_vb=404370;
inline constexpr int32_t Lvl_MapFilenameX_vb=404387;
inline constexpr int32_t Lvl_FlyMapFilename_vb=404400;
inline constexpr int32_t Lvl_FlyMapFilenameX_vb=404417;
inline constexpr int32_t Lvl_FloorFilename_vb=404433;
inline constexpr int32_t Lvl_FloorFilenameX_vb=404450;
inline constexpr int32_t Lvl_WallFilename_vb=404462;
inline constexpr int32_t Lvl_WallFilenameX_vb=404479;
inline constexpr int32_t Lvl_WallFilenameN_vb=404486;
inline constexpr int32_t Lvl_ModPropsFilename_vb=404495;
inline constexpr int32_t Lvl_ModPropsFilenameX_vb=404512;
inline constexpr int32_t Lvl_ErrataFilename_vb=404529;
inline constexpr int32_t Lvl_ErrataFilenameX_vb=404546;
}
namespace MenunbData {
inline constexpr int32_t mnu_askfordisktext=2924542;
inline constexpr int32_t mnu_diskline=2924564;
}
namespace SystemData {
inline constexpr int32_t DosName=235700;
inline constexpr int32_t MiscResourceName=235712;
inline constexpr int32_t PotgoResourceName=235726;
inline constexpr int32_t IntuitionName=235741;
inline constexpr int32_t GraphicsName=235759;
inline constexpr int32_t TimerName=235776;
inline constexpr int32_t TempMessageBuffer_vb=235789;
inline constexpr int32_t sys_TimerFlag_l=235952;
inline constexpr int32_t INTUITION_REV=31;
}
namespace TablesData {
inline constexpr int32_t MAX_ONE_OVER_N=511;
inline constexpr int32_t SinCosTable_vw=404560;
inline constexpr int32_t SINE_SIZE=4096;
inline constexpr int32_t SINE_OFS=0;
inline constexpr int32_t COSINE_OFS=2048;
inline constexpr int32_t SINTAB_MASK_ADR=8190;
inline constexpr int32_t SINTAB_MASK_IDX=8191;
inline constexpr int32_t DivThreeTable_vb=420944;
int32_t AMOD_A(int32_t reg);
int32_t AMOD_I(int32_t reg);
}
namespace TextData {
inline constexpr int32_t Game_SoundOptionsText_vb=422264;
inline constexpr int32_t Game_LightingOptionsText_vb=422424;
inline constexpr int32_t Game_TwoPlayerVictoryMessages_vb=422504;
inline constexpr int32_t Game_DrawHighQualityText_vb=423224;
inline constexpr int32_t Game_DrawLowQualityText_vb=423247;
inline constexpr int32_t Game_CantCollectItemText_vb=423273;
inline constexpr int32_t Game_InputKeyboard_vb=423315;
inline constexpr int32_t Game_InputJoystick_vb=423336;
inline constexpr int32_t Game_InputMouse_vb=423352;
inline constexpr int32_t Game_InputMouseInv_vb=423378;
inline constexpr int32_t Game_SinglePlayerVictoryText_vb=423416;
inline constexpr int32_t ENDENDGAMETEXT=434650;
inline void line(int32_t flag,std::string text){return j_unported<void>("TextData.line");}
}
namespace TitlecopData {
inline constexpr int32_t TITLEPAL=2924542;
}
namespace Version {
}
namespace VidData {
inline constexpr int32_t VID_CONTRAST_ADJ_STEP=8;
inline constexpr int32_t VID_CONTRAST_ADJ_MIN=80;
inline constexpr int32_t VID_CONTRAST_ADJ_MAX=512;
inline constexpr int32_t VID_CONTRAST_ADJ_DEF=256;
inline constexpr int32_t Vid_GammaIncTables_vb=434780;
inline constexpr int32_t Vid_GammaIncTable1_vb=434780;
inline constexpr int32_t Vid_GammaIncTable2_vb=435036;
inline constexpr int32_t Vid_GammaIncTable3_vb=435292;
inline constexpr int32_t Vid_GammaIncTable4_vb=435548;
inline constexpr int32_t Vid_GammaIncTable5_vb=435804;
inline constexpr int32_t Vid_GammaIncTable6_vb=436060;
inline constexpr int32_t Vid_GammaIncTable7_vb=436316;
inline constexpr int32_t Vid_GammaIncTable8_vb=436572;
inline constexpr int32_t Vid_ContrastAdjust_w=436828;
inline constexpr int32_t Vid_BrightnessOffset_w=436830;
inline constexpr int32_t Vid_GammaLevel_b=436832;
inline constexpr int32_t Vid_UpdatePalette_b=436833;
inline constexpr int32_t SMALL_YPOS=436834;
}
namespace Adf {
inline constexpr bool ffs={};
inline std::string volume_fn(){return j_unported<std::string>("Adf.volume");}
inline int32_t source_fn(){return j_unported<int32_t>("Adf.source");}
inline int32_t Entry(std::string path,int32_t header,int32_t size,bool dir){return j_unported<int32_t>("Adf.Entry");}
inline int32_t be32(int32_t off){return j_unported<int32_t>("Adf.be32");}
inline int32_t word(int32_t block,int32_t off){return j_unported<int32_t>("Adf.word");}
inline std::string name(int32_t block){return j_unported<std::string>("Adf.name");}
inline int32_t children(int32_t header){return j_unported<int32_t>("Adf.children");}
inline int32_t list(){return j_unported<int32_t>("Adf.list");}
inline void walk(int32_t header,std::string path,int32_t out){return j_unported<void>("Adf.walk");}
inline std::vector<int8_t> read(int32_t f){return j_unported<std::vector<int8_t>>("Adf.read");}
}
namespace AdfAssets {
inline int32_t disks(int32_t adfDir){return j_unported<int32_t>("AdfAssets.disks");}
inline int32_t diskNumber(int32_t p){return j_unported<int32_t>("AdfAssets.diskNumber");}
inline std::string fingerprint(int32_t disks){return j_unported<std::string>("AdfAssets.fingerprint");}
inline int32_t ensureExtracted(int32_t adfDir,int32_t dest){return j_unported<int32_t>("AdfAssets.ensureExtracted");}
inline std::string canonical(std::string adfPath,int32_t dirCase){return j_unported<std::string>("AdfAssets.canonical");}
inline int32_t ensureExtractedUnchecked(int32_t adfDir,int32_t dest){return j_unported<int32_t>("AdfAssets.ensureExtractedUnchecked");}
}
namespace Audio {
inline bool disabled=false;
inline bool started={};
inline bool running={};
inline std::vector<bool> segActive=std::vector<bool>(4);
inline bool dbgCapture=false;
inline bool ensureStarted(){return false;}
inline bool needsBuffer(){return false;}
inline void consumeTriggers(){return j_unported<void>("Audio.consumeTriggers");}
inline void queueFromPaula(){return j_unported<void>("Audio.queueFromPaula");}
inline int32_t smp(int32_t ch,int32_t refPer){return j_unported<int32_t>("Audio.smp");}
inline int32_t clamp16(int32_t v){return j_unported<int32_t>("Audio.clamp16");}
inline void captureFrame(){return j_unported<void>("Audio.captureFrame");}
inline void dumpWav(std::string path){return j_unported<void>("Audio.dumpWav");}
inline void writeStr(int32_t o,std::string s){return j_unported<void>("Audio.writeStr");}
inline void writeLE16(int32_t o,int32_t v){return j_unported<void>("Audio.writeLE16");}
inline void writeLE32(int32_t o,int32_t v){return j_unported<void>("Audio.writeLE32");}
inline void stop(){return;}
}
namespace Display {
inline void open(std::string title,int32_t scale){return j_unported<void>("Display.open");}
inline void present(std::vector<int32_t>& argb){return j_unported<void>("Display.present");}
inline void pollEvents(){return j_unported<void>("Display.pollEvents");}
inline bool shouldClose(){return j_unported<bool>("Display.shouldClose");}
inline int64_t handle(){return j_unported<int64_t>("Display.handle");}
inline void close(){return j_unported<void>("Display.close");}
}
namespace DisplayTest {
inline void main(std::vector<std::string>& args){return j_unported<void>("DisplayTest.main");}
}
namespace ExecLib {
inline int32_t AllocVec(int32_t byteSize,int32_t requirements){return j_unported<int32_t>("ExecLib.AllocVec");}
inline void FreeVec(int32_t addr){return j_unported<void>("ExecLib.FreeVec");}
inline int32_t AllocMem(int32_t byteSize,int32_t requirements){return j_unported<int32_t>("ExecLib.AllocMem");}
inline void FreeMem(int32_t addr,int32_t byteSize){return j_unported<void>("ExecLib.FreeMem");}
inline void CopyMem(int32_t source,int32_t dest,int32_t size){Mem::copy(source,dest,size);}
inline void RawDoFmt(int32_t a0,int32_t a1,std::function<void(int32_t)> sink){j_rawDoFmt(a0,a1,sink);}
}
namespace FatalError {
}
namespace FrameBridge {
inline bool stopping=false;
inline void run(){return j_unported<void>("FrameBridge.run");}
inline bool awaitFrame(int64_t timeoutMs){return j_unported<bool>("FrameBridge.awaitFrame");}
inline void releaseAdvance(){return j_unported<void>("FrameBridge.releaseAdvance");}
inline void stop(){return j_unported<void>("FrameBridge.stop");}
}
namespace GraphicsLib {
inline void Move(int32_t rastPort,int32_t x,int32_t y){return j_unported<void>("GraphicsLib.Move");}
inline void Text(int32_t rastPort,int32_t addr,int32_t len){return j_unported<void>("GraphicsLib.Text");}
}
namespace Input {
inline bool haveLast={};
inline int32_t keyReadKey(){return j_unported<int32_t>("Input.keyReadKey");}
inline void clearKeyQueue(){return j_unported<void>("Input.clearKeyQueue");}
inline void install(int64_t window){return j_unported<void>("Input.install");}
inline int32_t mapKey(int32_t k){return j_unported<int32_t>("Input.mapKey");}
}
namespace IntuitionLib {
inline bool DisplayAlert(int32_t alertNumber,int32_t string,int32_t height){return j_unported<bool>("IntuitionLib.DisplayAlert");}
}
namespace LevelTest {
inline std::string cstr(int32_t addr,int32_t max){return j_unported<std::string>("LevelTest.cstr");}
inline void dumpObjects(){return j_unported<void>("LevelTest.dumpObjects");}
inline void main(std::vector<std::string>& args){return j_unported<void>("LevelTest.main");}
inline void fillConstantTable(){return j_unported<void>("LevelTest.fillConstantTable");}
}
namespace LowLevelLib {
inline int32_t ReadJoyPort(int32_t port){return j_unported<int32_t>("LowLevelLib.ReadJoyPort");}
}
namespace Main {
inline void main(std::vector<std::string>& args){return j_unported<void>("Main.main");}
inline void resolveDataDirs(int32_t base){return j_unported<void>("Main.resolveDataDirs");}
inline int32_t appImageBaseDir(){return j_unported<int32_t>("Main.appImageBaseDir");}
inline void setupLogging(int32_t base){return j_unported<void>("Main.setupLogging");}
inline void installCrashHandler(){return j_unported<void>("Main.installCrashHandler");}
inline void startFreezeWatchdog(){return j_unported<void>("Main.startFreezeWatchdog");}
inline void dumpAllThreads(int64_t stalledMs){return j_unported<void>("Main.dumpAllThreads");}
}
namespace SbDepack {
inline bool isPacked(std::vector<int8_t>& d){return j_unported<bool>("SbDepack.isPacked");}
inline int32_t unpackedLength(std::vector<int8_t>& d){return j_unported<int32_t>("SbDepack.unpackedLength");}
inline std::vector<int8_t> unpack(std::vector<int8_t>& file){return j_unported<std::vector<int8_t>>("SbDepack.unpack");}
inline int32_t be32(std::vector<int8_t>& d,int32_t o){return j_unported<int32_t>("SbDepack.be32");}
inline int32_t readPtLen(int32_t br,int32_t nn,int32_t nbit,int32_t iSpecial){return j_unported<int32_t>("SbDepack.readPtLen");}
inline int32_t readCLen(int32_t br,int32_t pt){return j_unported<int32_t>("SbDepack.readCLen");}
inline std::vector<int8_t> decode(std::vector<int8_t>& src,int32_t off,int32_t outLen,int32_t dicbit){return j_unported<std::vector<int8_t>>("SbDepack.decode");}
}
namespace SerialLink {
inline bool isConnected(){return j_unported<bool>("SerialLink.isConnected");}
inline void startMaster(int32_t port,int32_t acceptTimeoutMs){return j_unported<void>("SerialLink.startMaster");}
inline void startSlave(std::string host,int32_t port,int32_t totalTimeoutMs){return j_unported<void>("SerialLink.startSlave");}
inline void setup(){return j_unported<void>("SerialLink.setup");}
inline void sendByte(int32_t b){return j_unported<void>("SerialLink.sendByte");}
inline int32_t recvByte(){return j_unported<int32_t>("SerialLink.recvByte");}
inline void close(){return j_unported<void>("SerialLink.close");}
}
namespace SysTimer {
inline constexpr int32_t ECLOCK_RATE=709379;
inline constexpr int32_t TV_SECS=0;
inline constexpr int32_t TV_MICRO=4;
int32_t readEClock(int32_t dest);
void GetSysTime(int32_t dest);
void SubTime(int32_t dest,int32_t src);
}
namespace TwoPlayerTest {
inline void main(std::vector<std::string>& args){return j_unported<void>("TwoPlayerTest.main");}
inline void fillConstantTable(){return j_unported<void>("TwoPlayerTest.fillConstantTable");}
}
namespace Vbl {
inline void reset(){return j_unported<void>("Vbl.reset");}
inline int32_t due(){return j_unported<int32_t>("Vbl.due");}
inline void waitNext(){return j_unported<void>("Vbl.waitNext");}
}
namespace Menunb {
inline int32_t mnu_askfordisk=0;
inline void mnu_domenu(int32_t a0){return j_unported<void>("Menunb.mnu_domenu");}
inline void adjust(int32_t a0,int32_t sel,int32_t dir){return j_unported<void>("Menunb.adjust");}
}
namespace Ai {
inline constexpr int32_t AI_WorkT_LastX_w=0;
inline constexpr int32_t AI_WorkT_LastY_w=2;
inline constexpr int32_t AI_WorkT_LastZone_w=4;
inline constexpr int32_t AI_WorkT_LastControlPoint_w=6;
inline constexpr int32_t AI_WorkT_SeenBy_w=8;
inline constexpr int32_t AI_WorkT_DamageDone_w=10;
inline constexpr int32_t AI_WorkT_DamageTaken_w=12;
void AI_MainRoutine(int32_t a0);
void ai_DoTakeDamage(int32_t a0);
void ai_DoDie(int32_t a0);
void ai_TakeDamage(int32_t a0);
void ai_JustDied(int32_t a0);
void ai_DoRetreat(int32_t a0);
void ai_DoDefault(int32_t a0);
void ai_DoResponse(int32_t a0);
void ai_DoFollowup(int32_t a0);
void ai_ProwlRandomFlying(int32_t a0);
void ai_ProwlRandom(int32_t a0);
void ai_ProwlFly(int32_t a0);
int32_t M68kDivsMem(int32_t d,int32_t addr);
void ai_ChargeToSide(int32_t a0);
void ai_Charge(int32_t a0);
void ai_ChargeCommon(int32_t a0);
void ai_AttackWithGunFlying(int32_t a0);
void ai_AttackWithGun(int32_t a0);
void ai_AttackCommon(int32_t a0);
void ai_AttackWithHitScan(int32_t a0);
void ai_AttackWithProjectile(int32_t a0);
void ai_ChargeToSideFlying(int32_t a0);
void ai_ChargeFlying(int32_t a0);
void ai_ChargeFlyingCommon(int32_t a0);
void ai_PauseBriefly(int32_t a0);
void ai_Approach(int32_t a0);
void ai_ApproachFlying(int32_t a0);
void ai_ApproachToSideFlying(int32_t a0);
void ai_ApproachToSide(int32_t a0);
void ai_ApproachCommon(int32_t a0);
void ai_FlyToCPTHeight(int32_t a0);
void ai_FlyToPlayerHeight(int32_t a0);
void ai_FlyToHeightCommon(int32_t a0,int32_t d1);
void ai_CheckFloorCeiling(int32_t a0);
void ai_StorePlayerPosition(int32_t a0);
void ai_GetRoomStats(int32_t a0);
void ai_GetRoomStatsStill(int32_t a0);
int32_t ai_CheckForDark(int32_t a0);
int32_t ai_CheckInFront(int32_t a0);
void AI_LookForPlayer1(int32_t a0);
void AI_InitAlienWorkspace();
void ai_CheckDamage(int32_t a0,int32_t a1);
void ai_DoTorch(int32_t a0);
void ai_DoWalkAnim(int32_t a0);
void ai_DoAttackAnim(int32_t a0);
int32_t ai_CheckAttackOnGround(int32_t a0);
void ai_GetRoomCPT(int32_t a0);
int32_t ai_CalcSqrt(int32_t d2);
}
namespace C2pData {
inline constexpr int32_t C2P_NeedsInit_b=2924585;
inline constexpr int32_t C2P_Teleporting_b=2924586;
inline constexpr int32_t C2P_NeedsSetParam_b=2924587;
inline constexpr int32_t Game_TeleportFrame_w=2924588;
}
namespace DevInst {
inline constexpr int32_t _a0=2924592;
inline constexpr int32_t Dev_RegStatePtr_l=2924592;
inline constexpr int32_t Dev_DebugFlags_l=2924596;
inline constexpr int32_t _a1=2924600;
inline constexpr int32_t dev_GraphBuffer_vb=2924600;
inline constexpr int32_t dev_ECVDrawDone_q=2924728;
inline constexpr int32_t dev_ECVChunkyDone_q=2924736;
inline constexpr int32_t dev_ECVInterruptBegin_q=2924744;
inline constexpr int32_t dev_ECVInterruptDone_q=2924752;
inline constexpr int32_t dev_InterruptCount_l=2924760;
inline constexpr int32_t dev_InterruptClocks_l=2924764;
inline constexpr int32_t dev_Counters_vw=2924768;
inline constexpr int32_t dev_VisibleSimpleWalls_w=2924768;
inline constexpr int32_t dev_VisibleShadedWalls_w=2924770;
inline constexpr int32_t dev_VisibleModelCount_w=2924772;
inline constexpr int32_t dev_VisibleGlareCount_w=2924774;
inline constexpr int32_t dev_VisibleLightMapCount_w=2924776;
inline constexpr int32_t dev_VisibleAdditiveCount_w=2924778;
inline constexpr int32_t dev_VisibleBitmapCount_w=2924780;
inline constexpr int32_t dev_Reserved0_w=2924782;
inline constexpr int32_t dev_TotalCounters_vw=2924784;
inline constexpr int32_t dev_VisibleWalls_w=2924784;
inline constexpr int32_t dev_VisibleFlats_w=2924786;
inline constexpr int32_t dev_VisibleObjectCount_w=2924788;
inline constexpr int32_t dev_DrawObjectCallCount_w=2924790;
inline constexpr int32_t dev_DrawTimeMsAvg_w=2924792;
inline constexpr int32_t dev_FPSIntAvg_w=2924794;
inline constexpr int32_t dev_FPSFracAvg_w=2924796;
inline constexpr int32_t dev_FPSLimit_w=2924798;
inline constexpr int32_t dev_Reserved1_w=2924800;
inline constexpr int32_t dev_Reserved2_w=2924802;
inline constexpr int32_t dev_Reserved3_w=2924804;
inline constexpr int32_t dev_Reserved4_w=2924806;
inline constexpr int32_t dev_Reserved5_w=2924808;
inline constexpr int32_t dev_FrameIndex_w=2924810;
inline constexpr int32_t dev_CharBuffer_vb=2924812;
inline constexpr int32_t dev_Length=2924876;
inline constexpr int32_t dev_fs_stats_tpl_vb=2924878;
inline constexpr int32_t dev_ss_stats_wall_simple_vb=2924918;
inline constexpr int32_t dev_ss_stats_wall_shaded_vb=2924925;
inline constexpr int32_t dev_ss_stats_obj_poly_vb=2924932;
inline constexpr int32_t dev_ss_stats_obj_glare_vb=2924939;
inline constexpr int32_t dev_ss_stats_obj_lightmap_vb=2924946;
inline constexpr int32_t dev_ss_stats_obj_additive_vb=2924953;
inline constexpr int32_t dev_ss_stats_obj_bitmap_vb=2924960;
inline constexpr int32_t dev_ss_stats_order_zones_vb=2924967;
inline constexpr int32_t dev_ss_stats_zone_vb=2924974;
inline constexpr int32_t dev_ss_stats_dir_vb=2924981;
inline constexpr int32_t dev_ss_stats_pos_vb=2925001;
inline constexpr int32_t dev_ss_stats_join_vis_vb=2925013;
inline constexpr int32_t dev_ss_stats_edge_clips_vb=2925031;
inline constexpr int32_t dev_bool_off_vb=2925044;
inline constexpr int32_t dev_bool_on_vb=2925048;
inline constexpr int32_t dev_ss_door_mask_vb=2925051;
inline constexpr int32_t dev_strptr_bool_off=2925060;
inline constexpr int32_t dev_strptr_bool_on=2925064;
int32_t cstr(std::string s);
void Dev_Init();
void Dev_DataReset();
void Dev_ClearFastBuffer();
void Dev_MarkFrameBegin();
void Dev_MarkDrawDone();
void Dev_MarkChunkyDone();
void Dev_PrintF(int32_t d0,int32_t a0,int32_t a1);
void Dev_PrintStats();
int32_t dev_ECVDiffToMs(int32_t a0,int32_t a1);
void Dev_DrawGraph();
void Dev_Dump(int32_t a0,int32_t a1,int32_t d0);
}
namespace DevMacros {
inline constexpr int32_t DEV_SKIP_FLATS=0;
inline constexpr int32_t DEV_SKIP_SIMPLE_WALLS=1;
inline constexpr int32_t DEV_SKIP_SHADED_WALLS=2;
inline constexpr int32_t DEV_SKIP_BITMAPS=3;
inline constexpr int32_t DEV_SKIP_GLARE_BITMAPS=4;
inline constexpr int32_t DEV_SKIP_ADDITIVE_BITMAPS=5;
inline constexpr int32_t DEV_SKIP_LIGHTSOURCED_BITMAPS=6;
inline constexpr int32_t DEV_SKIP_POLYGON_MODELS=7;
inline constexpr int32_t DEV_SKIP_FASTBUFFER_CLEAR=8;
inline constexpr int32_t DEV_SKIP_AI_ATTACK=9;
inline constexpr int32_t DEV_SKIP_TIMEGRAPH=10;
inline constexpr int32_t DEV_SKIP_LIGHTING=11;
inline constexpr int32_t DEV_SKIP_DUMP_BG_DISABLE=12;
inline constexpr int32_t DEV_ZONE_TRACE=13;
inline constexpr int32_t DEV_SKIP_PVS_AMEND=14;
inline constexpr int32_t DEV_SKIP_EDGE_PVS=15;
inline constexpr int32_t DEV_SKIP_OVERLAY=31;
inline constexpr int32_t DEV_CLEAR_FASTBUFFER_MASK=7;
inline constexpr int32_t DEV_GRAPH_BUFFER_DIM=6;
inline constexpr int32_t DEV_GRAPH_BUFFER_SIZE=64;
inline constexpr int32_t DEV_GRAPH_BUFFER_MASK=63;
inline constexpr int32_t DEV_GRAPH_DRAW_TIME_COLOUR=255;
inline constexpr int32_t DEV_GRAPH_OBJECT_COUNT_COLOUR=31;
bool DEV_TEST(int32_t flagsAddr,int32_t bit);
void DEV_ENABLE(int32_t flagsAddr,int32_t bit);
void DEV_DISABLE(int32_t flagsAddr,int32_t bit);
void DEV_TOGGLE(int32_t flagsAddr,int32_t bit);
}
namespace DevMemtrack {
inline void Mem_TrackInit(){return j_unported<void>("DevMemtrack.Mem_TrackInit");}
inline void Mem_TrackDone(){return j_unported<void>("DevMemtrack.Mem_TrackDone");}
}
namespace Draw {
inline constexpr int32_t _a0=2925068;
inline constexpr int32_t firstdigit_b=2925068;
inline constexpr int32_t secdigit_b=2925069;
inline constexpr int32_t thirddigit_b=2925070;
inline constexpr int32_t gunny_b=2925071;
inline constexpr int32_t _a1=2925072;
inline constexpr int32_t Draw_CrosshairPens_vb=2925072;
inline void Draw_Crosshair(){return j_unported<void>("Draw.Draw_Crosshair");}
}
namespace FileIo {
inline constexpr int32_t IO_MAX_FILENAME_LEN=79;
inline constexpr int32_t MEMF_ANY=0;
inline constexpr int32_t compressed_sample_position_l=518384;
inline constexpr int32_t compressed_sample_size_l=518388;
inline constexpr int32_t sample_position_l=518392;
inline constexpr int32_t sample_size_l=518396;
inline constexpr int32_t fibonnaci_lookup_vb=518400;
inline constexpr int32_t unpacked_start_l=518416;
inline constexpr int32_t unpacked_length_l=518420;
inline constexpr int32_t unlha_temp_buffer_vl=518424;
inline int32_t errfmtAddr=0;
inline int32_t addr(int64_t r){return j_unported<int32_t>("FileIo.addr");}
inline int32_t len(int64_t r){return j_unported<int32_t>("FileIo.len");}
inline int64_t result(int32_t d0,int32_t d1){return j_unported<int64_t>("FileIo.result");}
inline void IO_InitQueue(){return j_unported<void>("FileIo.IO_InitQueue");}
inline void IO_QueueFile(int32_t a0,int32_t d0,int32_t d1){return j_unported<void>("FileIo.IO_QueueFile");}
inline void IO_FlushQueue(){return j_unported<void>("FileIo.IO_FlushQueue");}
inline int32_t io_FlushPass(){return j_unported<int32_t>("FileIo.io_FlushPass");}
inline int32_t io_TryToOpen(int32_t a0){return j_unported<int32_t>("FileIo.io_TryToOpen");}
inline int64_t io_LoadAndUnpackFile(){return j_unported<int64_t>("FileIo.io_LoadAndUnpackFile");}
inline int64_t IO_LoadFileOptional(int32_t a0){return j_unported<int64_t>("FileIo.IO_LoadFileOptional");}
inline int64_t IO_LoadFile(int32_t a0){return j_unported<int64_t>("FileIo.IO_LoadFile");}
inline int64_t io_LoadCommon(int32_t a5name){return j_unported<int64_t>("FileIo.io_LoadCommon");}
inline void io_LoadFailure(int32_t a5){return j_unported<void>("FileIo.io_LoadFailure");}
inline int32_t errfmt(){return j_unported<int32_t>("FileIo.errfmt");}
inline int64_t io_LoadSample(int32_t d0,int32_t d1){return j_unported<int64_t>("FileIo.io_LoadSample");}
inline int64_t io_HandlePacked(int32_t a0){return j_unported<int64_t>("FileIo.io_HandlePacked");}
inline void unLHA(int32_t d0,int32_t d1,int32_t a0,int32_t a1,int32_t a2){return j_unported<void>("FileIo.unLHA");}
}
namespace Level {
inline constexpr int32_t backdrop_disable_dumpfile_vb=2925080;
inline void Lvl_InitLevelMods(){return j_unported<void>("Level.Lvl_InitLevelMods");}
inline void Lvl_ClearBackdropDisable(){return j_unported<void>("Level.Lvl_ClearBackdropDisable");}
inline void Lvl_FillBackdropDisable(){return j_unported<void>("Level.Lvl_FillBackdropDisable");}
inline void Lvl_DumpBackdropDisableData(){return j_unported<void>("Level.Lvl_DumpBackdropDisableData");}
}
namespace Music {
inline constexpr int32_t mt_sin=2925105;
inline constexpr int32_t mt_periods=2925137;
inline constexpr int32_t reachedend=2925213;
inline constexpr int32_t mt_speed=2925214;
inline constexpr int32_t mt_songpos=2925215;
inline constexpr int32_t _a0=2925216;
inline constexpr int32_t mt_pattpos=2925216;
inline constexpr int32_t mt_counter=2925218;
inline constexpr int32_t mt_break=2925219;
inline constexpr int32_t mt_dmacon=2925220;
inline constexpr int32_t mt_samplestarts=2925222;
inline constexpr int32_t mt_voice1=2925346;
inline constexpr int32_t mt_voice2=2925374;
inline constexpr int32_t mt_voice3=2925402;
inline constexpr int32_t mt_voice4=2925430;
inline constexpr int32_t mt_data=2925458;
void mt_init();
void mt_end();
void mt_music();
void mt_arpeggio(int32_t a5,int32_t a6);
void mt_getnew();
int32_t mt_playvoice(int32_t a0,int32_t a3,int32_t d1,int32_t a5,int32_t a6);
void mt_setdma();
void mt_nex();
void mt_endr();
void mt_setmyport(int32_t a6);
void mt_myport(int32_t a5,int32_t a6);
void mt_vib(int32_t a5,int32_t a6);
void mt_checkcom(int32_t a5,int32_t a6);
void mt_volslide(int32_t a5,int32_t a6);
void mt_portup(int32_t a5,int32_t a6);
void mt_portdown(int32_t a5,int32_t a6);
void mt_checkcom2(int32_t a5,int32_t a6);
}
namespace Player {
inline int32_t dbgSpawnZone=-1;
inline int32_t dbgSpawnX=0;
inline int32_t dbgSpawnZ=0;
inline int32_t dbgSpawnAng=-1;
void Plr_Initialise();
void plr_MouseControl(int32_t a0);
void plr_KeyboardControl(int32_t a0);
void devCheckKey(int32_t a5,int32_t rawkey,int32_t devBit);
void plr_ShowGunName(int32_t a0);
void plr_Fall(int32_t a0);
void proceed(int32_t a0,int32_t d1,int32_t d2);
void plr_DoFootstepFX(int32_t a0);
}
namespace RawKeyMacros {
inline constexpr int32_t RAWKEY_ESC=69;
inline constexpr int32_t RAWKEY_F1=80;
inline constexpr int32_t RAWKEY_F2=81;
inline constexpr int32_t RAWKEY_F3=82;
inline constexpr int32_t RAWKEY_F4=83;
inline constexpr int32_t RAWKEY_F5=84;
inline constexpr int32_t RAWKEY_F6=85;
inline constexpr int32_t RAWKEY_F7=86;
inline constexpr int32_t RAWKEY_F8=87;
inline constexpr int32_t RAWKEY_F9=88;
inline constexpr int32_t RAWKEY_F10=89;
inline constexpr int32_t RAWKEY_BACKTICK=0;
inline constexpr int32_t RAWKEY_1=1;
inline constexpr int32_t RAWKEY_2=2;
inline constexpr int32_t RAWKEY_3=3;
inline constexpr int32_t RAWKEY_4=4;
inline constexpr int32_t RAWKEY_5=5;
inline constexpr int32_t RAWKEY_6=6;
inline constexpr int32_t RAWKEY_7=7;
inline constexpr int32_t RAWKEY_8=8;
inline constexpr int32_t RAWKEY_9=9;
inline constexpr int32_t RAWKEY_0=10;
inline constexpr int32_t RAWKEY_UNDERSCORE=11;
inline constexpr int32_t RAWKEY_EQUAL=12;
inline constexpr int32_t RAWKEY_BSLASH=13;
inline constexpr int32_t RAWKEY_BACKSPACE=65;
inline constexpr int32_t RAWKEY_TAB=66;
inline constexpr int32_t RAWKEY_Q=16;
inline constexpr int32_t RAWKEY_W=17;
inline constexpr int32_t RAWKEY_E=18;
inline constexpr int32_t RAWKEY_R=19;
inline constexpr int32_t RAWKEY_T=20;
inline constexpr int32_t RAWKEY_Y=21;
inline constexpr int32_t RAWKEY_U=22;
inline constexpr int32_t RAWKEY_I=23;
inline constexpr int32_t RAWKEY_O=24;
inline constexpr int32_t RAWKEY_P=25;
inline constexpr int32_t RAWKEY_LSQR_BRKT=26;
inline constexpr int32_t RAWKEY_RSQR_BRKT=27;
inline constexpr int32_t RAWKEY_ENTER=68;
inline constexpr int32_t RAWKEY_CTRL=99;
inline constexpr int32_t RAWKEY_CAPSLOCK=98;
inline constexpr int32_t RAWKEY_A=32;
inline constexpr int32_t RAWKEY_S=33;
inline constexpr int32_t RAWKEY_D=34;
inline constexpr int32_t RAWKEY_F=35;
inline constexpr int32_t RAWKEY_G=36;
inline constexpr int32_t RAWKEY_H=37;
inline constexpr int32_t RAWKEY_J=38;
inline constexpr int32_t RAWKEY_K=39;
inline constexpr int32_t RAWKEY_L=40;
inline constexpr int32_t RAWKEY_SEMICOLON=41;
inline constexpr int32_t RAWKEY_HASH=42;
inline constexpr int32_t RAWKEY_RMYSTERY=43;
inline constexpr int32_t RAWKEY_LSHIFT=96;
inline constexpr int32_t RAWKEY_LMYSTERY=48;
inline constexpr int32_t RAWKEY_Z=49;
inline constexpr int32_t RAWKEY_X=50;
inline constexpr int32_t RAWKEY_C=51;
inline constexpr int32_t RAWKEY_V=52;
inline constexpr int32_t RAWKEY_B=53;
inline constexpr int32_t RAWKEY_N=54;
inline constexpr int32_t RAWKEY_M=55;
inline constexpr int32_t RAWKEY_COMMA=56;
inline constexpr int32_t RAWKEY_DOT=57;
inline constexpr int32_t RAWKEY_FSLASH=58;
inline constexpr int32_t RAWKEY_RSHIFT=97;
inline constexpr int32_t RAWKEY_LALT=100;
inline constexpr int32_t RAWKEY_LAMIGA=102;
inline constexpr int32_t RAWKEY_SPACEBAR=64;
inline constexpr int32_t RAWKEY_RAMIGA=103;
inline constexpr int32_t RAWKEY_RALT=100;
inline constexpr int32_t RAWKEY_DEL=70;
inline constexpr int32_t RAWKEY_HELP=95;
inline constexpr int32_t RAWKEY_UP=76;
inline constexpr int32_t RAWKEY_LEFT=79;
inline constexpr int32_t RAWKEY_DOWN=77;
inline constexpr int32_t RAWKEY_RIGHT=78;
inline constexpr int32_t RAWKEY_NUM_LBRKT=90;
inline constexpr int32_t RAWKEY_NUM_RBRKT=91;
inline constexpr int32_t RAWKEY_NUM_FSLASH=92;
inline constexpr int32_t RAWKEY_NUM_ASTERISK=93;
inline constexpr int32_t RAWKEY_NUM_7=61;
inline constexpr int32_t RAWKEY_NUM_8=62;
inline constexpr int32_t RAWKEY_NUM_9=63;
inline constexpr int32_t RAWKEY_NUM_MINUS=74;
inline constexpr int32_t RAWKEY_NUM_4=45;
inline constexpr int32_t RAWKEY_NUM_5=46;
inline constexpr int32_t RAWKEY_NUM_6=47;
inline constexpr int32_t RAWKEY_NUM_PLUS=94;
inline constexpr int32_t RAWKEY_NUM_1=29;
inline constexpr int32_t RAWKEY_NUM_2=30;
inline constexpr int32_t RAWKEY_NUM_3=31;
inline constexpr int32_t RAWKEY_NUM_ENTER=67;
inline constexpr int32_t RAWKEY_NUM_0=15;
inline constexpr int32_t RAWKEY_NUM_DOT=60;
}
namespace Res {
inline constexpr int32_t RES_NUM_SFX=59;
inline constexpr int32_t bin2hex=621160;
inline void Res_LoadObjects(){return j_unported<void>("Res.Res_LoadObjects");}
inline void RES_FREEPTR(int32_t varAddr){return j_unported<void>("Res.RES_FREEPTR");}
inline void Res_FreeObjects(){return j_unported<void>("Res.Res_FreeObjects");}
inline void res_FreeList(int32_t d2,int32_t a2){return j_unported<void>("Res.res_FreeList");}
inline void Res_LoadSoundFx(){return j_unported<void>("Res.Res_LoadSoundFx");}
inline void Res_PatchSoundFx(){return j_unported<void>("Res.Res_PatchSoundFx");}
inline void Res_FreeSoundFx(){return j_unported<void>("Res.Res_FreeSoundFx");}
inline void Res_LoadFloorsAndTextures(){return j_unported<void>("Res.Res_LoadFloorsAndTextures");}
inline void Res_FreeFloorsAndTextures(){return j_unported<void>("Res.Res_FreeFloorsAndTextures");}
inline void Res_LoadWallTextures(){return j_unported<void>("Res.Res_LoadWallTextures");}
inline void Res_FreeWallTextures(){return j_unported<void>("Res.Res_FreeWallTextures");}
inline void Res_LoadLevelData(){return j_unported<void>("Res.Res_LoadLevelData");}
inline void Res_FreeLevelData(){return j_unported<void>("Res.Res_FreeLevelData");}
inline void Res_ReleaseScreenMemory(){return j_unported<void>("Res.Res_ReleaseScreenMemory");}
}
namespace Sys {
inline constexpr int32_t SYS_ALERT_Y_SPACE=12;
inline constexpr int32_t errorfmt=534816;
inline constexpr int32_t allocVecArgs=534808;
inline int32_t putch_a3=0;
void Sys_MemFillLong(int32_t a0,int32_t d0,int32_t d1);
void Sys_CopyMemMove16(int32_t d0,int32_t a0,int32_t a1);
void Sys_FatalError(int32_t a0,int32_t a1);
void putch(int32_t d0);
void startline();
void Sys_DisplayError();
int32_t Sys_AllocVec(int32_t d0,int32_t d1);
void gameQuitAfterFatal();
}
namespace Transform {
void RotateLevelPts();
void xform_all_fs(int32_t d4,int32_t d5,int32_t d6,int32_t d7,int32_t a1,int32_t a2,int32_t a3);
void xform_pvs_subset();
void CalcPLR1InLine();
void CalcPLR2InLine(int32_t a6);
void RotateObjectPts();
void RotateObjectPtsFullScreen(int32_t d5,int32_t d6,int32_t d7,int32_t a0,int32_t a1,int32_t a4);
}
namespace Vid {
inline constexpr int32_t VID_BRIGHT_ADJ_STEP=128;
inline constexpr int32_t VID_BRIGHT_ADJ_MIN=-4096;
inline constexpr int32_t VID_BRIGHT_ADJ_MAX=5120;
void Vid_CheckSettingsAdjust(int32_t a5);
}
namespace AdfCheck {
inline void main(std::vector<std::string>& args){return j_unported<void>("AdfCheck.main");}
inline int32_t indexByName(int32_t root){return j_unported<int32_t>("AdfCheck.indexByName");}
}
namespace CheckLayout {
inline void main(std::vector<std::string>& args){return j_unported<void>("CheckLayout.main");}
inline int32_t endOfDivThree(){return j_unported<int32_t>("CheckLayout.endOfDivThree");}
inline void check(std::string name,int32_t actual,int32_t expected){return j_unported<void>("CheckLayout.check");}
}
namespace Depack {
inline void main(std::vector<std::string>& args){return j_unported<void>("Depack.main");}
}
namespace SerialLinkTest {
inline std::vector<int32_t> buildSeq(int32_t base){return j_unported<std::vector<int32_t>>("SerialLinkTest.buildSeq");}
inline void main(std::vector<std::string>& args){return j_unported<void>("SerialLinkTest.main");}
inline int32_t runMasterAndForkSlave(){return j_unported<int32_t>("SerialLinkTest.runMasterAndForkSlave");}
inline int32_t runSlave(int32_t port){return j_unported<int32_t>("SerialLinkTest.runSlave");}
inline int32_t exchangeAndVerify(std::string role,std::vector<int32_t>& mine,std::vector<int32_t>& peer,bool master){return j_unported<int32_t>("SerialLinkTest.exchangeAndVerify");}
inline int32_t forkSlave(int32_t port){return j_unported<int32_t>("SerialLinkTest.forkSlave");}
}
namespace SkyDump {
inline void main(std::vector<std::string>& args){return j_unported<void>("SkyDump.main");}
}
namespace DrawFloor {
inline int32_t draw_GoraudFloor(int32_t d1,int32_t d2,int32_t d5,int32_t d7,int32_t a0,int32_t a1,int32_t a3){return j_unported<int32_t>("DrawFloor.draw_GoraudFloor");}
}
namespace DrawFloor060 {
inline int32_t draw_GoraudFloor(int32_t d1,int32_t d2,int32_t d5,int32_t d7,int32_t a0,int32_t a1,int32_t a3){return j_unported<int32_t>("DrawFloor060.draw_GoraudFloor");}
}
namespace DrawMap {
inline constexpr int32_t MAP_SOLID_WALL_PEN=255;
inline constexpr int32_t MAP_STEP_WALL_PEN=254;
inline constexpr int32_t _a0=2925464;
inline constexpr int32_t draw_BaseMapTransparencyPtr_l=2925464;
inline constexpr int32_t Draw_MapZoomLevel_w=2925468;
inline constexpr int32_t Draw_MapTransparent_b=2925470;
inline constexpr int32_t draw_MapXOffset_w=2925472;
inline constexpr int32_t draw_MapZOffset_w=2925474;
inline void DoTheMapWotNastyCharlesIsForcingMeToDo(){return j_unported<void>("DrawMap.DoTheMapWotNastyCharlesIsForcingMeToDo");}
inline void shown_map(int32_t a4){return j_unported<void>("DrawMap.shown_map");}
inline void draw_MapClipAndDraw(int32_t d0,int32_t d1,int32_t d2,int32_t d3,int32_t d4,int32_t a4){return j_unported<void>("DrawMap.draw_MapClipAndDraw");}
inline void draw_MapLine(int32_t d0,int32_t d1,int32_t d2,int32_t d3,int32_t d4,int32_t a4){return j_unported<void>("DrawMap.draw_MapLine");}
inline void draw_MapLineDoubleWidth(int32_t d0,int32_t d1,int32_t d2,int32_t d3,int32_t d4){return j_unported<void>("DrawMap.draw_MapLineDoubleWidth");}
}
namespace DrawSetClip {
inline constexpr int32_t SetClipStage_w=2925476;
inline constexpr int32_t SetClipTmpL=2925478;
inline constexpr int32_t SetClipTmpR=2925480;
inline void DEV_ZDBG_CLIP(int32_t n){return j_unported<void>("DrawSetClip.DEV_ZDBG_CLIP");}
inline bool zdbgEnabled(){return j_unported<bool>("DrawSetClip.zdbgEnabled");}
inline int32_t Draw_SetLeftClip(int32_t a0){return j_unported<int32_t>("DrawSetClip.Draw_SetLeftClip");}
inline int32_t Draw_SetRightClip(int32_t a0){return j_unported<int32_t>("DrawSetClip.Draw_SetRightClip");}
}
namespace DrawWall {
inline void nostrip(){return j_unported<void>("DrawWall.nostrip");}
inline void drawwallPACK0(int32_t d0,int32_t d1,int32_t d2,int32_t d3,int32_t d4,int32_t d6,int32_t d7,int32_t a2,int32_t a3,int32_t a4,int32_t a5){return j_unported<void>("DrawWall.drawwallPACK0");}
inline void drawwalldimPACK0(int32_t d0,int32_t d1,int32_t d2,int32_t d3,int32_t d4,int32_t d6,int32_t d7,int32_t a2,int32_t a3,int32_t a4,int32_t a5){return j_unported<void>("DrawWall.drawwalldimPACK0");}
inline void pack0(bool dim,int32_t d0,int32_t d1,int32_t d2,int32_t d3,int32_t d4,int32_t d6,int32_t d7,int32_t a2,int32_t a3,int32_t a4,int32_t a5){return j_unported<void>("DrawWall.pack0");}
inline void drawwallPACK1(int32_t d0,int32_t d1,int32_t d2,int32_t d3,int32_t d4,int32_t d6,int32_t d7,int32_t a2,int32_t a3,int32_t a4,int32_t a5){return j_unported<void>("DrawWall.drawwallPACK1");}
inline void drawwalldimPACK1(int32_t d0,int32_t d1,int32_t d2,int32_t d3,int32_t d4,int32_t d6,int32_t d7,int32_t a2,int32_t a3,int32_t a4,int32_t a5){return j_unported<void>("DrawWall.drawwalldimPACK1");}
inline void pack1(bool dim,int32_t d0,int32_t d1,int32_t d2,int32_t d3,int32_t d4,int32_t d6,int32_t d7,int32_t a2,int32_t a3,int32_t a4,int32_t a5){return j_unported<void>("DrawWall.pack1");}
inline void drawwallPACK2(int32_t d0,int32_t d1,int32_t d2,int32_t d3,int32_t d4,int32_t d6,int32_t d7,int32_t a2,int32_t a3,int32_t a4,int32_t a5){return j_unported<void>("DrawWall.drawwallPACK2");}
inline void drawwalldimPACK2(int32_t d0,int32_t d1,int32_t d2,int32_t d3,int32_t d4,int32_t d6,int32_t d7,int32_t a2,int32_t a3,int32_t a4,int32_t a5){return j_unported<void>("DrawWall.drawwalldimPACK2");}
inline void pack2(bool dim,int32_t d0,int32_t d1,int32_t d2,int32_t d3,int32_t d4,int32_t d6,int32_t d7,int32_t a2,int32_t a3,int32_t a4,int32_t a5){return j_unported<void>("DrawWall.pack2");}
}
namespace DrawWall060 {
inline void drawwallPACK0(int32_t d0,int32_t d1,int32_t d2,int32_t d3,int32_t d4,int32_t d6,int32_t d7,int32_t a2,int32_t a3,int32_t a4,int32_t a5){return j_unported<void>("DrawWall060.drawwallPACK0");}
inline void drawwallPACK1(int32_t d0,int32_t d1,int32_t d2,int32_t d3,int32_t d4,int32_t d6,int32_t d7,int32_t a2,int32_t a3,int32_t a4,int32_t a5){return j_unported<void>("DrawWall060.drawwallPACK1");}
inline void drawwallPACK2(int32_t d0,int32_t d1,int32_t d2,int32_t d3,int32_t d4,int32_t d6,int32_t d7,int32_t a2,int32_t a3,int32_t a4,int32_t a5){return j_unported<void>("DrawWall060.drawwallPACK2");}
}
namespace DrawZoneGraph {
inline constexpr int32_t draw_Root_Zone_w=2925482;
inline bool zdbgEnabled(){return j_unported<bool>("DrawZoneGraph.zdbgEnabled");}
inline bool devSkipEdgePvs(){return j_unported<bool>("DrawZoneGraph.devSkipEdgePvs");}
inline void Draw_Zone_Graph(){return j_unported<void>("DrawZoneGraph.Draw_Zone_Graph");}
inline void ready_upper(){return j_unported<void>("DrawZoneGraph.ready_upper");}
inline void lower_zone_first(){return j_unported<void>("DrawZoneGraph.lower_zone_first");}
inline void draw_RenderCurrentZone(int32_t a0){return j_unported<void>("DrawZoneGraph.draw_RenderCurrentZone");}
}
