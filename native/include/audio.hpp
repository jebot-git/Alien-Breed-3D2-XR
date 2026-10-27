#pragma once
#include <cstdint>
namespace ab3d2::audio {
struct Stats {bool enabled=false,active=false;int referencePeriod=443,referenceRate=8006,deviceRate=0;uint64_t buffers=0,inputFrames=0,outputFrames=0,dmaTriggers=0,queueFailures=0;unsigned queuedBytes=0;int peak=0;};
/* Disabled by default. The original worker calls the four Paula hooks in
 * order, with original newsampbitl() immediately before queueFromPaula().
 * No SDL callback reads original RAM. Stop after parking/joining the worker. */
void setEnabled(bool enabled);
bool ensureStarted();
bool needsBuffer();
void queueFromPaula();
void stop();
Stats stats();
}
