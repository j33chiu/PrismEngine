#include "graphics/Texture.h"

namespace prism {

Texture::Texture(std::uint32_t id,
    TextureUse textureUsage, 
    const std::vector<std::byte>& bytes, 
    std::uint32_t width, 
    std::uint32_t height,
    const TextureSampler* textureSampler)
    : textureUsage(textureUsage)
    , bytes(bytes)
    , width(width)
    , height(height)
    , ID(ID)
    , transparencyModifier(1.0f)
    , transparent(false)
    , textureSampler(textureSampler)
{
    // assume 4 channel texture, rgba
    for (int i = 3; i < bytes.size(); i += 4) {
        if (bytes[i] != std::byte{0xFF}) {
            transparent = true;
            break;
        }
    }
}

Texture::~Texture() = default;

std::uint32_t Texture::getID() const {
    return ID;
}

TextureUse Texture::getTextureUse() const {
    return textureUsage;
}

const std::vector<std::byte>& Texture::getBytes() const {
    return bytes;
}

std::uint32_t Texture::getWidth() const {
    return width;
}

std::uint32_t Texture::getHeight() const {
    return height;
}

void Texture::setTransparencyModifier(float transparencyModifier) {
    this->transparencyModifier = transparencyModifier;
}

float Texture::getTransparencyModifier() const {
    return transparencyModifier;
}

bool Texture::isTransparent() const {
    return transparent;
}

const TextureSampler* Texture::getTextureSampler() const {
    return textureSampler;
}

}