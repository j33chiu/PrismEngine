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
class VertexContainer {

public:
    VertexContainer(const VertexDataAttributes& vertexAttr, std::vector<std::uint8_t>& verticesBytes) 
        : vertexAttr(vertexAttr)
        , vertexStride(vertexAttr.vertexStride)
        , verticesBytes(verticesBytes)
        , numVertices(verticesBytes.size() / vertexAttr.vertexStride)
        , newVertexOffset(verticesBytes.size())
        , newVertexI(0)
    {}

    VertexContainer(const VertexDataAttributes& vertexAttr) 
        : vertexAttr(vertexAttr)
        , vertexStride(vertexAttr.vertexStride)
        , verticesBytes()
        , numVertices(0)
        , newVertexOffset(0)
        , newVertexI(0)
    {}


// sample cast function
/*
std::vector<std::uint8_t> cast(pml::DOUBLE value) {
    std::uint64_t casted = *((std::int64_t*)&value);

    std::vector<std::uint8_t> out;

    for (int i = 0; i < sizeof(value) / sizeof(std::uint8_t); i++) {
        out.push_back((casted >> 8 * i) & 0xFF);
    }
    return out;
}
*/

    void addVertex(const void* vertexDataPtr) {/*
        // cast ptr to unsigned 8 bit int
        const std::uint8_t* p = static_cast<const std::uint8_t*>(vertexDataPtr);
        // insert new bytes at end of vector
        newVertexOffset = verticesBytes.size();
        newVertexI = 0;
        numVertices++;
        verticesBytes.insert(verticesBytes.end(), vertexStride, 0u);
        // insert data
        for (int i = 0; i < vertexStride; i++) {
            verticesBytes[newVertexOffset + newVertexI] = p[i];
            newVertexI = (newVertexI + 1) % vertexStride;
        }
*/

        // endianness
        // constexpr bool isBigEndian = (std::endian::native == std::endian::big);

        // insert new bytes at end of vector
        newVertexOffset = verticesBytes.size();
        newVertexI = 0;
        numVertices++;
        verticesBytes.insert(verticesBytes.end(), vertexStride, 0u);
        // insert data
        std::uint8_t* casted = (std::uint8_t*)vertexDataPtr;
        for (int i = 0; i < vertexStride; i++) {
            verticesBytes[newVertexOffset + newVertexI] = casted[i];
            newVertexI = (newVertexI + 1) % vertexStride;
        }
    }

    const std::vector<std::uint8_t>& getBytes() const {
        return verticesBytes;
    }

   std::vector<std::uint8_t> getBytesCopy() const {
        return verticesBytes;
    }

    const void* getVerticesAddress() const {
        return verticesBytes.data();
    }

    std::size_t getDataSize() const {
        return sizeof(std::uint8_t) * verticesBytes.size();
    }

    std::size_t getNumVertices() const {
        return numVertices;
    }

    std::size_t getVertexStride() const {
        return vertexStride;
    }

    const VertexDataAttributes getVertexAttr() const {
        return vertexAttr;
    }
    

private:
    const VertexDataAttributes vertexAttr;

    std::vector<std::uint8_t> verticesBytes;
    std::size_t numVertices;


    const std::size_t vertexStride;
    
    std::size_t newVertexOffset;
    int newVertexI;

};

}