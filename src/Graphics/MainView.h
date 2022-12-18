#include "IO/Files/IOTexture.h"
#include "Window/Canvas.h"
#include "Graphics/FrameBuffer.h"
#include <iostream>
#include "IO/Files/IOTexture.h"
#include "Graphics/Shaders/ShaderPrograms.h"
#include "Graphics/Objects/ImageObject.h"


#ifndef MAINVIEW_H
#define MAINVIEW_H

class MainView {

    glm::vec3 outerBackgroundColor;

    const int maxWidth = 1920;
    const int maxHeight = 1080;
    FrameBuffer view;
    Canvas& window;
    ImageObject& imageObject;

    std::pair<int, int> getPixelPosition(int _x, int _y);
    void render();

public:
    MainView(Canvas& _window, ImageObject& _imageObject, ShaderPrograms& _shaderPrograms, IOTexture& _iotexture);

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
