#include "graphics/InstancedRenderObject.h"

namespace prism {

InstancedRenderObject::InstancedRenderObject(const Mesh *mesh, const std::vector<pml::mat4> &instances, PrimitiveType primitiveType)
    : RenderObject(mesh, primitiveType)
    , instances(instances.size())
{
    assert(instances.size() > 1);
    for (pml::mat4 transform : instances) {
        data.emplace_back(transform);
    }
}

RenderObjectType InstancedRenderObject::getType() const {
    return RenderObjectType::INSTANCED;
}

const std::vector<pml::mat4>& InstancedRenderObject::getData() const {
    return data;
}

std::size_t InstancedRenderObject::getInstancesCount() const {
    return instances;
}

}