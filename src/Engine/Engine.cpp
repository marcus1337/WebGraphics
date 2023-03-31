#include "Engine/Engine.h"

#define GLEW_STATIC
#include <GL/glew.h>

#include "glm/glm.hpp"

Engine::Engine() : graphics(window) {

}

Engine::~Engine() {
}

void Engine::setIconImage() {
    auto& ioContainer = IOContainer::getInstance();
    auto iconImageFilePath = ioContainer.filePathContainer.getFilePath("icon256x256", FileType::PNG);
    if (!iconImageFilePath.empty()) {
        ioContainer.ioTexture.loadIconImage(iconImageFilePath);
        window.setIconImage(ioContainer.ioTexture.iconImage);
    }
}

