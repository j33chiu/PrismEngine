#pragma once

#include <unordered_map>
#include <memory>

#include "core/math/pml.h"
#include "graphics/Mesh.h"
#include "graphics/Vertex.h"

namespace prism {

/**
 * manages and stores all meshes created
 * provides ability to load meshes from files, create from vertices/indices
 * some default meshes too (quads, triangles, cubes) (only position and colour attributes)
*/
class MeshManager {

public:

    MeshManager();
    virtual ~MeshManager() = default;

    const Mesh* generateQuad(
        const pml::vec4& colour,
        const pml::vec3& topLeft,
        const pml::vec3& topRight,
        const pml::vec3& bottomRight,
        const pml::vec3& bottomLeft);

    const Mesh* generateTriangle(
        const pml::vec4& colour,
        const pml::vec3& a,
        const pml::vec3& b,
        const pml::vec3& c);

    const Mesh* generateCube(
        const pml::vec4& colour,
        const pml::FLOAT dimension);

    const Mesh* createMesh(
        const BaseVertexContainer& vertexContainer, 
        const std::vector<std::uint32_t>& indices);

protected:

    virtual std::unique_ptr<Mesh> createUniqueMesh(
        const BaseVertexContainer& vertexContainer, 
        const std::vector<std::uint32_t>& indices) const = 0;

private:
    // stored meshes
    struct StoredMesh {
        std::size_t meshId;
        std::unique_ptr<Mesh> mesh;
    };

    std::unordered_map<std::size_t, StoredMesh> loadedMeshes;


};

}