#pragma once

#include <cstdint>
#include <vector>
#include <memory>
#include <unordered_map>

#include "graphics/RenderStep.h"
#include "graphics/Scene.h"
#include "core/Camera.h"

namespace prism {

class RenderPipeline {

public:
    RenderPipeline(std::uint32_t width, std::uint32_t height);

    ~RenderPipeline() = default;

    Scene* createNewScene(bool setCurrent = true);

    Scene* getScene(PrismId prismId) const;

    bool setCurrentScene(Scene* scene);

    bool setCurrentScene(PrismId prismId);

    Scene* getCurrentScene() const;

    PrismId getCurrentSceneId() const;

    Camera* createNewCamera(bool setCurrent = true);

    Camera* getCamera(PrismId prismId) const;

    bool setCurrentCamera(Camera* camera);

    bool setCurrentCamera(PrismId prismId);

    Camera* getCurrentCamera() const;

    PrismId getCurrentCameraId() const;

    void buildQueue();

    void updateQueue();

    std::vector<RenderStep>& getRenderQueue();

private:
    // necessary data structures to create RenderStep objects and build the renderqueue
    std::unordered_map<PrismId, std::unique_ptr<Scene>> sceneMap;
    std::unordered_map<PrismId, std::unique_ptr<Camera>> cameraMap;

    PrismId currentSceneId = -1;
    PrismId currentCameraId = -1;

    bool sceneChanged = false;
    bool cameraChanged = false;

    // add list of targets (textures, screens, colour targets, normal targets, position targets, depth targets etc)

    // list (ordered) of renderSteps
    std::vector<RenderStep> renderQueue;

    // width and height of the final render target
    std::uint32_t width;
    std::uint32_t height;

};

}