#include "core/PrismRoot.h"

namespace prism {

PrismRoot::PrismRoot()
    : graphicsManagers()
    , currentGraphicsApi()
{}

PrismRoot& PrismRoot::rootInstance() {
    static PrismRoot prismRoot{};
    return prismRoot;
}

WindowManager& PrismRoot::windowManager() {
    return rootInstance().windowManagerImpl();
}

MeshManager& PrismRoot::meshManager() {
    return rootInstance().meshManagerImpl();
}

MaterialManager& PrismRoot::materialManager() {
    return rootInstance().materialManagerImpl();
}

TextureManager& PrismRoot::textureManager() {
    return rootInstance().textureManagerImpl();
}

void PrismRoot::registerGraphicsApi(
    const GraphicsApi& graphicsApi,
    std::unique_ptr<WindowManager> windowManager,
    std::unique_ptr<MeshManager> meshManager,
    std::unique_ptr<MaterialManager> materialManager,
    std::unique_ptr<TextureManager> textureManager
) {
    return rootInstance().registerGraphicsApiImpl(
        graphicsApi,
        std::move(windowManager),
        std::move(meshManager),
        std::move(materialManager),
        std::move(textureManager)
    );
}

void PrismRoot::stop() {
    return rootInstance().stopImpl();
}

WindowManager& PrismRoot::windowManagerImpl() const {
    return *graphicsManagers.at(currentGraphicsApi).windowManager;
}

MeshManager& PrismRoot::meshManagerImpl() const {
    return *graphicsManagers.at(currentGraphicsApi).meshManager;
}

MaterialManager& PrismRoot::materialManagerImpl() const {
    return *graphicsManagers.at(currentGraphicsApi).materialManager;
}

TextureManager& PrismRoot::textureManagerImpl() const {
    return *graphicsManagers.at(currentGraphicsApi).textureManager;
}

void PrismRoot::registerGraphicsApiImpl(
    const GraphicsApi& graphicsApi,
    std::unique_ptr<WindowManager> windowManager,
    std::unique_ptr<MeshManager> meshManager,
    std::unique_ptr<MaterialManager> materialManager,
    std::unique_ptr<TextureManager> textureManager
) {
    GraphicsManagers m {
        std::move(windowManager),
        std::move(meshManager),
        std::move(materialManager),
        std::move(textureManager)
    };

    graphicsManagers[graphicsApi] = std::move(m);
}

void PrismRoot::stopImpl() {
    
}

}