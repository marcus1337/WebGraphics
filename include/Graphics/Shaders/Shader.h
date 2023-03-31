
#ifndef SHADER_H
#define SHADER_H
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <vector>
#include <glm/gtx/quaternion.hpp>
#include <glm/common.hpp>
#include "glm/glm.hpp"
#include <string>
#include "IO/Files/Shader/IOShader.h"
#include <map>

class Shader{

    glm::mat4 getViewMatrix();
    glm::mat4 getOrthographicProjectionMatrix(int windowWidth, int windowHeight);
    glm::mat4 getUIViewProjectionMatrix(int windowWidth, int windowHeight);

protected:
    IOShader& ioShader;
    int screenWidth = 1920;
    int screenHeight = 1080;

    std::string programName;
    glm::mat4 VP, V, P;

    glm::mat4 getModel();
    void setMatrixUniforms();
    void setColorUniforms();
    void setExtraUniforms();
    virtual void setCustomUniforms() = 0;
    glm::vec3 position, scale;
    void setViewProjectionMatrix(glm::mat4& _VP, glm::mat4& _V, glm::mat4& _P);

    std::map<std::string, float> extraFloatUniforms;

public:
    glm::vec3 color;
    glm::vec2 rotateOffset;
    float rotation = 0.0f;
    float alpha = 1.0f;
    bool mirror = false;
    float effect = 0.0f;

    Shader(IOShader& _ioShader, std::string programName);
    virtual ~Shader();

    void setProgram(std::string _programName);
    void setScale(int _width, int _height);
    void setUniforms();
    void setPosition(int _x, int _y);
    void setViewProjectionMatrix(int _width, int _height);
    void setRotation(float _rotation);
    
    int getX();
    int getY();
    int getWidth();
    int getHeight();

    void setFloatUniform(std::string name, float value);

};

#endif