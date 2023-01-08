#pragma once

#include <string>
#include <cstdint>

#include "graphics/Mesh.h"
#include "graphics/PrimitiveType.h"

namespace prism {

enum class RenderObjectType {
    SINGLE, INSTANCED
};

class RenderObject {

public:
    RenderObject(const Mesh *mesh, PrimitiveType type = PrimitiveType::TRIANGE);

    virtual ~RenderObject() = default;

    // remove copy constructors
    RenderObject(const RenderObject&) = delete;
    RenderObject &operator=(const RenderObject&) = delete;
    // default move constructors
    RenderObject(RenderObject&&) = default;
    RenderObject &operator=(RenderObject&&) = default;

    const Mesh* getMesh() const;

    virtual RenderObjectType getType() const = 0;
    PrimitiveType getPrimitiveType() const;

    bool showsWireframe() const;
    void setWireframe(bool showWireframe);

    std::string getGroupName() const;
    void setGroupName(std::string groupName);

    std::string getName() const;
    void setName(std::string name);

private:
    const Mesh* mesh;

    std::string groupName;      // group of similar objects can share a group name
    std::string objectName;     // should be a unique identifier

    // render properties
    PrimitiveType type;
    bool showWireframe = false;
    // transparency, shadows, reflections, etc...

};

}