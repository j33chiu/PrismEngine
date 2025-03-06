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
    int currentWindowIndex;

    windowMut.lock();
    // increase size of windowsList vector by 1
    windowsList.push_back(nullptr);
    windowThreadsRunning.push_back(true);
    windowCanBeDestroyed.resize(windowCanBeDestroyed.size() + 1);
    windowCanBeDestroyed[windowCanBeDestroyed.size() - 1] = std::make_shared<std::atomic<bool>>(false);
    windowThreads.push_back(std::thread(&Win32WindowManager::createWindowThreaded, this, windowName, width, height, windowIdCounter));
    currentWindowIndex = windowIdCounter;
    windowIdCounter++;
    windowMut.unlock();

    Window* out = nullptr;
    while (!windowsList.at(currentWindowIndex).get());
    out = windowsList.at(currentWindowIndex).get();
    out->setContext(); // grab context back to this thread
    return out;
}

Window *Win32WindowManager::getCurrentWindow() const {
    return currentWindow;
}

void Win32WindowManager::createWindowThreaded(std::string windowName, std::uint32_t width, std::uint32_t height, int windowId) {
    if (platform.graphicsApi == GraphicsApi::OPENGL) {
        std::unique_ptr<Win32OpenglWindow> window = std::make_unique<Win32OpenglWindow>(windowName, width, height);
        window->setPrismFocusCallback(std::bind(&WindowManager::setCurrentWindow, this, std::placeholders::_1));
        window.get()->removeContext(); // remove context from this thread, window has been created and we can give it back to the main thread;
        windowsList[windowId] = std::move(window);
    } else if (platform.graphicsApi == GraphicsApi::DIRECTX12) {
      
    } else if (platform.graphicsApi == GraphicsApi::VULKAN) {

    } else {
        throw Exception("unrecognized graphics api");
    }
    
    Window* newWindow = windowsList[windowId].get();
    bool windowRunning = true;
    while (windowRunning) {
        auto event = newWindow->pollWindow();
		// catch and pring events (key presses and releases, window focus events)
		if (event.has_value()) {
			if (event->isExitEvent()) {
                windowRunning = false; 
            }
			Event e1 = event.value();
            if (e1.getEventType() == EventType::SIZE) {
                if (e1.getSizeEvent().has_value()) {
                    SizeEvent se = e1.getSizeEvent().value();
                    newWindow->updateSize(se.newWidth, se.newHeight);
                }
            } else if (e1.getEventType() != EventType::MOUSE_MOVE) {
				Logger::debug("Win32Window::eventLoop", e1);
			}
			else {
				// Logger::debug("main", e1);
			}
		}
    }
    windowThreadsRunning[windowId] = false;

    // works with the destructor to ensure this thread calls ReleaseDC and DestroyWindow
    while (!windowCanBeDestroyed[windowId]->load());
    windowsList[windowId].reset();  // ensure proper destruction of window by this thread
    // thread done, can be joined in ~Win32WindowManager() below
}

Win32WindowManager::~Win32WindowManager() {
    for (int i = 0; i < windowsList.size(); i++) {
        windowCanBeDestroyed[i]->store(true);
    }
    joinAllWindowThreads();
    currentWindow = nullptr;
}

}