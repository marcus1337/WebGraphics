#include "Graphics.h"

Graphics::Graphics(Window& _window) : window(_window), framebuffer(1920, 1080)
{
    imageShader = Shader(glData.getProgram("image"));
    framebuffer.shader = Shader(glData.getProgram("postimage"));
    framebuffer.shader.setTexture(framebuffer.texture);

    imageShader.setTexture(glData.getTexture("stallTexture.png"));

    text.programID = glData.getProgram("text");
    text.font = "Roboto-Regular";

}

Graphics::~Graphics() {

}

void Graphics::draw() {
    glViewport(0, 0, window.width, window.height);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    MatrixData matrixdata = camera.getMatrixData(framebuffer.width, framebuffer.height);
    imageShader.setViewProjectionMatrix(matrixdata.VP, matrixdata.V, matrixdata.P);
    text.setViewProjectionMatrix(matrixdata.VP, matrixdata.V, matrixdata.P);

    framebuffer.use();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    imageShader.setPosition(glm::vec3(0, 980, 0));
    imageShader.scale = glm::vec3(100.0f, 100.0f, 1.0f);

    image.draw(&imageShader);

    text.setText("Hello world");
    text.setScale(glm::vec3(1.f, 1.f, 1.f));
    text.setPosition(glm::vec3(100.0f, 100.0f + 46.0f, 1.0f));
    text.rotation = 45.0f;
    text.draw();

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    framebuffer.shader.scale = glm::vec3((float)window.width, (float)window.height, 1.0f);
    glViewport(0, 0, window.width, window.height);

    matrixdata = camera.getMatrixData(window.width, window.height);
    framebuffer.shader.setViewProjectionMatrix(matrixdata.VP, matrixdata.V, matrixdata.P);
    image.draw(&framebuffer.shader);
}

