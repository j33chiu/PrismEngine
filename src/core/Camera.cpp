#include "core/Camera.h"

#include "core/PrismId.h"

namespace prism {

Camera::Camera(std::uint32_t width, std::uint32_t height, float fovRad, float near, float far, CameraType type)
    : width(width)
    , height(height)
    , fovRad(fovRad)
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
    // TODO: depending on graphics api, the perspective and ortho matrices can be different (and also use different RH/LH conventions)
    switch(type) {
        default:
        case CameraType::PERSPECTIVE:
            projection = pml::perspective(fovRad, static_cast<float>(width) / height, nearPlane, farPlane);
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
    this->orientation = pml::normalize(orientation);
}

pml::vec3 Camera::getUp() const {
    return up;
}

void Camera::setUp(pml::vec3& up) {
    this->up = pml::normalize(up);
}

float Camera::getfovRad() const {
    return fovRad;
}

pml::vec3 Camera::getForwardOrientation() const {
    return orientation;
}

pml::vec3 Camera::getBackwardOrientation() const {
    return -orientation;
}

pml::vec3 Camera::getLeftOrientation() const {
    return -pml::normalize(pml::cross(orientation, up));
}

pml::vec3 Camera::getRightOrientation() const {
    return pml::normalize(pml::cross(orientation, up));
}

pml::vec3 Camera::getUpOrientation() const {
    return pml::normalize(pml::cross(getRightOrientation(), orientation));
}

pml::vec3 Camera::getDownOrientation() const {
    return pml::normalize(pml::cross(getLeftOrientation(), orientation));
}

pml::vec3 Camera::getForwardCardinal() const {
    return pml::normalize(pml::vec3(orientation.x, 0, orientation.z));
}

pml::vec3 Camera::getBackwardCardinal() const {
    return -pml::normalize(pml::vec3(orientation.x, 0, orientation.z));
}

pml::vec3 Camera::getLeftCardinal() const {
    return -pml::normalize(pml::cross(pml::vec3(orientation.x, 0, orientation.z), up));
}

pml::vec3 Camera::getRightCardinal() const {
    return pml::normalize(pml::cross(pml::vec3(orientation.x, 0, orientation.z), up));
}

pml::vec3 Camera::getUpCardinal() const {
    return up;
}

pml::vec3 Camera::getDownCardinal() const {
    return -up;
}

void Camera::setfovRad(float fovRad) {
    this->fovRad = fovRad;
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

void Camera::moveForwardOrientation(const float speed) {
    this->position += speed * getForwardOrientation();
}

void Camera::moveBackwardOrientation(const float speed) {
    this->position += speed * getBackwardOrientation();
}

void Camera::moveLeftOrientation(const float speed) {
    this->position += speed * getLeftOrientation();
}

void Camera::moveRightOrientation(const float speed) {
    this->position += speed * getRightOrientation();
}

void Camera::moveUpOrientation(const float speed) {
    this->position += speed * getUpOrientation();
}

void Camera::moveDownOrientation(const float speed) {
    this->position += speed * getDownOrientation();
}

void Camera::moveForwardCardinal(const float speed) {
    this->position += speed * getForwardCardinal();
}

void Camera::moveBackwardCardinal(const float speed) {
    this->position += speed * getBackwardCardinal();
}

void Camera::moveLeftCardinal(const float speed) {
    this->position += speed * getLeftCardinal();
}

void Camera::moveRightCardinal(const float speed) {
    this->position += speed * getRightCardinal();
}

void Camera::moveUpCardinal(const float speed) {
    this->position += speed * getUpCardinal();
}

void Camera::moveDownCardinal(const float speed) {
    this->position += speed * getDownCardinal();
}

bool Camera::isFPSCamera() const {
    return fpsCamera;
}

void Camera::setFPSMode(const bool fpsCamera) {
    this->fpsCamera = fpsCamera;
}

void Camera::updateFPSOrientation(const short mouseX, const short mouseY) {
    static short prevMouseX = width / 2;
    static short prevMouseY = height / 2;

    short dx = mouseX - prevMouseX;
    short dy = mouseY - prevMouseY;
    prevMouseX = mouseX;
    prevMouseY = mouseY;

    updateFPSOrientationDelta(dx, dy);
}

void Camera::updateFPSOrientationDelta(const short mouseDX, const short mouseDY) {
    if (fpsCamera) {
        float rotX = fpsSens * mouseDY / height;
        float rotY = fpsSens * mouseDX / width;

        applyRotation(rotX, rotY);
    }
}

void Camera::applyRotation(const float rotX, const float rotY) {
    // up and down rotation
    pml::vec3 newOrientation = prism::pml::rotate(orientation, pml::toRadians(-rotX), -pml::cross(orientation, up));

    // TODO allow custom limiting of up and down rotation
    if (!((pml::angle(newOrientation, up) <= pml::toRadians(5.0f)) || (pml::angle(newOrientation, -up) <= pml::toRadians(5.0f)))) {
        orientation = newOrientation;
    }

    // left and right rotation
    newOrientation = pml::rotate(orientation, pml::toRadians(-rotY), -up);

    // TODO allow custom limiting of left and right rotation
    orientation = newOrientation;
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