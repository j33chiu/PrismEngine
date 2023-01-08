#include "graphics/RenderObject.h"

namespace prism {

RenderObject::RenderObject(const Mesh* mesh, PrimitiveType type) 
    : mesh(mesh)
    , type(type)
    , groupName()
    , objectName()
    , showWireframe(false)
{}

const Mesh* RenderObject::getMesh() const {
    return mesh;
}

PrimitiveType RenderObject::getPrimitiveType() const {
    return type;
}

bool RenderObject::showsWireframe() const {
    return showWireframe;
}

void RenderObject::setWireframe(bool showWireframe) {
    this->showWireframe = showWireframe;
}

std::string RenderObject::getGroupName() const {
    return groupName;
}

void RenderObject::setGroupName(std::string groupName) {
    this->groupName = groupName;
}

std::string RenderObject::getName() const {
    return objectName;
}

void RenderObject::setName(std::string objectName) {
    this->objectName = objectName;
}

}