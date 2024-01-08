#include "graphics/Renderer.h"

#include "core/Exception.h"

namespace prism {

Renderer::Renderer()
    : pipeline()
    , renderQueue()
{}

void Renderer::render() {
    preRender();
    this->pipeline->updateQueue();
    for (RenderStep& step : renderQueue) {
        switch(step.getType()) {
            case RenderStepType::START_PASS: startPass(step); break;
            case RenderStepType::DRAW: draw(step); break;
            case RenderStepType::END_PASS: endPass(step); break;
            case RenderStepType::FRAME: frame(step); break;
            default: throw Exception("unknown RenderStep type");
        }
    }

    postRender();
}

void Renderer::setRenderPipeline(std::unique_ptr<RenderPipeline> pipeline) {
    this->pipeline = std::move(pipeline);
    this->pipeline->buildQueue();
    renderQueue = this->pipeline->getRenderQueue();
}

RenderPipeline* Renderer::getRenderPipeline() const {
    if (!this->pipeline) return nullptr;
    return this->pipeline.get();
}

// render functions are empty (are implemented based on graphics api)
void Renderer::preRender() {

}

void Renderer::startPass(RenderStep& step) {

}

void Renderer::draw(RenderStep& step) {

}

void Renderer::endPass(RenderStep& step) {

}

void Renderer::frame(RenderStep& step) {

}

void Renderer::postRender() {

}

}