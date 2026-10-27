#include "original.hpp"
namespace GameC {
int32_t Game_CheckInventoryLimits(int32_t inventory,int32_t consumables,int32_t items){
int32_t plrInvPtr=j_add(j_add(inventory,Defs::InvT_Items),Defs::InvIT_JetPack_w);
int32_t objInvPtr=j_add(items,Defs::InvIT_JetPack_w);
int32_t givesAnything=0;
if((Mem::b(PlayerBss::Plr_MultiplayerType_b) == GameC::GAME_MODE_SINGLE_PLAYER)) {
for(int32_t n=0;(n < Defs::NUM_INVENTORY_ITEMS);++(n)){
if((Mem::uw(j_add(objInvPtr,(2 * n))) != 0)) {
return GameC::TRUE;
}
}
}
else {
for(int32_t n=0;(n < Defs::NUM_INVENTORY_ITEMS);++(n)){
(givesAnything|=Mem::uw(j_add(objInvPtr,(2 * n))));
if(((Mem::uw(j_add(objInvPtr,(2 * n))) != 0) && (Mem::uw(j_add(plrInvPtr,(2 * n))) == 0))) {
return GameC::TRUE;
}
}
}
(plrInvPtr=j_add(inventory,Defs::InvCT_Health_w));
(objInvPtr=j_add(consumables,Defs::InvCT_Health_w));
int32_t limPtr=j_add(j_add(TablesBss::game_ModProps,Defs::GModT_MaxInv),Defs::InvCT_Health_w);
for(int32_t n=0;(n < Defs::NUM_INVENTORY_CONSUMABLES);++(n)){
(givesAnything=(j_add(givesAnything,Mem::uw(j_add(objInvPtr,(2 * n)))) & 0xFFFF));
if(((Mem::uw(j_add(objInvPtr,(2 * n))) > 0) && (Mem::uw(j_add(plrInvPtr,(2 * n))) < Mem::uw(j_add(limPtr,(2 * n)))))) {
return GameC::TRUE;
}
}
return ((givesAnything != 0)?GameC::FALSE:GameC::TRUE);
}

int32_t addSaturated(int32_t a,int32_t b,int32_t limit){
int32_t sum=(j_add(a,b) & 0xFFFF);
return ((((sum < a) || (sum < b)) || (sum > limit))?limit:sum);
}

void Game_AddToInventory(int32_t inventory,int32_t consumables,int32_t items){
int32_t plrInvPtr=j_add(j_add(inventory,Defs::InvT_Items),Defs::InvIT_JetPack_w);
int32_t objInvPtr=j_add(items,Defs::InvIT_JetPack_w);
for(int32_t n=0;(n < Defs::NUM_INVENTORY_ITEMS);++(n)){
Mem::ww(j_add(plrInvPtr,(2 * n)),(Mem::uw(j_add(plrInvPtr,(2 * n))) | Mem::uw(j_add(objInvPtr,(2 * n)))));
}
(plrInvPtr=j_add(inventory,Defs::InvCT_Health_w));
(objInvPtr=j_add(consumables,Defs::InvCT_Health_w));
int32_t game_TotalCollectedPtr=j_add(GameBss::game_PlayerProgression,Defs::GStatT_TotalHealthCollected_w);
int32_t limInvPtr=j_add(j_add(TablesBss::game_ModProps,Defs::GModT_MaxInv),Defs::InvCT_Health_w);
for(int32_t n=0;(n < Defs::NUM_INVENTORY_CONSUMABLES);++(n)){
int32_t preInv=Mem::uw(j_add(plrInvPtr,(2 * n)));
int32_t newInv=GameC::addSaturated(Mem::uw(j_add(plrInvPtr,(2 * n))),Mem::uw(j_add(objInvPtr,(2 * n))),Mem::uw(j_add(limInvPtr,(2 * n))));
Mem::ww(j_add(plrInvPtr,(2 * n)),newInv);
Mem::wl(j_add(game_TotalCollectedPtr,(4 * n)),j_add(Mem::l(j_add(game_TotalCollectedPtr,(4 * n))),(newInv - preInv)));
}
Mem::wl(GameBss::Game_ProgressSignal_l,(Mem::l(GameBss::Game_ProgressSignal_l) | j_shl(1,Defs::GAME_EVENTBIT_ADD_INVENTORY)));
}

void Game_ApplyInventoryLimits(int32_t inventory){
int32_t limPtr=j_add(j_add(TablesBss::game_ModProps,Defs::GModT_MaxInv),Defs::InvCT_Health_w);
int32_t invPtr=j_add(inventory,Defs::InvCT_Health_w);
for(int32_t n=0;(n < Defs::NUM_INVENTORY_CONSUMABLES);++(n)){
if((Mem::uw(j_add(invPtr,(2 * n))) > Mem::uw(j_add(limPtr,(2 * n))))) {
Mem::ww(j_add(invPtr,(2 * n)),Mem::uw(j_add(limPtr,(2 * n))));
}
}
}

void Game_Init(){
GameC::game_LoadModProperties();
GamePreferences::game_LoadPreferences();
GameProgress::game_LoadPlayerProgression();
}

void Game_Done(){
GameProgress::game_SavePlayerProgression();
GamePreferences::game_SavePreferences();
GameC::game_FreeAchievementsData();
}

void game_LoadModProperties(){
int32_t maxInv=j_add(TablesBss::game_ModProps,Defs::GModT_MaxInv);
Mem::ww(j_add(maxInv,Defs::InvCT_Health_w),GameC::GAME_DEFAULT_HEALTH_LIMIT);
Mem::ww(j_add(maxInv,Defs::InvCT_JetpackFuel_w),GameC::GAME_DEFAULT_FUEL_LIMIT);
for(int32_t i=0;(i < Defs::NUM_BULLET_DEFS);++(i)){
Mem::ww(j_add(j_add(maxInv,Defs::InvCT_AmmoCounts_vw),(i * 2)),GameC::GAME_DEFAULT_AMMO_LIMIT);
}
}

void game_FreeAchievementsData(){
int32_t ptr=Mem::l(GameBss::game_AchievementsDataPtr_l);
if((ptr != 0)) {
ExecLib::FreeVec(ptr);
}
Mem::wl(GameBss::game_AchievementsDataPtr_l,0);
Mem::ww(j_add(TablesBss::game_ModProps,Defs::GModT_NumAchievements),0);
Mem::ww(j_add(TablesBss::game_ModProps,Defs::GModT_AchievementSize),0);
}

}