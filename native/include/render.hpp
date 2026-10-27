#pragma once
#include <array>
#include <cstdint>
#include <filesystem>
#include <memory>
#include <string>
#include <vector>
namespace ab3d2 {
using Matrix=std::array<float,16>;
inline constexpr Matrix Identity{1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1};
struct RenderView {
    Matrix viewProjection=Identity;
    Matrix headWorld=Identity;
    Matrix weaponWorld=Identity;
    std::array<float,3> camera{};
    float worldScale=1.0f;
    bool trackedWeapon=false;
};
struct Panel {
    enum Kind { Gameplay, Title, Story, Pause, Ending } kind=Gameplay;
    std::string caption;
    std::vector<std::string> lines;
    int selection=-1;
};
struct RenderStats {
    uint64_t eyeFrames=0,drawCalls=0,triangles=0,textureUploads=0,meshUploads=0,dynamicUpdates=0;
    uint64_t entities=0,weaponDraws=0,panelDraws=0,missingAssets=0;
};
/* Caller owns GL context, framebuffer, viewport and synchronization. Construct/
 * destroy in the GL thread. sync() only reads the parked original core, once
 * per PAL tick; drawEye never advances or writes simulation state. */
class Renderer {
    struct Impl;
    std::unique_ptr<Impl> impl;
public:
    Renderer();
    ~Renderer();
    Renderer(const Renderer&)=delete;
    Renderer& operator=(const Renderer&)=delete;
    void loadAssets(const std::filesystem::path &root);
    void loadLevel(int index);
    void sync();
    void setPanel(const Panel &panel);
    void drawEye(const RenderView &view);
    // Synced rest-pose socket on weaponWorld -Z, in physical metres.
    float muzzleDistance() const;
    const RenderStats &stats() const;
};
}
