#pragma once

#include <vector>
#include <unordered_map>

#include "graphics/opengl/opengl.h"
#include "graphics/opengl/openglBuffers.h"
#include "graphics/Vertex.h"

namespace prism {

class OpenglVAO {

public:

    OpenglVAO();

    OpenglVAO(const VertexDescriptor& vertexDescription);

    ~OpenglVAO();

    void linkAttributeInfo(const VertexDescriptor& vertexDescription);

    void addVBO(GLuint vbo, GLuint bindingIndex, GLsizei vertexStride);

    void addEBO(GLuint ebo);

    void bind() const;

    void unbind() const;

    const VertexDescriptor& getVertexDescription() const;

private:
    GLenum getGLType(VertexAttributeType type) const;

    GLuint ID;

    VertexDescriptor vertexDescription;
    unsigned int numVBO = 0;
    unsigned int numEBO = 0;

};

}