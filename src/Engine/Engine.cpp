#include "Engine/Engine.h"

#define GLEW_STATIC
#include <GL/glew.h>

#include "glm/glm.hpp"

Engine::Engine() : window(){
    graphics = std::shared_ptr<Graphics>(new Graphics(window, ioContainer.ioShader, ioContainer.ioTexture, ioContainer.ioFonts));
}

Engine::~Engine() {
}

bool Engine::areShadersLoaded() {
    return ioContainer.ioShader.getNumPrograms() > 0;
}

void Engine::loadFonts() {
    auto& fileContainer = ioContainer.filePathContainer;
    auto fontFilePaths = fileContainer.getFilePaths(FileType::TTF);
    auto fontFileNames = fileContainer.getFileNames(FileType::TTF);
    ioContainer.ioFonts.loadFonts(fontFilePaths, fontFileNames);
}

void Engine::loadTextures() {
    auto& fileContainer = ioContainer.filePathContainer;
    auto textureFilePaths = fileContainer.getFilePaths(FileType::PNG);
    auto textureFileNames = fileContainer.getFileNames(FileType::PNG);
    ioContainer.ioTexture.loadTextures(textureFilePaths, textureFileNames);
}

void Engine::addFilePaths(const std::vector<std::string>& resourceFolderPaths) {
    for (const std::string& folderPath : resourceFolderPaths) {
        std::cout << "Loading folder [" << folderPath << "]\n";
        ioContainer.filePathContainer.addFolderPath(folderPath);
    }
}

void Engine::loadResourceFiles(const std::vector<std::string>& resourceFolderPaths) {
    addFilePaths(resourceFolderPaths);
    loadFonts();
    loadShaders();
    loadTextures();
    setIconImage();
    printLoadWarnings();
}

void Engine::printLoadWarnings() {
    if (ioContainer.ioFonts.fonts.empty()) {
        std::cout << "Warning: no fonts loaded.\n";
    }
    if (!areShadersLoaded()) {
        std::cerr << "Warning: no shaders loaded. #shaderCodeSets: " << ioContainer.ioShader.getNumPrograms() << "\n";
    }
}

void Engine::loadShaders() {
    ioContainer.ioShader.clearCodeSets();
    ioContainer.ioShader.addDefaultShaderCode();
    auto shaderFilePaths = ioContainer.filePathContainer.getFilePaths(FileType::SHADER);
    auto shaderFileNames = ioContainer.filePathContainer.getFileNames(FileType::SHADER);
    auto shaderFileExtensions = ioContainer.filePathContainer.getFileExtensions(FileType::SHADER);
    ioContainer.ioShader.loadShaderCode(shaderFilePaths, shaderFileNames, shaderFileExtensions);
    ioContainer.ioShader.loadPrograms();
}

void Engine::setIconImage() {
    auto iconImageFilePath = ioContainer.filePathContainer.getFilePath("icon256x256", FileType::PNG);
    if (!iconImageFilePath.empty()) {
        ioContainer.ioTexture.loadIconImage(iconImageFilePath);
        window.setIconImage(ioContainer.ioTexture.iconImage);
    }
}

