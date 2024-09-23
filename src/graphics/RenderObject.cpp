#include "graphics/RenderObject.h"

namespace prism {

RenderObject::RenderObject(const Mesh* mesh, PrimitiveType type) 
    : mesh(mesh)
    , type(type)
    , groupName()
    , objectName()
    , showWireframe(false)
    , instanceTransforms()
{}

const Mesh* RenderObject::getMesh() const {
    return mesh;
}

const PrismId RenderObject::getId() const {
    return objectId;
}

RenderObjectType RenderObject::getType() const {
    int instances = instanceTransforms.size();
    if (instances > 1) return RenderObjectType::INSTANCED;
    else if (instances == 1) return RenderObjectType::SINGLE;
    else return RenderObjectType::NONE;
}

PrimitiveType RenderObject::getPrimitiveType() const {
    return type;
}

void RenderObject::addInstance(const pml::vec3& position) {
    instanceTransforms.emplace_back(pml::mat4({
        {1.0f, 0.0f, 0.0f, position.x},
        {0.0f, 1.0f, 0.0f, position.y},
        {0.0f, 0.0f, 1.0f, position.z},
        {0.0f, 0.0f, 0.0f, 1.0f}
    }));
}

void RenderObject::addInstance(const pml::mat4& transform) {
    instanceTransforms.emplace_back(transform);
}

bool RenderObject::removeInstance(int i) {
    if (i >= instanceTransforms.size()) return false;
    instanceTransforms.erase(instanceTransforms.begin() + i);
    return true;
}

int RenderObject::getNumInstances() const {
    return instanceTransforms.size();
}

const std::vector<pml::mat4>& RenderObject::getInstanceData() const {
    return instanceTransforms;
}

pml::mat4* RenderObject::getInstance(int i) {
    if (i >= instanceTransforms.size()) return nullptr;
    return &instanceTransforms[i];
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