
#include "IOStuff.h"
#include <filesystem>
#include <fstream>




IOStuff::IOStuff() {
    #ifdef EMSCRIPTEN
        binFolderPath = "./res/";
        shaderPath = binFolderPath + "shaders/";
        texturePath = binFolderPath + "textures/";
        normalTexturePath = texturePath + "normals/";
        modelsPath = binFolderPath + "models/";
    #else
        binFolderPath = std::filesystem::current_path().string() + "//res//";
        shaderPath = binFolderPath + "shaders//";
        texturePath = binFolderPath + "textures//";
        normalTexturePath = texturePath + "normals//";
        modelsPath = binFolderPath + "models//";
    #endif

}

IOStuff::~IOStuff() {

}

