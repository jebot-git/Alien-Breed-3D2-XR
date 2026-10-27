#pragma once
#include <functional>
namespace ab3d2::audio_bridge {
inline std::function<bool()> ensureStarted, needsBuffer;
inline std::function<void()> queueFromPaula, stop, captureFrame;
inline std::function<void(bool)> reset;
} // namespace ab3d2::audio_bridge
