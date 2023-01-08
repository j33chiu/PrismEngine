#include "graphics/SingleRenderObject.h"

namespace prism {

SingleRenderObject::SingleRenderObject(const Mesh* mesh, const pml::vec3 position, PrimitiveType primitiveType) 
    : RenderObject(mesh, primitiveType)
    , position(position)
    , transform()
{}

SingleRenderObject::SingleRenderObject(const Mesh* mesh, const pml::mat4 transform, PrimitiveType primitiveType) 
    : RenderObject(mesh, primitiveType)
    , position()
    , transform(transform)
{}

RenderObjectType SingleRenderObject::getType() const {
    return RenderObjectType::SINGLE;
}

pml::vec3 SingleRenderObject::getPosition() const {
    return position;
}

void SingleRenderObject::setPosition(pml::vec3 position) {
    this->position = position;
}

pml::mat4 SingleRenderObject::getData() const {
    return transform;
}

pml::mat4 SingleRenderObject::getTransform() const {
    return transform;
}

void SingleRenderObject::setTransform(pml::mat4 transform) {
    this->transform = transform;
}


}