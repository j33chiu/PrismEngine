#pragma once

#include <memory>
#include <unordered_map>

#include "graphics/opengl/OpenglVAO.h"
#include "graphics/opengl/OpenglMesh.h"

namespace prism {

class OpenglVAOFactory {

public:
    ~OpenglVAOFactory() = default;

    static OpenglVAO* generateVAO(VertexDataAttributes vertexAttr);

private:
    // hide constructors
    OpenglVAOFactory();
    static OpenglVAOFactory& getInstance();

    OpenglVAO* generateVAOImpl(VertexDataAttributes vertexAttr);

    std::unordered_map<std::string, std::unique_ptr<OpenglVAO>> vaoMap;
};

}