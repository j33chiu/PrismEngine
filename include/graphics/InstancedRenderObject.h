#pragma once

#include "graphics/RenderObject.h"
#include "core/math/pml.h"


namespace prism {

class InstancedRenderObject : public RenderObject {

public:
    InstancedRenderObject(const Mesh *mesh, const std::vector<pml::mat4> &instances, PrimitiveType primitiveType = PrimitiveType::TRIANGE);
    ~InstancedRenderObject() override = default;

    RenderObjectType getType() const override;

    std::size_t getInstancesCount() const;

    const std::vector<pml::mat4>& getData() const;

private:
    std::size_t instances;
    std::vector<pml::mat4> data;

};

}