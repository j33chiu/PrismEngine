#pragma once

#include "core/Camera.h"
#include "graphics/RenderObject.h"
#include "graphics/Material.h"

namespace prism {

enum class RenderStepType {
    START_PASS,
    DRAW,
    END_PASS,
    FRAME
};

class RenderStep {

public:
    RenderStepType getType() const;
    void setType(RenderStepType type);

    const Camera* getCamera() const;
    void setCamera(const Camera* camera);

    const RenderObject* getObject() const;
    void setObject(const RenderObject* object);

    const Material* getMaterial() const;
    void setMaterial(const Material* object);


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

    const Camera* camera;
    const RenderObject* renderObject;
    const Material* material;

    // todo: add target of render

};

}