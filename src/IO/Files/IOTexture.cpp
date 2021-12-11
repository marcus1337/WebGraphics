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
#ifdef EMSCRIPTEN
    binFolderPath = "./res/";
    texturePath = binFolderPath + "textures/";
    normalTexturePath = texturePath + "normals/";
#else
    binFolderPath = std::filesystem::current_path().string() + "//res//";
    texturePath = binFolderPath + "textures//";
    normalTexturePath = texturePath + "normals//";
#endif
}

GLFWimage IOTexture::loadIconImage(const std::string &fileName)
{
    std::string filePathAndName = texturePath + fileName;
    unsigned error;
    GLFWimage image;
    error = lodepng_decode32_file(&(image.pixels), (unsigned int *)&(image.width), (unsigned int *)&(image.height), filePathAndName.c_str());
    if (error)
        printf("error %u: %s\n", error, lodepng_error_text(error));
    return image;
}

TextureData IOTexture::getTextureData(const std::string& fileName){
    TextureData textureData;
    textureData.fileName = fileName;
    std::string filePathAndName = texturePath + fileName;
    textureData.error = lodepng::decode(textureData.data, textureData.width, textureData.height, filePathAndName);
    if (textureData.error != 0)
    {
        std::clog << "Error: " << lodepng_error_text(textureData.error) << std::endl;
    }
    return textureData;
}