#pragma once

#include "graphics/Texture.h"

#include "graphics/opengl/openglTextureSampler.h"
#include "graphics/opengl/opengl.h"

namespace prism {

class OpenGLTexture : public Texture {

public:
    OpenGLTexture(std::uint32_t textureId,
        TextureUse textureUse, 
        const std::vector<std::byte>& bytes, 
        std::uint32_t width, 
        std::uint32_t height,
        std::uint8_t channels,
        const TextureSampler* textureSampler);
    ~OpenGLTexture() override;

    // remove assignment and copy constructor
    OpenGLTexture(const OpenGLTexture&) = delete;
    OpenGLTexture &operator=(const OpenGLTexture&) = delete;

    // opengl specific
    GLuint getID() const;
    GLuint getTextureUnit() const;
    void setTextureUnit(GLuint unit);
    void bindTexture();
    void unbindTexture();

private:
    void deleteTexture();

    GLuint ID;  // opengl ID to the texture, different from the textureId, which is used by prism to manage textures and samples
    GLuint textureUnit;
    GLint totalNumTextureUnits;
    GLuint getNextAvailableUnit();
};

}