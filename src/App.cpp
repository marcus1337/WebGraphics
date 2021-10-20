
#include "App.h"

#include "glm/glm.hpp"
#include <filesystem>

void App::init()
{
    mywindow.initWindow();
    MS_PASSED = 0;
    MS_FRAME = 16600;
    io.gldata.init(io.iostuff.shaderPath, io.iostuff.texturePath, io.iostuff.normalTexturePath);
    image.init(io.gldata);
    modelManager.init(io);
}

bool App::isGameUpdate()
{
    using namespace std::chrono;
    steady_clock::time_point timeGameUpdate = steady_clock::now();
    MS_PASSED += duration_cast<microseconds>(timeGameUpdate - timeSinceGameUpdate).count();
    timeSinceGameUpdate = timeGameUpdate;
    return MS_PASSED >= MS_FRAME;
}

void App::drawStep()
{
    beginDraw();

    image.scale = glm::vec3(1.0, 1.0, 1.0f);
    image.draw(GLData::Program::IMAGE, GLData::Texture::STALL);

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

    camera.setOrthographic(true);
    matrixdata = camera.getMatrixData(mywindow.SCR_WIDTH, mywindow.SCR_HEIGHT);
    image.setViewProjectionMatrix(matrixdata.VP, matrixdata.V, matrixdata.P);
}

void App::run()
{
    while (!glfwWindowShouldClose(mywindow.window) && !mywindow.keyboard.quitProgram)
    {
        gameStep();
    }
}

App::App() : camera(glm::vec3(0.0f, 0.0f, 4.0f))
{
    init();
}

App::~App()
{
}

void App::prepareUpdate()
{
    gameTicks++;
    MS_PASSED = 0;
    glfwPollEvents();
    mywindow.mouse.beginFrame();
}

void App::gameStep()
{
    if (isGameUpdate())
    {
        prepareUpdate();
        update();
        drawStep();
        mywindow.mouse.endFrame();
    }

#ifndef EMSCRIPTEN
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
#endif
}

void App::update()
{
    camera.move(mywindow.mouse, mywindow.keyboard);
}

void App::resizeWindow(int _width, int _height)
{
    mywindow.resizeWindow(_width, _height);
}