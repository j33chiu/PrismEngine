#pragma once 

#include <unordered_map>
#include <memory>

#include "graphics/MaterialManager.h"

namespace prism {

class OpenglMaterialManager : public MaterialManager {

public:

    ~OpenglMaterialManager() override = default;

    Material* createMaterial(const std::string &vertexSource, const std::string &fragmentSource) override;
    void clearMaterials() override;

private:
    std::unordered_map<std::size_t, std::unique_ptr<Material>> materials;

};

}