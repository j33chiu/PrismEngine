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

FileManager& PrismRoot::fileManager() {
    return rootInstance().fileManagerImpl();
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

void PrismRoot::registerGraphicsApi(
    const GraphicsApi& graphicsApi,
    std::unique_ptr<FileManager> fileManager,
    std::unique_ptr<WindowManager> windowManager,
    std::unique_ptr<MeshManager> meshManager,
    std::unique_ptr<MaterialManager> materialManager
) {
    return rootInstance().registerGraphicsApiImpl(
        graphicsApi,
        std::move(fileManager),
        std::move(windowManager),
        std::move(meshManager),
        std::move(materialManager)
    );
}

void PrismRoot::stop() {
    return rootInstance().stopImpl();
}

FileManager& PrismRoot::fileManagerImpl() const {
    return *graphicsManagers.at(currentGraphicsApi).fileManager;
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

void PrismRoot::registerGraphicsApiImpl(
    const GraphicsApi& graphicsApi,
    std::unique_ptr<FileManager> fileManager,
    std::unique_ptr<WindowManager> windowManager,
    std::unique_ptr<MeshManager> meshManager,
    std::unique_ptr<MaterialManager> materialManager
) {
    GraphicsManagers m {
        std::move(fileManager),
        std::move(windowManager),
        std::move(meshManager),
        std::move(materialManager)
    };

    graphicsManagers[graphicsApi] = std::move(m);
}

void PrismRoot::stopImpl() {
    
}

}