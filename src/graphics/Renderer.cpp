#include "graphics/Renderer.h"

#include "core/Exception.h"
#include "logger/Logger.h"

namespace prism {

Renderer::Renderer(const uint32_t width, const uint32_t height)
    : pipeline()
    , width(width)
    , height(height)
{}

void Renderer::render() {
    preRender();
    this->pipeline->updateQueue();
    RenderStep* prevStep = nullptr;
    RenderStep* currentStep = this->pipeline->getRenderQueueStart();
    while (currentStep) {
        if (!currentStep->isAsyncReady()) { // current step is not ready (other threads may be modifying)
            prevStep = currentStep;
            currentStep = currentStep->getNextStep();
            continue;
        }
        if (!currentStep->isValid()) {  // another thread has invalidated this step, we can remove it from the queue
            if (currentStep->getObject() != nullptr) {
                // if the step holds an object, we remove it from the scene (causing object deallocation)
                this->pipeline->getCurrentScene()->removeObject(currentStep->getObject()->getId());
            }
            currentStep->removeSelf(prevStep);
            currentStep = prevStep->getNextStep();
            continue;
        }
        switch(currentStep->getType()) {
            case RenderStepType::START_PASS: startPass(currentStep); break;
            case RenderStepType::DRAW: draw(currentStep); break;
            case RenderStepType::END_PASS: endPass(currentStep); break;
            case RenderStepType::FRAME: frame(currentStep); break;
            case RenderStepType::MATERIAL:
            case RenderStepType::NONE: break;
            default: 
                Logger::warn("Renderer::render()", "unknown RenderStep type");
                break;
        }
        prevStep = currentStep;
        currentStep = currentStep->getNextStep();
    }

    postRender();
}

void Renderer::setRenderPipeline(std::unique_ptr<RenderPipeline> pipeline) {
    this->pipeline = std::move(pipeline);
    this->pipeline->buildQueue();
}

RenderPipeline* Renderer::getRenderPipeline() const {
    if (!this->pipeline) return nullptr;
    return this->pipeline.get();
}

// render functions are empty (are implemented based on graphics api)
void Renderer::preRender() {

}

void Renderer::startPass(RenderStep* step) {

}

void Renderer::draw(RenderStep* step) {

}

void Renderer::endPass(RenderStep* step) {

}

void Renderer::frame(RenderStep* step) {

}

void Renderer::postRender() {

}

void Renderer::updateSize(const uint32_t width, const uint32_t height) {
    this->width = width;
    this->height = height;
    // update pipeline too
    if (!pipeline) {
        Logger::error("Renderer::updateSize", "RenderPipeline unavailable to update. If Error appears on startup, can ignore...");
    } else {
        pipeline->updateCameraSize(width, height);
    }
}

}