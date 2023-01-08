#pragma once

#include <cstdint>
#include <vector>
#include <memory>

#include "graphics/RenderStep.h"
#include "graphics/Scene.h"
#include "core/Camera.h"

namespace prism {

class RenderPipeline {

public:
    RenderPipeline(std::uint32_t width, std::uint32_t height);

    ~RenderPipeline() = default;

    Scene* createNewScene();

    Scene* getScene(int i);

    Camera* createNewCamera();

    Camera* getCamera(int i);

    void buildQueue();

    std::vector<RenderStep>& getRenderQueue();

private:
    // necessary data structures to create RenderStep objects and build the renderqueue
    std::vector<std::unique_ptr<Scene>> scenes;
    std::vector<std::unique_ptr<Camera>> cameras;
    // add list of targets (textures, screens, colour targets, normal targets, position targets, depth targets etc)

    // list (ordered) of renderSteps
    std::vector<RenderStep> renderQueue;

    // width and height of the final render target
    std::uint32_t width;
    std::uint32_t height;

};

}