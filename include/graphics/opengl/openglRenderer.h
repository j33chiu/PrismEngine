#pragma once

#include <cstdint>
#include <memory>
#include <unordered_map>
#include <vector>

#include "graphics/opengl/opengl.h"
#include "graphics/opengl/openglVAO.h"
#include "graphics/opengl/openglBuffers.h"
#include "graphics/Renderer.h"
#include "graphics/RenderObject.h"
#include "graphics/RenderStep.h"

namespace prism {

class OpenGLRenderer : public Renderer {

public:
    OpenGLRenderer(const uint32_t width, const uint32_t height);
    ~OpenGLRenderer() override = default;

    void setRenderPipeline(std::unique_ptr<RenderPipeline> pipeline) override;

protected:
    void startPass(RenderStep* step) override;
    void draw(RenderStep* step) override;
    void frame(RenderStep* step) override;

private:

    // ubo for camera data, 
    // TODO: manage 1 UBO per camera to avoid re-writing camera data to the same buffer each time a frame is rendered
    //      would allow for multiple cameras to be rendered per frame
    std::unique_ptr<UBO> cameraData;

    // frame buffer (single one for now)
    

    // SSBO for object data (transforms etc)
    std::unordered_map<const RenderObject*, std::unique_ptr<SSBO>> objectData;

    // store all required VAOs and objects that use them
    // generate VAOs when renderpipeline is set (since all objects to be rendered will be processed)
    std::vector<std::unique_ptr<OpenglVAO>> vaos;
    std::unordered_map<OpenglVAO*, std::vector<const RenderObject*>> vaoObjectMap;

    const GLuint CAMERA_UBO_BINDING_INDEX = 0u;
    const GLuint OBJECT_TRANSFORM_SSBO_BINDING_INDEX = 1u;

};

}