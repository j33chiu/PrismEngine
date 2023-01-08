#include "graphics/RenderStep.h"

namespace prism {

RenderStep::RenderStep(RenderStepType type)
    : type(type)
    , camera(nullptr)
    , renderObject(nullptr)
    , material(nullptr)
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
{}

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

}