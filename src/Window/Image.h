#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <vector>

#include "Utility/GLData.h"

#include <glm/gtx/quaternion.hpp>
#include <glm/common.hpp>
#include "glm/glm.hpp"


#ifndef FLOOR_H
#define FLOOR_H

class Image
{
    void initVBO();
    glm::mat4 getModel();

    glm::mat4 VP, V, P;

    void setProgram(GLuint program);
    void setTexture(GLuint texture);
    void setNormal(GLuint texture);
    GLuint programID = -1;
    GLuint textureID = -1;
    GLuint normalID = -1;

    void setTextureUniforms();
    void setMatrixUniforms();
    void setColorUniforms();
    void setClippingUniforms();
    void setUniforms();

    GLuint vao;
    GLuint vbo;

public:
    glm::vec3 cameraPosition;
    glm::vec3 position, scale;
    glm::quat rotation;

    float alpha = 1.0f;
    bool isNormalUsed = false;

    glm::vec2 textureSize, textureCorner;
    void setTextureArea(glm::vec2 _textureSize, glm::vec2 _textureCorner);

    Image();
    ~Image();
    void setPosition(glm::vec3 _position);
    void setMidPosition(glm::vec3 _midPosition);

    void setViewProjectionMatrix(glm::mat4 &_VP, glm::mat4 &_V, glm::mat4 &_P);

    void draw(GLuint _program, GLuint _texture, GLuint _normal = 0);
    void setNormalOnOff(bool _on);
};

#endif