#pragma once

#include "graphics/RenderObject.h"
#include "core/math/pml.h"

namespace prism {

class SingleRenderObject : public RenderObject {

public:
    SingleRenderObject(const Mesh* mesh, const pml::vec3 position, PrimitiveType primitiveType = PrimitiveType::TRIANGE);
    SingleRenderObject(const Mesh* mesh, const pml::mat4 transform, PrimitiveType primitiveType = PrimitiveType::TRIANGE);

    ~SingleRenderObject() override = default;
    
    SingleRenderObject(const SingleRenderObject &) = delete;
    SingleRenderObject &operator=(const SingleRenderObject &) = delete;
    SingleRenderObject(SingleRenderObject &&) = default;
    SingleRenderObject &operator=(SingleRenderObject &&) = default;

    RenderObjectType getType() const override;

    pml::vec3 getPosition() const;
    void setPosition(pml::vec3 position);
    
    pml::mat4 getData() const;

    pml::mat4 getTransform() const;
    void setTransform(pml::mat4 transform);

private:
    pml::mat4 transform;
    pml::vec3 position;


};

}