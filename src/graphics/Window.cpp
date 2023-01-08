#include "graphics/Window.h"

namespace prism {

Window::Window(std::uint32_t width, std::uint32_t height) 
    : width(width),
    height(height)
{}

void Window::setRenderPipeline(std::unique_ptr<RenderPipeline> pipeline) {
    renderer->setRenderPipeline(std::move(pipeline));
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

}