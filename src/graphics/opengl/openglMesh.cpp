#include "graphics/opengl/openglMesh.h"

#include "graphics/opengl/openglVAO.h"

namespace prism {


OpenGLMesh::OpenGLMesh(const BaseVertexContainer& vertices, const std::vector<std::uint32_t>& indices, OpenglVAO* vao) 
    : vbo(vertices.getVerticesAddress(), vertices.getDataSize())
    , Mesh(std::move(vertices), indices)
    , ebo(indices.data(), indices.size() * sizeof(std::uint32_t))
    , vao(vao)
{
    vao->addVBO(vbo.getID(), 0, static_cast<int>(this->vertices.getVertexStride()));
    vao->addEBO(ebo.getID());
}

void OpenGLMesh::updateVertices(const BaseVertexContainer& newVertices) {
    // overwrites from beginning of buffer
    vbo.write(newVertices.getVerticesAddress(), newVertices.getDataSize(), 0);
}

void OpenGLMesh::updateIndices(const std::vector<std::uint32_t>& newIndices) {
    ebo.writeVector(newIndices, 0);
}

void OpenGLMesh::changeVAO(OpenglVAO* newVAO) {
    newVAO->addVBO(vbo.getID(), 0, static_cast<int>(vertices.getVertexStride()));
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