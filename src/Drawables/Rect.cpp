#include "Rect.h"

void Rect::render(Graphics& _graphics){
    _graphics.rectangleShader.setPosition(glm::vec3(x, y, 0.0f));
    _graphics.rectangleShader.scale = glm::vec3(width, height, 1.0f);
    _graphics.rectangleShader.alpha = alpha;
    _graphics.rectangleShader.rotation = rotation;
    _graphics.rectangleShader.color = color;
    _graphics.imageObject.draw(_graphics.rectangleShader);
}