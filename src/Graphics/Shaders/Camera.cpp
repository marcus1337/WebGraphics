#include "Graphics/Shaders/Camera.h"
#include <iostream>

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
    const float nearPlane = 0.001f;
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

