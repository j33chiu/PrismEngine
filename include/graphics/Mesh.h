#pragma once

#include <cstdint>
#include <vector>

#include "Vertex.h"

namespace prism {

class Mesh {

public:
    Mesh(const BaseVertexContainer& vertices, const std::vector<std::uint32_t>& indices);

    virtual ~Mesh() = default;

    virtual void updateVertices(const BaseVertexContainer& newVertices) = 0;

    virtual void updateIndices(const std::vector<std::uint32_t>& newIndices) = 0;

    const BaseVertexContainer& getVertices() const;

    const std::vector<std::uint32_t> &getIndices() const;

protected:
    const BaseVertexContainer& vertices;
    std::vector<std::uint32_t> indices;

};

}