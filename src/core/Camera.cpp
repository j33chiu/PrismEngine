#include "core/Camera.h"

#include "core/PrismId.h"

namespace prism {

Camera::Camera(std::uint32_t width, std::uint32_t height, float fovDegrees, float near, float far, CameraType type)
    : width(width)
    , height(height)
    , fovDegrees(fovDegrees)
    , nearPlane(near)
    , farPlane(far)
    , type(type)
{
    updateCamMatrix();
}

PrismId Camera::getId() const {
    return cameraId;
}

void Camera::updateCamMatrix() {
    switch(type) {
        default:
        case CameraType::PERSPECTIVE:
            projection = pml::perspective(fovDegrees, static_cast<float>(width) / height, nearPlane, farPlane);
            break;
        case CameraType::ORTHOGRAPHIC:
            projection = pml::ortho(0.0f, static_cast<float>(width), 0.0f, static_cast<float>(height), nearPlane, farPlane);
            break;
    }

    view = pml::lookAt(position, position + orientation, up);
    camMatrix = projection * view;
}

std::uint32_t Camera::getWidth() const {
    return width;
}

void Camera::setWidth(std::uint32_t width) {
    this->width = width;
}

std::uint32_t Camera::getHeight() const {
    return height;
}

void Camera::setHeight(std::uint32_t height) {
    this->height = height;
}

pml::vec3 Camera::getPosition() const {
    return position;
}

void Camera::setPosition(pml::vec3& position) {
    this->position = position;
}

pml::vec3 Camera::getOrientation() const {
    return orientation;
}

void Camera::setOrientation(pml::vec3& orientation) {
    this->orientation = orientation;
}

pml::vec3 Camera::getUp() const {
    return up;
}

void Camera::setUp(pml::vec3& up) {
    this->up = up;
}

float Camera::getFovDegrees() const {
    return fovDegrees;
}

void Camera::setFovDegrees(float fovDegrees) {
    this->fovDegrees = fovDegrees;
}

float Camera::getNear() const {
    return nearPlane;
}

void Camera::setNear(float near) {
    this->nearPlane = near;
}

float Camera::getFar() const {
    return farPlane;
}

void Camera::setFar(float far) {
    this->farPlane = far;
}

CameraType Camera::getCameraType() const {
    return type;
}

void Camera::setCameraType(CameraType type) {
    this->type = type;
}

pml::mat4 Camera::getCamMatrix() const {
    return camMatrix;
}

}