#include "graphics/TextureSampler.h"

namespace prism {

TextureSampler::TextureSampler(TextureSamplerAttributes samplerAttributes, std::uint32_t textureSamplerId) 
    : samplerAttributes(samplerAttributes)
    , textureSamplerId(textureSamplerId)
{}

TextureSamplerAttributes TextureSampler::getSamplerAttributes() const {
    return samplerAttributes;
}

std::uint32_t TextureSampler::getID() const {
    return textureSamplerId;
}

}