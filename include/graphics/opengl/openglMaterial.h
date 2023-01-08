#pragma once

#include "graphics/Material.h"
#include "graphics/opengl/opengl.h"

namespace prism {

class OpenglMaterial : public Material {

public:

    OpenglMaterial(const std::string &vertexSource, const std::string &fragmentSource);
    ~OpenglMaterial() override;

    void bind() const;
    GLuint getID() const;

private:

    GLuint ID;

};

}