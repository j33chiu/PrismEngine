#include "graphics/opengl/openglMeshManager.h"

#include "graphics/opengl/openglVAO.h"
#include "graphics/opengl/openglVAOFactory.h"

namespace prism {

OpenglMeshManager::OpenglMeshManager() 
    : MeshManager()
{}

std::unique_ptr<Mesh> OpenglMeshManager::createUniqueMesh(
    std::unique_ptr<VertexContainer> vertexContainer, 
    const std::vector<std::uint32_t>& indices) const 
{
    OpenglVAO* vao = OpenglVAOFactory::generateVAO(vertexContainer->getVertexAttr());
    return std::make_unique<OpenGLMesh>(std::move(vertexContainer), indices, vao);
}

}