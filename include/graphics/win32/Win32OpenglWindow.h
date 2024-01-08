#pragma once

#include "graphics/win32/Win32Window.h"

namespace prism {

class Win32OpenglWindow : public Win32Window {

public:
    Win32OpenglWindow(std::string windowName, std::uint32_t width, std::uint32_t height);

    ~Win32OpenglWindow() = default;

    void removeContext() override;

    void setContext() override;

private:
    bool initActualOpenGL(HDC actualDc);

    HGLRC glContext;

};


}