#include "graphics/opengl/openglMaterialManager.h"

#include "graphics/opengl/openglMaterial.h"
#include "util/PrismHash.h"

namespace prism {

Material* OpenglMaterialManager::createMaterial(const std::string &vertexSource, const std::string &fragmentSource) {
    // generate id for material
    assert(!vertexSource.empty() && !fragmentSource.empty());
    std::size_t vInd1 = vertexSource.length() / 4;
    std::size_t vInd2 = vInd1 * 2;
    std::size_t vInd3 = vInd1 * 3;
    std::size_t fInd1 = fragmentSource.length() / 4;
    std::size_t fInd2 = fInd1 * 2;
    std::size_t fInd3 = fInd1 * 3;

    std::size_t materialId = prism::hash(
        vertexSource.length(), 
        fragmentSource.length(),
        vertexSource.at(vInd1),
        vertexSource.at(vInd2),
        vertexSource.at(vInd3),
        fragmentSource.at(fInd1),
        fragmentSource.at(fInd2),
        fragmentSource.at(fInd3));

    if (!materials.contains(materialId)) {
        materials[materialId] = std::make_unique<OpenglMaterial>(vertexSource, fragmentSource);
    }
    
    return materials[materialId].get();
}

void OpenglMaterialManager::clearMaterials() {
    materials.clear();
}

}