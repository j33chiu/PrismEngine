#pragma once

#include <cstdint>

#include "core/math/pml.h"
#include "core/PrismId.h"

namespace prism {

enum class CameraType {
    PERSPECTIVE,
    ORTHOGRAPHIC
};

class Camera {

public:
    
    Camera(std::uint32_t width, std::uint32_t height, float fovRad = pml::toRadians(70.0f), float near = 0.1f, float far = 500.0f, CameraType type = CameraType::PERSPECTIVE);

    PrismId getId() const;

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

    // get orientation vectors for directions relative to camera orientation
    pml::vec3 getForwardOrientation() const;
    pml::vec3 getBackwardOrientation() const;
    pml::vec3 getLeftOrientation() const;
    pml::vec3 getRightOrientation() const;
    pml::vec3 getUpOrientation() const;
    pml::vec3 getDownOrientation() const;

    // get direction vectors for cardinal directions 
    pml::vec3 getForwardCardinal() const;
    pml::vec3 getBackwardCardinal() const;
    pml::vec3 getLeftCardinal() const;
    pml::vec3 getRightCardinal() const;
    pml::vec3 getUpCardinal() const;
    pml::vec3 getDownCardinal() const;
    
    float getfovRad() const;
    void setfovRad(float fovRad);
    float getNear() const;
    void setNear(float near);
    float getFar() const;
    void setFar(float far);

    // movement
    void moveForwardOrientation(const float speed);
    void moveBackwardOrientation(const float speed);
    void moveLeftOrientation(const float speed);
    void moveRightOrientation(const float speed);
    void moveUpOrientation(const float speed);
    void moveDownOrientation(const float speed);

    void moveForwardCardinal(const float speed);
    void moveBackwardCardinal(const float speed);
    void moveLeftCardinal(const float speed);
    void moveRightCardinal(const float speed);
    void moveUpCardinal(const float speed);
    void moveDownCardinal(const float speed);

    // camera orientation movement
    bool isFPSCamera() const;
    void setFPSMode(const bool fpsCamera);
    void updateFPSOrientation(const short mouseX, const short mouseY);
    void updateFPSOrientationDelta(const short mouseDX, const short mouseDY);
    void applyRotation(const float rotX, const float rotY);

    CameraType getCameraType() const;
    void setCameraType(CameraType type);

    pml::mat4 getCamMatrix() const;

private:

    PrismId cameraId;

    std::uint32_t width;
    std::uint32_t height;

    pml::vec3 position;     // camera position vector
    pml::vec3 orientation;  // vector that points in the direction the camera points
    pml::vec3 up;           // vector that is normal to the "flat plane", typically direction of z axis

    pml::mat4 projection;
    pml::mat4 view;
    pml::mat4 camMatrix;

    float fovRad;
    float nearPlane;
    float farPlane;

    bool fpsCamera = false;
    float fpsSens = 100.0f;
    CameraType type;

};

}