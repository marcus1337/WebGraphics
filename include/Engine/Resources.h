#ifndef RESOURCES_H
#define RESOURCES_H
#include "IO/Files/IOContainer.h"

class Resources {
    void addFilePaths(const std::vector<std::string>& resourceFolderPaths);
    void printLoadWarnings();
    bool areShadersLoaded();
public:

    void loadResourceFiles(const std::vector<std::string>& resourceFolderPaths);
    void loadShaders();
    void loadFonts();
    void loadTextures();
    IOContainer ioContainer;
};

#endif // !RESOURCES_H
