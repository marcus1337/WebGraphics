#include <functional>
#include "IO/Controller/Mouse.h"
#include <Engine/Graphics.h>
#include <Engine/Engine.h>
#include <Graphics/Shaders/Shader.h>
#include <Graphics/Shaders/ImageShader.h>
#include <Graphics/Shaders/TextShader.h>

#ifndef DRAWABLE_H
#define DRAWABLE_H

class Drawable {

protected:
    Engine& engine;
    Graphics& graphics;
    Mouse& mouse;
    Shader* shader = nullptr;

public:
    Drawable(Engine& _engine);
    virtual ~Drawable();
    virtual void render() = 0;

    void setPosition(int _x, int _y);
    void setSize(int _width, int _height);
    void setColor(glm::vec3 _color);
    void setAlpha(float _alpha);
    void setRotation(float _rotation);

};

#endif