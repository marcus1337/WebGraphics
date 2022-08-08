#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include "IO/Controller/Keyboard.h"
#include "IO/Controller/Mouse.h"
#include "Utility/MatrixData.h"

#ifndef CAMERA_H
#define CAMERA_H

enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    ROTATELEFT,
    ROTATERIGHT
};

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

class Camera
{
public:
    glm::vec3 Position = glm::vec3(0.0f, 0.0f, 3.0f);
    glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);

    glm::mat4 GetViewMatrix();
    glm::mat4 GetPerspectiveMatrix(int windowWidth, int windowHeight);
    MatrixData getMatrixData(int windowWidth, int windowHeight);

private:

};
#endif