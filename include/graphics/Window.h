#pragma once

#include <memory>
#include <cstdint>
#include <functional>
#include <thread>
#include <deque>
#include <queue>

#include "core/Controller.h"
#include "event/Event.h"
#include "graphics/Renderer.h"
#include "graphics/RenderPipeline.h"
#include "graphics/GraphicsSettings.h"

namespace prism {

class Window {
public:
    Window(std::uint32_t width, std::uint32_t height);

    virtual ~Window() = default;

    Window(const Window &) = delete;
    Window &operator=(const Window &) = delete;

    // these are platform specific functions, so cannot be implemented in Window.cpp
    virtual void setCursorStyle() = 0;
    virtual void showWindowCursor(bool shouldShow) = 0;
    virtual std::optional<Event> pollWindow() = 0;
    virtual bool isKeyPressed(KeyId key) = 0;
    virtual bool isMousePressed(MouseButton mouseButton) = 0;

    // get/set/update graphics settings
    GraphicsSettings* getGraphicsSettings();
    virtual void updateGraphicsSettings();

    // rendering to window
    void setRenderPipeline(std::unique_ptr<RenderPipeline> pipeline);
    RenderPipeline* getRenderPipeline() const;
    virtual void removeContext();
    virtual void setContext();
    virtual void render();

    // for multiple windows, allow prism to know which is in focus and handle focus/unfocus events
    void setPrismFocusCallback(std::function<void(Window*)> prismGrabFocusCallback);
    void grabPrismFocus();

    std::uint32_t getWidth();
    std::uint32_t getHeight();
    void updateSize(const uint32_t width, const uint32_t height);
    virtual std::uint32_t getScreenScale() const = 0;

    bool getHasPrismFocus();

    // these should only be called from the main thread
    void startRenderThread();
    void stopRenderThread();
    bool isRenderThreadRunning() const;

    bool hasUiEvent() const;
    Event pollUiEvent();

    // get/set cursor position relative to the window
    virtual std::pair<int, int> getCursorPosition() = 0;               // implemented by specific platform
    virtual void setCursorPosition(int x, int y) = 0;   // implemented by specific platform

protected:
    std::uint32_t width;
    std::uint32_t height;
    std::unique_ptr<Renderer> renderer;
    bool hasPrismFocus = false;

    GraphicsSettings graphicsSettings;

    // event queues and key and button mappings for user interaction
    // uiState holds state of keys and mouse buttons, incrementing if != 0 for each time pollWindow is called
        // resets to 0 if key or mouse button released
        // sets to 0 if key or mouse button is pressed
    // heldState indicates whether or not a key is currently being pressed/held
    std::deque<Event> eventQueue;
    std::queue<Event> uiEventQueue;
    std::atomic<int> uiState[KEY_ID_MAX_SIZE] = {0};
    std::atomic<bool> heldState[KEY_ID_MAX_SIZE] = {false};

    
private: 
    std::function<void(Window*)> prismGrabFocusCallback;

    // for render thread
    bool renderFlag = false;
    bool renderThreadRunning = false;
    std::thread renderThread;

    void renderLoop();

};

}