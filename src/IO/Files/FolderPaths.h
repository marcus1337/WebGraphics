#include <string>

#ifndef FOLDERPATHS_H
#define FOLDERPATHS_H

class FolderPaths{

public:

static const std::string& getShaderPath() {return shaderFolder;}
static const std::string& getModelsPath() {return modelsFolder;}
static const std::string& getTexturesPath() {return textureFolder;}
static const std::string& getNormalTexturesPath() {return normalTextureFolder;}
static const std::string& getFontsPath() {return fontsFolder;}

private:
    static std::string binFolder, shaderFolder, modelsFolder, textureFolder, normalTextureFolder, fontsFolder;
};

#endif