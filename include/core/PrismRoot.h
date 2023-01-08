#pragma once

#include <string>
#include <unordered_map>

#include "core/Platform.h"
#include "util/files/FileManager.h"
#include "graphics/WindowManager.h"
#include "graphics/MeshManager.h"
#include "graphics/MaterialManager.h"

#include <memory>

namespace prism {

/**
 * class provides access to all required manager classes
*/
class PrismRoot {

public:
    ~PrismRoot() = default;

    // public static get methods for managers
    static FileManager& fileManager();
    static WindowManager& windowManager();
    static MeshManager& meshManager();
    static MaterialManager& materialManager();

    // public static set methods for application-wide managers
    static void registerGraphicsApi(
        const GraphicsApi& graphicsApi,
        std::unique_ptr<FileManager> fileManager,
        std::unique_ptr<WindowManager> windowManager,
        std::unique_ptr<MeshManager> meshManager,
        std::unique_ptr<MaterialManager> materialManager
    );

    // reset
    static void stop();

private:
    // hide constructors
    PrismRoot();
    static PrismRoot& rootInstance();

    // get methods corresponding to public ones
    FileManager& fileManagerImpl() const;
    WindowManager& windowManagerImpl() const;
    MeshManager& meshManagerImpl() const;
    MaterialManager& materialManagerImpl() const;

    void registerGraphicsApiImpl(
        const GraphicsApi& graphicsApi,
        std::unique_ptr<FileManager> fileManager,
        std::unique_ptr<WindowManager> windowManager,
        std::unique_ptr<MeshManager> meshManager,
        std::unique_ptr<MaterialManager> materialManager
    );

    void stopImpl();

    struct GraphicsManagers {
        std::unique_ptr<FileManager> fileManager;
        std::unique_ptr<WindowManager> windowManager;
        std::unique_ptr<MeshManager> meshManager;
        std::unique_ptr<MaterialManager> materialManager;
    };

    std::unordered_map<GraphicsApi, GraphicsManagers> graphicsManagers;

    GraphicsApi currentGraphicsApi;

};

}