#include "Graphics.h"
#include <algorithm>
#include <iostream>

Graphics::Graphics(Canvas& _window) : window(_window)
{
    backgroundColor = glm::vec3(0.2f, 0.2f, 0.2f);
    outerBackgroundColor = glm::vec3(0.05f, 0.05f, 0.05f);
    setShaderPrograms();
    frameBuffers.push_back(makeFrameBuffer(1920, 1080));
    textObject.setFont("Roboto-Regular");
    window.appResizeCallbackFunction = std::bind(&Graphics::display, this);
    setViewIndex(0);
    glData.preloadTextures();
}

void Graphics::setShaderPrograms() {
    glData.loadShaderCodeStrings();
    imageShader.setProgram(glData.getProgram("image"));
    rectangleShader.setProgram(glData.getProgram("rectangle"));
    textShader.setProgram(glData.getProgram("text"));
    buttonShader.setProgram(glData.getProgram("button"));
    for (auto& framebuffer : frameBuffers) {
        framebuffer->shader.setProgram(glData.getProgram("postimage"));
    }
}

void Graphics::setViewIndex(std::size_t _viewIndex){
    viewIndex = _viewIndex;
    frameBuffers[viewIndex]->use();
    FrameBuffer& fb = *frameBuffers[viewIndex];
    MatrixData matrixdata = camera.getMatrixData(fb.width, fb.height);
    rectangleShader.setViewProjectionMatrix(matrixdata.VP, matrixdata.V, matrixdata.P);
    imageShader.setViewProjectionMatrix(matrixdata.VP, matrixdata.V, matrixdata.P);
    textShader.setViewProjectionMatrix(matrixdata.VP, matrixdata.V, matrixdata.P);
    buttonShader.setViewProjectionMatrix(matrixdata.VP, matrixdata.V, matrixdata.P);
}

FrameBuffer* Graphics::makeFrameBuffer(int width, int height) {
    FrameBuffer* frameBuffer = new FrameBuffer(width, height);
    frameBuffer->shader = ImageShader(glData.getProgram("postimage"));
    frameBuffer->shader.setTexture(frameBuffer->texture);
    return frameBuffer;
}

Graphics::~Graphics() {
    for (FrameBuffer* frameBuffer : frameBuffers) {
        delete frameBuffer;
    }
}

void Graphics::clearView(std::size_t viewID) {
    glClearColor(backgroundColor.r, backgroundColor.g, backgroundColor.b, 1.0f);
    frameBuffers[viewID]->use();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void Graphics::clearViews() {
    for (std::size_t i = 0; i < frameBuffers.size(); i++)
        clearView(i);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, window.width, window.height);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    frameBuffers[viewIndex]->use();
}

void Graphics::display() {
    for (std::size_t i = 1; i < frameBuffers.size(); i++) {
        frameBuffers[i]->use();
        MatrixData matrixdata = camera.getMatrixData(frameBuffers[i]->width, frameBuffers[i]->height);
        frameBuffers[i]->shader.setViewProjectionMatrix(matrixdata.VP, matrixdata.V, matrixdata.P);
        imageObject.draw(frameBuffers[i]->shader);
    }
    drawMainView();
    window.display();
    frameBuffers[viewIndex]->use();
}

void Graphics::drawMainView() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glClearColor(outerBackgroundColor.r, outerBackgroundColor.g, outerBackgroundColor.b, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    window.aspectRatio.setIndexToLessOrEqual(window.width, window.height);
    int frameWidth = window.aspectRatio.getWidth();
    int frameHeight = window.aspectRatio.getHeight();
    float frameXPos = (float)(window.width - frameWidth) / 2.0f;
    float frameYPos = (float)(window.height - frameHeight) / 2.0f;

    frameBuffers[0]->shader.setPosition(glm::vec3(frameXPos, frameYPos, 0.f));
    frameBuffers[0]->shader.scale = glm::vec3((float)frameWidth, (float)frameHeight, 1.0f);
    glViewport(0, 0, window.width, window.height);
    MatrixData matrixdata = camera.getMatrixData(window.width, window.height);
    frameBuffers[0]->shader.setViewProjectionMatrix(matrixdata.VP, matrixdata.V, matrixdata.P);
    imageObject.draw(frameBuffers[0]->shader);
}

std::pair<int, int> Graphics::getPixelPosition(int _x, int _y, std::size_t viewID) {
    FrameBuffer& mainFrameBuffer = *frameBuffers[0];
    FrameBuffer& viewedFrameBuffer = *frameBuffers[viewID];
    int xOffset = (int)mainFrameBuffer.shader.position.x;
    int yOffset = (int)mainFrameBuffer.shader.position.y;
    _x -= xOffset;
    _y -= yOffset;
    _x = std::clamp(_x, 0, (int)viewedFrameBuffer.shader.scale.x);
    _y = std::clamp(_y, 0, (int)viewedFrameBuffer.shader.scale.y);
    float relX = (float)_x / viewedFrameBuffer.shader.scale.x;
    float relY = (float)_y / viewedFrameBuffer.shader.scale.y;
    return std::make_pair((int)(relX * viewedFrameBuffer.width), (int)(relY * viewedFrameBuffer.height));
}

bool Graphics::isInsideView(int _x, int _y, std::size_t viewID) {
    if (viewID == 0)
        return true;
    FrameBuffer& viewedFrameBuffer = *frameBuffers[viewID];
    std::pair<int, int> pos = getPixelPosition(_x, _y);
    _x = pos.first;
    _y = pos.second;
    int viewX = viewedFrameBuffer.shader.position.x;
    int viewY = viewedFrameBuffer.shader.position.y;
    int viewMaxX = viewX + viewedFrameBuffer.width;
    int viewMaxY = viewY + viewedFrameBuffer.height;
    return _x >= viewX && _x <= viewMaxX && _y >= viewY && _y <= viewMaxY;
}
