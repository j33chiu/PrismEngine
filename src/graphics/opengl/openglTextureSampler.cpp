#include "graphics/opengl/openglTextureSampler.h"

#include "logger/Logger.h"

namespace prism {

const GLint OpenGLTextureSampler::wrapTable[4] = {
    GL_REPEAT, GL_MIRRORED_REPEAT, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_BORDER
};  

OpenGLTextureSampler::OpenGLTextureSampler(TextureSamplerAttributes samplerAttributes, 
                                           std::uint32_t textureSamplerId) 
    : TextureSampler(samplerAttributes, textureSamplerId)
{
    glCreateSamplers(1, &ID);
    prism::checkGLError("unable to create texture sampler");

    // wrap
    glSamplerParameteri(ID, GL_TEXTURE_WRAP_S, OpenGLTextureSampler::wrapTable[samplerAttributes.sWrapMode]);
    prism::checkGLError("unable to set wrap mode (s) for texture sampler");
    glSamplerParameteri(ID, GL_TEXTURE_WRAP_T, OpenGLTextureSampler::wrapTable[samplerAttributes.tWrapMode]);
    prism::checkGLError("unable to set wrap mode (t) for texture sampler");
    glSamplerParameteri(ID, GL_TEXTURE_WRAP_R, OpenGLTextureSampler::wrapTable[samplerAttributes.rWrapMode]);
    prism::checkGLError("unable to set wrap mode (r) for texture sampler");

    // border colour
    glSamplerParameterfv(ID, GL_TEXTURE_BORDER_COLOR, reinterpret_cast<const float *>(&samplerAttributes.borderColour));
    prism::checkGLError("unable to set texture sampler border colour");

    // min filter
    if (samplerAttributes.mipmaps) {
        if (samplerAttributes.mipmapFilter == TextureSamplerFilter::NEAREST) {
            if (samplerAttributes.minFilter == TextureSamplerFilter::NEAREST) {
                glSamplerParameteri(ID, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
            } else {
                glSamplerParameteri(ID, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
            }
        } else {
            if (samplerAttributes.minFilter == TextureSamplerFilter::NEAREST) {
                glSamplerParameteri(ID, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
            } else {
                glSamplerParameteri(ID, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            }
        }
    } else {
        switch (samplerAttributes.minFilter) {
            case TextureSamplerFilter::NEAREST:
                glSamplerParameteri(ID, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
                break;
            case TextureSamplerFilter::LINEAR:
            default:
                glSamplerParameteri(ID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                break;
        }
    }
    prism::checkGLError("unable to set min filter for texture sampler");

    // mag filter
    switch (samplerAttributes.magFilter) {
        case TextureSamplerFilter::NEAREST:
            glSamplerParameteri(ID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            break;
        case TextureSamplerFilter::LINEAR:
        default:
            glSamplerParameteri(ID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            break;
    }
    prism::checkGLError("unable to set mag filter for texture sampler");

    // anisotropic filtering
    float targetAniso = samplerAttributes.anisotropicFilter;
    GLfloat maxAniso = 1.0f;
    glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &maxAniso);
    glSamplerParameterf(ID, GL_TEXTURE_MAX_ANISOTROPY_EXT, min(targetAniso, maxAniso));
    
}

GLuint OpenGLTextureSampler::getID() const {
    return ID;
}

GLuint OpenGLTextureSampler::getTextureUnit() const {
    return textureUnit;
}

void OpenGLTextureSampler::setTextureUnit(GLuint unit) {
    textureUnit = unit;
}

void OpenGLTextureSampler::bindTextureSampler() {
    if (textureUnit != 0) {
        glBindSampler(textureUnit, ID);
        prism::checkGLError("unable to bind texture sampler");
    } else {
        Logger::error("OpenGLTextureSampler::bindTextureSampler()", "texture unit has not been set yet for texture sampler");
    }
}

void OpenGLTextureSampler::unbindTextureSampler() {
    if (textureUnit != 0) {
        glBindSampler(textureUnit, 0);
        prism::checkGLError("unable to unbind texture sampler");
    } else {
        Logger::error("OpenGLTextureSampler::unbindTextureSampler()", "texture unit has not been set yet for texture sampler");
    }
}

void OpenGLTextureSampler::deleteTextureSampler() {
    glDeleteSamplers(1, &ID);
}

OpenGLTextureSampler::~OpenGLTextureSampler() {
    deleteTextureSampler();
}

}
