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

    //Delete copy constructor and assignment operator for now as I might not need them and including them requires extra work and code.
    //There is also a "cost of carry" for having extra code for this.
    Drawable& operator=(const Drawable&) = delete;
    Drawable() = delete;
    Drawable(const Drawable&) = delete;
public:
    Shader* shader = nullptr;
    Drawable(Engine& _engine);
    virtual ~Drawable();
    virtual void render() = 0;

    void setPosition(int _x, int _y);
    void setSize(int _width, int _height);
    void setColor(glm::vec3 _color);
    void setAlpha(float _alpha);
    void setRotation(float _rotation);
    void setViewProjectionMatrix(int _width, int _height);
    int getX();
    int getY();
    int getWidth();
    int getHeight();
    void setShaderProgram(std::string shaderProgramName);
};

#endif