#ifndef CAMERA_H
#define CAMERA_H
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <vector>
#include <glm/gtx/quaternion.hpp>
#include <glm/common.hpp>
#include "glm/glm.hpp"

class Camera {
    glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f);
    float yaw = 270.f;
    float pitch = 0.f;
    int screenWidth, screenHeight;
public:
    Camera();
    void setPosition(glm::vec3 _position);
    void setScreenSize(int width, int height);
    glm::mat4 getView();
    glm::mat4 getProjection();
    int getScreenWidth();
    int getScreenHeight();
    void setYaw(float _yaw);
    void setPitch(float _pitch);
    float getYaw();
    float getPitch();

};

#endif // !CAMERA_H
