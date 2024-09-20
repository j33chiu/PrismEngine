#include "graphics/opengl/opengl.h"

#include "logger/Logger.h"

namespace {

std::unordered_map<std::string, bool> glFunctionSupported;

}

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

void setGLFunctionSupported(std::string function, bool isSupported) {
    glFunctionSupported[function] = isSupported;
}

bool checkGLFunctionSupported(std::string function) {
    auto it = glFunctionSupported.find(function);
    if (it == glFunctionSupported.end()) return false;
    return it->second;
}
    
}