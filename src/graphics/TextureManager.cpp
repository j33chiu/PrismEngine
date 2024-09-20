#include "graphics/TextureManager.h"

#include <sstream>

#include "core/Exception.h"
#include "util/PrismHash.h"
#include "util/files/FileManager.h"

namespace prism {

TextureManager::TextureManager() 
    : texturesList()
    , loadedTexturesMap()
    , textureSamplersList()
    , loadedTextureSamplersMap()
{}

Texture* TextureManager::loadTexture(const std::string& textureFile, 
                        TextureUse textureUsage, 
                        const TextureSampler* textureSampler) 
{
    if (textureUsage != TextureUse::IMAGE && textureUsage != TextureUse::DATA_MAP) 
        throw Exception("Only data maps and images can be loaded into textures from files.");

    if (!textureSampler) {
        throw Exception("Texture Sampler must not be null when loading a texture.");
    }

    int textureId = -1;
    auto it = loadedTexturesMap.find(textureFile);
    if (it != loadedTexturesMap.end()) {
        // texture already loaded
        textureId = it->second;
        // increment number of uses of the texture
        std::get<1>(texturesList[textureId]) += 1;
    } else {
        // TODO: load from file
        auto parsedFile = FileManager::getInstance().parseImage(textureFile);
        textureId = getAvailableTextureId();
        std::unique_ptr texture = createUniqueTexture(textureUsage, 
                                                      std::get<0>(parsedFile), 
                                                      std::get<1>(parsedFile), 
                                                      std::get<2>(parsedFile), 
                                                      std::get<3>(parsedFile), 
                                                      textureSampler, 
                                                      textureId);
        texturesList.push_back({std::move(texture), 1u});
    }

    return std::get<0>(texturesList[textureId]).get();
}

Texture* TextureManager::createTexture(TextureUse textureUsage, 
                        const std::vector<std::byte>& bytes, 
                        std::uint32_t width, 
                        std::uint32_t height,
                        std::uint8_t channels,
                        const TextureSampler* textureSampler)
{
    // hash generated string, should not collide with possible texture filenames
    static std::uint32_t i = 0u;

    std::stringstream st;
    st << "<!#'/" << i << "/'#!>"; // illegal characters in filenames
    i++;

    size_t hash = prism::hash(st.str());

    std::unique_ptr texture = createUniqueTexture(textureUsage, bytes, width, height, channels, textureSampler, getAvailableTextureId());
    texturesList.push_back({std::move(texture), 1u});
    return std::get<0>(texturesList[texturesList.size() - 1]).get();
}

std::uint32_t TextureManager::getAvailableTextureId() {
    return texturesList.size();
}

std::vector<const Texture*> TextureManager::getTextures() const {
    std::vector<const Texture*> textures;
    for (auto& pair : texturesList) {
        textures.push_back(std::get<0>(pair).get());
    }
    return textures;
}

// texture samplers
TextureSampler* TextureManager::createSampler(const TextureSamplerAttributes& samplerAttributes) {
    int samplerId = -1;
    auto it = loadedTextureSamplersMap.find(samplerAttributes);
    if (it != loadedTextureSamplersMap.end()) {
        // sampler already loaded
        // increment number of uses of the sampler
        samplerId = it->second;
        std::get<1>(textureSamplersList[samplerId]) += 1;
    } else {
        // sample not made yet
        // create default sampler
        samplerId = getAvailableSamplerId();
        std::unique_ptr<TextureSampler> sampler = createUniqueSampler(samplerAttributes, samplerId);
        textureSamplersList.push_back({std::move(sampler), 1u});
    }
    return std::get<0>(textureSamplersList[samplerId]).get();
}

TextureSampler* TextureManager::getDefaultSampler() {
    TextureSamplerAttributes defaultAttr{};

    return createSampler(defaultAttr);
}

std::uint32_t TextureManager::getAvailableSamplerId() {
    return textureSamplersList.size();
}

std::vector<const TextureSampler*> TextureManager::getSamplers() const {
    std::vector<const TextureSampler*> samplers;
    for (auto& pair : textureSamplersList) {
        samplers.push_back(std::get<0>(pair).get());
    }
    return samplers;
}

}