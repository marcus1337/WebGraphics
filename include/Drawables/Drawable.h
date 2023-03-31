
#ifndef DRAWABLE_H
#define DRAWABLE_H
#include <functional>
#include <Graphics/Graphics.h>
#include <IO/Files/IOContainer.h>
#include <Graphics/Shaders/Shader.h>
#include <Graphics/Shaders/ImageShader.h>
#include <Graphics/Shaders/TextShader.h>

class Drawable {
    Shader* shader = nullptr;
protected:
    Graphics& graphics;

public:
    Drawable(Graphics& _graphics, IOContainer& _ioContainer, Shader& _shader);
    Drawable(const Drawable&) = delete;
    virtual ~Drawable();
    virtual void render() = 0;

    void setEffect(float _effect);
    void setCenterPosition(int _x, int _y);
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
    void setUniform(std::string key, float value);

};

#endif