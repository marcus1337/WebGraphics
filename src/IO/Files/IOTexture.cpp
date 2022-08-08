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