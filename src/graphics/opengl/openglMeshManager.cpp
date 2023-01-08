#include "graphics/opengl/openglMeshManager.h"

#include "graphics/opengl/openglVAO.h"
#include "graphics/opengl/openglVAOFactory.h"

namespace prism {

OpenglMeshManager::OpenglMeshManager() 
    : MeshManager()
{}

std::unique_ptr<Mesh> OpenglMeshManager::createUniqueMesh(
    const BaseVertexContainer& vertexContainer, 
    const std::vector<std::uint32_t>& indices) const 
{
    OpenglVAO* vao = OpenglVAOFactory::generateVAO(vertexContainer.getVertexDataAttributes());
    return std::make_unique<OpenGLMesh>(std::move(vertexContainer), indices, vao);
}

}