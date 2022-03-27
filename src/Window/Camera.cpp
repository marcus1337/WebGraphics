
#include "Camera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include <iostream>


glm::mat4 Camera::GetViewMatrix()
{
    glm::vec3 front;
    const float Yaw = -90.0f;
    const float Pitch = 0.0f;
    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    glm::vec3 Front = glm::normalize(front);
    return glm::lookAt(Position, Position + Front, Up);
}

glm::mat4 Camera::GetPerspectiveMatrix(int windowWidth, int windowHeight)
{
    return glm::ortho(0.0f, (float)windowWidth, 0.0f, (float)windowHeight, 0.01f, 100.0f);
}

MatrixData Camera::getMatrixData(int windowWidth, int windowHeight)
{
    return MatrixData(GetViewMatrix(), GetPerspectiveMatrix(windowWidth, windowHeight));
}