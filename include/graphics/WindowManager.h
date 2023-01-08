#pragma once

#include <string>
#include <vector>
#include <memory>

#include "Window.h"

namespace prism {

class WindowManager {

public:
    virtual ~WindowManager() = default;

    virtual Window *createWindow(std::uint32_t width, std::uint32_t height) = 0;
    virtual Window *createWindow(std::string windowName, std::uint32_t width, std::uint32_t height) = 0;
    virtual Window *getCurrentWindow() const = 0;

    void setCurrentWindow(Window* window) {
        currentWindow = window;
    }

protected:
    Window* currentWindow = nullptr;
    int windowIdCounter = 0;
    std::vector<std::unique_ptr<Window>> windowsList;

};

}