#pragma once

#include <string>
#include <unordered_map>

#include "core/Platform.h"
#include "graphics/WindowManager.h"
#include "graphics/MeshManager.h"
#include "graphics/MaterialManager.h"
#include "graphics/TextureManager.h"

#include <memory>

namespace prism {

/**
 * class provides access to all required manager classes
*/
class PrismRoot {

public:
    ~PrismRoot() = default;

    // public static get methods for managers
    static WindowManager& windowManager();
    static MeshManager& meshManager();
    static MaterialManager& materialManager();
    static TextureManager& textureManager();

    // public static set methods for application-wide managers
    static void registerGraphicsApi(
        const GraphicsApi& graphicsApi,
        std::unique_ptr<WindowManager> windowManager,
        std::unique_ptr<MeshManager> meshManager,
        std::unique_ptr<MaterialManager> materialManager,
        std::unique_ptr<TextureManager> textureManager
    );

    // reset
    static void stop();

private:
    // hide constructors
    PrismRoot();
    static PrismRoot& rootInstance();

    // get methods corresponding to public ones
    WindowManager& windowManagerImpl() const;
    MeshManager& meshManagerImpl() const;
    MaterialManager& materialManagerImpl() const;
    TextureManager& textureManagerImpl() const;

    void registerGraphicsApiImpl(
        const GraphicsApi& graphicsApi,
        std::unique_ptr<WindowManager> windowManager,
        std::unique_ptr<MeshManager> meshManager,
        std::unique_ptr<MaterialManager> materialManager,
        std::unique_ptr<TextureManager> textureManager
    );

    void stopImpl();

    struct GraphicsManagers {
        std::unique_ptr<WindowManager> windowManager;
        std::unique_ptr<MeshManager> meshManager;
        std::unique_ptr<MaterialManager> materialManager;
        std::unique_ptr<TextureManager> textureManager;
    };

    std::unordered_map<GraphicsApi, GraphicsManagers> graphicsManagers;

    GraphicsApi currentGraphicsApi;

};

}