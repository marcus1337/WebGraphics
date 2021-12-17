
#include "App.h"

#include "glm/glm.hpp"

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

void App::setGLSettings(){
    glClearColor(0.15f, 0.15f, 0.0f, 1.0f);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    glStencilMask(0x00);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_DEPTH_TEST);
}

void App::beginDraw()
{
    glViewport(0, 0, mywindow.SCR_WIDTH, mywindow.SCR_HEIGHT);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    camera.setOrthographic(true);
    matrixdata = camera.getMatrixData(mywindow.SCR_WIDTH, mywindow.SCR_HEIGHT);
    imageUniform->setViewProjectionMatrix(matrixdata.VP, matrixdata.V, matrixdata.P);

    text.setSourceWindowSize((float)mywindow.SCR_WIDTH, (float)mywindow.SCR_HEIGHT);
    text.setViewProjectionMatrix(matrixdata.VP, matrixdata.V, matrixdata.P);

    text.setText("Hello world");
    text.setScale(glm::vec3(1.f, 1.f, 1.f));
    text.setPosition(glm::vec3(0.0f,0.0f,0.0f));
}

void App::run()
{
    while (!glfwWindowShouldClose(mywindow.window) && !mywindow.keyboard.quitProgram)
    {
        if (isGameUpdate()){
            step();
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

App::App() : mywindow(), camera(glm::vec3(0.0f, 0.0f, 4.0f))
{
    setGLSettings();
    MS_PASSED = 0;
    MS_FRAME = 16600;

    imageUniform = new ImageUniform(glData.getProgram("image"));
    postImageUniform = new PostImageUniform(glData.getProgram("postimage"));

    imageUniform->setTexture(glData.getTexture("stallTexture.png"));
    image.imageUniform = imageUniform;

    text.programID = glData.getProgram("text");
    text.font = "Roboto-Regular";
}

App::~App()
{
    delete imageUniform;
    delete postImageUniform;
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

void App::update()
{
    camera.move(mywindow.mouse, mywindow.keyboard);
}

void App::resizeWindow(int _width, int _height)
{
    mywindow.resizeWindow(_width, _height);
}