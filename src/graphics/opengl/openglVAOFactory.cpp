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

OpenglVAO* OpenglVAOFactory::generateVAO(VertexDataAttributes vertexAttr) {
    return getInstance().generateVAOImpl(vertexAttr);
}

OpenglVAO* OpenglVAOFactory::generateVAOImpl(VertexDataAttributes vertexAttr) {
    if (vaoMap.find(vertexAttr.vertexDataId) == vaoMap.end()) {
        vaoMap[vertexAttr.vertexDataId] = std::make_unique<OpenglVAO>(vertexAttr);
    }
    return vaoMap[vertexAttr.vertexDataId].get();
}

}