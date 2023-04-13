#include "Graphics/Shaders/Camera.h"
#include <iostream>
#include "glm/ext.hpp"
#include "glm/gtx/string_cast.hpp"

Camera::Camera() {

}

Camera::Camera(int screenWidth, int screenHeight) : screenWidth(screenWidth), screenHeight(screenHeight) {

}

void Camera::setPosition(glm::vec3 _position) {
    position = _position;
}

bool Camera::isOrthographic() {
    return orthographic;
}

void Camera::setProjectionType(bool _orthographic) {
    orthographic = _orthographic;
}

void Camera::setScreenSize(int width, int height) {
    screenWidth = width;
    screenHeight = height;
}

glm::mat4 Camera::getView() {
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(front);
    return glm::lookAt(position, position + front, up);
}

glm::mat4 Camera::getProjection() {
    const float nearPlane = 0.01f;
    const float farPlane = 10000.0f;
    if (isOrthographic()) {
        return glm::ortho(0.0f, (float)screenWidth, 0.0f, (float)screenHeight, nearPlane, farPlane);
    }
    else {
        float fov = glm::radians(45.0f);
        float aspectRatio = (float)screenWidth / (float)screenHeight;
        return glm::perspective(fov, aspectRatio, nearPlane, farPlane);
    }
}

int Camera::getScreenWidth() {
    return screenWidth;
}

int Camera::getScreenHeight() {
    return screenHeight;
}

void Camera::setYaw(float _yaw) {
    yaw = _yaw;
}
void Camera::setPitch(float _pitch) {
    pitch = _pitch;
}
float Camera::getYaw() {
    return yaw;
}
float Camera::getPitch() {
    return pitch;
}

void Camera::setOrbitTarget(glm::vec3 _orbitTarget) {
    orbitTarget = _orbitTarget;
    orbit(0.f, 0.f, 0.f);
}

void Camera::setOrbitDistance(float _distance) {
    orbitDistance = _distance;
    orbit(0.f, 0.f, 0.f);
}

void Camera::setOrbitPosition() {
    glm::vec3 direction(
        cos(glm::radians(yaw)) * cos(glm::radians(pitch)),
        sin(glm::radians(pitch)),
        sin(glm::radians(yaw)) * cos(glm::radians(pitch)));
    glm::vec3 moveDirection = orbitTarget - direction;
    moveDirection = glm::normalize(moveDirection);
    position = orbitDistance * moveDirection;
}

void Camera::orbit(float deltaX, float deltaY, float zoomDelta) {
    yaw += deltaX;
    pitch += deltaY;
    pitch = glm::clamp(pitch, -80.0f, 80.0f);
    yaw = fmod(yaw, 360.0f);
    orbitDistance = glm::clamp(orbitDistance + minOrbitDistance*zoomDelta, minOrbitDistance, maxOrbitDistance);
    setOrbitPosition();
}