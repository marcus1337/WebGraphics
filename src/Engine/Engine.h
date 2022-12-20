#include "Audio/Audio.h"
#include "Graphics/Graphics.h"
#include "IO/Files/IOContainer.h"
#include <vector>

#ifndef ENGINE_H
#define ENGINE_H

class Engine {

    void loadResourceFiles(std::vector<std::string> resourceFolderPaths);
    bool areResourcesLoaded();
    void printResourceLoadError();

public:
    Canvas window;
    Graphics* graphics = nullptr;
    Audio audio;
    IOContainer ioContainer;

    Engine(std::vector<std::string> resourceFolderPaths);
    ~Engine();
};

#endif // !ENGINE_H
