#include "ShaderUpdater.h"
#include <iostream>
#include <filesystem>
#include <limits>

ShaderUpdater::ShaderUpdater(Engine& _engine) : engine(_engine), graphics(_engine.graphics), mouse(_engine.window.mouse), keyboard(_engine.window.keyboard) {
    IOShader ioshader;
    trackedShaderFilePaths = ioshader.getShaderFilePaths();
    mostRecentShaderEditTime = getMostRecentEditTime(trackedShaderFilePaths);
}

void ShaderUpdater::update() {
    if (keyboard.isDownClick[GLFW_KEY_P]) {
        autoUpdateShaders = !autoUpdateShaders;
        std::cout << "auto updating shaders: " << autoUpdateShaders << "\n";
    }

    if (autoUpdateShaders && wasAnyShaderFileModified()) {
        std::cout << "auto-shader-update to be implemented here........\n";
        engine.graphics.shaderPrograms.reload();
    }
}

uint64_t ShaderUpdater::getMostRecentEditTime(std::vector<std::string> paths) {
    std::filesystem::file_time_type ftime;
    uint64_t timeSinceEpoch = std::numeric_limits<uint64_t>::min();
    for (std::string path : paths) {
        ftime = std::filesystem::last_write_time(path);
        timeSinceEpoch = std::max<uint64_t>(ftime.time_since_epoch().count(), timeSinceEpoch);
    }
    return timeSinceEpoch;
}

bool ShaderUpdater::wasAnyShaderFileModified() {
    uint64_t tmpMostRecentShaderEditTime = getMostRecentEditTime(trackedShaderFilePaths);
    if (tmpMostRecentShaderEditTime != mostRecentShaderEditTime) {
        mostRecentShaderEditTime = tmpMostRecentShaderEditTime;
        return true;
    }
    return false;
}