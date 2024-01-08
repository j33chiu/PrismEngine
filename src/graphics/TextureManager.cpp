#include "graphics/TextureManager.h"

#include <sstream>

#include "core/Exception.h"
#include "util/PrismHash.h"
#include "util/files/FileManager.h"

namespace {

std::tuple<std::vector<std::byte>, std::uint32_t, std::uint32_t, std::uint8_t> parse_image(
    const std::vector<char>& data,
    bool flipOnLoad = true)
{
    int width = 0;
    int height = 0;
    int channels = 0;

    stbi_set_flip_vertically_on_load(flipOnLoad);

    unsigned char* rawDataStart = stbi_load_from_memory(reinterpret_cast<const stbi_uc *>(data.data()),
                                                    static_cast<int>(data.size()),
                                                    &width,
                                                    &height,
                                                    &channels,
                                                    0);

    if (!rawDataStart || (channels == 0)) 
        throw prism::Exception("failed to load image data");

    std::byte* rawDataStartBytes = reinterpret_cast<std::byte*>(rawDataStart);

    const int rawDataSize = width * height * channels;

    std::byte* rawDataEndBytes = rawDataStartBytes + rawDataSize;

    std::vector<std::byte> out(rawDataSize);

    out.assign(rawDataStartBytes, rawDataEndBytes);

    return std::make_tuple(
        std::move(out), static_cast<std::uint32_t>(width), static_cast<std::uint32_t>(height), static_cast<std::uint8_t>(channels));
}

}

namespace prism {

TextureManager::TextureManager() 
    : textureIdCounter(0u)
    , texturesMap()
    , samplerIdCounter(0u)
    , samplersMap()
{}

Texture* TextureManager::loadTexture(const std::string& textureFile, 
                        TextureUse textureUsage, 
                        const TextureSampler* textureSampler) 
{
    if (textureUsage != TextureUse::IMAGE || textureUsage != TextureUse::DATA_MAP) 
        throw Exception("Only data maps and images can be loaded into textures from files.");

    std::size_t hash = prism::hash(textureFile);

    if (!texturesMap.contains(hash)) {
        // load from file

        FileManager::setLocation("testLocation");
        std::vector<char> data = FileManager::readFileBytes(textureFile);
        
    } else {
        // increment number of uses of the texture
        std::get<0>(texturesMap[hash])++;
    }

    return std::get<1>(texturesMap[hash]).get();
}

Texture* TextureManager::createTexture(TextureUse textureUsage, 
                        const std::vector<std::byte>& bytes, 
                        std::uint32_t width, 
                        std::uint32_t height,
                        const TextureSampler* textureSampler)
{
    // hash generated string, should not collide with possible texture filenames
    static std::uint32_t i = 0u;

    std::stringstream st;
    st << "<!#'/" << i << "/'#!>"; // illegal characters in filenames
    i++;

    size_t hash = prism::hash(st.str());

    std::unique_ptr texture = createUniqueTexture(textureUsage, bytes, width, height, textureSampler, getAvailableTextureId());

    texturesMap[hash] = {1u, std::move(texture)};
    return std::get<1>(texturesMap[hash]).get();
}

std::uint32_t TextureManager::getAvailableTextureId() {
    return textureIdCounter++;
}

std::vector<const Texture*> TextureManager::getTextures() const {
    std::vector<const Texture*> textures;
    std::for_each(texturesMap.begin(), texturesMap.end(),
                    [&textures] (const auto& pair) {
                        textures.push_back(std::get<1>(pair.second).get());
                    });
    return textures;
}

// texture samplers
TextureSampler* TextureManager::createSampler(const TextureSamplerAttributes& samplerAttributes) {
    if (!samplersMap.contains(samplerAttributes)) {
        // create default sampler
        std::unique_ptr<TextureSampler> sampler = createUniqueSampler(samplerAttributes, getAvailableSamplerId());
        samplersMap[samplerAttributes] = {1u, std::move(sampler)};
    } else {
        // incrememnt number of uses of the sampler
       std::get<0>(samplersMap[samplerAttributes])++;
    }
    return std::get<1>(samplersMap[samplerAttributes]).get();
}

TextureSampler* TextureManager::getDefaultSampler() {
    TextureSamplerAttributes defaultAttr{};

    return createSampler(defaultAttr);
}

std::uint32_t TextureManager::getAvailableSamplerId() {
    return samplerIdCounter++;
}

std::vector<const TextureSampler*> TextureManager::getSamplers() const {
    std::vector<const TextureSampler*> samplers;
    std::for_each(samplersMap.begin(), samplersMap.end(),
                    [&samplers] (const auto& pair) {
                        samplers.push_back(std::get<1>(pair.second).get());
                    });
    return samplers;
}

}