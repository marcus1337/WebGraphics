#include "Graphics.h"
#include <algorithm>

Graphics::Graphics(Window& _window) : window(_window)
{
    frameBuffers.push_back(makeFrameBuffer(1920, 1080));
    imageShader = Shader(glData.getProgram("image"));
    rectangleShader = Shader(glData.getProgram("rectangle"));
    textObject.programID = glData.getProgram("text");
    window.appResizeCallbackFunction = std::bind(&Graphics::display, this);
}

void Graphics::initViews(std::vector<View> views) {
    for (View& view : views) {
        frameBuffers.push_back(makeFrameBuffer(view.width, view.height));
    }
}

FrameBuffer* Graphics::makeFrameBuffer(int width, int height) {
    FrameBuffer* frameBuffer = new FrameBuffer(width, height);
    frameBuffer->shader = Shader(glData.getProgram("postimage"));
    frameBuffer->shader.setTexture(frameBuffer->texture);
    return frameBuffer;
}

Graphics::~Graphics() {
    for (FrameBuffer* frameBuffer : frameBuffers) {
        delete frameBuffer;
    }
}

void Graphics::clearView(std::size_t viewID) {
    glClearColor(0.1f, 0.1f, 0.0f, 1.0f);
    frameBuffers[viewID]->use();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void Graphics::clearViews() {
    for (std::size_t i = 0; i < frameBuffers.size(); i++)
        clearView(i);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, window.width, window.height);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void Graphics::display() {
    frameBuffers[0]->use();
    MatrixData matrixdata = camera.getMatrixData(frameBuffers[0]->width, frameBuffers[0]->height);
    for (std::size_t i = 1; i < frameBuffers.size(); i++) {
        frameBuffers[i]->shader.setViewProjectionMatrix(matrixdata.VP, matrixdata.V, matrixdata.P);
        imageObject.draw(&frameBuffers[i]->shader);
    }
    drawMainView();
    window.display();
}

void Graphics::drawRectangle(Rectangle& rectangle, std::size_t viewID) {
    FrameBuffer& frameBuffer = *frameBuffers[viewID];
    frameBuffer.use();
    MatrixData matrixdata = camera.getMatrixData(frameBuffer.width, frameBuffer.height);

    rectangleShader.setViewProjectionMatrix(matrixdata.VP, matrixdata.V, matrixdata.P);
    rectangleShader.setPosition(glm::vec3(rectangle.x, rectangle.y, 0.0f));
    rectangleShader.scale = glm::vec3(rectangle.width, rectangle.height, 1.0f);
    rectangleShader.alpha = rectangle.alpha;
    rectangleShader.rotation = rectangle.rotation;
    rectangleShader.color = rectangle.color;
    imageObject.draw(&rectangleShader);

}

void Graphics::drawImage(Image& image, std::size_t viewID) {
    FrameBuffer& frameBuffer = *frameBuffers[viewID];
    frameBuffer.use();
    MatrixData matrixdata = camera.getMatrixData(frameBuffer.width, frameBuffer.height);
    imageShader.setViewProjectionMatrix(matrixdata.VP, matrixdata.V, matrixdata.P);
    imageShader.setPosition(glm::vec3(image.x, image.y, 0.0f));
    imageShader.scale = glm::vec3(image.width, image.height, 1.0f);
    imageShader.setTexture(glData.getTexture(image.texture));
    imageShader.rotation = image.rotation;
    imageObject.draw(&imageShader);
}

void Graphics::drawText(Text& text, std::size_t viewID) {
    FrameBuffer& frameBuffer = *frameBuffers[viewID];
    frameBuffer.use();
    MatrixData matrixdata = camera.getMatrixData(frameBuffer.width, frameBuffer.height);
    textObject.setViewProjectionMatrix(matrixdata.VP, matrixdata.V, matrixdata.P);
    textObject.font = text.font;
    textObject.setPosition(glm::vec3(text.x, text.y, 0.0f));
    //textObject.scale = text.scale;
    textObject.text = text.text;
    textObject.rotation = text.rotation;
    textObject.color = text.color;
    textObject.draw();
}

void Graphics::drawMainView() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glClearColor(0.1f, 0.5f, 0.0f, 1.0f);
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
    imageObject.draw(&frameBuffers[0]->shader);
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
    //std::cout << "a " << relX << " b " << relY << "\n";
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