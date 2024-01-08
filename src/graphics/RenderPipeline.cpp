#include "graphics/RenderPipeline.h"

#include <assert.h>

#include "graphics/RenderObject.h"

namespace prism {

RenderPipeline::RenderPipeline(std::uint32_t width, std::uint32_t height) 
    : width(width)
    , height(height)
    , renderQueue()
    , sceneMap()
    , cameraMap()
{}

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
    if (currentSceneId != scene->getId()) sceneChanged = true;
    currentSceneId = scene->getId();
    return true;
}

bool RenderPipeline::setCurrentScene(PrismId prismId) {
    if (sceneMap.find(prismId) == sceneMap.end()) {
        Logger::error("RenderPipeline::setCurrentScene", "map does not contain this id");
        return false;
    }
    if (currentSceneId != prismId) sceneChanged = true;
    currentSceneId = prismId;
    return true;
}

Scene* RenderPipeline::getCurrentScene() const {
    return sceneMap.at(currentSceneId).get();
}

PrismId RenderPipeline::getCurrentSceneId() const {
    return currentSceneId;
}

std::uint32_t getCurrentSceneIdx();

Camera* RenderPipeline::createNewCamera(bool setCurrent) {
    std::unique_ptr<Camera> newCamera = std::make_unique<Camera>(height, width);
    PrismId newCameraId = newCamera.get()->getId();
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
    if (currentCameraId != camera->getId()) cameraChanged = true;
    currentCameraId = camera->getId();
    return true;
}

bool RenderPipeline::setCurrentCamera(PrismId prismId) {
    if (cameraMap.find(prismId) == cameraMap.end()) {
        Logger::error("RenderPipeline::setCurrentCamera", "map does not contain this id");
        return false;
    }
    if (currentCameraId != prismId) cameraChanged = true;
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
    renderQueue.clear();
    
    if (cameraMap.size() > 0 && sceneMap.size() > 0) {
        RenderStep startPassStep(RenderStepType::START_PASS);
        Camera* currentCamera = getCurrentCamera();
        Scene* currentScene = getCurrentScene();
        startPassStep.setCamera(currentCamera);
        renderQueue.push_back(startPassStep);

        for (const auto &[material, renderObject] : currentScene->getObjects()) {
            RenderStep s(RenderStepType::DRAW);
            s.setCamera(currentCamera);
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

void RenderPipeline::updateQueue() {
    if (!sceneChanged && !cameraChanged) return;

    if (sceneChanged) {
        // need to remove all DRAW rendersteps since they are tied to a scene's objects
        // this is basically a full reload of a scene, so game will likely need a loading page or something here
        buildQueue();
    } else {
        // only the camera has changed, so should just be rendering the same scene from a different perspective
        Camera* currentCamera = getCurrentCamera();
        Scene* currentScene = getCurrentScene();
        for (RenderStep& step : renderQueue) {
            switch(step.getType()) {
                case RenderStepType::START_PASS: 
                    step.setCamera(currentCamera);
                    break;
                case RenderStepType::DRAW:
                    for (const auto &[material, renderObject] : currentScene->getObjects()) {
                        step.setCamera(currentCamera);
                        step.setObject(renderObject.get());
                        step.setMaterial(material);
                    }
                    break;
                case RenderStepType::END_PASS: 
                    break;
                case RenderStepType::FRAME: 
                    break;
                default: throw Exception("unknown RenderStep type");
            }
        }
    }

    sceneChanged = false;
    cameraChanged = false;
}

std::vector<RenderStep>& RenderPipeline::getRenderQueue() {
    return renderQueue;
}

}