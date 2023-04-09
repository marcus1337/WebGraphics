#ifndef CAMERA_H
#define CAMERA_H
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <vector>
#include <glm/gtx/quaternion.hpp>
#include <glm/common.hpp>
#include "glm/glm.hpp"

class Camera {
    int screenWidth, screenHeight;
    bool orthographic = true;
    glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f);
    float yaw = -90.f;
    float pitch = 0.f;
    bool isOrthographic();
public:
    Camera();
    Camera(int screenWidth, int screenHeight);
    void setPosition(glm::vec3 _position);
    void setProjectionType(bool _orthographic);
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
