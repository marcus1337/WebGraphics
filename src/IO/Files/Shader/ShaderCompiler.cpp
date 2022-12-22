#include "ShaderCompiler.h"
#include <iostream>

void ShaderCompiler::printCompileError(GLuint shader)
{
    std::cerr << "Shader compilation failed, " << shader << std::endl;
    GLint infoLogLength = 0;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
    std::vector<char> infoLog(infoLogLength);
    glGetShaderInfoLog(shader, infoLogLength, &infoLogLength, &infoLog[0]);
    std::string infoLogStr(infoLog.begin(), infoLog.end());
    std::cerr << infoLogStr << std::endl;
}

void ShaderCompiler::printLinkError(GLuint program)
{
    std::cerr << "Program linking failed, " << program << std::endl;
    GLint infoLogLength = 0;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);
    std::vector<char> infoLog(infoLogLength);
    glGetProgramInfoLog(program, infoLogLength, &infoLogLength, &infoLog[0]);
    std::string infoLogStr(infoLog.begin(), infoLog.end());
    std::cerr << infoLogStr << std::endl;
}

bool ShaderCompiler::wasShaderCompiled(GLuint shader)
{
    GLint compiled = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    return compiled != 0;
}

GLuint ShaderCompiler::linkProgram(std::vector<GLuint> shaders)
{
    GLuint program = glCreateProgram();
    for (GLuint shader : shaders)
        glAttachShader(program, shader);
    glLinkProgram(program);
    GLint linked = 0;
    glGetProgramiv(program, GL_LINK_STATUS, &linked);

    for (GLuint shader : shaders)
    {
        glDetachShader(program, shader);
        glDeleteShader(shader);
    }

    if (!linked)
    {
        printLinkError(program);
        glDeleteProgram(program);
        return 0;
    }
    return program;
}

GLuint ShaderCompiler::compileShader(const ShaderCode& shaderInfo)
{
    const char* shaderCode = shaderInfo.glslCode.c_str();
    GLuint shader = glCreateShader(shaderInfo.shaderType);
    glShaderSource(shader, 1, &shaderCode, nullptr);
    glCompileShader(shader);
    return shader;
}

std::vector<GLuint> ShaderCompiler::compileShaders(std::vector<ShaderCode>& shaderInfos)
{
    std::vector<GLuint> shaders;
    for (std::size_t i = 0; i < shaderInfos.size(); i++)
    {
        GLuint shader = compileShader(shaderInfos[i]);
        shaders.push_back(shader);
        if (!wasShaderCompiled(shader))
        {
            printCompileError(shader);
            for (GLuint tmpShader : shaders)
                glDeleteShader(shader);
            return std::vector<GLuint>();
        }
    }
    return shaders;
}

GLuint ShaderCompiler::loadShaderProgram(std::vector<ShaderCode>& shaderInfos)
{
    std::vector<GLuint> shaders = compileShaders(shaderInfos);
    if (shaders.empty())
        return 0;
    return linkProgram(shaders);
}