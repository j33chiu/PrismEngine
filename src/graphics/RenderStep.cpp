#include "graphics/RenderStep.h"

namespace prism {

RenderStep::RenderStep(RenderStepType type)
    : type(type)
    , camera(nullptr)
    , renderObject(nullptr)
    , material(nullptr)
    , asyncReady(false)
    , valid(true)
{}

RenderStep::RenderStep(
    RenderStepType type,
    const Camera* camera,
    const RenderObject* object,
    const Material* material) 
    : type(type)
    , camera(camera)
    , renderObject(object)
    , material(material)
    , asyncReady(false)
    , valid(true)
{}

RenderStep::RenderStep(RenderStep&& other) noexcept 
    : type(other.type)
    , nextStep(std::move(other.nextStep))
    , camera(other.camera)
    , renderObject(other.renderObject)
    , material(other.material)
    , asyncReady(other.asyncReady.load())
    , valid(other.valid.load())
{}

RenderStep& RenderStep::operator=(RenderStep&& other) noexcept {
    if (this != &other) {
        type = other.type;
        nextStep = std::move(other.nextStep);
        camera = other.camera;
        renderObject = other.renderObject;
        material = other.material;
        asyncReady.store(other.asyncReady.load());
        valid.store(other.valid.load());
    }
    return *this;
}

RenderStep* RenderStep::getNextStep() const {
    return nextStep.get();
}

RenderStep* RenderStep::setNextStep(std::unique_ptr<RenderStep> nextStep) {
    this->nextStep = std::move(nextStep);
    return this->nextStep.get();
}

RenderStep* RenderStep::insertStep(std::unique_ptr<RenderStep> nextStep) {
    nextStep->setNextStep(std::move(this->nextStep));
    this->nextStep = std::move(nextStep);
    return this->nextStep.get();
}

bool RenderStep::removeSelf(RenderStep* previousStep) {
    if (!previousStep) return false;
    previousStep->setNextStep(std::move(nextStep));
    return true;
}

RenderStepType RenderStep::getType() const {
    return type;
}

void RenderStep::setType(RenderStepType type) {
    this->type = type;
}

const Camera* RenderStep::getCamera() const {
    return camera;
}

void RenderStep::setCamera(const Camera* camera) {
    this->camera = camera;
}

const RenderObject* RenderStep::getObject() const {
    return renderObject;
}

void RenderStep::setObject(const RenderObject* object) {
    this->renderObject = object;
}

const Material* RenderStep::getMaterial() const {
    return material;
}

void RenderStep::setMaterial(const Material* material) {
    this->material = material;
}

void RenderStep::setAsyncReady(bool ready) {
    asyncReady.store(ready);
}

bool RenderStep::isAsyncReady() const {
    return asyncReady.load();
}

void RenderStep::setValid(bool valid) {
    this->valid.store(valid);
}

bool RenderStep::isValid() const {
    return valid.load();
}

}