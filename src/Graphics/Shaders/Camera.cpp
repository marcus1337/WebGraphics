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
    const float Yaw = -90.0f;
    const float Pitch = 0.0f;
    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front = glm::normalize(front);
    return glm::lookAt(position, position + front, up);
}

glm::mat4 Camera::getProjection() {
    const float nearPlane = 0.01f;
    const float farPlane = 100.0f;
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

