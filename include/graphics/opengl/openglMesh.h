#pragma once

#include <vector>
#include <memory> 

#include "graphics/opengl/openglVAO.h"
#include "graphics/opengl/openglBuffers.h"
#include "graphics/Vertex.h"
#include "graphics/Mesh.h"

namespace prism {

class OpenGLMesh : public Mesh {

public:
    OpenGLMesh(std::unique_ptr<VertexContainer> vertexContainer, const::std::vector<std::uint32_t>& indices, OpenglVAO* vao);

    void updateVertices(std::unique_ptr<VertexContainer> newVertexContainer) override;

    void updateIndices(const std::vector<std::uint32_t>& newIndices) override;

    void changeVAO(OpenglVAO* newVAO);

    OpenglVAO* getVAO() const;

    GLuint getVBOId() const;
    
    GLuint getEBOId() const;

private:
    OpenglVAO* vao = nullptr;
    VBO vbo;
    EBO ebo;


};

}