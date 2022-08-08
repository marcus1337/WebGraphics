
#include "FolderPaths.h"

#ifndef EMSCRIPTEN
#include <filesystem>
#endif

#include <iostream>

std::string FolderPaths::getResPath() {
#ifdef EMSCRIPTEN
    return "./res/";
#else
    return std::filesystem::current_path().string() + "//res//";
#endif
}

std::string FolderPaths::getShaderPath() {
#ifdef EMSCRIPTEN
    return "./res/shaders/";
#else
    return std::filesystem::current_path().string() + "//res//shaders//";
#endif
}

std::string FolderPaths::getTexturesPath() {
#ifdef EMSCRIPTEN
    return "./res/textures/";
#else
    return std::filesystem::current_path().string() + "//res//textures//";
#endif
}

std::string FolderPaths::getNormalTexturesPath() {
#ifdef EMSCRIPTEN
    return "./res/normals/";
#else
    return std::filesystem::current_path().string() + "//res//normals//";
#endif
}

std::string FolderPaths::getFontsPath() {
#ifdef EMSCRIPTEN
    return "./res/fonts/";
#else
    return std::filesystem::current_path().string() + "//res//fonts//";
#endif
}

std::string FolderPaths::getSavesPath() {
#ifdef EMSCRIPTEN
    return "./res/saves/";
#else
    return std::filesystem::current_path().string() + "//res//saves//";
#endif
}

std::string FolderPaths::getLogsPath() {
#ifdef EMSCRIPTEN
    return "./res/logs/";
#else
    return std::filesystem::current_path().string() + "//res//logs//";
#endif
}
