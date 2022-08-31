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
    Shader* shader = nullptr;
protected:
    Engine& engine;
    Graphics& graphics;
    Mouse& mouse;

public:
    Drawable(Engine& _engine, Shader& _shader);
    Drawable(const Drawable&) = delete;
    virtual ~Drawable();
    virtual void render() = 0;

    void setEffect(float _effect);
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