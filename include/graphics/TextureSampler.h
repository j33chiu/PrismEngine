#pragma once

#include <cstdint>
#include <algorithm>
#include <type_traits>

#include "core/math/pml.h"
#include "util/PrismHash.h"

namespace prism {

// behaviour when texcoords outside [0, 1] are used
enum class TextureSamplerWrap : std::uint8_t {
    REPEAT,
    MIRRORED_REPEAT,
    CLAMP_EDGE,
    CLAMP_BORDER
};

// for minifying, magnifying, choosing mip maps
enum class TextureSamplerFilter : std::uint8_t {
    NEAREST,                // min/mag filter: pixel art
    LINEAR                  // min/mag filter: blurred when scaled up
};

// values set here are defaults
struct TextureSamplerAttributes {
    // wrap modes in 3 dimensions (if applicable)
    TextureSamplerWrap sWrapMode = TextureSamplerWrap::REPEAT;
    TextureSamplerWrap tWrapMode = TextureSamplerWrap::REPEAT;
    TextureSamplerWrap rWrapMode = TextureSamplerWrap::REPEAT;

    pml::vec4 borderColour = pml::vec4(1.0f, 1.0f, 1.0f, 1.0f);

    TextureSamplerFilter minFilter = TextureSamplerFilter::LINEAR;
    TextureSamplerFilter magFilter = TextureSamplerFilter::LINEAR;

    bool mipmaps = true;
    TextureSamplerFilter mipmapFilter = TextureSamplerFilter::LINEAR;

    bool operator==(const TextureSamplerAttributes& other) const {
        return (sWrapMode == other.sWrapMode)
            && (tWrapMode == other.tWrapMode)
            && (rWrapMode == other.rWrapMode)
            && (borderColour == other.borderColour)
            && (minFilter == other.minFilter)
            && (magFilter == other.magFilter)
            && (mipmaps == other.mipmaps)
            && (mipmapFilter == other.mipmapFilter);
    }

    bool operator!=(const TextureSamplerAttributes& other) const {
        return !(*this == other);
    }
};

// abstract class to be implemented by specific graphics api
class TextureSampler {

public:
    TextureSampler(TextureSamplerAttributes samplerAttributes);

    virtual ~TextureSampler() = default;

    TextureSampler(const TextureSampler&) = delete;
    TextureSampler &operator=(const TextureSampler&) = delete;

    TextureSamplerAttributes getSamplerAttributes() const;

private:
    TextureSamplerAttributes samplerAttributes;

};

}

// has to use std to be declared in this file
namespace std {

template<>
struct hash<prism::TextureSamplerAttributes> {
    size_t operator()(const prism::TextureSamplerAttributes& textureSamplerAttr) const {
        return prism::hash(static_cast<std::underlying_type_t<prism::TextureSamplerWrap>>(textureSamplerAttr.sWrapMode),
                           static_cast<std::underlying_type_t<prism::TextureSamplerWrap>>(textureSamplerAttr.tWrapMode),
                           static_cast<std::underlying_type_t<prism::TextureSamplerWrap>>(textureSamplerAttr.rWrapMode),
                           textureSamplerAttr.borderColour,
                           static_cast<std::underlying_type_t<prism::TextureSamplerFilter>>(textureSamplerAttr.minFilter),
                           static_cast<std::underlying_type_t<prism::TextureSamplerFilter>>(textureSamplerAttr.magFilter),
                           textureSamplerAttr.mipmaps,
                           static_cast<std::underlying_type_t<prism::TextureSamplerFilter>>(textureSamplerAttr.mipmapFilter));
    }
};

}
