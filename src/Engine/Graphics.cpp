#include "Graphics.h"

Graphics::Graphics(Window& _window) : window(_window), camera(glm::vec3(0.0f, 0.0f, 3.0f)), framebuffer(1920, 1080)
{
    imageShader = Shader(glData.getProgram("image"));
    framebuffer.shader = Shader(glData.getProgram("postimage"));
    framebuffer.shader.setTexture(framebuffer.texture);

    imageShader.setTexture(glData.getTexture("stallTexture.png"));

    text.programID = glData.getProgram("text");
    text.font = "Roboto-Regular";

    camera.setOrthographic(true);
}

Graphics::~Graphics() {

}

void Graphics::draw() {
    preDraw();

    framebuffer.use();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    image.draw(&imageShader);
    text.draw();

    framebuffer.shader.setPosition(glm::vec3(-1.f, -1.f, 0.f));
    framebuffer.shader.scale = glm::vec3(2.0f, 2.0f, 1.0f);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, window.width, window.height);

    image.draw(&framebuffer.shader);
}

void Graphics::preDraw()
{
    glViewport(0, 0, window.width, window.height);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    MatrixData matrixdata = camera.getMatrixData(framebuffer.width, framebuffer.height);
    text.setSourceWindowSize(framebuffer.width, framebuffer.height);

    imageShader.setViewProjectionMatrix(matrixdata.VP, matrixdata.V, matrixdata.P);
    text.setViewProjectionMatrix(matrixdata.VP, matrixdata.V, matrixdata.P);

    text.setText("Hello world");
    text.setScale(glm::vec3(1.f, 1.f, 1.f));
    text.setPosition(glm::vec3(0.0f, 0.0f, 1.0f));

    MatrixData matrixdataReal = camera.getMatrixData(window.width, window.height);
    framebuffer.shader.setViewProjectionMatrix(matrixdataReal.VP, matrixdataReal.V, matrixdataReal.P);

}

FrameBuffer& Graphics::getDefaultView() {
    return framebuffer;
}
