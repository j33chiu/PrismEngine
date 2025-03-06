#include "graphics/opengl/openglTexture.h"
#include "logger/Logger.h"

namespace prism {

OpenGLTexture::OpenGLTexture(std::uint32_t textureId,
    TextureUse textureUse, 
    const std::vector<std::byte>& bytes, 
    std::uint32_t width, 
    std::uint32_t height,
    std::uint8_t channels,
    const TextureSampler* textureSampler) 
    : Texture(textureId, textureUse, bytes, width, height, channels, textureSampler)
{
    // get number of texture units available
    glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &totalNumTextureUnits);

    // set current texture's texture unit
    textureUnit = getNextAvailableUnit();
    
    TextureSamplerAttributes attr = textureSampler->getSamplerAttributes();
    
    glCreateTextures(GL_TEXTURE_2D, 1, &ID);
    prism::checkGLError("unable to create texture");

    // allocate storage for texture
    // TODO: modify the enum for different texture data representations
    GLenum dataFormat = GL_RGBA8;       // default for 4 channels
    GLenum pixelDataFormat = GL_RGBA;   // default for 4 channels
    if (channels == 3) {
        dataFormat = GL_RGB8;
        pixelDataFormat = GL_RGB;
    } else if (channels == 2) {
        dataFormat = GL_RG8;
        pixelDataFormat = GL_RG;
    } else if (channels == 1) {
        dataFormat = GL_R8;
        pixelDataFormat = GL_R;
    }

    int mipMapLevels = 1;
    if (attr.mipmaps) {
        mipMapLevels = floor(log2(max(width, height))) + 1;
    }

    glTextureStorage2D(ID, mipMapLevels, dataFormat, width, height);
    prism::checkGLError("unable to allocate memory for texture");
    const std::byte* rawData = bytes.data();
    const unsigned char* conv = reinterpret_cast<const unsigned char*>(rawData);
    glTextureSubImage2D(ID, 0, 0, 0, width, height, pixelDataFormat, GL_UNSIGNED_BYTE, conv);
    prism::checkGLError("unable to upload texture data to memory");

    // generate mipmaps
    if (attr.mipmaps) {
        glGenerateTextureMipmap(ID);
        prism::checkGLError("unable generate mipmaps for texture");
    }

    // fallback sampling settings if sampler is not bound
    // wrap
    glTextureParameteri(ID, GL_TEXTURE_WRAP_S, OpenGLTextureSampler::wrapTable[attr.sWrapMode]);
    prism::checkGLError("unable to set wrap mode (s) for texture");
    glTextureParameteri(ID, GL_TEXTURE_WRAP_T, OpenGLTextureSampler::wrapTable[attr.tWrapMode]);
    prism::checkGLError("unable to set wrap mode (t) for texture");
    glTextureParameteri(ID, GL_TEXTURE_WRAP_R, OpenGLTextureSampler::wrapTable[attr.rWrapMode]);
    prism::checkGLError("unable to set wrap mode (r) for texture");

    // border colour
    glTextureParameterfv(ID, GL_TEXTURE_BORDER_COLOR, reinterpret_cast<const float *>(&attr.borderColour));
    prism::checkGLError("unable to set texture border colour");

    // min filter
    if (attr.mipmaps) {
        if (attr.mipmapFilter == TextureSamplerFilter::NEAREST) {
            if (attr.minFilter == TextureSamplerFilter::NEAREST) {
                glTextureParameteri(ID, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
            } else {
                glTextureParameteri(ID, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
            }
        } else {
            if (attr.minFilter == TextureSamplerFilter::NEAREST) {
                glTextureParameteri(ID, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
            } else {
                glTextureParameteri(ID, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            }
        }
    } else {
        switch (attr.minFilter) {
            case TextureSamplerFilter::NEAREST:
                glTextureParameteri(ID, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
                break;
            case TextureSamplerFilter::LINEAR:
            default:
                glTextureParameteri(ID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                break;
        }
    }
    prism::checkGLError("unable to set min filter for texture");

    // mag filter
    switch (attr.magFilter) {
        case TextureSamplerFilter::NEAREST:
            glTextureParameteri(ID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            break;
        case TextureSamplerFilter::LINEAR:
        default:
            glTextureParameteri(ID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            break;
    }
    prism::checkGLError("unable to set mag filter for texture");

    // anisotropic filtering
    float targetAniso = attr.anisotropicFilter;
    GLfloat maxAniso = 1.0f;
    glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &maxAniso);
    glTextureParameterf(ID, GL_TEXTURE_MAX_ANISOTROPY_EXT, min(targetAniso, maxAniso));
}

GLuint OpenGLTexture::getID() const {
    return ID;
}

GLuint OpenGLTexture::getTextureUnit() const {
    return textureUnit;
}

void OpenGLTexture::setTextureUnit(GLuint unit) {
    textureUnit = unit;
}

void OpenGLTexture::bindTexture() {
    glBindTextureUnit(textureUnit, ID);
}

void OpenGLTexture::unbindTexture() {
    glBindTextureUnit(textureUnit, 0);
}

void OpenGLTexture::deleteTexture() {
    unbindTexture();
    glDeleteTextures(1, &ID);
}

GLuint OpenGLTexture::getNextAvailableUnit() {
    static GLuint unit = 0;
    GLuint out = unit;
    unit = (unit + 1) % totalNumTextureUnits;
    return out;
}

OpenGLTexture::~OpenGLTexture() {
    deleteTexture();
}

}