
#ifndef ENGINE_H
#define ENGINE_H
#include "Graphics/Graphics.h"
#include "IO/Files/IOContainer.h"
#include <vector>
#include <memory>

class Engine {

    bool areShadersLoaded();
    void setIconImage();

    void addFilePaths(const std::vector<std::string>& resourceFolderPaths);
    void printLoadWarnings();

public:
    Canvas window;
    std::shared_ptr<Graphics> graphics;
    IOContainer ioContainer;

    Engine();
    void loadResourceFiles(const std::vector<std::string>& resourceFolderPaths);

    ~Engine();
    void loadShaders();
    void loadFonts();
    void loadTextures();
};

#endif // !ENGINE_H
