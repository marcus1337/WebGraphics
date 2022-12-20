#include "ShaderPrograms.h"

ShaderPrograms::ShaderPrograms() {
}

ShaderPrograms::~ShaderPrograms() {
    deletePrograms();
}

void ShaderPrograms::deletePrograms() {
    for (auto& programObj : programs)
        glDeleteProgram(std::get<1>(programObj));
    programs.clear();
}

void ShaderPrograms::load(std::vector<ShaderCodeSet> shaderCodeSets) {
    deletePrograms();
    for (ShaderCodeSet& shaderCodeSet : shaderCodeSets) {
        makeProgram(shaderCodeSet);
    }
}

void ShaderPrograms::makeProgram(ShaderCodeSet& shaderCodeSet) {
    GLuint programID = shaderCompiler.loadShaderProgram(shaderCodeSet.shaders);
    if (programID != 0)
        programs[shaderCodeSet.name] = programID;
}

GLuint ShaderPrograms::get(std::string name) {
    if (!programs.contains(name)) {
        std::cout << "Error: shader program not found (" << name << ")\n";
        return 0;
    }
    return programs[name];
}