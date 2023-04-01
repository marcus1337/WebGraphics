#include "Engine/Engine.h"

#define GLEW_STATIC
#include <GL/glew.h>

#include "glm/glm.hpp"

Engine::Engine() : graphics(window) {

}

Engine& Engine::getInstance() {
    static Engine engine;
    return engine;
}

void Engine::setIconImage() {
    auto& ioContainer = IOContainer::getInstance();
    auto iconImageFilePath = ioContainer.filePathContainer.getFilePath("icon256x256", FileType::PNG);
    if (!iconImageFilePath.empty()) {
        ioContainer.ioTexture.loadIconImage(iconImageFilePath);
        window.setIconImage(ioContainer.ioTexture.iconImage);
    }
}

void Engine::clearScreen() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}
