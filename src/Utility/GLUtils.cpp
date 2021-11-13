
#include "GLUtils.h"


void GLUtils::showShaderInfoLog(GLuint shader)
{
    GLint infoLogLength = 0;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
    std::vector<char> infoLog(infoLogLength);
    glGetShaderInfoLog(shader, infoLogLength, &infoLogLength, &infoLog[0]);
    std::string infoLogStr(infoLog.begin(), infoLog.end());
    std::cerr << infoLogStr << std::endl;
}

void GLUtils::showProgramInfoLog(GLuint program)
{
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
    if (!compiled)
    {
        std::clog << "Shader compilation failed, " << shader << std::endl;
        showShaderInfoLog(shader);
    }
    return compiled != 0;
}

GLuint GLUtils::linkProgram(std::vector<GLuint> shaders)
{
    GLuint program = glCreateProgram();

    for (GLuint shader : shaders)
    {
        glAttachShader(program, shader);
    }
    glLinkProgram(program);

    GLint linked = 0;
    glGetProgramiv(program, GL_LINK_STATUS, &linked);
    if (!linked)
    {
        std::cerr << "Program linking failed, " << program << std::endl;
        showProgramInfoLog(program);
        glDeleteProgram(program);
    }

    for (GLuint shader : shaders)
    {
        glDetachShader(program, shader);
        glDeleteShader(shader);
    }

    if (!linked)
        return 0;

    return program;
}

GLuint GLUtils::compileShader(const std::tuple<std::string, uint32_t>& shaderInfo)
{
    const char* shaderCode = std::get<0>(shaderInfo).c_str();
    uint32_t shaderType = std::get<1>(shaderInfo);
    GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &shaderCode, nullptr);
    glCompileShader(shader);
    return shader;
}

std::vector<GLuint> GLUtils::compileShaders(std::vector<std::tuple<std::string, uint32_t>> shaderInfos)
{
    std::vector<GLuint> shaders;
    shaders.reserve(shaderInfos.size());
    for (std::size_t i = 0; i < shaderInfos.size(); i++)
    {
        GLuint shader = compileShader(shaderInfos[i]);
        shaders.push_back(shader);

        if (!wasShaderCompiled(shader))
        {
            for(GLuint tmpShader : shaders)
                glDeleteShader(shader);
            return std::vector<GLuint>();
        }
    }
    return shaders;
}

GLuint GLUtils::loadShaderProgram(std::vector<std::tuple<std::string,uint32_t>> shaderInfos)
{
    std::vector<GLuint> shaders = compileShaders(shaderInfos);
    if(shaders.empty())
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