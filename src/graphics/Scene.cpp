#include "graphics/Scene.h"

#include <assert.h>

namespace prism {

Scene::Scene() 
    : objects()
{}

RenderObject* Scene::addObject(const Material* material, std::unique_ptr<RenderObject> obj) {
    assert(material != nullptr);
    // todo: if material is nullptr, use default material (if set by user)

    objects.emplace_back(material, std::move(obj));

    return std::get<1>(objects.back()).get();
}

void Scene::removeObject(RenderObject* obj) {
    objects.erase(
        std::remove_if(
            std::begin(objects),
            std::end(objects),
            [obj](const auto &o) {return std::get<1>(o).get() == obj;}
        ),
        std::end(objects)
    );
}


std::vector<std::tuple<const Material*, std::unique_ptr<RenderObject>>>& Scene::getObjects() {
    return objects;
}

const std::vector<std::tuple<const Material*, std::unique_ptr<RenderObject>>>& Scene::getObjects() const {
    return objects;
}

}