#include "Engine/Resources.h"

Resources::Resources() : ioContainer(IOContainer::getInstance()) {

}

bool Resources::areShadersLoaded() {
    return ioContainer.ioShader.getNumPrograms() > 0;
}

void Resources::loadFonts() {
    auto& fileContainer = ioContainer.filePathContainer;
    auto fontFilePaths = fileContainer.getFilePaths(FileType::TTF);
    auto fontFileNames = fileContainer.getFileNames(FileType::TTF);
    ioContainer.ioFonts.loadFonts(fontFilePaths, fontFileNames);
}

void Resources::loadTextures() {
    auto& fileContainer = ioContainer.filePathContainer;
    auto textureFilePaths = fileContainer.getFilePaths(FileType::PNG);
    auto textureFileNames = fileContainer.getFileNames(FileType::PNG);
    ioContainer.ioTexture.loadTextures(textureFilePaths, textureFileNames);
}

void Resources::addFilePaths(const std::vector<std::string>& resourceFolderPaths) {
    for (const std::string& folderPath : resourceFolderPaths) {
        std::cout << "Loading folder [" << folderPath << "]\n";
        ioContainer.filePathContainer.addFolderPath(folderPath);
    }
}

void Resources::loadResourceFiles(const std::vector<std::string>& resourceFolderPaths) {
    addFilePaths(resourceFolderPaths);
    loadFiles();
}

void Resources::loadDefaultResourceFiles() {
    ioContainer.filePathContainer.addDefaultFolderPaths();
    loadFiles();
}

void Resources::loadFiles() {
    loadFonts();
    loadShaders();
    loadTextures();
    printLoadWarnings();
}

void Resources::printLoadWarnings() {
    if (ioContainer.ioFonts.fonts.empty()) {
        std::cout << "Warning: no fonts loaded.\n";
    }
    if (!areShadersLoaded()) {
        std::cerr << "Warning: no shaders loaded. #shaderCodeSets: " << ioContainer.ioShader.getNumPrograms() << "\n";
    }
}

void Resources::loadShaders() {
    ioContainer.ioShader.clearCodeSets();
    ioContainer.ioShader.addDefaultShaderCode();
    auto shaderFilePaths = ioContainer.filePathContainer.getFilePaths(FileType::SHADER);
    auto shaderFileNames = ioContainer.filePathContainer.getFileNames(FileType::SHADER);
    auto shaderFileExtensions = ioContainer.filePathContainer.getFileExtensions(FileType::SHADER);
    ioContainer.ioShader.loadShaderCode(shaderFilePaths, shaderFileNames, shaderFileExtensions);
    ioContainer.ioShader.loadPrograms();
}

