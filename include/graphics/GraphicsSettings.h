#pragma once

namespace prism {

// graphics settings include: fps caps, vsync, etc
class GraphicsSettings {

public: 
    GraphicsSettings();

    bool isVsyncEnabled();
    void setVsyncEnabled(bool vsyncEnabled = false);

    bool isFPSCapped();
    void setFPSCapped(bool fpsCapped = false);

    int getFPSCap();
    bool setFPSCap(int fpsCap);

private:
    bool vsyncEnabled = false;
    bool fpsCapped = false;
    int fpsCap = 0;

};

}