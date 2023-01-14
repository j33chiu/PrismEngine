#include "graphics/opengl/openglMesh.h"

#include "graphics/opengl/openglVAO.h"

namespace prism {


OpenGLMesh::OpenGLMesh(std::unique_ptr<VertexContainer> vertexContainer, const std::vector<std::uint32_t>& indices, OpenglVAO* vao) 
    : Mesh(std::move(vertexContainer), indices)
    , vbo(this->vertexContainer->getVerticesAddress(), this->vertexContainer->getDataSize())
    , ebo(indices.data(), indices.size() * sizeof(std::uint32_t))
    , vao(vao)
{
    vao->addVBO(vbo.getID(), 0, static_cast<int>(this->vertexContainer->getVertexStride()));
    vao->addEBO(ebo.getID());
}

void OpenGLMesh::updateVertices(std::unique_ptr<VertexContainer> newVertexContainer) {
    // overwrites from beginning of buffer
    vbo.write(newVertexContainer->getVerticesAddress(), newVertexContainer->getDataSize(), 0);
    this->vertexContainer = std::move(newVertexContainer);
}

void OpenGLMesh::updateIndices(const std::vector<std::uint32_t>& newIndices) {
    ebo.writeVector(newIndices, 0);
}

void OpenGLMesh::changeVAO(OpenglVAO* newVAO) {
    newVAO->addVBO(vbo.getID(), 0, static_cast<int>(vertexContainer->getVertexStride()));
    newVAO->addEBO(ebo.getID());
    vao = newVAO;
}

OpenglVAO* OpenGLMesh::getVAO() const {
    return vao;
}

GLuint OpenGLMesh::getVBOId() const {
    return vbo.getID();
}

GLuint OpenGLMesh::getEBOId() const {
    return ebo.getID();
}

}