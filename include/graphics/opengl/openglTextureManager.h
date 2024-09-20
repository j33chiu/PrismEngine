#pragma once

#include "graphics/TextureManager.h"

namespace prism {

class OpenGLTextureManager : public TextureManager {

public:
    OpenGLTextureManager();
    ~OpenGLTextureManager() override = default;

    bool arebindlessTexturesEnabled() const;
    
private:
    // textures: opengl specific creation and deletion needed
    std::unique_ptr<Texture> createUniqueTexture(TextureUse textureUsage, 
                                                 const std::vector<std::byte>& bytes, 
                                                 std::uint32_t width, 
                                                 std::uint32_t height,
                                                 std::uint8_t channels,
                                                 const TextureSampler* textureSampler,
                                                 std::uint32_t textureId) override;

    // texture samplers: opengl specific creation and deletion needed
    std::unique_ptr<TextureSampler> createUniqueSampler(const TextureSamplerAttributes& samplerAttributes,
                                                        std::uint32_t samplerId) override;

    // opengl specific fields
    bool bindlessTexturesEnabled = false;

};
    
}