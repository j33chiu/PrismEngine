#pragma once

#include <cstdint>
#include <vector>
#include <variant>

#include "core/math/pml.h"
#include "core/Exception.h"
#include "logger/Logger.h"

namespace prism {

// TODO: add tangent, bitangent, bones
enum class VertexAttr : std::uint32_t {
    POSITION,
    NORMAL,
    COLOUR,
    TEXUV
};

enum class VertexAttrDataType : std::uint32_t {
    FLOAT,
    INT8,
    UINT8,
    INT16,
    UINT16,
    INT32,
    UINT32,
    INT64,
    UINT64,
    UNKNOWN
};

struct VertexDataAttributes {
    std::string vertexDataId;
    std::vector<VertexAttr> attributes;
    std::vector<VertexAttrDataType> componentTypes;
    std::vector<int> componentLengths;
    int vertexStride;
};

// users can create custom vertex data arrangements and can include attributes listed in VertexAttr
// note that getAttributeInfo MUST be implemented for ALL VertexAttr enums, and getVertexId must be implemented with unique ids
//      For Unused attributes, skip
// see existing examples in this file
// NOTE: getVertexDataAttributes should NEVER be called by the engine unless a specic DEFAULT vertex type is used
struct VertexData {};

// default vertex data layout
struct VertexDataFloat : public VertexData {
    pml::vec3 position;
    pml::vec3 normal;
    pml::vec4 colour;
    pml::vec2 texCoords;
};
inline static VertexDataAttributes getVertexDataAttributes(VertexDataFloat vertexDataDummy) {
    std::string vertexDataId = "vertexDataFloat";
    std::vector<VertexAttr> a;
    a.insert(a.end(), {VertexAttr::POSITION, VertexAttr::NORMAL, VertexAttr::COLOUR, VertexAttr::TEXUV});
    std::vector<VertexAttrDataType> b;
    b.insert(b.end(), {VertexAttrDataType::FLOAT, VertexAttrDataType::FLOAT, VertexAttrDataType::FLOAT, VertexAttrDataType::FLOAT});
    std::vector<int> c;
    c.insert(c.end(), {3, 3, 4, 2});
    int vertexStride = 12u * sizeof(pml::FLOAT);
    return VertexDataAttributes {
        vertexDataId, a, b, c, vertexStride
    };
}

// space efficient for procedurally generated chunk voxel/grid worlds with fixed blocks (aka minecraft)
struct VertexDataEfficient : public VertexData {
    // posX, posY and posZ rely on "chunks" less than 256 large
    // this is equivalent to pml::vec<3, pml::UINT8> position
    pml::UINT8 posX;
    pml::UINT8 posY;
    pml::UINT8 posZ;
    pml::UINT8 normal; // 8 bits is sufficient for 6 possible normal vectors
    pml::vec<4, pml::UINT8> colour;
    pml::UINT8 textureCoord; // number corresponding to texture on a texture atlas    
};
inline static VertexDataAttributes getVertexDataAttributes(VertexDataEfficient vertexDataDummy) {
    std::string vertexDataId = "vertexDataEfficient";
    std::vector<VertexAttr> a;
    a.insert(a.end(), {VertexAttr::POSITION, VertexAttr::NORMAL, VertexAttr::COLOUR, VertexAttr::TEXUV});
    std::vector<VertexAttrDataType> b;
    b.insert(b.end(), {VertexAttrDataType::UINT8, VertexAttrDataType::UINT8, VertexAttrDataType::UINT8, VertexAttrDataType::UINT8});
    std::vector<int> c;
    c.insert(c.end(), {3, 1, 4, 1});
    int vertexStride = 9u * sizeof(pml::UINT8);
    return VertexDataAttributes {
        vertexDataId, a, b, c, vertexStride
    };
}

// basic vertex for debugging purposes
struct VertexDataDebug : public VertexData {
    pml::vec3 pos;
    pml::vec4 colour;
};
inline static VertexDataAttributes getVertexDataAttributes(VertexDataDebug vertexDataDummy) {
    std::string vertexDataId = "vertexDataDebug";
    std::vector<VertexAttr> a;
    a.insert(a.end(), {VertexAttr::POSITION, VertexAttr::COLOUR});
    std::vector<VertexAttrDataType> b;
    b.insert(b.end(), {VertexAttrDataType::FLOAT, VertexAttrDataType::FLOAT});
    std::vector<int> c;
    c.insert(c.end(), {3, 4});
    int vertexStride = 7u * sizeof(pml::FLOAT);
    return VertexDataAttributes {
        vertexDataId, a, b, c, vertexStride
    };
}

/**
 * this is a container class for vertex objects 
 * 
*/
class BaseVertexContainer {

public:
    BaseVertexContainer(const VertexDataAttributes& vertexAttr) 
        : vertexAttr(vertexAttr)
    {}

    const VertexDataAttributes getVertexDataAttributes() const {
        return vertexAttr;
    }

    virtual const void* getVerticesAddress() const = 0;

    virtual std::size_t getDataSize() const = 0;

    virtual std::size_t getNumVertices() const = 0;

    virtual std::size_t getVertexStride() const = 0;

private:
    const VertexDataAttributes vertexAttr;

};

template<class T>
class VertexContainer : public BaseVertexContainer {

public:
    VertexContainer(const VertexDataAttributes& vertexAttr, std::vector<T>& vertices) 
        : BaseVertexContainer(vertexAttr)
        , vertices(vertices)
    {}

    VertexContainer(const VertexDataAttributes& vertexAttr) 
        : BaseVertexContainer(vertexAttr)
        , vertices()
    {}

    void addVertex(T& v) {
        vertices.push_back(v);
    }

    void insertVertex(T& v, int index) {
        vertices.insert(vertices.begin() + index, v);
    }

    const T& at(int index) const {
        return vertices.at(index);
    }

    void remove(int index) {
        vertices.erase(vertices.begin() + index);
    }

    const std::vector<T>& getVertices() const {
        return vertices;
    }

    std::vector<T> getVerticesCopy() const {
        return vertices;
    }

    const void* getVerticesAddress() const override {
        return vertices.data();
    }

    std::size_t getDataSize() const override {
        return sizeof(T) * vertices.size();
    }

    std::size_t getNumVertices() const override {
        return vertices.size();
    }

    std::size_t getVertexStride() const override {
        return sizeof(T);
    }

private:
    std::vector<T> vertices;

};

}