#include "graphics/win32/Win32WindowManager.h"

namespace prism {

Win32WindowManager::Win32WindowManager() 
{}

Win32WindowManager::Win32WindowManager(Platform platform) 
    : platform(platform)
{}

Window *Win32WindowManager::createWindow(std::uint32_t width, std::uint32_t height) {
    return createWindow("Prism Application", width, height);
}

Window *Win32WindowManager::createWindow(std::string windowName, std::uint32_t width, std::uint32_t height) {
    // graphics api to use (openGL, Vulkan, DirectX etc)

    Window* out = nullptr;

    if (platform.graphicsApi == GraphicsApi::OPENGL) {
        std::unique_ptr<Win32OpenglWindow> window = std::make_unique<Win32OpenglWindow>(windowName, width, height);
        window->setPrismFocusCallback(std::bind(&WindowManager::setCurrentWindow, this, std::placeholders::_1));
        out = window.get();
        windowsList.push_back(std::move(window));
        windowIdCounter++;
    } else if (platform.graphicsApi == GraphicsApi::DIRECTX12) {
        windowIdCounter++;
    } else if (platform.graphicsApi == GraphicsApi::VULKAN) {
        windowIdCounter++;
    } else {
        throw Exception("unrecognized graphics api");
    }
    
    // return most recently added window
    return out;
}

Window *Win32WindowManager::getCurrentWindow() const {
    return currentWindow;
}

}