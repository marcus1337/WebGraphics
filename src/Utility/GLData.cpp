
#include "GLData.h"

GLData::GLData()
{
    preloadTextures();
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

GLuint GLData::makeTexture(TextureData &textureData)
{
    GLuint textID = 0;
    textID = load2DTexture(textureData);
    textureData.data.clear(); //free up some RAM
    if (textID != 0)
        textures[textureData.fileName] = textID;
    return textID;
}
GLuint GLData::makeProgram(ShaderData &shaders)
{
    GLuint programID = 0;
    programID = loadShaderProgram(shaders.shaders);
    if (programID != 0)
        programs[shaders.name] = programID;
    return programID;
}

GLuint GLData::getTexture(TextureData &textureData)
{
    if (textures.contains(textureData.fileName))
        return textures[textureData.fileName];
    return makeTexture(textureData);
}

GLuint GLData::getTexture(std::string name){
    for(TextureData& textureInfo : textureInfos){
        if(textureInfo.fileName == name)
            return getTexture(textureInfo);
    }
    TextureData textureInfo = iotexture.getTextureData(name);
    if (textureInfo.error != 0) {
        return 0;
    }
    textureInfos.push_back(textureInfo);
    return getTexture(textureInfo);
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
    for (auto &textureObj : textures)
        glDeleteTextures(1, &std::get<1>(textureObj));
}

void GLData::preloadTextures() {
    std::vector<std::string> textureNames = iotexture.getAllTextureNames();
    for (std::string textureName : textureNames) {
        getTexture(textureName);
       // std::cout << "loaded: " << textureName << "\n";
    }
}

//////IO/////////
void GLData::printCompileError(GLuint shader)
{
    std::cerr << "Shader compilation failed, " << shader << std::endl;
    GLint infoLogLength = 0;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
    std::vector<char> infoLog(infoLogLength);
    glGetShaderInfoLog(shader, infoLogLength, &infoLogLength, &infoLog[0]);
    std::string infoLogStr(infoLog.begin(), infoLog.end());
    std::cerr << infoLogStr << std::endl;
}

void GLData::printLinkError(GLuint program)
{
    std::cerr << "Program linking failed, " << program << std::endl;
    GLint infoLogLength = 0;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);
    std::vector<char> infoLog(infoLogLength);
    glGetProgramInfoLog(program, infoLogLength, &infoLogLength, &infoLog[0]);
    std::string infoLogStr(infoLog.begin(), infoLog.end());
    std::cerr << infoLogStr << std::endl;
}

bool GLData::wasShaderCompiled(GLuint shader)
{
    GLint compiled = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    return compiled != 0;
}

GLuint GLData::linkProgram(std::vector<GLuint> shaders)
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

GLuint GLData::compileShader(const ShaderCode& shaderInfo)
{
    const char* shaderCode = shaderInfo.glslCode.c_str();
    GLuint shader = glCreateShader(shaderInfo.shaderType);
    glShaderSource(shader, 1, &shaderCode, nullptr);
    glCompileShader(shader);
    return shader;
}

std::vector<GLuint> GLData::compileShaders(std::vector<ShaderCode>& shaderInfos)
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

GLuint GLData::loadShaderProgram(std::vector<ShaderCode>& shaderInfos)
{
    std::vector<GLuint> shaders = compileShaders(shaderInfos);
    if (shaders.empty())
        return 0;
    return linkProgram(shaders);
}

GLuint GLData::load2DTexture(const TextureData& textureData)
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