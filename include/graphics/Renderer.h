#pragma once

#include <vector>
#include <memory>

#include "graphics/RenderPipeline.h"
#include "graphics/RenderStep.h"

namespace prism {

class Renderer {

public:

    Renderer();

    virtual ~Renderer() = default;

    virtual void render();

    virtual void setRenderPipeline(std::unique_ptr<RenderPipeline> pipeline);

    virtual RenderPipeline* getRenderPipeline() const;

protected:

    virtual void preRender();

    virtual void startPass(RenderStep& step);

    virtual void draw(RenderStep& step);

    virtual void endPass(RenderStep& step);

    virtual void frame(RenderStep& step);

    virtual void postRender();

    std::unique_ptr<RenderPipeline> pipeline;

    std::vector<RenderStep> renderQueue;

};

}