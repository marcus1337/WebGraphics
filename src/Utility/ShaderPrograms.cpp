#include "ShaderPrograms.h"

ShaderPrograms::ShaderPrograms() {
    reload();
    std::cout << "ShaderPrograms()\n";
}
ShaderPrograms::~ShaderPrograms() {
    for (auto& programObj : programs)
        glDeleteProgram(std::get<1>(programObj));
}

void ShaderPrograms::reload() {
    for (auto& programObj : programs)
        glDeleteProgram(std::get<1>(programObj));
    programs.clear();
    ioshader.loadData();
}

GLuint ShaderPrograms::makeProgram(ShaderData& shaders)
{
    GLuint programID = 0;
    programID = shaderCompiler.loadShaderProgram(shaders.shaders);
    if (programID != 0)
        programs[shaders.name] = programID;
    return programID;
}


GLuint ShaderPrograms::getProgram(ShaderData shaders)
{
    if (programs.contains(shaders.name))
        return programs[shaders.name];
    return makeProgram(shaders);
}

GLuint ShaderPrograms::get(std::string name) {
    if (!ioshader.shaderDataExists(name))
        std::cout << "Error: shader not found (" << name << ")\n";
    return getProgram(ioshader.getShaderData(name));
}