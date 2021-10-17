
#include "App.h"


#include "glm/glm.hpp"
#include <filesystem>

bool App::keepRunning = true;

uint64_t App::getTicks() {
    return gameTicks;
}


void App::init() {
    mywindow.initWindow();
    MS_PASSED = 0;
    MS_FRAME = 16600;
    io.gldata.init(io.iostuff.shaderPath, io.iostuff.texturePath, io.iostuff.normalTexturePath);
    image.init(io.gldata);
    modelManager.init(io);
}


bool App::isGameUpdate() {
    using namespace std::chrono;
    steady_clock::time_point timeGameUpdate = steady_clock::now();
    MS_PASSED += duration_cast<microseconds>(timeGameUpdate - timeSinceGameUpdate).count();
    timeSinceGameUpdate = timeGameUpdate;
    return MS_PASSED >= MS_FRAME;
}

void App::drawStep() { 
    beginDraw();

    image.setProgram(GLData::Program::IMAGE);
    image.setTexture(GLData::Texture::STALL);
    image.scale = glm::vec3(1.0, 1.0, 1.0f);
    image.draw();
    
    endDraw();
}

void App::endDraw()
{

    glfwSwapBuffers(mywindow.window);
}


void App::beginDraw()
{
    glViewport(0, 0, mywindow.SCR_WIDTH, mywindow.SCR_HEIGHT);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glStencilMask(0x00);
    glm::mat4 VP = mywindow.projection * mywindow.view;
    matrixdata.VP = VP;
    matrixdata.P = mywindow.projection;
    matrixdata.V = mywindow.view;
    image.setViewProjectionMatrix(VP, mywindow.view, mywindow.projection);
}

void App::run() {
    while (keepRunning && !glfwWindowShouldClose(mywindow.window)) {
        gameStep();
    }
}

App::App() {
    init();
}

App::~App() {

}

void App::gameStep() {
    if (isGameUpdate()) {
        glfwPollEvents();

        if (!mywindow.wasLeftMousePressed && mywindow.isLeftMousePressed)
            mywindow.wasLeftMousePressed = true;
        if (mywindow.wasLeftMousePressed && !mywindow.isLeftMousePressed) {
            mywindow.wasLeftMousePressed = false;
            mywindow.wasLeftMouseReleased = true;
        }

        mywindow.processActions();
        gameTicks++;
        MS_PASSED = 0;
        mywindow.handleFrame();
        updatePage();
        drawStep();

        if (mywindow.wasLeftMouseReleased ){
            mywindow.wasLeftMouseReleased = false;
        }

    }

    #ifndef EMSCRIPTEN
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    #endif
}

void App::updatePage()
{

}

void App::resizeWindow(int _width, int _height){
    mywindow.resizeWindow(_width, _height);
}