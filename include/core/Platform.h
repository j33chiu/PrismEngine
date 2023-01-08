#pragma once

#include <cstdint>

namespace prism {

enum class DevicePlatform : std::uint32_t {
    WINDOWS,
    MACOS,
    LINUX,
    ANDROID,
    IOS
};

enum class GraphicsApi : std::uint32_t {
    OPENGL,
    VULKAN,
    DIRECTX12
};

struct Platform {
    DevicePlatform devicePlatform;
    GraphicsApi graphicsApi;
};

}