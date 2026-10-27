#include "original.hpp"
namespace GameProgress {
void game_LoadPlayerProgression(){
int32_t gameProgressFH=DosLib::Open(GameData::game_ProgressFile_vb,DosLib::MODE_OLDFILE);
if((GameProgress::DOSFALSE == gameProgressFH)) {
ExecLib::CopyMem(j_add(TablesBss::game_ModProps,Defs::GModT_MaxInv),j_add(GameBss::game_PlayerProgression,Defs::GStatT_MaxInv),Defs::InvCT_SizeOf_l);
return ;
}
int32_t read=DosLib::Read(gameProgressFH,GameBss::game_PlayerProgression,Defs::GStatT_SizeOf_l);
if((read == Defs::GStatT_SizeOf_l)) {
ExecLib::CopyMem(j_add(GameBss::game_PlayerProgression,Defs::GStatT_MaxInv),j_add(TablesBss::game_ModProps,Defs::GModT_MaxInv),Defs::InvCT_SizeOf_l);
}
DosLib::Close(gameProgressFH);
}

void game_SavePlayerProgression(){
int32_t gameProgressFH=DosLib::Open(GameData::game_ProgressFile_vb,DosLib::MODE_READWRITE);
if((GameProgress::DOSFALSE == gameProgressFH)) {
return ;
}
ExecLib::CopyMem(j_add(TablesBss::game_ModProps,Defs::GModT_MaxInv),j_add(GameBss::game_PlayerProgression,Defs::GStatT_MaxInv),Defs::InvCT_SizeOf_l);
DosLib::Write(gameProgressFH,GameBss::game_PlayerProgression,Defs::GStatT_SizeOf_l);
DosLib::Close(gameProgressFH);
}

bool game_CheckAchieved(int32_t i){
return ((Mem::ub(j_add(j_add(GameBss::game_PlayerProgression,Defs::GStatT_Achieved_vb),j_shr(i,3))) & j_shl(1,(i & 7))) != 0);
}

void game_MarkAchieved(int32_t i){
int32_t a=j_add(j_add(GameBss::game_PlayerProgression,Defs::GStatT_Achieved_vb),j_shr(i,3));
Mem::wb(a,(Mem::ub(a) | j_shl(1,(i & 7))));
}

bool game_AchievementRuleKillCount(int32_t achievement){
int32_t p=j_add(achievement,Defs::AchievementT_RuleParams_vb);
return (Mem::uw(j_add(j_add(GameBss::game_PlayerProgression,Defs::GStatT_AlienKills_vw),(Mem::uw(p) * 2))) >= Mem::uw(j_add(p,2)));
}

bool game_AchievementRuleStuffCollected(int32_t achievement){
int32_t p=j_add(achievement,Defs::AchievementT_RuleParams_vb);
int64_t totalCount=(Mem::l(p) & 0xFFFFFFFFL);
int32_t consumable=Mem::uw(j_add(p,4));
int32_t consumables=j_add(GameBss::game_PlayerProgression,Defs::GStatT_TotalHealthCollected_w);
return ((Mem::l(j_add(consumables,(consumable * 4))) & 0xFFFFFFFFL) >= totalCount);
}

bool game_AchievementRuleGroupKillCount(int32_t achievement){
int32_t p=j_add(achievement,Defs::AchievementT_RuleParams_vb);
int32_t enemyMask=(Mem::l(p) & (j_shl(1,Defs::NUM_ALIEN_DEFS) - 1));
int32_t countLimit=Mem::uw(j_add(p,4));
int32_t count=0;
for(int32_t id=0;(id < Defs::NUM_ALIEN_DEFS);++(id)){
if(((enemyMask & j_shl(1,id)) != 0)) {
(count=(j_add(count,Mem::uw(j_add(j_add(GameBss::game_PlayerProgression,Defs::GStatT_AlienKills_vw),(id * 2)))) & 0xFFFF));
}
if((count >= countLimit)) {
return (GameProgress::TRUE != 0);
}
}
return false;
}

bool game_AchievementRuleZoneFound(int32_t achievement){
int32_t p=j_add(achievement,Defs::AchievementT_RuleParams_vb);
int32_t levelAndZone=(j_shl(Mem::uw(ControlloopData::Game_LevelNumber_w),16) | Mem::uw(PlayerBss::Plr1_Zone_w));
return (levelAndZone == Mem::l(p));
}

bool game_AchievementRuleLevelTimeImproved(int32_t achievement){
int32_t p=j_add(achievement,Defs::AchievementT_RuleParams_vb);
int32_t levelMask=Mem::l(p);
int32_t countLimit=Mem::uw(j_add(p,4));
int32_t count=0;
bool overall=(Mem::uw(j_add(p,6)) != 0);
for(int32_t levelNum=0;(levelNum < Defs::NUM_LEVELS);++(levelNum)){
if(((levelMask & j_shl(1,levelNum)) != 0)) {
if(overall) {
(count=(j_add(count,Mem::uw(j_add(j_add(GameBss::game_PlayerProgression,Defs::GStatT_LevelImprovedTimeCounts_vw),(levelNum * 2)))) & 0xFFFF));
}
else {
(count=Mem::uw(j_add(j_add(GameBss::game_PlayerProgression,Defs::GStatT_LevelImprovedTimeCounts_vw),(levelNum * 2))));
}
if((count >= countLimit)) {
return (GameProgress::TRUE != 0);
}
}
}
return false;
}

bool game_AchievementRuleTimesDied(int32_t achievement){
int32_t p=j_add(achievement,Defs::AchievementT_RuleParams_vb);
int32_t levelMask=Mem::l(p);
int32_t countLimit=Mem::uw(j_add(p,4));
int32_t count=0;
bool overall=(Mem::uw(j_add(p,6)) != 0);
for(int32_t levelNum=0;(levelNum < Defs::NUM_LEVELS);++(levelNum)){
if(((levelMask & j_shl(1,levelNum)) != 0)) {
if(overall) {
(count=(j_add(count,Mem::uw(j_add(j_add(GameBss::game_PlayerProgression,Defs::GStatT_LevelFailCounts_vw),(levelNum * 2)))) & 0xFFFF));
}
else {
(count=Mem::uw(j_add(j_add(GameBss::game_PlayerProgression,Defs::GStatT_LevelFailCounts_vw),(levelNum * 2))));
}
if((count >= countLimit)) {
return (GameProgress::TRUE != 0);
}
}
}
return false;
}

bool callRule(int32_t ruleId,int32_t achievement){
switch(ruleId){
case 0:
{return GameProgress::game_AchievementRuleKillCount(achievement);
}
case 1:
{return GameProgress::game_AchievementRuleGroupKillCount(achievement);
}
case 2:
{return GameProgress::game_AchievementRuleZoneFound(achievement);
}
case 3:
{return GameProgress::game_AchievementRuleLevelTimeImproved(achievement);
}
case 4:
{return GameProgress::game_AchievementRuleTimesDied(achievement);
}
case 5:
{return GameProgress::game_AchievementRuleStuffCollected(achievement);
}
default:
{return false;
}
}
}

void game_ApplyAchievementReward(int32_t achievement){
Message::Msg_PushLine(Mem::l(j_add(achievement,Defs::AchievementT_RewardDesc_l)),(Defs::MSG_TAG_OPTIONS | 80));
int32_t player_ic=j_add(PlayerBss::Plr1_Invetory_vw,Defs::InvT_Consumables);
int32_t capH=j_add(j_add(TablesBss::game_ModProps,Defs::GModT_MaxInv),Defs::InvCT_Health_w);
Mem::ww(capH,j_add(Mem::uw(capH),Mem::uw(j_add(achievement,Defs::AchievementT_HealthCapBonus_w))));
int32_t capF=j_add(j_add(TablesBss::game_ModProps,Defs::GModT_MaxInv),Defs::InvCT_JetpackFuel_w);
Mem::ww(capF,j_add(Mem::uw(capF),Mem::uw(j_add(achievement,Defs::AchievementT_FuelCapBonus_w))));
int32_t plrH=j_add(player_ic,Defs::InvCT_Health_w);
Mem::ww(plrH,j_add(Mem::uw(plrH),Mem::uw(j_add(achievement,Defs::AchievementT_HealthBonus_w))));
int32_t ammoType=Mem::w(j_add(achievement,Defs::AchievementT_AmmoType_w));
if(((ammoType > -(1)) && (ammoType < Defs::NUM_BULLET_DEFS))) {
int32_t capA=j_add(j_add(j_add(TablesBss::game_ModProps,Defs::GModT_MaxInv),Defs::InvCT_AmmoCounts_vw),(ammoType * 2));
Mem::ww(capA,j_add(Mem::uw(capA),Mem::uw(j_add(achievement,Defs::AchievementT_AmmoTypeCapBonus_w))));
int32_t plrA=j_add(j_add(player_ic,Defs::InvCT_AmmoCounts_vw),(ammoType * 2));
Mem::ww(plrA,j_add(Mem::uw(plrA),Mem::uw(j_add(achievement,Defs::AchievementT_AmmoTypeBonus_w))));
}
GameC::Game_ApplyInventoryLimits(PlayerBss::Plr1_Invetory_vw);
}

void Game_UpdatePlayerProgress(){
int32_t achievements=Mem::l(GameBss::game_AchievementsDataPtr_l);
for(int32_t id=0;(id < Mem::uw(j_add(TablesBss::game_ModProps,Defs::GModT_NumAchievements)));++(id)){
int32_t ach=j_add(achievements,(id * Defs::AchievementT_SizeOf_l));
if((((Mem::l(GameBss::Game_ProgressSignal_l) & Mem::uw(j_add(ach,Defs::AchievementT_RuleMask_w))) == 0) || GameProgress::game_CheckAchieved(id))) {
continue;
}
if(GameProgress::callRule(Mem::uw(j_add(ach,Defs::AchievementT_RuleId_w)),ach)) {
Message::Msg_PushLine(Mem::l(j_add(ach,Defs::AchievementT_Name_l)),(Defs::MSG_TAG_OPTIONS | 80));
if((Mem::l(j_add(ach,Defs::AchievementT_RewardDesc_l)) != 0)) {
GameProgress::game_ApplyAchievementReward(ach);
}
GameProgress::game_MarkAchieved(id);
}
}
Mem::wl(GameBss::Game_ProgressSignal_l,0);
}

void Game_LevelBegin(){
SysTimer::GetSysTime(GameProgress::game_LevelBegin);
int32_t lvl=Mem::uw(ControlloopData::Game_LevelNumber_w);
int32_t play=j_add(j_add(GameBss::game_PlayerProgression,Defs::GStatT_LevelPlayCounts_vw),(lvl * 2));
Mem::ww(play,j_add(Mem::uw(play),1));
if((Mem::l(j_add(j_add(GameBss::game_PlayerProgression,Defs::GStatT_LevelBestTimes_vl),(lvl * 4))) != 0)) {
int64_t time=(Mem::l(j_add(j_add(GameBss::game_PlayerProgression,Defs::GStatT_LevelBestTimes_vl),(lvl * 4))) & 0xFFFFFFFFL);
Mem::ww(j_add(GameProgress::lvlBegin_data,8),int32_t(j_mod(time,100)));
(time/=100);
Mem::ww(j_add(GameProgress::lvlBegin_data,6),int32_t(j_mod(time,60)));
(time/=60);
Mem::ww(j_add(GameProgress::lvlBegin_data,4),int32_t(j_mod(time,60)));
(time/=60);
Mem::ww(j_add(GameProgress::lvlBegin_data,2),int32_t(time));
Mem::ww(j_add(GameProgress::lvlBegin_data,0),j_add('A',lvl));
std::vector<int32_t> outPtr={GameBss::game_BestLevelTimeBuffer_vb};
ExecLib::RawDoFmt(GameProgress::lvlBegin_fmt,GameProgress::lvlBegin_data,[&](int32_t ch){Mem::wb(outPtr[0],ch);
(outPtr[0])++;
});
Message::Msg_PushLine(GameBss::game_BestLevelTimeBuffer_vb,(Defs::MSG_TAG_OPTIONS | (outPtr[0] - GameBss::game_BestLevelTimeBuffer_vb)));
}
Mem::wl(GameBss::Game_ProgressSignal_l,(Mem::l(GameBss::Game_ProgressSignal_l) | j_shl(1,Defs::GAME_EVENTBIT_LEVEL_START)));
GameProgress::Game_UpdatePlayerProgress();
}

void Game_LevelWon(){
SysTimer::GetSysTime(GameProgress::game_LevelEnd);
SysTimer::SubTime(GameProgress::game_LevelEnd,GameProgress::game_LevelBegin);
int32_t lvl=Mem::uw(ControlloopData::Game_LevelNumber_w);
int32_t won=j_add(j_add(GameBss::game_PlayerProgression,Defs::GStatT_LevelWonCounts_vw),(lvl * 2));
Mem::ww(won,j_add(Mem::uw(won),1));
int64_t secs=(Mem::l(j_add(GameProgress::game_LevelEnd,0)) & 0xFFFFFFFFL);
int64_t micro=(Mem::l(j_add(GameProgress::game_LevelEnd,4)) & 0xFFFFFFFFL);
int64_t elapsedCentis=j_add((secs * 100),j_div(micro,10000));
int32_t bestPtr=j_add(j_add(GameBss::game_PlayerProgression,Defs::GStatT_LevelBestTimes_vl),(lvl * 4));
int64_t best=(Mem::l(bestPtr) & 0xFFFFFFFFL);
if((0 == best)) {
Mem::wl(bestPtr,int32_t(elapsedCentis));
}
else if((elapsedCentis < best)) {
Mem::wl(bestPtr,int32_t(elapsedCentis));
int32_t imp=j_add(j_add(GameBss::game_PlayerProgression,Defs::GStatT_LevelImprovedTimeCounts_vw),(lvl * 2));
Mem::ww(imp,j_add(Mem::uw(imp),1));
}
}

void Game_LevelFailed(){
int32_t lvl=Mem::uw(ControlloopData::Game_LevelNumber_w);
int32_t fail=j_add(j_add(GameBss::game_PlayerProgression,Defs::GStatT_LevelFailCounts_vw),(lvl * 2));
Mem::ww(fail,j_add(Mem::uw(fail),1));
}

}