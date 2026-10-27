#pragma once
#include <cstdint>
#include <vector>
namespace ab3d2 {
std::vector<uint64_t> captureCoreGlobals();
void restoreCoreGlobals(const std::vector<uint64_t> &values);
const char *coreLayoutId();
} // namespace ab3d2
