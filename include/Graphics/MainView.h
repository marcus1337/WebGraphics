
#ifndef MAINVIEW_H
#define MAINVIEW_H
#include "Window/Canvas.h"
#include "Graphics/FrameBuffer.h"
#include <iostream>
#include "IO/Files/Texture/IOTexture.h"
#include "IO/Files/Shader/IOShader.h"
#include "Graphics/Objects/ImageObject.h"
#include <memory>
#include <tuple>

class MainView {

    glm::vec3 outerBackgroundColor;
    std::shared_ptr<FrameBuffer> frame;
    Canvas& window;
    std::pair<int, int> getPixelPosition(int _x, int _y);
    void render();
    void useDefaultFramebuffer();
    void setFrameModel();
    void setFrameCamera();
    std::pair<int, int> getAspectRatio();

public:
    MainView(Canvas& _window);

    int getX();
    int getY();
    int getWidth();
    int getHeight();
    void setSize(int width, int height);
    void use();
    void clear();
    void display();
    std::pair<int, int> getMousePosition();

};

#endif
