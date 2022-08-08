#include "Utility/GLData.h"
#include "Window/Canvas.h"
#include "Graphics/Objects/ImageObject.h"
#include "Utility/MatrixData.h"
#include "Graphics/Shaders/Shader.h"
#include "Graphics/Shaders/ImageShader.h"
#include "Graphics/Objects/TextObject.h"
#include "Graphics/FrameBuffer.h"
#include "Graphics/Shaders/TextShader.h"
#include "Window/Camera.h"

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
    Camera camera;
    Canvas& window;

    void drawMainView();
    std::vector<FrameBuffer*> frameBuffers;
    FrameBuffer* makeFrameBuffer(int width, int height);
    std::size_t viewIndex = 0;

public:
    void setViewIndex(std::size_t _viewIndex);
    void setShaderPrograms();
    GLData glData;
    ImageObject imageObject;
    ImageShader imageShader, rectangleShader;
    TextShader textShader;
    TextObject textObject;
    glm::vec3 backgroundColor, outerBackgroundColor;

    Graphics(Canvas& _window);
    ~Graphics();

    void clearViews();
    void clearView(std::size_t viewID = 0);
    void display();
    std::pair<int, int> getPixelPosition(int _x, int _y, std::size_t viewID = 0);
    bool isInsideView(int _x, int _y, std::size_t viewID = 0);
};

#endif // !GRAPHICS_H
