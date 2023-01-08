#include "graphics/opengl/openglMaterial.h"

#include "graphics/opengl/openglShader.h"
#include "graphics/ShaderType.h"
#include "logger/Logger.h"

namespace {

void compileShaderProgramErrors(GLuint programID) {
    GLint hasCompiled;
	char infoLog[1024];
	glGetProgramiv(programID, GL_LINK_STATUS, &hasCompiled);
    prism::checkGLError("unable to check gl shader program compile status");
    if (hasCompiled == GL_FALSE) {
        glGetProgramInfoLog(programID, 1024, nullptr, infoLog);
        prism::checkGLError("unable to get gl shader program info log");
        prism::Logger::warn("OpenglMaterial::compileShaderProgramErrors", "SHADER_LINKING_ERROR for: PROGRAM\n");
    }
}

}

namespace prism {

OpenglMaterial::OpenglMaterial(const std::string &vertexSource, const std::string &fragmentSource) {
    OpenglShader vertexShader(vertexSource, ShaderType::VERTEX);
    OpenglShader fragmentShader(fragmentSource, ShaderType::FRAGMENT);

    ID = glCreateProgram();
    checkGLError("unable to create gl shader program");
    glAttachShader(ID, vertexShader.getID());
    checkGLError("unable to attach gl vertex shader to program");
    glAttachShader(ID, fragmentShader.getID());
    checkGLError("unable to attach gl fragment shader to program");
    glLinkProgram(ID);
    checkGLError("unable to link gl shader program");

    compileShaderProgramErrors(ID);
}

OpenglMaterial::~OpenglMaterial() {
    glDeleteProgram(ID);
    checkGLError("unable to delete gl shader program");
}

void OpenglMaterial::bind() const {
    glUseProgram(ID);
    checkGLError("unable to bind gl shader program");
}

GLuint OpenglMaterial::getID() const {
    return ID;
}

}