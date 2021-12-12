
#include "FolderPaths.h"

#ifdef EMSCRIPTEN
    std::string FolderPaths::binFolder = "./res/";
    std::string FolderPaths::modelsFolder = binFolder + "models/";
    std::string FolderPaths::fontsFolder = binFolder + "fonts/";
    std::string FolderPaths::shaderFolder = binFolder + "shaders/";
    std::string FolderPaths::textureFolder = binFolder + "textures/";
    std::string FolderPaths::normalTextureFolder = textureFolder + "normals/";
#else
#include <filesystem>
    std::string FolderPaths::binFolder = std::filesystem::current_path().string() + "//res//";
    std::string FolderPaths::modelsFolder = binFolder + "models//";
    std::string FolderPaths::fontsFolder = binFolder + "fonts//";
    std::string FolderPaths::shaderFolder = binFolder + "shaders//";
    std::string FolderPaths::textureFolder = binFolder + "textures//";
    std::string FolderPaths::normalTextureFolder = textureFolder + "normals//";
#endif
