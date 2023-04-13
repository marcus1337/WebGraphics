
#ifndef MAINVIEW_H
#define MAINVIEW_H
#include "Window/Canvas.h"
#include "Graphics/FrameBuffer.h"
#include <iostream>
#include "IO/Files/Texture/IOTexture.h"
#include "IO/Files/Shader/IOShader.h"
#include "Graphics/Objects/ImageObject.h"

class MainView {

    glm::vec3 outerBackgroundColor;

    const int maxWidth = 1920;
    const int maxHeight = 1080;
    FrameBuffer frame;
    Canvas& window;
    std::pair<int, int> getPixelPosition(int _x, int _y);
    void render();

public:
    MainView(Canvas& _window);

    int getX();
    int getY();
    int getWidth();
    int getHeight();
    void use();
    void clear();
    void display();
    std::pair<int, int> getMousePosition();

};

#endif
