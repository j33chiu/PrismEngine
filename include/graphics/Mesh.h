#pragma once

#include <cstdint>
#include <vector>
#include <memory>

#include "Vertex.h"

namespace prism {

class Mesh {

public:
    Mesh(std::unique_ptr<VertexContainer> vertexContainer, const std::vector<std::uint32_t>& indices);

    virtual ~Mesh() = default;

    virtual void updateVertices(std::unique_ptr<VertexContainer> newVertexContainer) = 0;

    virtual void updateIndices(const std::vector<std::uint32_t>& newIndices) = 0;

    const VertexContainer* getVertices() const;

    const std::vector<std::uint32_t> &getIndices() const;

protected:
    std::unique_ptr<VertexContainer> vertexContainer;
    std::vector<std::uint32_t> indices;

};

}