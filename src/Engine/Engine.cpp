#include "Engine.h"

#define GLEW_STATIC
#include <GL/glew.h>

#include "glm/glm.hpp"

Engine::Engine(std::vector<std::string> resourceFolderPaths) : window(){
    loadResourceFiles(resourceFolderPaths);
    if (ioContainer.ioFonts.fonts.empty()) {
        std::cout << "Warning: no fonts loaded.\n";
    }
    if (!areShadersLoaded()) {
        printResourceLoadError();
        exit(EXIT_FAILURE);
    }

    graphics = new Graphics(window, ioContainer.ioShader, ioContainer.ioTexture, ioContainer.ioFonts);
}

bool Engine::areShadersLoaded() {
    return ioContainer.ioShader.getNumPrograms() > 0;
}

void Engine::printResourceLoadError() {
    std::cerr << "Failed to load one or more crucial resource files.\n";
    std::cerr << "Num shaderCodeSets: " << ioContainer.ioShader.getNumPrograms() << "\n";
}

void Engine::loadResourceFiles(std::vector<std::string> resourceFolderPaths) {
    auto& filePathContainer = ioContainer.filePathContainer;

    for (std::string folderPath : resourceFolderPaths) {
        std::cout << "Loading folder [" << folderPath << "]\n";
        filePathContainer.addFolderPath(folderPath);
    }

    auto fontFilePaths = filePathContainer.getFilePaths(FileType::TTF);
    auto fontFileNames = filePathContainer.getFileNames(FileType::TTF);
    ioContainer.ioFonts.loadFonts(fontFilePaths, fontFileNames);

    loadShaderResourceFiles();
    setIconImage();

    auto textureFilePaths = filePathContainer.getFilePaths(FileType::PNG);
    auto textureFileNames = filePathContainer.getFileNames(FileType::PNG);
    ioContainer.ioTexture.loadTextures(textureFilePaths, textureFileNames);

    loadAudioResourceFiles();
}

void Engine::loadShaderResourceFiles() {
    ioContainer.ioShader.clearCodeSets();
    ioContainer.ioShader.addDefaultShaderCode();
    auto shaderFilePaths = ioContainer.filePathContainer.getFilePaths(FileType::SHADER);
    auto shaderFileNames = ioContainer.filePathContainer.getFileNames(FileType::SHADER);
    auto shaderFileExtensions = ioContainer.filePathContainer.getFileExtensions(FileType::SHADER);
    ioContainer.ioShader.loadShaderCode(shaderFilePaths, shaderFileNames, shaderFileExtensions);
    ioContainer.ioShader.loadPrograms();
}

void Engine::loadAudioResourceFiles() {
    auto soundFilePaths = ioContainer.filePathContainer.getFilePaths(FileType::WAV);
    auto soundFileNames = ioContainer.filePathContainer.getFileNames(FileType::WAV);
    audio.loadSounds(soundFilePaths, soundFileNames);
}

void Engine::setIconImage() {
    auto iconImageFilePath = ioContainer.filePathContainer.getFilePath("icon256x256", FileType::PNG);
    if (!iconImageFilePath.empty()) {
        ioContainer.ioTexture.loadIconImage(iconImageFilePath);
        window.setIconImage(ioContainer.ioTexture.iconImage);
    }
}

Engine::~Engine() {
    if (graphics != nullptr)
        delete graphics;
}

