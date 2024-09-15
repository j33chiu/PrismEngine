#pragma once

#include <string>
#include <vector>
#include <memory>
#include <mutex>

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

    bool hasRunningWindows() {
        for (bool b : windowThreadsRunning) {
            if (b) return true;
        }
        return false;
    }

protected:
    // for window events, we start the window in a separate helper thread from the render and game loop threads
    // this thread polls for window events and updates a shared window resource that the game loop and render threads can access if needed
    std::vector<bool> windowThreadsRunning;
    std::vector<bool> windowCanBeDestroyed;
    std::vector<std::thread> windowThreads;

    virtual void createWindowThreaded(std::string windowName, std::uint32_t width, std::uint32_t height, int windowId) = 0;

    std::mutex currentWindowMut;
    Window* currentWindow = nullptr;

    std::mutex windowMut;
    int windowIdCounter = 0;
    std::vector<std::unique_ptr<Window>> windowsList;

    void joinAllWindowThreads() {
        for (int i = 0; i < windowThreads.size(); i++) {
            windowThreads.at(i).join();
        }
    }

};

}