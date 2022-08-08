
#include "GLData.h"
#include "GLUtils.h"

GLData::GLData()
{
    preloadTextures();
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
    textID = GLUtils::load2DTexture(textureData);
    textureData.data.clear(); //free up some RAM
    if (textID != 0)
        textures[textureData.fileName] = textID;
    return textID;
}
GLuint GLData::makeProgram(ShaderData &shaders)
{
    GLuint programID = 0;
    programID = GLUtils::loadShaderProgram(shaders.shaders);
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