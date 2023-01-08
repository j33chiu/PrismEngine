#include "graphics/RenderPipeline.h"

#include <assert.h>

#include "graphics/RenderObject.h"

namespace prism {

RenderPipeline::RenderPipeline(std::uint32_t width, std::uint32_t height) 
    : width(width)
    , height(height)
    , renderQueue()
    , scenes()
    , cameras()
{}

Scene* RenderPipeline::createNewScene() {
    scenes.push_back(std::unique_ptr<Scene>(new Scene{}));
    return scenes.back().get();
}

Scene* RenderPipeline::getScene(int i) {
    assert(i < scenes.size());
    return scenes[i].get();
}

Camera* RenderPipeline::createNewCamera() {
    cameras.push_back(std::make_unique<Camera>(height, width));
    return cameras.back().get();
}

Camera* RenderPipeline::getCamera(int i) {
    assert(i < cameras.size());
    return cameras[i].get();
}

// currently just building based on 1 camera and 1 scene for debug purposes
void RenderPipeline::buildQueue() {
    renderQueue.clear();
    
    if (cameras.size() > 0 && scenes.size() > 0) {
        RenderStep startPassStep(RenderStepType::START_PASS);
        startPassStep.setCamera(cameras[0].get());
        renderQueue.push_back(startPassStep);

        for (const auto &[material, renderObject] : scenes[0]->getObjects()) {
            RenderStep s(RenderStepType::DRAW);
            s.setCamera(cameras[0].get());
            s.setObject(renderObject.get());
            s.setMaterial(material);
            renderQueue.push_back(s);
        }

        RenderStep endPassStep(RenderStepType::END_PASS);
        renderQueue.push_back(endPassStep);

        RenderStep frameStep(RenderStepType::FRAME);
        renderQueue.push_back(frameStep);
    }
}

std::vector<RenderStep>& RenderPipeline::getRenderQueue() {
    return renderQueue;
}

}