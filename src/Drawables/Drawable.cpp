#include "Drawables/Drawable.h"
#include "Engine/Engine.h"

Drawable::Drawable(Shader& _shader) : shader(&_shader), objectContainer(ObjectContainer::getInstance())
{

};

Drawable::~Drawable() {

}

void Drawable::setCenterPosition(int _x, int _y) {
    shader->setPosition(_x - getWidth()/2, _y - getHeight() / 2);
}
void Drawable::setPosition(int _x, int _y) {
    shader->setPosition(_x, _y);
}
void Drawable::setSize(int _width, int _height) {
    shader->setScale(_width, _height);
}
void Drawable::setColor(glm::vec3 _color) {
    shader->color = _color;
}
void Drawable::setAlpha(float _alpha) {
    shader->alpha = _alpha;
}
void Drawable::setRotation(float _rotation) {
    shader->rotation = _rotation;
}
void Drawable::setViewProjectionMatrix(int _width, int _height) {
    Camera camera;
    camera.setScreenSize(_width, _height);
    shader->setCamera(camera);
}
int Drawable::getX() {
    return shader->getX();
}
int Drawable::getY() {
    return shader->getY();
}
int Drawable::getWidth() {
    return shader->getWidth();
}
int Drawable::getHeight() {
    return shader->getHeight();
}
void Drawable::setShaderProgram(std::string shaderProgramName) {
    shader->setProgram(shaderProgramName);
}
void Drawable::setEffect(float _effect) {
    shader->effect = _effect;
}

void Drawable::setUniform(std::string key, float value) {
    shader->setFloatUniform(key, value);
}
