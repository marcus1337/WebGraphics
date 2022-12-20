#include "Engine.h"

#define GLEW_STATIC
#include <GL/glew.h>

#include "glm/glm.hpp"

Engine::Engine(std::vector<std::string> resourceFolderPaths) : window(){
    loadResourceFiles(resourceFolderPaths);
    if (!areResourcesLoaded()) {
        printResourceLoadError();
        exit(EXIT_FAILURE);
    }

    graphics = new Graphics(window, ioContainer.ioShader, ioContainer.ioTexture, ioContainer.ioFonts);
}

bool Engine::areResourcesLoaded() {
    return ioContainer.ioFonts.fonts.size() > 0 && ioContainer.ioShader.shaderCodeSets.size() > 0;
}

void Engine::printResourceLoadError() {
    std::cerr << "Failed to load one or more crucial resource files.\n";
    std::cerr << "Num fonts: " << ioContainer.ioFonts.fonts.size() << "\n";
    std::cerr << "Num shaderCodeSets: " << ioContainer.ioShader.shaderCodeSets.size() << "\n";
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
    ioContainer.ioFonts.print();

    auto shaderFilePaths = filePathContainer.getFilePaths(FileType::SHADER);
    auto shaderFileNames = filePathContainer.getFileNames(FileType::SHADER);
    auto shaderFileExtensions = filePathContainer.getFileExtensions(FileType::SHADER);
    ioContainer.ioShader.loadShaderCode(shaderFilePaths, shaderFileNames, shaderFileExtensions);

    setIconImage();

    auto textureFilePaths = filePathContainer.getFilePaths(FileType::PNG);
    auto textureFileNames = filePathContainer.getFileNames(FileType::PNG);
    ioContainer.ioTexture.loadTextures(textureFilePaths, textureFileNames);

    loadAudioResourceFiles();
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

