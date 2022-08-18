#include <Engine/Engine.h>
#include <Engine/Graphics.h>
#include <IO/Controller/Keyboard.h>
#include <IO/Controller/Mouse.h>
#include <vector>
#include <string>

#ifndef DEVCONTROLLER_H
#define DEVCONTROLLER_H

class DevController {

    Engine& engine;
    Graphics& graphics;
    Keyboard& keyboard;
    Mouse& mouse;
    uint64_t mostRecentShaderEditTime;
    uint64_t getMostRecentEditTime(std::vector<std::string> paths);
    std::vector<std::string> trackedShaderFilePaths;
    bool autoUpdateShaders = true;

public:

    DevController(Engine& _engine);
    void update();
    bool wasAnyShaderFileModified();


};

#endif // !DEVCONTROLLER_H
