
#ifndef DRAWABLE_H
#define DRAWABLE_H
#include <functional>
#include <Graphics/Graphics.h>
#include <IO/Files/IOContainer.h>
#include <Graphics/Shaders/Shader.h>
#include <Graphics/Shaders/ImageShader.h>
#include <Graphics/Shaders/TextShader.h>
#include "Graphics/Objects/ObjectContainer.h"
#include "Graphics/Shaders/Camera.h"
#include "Graphics/Shaders/Model.h"

class Drawable {
    Shader* shader = nullptr;
protected:
    Model model;
    ObjectContainer& objectContainer;
public:
    Drawable(Shader& _shader);
    Drawable(const Drawable&) = delete;
    virtual ~Drawable();
    virtual void render() = 0;
    void setCenterPosition(int _x, int _y);
    void setPosition(int _x, int _y);
    void setSize(int _width, int _height);
    void setPosition(glm::vec3 _position);
    void setSize(glm::vec3 _size);
    void setColor(glm::vec3 _color);
    void setAlpha(float _alpha);
    void setRotation(glm::vec3 rotation);
    int getX();
    int getY();
    int getWidth();
    int getHeight();
    void setShaderProgram(std::string shaderProgramName);
    void setUniform(std::string key, float value);

};

#endif