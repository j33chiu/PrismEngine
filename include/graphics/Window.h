#pragma once

#include <memory>
#include <cstdint>
#include <functional>
#include <thread>

#include "core/Controller.h"
#include "event/Event.h"
#include "graphics/Renderer.h"
#include "graphics/RenderPipeline.h"

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
    virtual std::uint32_t getScreenScale() const = 0;

    bool getHasPrismFocus();

    // these should only be called from the main thread
    void startRenderThread();
    void stopRenderThread();
    bool isRenderThreadRunning() const;

protected:
    std::uint32_t width;
    std::uint32_t height;
    std::unique_ptr<Renderer> renderer;
    bool hasPrismFocus = false;
    
private: 
    std::function<void(Window*)> prismGrabFocusCallback;

    // for render thread
    bool renderFlag = false;
    bool renderThreadRunning = false;
    std::thread renderThread;

    void renderLoop();

};

}