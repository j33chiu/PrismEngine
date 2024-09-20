#pragma once

#include <cstdint>

namespace prism {

enum class AntiAliasingSetting : std::uint32_t {
    DISABLED = 0U,
    SSAA,           // renders at higher resolution and downscales to fit display
    MSAA,           // samples edges of polygons and blends
    FXAA,           // post processing that smooths high-contrast edges (can lead to blurriness)
    TAA,            // uses previous frames to smooth edges (can blur)
    MLAA,           // post processing that identifies edges and smooths them
    SMAA            // enhanced MLAA
};

// graphics settings include: fps caps, vsync, etc
class GraphicsSettings {

public: 
    GraphicsSettings();

    AntiAliasingSetting getAntiAliasingSetting();
    void setAntiAliasingSetting(AntiAliasingSetting setting);

    bool isVsyncEnabled();
    void setVsyncEnabled(bool vsyncEnabled = false);

    bool isFPSCapped();
    void setFPSCapped(bool fpsCapped = false);

    int getFPSCap();
    bool setFPSCap(int fpsCap);

private:
    AntiAliasingSetting antiAliasing = AntiAliasingSetting::DISABLED;
    bool vsyncEnabled = false;
    bool fpsCapped = false;
    int fpsCap = 0;

};

}