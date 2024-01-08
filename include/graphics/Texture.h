#pragma once

#include <vector>
#include <cstdint>

#include "TextureSampler.h"

namespace prism {

enum class TextureUse : std::uint8_t {
    IMAGE,              // texture image
    RENDER_TARGET,      
    DATA_MAP            
};

class Texture {

public:
    Texture(std::uint32_t id,
        TextureUse textureUsage, 
        const std::vector<std::byte>& bytes, 
        std::uint32_t width, 
        std::uint32_t height,
        const TextureSampler* textureSampler);

    // destructor needs to be implemented by specific graphics api
    virtual ~Texture() = 0;

    // remove assignment and copy constructor
    Texture(const Texture&) = delete;
    Texture &operator=(const Texture&) = delete;

    std::uint32_t getID() const;
    TextureUse getTextureUse() const;
    const std::vector<std::byte>& getBytes() const;
    std::uint32_t getWidth() const;
    std::uint32_t getHeight() const;

    void setTransparencyModifier(float transparencyModifier);
    float getTransparencyModifier() const;
    bool isTransparent() const;

    const TextureSampler* getTextureSampler() const;


protected:
    TextureUse textureUsage;
    std::vector<std::byte> bytes;

    std::uint32_t width;
    std::uint32_t height;

    std::uint32_t ID;
    float transparencyModifier;
    bool transparent;

    const TextureSampler* textureSampler;

};

}