#include <string>

#ifndef FOLDERPATHS_H
#define FOLDERPATHS_H

class FolderPaths{

public:

static std::string getShaderPath();
static std::string getTexturesPath();
static std::string getNormalTexturesPath();
static std::string getFontsPath();
static std::string getSavesPath();
static std::string getResPath();
static std::string getLogsPath();

};

#endif