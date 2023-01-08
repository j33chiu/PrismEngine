#pragma once

#include <vector>
#include <tuple>
#include <memory>

#include "graphics/RenderObject.h"
#include "graphics/PrimitiveType.h"
#include "graphics/Material.h"

namespace prism {

class Scene {

public:
    template<class T, class... ARGS>
    RenderObject* createObject(const Material* material, ARGS &&... args) {
        RenderObject* obj = std::make_unique<T>(std::forward<ARGS>(args)...);
        return static_cast<T*>(addObject(material, std::move(obj)));
    }

    RenderObject* addObject(const Material* material, std::unique_ptr<RenderObject> obj);
    void removeObject(RenderObject* obj);

    std::vector<std::tuple<const Material*, std::unique_ptr<RenderObject>>>& getObjects();
    const std::vector<std::tuple<const Material*, std::unique_ptr<RenderObject>>>& getObjects() const;

private:
    // only renderpipeline should be able to create/own scenes
    friend class RenderPipeline;
    Scene();


    // map of material to objects, mostly for optimizing shader bindings
    std::vector<std::tuple<const Material*, std::unique_ptr<RenderObject>>> objects;

    // add light sources (point, ambient, directional, etc...)


};

}