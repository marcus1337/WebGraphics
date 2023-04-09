#ifndef MODEL_H
#define MODEL_H
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <vector>
#include <glm/gtx/quaternion.hpp>
#include <glm/common.hpp>
#include "glm/glm.hpp"


class Model {
    glm::vec3 position = {0.f, 0.f, 0.f};
    glm::vec3 scale = {1.f,1.f,1.f};
    bool mirror = false;
    glm::vec2 rotateOffset = {0.f,0.f};
    float rotation = 0;

public:

    void setPosition(glm::vec3 _position);
    void setScale(glm::vec3 _scale);
    void setMirror(bool _mirror);
    void setRotation(float _roation);
    void setRotateOffset(glm::vec2 _rotateOffset);

    glm::mat4 getScaleMatrix();
    glm::mat4 getRotationMatrix();
    glm::mat4 getTranslationMatrix();
    glm::mat4 getModel();
    int getX();
    int getY();
    int getWidth();
    int getHeight();

};

#endif // !MODEL_H
