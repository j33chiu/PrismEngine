#include "graphics/GraphicsSettings.h"

namespace prism {

GraphicsSettings::GraphicsSettings() {
    // TODO: load from default settings/conf file which we read/write to/from
}

bool GraphicsSettings::isVsyncEnabled() {
    return vsyncEnabled;
}

void GraphicsSettings::setVsyncEnabled(bool vsyncEnabled) {
    this->vsyncEnabled = vsyncEnabled;
}

bool GraphicsSettings::isFPSCapped() {
    return fpsCapped;
}

void GraphicsSettings::setFPSCapped(bool fpsCapped) {
    this->fpsCapped = fpsCapped;
}

int GraphicsSettings::getFPSCap() {
    return fpsCap;
}

bool GraphicsSettings::setFPSCap(int fpsCap) {
    if (fpsCap <= 0) return false;
    this->fpsCap = fpsCap;
    return true;
}

}