#include "Engine.h"
#include "glm/glm.hpp"

Engine::Engine() : mywindow(), camera(glm::vec3(0.0f, 0.0f, 4.0f)), framebuffer(1920, 1080) {
    setGLSettings();

    imageUniform = new ImageUniform(glData.getProgram("image"));
    framebuffer.postImageUniform = new PostImageUniform(glData.getProgram("postimage"));
    framebuffer.postImageUniform->setTexture(framebuffer.texture);
    framebuffer.postImageUniform->blur = 0.0f;

    imageUniform->setTexture(glData.getTexture("stallTexture.png"));

    text.programID = glData.getProgram("text");
    text.font = "Roboto-Regular";

    camera.setOrthographic(true);
}

Engine::~Engine() {
    delete imageUniform;
}

void Engine::draw() {
    beginDraw();
    drawStep();
    endDraw();
}

void Engine::drawStep()
{

    framebuffer.begin();

    glClearColor(0.45f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    image.draw(imageUniform);
    text.draw();

    framebuffer.postImageUniform->setPosition(glm::vec3(-1.f, -1.f, 0.f));
    framebuffer.postImageUniform->scale = glm::vec3(2.0f, 2.0f, 1.0f);
    framebuffer.end(mywindow.SCR_WIDTH, mywindow.SCR_HEIGHT);

    image.draw(framebuffer.postImageUniform);

    if (getMouse().isLeftReleased) {
        std::cout << "CLICK1!\n";
        framebuffer.postImageUniform->blur += 0.1f;
    }
    if(getMouse().isRightReleased){
        std::cout << "CLICK2!\n";
        framebuffer.postImageUniform->blur -= 0.1f;
    }

}

void Engine::endDraw()
{
    glClearColor(0.1f, 0.1f, 0.0f, 1.0f);
    glfwSwapBuffers(mywindow.window);
}

void Engine::setGLSettings() {
    glClearColor(0.15f, 0.15f, 0.0f, 1.0f);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    glStencilMask(0x00);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_DEPTH_TEST);
}

void Engine::beginDraw()
{
    glViewport(0, 0, mywindow.SCR_WIDTH, mywindow.SCR_HEIGHT);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    MatrixData matrixdata = camera.getMatrixData(framebuffer.width, framebuffer.height);
    text.setSourceWindowSize(framebuffer.width, framebuffer.height);

    imageUniform->setViewProjectionMatrix(matrixdata.VP, matrixdata.V, matrixdata.P);
    text.setViewProjectionMatrix(matrixdata.VP, matrixdata.V, matrixdata.P);

    text.setText("Hello world");
    text.setScale(glm::vec3(1.f, 1.f, 1.f));
    text.setPosition(glm::vec3(0.0f, 0.0f, 1.0f));

    MatrixData matrixdataReal = camera.getMatrixData(mywindow.SCR_WIDTH, mywindow.SCR_HEIGHT);
    framebuffer.postImageUniform->setViewProjectionMatrix(matrixdataReal.VP, matrixdataReal.V, matrixdataReal.P);

}

void Engine::resizeWindow(int _width, int _height) {
    mywindow.resizeWindow(_width, _height);
}

bool Engine::hasQuit() {
    return glfwWindowShouldClose(mywindow.window) || mywindow.keyboard.quitProgram;
}

void Engine::pollEvents() {
    getMouse().reset();
    glfwPollEvents();
}

Mouse& Engine::getMouse() {
    return mywindow.mouse;
}

Keyboard& Engine::getKeyboard() {
    return mywindow.keyboard;
}