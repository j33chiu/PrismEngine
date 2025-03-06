#pragma once

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
                           std::uint8_t channels,
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

    // textures: api-specific creation
    virtual std::unique_ptr<Texture> createUniqueTexture(TextureUse textureUsage, 
                                                         const std::vector<std::byte>& bytes, 
                                                         std::uint32_t width, 
                                                         std::uint32_t height,
                                                         std::uint8_t channels,
                                                         const TextureSampler* textureSampler,
                                                         std::uint32_t textureId) = 0;

    // texture samplers: api-specific creation
    virtual std::unique_ptr<TextureSampler> createUniqueSampler(const TextureSamplerAttributes& samplerAttributes,
                                                                std::uint32_t samplerId) = 0;

private:
    // list of textures, their id corresponds to their index in the list
    std::vector<std::tuple<std::unique_ptr<Texture>, int>> texturesList;
    // set of loaded textures by texture file name, ensuring we do not double load textures
    std::unordered_map<std::string, int> loadedTexturesMap;

    // list of texture samplers, their id corresponds to their index in the list
    std::vector<std::tuple<std::unique_ptr<TextureSampler>, int>> textureSamplersList;
    // set of loaded texture samplers by attributes, ensuring we do not double create samplers with the same attributes
    std::unordered_map<TextureSamplerAttributes, int> loadedTextureSamplersMap;                                                     
};

}