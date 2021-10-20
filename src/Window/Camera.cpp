
#include "Camera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include <iostream>

void Camera::setOrthographic(bool _isOrthographic){
    isOrthographic = _isOrthographic;
}

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
{
    isOrthographic = false;
    Position = position;
    WorldUp = up;
    Yaw = yaw;
    Pitch = pitch;
    updateCameraVectors();
}

Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
{
    isOrthographic = false;
    Position = glm::vec3(posX, posY, posZ);
    WorldUp = glm::vec3(upX, upY, upZ);
    Yaw = yaw;
    Pitch = pitch;
    updateCameraVectors();
}

glm::mat4 Camera::GetViewMatrix()
{
    return glm::lookAt(Position, Position + Front, Up);
}

glm::mat4 Camera::GetPerspectiveMatrix(int windowWidth, int windowHeight)
{
    if (windowHeight == 0)
        return glm::mat4{};
    if(!isOrthographic)
        return glm::perspective(glm::radians(Zoom), (float)windowWidth / (float)windowHeight, 0.01f, 500.0f);
    return glm::ortho(-1.0f,(float)1.0f, (float)-1.0f, 1.0f, 0.01f, 500.0f);
}

void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime)
{
    float velocity = 0.03f;
    if (direction == FORWARD)
        Position += Front * velocity;
    if (direction == BACKWARD)
        Position -= Front * velocity;
    if (direction == LEFT)
        Position -= Right * velocity;
    if (direction == RIGHT)
        Position += Right * velocity;
    if (direction == ROTATELEFT)
    {
        Yaw -= 1;
        updateCameraVectors();
    }
    if (direction == ROTATERIGHT)
    {
        Yaw += 1;
        updateCameraVectors();
    }
}

void Camera::move(Mouse &mouse, Keyboard &keyboard)
{
    ProcessMouseMovement(mouse.deltaMouseX, mouse.deltaMouseY);

    if (keyboard.goForward)
        ProcessKeyboard(FORWARD, 0);
    if (keyboard.goBack)
        ProcessKeyboard(BACKWARD, 0);
    if (keyboard.goLeft)
        ProcessKeyboard(LEFT, 0);
    if (keyboard.goRight)
        ProcessKeyboard(RIGHT, 0);
    if (keyboard.rotateLeft)
    {
        ProcessKeyboard(ROTATELEFT, 0);
    }
    if (keyboard.rotateRight)
    {
        ProcessKeyboard(ROTATERIGHT, 0);
    }
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch)
{
    xoffset *= MouseSensitivity;
    yoffset *= MouseSensitivity;

    Yaw += xoffset;
    Pitch += yoffset;

    if (constrainPitch)
    {
        if (Pitch > 89.0f)
            Pitch = 89.0f;
        if (Pitch < -89.0f)
            Pitch = -89.0f;
    }

    updateCameraVectors();
}

void Camera::updateCameraVectors()
{
    glm::vec3 front;
    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    Front = glm::normalize(front);

    Right = glm::normalize(glm::cross(Front, WorldUp));
    Up = glm::normalize(glm::cross(Right, Front));
}

MatrixData Camera::getMatrixData(int windowWidth, int windowHeight)
{
    return MatrixData(GetViewMatrix(), GetPerspectiveMatrix(windowWidth, windowHeight));
}