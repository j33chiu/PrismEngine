#include "graphics/RenderPipeline.h"

#include <assert.h>

#include "graphics/RenderObject.h"
#include "logger/Logger.h"
#include "core/Exception.h"

namespace prism {

RenderPipeline::RenderPipeline(const uint32_t width, const uint32_t height) 
    : width(width)
    , height(height)
    , renderQueueStart(new RenderStep(RenderStepType::START_PASS))
    , queueMaterialLookup()
    , stepsToAdd(50)
    , loadedObjectRenderSteps()
    , sceneMap()
    , cameraMap()
{}

void RenderPipeline::updateCameraSize(const uint32_t width, const uint32_t height) {
    this->width = width;
    this->height = height;
    // update each camera
    for (PrismId cameraId : cameraIds) {
        Camera* camera = getCamera(cameraId);
        camera->setWidth(width);
        camera->setHeight(height);
    }
}

Scene* RenderPipeline::createNewScene(bool setCurrent) {
    //std::unique_ptr<Scene> newScene = std::make_unique<Scene>();
    std::unique_ptr<Scene> newScene = std::unique_ptr<Scene>(new Scene{});
    PrismId newSceneId = newScene.get()->getId();
    sceneMap.emplace(newSceneId, std::move(newScene));
    if (setCurrent) currentSceneId = newSceneId;
    return sceneMap[newSceneId].get();
}

Scene* RenderPipeline::getScene(PrismId prismId) const {
    if (sceneMap.find(prismId) == sceneMap.end()) {
        Logger::error("RenderPipeline::getScene", "no scene with id found in map");
        return nullptr;
    }
    return sceneMap.at(prismId).get();
}

bool RenderPipeline::setCurrentScene(Scene* scene) {
    if (sceneMap.find(scene->getId()) == sceneMap.end()) {
        Logger::error("RenderPipeline::setCurrentScene", "map does not contain this scene's id");
        return false;
    }
    if (currentSceneId != scene->getId()) sceneChanged.store(true);
    currentSceneId = scene->getId();
    return true;
}

bool RenderPipeline::setCurrentScene(PrismId prismId) {
    if (sceneMap.find(prismId) == sceneMap.end()) {
        Logger::error("RenderPipeline::setCurrentScene", "map does not contain this id");
        return false;
    }
    if (currentSceneId != prismId) sceneChanged.store(true);
    currentSceneId = prismId;
    return true;
}

Scene* RenderPipeline::getCurrentScene() const {
    return sceneMap.at(currentSceneId).get();
}

PrismId RenderPipeline::getCurrentSceneId() const {
    return currentSceneId;
}

RenderObject* RenderPipeline::triggerAddObject(const PrismId sceneId, const Material* material, std::unique_ptr<RenderObject> object) {
    Scene* scene = getScene(sceneId);
    if (!scene) {
        Logger::warn("RenderPipeline::triggerAddObject()", "Scene does not exist");
        return nullptr;
    }
    if (!object) {
        Logger::warn("RenderPipeline::triggerAddObject()", "Object is invalid");
        return nullptr;
    }
    RenderObject* out = scene->addObject(material, std::move(object));
    // if scene is the current scene create renderstep and add to queue to be inserted
    if (scene->getId() == getCurrentSceneId()) {
        std::unique_ptr<RenderStep> s(new RenderStep(RenderStepType::DRAW));
        s->setCamera(getCurrentCamera());
        s->setObject(out);
        s->setMaterial(material);
        s->setAsyncReady(true);
        while (stepsToAdd.full());
        if (!stepsToAdd.try_push(std::move(s))) {
            Logger::error("RenderPipeline::triggerAddObject()", "unable to queue object for rendering");
        }
    }
    return out;
}

bool RenderPipeline::triggerDeleteObject(const PrismId sceneId, const PrismId objectId) {
    Scene* scene = getScene(sceneId);
    if (!scene) {
        Logger::warn("RenderPipeline::triggerDeleteObject()", "Scene does not exist");
        return false;
    }
    if (scene->getId() != currentSceneId) {
        // renderer should not have the object in its renderqueue, safe to delete directly here
        scene->removeObject(objectId);
        return true;
    }

    // object is currently loaded, so we should flag it for removal from the render queue
    // Renderer class handles actual removal when .render() is called, so after we setValid(false), the next frame rendered should delete the RenderStep and object
    auto it = loadedObjectRenderSteps.find(objectId);
    if (it == loadedObjectRenderSteps.end()) {
        Logger::warn("RenderPipeline::triggerDeleteObject()", "object does not have RenderStep associated with it in the given scene.");
        return false;
    }
    RenderStep* step = it->second;
    if (!step) {
        Logger::warn("RenderPipeline::triggerDeleteObject()", "object has null RenderStep associated with it");
        return false;
    }
    step->setValid(false);
    loadedObjectRenderSteps.erase(objectId);
    return true;
}

Camera* RenderPipeline::createNewCamera(bool setCurrent) {
    std::unique_ptr<Camera> newCamera = std::make_unique<Camera>(width, height);
    PrismId newCameraId = newCamera.get()->getId();
    cameraIds.insert(newCameraId);
    cameraMap.emplace(newCameraId, std::move(newCamera));
    if (setCurrent) currentCameraId = newCameraId;
    return cameraMap[newCameraId].get();
}

Camera* RenderPipeline::getCamera(PrismId prismId) const {
    if (cameraMap.find(prismId) == cameraMap.end()) {
        Logger::error("RenderPipeline::getCamera", "no camera with id found in map");
        return nullptr;
    }
    return cameraMap.at(prismId).get();
}

bool RenderPipeline::setCurrentCamera(Camera* camera) {
    if (cameraMap.find(camera->getId()) == cameraMap.end()) {
        Logger::error("RenderPipeline::setCurrentCamera", "map does not contain this camera's id");
        return false;
    }
    if (currentCameraId != camera->getId()) cameraChanged.store(true);
    currentCameraId = camera->getId();
    return true;
}

bool RenderPipeline::setCurrentCamera(PrismId prismId) {
    if (cameraMap.find(prismId) == cameraMap.end()) {
        Logger::error("RenderPipeline::setCurrentCamera", "map does not contain this id");
        return false;
    }
    if (currentCameraId != prismId) cameraChanged.store(true);
    currentCameraId = prismId;
    return true;
}

Camera* RenderPipeline::getCurrentCamera() const {
    return cameraMap.at(currentCameraId).get();
}

PrismId RenderPipeline::getCurrentCameraId() const {
    return currentCameraId;
}

// currently just building based on 1 camera and 1 scene for debug purposes
// to choose specific scene and to render from specific camera pov, update the currentCameraId and currentSceneId, then rebuildqueue
void RenderPipeline::buildQueue() {
    queueMaterialLookup.clear();
    loadedObjectRenderSteps.clear();

    if (cameraMap.size() == 0 || sceneMap.size() == 0) return;

    Camera* currentCamera = getCurrentCamera();
    Scene* currentScene = getCurrentScene();

    RenderStep* currentStep = renderQueueStart.get();
    currentStep->setCamera(currentCamera);
    currentStep->setAsyncReady(true);

    for (const auto &[material, renderObject] : currentScene->getObjects()) {
        // create renderstep
        std::unique_ptr<RenderStep> s(new RenderStep(RenderStepType::DRAW));
        s->setCamera(currentCamera);
        s->setObject(renderObject.get());
        s->setMaterial(material);
        s->setAsyncReady(true);
        loadedObjectRenderSteps[renderObject->getId()] = s.get();

        // if material is new, add to lookup and add dummy renderstep then add s
        auto it = queueMaterialLookup.find(material);
        if (it == queueMaterialLookup.end()) {
            // new material
            std::unique_ptr<RenderStep> dummyDraw(new RenderStep(RenderStepType::MATERIAL));
            currentStep = currentStep->setNextStep(std::move(dummyDraw));
            queueMaterialLookup[material] = currentStep;
            currentStep = currentStep->setNextStep(std::move(s));
        } else {
            // old material, insert renderstep after the old dummy renderstep that corresponds to the material
            it->second->insertStep(std::move(s));
        }
    }

    std::unique_ptr<RenderStep> endPassStep(new RenderStep(RenderStepType::END_PASS));
    endPassStep->setAsyncReady(true);
    currentStep->setNextStep(std::move(endPassStep));
    currentStep = currentStep->getNextStep();

    std::unique_ptr<RenderStep> frameStep(new RenderStep(RenderStepType::FRAME));
    frameStep->setAsyncReady(true);
    currentStep->setNextStep(std::move(frameStep));
    currentStep = currentStep->getNextStep();

    std::unique_ptr<RenderStep> noneStep(new RenderStep(RenderStepType::NONE));
    noneStep->setAsyncReady(true);
    currentStep->setNextStep(std::move(noneStep));
}

void RenderPipeline::updateQueue() {
    if (sceneChanged.load()) {
        // need to remove all DRAW rendersteps since they are tied to a scene's objects
        // this is basically a full reload of a scene, so game will likely need a loading page or something here
        buildQueue();
    } 
    if (cameraChanged.load()) {
        // only the camera has changed, so should just be rendering the same scene from a different perspective
        Camera* currentCamera = getCurrentCamera();
        Scene* currentScene = getCurrentScene();
        RenderStep* currentStep = renderQueueStart.get();
        while (currentStep) {
            switch(currentStep->getType()) {
                case RenderStepType::START_PASS: 
                    currentStep->setCamera(currentCamera);
                    break;
                case RenderStepType::DRAW:
                    currentStep->setCamera(currentCamera);
                    break;
                case RenderStepType::MATERIAL:
                case RenderStepType::END_PASS: 
                case RenderStepType::FRAME: 
                case RenderStepType::NONE:
                    break;
                default: 
                    Logger::warn("RenderPipeline::updateQueue()", "unknown RenderStep type");
                    break;
            }
            currentStep->setAsyncReady(true);
            currentStep = currentStep->getNextStep();
        }
    }
    while (!stepsToAdd.empty()) {
        // need to update the render queue (asynchronously)
        // object(s) have been added/removed
        std::optional<std::unique_ptr<RenderStep>> step = stepsToAdd.try_pop();
        if (step.has_value()) {
            std::unique_ptr<RenderStep> s = std::move(step.value());
            const RenderObject* renderObject = s->getObject();
            const Material* material = s->getMaterial();
            if (loadedObjectRenderSteps.find(renderObject->getId()) != loadedObjectRenderSteps.end()) {
                Logger::warn("RenderPipeline::updateQueue()", "object already exists in render queue");
                continue;
            }
            loadedObjectRenderSteps[renderObject->getId()] = s.get();

            // if material is new, add to lookup and add dummy renderstep then add s
            auto it = queueMaterialLookup.find(material);
            if (it == queueMaterialLookup.end()) {
                // new material
                std::unique_ptr<RenderStep> dummyDraw(new RenderStep(RenderStepType::MATERIAL));
                RenderStep* dummy = renderQueueStart->insertStep(std::move(dummyDraw));
                queueMaterialLookup[material] = dummy;
                dummy->setNextStep(std::move(s));
            } else {
                // old material, insert renderstep after the old dummy renderstep that corresponds to the material
                it->second->insertStep(std::move(s));
            }
        }
    }

    sceneChanged.store(false);
    cameraChanged.store(false);
}

RenderStep* RenderPipeline::getRenderQueueStart() const {
    return renderQueueStart.get();
}

}