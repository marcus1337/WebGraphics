#include "Graphics.h"

Graphics::Graphics(Window& _window) : window(_window), camera(glm::vec3(0.0f, 0.0f, 3.0f)), framebuffer(1920, 1080)
{
    imageUniform = new Shader(glData.getProgram("image"));
    framebuffer.postImageUniform = new Shader(glData.getProgram("postimage"));
    framebuffer.postImageUniform->setTexture(framebuffer.texture);
    framebuffer.postImageUniform->setUniform("blur", 50.0f);

    imageUniform->setTexture(glData.getTexture("stallTexture.png"));

    text.programID = glData.getProgram("text");
    text.font = "Roboto-Regular";

    camera.setOrthographic(true);
}

Graphics::~Graphics() {
    delete imageUniform;
}

void Graphics::draw() {
    preDraw();

    framebuffer.begin();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    image.draw(imageUniform);
    text.draw();

    framebuffer.postImageUniform->setPosition(glm::vec3(-1.f, -1.f, 0.f));
    framebuffer.postImageUniform->scale = glm::vec3(2.0f, 2.0f, 1.0f);
    framebuffer.end(window.width, window.height);

    image.draw(framebuffer.postImageUniform);
}

void Graphics::preDraw()
{
    glViewport(0, 0, window.width, window.height);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    MatrixData matrixdata = camera.getMatrixData(framebuffer.width, framebuffer.height);
    text.setSourceWindowSize(framebuffer.width, framebuffer.height);

    imageUniform->setViewProjectionMatrix(matrixdata.VP, matrixdata.V, matrixdata.P);
    text.setViewProjectionMatrix(matrixdata.VP, matrixdata.V, matrixdata.P);

    text.setText("Hello world");
    text.setScale(glm::vec3(1.f, 1.f, 1.f));
    text.setPosition(glm::vec3(0.0f, 0.0f, 1.0f));

    MatrixData matrixdataReal = camera.getMatrixData(window.width, window.height);
    framebuffer.postImageUniform->setViewProjectionMatrix(matrixdataReal.VP, matrixdataReal.V, matrixdataReal.P);

}