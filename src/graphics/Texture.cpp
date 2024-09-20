#include "graphics/Texture.h"

namespace prism {

Texture::Texture(std::uint32_t textureId,
    TextureUse textureUse, 
    const std::vector<std::byte>& bytes, 
    std::uint32_t width, 
    std::uint32_t height,
    std::uint8_t channels,
    const TextureSampler* textureSampler)
    : textureUse(textureUse)
    , bytes(bytes)
    , width(width)
    , height(height)
    , channels(channels)
    , textureId(textureId)
    , transparencyModifier(1.0f)
    , transparent(false)
    , textureSampler(textureSampler)
{
    if (channels == 4) {
        // can check for transparency
        for (int i = 3; i < bytes.size(); i += 4) {
            if (bytes[i] != std::byte{0xFF}) {
                transparent = true;
                break;
            }
        }
    }
}

std::uint32_t Texture::getID() const {
    return textureId;
}

TextureUse Texture::getTextureUse() const {
    return textureUse;
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

std::uint8_t Texture::getChannels() const {
    return channels;
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