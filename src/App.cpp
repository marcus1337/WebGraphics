
#include "App.h"

#include "glm/glm.hpp"
#include <filesystem>

bool App::isGameUpdate()
{
    using namespace std::chrono;
    steady_clock::time_point timeGameUpdate = steady_clock::now();
    MS_PASSED += duration_cast<microseconds>(timeGameUpdate - timeSinceGameUpdate).count();
    timeSinceGameUpdate = timeGameUpdate;
    return MS_PASSED >= MS_FRAME;
}

void App::draw(){
    beginDraw();
    drawStep();
    endDraw();
}

void App::drawStep()
{
    GLuint textureID = glData.getTexture(textureData);
    GLuint programID = glData.getProgram(shaders[0]);

    image.draw(programID, textureID);

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

    camera.setOrthographic(false);
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

App::App() : mywindow(), camera(glm::vec3(0.0f, 0.0f, 4.0f))
{
    MS_PASSED = 0;
    MS_FRAME = 16600;
    std::string textureFile = "stallTexture.png";
    textureData = iotexture.getTextureData(textureFile);
    shaders = ioshader.getShaderData();
}

App::~App()
{
}

void App::prepareUpdate()
{
    gameTicks++;
    MS_PASSED = 0;
    mywindow.mouse.endFrame();
    glfwPollEvents();
    mywindow.mouse.beginFrame();
}

void App::step(){
    prepareUpdate();
    update();
    draw();
}

void App::gameStep()
{
    if (isGameUpdate())
        step();
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
}

void App::update()
{
    camera.move(mywindow.mouse, mywindow.keyboard);
}

void App::resizeWindow(int _width, int _height)
{
    mywindow.resizeWindow(_width, _height);
}