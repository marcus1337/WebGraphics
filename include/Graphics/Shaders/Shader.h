
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
#include "Camera.h"

class Shader{

protected:
    IOShader& ioShader;
    int screenWidth = 1920;
    int screenHeight = 1080;

    std::string programName;
    Camera camera;

    glm::mat4 getScaleMatrix(glm::vec3 scale, bool mirror);
    glm::mat4 getRotationMatrix(float rotation, glm::vec3 rotationAxis, glm::vec2 rotateOffset);
    glm::mat4 getTranslationMatrix(glm::vec3 position, glm::vec3 scale);

    glm::mat4 getModel();
    void setMatrixUniforms();
    void setColorUniforms();
    void setExtraUniforms();
    virtual void setCustomUniforms() = 0;
    glm::vec3 position, scale;

    std::map<std::string, float> extraFloatUniforms;

public:
    glm::vec3 color;
    glm::vec2 rotateOffset;
    float rotation = 0.0f;
    float alpha = 1.0f;
    bool mirror = false;
    float effect = 0.0f;

    Shader(std::string programName);
    virtual ~Shader();

    void setCamera(Camera _camera);
    void setProgram(std::string _programName);
    void setScale(int _width, int _height);
    void setUniforms();
    void setPosition(int _x, int _y);
    void setRotation(float _rotation);
    
    int getX();
    int getY();
    int getWidth();
    int getHeight();

    void setFloatUniform(std::string name, float value);

};

#endif