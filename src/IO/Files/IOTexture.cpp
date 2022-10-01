#include "IOTexture.h"

#include <filesystem>
#include <fstream>

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <map>
#include "lodepng.h"

#include "FolderPaths.h"

IOTexture::IOTexture()
{

}

IOTexture::~IOTexture() {
    for (auto& textureObj : textures)
        glDeleteTextures(1, &std::get<1>(textureObj));
}

std::vector<std::string> IOTexture::getAllTextureNames() {
    std::string rootFolder = FolderPaths::getTexturesPath();
    std::vector<std::string> texturePaths;

#ifndef EMSCRIPTEN
    for (const auto& entry : std::filesystem::recursive_directory_iterator(rootFolder)) {
        if (entry.is_regular_file()) {
            std::string imgPath = entry.path().string();
            std::size_t strSize = rootFolder.size() - imgPath.size();
            imgPath = imgPath.substr(rootFolder.size(), strSize);
            std::string strToRemove = "\\";
            while (imgPath.find(strToRemove) != std::string::npos) {
                imgPath.replace(imgPath.find(strToRemove), strToRemove.size(), "//");
            }
            texturePaths.push_back(imgPath);
        }   
    }
#endif
    return texturePaths;
}

GLFWimage IOTexture::loadIconImage(const std::string &fileName)
{
    std::string filePathAndName = FolderPaths::getTexturesPath() + fileName;
    unsigned error;
    GLFWimage image;
    error = lodepng_decode32_file(&(image.pixels), (unsigned int *)&(image.width), (unsigned int *)&(image.height), filePathAndName.c_str());
    if (error) {
        printf("error %u: %s\n", error, lodepng_error_text(error));
        std::cout << "filename: " << fileName << "\n";
    }
    return image;
}

TextureData IOTexture::getTextureData(const std::string& fileName){
    TextureData textureData;
    textureData.fileName = fileName;
    std::string filePathAndName = FolderPaths::getTexturesPath() + fileName;
    textureData.error = lodepng::decode(textureData.data, textureData.width, textureData.height, filePathAndName);
    if (textureData.error != 0)
    {
        std::clog << "File: " << fileName << " Error: " << lodepng_error_text(textureData.error) << std::endl;
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

void IOTexture::preloadTextures() {
    std::vector<std::string> textureNames = getAllTextureNames();
    for (std::string textureName : textureNames) {
        getTexture(textureName);
        // std::cout << "loaded: " << textureName << "\n";
    }
}

GLuint IOTexture::getTexture(TextureData& textureData)
{
    if (textures.contains(textureData.fileName))
        return textures[textureData.fileName];
    return makeTexture(textureData);
}

GLuint IOTexture::getTexture(std::string name) {
    for (TextureData& textureInfo : textureInfos) {
        if (textureInfo.fileName == name)
            return getTexture(textureInfo);
    }
    TextureData textureInfo = getTextureData(name);
    if (textureInfo.error != 0) {
        return 0;
    }
    textureInfos.push_back(textureInfo);
    return getTexture(textureInfo);
}

GLuint IOTexture::makeTexture(TextureData& textureData)
{
    GLuint textID = 0;
    textID = load2DTexture(textureData);
    textureData.data.clear(); //free up some RAM
    if (textID != 0)
        textures[textureData.fileName] = textID;
    return textID;
}

