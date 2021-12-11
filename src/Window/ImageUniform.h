#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <vector>
#include <glm/gtx/quaternion.hpp>
#include <glm/common.hpp>
#include "glm/glm.hpp"

#ifndef IMAGE_UNIFORM_H
#define IMAGE_UNIFORM_H

class ImageUniform{

    glm::mat4 VP, V, P;
    GLuint programID;
    GLuint textureID;
    GLuint normalID;

    glm::mat4 getModel();
    void setTextureUniforms();
    void setMatrixUniforms();
    void setColorUniforms();
    void setClippingUniforms();

protected:
    virtual void setCustomUniforms() {};

public:
    ImageUniform(GLuint _programID);
    virtual ~ImageUniform();

    void setUniforms();

    glm::vec3 position, scale;
    glm::quat rotation;
    float alpha = 1.0f;
    bool isNormalUsed = false;
    glm::vec2 textureSize, textureCorner;

    void setProgram(GLuint _programID);
    void setTexture(GLuint _textureID);
    void setNormal(GLuint _textureID);
    void setPosition(glm::vec3 _position);
    void setMidPosition(glm::vec3 _midPosition);
    void setTextureArea(glm::vec2 _textureSize, glm::vec2 _textureCorner);
    void setViewProjectionMatrix(glm::mat4 &_VP, glm::mat4 &_V, glm::mat4 &_P);

};

#endif