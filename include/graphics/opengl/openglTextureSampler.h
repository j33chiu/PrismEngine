#pragma once

#include "graphics/TextureSampler.h"
#include "opengl.h"

namespace prism {

class OpenGLTextureSampler : public TextureSampler {

public:
    OpenGLTextureSampler(TextureSamplerAttributes samplerAttributes, std::uint32_t textureSamplerId);
    ~OpenGLTextureSampler() override;

    OpenGLTextureSampler(const OpenGLTextureSampler&) = delete;
    OpenGLTextureSampler &operator=(const OpenGLTextureSampler&) = delete;

    // opengl specific
    const static GLint wrapTable[4];

    GLuint getID() const;
    GLuint getTextureUnit() const;
    void setTextureUnit(GLuint unit);
    void bindTextureSampler();
    void unbindTextureSampler();

private:
    void deleteTextureSampler();

    GLuint ID;
    GLuint textureUnit = 0;
};

}