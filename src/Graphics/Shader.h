#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <vector>
#include <glm/gtx/quaternion.hpp>
#include <glm/common.hpp>
#include "glm/glm.hpp"
#include <string>

#ifndef IMAGE_UNIFORM_H
#define IMAGE_UNIFORM_H

class Shader{

    glm::mat4 VP, V, P;
    GLuint textureID;
    GLuint normalID;

    glm::mat4 getModel();
    void setTextureUniforms();
    void setMatrixUniforms();
    void setColorUniforms();
    void setClippingUniforms();

protected:
    GLuint programID;
    virtual void setCustomUniforms() {};

public:
    Shader(GLuint _programID = 0);
    virtual ~Shader();

    void setUniforms();

    glm::vec3 position, scale, color;
    float rotation = 0.0f;
    float alpha = 1.0f;
    bool isNormalUsed = false;
    bool isSingleColor = false;
    glm::vec2 textureSize, textureCorner;

    void setProgram(GLuint _programID);
    void setTexture(GLuint _textureID);
    void setNormal(GLuint _textureID);
    void setPosition(glm::vec3 _position);
    void setTextureArea(glm::vec2 _textureSize, glm::vec2 _textureCorner);
    void setViewProjectionMatrix(glm::mat4 &_VP, glm::mat4 &_V, glm::mat4 &_P);

    void setUniform(std::string name, glm::vec3 value);
    void setUniform(std::string name, glm::vec2 value);
    void setUniform(std::string name, float value);

    void setRotation(float _rotation);
};

#endif