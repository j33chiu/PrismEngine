#pragma once

#include "graphics/opengl/opengl.h"
#include "graphics/ShaderType.h"

namespace prism {

class OpenglShader {

public:

    OpenglShader(const std::string &source, ShaderType type);
    ~OpenglShader();

    // delete move, copy constructor and assignment
    OpenglShader(OpenglShader &&other) = delete;
    OpenglShader &operator=(OpenglShader &&) = delete;
    OpenglShader(const OpenglShader &) = delete;
    OpenglShader &operator=(const OpenglShader &) = delete;

    GLuint getID() const;

private:
    GLuint ID;

};

}