#include "Graphics/Shaders/ShaderPrograms.h"
#include "IO/Files/IOTexture.h"
#include "Window/Canvas.h"

#include "Graphics/Objects/ImageObject.h"
#include "Graphics/Shaders/Shader.h"
#include "Graphics/Shaders/ImageShader.h"
#include "Graphics/Objects/TextObject.h"
#include "Graphics/FrameBuffer.h"
#include "Graphics/Shaders/TextShader.h"

#include <stack>
#include <tuple>
#include <functional>
#include <chrono>
#include <thread>
#include <string>
#include <iostream>
#include <vector>
#include <utility>


#ifndef GRAPHICS_H
#define GRAPHICS_H

class Graphics {
public:
    ShaderPrograms shaderPrograms;
    IOTexture iotexture;

private:
    Canvas& window;
    void drawMainView();
    FrameBuffer mainView;
    void setGLSettings();

    int getMainViewWidth();
    int getMainViewHeight();

public:
    ImageObject imageObject;
    TextObject textObject;
    glm::vec3 outerBackgroundColor;

    Graphics(Canvas& _window);
    ~Graphics();

    int getScreenWidth();
    int getScrenHeight();
    void useMainView();
    void clearView();
    void display();
    std::pair<int, int> getPixelPosition(int _x, int _y);
    std::pair<int, int> getMousePixelPosition();
};

#endif // !GRAPHICS_H
