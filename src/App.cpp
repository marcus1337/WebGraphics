
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
    image.draw();
    text.draw();
}

void App::endDraw()
{
    glfwSwapBuffers(mywindow.window);
}

void App::beginDraw()
{
    glViewport(0, 0, mywindow.SCR_WIDTH, mywindow.SCR_HEIGHT);
    glClearColor(0.15f, 0.15f, 0.0f, 1.0f);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glStencilMask(0x00);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    camera.setOrthographic(false);
    matrixdata = camera.getMatrixData(mywindow.SCR_WIDTH, mywindow.SCR_HEIGHT);
    imageUniform->setViewProjectionMatrix(matrixdata.VP, matrixdata.V, matrixdata.P);

    text.setSourceWindowSize((float)mywindow.SCR_WIDTH, (float)mywindow.SCR_HEIGHT);
    text.setViewProjectionMatrix(matrixdata.VP, matrixdata.V, matrixdata.P);

    text.setText("Hello world 123 AAA");
    //text.rotationAxis = glm::vec3(0.f, 1.f, 0.f);
    //text.rotation += 0.1f;
    text.setScale(glm::vec3(5.f, 5.f, 1.f));
    text.setPosition(glm::vec3(0.0f,0.0f,1.0f));
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

    imageUniform = new ImageUniform(glData.getProgram("image"));
    imageUniform->setTexture(glData.getTexture(textureData));
    image.imageUniform = imageUniform;

    text.programID = glData.getProgram("text");
    text.font = "Roboto-Regular";
}

App::~App()
{
    delete imageUniform;
}

void App::prepareUpdate()
{
    gameTicks++;
    MS_PASSED = 0;
    glfwPollEvents();
    mywindow.mouse.beginFrame();
}

void App::step(){
    prepareUpdate();
    update();
    draw();
    mywindow.mouse.endFrame();
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