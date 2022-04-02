
#include "FolderPaths.h"

#ifndef EMSCRIPTEN
#include <filesystem>
#endif

std::string FolderPaths::getResPath(){
    #ifdef EMSCRIPTEN
        return "./res/";
    #else
        return std::filesystem::current_path().string() + "//res//";
    #endif
}

std::string FolderPaths::getShaderPath(){
    #ifdef EMSCRIPTEN
        return "./res/shaders/";
    #else
        return "//res//shaders//";
    #endif
}

std::string FolderPaths::getModelsPath(){
    #ifdef EMSCRIPTEN
        return "./res/models/";
    #else
        return "//res//models//";
    #endif
}

std::string FolderPaths::getTexturesPath(){
    #ifdef EMSCRIPTEN
        return "./res/textures/";
    #else
        return "//res//textures//";
    #endif
}

std::string FolderPaths::getNormalTexturesPath(){
    #ifdef EMSCRIPTEN
        return "./res/normals/";
    #else
        return "//res//normals//";
    #endif
}

std::string FolderPaths::getFontsPath(){
    #ifdef EMSCRIPTEN
        return "./res/fonts/";
    #else
        return "//res//fonts//";
    #endif
}
