#include "Drawable.h"

Drawable::Drawable(Engine& _engine) : engine(_engine), graphics(_engine.graphics), mouse(_engine.window.mouse)
{};

Drawable::~Drawable() {
    delete shader;
}

void Drawable::setPosition(int _x, int _y) {
    shader->setPosition(glm::vec3(_x, _y, 0.0f));
}
void Drawable::setSize(int _width, int _height) {
    shader->scale = glm::vec3(_width, _height, 1.0f);
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