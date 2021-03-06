#include "Engine.h"
#include "glm/glm.hpp"

Engine::Engine() : window(), graphics(window) {
    setGLSettings();
}

Engine::~Engine() {

}

void Engine::setGLSettings() {
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    glStencilMask(0x00);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_DEPTH_TEST);
    glClearColor(0.1f, 0.1f, 0.0f, 1.0f);
}
