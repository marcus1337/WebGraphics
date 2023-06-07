
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
#include <memory>
#include <tuple>
#include <array>

class Shader{

protected:
    IOShader& ioShader;
    std::string programName;
    Camera camera;
    void setMatrixUniforms();
    void setColorUniforms();
    void setExtraUniforms();
    void setTextureUniforms();
    virtual void setCustomUniforms() = 0;
    std::map<std::string, float> extraFloatUniforms;
    Model model;

    std::vector<std::pair<GLuint, std::string>> textures;

public:
    static std::string getDefaultShaderTextureName();
    glm::vec3 color;
    float alpha = 1.0f;

    Shader(std::string programName);
    virtual ~Shader();

    void setViewSize(int width, int height);
    void setModel(Model _model);
    void setProgram(std::string _programName);
    void setUniforms();
    void setFloatUniform(std::string name, float value);
    void setMatricesUniform(const std::string& name, const std::vector<glm::mat4>& arr);

    void setTexture(std::string textureName, std::string shaderName);
    void setTexture(GLuint _texture, std::string shaderName);
    void setTextures(std::vector<std::pair<std::string, std::string>> _textures);
};

#endif