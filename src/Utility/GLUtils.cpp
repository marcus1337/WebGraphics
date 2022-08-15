
#include "GLUtils.h"


void GLUtils::printCompileError(GLuint shader)
{
    std::cerr << "Shader compilation failed, " << shader << std::endl;
    GLint infoLogLength = 0;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
    std::vector<char> infoLog(infoLogLength);
    glGetShaderInfoLog(shader, infoLogLength, &infoLogLength, &infoLog[0]);
    std::string infoLogStr(infoLog.begin(), infoLog.end());
    std::cerr << infoLogStr << std::endl;
}

void GLUtils::printLinkError(GLuint program)
{
    std::cerr << "Program linking failed, " << program << std::endl;
    GLint infoLogLength = 0;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);
    std::vector<char> infoLog(infoLogLength);
    glGetProgramInfoLog(program, infoLogLength, &infoLogLength, &infoLog[0]);
    std::string infoLogStr(infoLog.begin(), infoLog.end());
    std::cerr << infoLogStr << std::endl;
}

bool GLUtils::wasShaderCompiled(GLuint shader)
{
    GLint compiled = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    return compiled != 0;
}

GLuint GLUtils::linkProgram(std::vector<GLuint> shaders)
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

GLuint GLUtils::compileShader(const ShaderCode& shaderInfo)
{
    const char* shaderCode = shaderInfo.glslCode.c_str();
    GLuint shader = glCreateShader(shaderInfo.shaderType);
    glShaderSource(shader, 1, &shaderCode, nullptr);
    glCompileShader(shader);
    return shader;
}

std::vector<GLuint> GLUtils::compileShaders(std::vector<ShaderCode>& shaderInfos)
{
    std::vector<GLuint> shaders;
    shaders.reserve(shaderInfos.size());
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

GLuint GLUtils::loadShaderProgram(std::vector<ShaderCode>& shaderInfos)
{
    std::vector<GLuint> shaders = compileShaders(shaderInfos);
    if (shaders.empty())
        return 0;
    return linkProgram(shaders);
}

GLuint GLUtils::load2DTexture(const TextureData& textureData)
{
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, textureData.width, textureData.height, 0, GL_RGBA,
        GL_UNSIGNED_BYTE, &(textureData.data[0]));
    glBindTexture(GL_TEXTURE_2D, 0);
    return texture;
}