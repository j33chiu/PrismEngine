#include "graphics/Window.h"

#include "logger/Logger.h"

namespace prism {

Window::Window(std::uint32_t width, std::uint32_t height) 
    : width(width),
    height(height)
{}

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
    renderFlag = true;
    renderThreadRunning = true;
    this->removeContext(); // remove context from current thread so renderThread can set context
    renderThread = std::thread(&Window::renderLoop, this);
}

void Window::stopRenderThread() {
    //windowController.stop();
    renderFlag = false;
    renderThread.join(); // render thread finished
    this->setContext();  // set the context back to current thread
}

bool Window::isRenderThreadRunning() const {
    return renderThreadRunning;
}

void Window::renderLoop() {
    this->setContext(); // set context in render thread
    while(renderFlag) {
        this->render();
    }
    renderThreadRunning = false;
    this->removeContext(); // remove context from render thread, renderloop is done, usually means app shutdown, or stop rendering of scene
}

}