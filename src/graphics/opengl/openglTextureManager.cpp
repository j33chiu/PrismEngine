#include "graphics/opengl/openglTextureManager.h"
#include "graphics/opengl/openglTexture.h"

namespace prism {

OpenGLTextureManager::OpenGLTextureManager() 
    : TextureManager()
{
    bindlessTexturesEnabled = checkGLFunctionSupported("glGetTextureSamplerHandleARB");
}

bool OpenGLTextureManager::arebindlessTexturesEnabled() const {
    return bindlessTexturesEnabled;
}

std::unique_ptr<Texture> OpenGLTextureManager::createUniqueTexture(TextureUse textureUsage, 
                                                                   const std::vector<std::byte>& bytes, 
                                                                   std::uint32_t width, 
                                                                   std::uint32_t height,
                                                                   std::uint8_t channels,
                                                                   const TextureSampler* textureSampler,
                                                                   std::uint32_t textureId) 
{
    std::unique_ptr<OpenGLTexture> texture = std::make_unique<OpenGLTexture>(textureId, textureUsage, bytes, width, height, channels, textureSampler);
    return std::move(texture);
}

std::unique_ptr<TextureSampler> OpenGLTextureManager::createUniqueSampler(const TextureSamplerAttributes& samplerAttributes,
                                                                          std::uint32_t samplerId)
{
    std::unique_ptr<TextureSampler> textureSampler = std::make_unique<OpenGLTextureSampler>(samplerAttributes, samplerId);
    return std::move(textureSampler);
}

}