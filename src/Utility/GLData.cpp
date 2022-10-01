
#include "GLData.h"

GLData::GLData()
{
    iotexture.preloadTextures();
    loadShaderCodeStrings();
    std::cout << "GLData()\n";
}

void GLData::loadShaderCodeStrings() {
    for (auto& programObj : programs)
        glDeleteProgram(std::get<1>(programObj));
    programs.clear();
    shaders = ioshader.getShaderData();
    for (auto& s : shaders) {
        std::cout << "Shader name: " << s.name << "\n";
    }
}

GLuint GLData::getProgram(std::string name){
    for(auto& shader : shaders){
        if(shader.name == name)
            return getProgram(shader);
    }
    std::cout << "Error: shader not found (" << name << ")\n";
    return 0;
}

GLuint GLData::makeProgram(ShaderData &shaders)
{
    GLuint programID = 0;
    programID = shaderCompiler.loadShaderProgram(shaders.shaders);
    if (programID != 0)
        programs[shaders.name] = programID;
    return programID;
}


GLuint GLData::getProgram(ShaderData &shaders)
{
    if (programs.contains(shaders.name))
        return programs[shaders.name];
    return makeProgram(shaders);
}

GLData::~GLData()
{
    for (auto &programObj : programs)
        glDeleteProgram(std::get<1>(programObj));
}

GLuint GLData::getTexture(std::string name) {
    return iotexture.getTexture(name);
}