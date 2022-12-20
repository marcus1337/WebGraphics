#include "IOTexture.h"

#include <filesystem>
#include <fstream>

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <map>
#include "lodepng.h"

IOTexture::IOTexture()
{

}

IOTexture::~IOTexture() {
    deleteTextures();
}

void IOTexture::deleteTextures() {
    for (auto& textureHandleKeyValue : loadedTextureHandles)
        glDeleteTextures(1, &std::get<1>(textureHandleKeyValue));
    loadedTextureHandles.clear();
}

void IOTexture::loadTextures(std::vector<std::string> textureFilePaths, std::vector<std::string> textureNames) {
    deleteTextures();
    for (int i = 0; i < textureFilePaths.size(); i++) {
        std::string textureFilePath = textureFilePaths[i];
        std::string textureName = textureNames[i];
        TextureData textureData = getTextureData(textureFilePath, textureName);

        std::cout << "loadTexture " << textureName << " [" << textureFilePath << "]\n";
        makeTexture(textureData);
    }
}

void IOTexture::loadIconImage(std::string filePath)
{
    unsigned error;
    GLFWimage image;
    error = lodepng_decode32_file(&(image.pixels), (unsigned int *)&(image.width), (unsigned int *)&(image.height), filePath.c_str());
    if (error) {
        printf("Icon load error %u: %s\n", error, lodepng_error_text(error));
        std::cout << "Icon load path: " << filePath << "\n";
    }
    iconImage = image;
}

TextureData IOTexture::getTextureData(std::string textureFilePath, std::string textureName){
    TextureData textureData;
    textureData.name = textureName;
    unsigned error = lodepng::decode(textureData.data, textureData.width, textureData.height, textureFilePath);
    if (error != 0)
    {
        std::cerr << "Texture load error: " << textureFilePath << " Error: " << lodepng_error_text(error) << std::endl;
    }
    return textureData;
}

GLuint IOTexture::load2DTexture(const TextureData& textureData)
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

GLuint IOTexture::getTexture(std::string name) {
    if (loadedTextureHandles.contains(name))
        return loadedTextureHandles[name];
    std::cout << "getTexture() error: " << name << " does not exist or isn't loaded.\n";
    return 0;
}

void IOTexture::makeTexture(TextureData& textureData)
{
    GLuint textureHandle = 0;
    textureHandle = load2DTexture(textureData);
    textureData.data.clear(); //free up some RAM
    if (textureHandle != 0)
        loadedTextureHandles[textureData.name] = textureHandle;
}

