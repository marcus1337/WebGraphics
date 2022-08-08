#include "Utility/GLData.h"
#include "Window/Canvas.h"
#include "Graphics/Objects/ImageObject.h"
#include "Utility/MatrixData.h"
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
    GLData glData;

private:
    Canvas& window;
    void drawMainView();
    FrameBuffer mainView;
    std::size_t viewIndex = 0;

public:
    ImageObject imageObject;
    TextObject textObject;
    glm::vec3 backgroundColor, outerBackgroundColor;

    Graphics(Canvas& _window);
    ~Graphics();

    void clearView();
    void display();
};

#endif // !GRAPHICS_H
