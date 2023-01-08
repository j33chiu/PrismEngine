#include "graphics/opengl/opengl.h"

#include "logger/Logger.h"

namespace prism {

void checkGLError() {
    auto err = glGetError();
    if (err == GL_NO_ERROR) return;

    Logger::warn("GL Error: " + err);
}

void checkGLError(std::string baseErrMsg) {
    auto err = glGetError();
    if (err == GL_NO_ERROR) return;

    std::stringstream ss;
    ss << baseErrMsg << ": " << err;
    Logger::warn(ss.str());
}
    
}