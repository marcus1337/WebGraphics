#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <vector>

#include "Utility/GLData.h"

#ifndef FLOOR_H
#define FLOOR_H

class Image {
    
    void initVBO();
    glm::mat4 getMVP();
    glm::mat4 getModel();

    glm::mat4 VP, V, P;
    GLData* glData;

public:

    glm::vec3 cameraPosition;
    glm::vec3 position, scale;
    glm::vec3 rotationAxis;
    float rotation;
    float alpha = 1.0f;

    GLuint programID = -1;
    GLuint textureID = -1;
    GLuint normalID = -1;
    bool isNormalUsed = false;
    GLuint vbo;

    glm::vec2 textureSize, textureCorner;
    void setTextureArea(glm::vec2 _textureSize, glm::vec2 _textureCorner);

    Image();
    ~Image();
    void setPosition(glm::vec3 _position);
    void setMidPosition(glm::vec3 _midPosition);

    void init(GLData& _gldata);
    void setViewProjectionMatrix(glm::mat4& _VP, glm::mat4& _V, glm::mat4& _P);

    void cleanup();
    void draw();

    void setProgram(GLData::Program program);
    void setTexture(GLData::Texture texture);
    void setNormal(GLData::Texture texture);
    void setNormalOnOff(bool _on);
};


#endif