#include <GL/glew.h>
#include <vector>
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>
#include <map>
#include <iostream>
#include <vector>
#include <fstream>
#include <tuple>

#include "GLFW/glfw3.h"
#include "TextureData.h"

#ifndef IOTEXTURE_H
#define IOTEXTURE_H

class IOTexture
{
    std::vector<std::string> getAllTextureNames();
    std::vector<TextureData> textureInfos;
    std::map<std::string, GLuint> textures;
    GLuint makeTexture(TextureData& textureData);
    GLuint getTexture(TextureData& textureData);

    TextureData getTextureData(const std::string& fileName);
    GLuint load2DTexture(const TextureData& textureData);

public:
    IOTexture();
    ~IOTexture();
    GLFWimage loadIconImage(const std::string& fileName);

    void preloadTextures();
    GLuint getTexture(std::string name);
};

#endif