#include "original.hpp"
namespace ZoneEdgePvs {
int32_t edgeAddr(int32_t edgeID){
return j_add(Mem::l(LevelBss::Lvl_ZoneEdgePtr_l),(edgeID * Defs::EdgeT_SizeOf_l));
}

int32_t zoneAddr(int32_t zoneID){
return Mem::l(j_add(Mem::l(LevelBss::Lvl_ZonePtrsPtr_l),(4 * zoneID)));
}

int32_t headerPtr(int32_t zoneID){
return Mem::l(j_add(Mem::l(LevelBss::Lvl_ZEdgePVSHeaderPtrsPtr_l),(4 * zoneID)));
}

int32_t zeiAddr(int32_t edgePVSPtr,int32_t i,int32_t field){
return j_add(j_add(j_add(edgePVSPtr,Defs::ZEdgePVSHeaderT_EdgeInfoList_v),(i * Defs::ZEdgeInfoT_SizeOf_l)),field);
}

bool Zone_IsValidZoneID(int32_t id){
return ((id >= 0) && (id < Mem::w(LevelBss::Lvl_NumZones_w)));
}

bool Zone_IsValidEdgeID(int32_t id){
return (id >= 0);
}

bool Zone_IsDoor(int32_t zoneID){
return (ZoneEdgePvs::Zone_IsValidZoneID(zoneID) && ((Mem::ub(j_add(ZoneBss::Zone_DoorMap_vb,j_shr(zoneID,3))) & j_shl(1,(zoneID & 7))) != 0));
}

int32_t Zone_GetEdgeList(int32_t zonePtr){
return j_add(zonePtr,int16_t(Mem::w(j_add(zonePtr,Defs::ZoneT_EdgeListOffset_w))));
}

int32_t Zone_SideOfEdge(int32_t edgePtr,int32_t coordPtr){
return ((Mem::w(j_add(edgePtr,Defs::EdgeT_XLen_w)) * (Mem::w(j_add(coordPtr,Defs::Vec2W_Z)) - Mem::w(j_add(edgePtr,Defs::EdgeT_ZPos_w)))) - (Mem::w(j_add(edgePtr,Defs::EdgeT_ZLen_w)) * (Mem::w(j_add(coordPtr,Defs::Vec2W_X)) - Mem::w(j_add(edgePtr,Defs::EdgeT_XPos_w)))));
}

int32_t sideOfDirection(int32_t org,int32_t dir,int32_t point){
return ((Mem::w(j_add(dir,Defs::Vec2W_X)) * (Mem::w(j_add(point,Defs::Vec2W_Z)) - Mem::w(j_add(org,Defs::Vec2W_Z)))) - (Mem::w(j_add(dir,Defs::Vec2W_Z)) * (Mem::w(j_add(point,Defs::Vec2W_X)) - Mem::w(j_add(org,Defs::Vec2W_X)))));
}

int32_t sinw(int32_t a){
return Mem::w(j_add(TablesData::SinCosTable_vw,(j_shr((a & (ZoneEdgePvs::SINTAB_SIZE - 2)),1) * 2)));
}

int32_t cosw(int32_t a){
return Mem::w(j_add(TablesData::SinCosTable_vw,(j_shr((j_add(a,j_div(ZoneEdgePvs::SINTAB_SIZE,4)) & (ZoneEdgePvs::SINTAB_SIZE - 2)),1) * 2)));
}

int32_t heightOf(int32_t level){
return int16_t(j_shr(level,8));
}

bool zone_HasUpper(int32_t zone){
int32_t floor=ZoneEdgePvs::heightOf(Mem::l(j_add(zone,Defs::ZoneT_UpperFloor_l)));
return ((floor < ZoneEdgePvs::DISABLED_HEIGHT) && (floor > ZoneEdgePvs::heightOf(Mem::l(j_add(zone,Defs::ZoneT_UpperRoof_l)))));
}

int32_t zone_GetLowerLevel(int32_t zone){
return j_add(zone,Defs::ZoneT_Floor_l);
}

int32_t zone_GetUpperLevel(int32_t zone){
return j_add(zone,Defs::ZoneT_UpperFloor_l);
}

bool zone_LevelOverlap(int32_t z1,int32_t z2){
int32_t floor=ZoneEdgePvs::heightOf(Mem::l(j_add(z2,ZoneEdgePvs::ZLP_Floor)));
int32_t roof=ZoneEdgePvs::heightOf(Mem::l(j_add(z1,ZoneEdgePvs::ZLP_Roof)));
if((roof >= floor)) {
return false;
}
(floor=ZoneEdgePvs::heightOf(Mem::l(j_add(z1,ZoneEdgePvs::ZLP_Floor))));
(roof=ZoneEdgePvs::heightOf(Mem::l(j_add(z2,ZoneEdgePvs::ZLP_Roof))));
if((roof >= floor)) {
return false;
}
return true;
}

int32_t zone_MakePVSZoneIDList(int32_t zonePtr,int32_t bufferPtr){
int32_t pvsPtr=j_add(zonePtr,Defs::ZoneT_PotVisibleZoneList_vw);
while(ZoneEdgePvs::Zone_IsValidZoneID(Mem::w(j_add(pvsPtr,Defs::ZPVSRecordT_ZoneID_w)))){
Mem::ww(bufferPtr,Mem::w(j_add(pvsPtr,Defs::ZPVSRecordT_ZoneID_w)));
(bufferPtr+=2);
(pvsPtr+=Defs::ZPVSRecordT_SizeOf_l);
}
Mem::ww(bufferPtr,ZoneEdgePvs::ZONE_ID_LIST_END);
(bufferPtr+=2);
return bufferPtr;
}

int32_t zone_CountJoiningEdges(int32_t zonePtr){
int32_t numEdges=0;
int32_t zEdgeList=ZoneEdgePvs::Zone_GetEdgeList(zonePtr);
int32_t edgeID{};
while(true){
(edgeID=Mem::w(zEdgeList));
(zEdgeList+=2);
if(!(ZoneEdgePvs::Zone_IsValidEdgeID(edgeID))) {
break;
}
int32_t nextZoneID=Mem::w(j_add(ZoneEdgePvs::edgeAddr(edgeID),Defs::EdgeT_JoinZone_w));
if(ZoneEdgePvs::Zone_IsValidZoneID(nextZoneID)) {
int32_t crossing=ZoneEdgePvs::Zone_DetermineCrossing(zonePtr,ZoneEdgePvs::zoneAddr(nextZoneID));
if((crossing != ZoneEdgePvs::NO_PATH)) {
++(numEdges);
}
}
}
return numEdges;
}

void zone_CountPVS(int32_t zonePtr,int32_t pvsCountPtr){
int32_t start=j_add(zonePtr,Defs::ZoneT_PotVisibleZoneList_vw);
int32_t pvsPtr=start;
Mem::ww(j_add(pvsCountPtr,ZoneEdgePvs::ZPVSCOUNT_features),0);
while(ZoneEdgePvs::Zone_IsValidZoneID(Mem::w(j_add(pvsPtr,Defs::ZPVSRecordT_ZoneID_w)))){
if((((Mem::uw(j_add(pvsCountPtr,ZoneEdgePvs::ZPVSCOUNT_features)) & ZoneEdgePvs::PVSCF_DOOR) == 0) && ZoneEdgePvs::Zone_IsDoor(Mem::w(j_add(pvsPtr,Defs::ZPVSRecordT_ZoneID_w))))) {
Mem::ww(j_add(pvsCountPtr,ZoneEdgePvs::ZPVSCOUNT_features),(Mem::uw(j_add(pvsCountPtr,ZoneEdgePvs::ZPVSCOUNT_features)) | ZoneEdgePvs::PVSCF_DOOR));
}
(pvsPtr+=Defs::ZPVSRecordT_SizeOf_l);
}
int32_t numZones=j_div((pvsPtr - start),Defs::ZPVSRecordT_SizeOf_l);
Mem::ww(j_add(pvsCountPtr,ZoneEdgePvs::ZPVSCOUNT_numZones),numZones);
int32_t numJoins=ZoneEdgePvs::zone_CountJoiningEdges(zonePtr);
Mem::ww(j_add(pvsCountPtr,ZoneEdgePvs::ZPVSCOUNT_numJoins),numJoins);
int32_t features=Mem::uw(j_add(pvsCountPtr,ZoneEdgePvs::ZPVSCOUNT_features));
int64_t dataSize=j_add(int64_t((Defs::ZEdgePVSHeaderT_SizeOf_l - Defs::ZEdgeInfoT_SizeOf_l)),(int64_t(numJoins) * j_add(Defs::ZEdgeInfoT_SizeOf_l,int64_t(numZones))));
if(((features & ZoneEdgePvs::PVSCF_DOOR) != 0)) {
(dataSize+=((int64_t(numZones) * numJoins) * Defs::ZDoorListMask_SizeOf));
}
Mem::ww(j_add(pvsCountPtr,ZoneEdgePvs::ZPVSCOUNT_dataSize),int32_t((j_add(dataSize,1) & ~(1LL))));
}

int64_t zone_CalcEdgePVSDataSize(int32_t pvsCountBufferPtr){
int64_t totalSize=(int64_t(Mem::w(LevelBss::Lvl_NumZones_w)) * 4);
for(int32_t zoneID=0;(zoneID < Mem::w(LevelBss::Lvl_NumZones_w));++(zoneID)){
int32_t zonePtr=ZoneEdgePvs::zoneAddr(zoneID);
ZoneEdgePvs::zone_CountPVS(zonePtr,pvsCountBufferPtr);
(totalSize+=Mem::uw(j_add(pvsCountBufferPtr,ZoneEdgePvs::ZPVSCOUNT_dataSize)));
(pvsCountBufferPtr+=ZoneEdgePvs::ZPVSCOUNT_SIZEOF);
}
return totalSize;
}

int32_t zone_AllocEdgePVS(int32_t pvsCountBufferPtr){
int64_t totalSize=ZoneEdgePvs::zone_CalcEdgePVSDataSize(pvsCountBufferPtr);
(totalSize=(j_add(totalSize,3) & ~(3LL)));
return ExecLib::AllocVec(int32_t(totalSize),ZoneEdgePvs::MEMF_ANY);
}

void zone_CalcZEdgePVSHeaderOffsets(int32_t currentEdgePVSPtr,int32_t features){
int64_t offset=j_add((Defs::ZEdgePVSHeaderT_SizeOf_l - Defs::ZEdgeInfoT_SizeOf_l),(int64_t(Mem::w(j_add(currentEdgePVSPtr,Defs::ZEdgePVSHeaderT_EdgeCount_w))) * Defs::ZEdgeInfoT_SizeOf_l));
Mem::ww(j_add(currentEdgePVSPtr,Defs::ZEdgePVSHeaderT_ZoneMaskOffset_w),int32_t(offset));
if(((features & ZoneEdgePvs::PVSCF_DOOR) != 0)) {
int64_t t=(int64_t(Mem::w(j_add(currentEdgePVSPtr,Defs::ZEdgePVSHeaderT_ListSize_w))) * Mem::w(j_add(currentEdgePVSPtr,Defs::ZEdgePVSHeaderT_EdgeCount_w)));
(offset+=(j_add(t,1) & ~(1LL)));
Mem::ww(j_add(currentEdgePVSPtr,Defs::ZEdgePVSHeaderT_DoorMaskOffset_w),int32_t(offset));
}
else {
Mem::ww(j_add(currentEdgePVSPtr,Defs::ZEdgePVSHeaderT_DoorMaskOffset_w),0);
}
Mem::ww(j_add(currentEdgePVSPtr,Defs::ZEdgePVSHeaderT_LiftMaskOffset_w),0);
}

void zone_FillZEdgePVSHeaders(int32_t currentEdgePVSPtr,int32_t pvsCountBufferPtr){
for(int32_t zoneID=0;(zoneID < Mem::w(LevelBss::Lvl_NumZones_w));++(zoneID)){
Mem::ww(j_add(currentEdgePVSPtr,Defs::ZEdgePVSHeaderT_ZoneID_w),zoneID);
Mem::ww(j_add(currentEdgePVSPtr,Defs::ZEdgePVSHeaderT_ListSize_w),Mem::w(j_add(pvsCountBufferPtr,ZoneEdgePvs::ZPVSCOUNT_numZones)));
Mem::ww(j_add(currentEdgePVSPtr,Defs::ZEdgePVSHeaderT_EdgeCount_w),Mem::w(j_add(pvsCountBufferPtr,ZoneEdgePvs::ZPVSCOUNT_numJoins)));
ZoneEdgePvs::zone_CalcZEdgePVSHeaderOffsets(currentEdgePVSPtr,Mem::uw(j_add(pvsCountBufferPtr,ZoneEdgePvs::ZPVSCOUNT_features)));
Mem::wl(j_add(Mem::l(LevelBss::Lvl_ZEdgePVSHeaderPtrsPtr_l),(4 * zoneID)),currentEdgePVSPtr);
int32_t zonePtr=ZoneEdgePvs::zoneAddr(zoneID);
int32_t zEdgeList=ZoneEdgePvs::Zone_GetEdgeList(zonePtr);
int32_t edgeIndex=0;
int32_t edgeID{};
while(true){
(edgeID=Mem::w(zEdgeList));
(zEdgeList+=2);
if(!(ZoneEdgePvs::Zone_IsValidEdgeID(edgeID))) {
break;
}
int32_t nextZoneID=Mem::w(j_add(ZoneEdgePvs::edgeAddr(edgeID),Defs::EdgeT_JoinZone_w));
if(ZoneEdgePvs::Zone_IsValidZoneID(nextZoneID)) {
int32_t crossing=ZoneEdgePvs::Zone_DetermineCrossing(zonePtr,ZoneEdgePvs::zoneAddr(nextZoneID));
if((crossing != ZoneEdgePvs::NO_PATH)) {
Mem::ww(ZoneEdgePvs::zeiAddr(currentEdgePVSPtr,edgeIndex,Defs::ZEdgeInfoT_EdgeID_w),edgeID);
(edgeIndex)++;
}
}
}
(currentEdgePVSPtr+=Mem::uw(j_add(pvsCountBufferPtr,ZoneEdgePvs::ZPVSCOUNT_dataSize)));
(pvsCountBufferPtr+=ZoneEdgePvs::ZPVSCOUNT_SIZEOF);
}
}

int32_t zone_GetIndexInPVSList(int32_t zoneID){
int32_t nextIDPtr=ZoneEdgePvs::zre_FullPVSListPtr;
while(ZoneEdgePvs::Zone_IsValidZoneID(Mem::w(nextIDPtr))){
if((zoneID == Mem::w(nextIDPtr))) {
return j_div((nextIDPtr - ZoneEdgePvs::zre_FullPVSListPtr),2);
}
(nextIDPtr+=2);
}
return ZoneEdgePvs::ZONE_ID_LIST_END;
}

int32_t zone_GetInitialDoorMask(int32_t zoneID){
int32_t doorIndex=ZoneLiftablePvs::Zone_GetDoorID(zoneID);
if((doorIndex != ZoneEdgePvs::NOT_A_DOOR)) {
return (j_shl(1,doorIndex) & 0xFFFF);
}
return 0;
}

void zone_RecurseEdgePVS(int32_t indexInPVS,int32_t doorMask){
if((++(ZoneEdgePvs::zre_RecursionDepth) > ZoneEdgePvs::zre_MaxRecursionDepth)) {
(ZoneEdgePvs::zre_MaxRecursionDepth=ZoneEdgePvs::zre_RecursionDepth);
}
++(ZoneEdgePvs::zre_OperationCount);
int32_t zoneID=Mem::w(j_add(ZoneEdgePvs::zre_FullPVSListPtr,(indexInPVS * 2)));
int32_t visType=ZoneEdgePvs::ZVIS_DIRECT;
Mem::wb(j_add(ZoneEdgePvs::zre_EdgePVSList,indexInPVS),ZoneEdgePvs::ZVIS_DIRECT);
if((ZoneEdgePvs::zre_DoorMaskList != 0)) {
int32_t myDoorMask=ZoneEdgePvs::zone_GetInitialDoorMask(zoneID);
if((myDoorMask != 0)) {
(doorMask|=myDoorMask);
(visType=ZoneEdgePvs::ZVIS_DOOR);
}
else if((doorMask != 0)) {
(visType=ZoneEdgePvs::ZVIS_COND);
}
Mem::ww(j_add(ZoneEdgePvs::zre_DoorMaskList,(indexInPVS * 2)),doorMask);
}
Mem::wb(j_add(ZoneEdgePvs::zre_EdgePVSList,indexInPVS),visType);
int32_t currentEdgePVSPtr=ZoneEdgePvs::headerPtr(zoneID);
for(int32_t edgeNum=0;(edgeNum < Mem::w(j_add(currentEdgePVSPtr,Defs::ZEdgePVSHeaderT_EdgeCount_w)));++(edgeNum)){
int32_t edgePtr=ZoneEdgePvs::edgeAddr(Mem::w(ZoneEdgePvs::zeiAddr(currentEdgePVSPtr,edgeNum,Defs::ZEdgeInfoT_EdgeID_w)));
int32_t nextZoneID=Mem::w(j_add(edgePtr,Defs::EdgeT_JoinZone_w));
(indexInPVS=ZoneEdgePvs::zone_GetIndexInPVSList(nextZoneID));
if((indexInPVS == ZoneEdgePvs::ZONE_ID_LIST_END)) {
continue;
}
int32_t nextVis=Mem::ub(j_add(ZoneEdgePvs::zre_EdgePVSList,indexInPVS));
if((nextVis >= ZoneEdgePvs::ZVIS_DOOR)) {
continue;
}
else if(((nextVis > ZoneEdgePvs::ZVIS_NONE) && (visType < ZoneEdgePvs::ZVIS_DIRECT))) {
continue;
}
if(((ZoneEdgePvs::Zone_SideOfEdge(edgePtr,ZoneEdgePvs::zre_ViewPoint1) < 0) || (ZoneEdgePvs::Zone_SideOfEdge(edgePtr,ZoneEdgePvs::zre_ViewPoint2) < 0))) {
ZoneEdgePvs::zone_RecurseEdgePVS(indexInPVS,doorMask);
}
}
--(ZoneEdgePvs::zre_RecursionDepth);
}

void zone_FillZEdgePVSListData(){
(ZoneEdgePvs::zre_FullPVSListPtr=SystemBss::Sys_Workspace_vl);
(ZoneEdgePvs::zre_RecursionDepth=0);
(ZoneEdgePvs::zre_MaxRecursionDepth=0);
(ZoneEdgePvs::zre_OperationCount=0);
for(int32_t zoneID=0;(zoneID < Mem::w(LevelBss::Lvl_NumZones_w));++(zoneID)){
(ZoneEdgePvs::zre_rootZonePtr=ZoneEdgePvs::zoneAddr(zoneID));
ZoneEdgePvs::zone_MakePVSZoneIDList(ZoneEdgePvs::zre_rootZonePtr,ZoneEdgePvs::zre_FullPVSListPtr);
int32_t currentEdgePVSPtr=ZoneEdgePvs::headerPtr(zoneID);
(ZoneEdgePvs::zre_EdgePVSList=j_add(currentEdgePVSPtr,Mem::w(j_add(currentEdgePVSPtr,Defs::ZEdgePVSHeaderT_ZoneMaskOffset_w))));
int32_t doorOff=Mem::w(j_add(currentEdgePVSPtr,Defs::ZEdgePVSHeaderT_DoorMaskOffset_w));
(ZoneEdgePvs::zre_DoorMaskList=((doorOff != 0)?j_add(currentEdgePVSPtr,doorOff):0));
if((Mem::w(j_add(currentEdgePVSPtr,Defs::ZEdgePVSHeaderT_EdgeCount_w)) > 10)) {
continue;
}
int32_t doorMask=ZoneEdgePvs::zone_GetInitialDoorMask(zoneID);
for(int32_t edgeNum=0;(edgeNum < Mem::w(j_add(currentEdgePVSPtr,Defs::ZEdgePVSHeaderT_EdgeCount_w)));++(edgeNum)){
int32_t edgePtr=ZoneEdgePvs::edgeAddr(Mem::w(ZoneEdgePvs::zeiAddr(currentEdgePVSPtr,edgeNum,Defs::ZEdgeInfoT_EdgeID_w)));
Mem::ww(j_add(ZoneEdgePvs::zre_ViewPoint1,Defs::Vec2W_X),Mem::w(j_add(edgePtr,Defs::EdgeT_XPos_w)));
Mem::ww(j_add(ZoneEdgePvs::zre_ViewPoint1,Defs::Vec2W_Z),Mem::w(j_add(edgePtr,Defs::EdgeT_ZPos_w)));
Mem::ww(j_add(ZoneEdgePvs::zre_ViewPoint2,Defs::Vec2W_X),j_add(Mem::w(j_add(edgePtr,Defs::EdgeT_XPos_w)),Mem::w(j_add(edgePtr,Defs::EdgeT_XLen_w))));
Mem::ww(j_add(ZoneEdgePvs::zre_ViewPoint2,Defs::Vec2W_Z),j_add(Mem::w(j_add(edgePtr,Defs::EdgeT_ZPos_w)),Mem::w(j_add(edgePtr,Defs::EdgeT_ZLen_w))));
Mem::wb(ZoneEdgePvs::zre_EdgePVSList,ZoneEdgePvs::ZVIS_DIRECT);
if((ZoneEdgePvs::zre_DoorMaskList != 0)) {
Mem::ww(ZoneEdgePvs::zre_DoorMaskList,doorMask);
}
for(int32_t i=1;(i < Mem::w(j_add(currentEdgePVSPtr,Defs::ZEdgePVSHeaderT_ListSize_w)));++(i)){
Mem::wb(j_add(ZoneEdgePvs::zre_EdgePVSList,i),0);
}
int32_t indexInPVS=ZoneEdgePvs::zone_GetIndexInPVSList(Mem::w(j_add(edgePtr,Defs::EdgeT_JoinZone_w)));
if((indexInPVS > ZoneEdgePvs::ZONE_ID_LIST_END)) {
ZoneEdgePvs::zone_RecurseEdgePVS(indexInPVS,doorMask);
}
if((ZoneEdgePvs::zre_DoorMaskList != 0)) {
(ZoneEdgePvs::zre_DoorMaskList+=(Mem::w(j_add(currentEdgePVSPtr,Defs::ZEdgePVSHeaderT_ListSize_w)) * Defs::ZDoorListMask_SizeOf));
}
(ZoneEdgePvs::zre_EdgePVSList+=Mem::w(j_add(currentEdgePVSPtr,Defs::ZEdgePVSHeaderT_ListSize_w)));
}
}
}

int32_t zone_GetPointIndex(int32_t p){
int32_t pointPtr=Mem::l(LevelBss::Lvl_PointsPtr_l);
int32_t match=Mem::l(p);
for(int32_t i=0;(i < Mem::w(LevelBss::Lvl_NumPoints_w));++(i)){
if((match == Mem::l(j_add(pointPtr,(i * 4))))) {
return i;
}
}
return -(1);
}

void zone_FillEdgePointIndexes(){
for(int32_t zoneID=0;(zoneID < Mem::w(LevelBss::Lvl_NumZones_w));++(zoneID)){
int32_t edgePVSPtr=ZoneEdgePvs::headerPtr(zoneID);
for(int32_t i=0;(i < Mem::w(j_add(edgePVSPtr,Defs::ZEdgePVSHeaderT_EdgeCount_w)));++(i)){
int32_t edgePtr=ZoneEdgePvs::edgeAddr(Mem::w(ZoneEdgePvs::zeiAddr(edgePVSPtr,i,Defs::ZEdgeInfoT_EdgeID_w)));
Mem::ww(j_add(ZoneEdgePvs::scratch_end,Defs::Vec2W_X),j_add(Mem::w(j_add(edgePtr,Defs::EdgeT_XPos_w)),Mem::w(j_add(edgePtr,Defs::EdgeT_XLen_w))));
Mem::ww(j_add(ZoneEdgePvs::scratch_end,Defs::Vec2W_Z),j_add(Mem::w(j_add(edgePtr,Defs::EdgeT_ZPos_w)),Mem::w(j_add(edgePtr,Defs::EdgeT_ZLen_w))));
Mem::ww(ZoneEdgePvs::zeiAddr(edgePVSPtr,i,Defs::ZEdgeInfoT_StartPointID_w),ZoneEdgePvs::zone_GetPointIndex(j_add(edgePtr,Defs::EdgeT_XPos_w)));
Mem::ww(ZoneEdgePvs::zeiAddr(edgePVSPtr,i,Defs::ZEdgeInfoT_EndPointID_w),ZoneEdgePvs::zone_GetPointIndex(ZoneEdgePvs::scratch_end));
}
}
}

void Zone_InitEdgePVS(){
ZoneLiftablePvs::Zone_InitDoorList();
int32_t pvsCountBufferPtr=SystemBss::Sys_Workspace_vl;
int32_t alloc=ZoneEdgePvs::zone_AllocEdgePVS(pvsCountBufferPtr);
Mem::wl(LevelBss::Lvl_ZEdgePVSHeaderPtrsPtr_l,alloc);
int32_t base=j_add(Mem::l(LevelBss::Lvl_ZEdgePVSHeaderPtrsPtr_l),(Mem::w(LevelBss::Lvl_NumZones_w) * 4));
ZoneEdgePvs::zone_FillZEdgePVSHeaders(base,pvsCountBufferPtr);
ZoneEdgePvs::zone_FillZEdgePVSListData();
ZoneEdgePvs::zone_FillEdgePointIndexes();
Mem::ww(ZoneBss::Zone_RenderDoorState_w,0);
Mem::ww(ZoneBss::Zone_CurrentDoorState_w,0);
}

void Zone_FreeEdgePVS(){
if((Mem::l(LevelBss::Lvl_ZEdgePVSHeaderPtrsPtr_l) != 0)) {
ExecLib::FreeVec(Mem::l(LevelBss::Lvl_ZEdgePVSHeaderPtrsPtr_l));
Mem::wl(LevelBss::Lvl_ZEdgePVSHeaderPtrsPtr_l,0);
}
}

void Zone_UpdateVectors(){
if((Mem::b(PlayerBss::Plr_MultiplayerType_b) == ZoneEdgePvs::MULTIPLAYER_SLAVE)) {
Mem::ww(j_add(ZoneEdgePvs::zone_ViewPoint,Defs::Vec2W_X),Mem::w(j_add(PlayerBss::Plr2_Position_vl,(ZoneEdgePvs::POS_X * 2))));
Mem::ww(j_add(ZoneEdgePvs::zone_ViewPoint,Defs::Vec2W_Z),Mem::w(j_add(PlayerBss::Plr2_Position_vl,(ZoneEdgePvs::POS_Z * 2))));
}
else {
Mem::ww(j_add(ZoneEdgePvs::zone_ViewPoint,Defs::Vec2W_X),Mem::w(j_add(PlayerBss::Plr1_Position_vl,(ZoneEdgePvs::POS_X * 2))));
Mem::ww(j_add(ZoneEdgePvs::zone_ViewPoint,Defs::Vec2W_Z),Mem::w(j_add(PlayerBss::Plr1_Position_vl,(ZoneEdgePvs::POS_Z * 2))));
}
Mem::ww(j_add(ZoneEdgePvs::zone_PerpDir,Defs::Vec2W_X),-(Mem::w(HireswallData::Vis_CosVal_w)));
Mem::ww(j_add(ZoneEdgePvs::zone_PerpDir,Defs::Vec2W_Z),Mem::w(HireswallData::Vis_SinVal_w));
int32_t fovAngle=int16_t((Mem::w(HiresData::Vis_AngPos_w) - j_shr(ZoneEdgePvs::Zone_PVSFieldOfView,1)));
Mem::ww(j_add(ZoneEdgePvs::zone_LeftFOVDir,Defs::Vec2W_X),ZoneEdgePvs::sinw(fovAngle));
Mem::ww(j_add(ZoneEdgePvs::zone_LeftFOVDir,Defs::Vec2W_Z),ZoneEdgePvs::cosw(fovAngle));
(fovAngle=int16_t(j_add(fovAngle,ZoneEdgePvs::Zone_PVSFieldOfView)));
Mem::ww(j_add(ZoneEdgePvs::zone_RightFOVDir,Defs::Vec2W_X),ZoneEdgePvs::sinw(fovAngle));
Mem::ww(j_add(ZoneEdgePvs::zone_RightFOVDir,Defs::Vec2W_Z),ZoneEdgePvs::cosw(fovAngle));
}

void zone_ClearEdgePVSBuffer(int32_t size){
Mem::wb(ZoneBss::Zone_PVSMask_vb,0xFF);
for(int32_t i=1;(i < size);++(i)){
Mem::wb(j_add(ZoneBss::Zone_PVSMask_vb,i),0);
}
}

void zone_MergeEdgePVS(int32_t zoneMaskPtr,int32_t doorListMaskPtr,int32_t size){
if((doorListMaskPtr != 0)) {
int32_t mask=Mem::uw(ZoneBss::Zone_RenderDoorState_w);
for(int32_t i=1;(i < size);++(i)){
int32_t dlm=Mem::uw(j_add(doorListMaskPtr,(i * 2)));
Mem::wb(j_add(ZoneBss::Zone_PVSMask_vb,i),(Mem::ub(j_add(ZoneBss::Zone_PVSMask_vb,i)) | (((dlm & mask) == dlm)?Mem::ub(j_add(zoneMaskPtr,i)):0)));
}
}
else {
for(int32_t i=1;(i < size);++(i)){
Mem::wb(j_add(ZoneBss::Zone_PVSMask_vb,i),(Mem::ub(j_add(ZoneBss::Zone_PVSMask_vb,i)) | Mem::ub(j_add(zoneMaskPtr,i))));
}
}
}

void zone_MarkVisibleViaEdges(int32_t size){
int32_t zoneID=Mem::w(j_add(Mem::l(LevelBss::Lvl_ListOfGraphRoomsPtr_l),Defs::ZPVSRecordT_ZoneID_w));
ZoneEdgePvs::zone_MakePVSZoneIDList(ZoneEdgePvs::zoneAddr(zoneID),ZoneBss::Zone_PVSList_vw);
for(int32_t i=0;(i < size);++(i)){
int32_t z=Mem::w(j_add(ZoneBss::Zone_PVSList_vw,(i * 2)));
Mem::ww(j_add(ZoneEdgePvs::zoneAddr(z),Defs::ZoneT_Unused_w),Mem::ub(j_add(ZoneBss::Zone_PVSMask_vb,i)));
}
}

void Zone_CheckVisibleEdges(){
int32_t zoneID=Mem::w(j_add(Mem::l(LevelBss::Lvl_ListOfGraphRoomsPtr_l),Defs::ZPVSRecordT_ZoneID_w));
int32_t edgePVSPtr=ZoneEdgePvs::headerPtr(zoneID);
int32_t edgePVSListPtr=j_add(edgePVSPtr,Mem::w(j_add(edgePVSPtr,Defs::ZEdgePVSHeaderT_ZoneMaskOffset_w)));
int32_t doorOff=Mem::w(j_add(edgePVSPtr,Defs::ZEdgePVSHeaderT_DoorMaskOffset_w));
int32_t doorListMaskPtr=((doorOff != 0)?j_add(edgePVSPtr,doorOff):0);
int32_t numVisible=0;
int32_t edgeID{};
int32_t visJoinMask=0;
int32_t listSize=Mem::w(j_add(edgePVSPtr,Defs::ZEdgePVSHeaderT_ListSize_w));
int32_t edgeCount=Mem::w(j_add(edgePVSPtr,Defs::ZEdgePVSHeaderT_EdgeCount_w));
int32_t doorListStep=((doorListMaskPtr != 0)?listSize:0);
ZoneEdgePvs::Zone_UpdateVectors();
ZoneEdgePvs::zone_ClearEdgePVSBuffer(listSize);
Mem::ww(ZoneBss::Zone_RenderDoorState_w,Mem::uw(ZoneBss::Zone_CurrentDoorState_w));
int32_t edgePointIndex=ZoneBss::Zone_EdgePointIndexes_vw;
for(int32_t i=0;(i < edgeCount);++(i),(edgePVSListPtr+=listSize),(doorListMaskPtr+=(doorListStep * Defs::ZDoorListMask_SizeOf))){
(edgeID=Mem::w(ZoneEdgePvs::zeiAddr(edgePVSPtr,i,Defs::ZEdgeInfoT_EdgeID_w)));
int32_t edgePtr=ZoneEdgePvs::edgeAddr(edgeID);
int32_t startFlags=((ZoneEdgePvs::sideOfDirection(ZoneEdgePvs::zone_ViewPoint,ZoneEdgePvs::zone_PerpDir,edgePtr) < 0)?ZoneEdgePvs::BIT_FRONT:0);
(startFlags|=((ZoneEdgePvs::sideOfDirection(ZoneEdgePvs::zone_ViewPoint,ZoneEdgePvs::zone_LeftFOVDir,edgePtr) <= 0)?ZoneEdgePvs::BIT_LEFT:0));
(startFlags|=((ZoneEdgePvs::sideOfDirection(ZoneEdgePvs::zone_ViewPoint,ZoneEdgePvs::zone_RightFOVDir,edgePtr) >= 0)?ZoneEdgePvs::BIT_RIGHT:0));
if((startFlags == ((ZoneEdgePvs::BIT_FRONT | ZoneEdgePvs::BIT_LEFT) | ZoneEdgePvs::BIT_RIGHT))) {
(visJoinMask|=j_shl(1,i));
++(numVisible);
ZoneEdgePvs::zone_MergeEdgePVS(edgePVSListPtr,doorListMaskPtr,listSize);
Mem::ww(edgePointIndex,Mem::w(ZoneEdgePvs::zeiAddr(edgePVSPtr,i,Defs::ZEdgeInfoT_StartPointID_w)));
(edgePointIndex+=2);
Mem::ww(edgePointIndex,Mem::w(ZoneEdgePvs::zeiAddr(edgePVSPtr,i,Defs::ZEdgeInfoT_EndPointID_w)));
(edgePointIndex+=2);
continue;
}
Mem::ww(j_add(ZoneEdgePvs::scratch_endPoint,Defs::Vec2W_X),j_add(Mem::w(j_add(edgePtr,Defs::EdgeT_XPos_w)),Mem::w(j_add(edgePtr,Defs::EdgeT_XLen_w))));
Mem::ww(j_add(ZoneEdgePvs::scratch_endPoint,Defs::Vec2W_Z),j_add(Mem::w(j_add(edgePtr,Defs::EdgeT_ZPos_w)),Mem::w(j_add(edgePtr,Defs::EdgeT_ZLen_w))));
int32_t endFlags=((ZoneEdgePvs::sideOfDirection(ZoneEdgePvs::zone_ViewPoint,ZoneEdgePvs::zone_PerpDir,ZoneEdgePvs::scratch_endPoint) < 0)?ZoneEdgePvs::BIT_FRONT:0);
(endFlags|=((ZoneEdgePvs::sideOfDirection(ZoneEdgePvs::zone_ViewPoint,ZoneEdgePvs::zone_LeftFOVDir,ZoneEdgePvs::scratch_endPoint) <= 0)?ZoneEdgePvs::BIT_LEFT:0));
(endFlags|=((ZoneEdgePvs::sideOfDirection(ZoneEdgePvs::zone_ViewPoint,ZoneEdgePvs::zone_RightFOVDir,ZoneEdgePvs::scratch_endPoint) >= 0)?ZoneEdgePvs::BIT_RIGHT:0));
if((endFlags == ((ZoneEdgePvs::BIT_FRONT | ZoneEdgePvs::BIT_LEFT) | ZoneEdgePvs::BIT_RIGHT))) {
(visJoinMask|=j_shl(1,i));
++(numVisible);
ZoneEdgePvs::zone_MergeEdgePVS(edgePVSListPtr,doorListMaskPtr,listSize);
Mem::ww(edgePointIndex,Mem::w(ZoneEdgePvs::zeiAddr(edgePVSPtr,i,Defs::ZEdgeInfoT_StartPointID_w)));
(edgePointIndex+=2);
Mem::ww(edgePointIndex,Mem::w(ZoneEdgePvs::zeiAddr(edgePVSPtr,i,Defs::ZEdgeInfoT_EndPointID_w)));
(edgePointIndex+=2);
continue;
}
if((((((startFlags | endFlags) & ZoneEdgePvs::BIT_FRONT) != 0) && ((startFlags & ZoneEdgePvs::BIT_LEFT) == 0)) && ((endFlags & ZoneEdgePvs::BIT_RIGHT) == 0))) {
(visJoinMask|=j_shl(1,i));
++(numVisible);
ZoneEdgePvs::zone_MergeEdgePVS(edgePVSListPtr,doorListMaskPtr,listSize);
Mem::ww(edgePointIndex,Mem::w(ZoneEdgePvs::zeiAddr(edgePVSPtr,i,Defs::ZEdgeInfoT_StartPointID_w)));
(edgePointIndex+=2);
Mem::ww(edgePointIndex,Mem::w(ZoneEdgePvs::zeiAddr(edgePVSPtr,i,Defs::ZEdgeInfoT_EndPointID_w)));
(edgePointIndex+=2);
continue;
}
}
Mem::ww(edgePointIndex,ZoneEdgePvs::EDGE_POINT_ID_LIST_END);
Mem::ww(ZoneBss::Zone_VisJoinMask_w,visJoinMask);
Mem::ww(ZoneBss::Zone_VisJoins_w,numVisible);
Mem::ww(ZoneBss::Zone_TotJoins_w,edgeCount);
ZoneEdgePvs::zone_MarkVisibleViaEdges(listSize);
}

void Zone_SetupEdgeClipping(){
Mem::ww(DrawBss::Draw_ZoneClipL_w,0);
Mem::ww(DrawBss::Draw_ZoneClipR_w,Mem::w(HiresData::Vid_RightX_w));
Mem::wb(DrawBss::Draw_ForceZoneSkip_b,0);
int32_t minL=Mem::w(HiresData::Vid_RightX_w);
int32_t maxR=0;
if(((Mem::w(ZoneBss::Zone_VisJoins_w) > 0) && (Mem::w(j_add(Mem::l(LevelBss::Lvl_ListOfGraphRoomsPtr_l),Defs::ZPVSRecordT_ZoneID_w)) != Mem::w(DrawBss::Draw_CurrentZone_w)))) {
for(int32_t i=0;(i < j_shl(Mem::w(ZoneBss::Zone_VisJoins_w),1));(i+=2)){
int32_t scrL=Mem::w(j_add(TablesBss::OnScreen_vl,(Mem::w(j_add(ZoneBss::Zone_EdgePointIndexes_vw,(i * 2))) * 2)));
int32_t scrR=Mem::w(j_add(TablesBss::OnScreen_vl,(Mem::w(j_add(ZoneBss::Zone_EdgePointIndexes_vw,(j_add(i,1) * 2))) * 2)));
if((scrL > scrR)) {
(scrL=0);
(scrR=Mem::w(HiresData::Vid_RightX_w));
}
if((scrL < minL)) {
(minL=scrL);
}
if((scrR > maxR)) {
(maxR=scrR);
}
}
if((minL < 0)) {
(minL=0);
}
if((maxR > Mem::w(HiresData::Vid_RightX_w))) {
(maxR=Mem::w(HiresData::Vid_RightX_w));
}
Mem::ww(DrawBss::Draw_ZoneClipL_w,minL);
Mem::ww(DrawBss::Draw_ZoneClipR_w,maxR);
}
}

int32_t Zone_DetermineCrossing(int32_t from,int32_t to){
int32_t result=(ZoneEdgePvs::zone_LevelOverlap(ZoneEdgePvs::zone_GetLowerLevel(from),ZoneEdgePvs::zone_GetLowerLevel(to))?ZoneEdgePvs::LOWER_TO_LOWER:ZoneEdgePvs::NO_PATH);
int32_t test=((ZoneEdgePvs::zone_HasUpper(from)?1:0) | (ZoneEdgePvs::zone_HasUpper(to)?2:0));
switch(test){
case 1:
{(result|=(ZoneEdgePvs::zone_LevelOverlap(ZoneEdgePvs::zone_GetUpperLevel(from),ZoneEdgePvs::zone_GetLowerLevel(to))?ZoneEdgePvs::UPPER_TO_LOWER:ZoneEdgePvs::NO_PATH));
break;
}
case 2:
{(result|=(ZoneEdgePvs::zone_LevelOverlap(ZoneEdgePvs::zone_GetLowerLevel(from),ZoneEdgePvs::zone_GetUpperLevel(to))?ZoneEdgePvs::LOWER_TO_UPPER:ZoneEdgePvs::NO_PATH));
break;
}
case 3:
{(result|=(ZoneEdgePvs::zone_LevelOverlap(ZoneEdgePvs::zone_GetUpperLevel(from),ZoneEdgePvs::zone_GetLowerLevel(to))?ZoneEdgePvs::UPPER_TO_LOWER:ZoneEdgePvs::NO_PATH));
(result|=(ZoneEdgePvs::zone_LevelOverlap(ZoneEdgePvs::zone_GetLowerLevel(from),ZoneEdgePvs::zone_GetUpperLevel(to))?ZoneEdgePvs::LOWER_TO_UPPER:ZoneEdgePvs::NO_PATH));
(result|=(ZoneEdgePvs::zone_LevelOverlap(ZoneEdgePvs::zone_GetUpperLevel(from),ZoneEdgePvs::zone_GetUpperLevel(to))?ZoneEdgePvs::UPPER_TO_UPPER:ZoneEdgePvs::NO_PATH));
break;
}
default:
{break;
}
}
return result;
}

}