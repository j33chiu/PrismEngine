#pragma once

#include <cstdint>
#include <algorithm>
#include <type_traits>

#include "core/math/pml.h"
#include "util/PrismHash.h"

namespace prism {

// behaviour when texcoords outside [0, 1] are used
enum TextureSamplerWrap : std::uint8_t {
    REPEAT = 0U,
    MIRROR,
    CLAMP_EDGE,
    CLAMP_BORDER
};

// for filtering when minifying and magnifying, also describes selection of mipmaps when minified.
enum TextureSamplerFilter : std::uint8_t {
    NEAREST,
    LINEAR
};

enum AnisotropicFilter : std::uint8_t {
    NONE = 1U,
    X2 = 2U,
    X4 = 4U,
    X8 = 8U,
    X16 = 16U
};

// values set here are defaults
struct TextureSamplerAttributes {
    // wrap modes in 3 dimensions (cubemaps, skyboxes)
    TextureSamplerWrap sWrapMode = TextureSamplerWrap::CLAMP_EDGE;
    TextureSamplerWrap tWrapMode = TextureSamplerWrap::CLAMP_EDGE;
    TextureSamplerWrap rWrapMode = TextureSamplerWrap::CLAMP_EDGE;

    pml::vec4 borderColour = pml::vec4(1.0f, 1.0f, 1.0f, 1.0f);

    // trilinear minfilter by default (mipmaps = true, linear interpolation between mipmaps, linear filtering for min filter)
    // bilinear magfilter by default (linear filtering for mag filter)

    TextureSamplerFilter minFilter = TextureSamplerFilter::LINEAR;
    TextureSamplerFilter magFilter = TextureSamplerFilter::LINEAR;

    bool mipmaps = true;
    TextureSamplerFilter mipmapFilter = TextureSamplerFilter::LINEAR;

    // anisotropic filtering disabled (1x) by default
    AnisotropicFilter anisotropicFilter = AnisotropicFilter::NONE;

    bool operator==(const TextureSamplerAttributes& other) const {
        return (sWrapMode == other.sWrapMode)
            && (tWrapMode == other.tWrapMode)
            && (rWrapMode == other.rWrapMode)
            && (borderColour == other.borderColour)
            && (minFilter == other.minFilter)
            && (magFilter == other.magFilter)
            && (mipmaps == other.mipmaps)
            && (mipmapFilter == other.mipmapFilter)
            && (anisotropicFilter == other.anisotropicFilter);
    }

    bool operator!=(const TextureSamplerAttributes& other) const {
        return !(*this == other);
    }
};

// abstract class to be implemented by specific graphics api
class TextureSampler {

public:
    TextureSampler(TextureSamplerAttributes samplerAttributes, std::uint32_t textureSamplerId);

    virtual ~TextureSampler() = default;

    TextureSampler(const TextureSampler&) = delete;
    TextureSampler &operator=(const TextureSampler&) = delete;

    TextureSamplerAttributes getSamplerAttributes() const;
    std::uint32_t getID() const;

private:
    TextureSamplerAttributes samplerAttributes;

    std::uint32_t textureSamplerId;

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
                           static_cast<std::underlying_type_t<prism::TextureSamplerFilter>>(textureSamplerAttr.mipmapFilter),
                           static_cast<std::underlying_type_t<prism::AnisotropicFilter>>(textureSamplerAttr.anisotropicFilter));
    }
};

}
