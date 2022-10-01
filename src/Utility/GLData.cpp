
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
    ioshader.loadData();
}


GLuint GLData::makeProgram(ShaderData &shaders)
{
    GLuint programID = 0;
    programID = shaderCompiler.loadShaderProgram(shaders.shaders);
    if (programID != 0)
        programs[shaders.name] = programID;
    return programID;
}


GLuint GLData::getProgram(ShaderData shaders)
{
    if (programs.contains(shaders.name))
        return programs[shaders.name];
    return makeProgram(shaders);
}

GLuint GLData::getProgram(std::string name) {
    if (!ioshader.shaderDataExists(name))
        std::cout << "Error: shader not found (" << name << ")\n";
    return getProgram(ioshader.getShaderData(name));
}

GLData::~GLData()
{
    for (auto &programObj : programs)
        glDeleteProgram(std::get<1>(programObj));
}

GLuint GLData::getTexture(std::string name) {
    return iotexture.getTexture(name);
}