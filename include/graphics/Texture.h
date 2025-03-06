#pragma once

#include <vector>
#include <cstdint>

#include "TextureSampler.h"

namespace prism {

enum class TextureUse : std::uint8_t {
    IMAGE,              // texture image
    RENDER_TARGET,      // texture is a rendering target, gpu renders to this texture 
    DATA_MAP            // texture is a data mapping (eg depth, specular lighting maps)
};

/**
 * Storage class for raw texture data.
 * Contains texture information as well, including its use, width and height.
 */
class Texture {

public:
    Texture(std::uint32_t textureId,
        TextureUse textureUse, 
        const std::vector<std::byte>& bytes, 
        std::uint32_t width, 
        std::uint32_t height,
        std::uint8_t channels,
        const TextureSampler* textureSampler);

    // destructor needs to be implemented by specific graphics api
    virtual ~Texture() = default;

    // remove assignment and copy constructor
    Texture(const Texture&) = delete;
    Texture &operator=(const Texture&) = delete;

    std::uint32_t getID() const;
    TextureUse getTextureUse() const;
    const std::vector<std::byte>& getBytes() const;
    std::uint32_t getWidth() const;
    std::uint32_t getHeight() const;
    std::uint8_t getChannels() const;

    void setTransparencyModifier(float transparencyModifier);
    float getTransparencyModifier() const;
    bool isTransparent() const;

    const TextureSampler* getTextureSampler() const;


protected:
    TextureUse textureUse;
    std::vector<std::byte> bytes; // TODO: does this data need to be stored?

    std::uint32_t width;
    std::uint32_t height;
    std::uint8_t channels;

    std::uint32_t textureId;
    float transparencyModifier;
    bool transparent;

    const TextureSampler* textureSampler;

};

}