#include "Engine/Engine.h"

#define GLEW_STATIC
#include <GL/glew.h>

#include "glm/glm.hpp"

Engine::Engine() : window(), resources() {
    graphics = std::shared_ptr<Graphics>(new Graphics(window, resources.ioContainer.ioShader, resources.ioContainer.ioTexture, resources.ioContainer.ioFonts));
}

Engine::~Engine() {
}

void Engine::setIconImage() {
    auto iconImageFilePath = resources.ioContainer.filePathContainer.getFilePath("icon256x256", FileType::PNG);
    if (!iconImageFilePath.empty()) {
        resources.ioContainer.ioTexture.loadIconImage(iconImageFilePath);
        window.setIconImage(resources.ioContainer.ioTexture.iconImage);
    }
}

Engine& Engine::getInstance() {
    static Engine engine;
    return engine;
}
