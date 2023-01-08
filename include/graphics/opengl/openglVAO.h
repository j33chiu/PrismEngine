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

    OpenglVAO(VertexDataAttributes vertexAttr);

    ~OpenglVAO();

    void linkAttributeInfo(VertexDataAttributes vertexAttr);

    void addVBO(GLuint vbo, GLuint bindingIndex, GLsizei vertexStride);

    void addEBO(GLuint ebo);

    void bind() const;

    void unbind() const;

    VertexDataAttributes getVertexAttr() const;

private:
    GLenum getGLType(VertexAttrDataType type) const;

    GLuint ID;

    VertexDataAttributes vertexAttr;
    unsigned int numVBO = 0;
    unsigned int numEBO = 0;

};

}