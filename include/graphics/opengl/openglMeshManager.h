#pragma once

#include "graphics/MeshManager.h"

namespace prism {

// implementation of meshmanager specific to opengl
class OpenglMeshManager : public MeshManager {

public:

    OpenglMeshManager();
    ~OpenglMeshManager() override = default;

protected:
    std::unique_ptr<Mesh> createUniqueMesh(
        std::unique_ptr<VertexContainer> vertexContainer, 
        const std::vector<std::uint32_t>& indices) const override;

};

}