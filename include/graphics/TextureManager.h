#pragma once

#define STB_IMAGE_IMPLEMENTATION
#include "util/files/stb_image.h"

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>

#include "graphics/Texture.h"
#include "graphics/TextureSampler.h"

namespace prism {


class TextureManager {

public:
    TextureManager();
    virtual ~TextureManager() = default;

    // textures: load from file or create from raw data

    Texture* loadTexture(const std::string& textureFile, 
                         TextureUse textureUsage = TextureUse::IMAGE, 
                         const TextureSampler* textureSampler = nullptr);
    
    Texture* createTexture(TextureUse textureUsage, 
                           const std::vector<std::byte>& bytes, 
                           std::uint32_t width, 
                           std::uint32_t height,
                           const TextureSampler* textureSampler);

    std::uint32_t getAvailableTextureId();

    std::vector<const Texture*> getTextures() const;

    // texture samplers
    TextureSampler* createSampler(const TextureSamplerAttributes& samplerAttributes);

    TextureSampler* getDefaultSampler();

    std::uint32_t getAvailableSamplerId();

    std::vector<const TextureSampler*> getSamplers() const;

protected:
    // to be implemented by graphics api

    // textures: api-specific creation and deletion needed
    virtual std::unique_ptr<Texture> createUniqueTexture(TextureUse textureUsage, 
                                                         const std::vector<std::byte>& bytes, 
                                                         std::uint32_t width, 
                                                         std::uint32_t height,
                                                         const TextureSampler* textureSampler,
                                                         std::uint32_t textureId) = 0;

    virtual void deleteTexture(const Texture* texture) = 0;

    // texture samplers: api-specific creation and deletion needed
    virtual std::unique_ptr<TextureSampler> createUniqueSampler(const TextureSamplerAttributes& samplerAttributes,
                                                                std::uint32_t samplerId) = 0;

    virtual void deleteSampler(const TextureSampler* sampler) = 0;

private:
    std::uint32_t textureIdCounter;
    std::unordered_map<std::size_t, std::tuple<std::uint32_t, std::unique_ptr<Texture>>> texturesMap;

    std::uint32_t samplerIdCounter;
    std::unordered_map<TextureSamplerAttributes, std::tuple<std::uint32_t, std::unique_ptr<TextureSampler>>> samplersMap;

                                                        


};

}