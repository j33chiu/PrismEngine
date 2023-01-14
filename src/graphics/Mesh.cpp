#include "graphics/Mesh.h"

namespace prism {

Mesh::Mesh(std::unique_ptr<VertexContainer> vertexContainer, const std::vector<std::uint32_t>& indices)
    : vertexContainer(std::move(vertexContainer)), indices(indices)
{}

const VertexContainer* Mesh::getVertices() const {
    return vertexContainer.get();
}

const std::vector<std::uint32_t> &Mesh::getIndices() const {
    return indices;
}

}