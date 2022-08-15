#include "Drawable.h"

Drawable::Drawable(Engine& _engine, Shader& _shader) : engine(_engine), graphics(_engine.graphics), mouse(_engine.window.mouse), shader(&_shader)
{};

Drawable::~Drawable() {

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
    shader->setViewProjectionMatrix(_width, _height);
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
