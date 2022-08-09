#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <vector>
#include <glm/gtx/quaternion.hpp>
#include <glm/common.hpp>
#include "glm/glm.hpp"
#include <string>

#ifndef SHADER_H
#define SHADER_H

class Shader{

protected:

    int screenWidth = 1920;
    int screenHeight = 1080;

    GLuint programID;
    glm::mat4 VP, V, P;

    glm::mat4 getModel();
    void setMatrixUniforms();
    void setColorUniforms();

    virtual void setCustomUniforms() = 0;

public:
    glm::vec3 position, scale, color;
    glm::vec2 rotateOffset;
    float rotation = 0.0f;
    float alpha = 1.0f;
    bool mirror = false;

    Shader(GLuint _programID = 0);
    virtual ~Shader();

    void setScale(int _width, int _height);
    void setUniforms();
    void setProgram(GLuint _programID);
    void setPosition(glm::vec3 _position);
    void setViewProjectionMatrix(int _width, int _height);
    void setViewProjectionMatrix(glm::mat4 &_VP, glm::mat4 &_V, glm::mat4 &_P);
    void setRotation(float _rotation);


};

#endif