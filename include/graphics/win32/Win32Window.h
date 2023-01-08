#pragma once

#include "core/AutoResource.h"
#include "core/Exception.h"
#include "graphics/Window.h"
#include "event/Event.h"
#include "logger/Logger.h"

#include <set>
#include <unordered_map>
#include <queue>
#include <Windows.h>
#include <cstdint>

namespace prism {

class Win32Window : public Window {
public:

    using AutoHInstance = AutoResource<HINSTANCE>;
    using AutoHwnd = AutoResource<HWND>;
    using AutoHdc = AutoResource<HDC>;

    Win32Window(std::string windowName, std::uint32_t width, std::uint32_t height);
    ~Win32Window() override;

    void setCursorStyle() override;
    void showWindowCursor(bool shouldShow) override;
    std::optional<Event> pollWindow() override;


    HDC getDeviceContext() const;
    std::uint32_t getDpi() const;
    std::uint32_t getScreenScale() const override;

protected:
    AutoHInstance instance;
    AutoHwnd window;
    AutoHdc hdc;
    WNDCLASS wc;
    bool fullscreen;

};

}