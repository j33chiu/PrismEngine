#pragma once

#include <vector>

#include "logger/Logger.h"
#include "graphics/opengl/opengl.h"
#include "graphics/Vertex.h"

namespace prism {

enum class GLBufferType {
    VERTEX,             // VBO
    ELEMENT_ARRAY,      // EBO
    UNIFORM,            // UBO
    SHADER_STORAGE      // SSBO
};

template<GLBufferType B, bool FixedCapacity>
class OpenGLBuffer {

public:
    OpenGLBuffer(std::size_t bufferCapacity)
        : ID{}, bufferCapacity(bufferCapacity), bufferOffset(0u)
    {
        glCreateBuffers(1, &ID);
        checkGLError("unable to create new buffer");
        glNamedBufferData(ID, bufferCapacity, nullptr, GL_DYNAMIC_DRAW);
        checkGLError("unable to allocate capacity to new buffer");
        switch(B) {
            case GLBufferType::UNIFORM:
            case GLBufferType::SHADER_STORAGE:
                Logger::warn("OpenGLBuffer::OpenGLBuffer", "UBOs and SSBOs should have a binding index...");
                break;
            default:
                break;
        }
    }

    // specifically for ubo and ssbo, which have a binding index
    OpenGLBuffer(std::size_t bufferCapacity, GLuint bindingIndex)
        : ID{}, bufferCapacity(bufferCapacity), bufferOffset(0u)
    {
        glCreateBuffers(1, &ID);
        checkGLError("unable to create new buffer");
        glNamedBufferData(ID, bufferCapacity, nullptr, GL_DYNAMIC_DRAW);
        checkGLError("unable to allocate capacity to new buffer");
        GLenum bufferTarget;
        switch(B) {
            default:
            case GLBufferType::VERTEX: 
                bufferTarget = GL_ARRAY_BUFFER;
                break;
            case GLBufferType::ELEMENT_ARRAY: 
                bufferTarget = GL_ELEMENT_ARRAY_BUFFER;
                break;
            case GLBufferType::UNIFORM: 
                bufferTarget = GL_UNIFORM_BUFFER;
                break;
            case GLBufferType::SHADER_STORAGE: 
                bufferTarget = GL_SHADER_STORAGE_BUFFER;
                break;
        }
        glBindBufferRange(bufferTarget, bindingIndex, ID, 0, bufferCapacity);
        checkGLError("unable to set buffer binding index");
    }

    template<class T>
    OpenGLBuffer(const T *object, std::size_t bufferCapacity)
        : ID{}, bufferCapacity(bufferCapacity), bufferOffset(0u)
    {
        glCreateBuffers(1, &ID);
        checkGLError("unable to create new buffer");
        glNamedBufferData(ID, bufferCapacity, object, GL_DYNAMIC_DRAW);
        checkGLError("unable to write to new buffer");
        bufferOffset += bufferCapacity;
    }

    template<class T>
    OpenGLBuffer(const T &object) 
        : ID{}, bufferOffset(0u)
    {
        bufferCapacity = sizeof(T);
        glCreateBuffers(1, &ID);
        checkGLError("unable to create new buffer");
        glNamedBufferData(ID, bufferCapacity, std::addressof(object), GL_DYNAMIC_DRAW);
        checkGLError("unable to write to new buffer");

        bufferOffset += bufferCapacity;
    }

    ~OpenGLBuffer() {
        glDeleteBuffers(1, &ID);
    }

    GLuint getID() const {
        return ID;
    }

    std::size_t getBufferCapacity() const {
        return bufferCapacity;
    }

    std::size_t getBufferOffset() const {
        return bufferOffset;
    }

    void setBufferOffset(std::size_t bufferOffset) {
        this->bufferOffset = bufferOffset;
    }

    void advanceBufferOffset(std::size_t advance) {
        this->bufferOffset += advance;
    }

    template<class U>
    void writeVector(const std::vector<U> &objects) {
        write(objects.data(), sizeof(U) * objects.size(), bufferOffset);
    }

    template<class U>
    void writeVector(const std::vector<U> &objects, std::size_t offset) {
        write(objects.data(), sizeof(U) * objects.size(), offset);
    }

    template<class U, std::size_t N>
    void writeArray(const std::array<U, N> &objects) {
        write(objects.data(), sizeof(U) * N, bufferOffset);
    }

    template<class U, std::size_t N>
    void writeArray(const std::array<U, N> &objects, std::size_t offset) {
        write(objects.data(), sizeof(U) * N, offset);
    }

    template<class T>
    void write(const T &object) {
        write(std::addressof(object), sizeof(T), bufferOffset);
    }

    template<class T>
    void write(const T &object, std::size_t offset) {
        write(std::addressof(object), sizeof(T), offset);
    }

    template<class T>
    void write(const T *object, std::size_t size) {
        write(object, size, bufferOffset);
    }

    template<class T>
    void write(const T *object, std::size_t size, std::size_t offset) {
        if (offset + size > bufferCapacity) {
            if constexpr (false) {
                throw Exception("Attempting to write to buffer with insufficient capacity.");
            } 
            // create new buffer with increased capacity
            std::size_t newCapacity = max(offset + size, bufferCapacity * 3u);

            // create new buffer
            GLuint newID{};
            glCreateBuffers(1, &newID);
            checkGLError("unable to create new, larger buffer for write data");
            glNamedBufferData(newID, newCapacity, nullptr, GL_DYNAMIC_DRAW);
            checkGLError("unable to allocate larger capacity to buffer");

            // copy old buffer data into new buffer
            glCopyNamedBufferSubData(ID, newID, 0, 0, bufferCapacity);
            checkGLError("unable to copy data to new, larger buffer");

            // delete old buffer
            glDeleteBuffers(1, &ID);
            checkGLError("unable to delete old buffer");

            // update id and capacity
            ID = newID;
            bufferCapacity = newCapacity;
        }

        // write data
        glNamedBufferSubData(ID, offset, size, object);
        checkGLError("unable to write to gl buffer");
        bufferOffset = offset + size;
    }

private:
    // name/handle/id of buffer
    GLuint ID;
    // capacity of the buffer
    std::size_t bufferCapacity;
    // current offset for an undefined write of data
    std::size_t bufferOffset;
    
};

// define specific buffer types
using VBO = OpenGLBuffer<GLBufferType::VERTEX, false>;
using EBO = OpenGLBuffer<GLBufferType::ELEMENT_ARRAY, false>;
using UBO = OpenGLBuffer<GLBufferType::UNIFORM, false>;
using SSBO = OpenGLBuffer<GLBufferType::SHADER_STORAGE, false>;

}