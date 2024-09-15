#pragma once

#include <vector>
#include <memory>

#include "graphics/RenderPipeline.h"
#include "graphics/RenderStep.h"

namespace prism {

class Renderer {

public:

    Renderer(const uint32_t width, const uint32_t height);

    virtual ~Renderer() = default;

    virtual void render();

    virtual void setRenderPipeline(std::unique_ptr<RenderPipeline> pipeline);

    virtual RenderPipeline* getRenderPipeline() const;

    void updateSize(const uint32_t width, const uint32_t height);

protected:

    virtual void preRender();

    virtual void startPass(RenderStep& step);

    virtual void draw(RenderStep& step);

    virtual void endPass(RenderStep& step);

    virtual void frame(RenderStep& step);

    virtual void postRender();

    std::unique_ptr<RenderPipeline> pipeline;
    std::vector<RenderStep> renderQueue;

    uint32_t width;
    uint32_t height;

};

}