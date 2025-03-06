#include "graphics/opengl/openglVAOFactory.h"

#include <assert.h>
#include <type_traits>

namespace prism {

OpenglVAOFactory::OpenglVAOFactory() 
    : vaoMap()
{}

OpenglVAOFactory& OpenglVAOFactory::getInstance() {
    static OpenglVAOFactory vaoFactory{};
    return vaoFactory;
}

OpenglVAO* OpenglVAOFactory::generateVAO(const VertexDescriptor& vertexDescription) {
    return getInstance().generateVAOImpl(vertexDescription);
}

OpenglVAO* OpenglVAOFactory::generateVAOImpl(const VertexDescriptor& vertexDescription) {
    auto hasher = std::hash<prism::VertexDescriptor>();
    std::size_t hash = hasher(vertexDescription);
    if (vaoMap.find(hash) == vaoMap.end()) {
        vaoMap[hash] = std::make_unique<OpenglVAO>(vertexDescription);
    }
    return vaoMap[hash].get();
}

}