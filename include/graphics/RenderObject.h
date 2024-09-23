#pragma once

#include <string>
#include <cstdint>

#include "graphics/Mesh.h"
#include "graphics/PrimitiveType.h"
#include "core/PrismId.h"

namespace prism {

enum class RenderObjectType {
    SINGLE, INSTANCED, NONE
};

class RenderObject {

public:
    RenderObject(const Mesh *mesh, PrimitiveType type = PrimitiveType::TRIANGLE);

    virtual ~RenderObject() = default;

    // remove copy constructors
    RenderObject(const RenderObject&) = delete;
    RenderObject &operator=(const RenderObject&) = delete;
    // default move constructors
    RenderObject(RenderObject&&) = default;
    RenderObject &operator=(RenderObject&&) = default;

    const Mesh* getMesh() const;
    const PrismId getId() const;

    virtual RenderObjectType getType() const;
    PrimitiveType getPrimitiveType() const;

    void addInstance(const pml::vec3& position);
    void addInstance(const pml::mat4& transform);
    bool removeInstance(int id);
    int getNumInstances() const;
    const std::vector<pml::mat4>& getInstanceData() const;
    pml::mat4* getInstance(int id);

    bool showsWireframe() const;
    void setWireframe(bool showWireframe);

    std::string getGroupName() const;
    void setGroupName(std::string groupName);

    std::string getName() const;
    void setName(std::string name);

private:
    PrismId objectId;
    const Mesh* mesh;

    std::string groupName;      // group of similar objects can share a group name
    std::string objectName;     // should be a unique identifier

    // render properties
    PrimitiveType type;
    bool showWireframe = false;
    // transparency, shadows, reflections, etc...

    // object transforms, holds transformation matrices of each instance. Game objects can get pointers to these and modify them
    std::vector<pml::mat4> instanceTransforms;  // get and remove instance functions use index as id

};

}