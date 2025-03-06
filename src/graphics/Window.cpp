#include "graphics/Window.h"

#include "logger/Logger.h"

namespace prism {

Window::Window(std::uint32_t width, std::uint32_t height) 
    : width(width),
    height(height)
{}

GraphicsSettings* Window::getGraphicsSettings() {
    return &graphicsSettings;
}

void Window::updateGraphicsSettings() {
    // empty by default, implemented by the specific platform, as they each have different apis for stuff like vsync frame rates, texture resolution
}

void Window::setRenderPipeline(std::unique_ptr<RenderPipeline> pipeline) {
    renderer->setRenderPipeline(std::move(pipeline));
}

RenderPipeline* Window::getRenderPipeline() const {
    if (!renderer) return nullptr;
    return renderer->getRenderPipeline();
}

void Window::removeContext() {
    // empty by default, platforms that require this can implement them (like opengl)
}

void Window::setContext() {
    // empty by default, platforms that require this can implement them (like opengl)
}

void Window::render() {
    renderer->render();
}

std::uint32_t Window::getWidth() {
    return width;
}

std::uint32_t Window::getHeight() {
    return height;
}

void Window::updateSize(const uint32_t width, const uint32_t height) {
    this->width = width;
    this->height = height;
    // needs to update renderer and the render pipeline
    if (!renderer) {
        Logger::error("Window::updateSize", "Renderer unavailable to update...");
    } else {
        renderer->updateSize(width, height); // this updates the pipeline too
    }
}

bool Window::getHasPrismFocus() {
    return hasPrismFocus;
}

void Window::grabPrismFocus() {
    // callback to manager (dependent on platform) to set this window as "currentWindow"
    prismGrabFocusCallback(this);
}

void Window::setPrismFocusCallback(std::function<void(Window*)> prismGrabFocusCallback) {
    this->prismGrabFocusCallback = prismGrabFocusCallback;
}

void Window::startRenderThread() {
    //windowController.start();
    renderFlag.store(true);
    renderThreadRunning = true;
    this->removeContext(); // remove context from current thread so renderThread can set context
    renderThread = std::thread(&Window::renderLoop, this);
}

void Window::stopRenderThread() {
    //windowController.stop();
    renderFlag.store(false);
    renderThread.join(); // render thread finished
    this->setContext();  // set the context back to current thread
    // can now release the renderer, cleaning up resources
    renderer.reset();
}

bool Window::isRenderThreadRunning() const {
    return renderThreadRunning;
}

void Window::renderLoop() {
    this->setContext(); // set context in render thread
    setRenderThreadPriority();
    // fps counter
    int frames = 0;
    float fps = 0.0f;
    auto startTime = std::chrono::steady_clock::now();
    int elapsedMs;
    while(renderFlag.load()) {
        this->render();

        // fps counting
        auto timeNow = std::chrono::steady_clock::now();
        elapsedMs = std::chrono::duration_cast<std::chrono::milliseconds>(timeNow - startTime).count();
        frames++;
        if (elapsedMs >= 1000) {
            startTime = timeNow;
            fps = (frames * 1000.0f) / elapsedMs;
            frames = 0;
            prism::Logger::info("Window::renderLoop::fps", fps);
        }
    }
    renderThreadRunning = false;
    this->removeContext(); // remove context from render thread, renderloop is done, usually means app shutdown, or stop rendering of scene
}

bool Window::hasUiEvent() const {
    return !uiEventQueue.empty();
}

Event Window::pollUiEvent() {
    Event e = uiEventQueue.front();
    uiEventQueue.pop();
    return e;
}

}