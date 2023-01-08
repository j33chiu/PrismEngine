#include "graphics/opengl/openglShader.h"

#include "logger/Logger.h"

namespace {

void compileShaderErrors(GLuint shaderID, const char* shaderType) {
    GLint hasCompiled;
	char infoLog[1024];
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &hasCompiled);
    if (hasCompiled == GL_FALSE) {
        glGetShaderInfoLog(shaderID, 1024, NULL, infoLog);

        std::stringstream ss;
        ss << "SHADER_COMPILATION_ERROR for: " << shaderType << "\n" << std::endl;
        ss << infoLog << std::endl;
        prism::Logger::warn("OpenglShader::compileShaderErrors", ss.str());
    }
}

}


namespace prism {

OpenglShader::OpenglShader(const std::string &source, ShaderType type)
    : ID(0u)
{
    GLuint shaderType = (type == ShaderType::FRAGMENT) ? GL_FRAGMENT_SHADER : GL_VERTEX_SHADER;
    ID = glCreateShader(shaderType);
    checkGLError("unable to create shader");

    const char* sourceStr = source.data();

    glShaderSource(ID, 1, &sourceStr, nullptr);
    checkGLError("unable to set shader source code");
	glCompileShader(ID);
    checkGLError("unable to compile shader");
	compileShaderErrors(ID, (type == ShaderType::FRAGMENT) ? "FRAGMENT" : "VERTEX");
}

OpenglShader::~OpenglShader() {
    glDeleteShader(ID);
    checkGLError("unable to delete shader");
}

GLuint OpenglShader::getID() const {
    return ID;
}

}