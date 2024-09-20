#include "graphics/Vertex.h"

namespace prism {

const std::uint8_t VertexDescriptor::formatSizeLookup[] = {
    sizeof(pml::FLOAT),
    sizeof(pml::DOUBLE),
    sizeof(pml::INT8),
    sizeof(pml::UINT8),
    sizeof(pml::INT16),
    sizeof(pml::UINT16),
    sizeof(pml::INT32),
    sizeof(pml::UINT32),
    sizeof(pml::INT64),
    sizeof(pml::UINT64),
    0
};

VertexDescriptor::VertexDescriptor()
    : sizeBytes(0), format()
{}

VertexDescriptor::VertexDescriptor(std::vector<std::vector<VertexAttributeType>>& format) 
    : format(format)
{
    for (auto component : format) {
        for (auto vertexType : component) {
            sizeBytes += formatSizeLookup[vertexType];
        }
    }
}

const std::vector<std::vector<VertexAttributeType>>& VertexDescriptor::getFormat() const {
    return format;
}

void VertexDescriptor::clearFormat() {
    format.clear();
    sizeBytes = 0;
}

std::uint32_t VertexDescriptor::addVertexComponent(const std::vector<VertexAttributeType>& componentLayout) {
    format.emplace_back(componentLayout);
    for (auto componentType : componentLayout) {
        sizeBytes += formatSizeLookup[componentType];
    }
    return sizeBytes;
}

std::uint32_t VertexDescriptor::addVertexComponent(const int componentElements, const VertexAttributeType componentType) {
    std::vector<VertexAttributeType> componentLayout;
    for (int i = 0; i < componentElements; i++) {
        componentLayout.emplace_back(componentType);
        sizeBytes += formatSizeLookup[componentType];
    }
    format.emplace_back(componentLayout);
    return sizeBytes;
}

std::uint32_t VertexDescriptor::getVertexSizeBytes() const {
    return sizeBytes;
}

VertexContainer::VertexContainer(const VertexDescriptor& vertexDescription) 
    : vertexDescription(vertexDescription)
{}

void VertexContainer::addVertex(const Vertex& v) {
    // allocate space for 1 vertex, vertex stride (bytes) is vertexDescription.getVertexSizeBytes()
    verticesBytes.insert(verticesBytes.end(), vertexDescription.getVertexSizeBytes(), 0u);
    // copy from v into newly allocated space
    const std::vector<std::uint8_t>& vertexData = v.getData();
    for (int i = 0; i < vertexData.size(); i++) {
        verticesBytes[dataIndex + i] = vertexData[i];
    }
    dataIndex = verticesBytes.size();
}

const std::vector<std::uint8_t>& VertexContainer::getBytes() const {
    return verticesBytes;
}

std::vector<std::uint8_t> VertexContainer::getBytesCopy() const {
    return verticesBytes;
}

const void* VertexContainer::getDataAddress() const {
    return verticesBytes.data();
}

std::size_t VertexContainer::getDataSize() const {
    return verticesBytes.size();
}

std::size_t VertexContainer::getNumVertices() const {
    return verticesBytes.size() / vertexDescription.getVertexSizeBytes();
}

std::size_t VertexContainer::getVertexStride() const {
    return vertexDescription.getVertexSizeBytes();
}

const VertexDescriptor& VertexContainer::getVertexDescription() const {
    return vertexDescription;
}

}