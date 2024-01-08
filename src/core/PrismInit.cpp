#include "core/PrismInit.h"

#include "core/Exception.h"
#include "core/PrismRoot.h"
#include "logger/Logger.h"
#include "util/files/FileManager.h"
#include "graphics/WindowManager.h"
#include "graphics/win32/Win32WindowManager.h"
#include "graphics/MeshManager.h"
#include "graphics/opengl/openglMeshManager.h"
#include "graphics/MaterialManager.h"
#include "graphics/opengl/openglMaterialManager.h"

void engineRootInit(prism::Platform platformInfo) {
    // depending on platform, managers can be initialized and attached to root here:
    // so far, only support windows
    // TODO: support linux, macos

    std::unique_ptr<prism::WindowManager> windowManager;
    std::unique_ptr<prism::MeshManager> meshManager;
    std::unique_ptr<prism::MaterialManager> materialManager;

    // handle platform device first:
    switch (platformInfo.devicePlatform) {
        case prism::DevicePlatform::WINDOWS:
            windowManager = std::make_unique<prism::Win32WindowManager>(platformInfo);
            break;
        default:
            prism::Logger::error("unspecified platform info.. could not initialize app");
            throw prism::Exception("unspecified platform info.. could not initialize app");
            break;
    }

    // handle graphicsApi:
    switch (platformInfo.graphicsApi) {
        case prism::GraphicsApi::OPENGL:
            meshManager = std::make_unique<prism::OpenglMeshManager>();
            materialManager = std::make_unique<prism::OpenglMaterialManager>();
            break;
        case prism::GraphicsApi::VULKAN:
            break;
        case prism::GraphicsApi::DIRECTX12:
            break;
        default:
            prism::Logger::error("unspecified platform info.. could not initialize graphics api");
            throw prism::Exception("unspecified platform info.. could not initialize app");
            break;
    }

    prism::PrismRoot::registerGraphicsApi(
        platformInfo.graphicsApi,
        std::move(windowManager),
        std::move(meshManager),
        std::move(materialManager));
}

namespace prism {

/**
 * in these init functions, the Logger MUST be initialized first (by making any calls to any of the static functions)
 * since the variables that are freed on program termination are freed in reverse order of initialization
 * i.e. initialize Logger before any prism resources and it'll be kept until the end of the program
*/
void init(int argc, char **argv, std::function<void(int, char**)> func, Platform platformInfo) {
    Logger::turnOn();
    Logger::info("PrismInit::initDebug", "Prism initialized with Debug.");

    engineRootInit(platformInfo);

    Logger::turnOff();
    
    try {
        func(argc, argv);
    } catch (Exception e) {
        Logger::error("Exception", e.message);
    }

    Logger::turnOn();
    Logger::info("PrismInit::initDebug", "Prism stopping...");

    PrismRoot::stop();
}

void initDebug(int argc, char **argv, std::function<void(int, char**)> func, Platform platformInfo) {
    Logger::turnOn();
    Logger::info("PrismInit::initDebug", "Prism initialized with Debug.");

    engineRootInit(platformInfo);


    try {
        func(argc, argv);
    } catch (Exception e) {
        Logger::error("Exception", e.message);
    }
    

    Logger::info("PrismInit::initDebug", "Prism stopping...");

    PrismRoot::stop();
}

}