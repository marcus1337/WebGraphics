#include "Global.h"

std::vector<std::string> Global::getResourceFolderPaths() {
    std::vector<std::string> paths;
    std::string resourceFolderPath = std::filesystem::current_path().string() + "//res//";
    paths.push_back(resourceFolderPath + "textures//");
    paths.push_back(resourceFolderPath + "fonts//");
    paths.push_back(resourceFolderPath + "shaders//");
    return paths;
}

Engine& Global::getEngineInstance() {
    static Engine engine(getResourceFolderPaths());
    return engine;
}

void Global::reload() {
    getEngineInstance().loadShaderResourceFiles();
}