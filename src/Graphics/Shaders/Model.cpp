#include "Graphics/Shaders/Model.h"
#include "glm/gtx/string_cast.hpp"
#include <iostream>

void Model::setPosition(glm::vec3 _position) {
    position = _position;
}

void Model::setScale(glm::vec3 _scale) {
    scale = _scale;
}

void Model::setMirror(bool _mirror) {
    mirror = _mirror;
}

void Model::setRotation(glm::vec3 _rotation) {
    rotation = _rotation;
}

void Model::setRotateOffset(glm::vec2 _rotateOffset) {
    rotateOffset = _rotateOffset;
}

glm::mat4 Model::getScaleMatrix() {
    auto tmpScale = scale;
    if (mirror) {
        tmpScale.x = -tmpScale.x;
    }
    return glm::scale(glm::mat4(1.0f), tmpScale);
}

glm::mat4 Model::getRotationMatrix() {
    glm::mat4 rotateMat(1.0f);
    rotateMat = glm::rotate(rotateMat, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    rotateMat = glm::rotate(rotateMat, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    rotateMat = glm::rotate(rotateMat, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

    glm::mat4 offsetToMiddle = glm::translate(glm::mat4(1.0f),
        glm::vec3(-rotateOffset.x / 2.0f, -rotateOffset.y / 2.0f, 0.0f));
    glm::mat4 revertOffsetToMiddle = glm::translate(glm::mat4(1.0f),
        glm::vec3(rotateOffset.x / 2.0f, rotateOffset.y / 2.0f, 0.0f));

    return revertOffsetToMiddle * rotateMat * offsetToMiddle;
}

glm::mat4 Model::getTranslationMatrix() {
    glm::vec3 adjustedPosition = glm::vec3(position.x + scale.x / 2.0f, position.y + scale.y / 2.0f, position.z);
    return glm::translate(glm::mat4(1.0f), adjustedPosition);
}

glm::mat4 Model::getModel() {
    glm::mat4 scaleMat = getScaleMatrix();
    glm::mat4 rotateMat = getRotationMatrix();
    glm::mat4 translateMat = getTranslationMatrix();
    glm::mat4 modModel = translateMat * rotateMat * scaleMat;
    return modModel;
}

int Model::getX() {
    return position.x;
}
int Model::getY() {
    return position.y;
}
int Model::getWidth() {
    return scale.x;
}
int Model::getHeight() {
    return scale.y;
}