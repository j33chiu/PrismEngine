#pragma once

#include <cstdint>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>

#include "graphics/RenderStep.h"
#include "graphics/Scene.h"
#include "core/Camera.h"
#include "multithreading/Queue.h"

namespace prism {

class RenderPipeline {

public:
    RenderPipeline(const uint32_t width, const uint32_t height);

    ~RenderPipeline() = default;

    void updateCameraSize(const uint32_t width, const uint32_t height);

    Scene* createNewScene(bool setCurrent = true);
    Scene* getScene(PrismId prismId) const;
    bool setCurrentScene(Scene* scene);
    bool setCurrentScene(PrismId prismId);
    Scene* getCurrentScene() const;
    PrismId getCurrentSceneId() const;

    // signals an object should be added to a scene
    RenderObject* triggerAddObject(const PrismId sceneId, const Material* material, std::unique_ptr<RenderObject> object);
    // signals an object should be removed from a scene
    bool triggerDeleteObject(const PrismId sceneId, const PrismId objectId);

    Camera* createNewCamera(bool setCurrent = true);
    Camera* getCamera(PrismId prismId) const;
    bool setCurrentCamera(Camera* camera);
    bool setCurrentCamera(PrismId prismId);
    Camera* getCurrentCamera() const;
    PrismId getCurrentCameraId() const;

    /**
     * builds the initial render queue from the currently set scene
     */
    void buildQueue();

    /**
     * called by the render thread to poll for any updates to the scene or camera
     */
    void updateQueue();

    RenderStep* getRenderQueueStart() const;

private:
    // necessary data structures to create RenderStep objects and build the renderqueue
    std::unordered_set<PrismId> cameraIds;

    std::unordered_map<PrismId, std::unique_ptr<Scene>> sceneMap;
    std::unordered_map<PrismId, std::unique_ptr<Camera>> cameraMap;

    PrismId currentSceneId = -1;
    PrismId currentCameraId = -1;

    std::atomic<bool> sceneChanged = false;     // for when the entire scene is changed
    std::atomic<bool> cameraChanged = false;    // for when the current camera in the scene is changed

    // add list of targets (textures, screens, colour targets, normal targets, position targets, depth targets etc)

    // for gpu rendering optimization, draw steps are in order of shader, then also by object VAO (TODO)
    std::unique_ptr<RenderStep> renderQueueStart;   // linked-list implementation, each renderstep owns a pointer to the next
    std::unordered_map<PrismId, RenderStep*> loadedObjectRenderSteps;       // maps objectIds to their corresponding rendersteps (only if object is currently being rendered)
    std::unordered_map<const Material*, RenderStep*> queueMaterialLookup;   // lookup for ordering of drawing rendersteps by shader
    
    Queue<std::unique_ptr<RenderStep>> stepsToAdd;  // game thread adds steps, render thread pops and places into actual queue

    // width and height of the final render target
    std::uint32_t width;
    std::uint32_t height;

};

}