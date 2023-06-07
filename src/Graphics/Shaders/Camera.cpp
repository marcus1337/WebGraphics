#include "Graphics/Shaders/Camera.h"
#include <iostream>
#include "glm/ext.hpp"
#include "glm/gtx/string_cast.hpp"

Camera::Camera() {
    screenWidth = 1920;
    screenHeight = 1080;
}

void Camera::setPosition(glm::vec3 _position) {
    position = _position;
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
    const float nearPlane = 1.1f;
    const float farPlane = 100.0f;
    return glm::ortho(0.0f, (float)screenWidth, 0.0f, (float)screenHeight, nearPlane, farPlane);
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

