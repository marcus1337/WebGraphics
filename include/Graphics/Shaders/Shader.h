
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
#include "Model.h"

class Shader{

protected:
    IOShader& ioShader;
    int screenWidth = 1920;
    int screenHeight = 1080;

    std::string programName;
    Camera camera;
    void setMatrixUniforms();
    void setColorUniforms();
    void setExtraUniforms();
    virtual void setCustomUniforms() = 0;
    std::map<std::string, float> extraFloatUniforms;
    Model model;

public:
    glm::vec3 color;
    float alpha = 1.0f;
    float effect = 0.0f;

    Shader(std::string programName);
    virtual ~Shader();

    void setModel(Model _model);
    void setCamera(Camera _camera);
    void setProgram(std::string _programName);
    void setUniforms();
    void setFloatUniform(std::string name, float value);

};

#endif