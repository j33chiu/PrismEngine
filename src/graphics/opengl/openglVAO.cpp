#include "graphics/opengl/openglVAO.h"

namespace prism {

OpenglVAO::OpenglVAO() {
    glCreateVertexArrays(1, &ID);
    checkGLError("unable to create vao");
}

OpenglVAO::OpenglVAO(VertexDataAttributes vertexAttr) {
    glCreateVertexArrays(1, &ID);
    checkGLError("unable to create vao");
    linkAttributeInfo(vertexAttr);
}

void OpenglVAO::linkAttributeInfo(VertexDataAttributes vertexAttr) {
    // assumes all vectors in vertexAttr are equal in length
    unsigned int offset = 0u;
    for (int i = 0; i < vertexAttr.attributes.size(); i++) {
        GLenum glType = getGLType(vertexAttr.componentTypes[i]);

        glEnableVertexArrayAttrib(ID, i);
        checkGLError("could not enable vertex array attrib");
        glVertexArrayAttribBinding(ID, i, 0); // 0 or bindingIndex for bindingIndex
        checkGLError("unable to set vertex array attrib binding");
        glVertexArrayAttribFormat(ID, i, 
            vertexAttr.componentLengths[i],
            glType, 
            GL_FALSE,
            offset);
        checkGLError("unable to link vertex attribute info to vao");
        offset += sizeof(glType) * static_cast<unsigned int>(vertexAttr.componentLengths[i]);
    }
    this->vertexAttr = vertexAttr;
}

OpenglVAO::~OpenglVAO() {
    glDeleteVertexArrays(1, &ID);
    checkGLError("unable to delete vao");
}

void OpenglVAO::addVBO(GLuint vbo, GLuint bindingIndex, GLsizei vertexStride) {
    glVertexArrayVertexBuffer(ID, bindingIndex, vbo, 0, vertexStride);
    checkGLError("unable to add vbo to vao");
    numVBO++;
}

void OpenglVAO::addEBO(GLuint ebo) {
    glVertexArrayElementBuffer(ID, ebo);
    checkGLError("unable to add ebo to vao");
    numEBO++;
}

void OpenglVAO::bind() const {
    glBindVertexArray(ID);
    checkGLError("unable to bind vao");
}

void OpenglVAO::unbind() const {
    glBindVertexArray(0u);
    checkGLError("unable to unbind vao");
}

GLenum OpenglVAO::getGLType(VertexAttrDataType type) const {
    switch(type) {
        case VertexAttrDataType::FLOAT:
            return GL_FLOAT;
        case VertexAttrDataType::INT8:
            return GL_BYTE;
        case VertexAttrDataType::UINT8:
            return GL_UNSIGNED_BYTE;
        case VertexAttrDataType::INT16:
            return GL_SHORT;
        case VertexAttrDataType::UINT16:
            return GL_UNSIGNED_SHORT;
        case VertexAttrDataType::INT32:
            return GL_INT;
        case VertexAttrDataType::UINT32:
            return GL_UNSIGNED_INT;
        // not really supported....
        case VertexAttrDataType::INT64:
        case VertexAttrDataType::UINT64:
        case VertexAttrDataType::UNKNOWN:
        default:
            return GL_DOUBLE;
    }
}

VertexDataAttributes OpenglVAO::getVertexAttr() const {
    return vertexAttr;
}

}