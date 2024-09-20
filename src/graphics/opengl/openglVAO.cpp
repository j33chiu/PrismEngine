#include "graphics/opengl/openglVAO.h"

namespace prism {

OpenglVAO::OpenglVAO() {
    glCreateVertexArrays(1, &ID);
    checkGLError("unable to create vao");
}

OpenglVAO::OpenglVAO(const VertexDescriptor& vertexDescription) {
    glCreateVertexArrays(1, &ID);
    checkGLError("unable to create vao");
    linkAttributeInfo(vertexDescription);
}

void OpenglVAO::linkAttributeInfo(const VertexDescriptor& vertexDescription) {
    // assumes all vectors in vertexAttr are equal in length
    unsigned int offset = 0u;
    auto& components = vertexDescription.getFormat();
    for (int i = 0; i < components.size(); i++) {
        auto& component = components[i];
        GLenum glType = getGLType(component[0]);

        glEnableVertexArrayAttrib(ID, i);
        checkGLError("could not enable vertex array attrib");
        glVertexArrayAttribBinding(ID, i, 0); // 0 or bindingIndex for bindingIndex
        checkGLError("unable to set vertex array attrib binding");
        glVertexArrayAttribFormat(ID, i, 
            component.size(),
            glType, 
            GL_FALSE,
            offset);
        checkGLError("unable to link vertex attribute info to vao");
        offset += sizeof(glType) * static_cast<unsigned int>(component.size());
    }
    this->vertexDescription = vertexDescription;
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

GLenum OpenglVAO::getGLType(VertexAttributeType type) const {
    switch(type) {
        case VertexAttributeType::FLOAT:
            return GL_FLOAT;
        case VertexAttributeType::INT8:
            return GL_BYTE;
        case VertexAttributeType::UINT8:
            return GL_UNSIGNED_BYTE;
        case VertexAttributeType::INT16:
            return GL_SHORT;
        case VertexAttributeType::UINT16:
            return GL_UNSIGNED_SHORT;
        case VertexAttributeType::INT32:
            return GL_INT;
        case VertexAttributeType::UINT32:
            return GL_UNSIGNED_INT;
        // not really supported....
        case VertexAttributeType::INT64:
        case VertexAttributeType::UINT64:
        case VertexAttributeType::UNKNOWN:
        default:
            return GL_DOUBLE;
    }
}

const VertexDescriptor& OpenglVAO::getVertexDescription() const {
    return vertexDescription;
}

}