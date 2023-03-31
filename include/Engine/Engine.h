
#ifndef ENGINE_H
#define ENGINE_H
#include "Graphics/Graphics.h"
#include "IO/Files/IOContainer.h"
#include <vector>

class Engine {

    void loadResourceFiles(std::vector<std::string> resourceFolderPaths);
    bool areShadersLoaded();
    void printResourceLoadError();
    void setIconImage();

public:
    Canvas window;
    Graphics* graphics = nullptr;
    IOContainer ioContainer;

    Engine(std::vector<std::string> resourceFolderPaths);
    ~Engine();
    void loadShaderResourceFiles();
};

#endif // !ENGINE_H
