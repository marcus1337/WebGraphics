
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

    framebuffer.begin();

    glClearColor(0.45f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    image.imageUniform = imageUniform;
    image.draw();
    text.draw();

    framebuffer.postImageUniform->setPosition(glm::vec3(-1.f,-1.f,0.f));
    framebuffer.postImageUniform->scale = glm::vec3(2.0f,2.0f,1.0f);
    framebuffer.end(mywindow.SCR_WIDTH, mywindow.SCR_HEIGHT);

    image.imageUniform = framebuffer.postImageUniform;
    image.draw();

}

void App::endDraw()
{
    glClearColor(0.1f, 0.1f, 0.0f, 1.0f);
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

    MatrixData matrixdata = camera.getMatrixData(framebuffer.width, framebuffer.height);
    text.setSourceWindowSize(framebuffer.width, framebuffer.height);

    imageUniform->setViewProjectionMatrix(matrixdata.VP, matrixdata.V, matrixdata.P);
    text.setViewProjectionMatrix(matrixdata.VP, matrixdata.V, matrixdata.P);

    text.setText("Hello world");
    text.setScale(glm::vec3(1.f, 1.f, 1.f));
    text.setPosition(glm::vec3(0.0f,0.0f,1.0f));

    MatrixData matrixdataReal = camera.getMatrixData(mywindow.SCR_WIDTH, mywindow.SCR_HEIGHT);
    framebuffer.postImageUniform->setViewProjectionMatrix(matrixdataReal.VP, matrixdataReal.V, matrixdataReal.P);

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

App::App() : mywindow(), camera(glm::vec3(0.0f, 0.0f, 4.0f)), framebuffer(1920, 1080)
{
    setGLSettings();
    MS_PASSED = 0;
    MS_FRAME = 16600;

    imageUniform = new ImageUniform(glData.getProgram("image"));
    framebuffer.postImageUniform = new PostImageUniform(glData.getProgram("postimage"));
    framebuffer.postImageUniform->setTexture(framebuffer.texture);

    imageUniform->setTexture(glData.getTexture("stallTexture.png"));

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

void App::update()
{
    //camera.move(mywindow.mouse, mywindow.keyboard);
    if(mywindow.mouse.wasLeftReleased){
        std::cout << "CLICK1!\n";
        framebuffer.postImageUniform->blur += 0.1f;
    }
    if(mywindow.mouse.wasRightReleased){
        std::cout << "CLICK2!\n";
        framebuffer.postImageUniform->blur -= 0.1f;
    }

}

void App::resizeWindow(int _width, int _height)
{
    mywindow.resizeWindow(_width, _height);
}