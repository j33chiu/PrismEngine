#pragma once

#include "core/Camera.h"
#include "graphics/RenderObject.h"
#include "graphics/Material.h"

#include <atomic>

namespace prism {

enum class RenderStepType {
    START_PASS,
    MATERIAL,
    DRAW,
    END_PASS,
    FRAME,
    NONE
};

class RenderStep {

public:
    RenderStepType getType() const;
    void setType(RenderStepType type);

    // disable copy and assignment
    RenderStep(const RenderStep&) = delete;
    RenderStep& operator=(const RenderStep&) = delete;

    // allow moves, but std::atomic must be moved manually
    RenderStep(RenderStep&&) noexcept;
    RenderStep& operator=(RenderStep&&) noexcept;

    RenderStep* getNextStep() const;
    RenderStep* setNextStep(std::unique_ptr<RenderStep> nextStep);
    RenderStep* insertStep(std::unique_ptr<RenderStep> nextStep);
    bool removeSelf(RenderStep* previousStep);

    const Camera* getCamera() const;
    void setCamera(const Camera* camera);

    const RenderObject* getObject() const;
    void setObject(const RenderObject* object);

    const Material* getMaterial() const;
    void setMaterial(const Material* object);

    void setAsyncReady(bool ready);
    bool isAsyncReady() const;

    void setValid(bool valid);
    bool isValid() const;


private:
    // only render pipeline should be able to create these render steps
    friend class RenderPipeline;
    RenderStep(RenderStepType type);

    RenderStep(
        RenderStepType type,
        const Camera* camera,
        const RenderObject* object,
        const Material* material);

    RenderStepType type;
    std::unique_ptr<RenderStep> nextStep;

    const Camera* camera;
    const RenderObject* renderObject;
    const Material* material;
    std::atomic<bool> asyncReady;   // flag to tell render thread that current step can be processed safely
    std::atomic<bool> valid;      // flag to tell render thread that current step should be processed (otherwise should be removed)

    // TODO: add target of render

};

}