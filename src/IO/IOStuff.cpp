
#include "IOStuff.h"
#include <filesystem>
#include <fstream>

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <map>
#include <GL/glew.h>

IOStuff::IOStuff()
{
#ifdef EMSCRIPTEN
    binFolderPath = "./res/";
    texturePath = binFolderPath + "textures/";
    normalTexturePath = texturePath + "normals/";
    modelsPath = binFolderPath + "models/";
#else
    binFolderPath = std::filesystem::current_path().string() + "//res//";
    texturePath = binFolderPath + "textures//";
    normalTexturePath = texturePath + "normals//";
    modelsPath = binFolderPath + "models//";
#endif
}

IOStuff::~IOStuff()
{
}
