#ifndef RESOURCES_H
#define RESOURCES_H
#include "IO/Files/IOContainer.h"
#include <vector>
#include <string>

class Resources {
    IOContainer& ioContainer;
    void addFilePaths(const std::vector<std::string>& resourceFolderPaths);
    void printLoadWarnings();
    bool areShadersLoaded();
public:
    Resources();
    void loadResourceFiles(const std::vector<std::string>& resourceFolderPaths);
    void loadShaders();
    void loadFonts();
    void loadTextures();
};

#endif // !RESOURCES_H
