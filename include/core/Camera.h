#pragma once

#include <cstdint>

#include "core/math/pml.h"

namespace prism {

enum class CameraType {
    PERSPECTIVE,
    ORTHOGRAPHIC
};

class Camera {

public:
    
    Camera(std::uint32_t width, std::uint32_t height, float fovDegrees = 45.0f, float near = 0.1f, float far = 500.0f, CameraType type = CameraType::PERSPECTIVE);
    void updateCamMatrix();

    std::uint32_t getWidth() const;
    void setWidth(std::uint32_t width);
    std::uint32_t getHeight() const;
    void setHeight(std::uint32_t height);

    pml::vec3 getPosition() const;
    void setPosition(pml::vec3& position);
    pml::vec3 getOrientation() const;
    void setOrientation(pml::vec3& orientation);
    pml::vec3 getUp() const;
    void setUp(pml::vec3& up);
    
    float getFovDegrees() const;
    void setFovDegrees(float fovDegrees);
    float getNear() const;
    void setNear(float near);
    float getFar() const;
    void setFar(float far);

    CameraType getCameraType() const;
    void setCameraType(CameraType type);

    pml::mat4 getCamMatrix() const;

private:

    std::uint32_t width;
    std::uint32_t height;

    pml::vec3 position;
    pml::vec3 orientation;
    pml::vec3 up;

    pml::mat4 projection;
    pml::mat4 view;
    pml::mat4 camMatrix;

    float fovDegrees;
    float nearPlane;
    float farPlane;

    CameraType type;

};

}