#pragma once

#include <memory>
#include <unordered_map>

#include "graphics/opengl/OpenglVAO.h"
#include "graphics/opengl/OpenglMesh.h"

namespace prism {

class OpenglVAOFactory {

public:
    ~OpenglVAOFactory() = default;

    static OpenglVAO* generateVAO(const VertexDescriptor& vertexDescription);

private:
    // hide constructors
    OpenglVAOFactory();
    static OpenglVAOFactory& getInstance();

    OpenglVAO* generateVAOImpl(const VertexDescriptor& vertexDescription);

    std::unordered_map<std::size_t, std::unique_ptr<OpenglVAO>> vaoMap;
};

}