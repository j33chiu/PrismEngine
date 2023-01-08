#pragma once

#include <string>

#include "graphics/Material.h"

namespace prism {

class MaterialManager {

public:

    virtual ~MaterialManager() = default;

    virtual Material* createMaterial(const std::string &vertexSource, const std::string &fragmentSource) = 0;
    virtual void clearMaterials() = 0;

};

}