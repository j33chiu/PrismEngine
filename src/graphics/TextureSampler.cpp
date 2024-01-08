#include "graphics/TextureSampler.h"

namespace prism {

TextureSampler::TextureSampler(TextureSamplerAttributes samplerAttributes) 
    : samplerAttributes(samplerAttributes)
{}

TextureSamplerAttributes TextureSampler::getSamplerAttributes() const {
    return samplerAttributes;
}

}