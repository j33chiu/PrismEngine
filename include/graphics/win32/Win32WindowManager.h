#pragma once

#include "graphics/WindowManager.h"
#include "graphics/win32/Win32OpenglWindow.h"
#include "logger/Logger.h"
#include "core/Exception.h"
#include "core/Platform.h"

namespace prism {

class Win32WindowManager : public WindowManager {

public:
    ~Win32WindowManager() override = default;
    Win32WindowManager();
    Win32WindowManager(Platform selectedPlatformInfo);

    Window *createWindow(std::uint32_t width, std::uint32_t height) override;
    Window *createWindow(std::string windowName, std::uint32_t width, std::uint32_t height) override;
    Window *getCurrentWindow() const override;

private:
    // default platform info
    Platform platform = {
        prism::DevicePlatform::WINDOWS,
        prism::GraphicsApi::OPENGL
    };
};

}