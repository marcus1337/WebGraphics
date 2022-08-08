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
public:
    IOTexture();
    std::vector<std::string> getAllTextureNames();
    GLFWimage loadIconImage(const std::string& fileName);
    TextureData getTextureData(const std::string& fileName);
};

#endif