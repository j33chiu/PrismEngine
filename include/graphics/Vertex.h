#pragma once

#include "core/math/pml.h"
#include "util/PrismHash.h"

namespace prism {

// TODO: add tangent, bitangent, bones
enum VertexAttribute : std::uint8_t {
    POSITION,
    NORMAL,
    COLOUR,
    TEXUV
};

enum VertexAttributeType : std::uint8_t {
    FLOAT,
    DOUBLE,
    INT8,
    UINT8,
    INT16,
    UINT16,
    INT32,
    UINT32,
    INT64,
    UINT64,
    UNKNOWN,
    NUMTYPES
};

class VertexDescriptor {

public:
    VertexDescriptor();
    VertexDescriptor(std::vector<std::vector<VertexAttributeType>>& format);
    
    const std::vector<std::vector<VertexAttributeType>>& getFormat() const;
    void clearFormat();
    std::uint32_t addVertexComponent(const std::vector<VertexAttributeType>& componentLayout);
    std::uint32_t addVertexComponent(const int componentElements, const VertexAttributeType componentType);
    std::uint32_t getVertexSizeBytes() const;

private:
    const static std::uint8_t formatSizeLookup[VertexAttributeType::NUMTYPES];

    std::uint32_t sizeBytes = 0;
    std::vector<std::vector<VertexAttributeType>> format;
};

class Vertex {

public:
    Vertex(const VertexDescriptor& vertexDescription) 
        : vertexData(), maxDataSize(vertexDescription.getVertexSizeBytes())
    {}

    // we allow copying and assignment, but delete default constructor
    Vertex() = delete;    

    template<int L, typename T>
    bool addData(const pml::vec<L, T>& vec) {
        if (vertexData.size() + (L * sizeof(T)) > maxDataSize) return false;
        for (int i = 0; i < L; i++) {
            T data = vec[i];
            addData(data);
        }
        return true;
    }

    template<typename A, typename = std::enable_if_t<std::is_arithmetic<A>::value>>
    bool addData(const A& data) {
        if (vertexData.size() + sizeof(A) > maxDataSize) return false;
        std::uint8_t* casted = (std::uint8_t*)(&data);
        for (int i = 0; i < sizeof(A); i++) {
            vertexData.push_back(casted[i]);
        }
        return true;
    }

    const std::vector<std::uint8_t>& getData() const {
        return vertexData;
    }

private:
    std::vector<std::uint8_t> vertexData;
    std::size_t maxDataSize;

};

class VertexContainer {

public:
    VertexContainer(const VertexDescriptor& vertexDescription);
    
    void addVertex(const Vertex& v);

    template<int L, typename T>
    void addRawData(const pml::vec<L, T>& vec) {
        for (int i = 0; i < L; i++) {
            T data = vec[i];
            addRawData(data);
        }
    }

    template<typename A, typename = std::enable_if_t<std::is_arithmetic<A>::value>>
    void addRawData(const A& data) {
        if (dataIndex + sizeof(A) > verticesBytes.size()) {
            // allocate space for 1 vertex
            verticesBytes.insert(verticesBytes.end(), vertexDescription.getVertexSizeBytes(), 0u);
        }
        std::uint8_t* casted = (std::uint8_t*)(&data);
        for (int i = 0; i < sizeof(A); i++) {
            verticesBytes[dataIndex + i] = casted[i];
        }
        dataIndex += sizeof(A);
    }    

    const std::vector<std::uint8_t>& getBytes() const;
    std::vector<std::uint8_t> getBytesCopy() const;
    const void* getDataAddress() const;
    std::size_t getDataSize() const;
    std::size_t getNumVertices() const;
    std::size_t getVertexStride() const;
    const VertexDescriptor& getVertexDescription() const;

private:
    VertexDescriptor vertexDescription;
    std::vector<std::uint8_t> verticesBytes;
    int dataIndex = 0;

};

}

namespace std {

template<>
struct std::hash<prism::VertexDescriptor> {
    std::size_t operator()(const prism::VertexDescriptor& vertexDescription) const {
        auto& components = vertexDescription.getFormat();
        std::size_t seed = 0u;
        seed ^= prism::hash(vertexDescription.getVertexSizeBytes(), components.size());

        for (auto& component : components) {
            seed ^= prism::hash(component.size());
            for (prism::VertexAttributeType type : component) {
                seed ^= prism::hash(type);
            }
        }
        return seed;
    }
};

}