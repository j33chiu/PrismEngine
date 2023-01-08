#include "graphics/Mesh.h"

namespace prism {

Mesh::Mesh(const BaseVertexContainer& vertices, const std::vector<std::uint32_t>& indices)
    : vertices(vertices), indices(indices)
{}

const BaseVertexContainer& Mesh::getVertices() const {
    return vertices;
}

const std::vector<std::uint32_t> &Mesh::getIndices() const {
    return indices;
}

}