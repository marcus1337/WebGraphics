#include "Utility/GLData.h"
#include "Window/Window.h"
#include "Graphics/ImageObject.h"
#include "Utility/MatrixData.h"
#include "Graphics/Shader.h"
#include "Graphics/TextObject.h"
#include "Graphics/FrameBuffer.h"
#include "Window/Camera.h"
#include "Drawables/View.h"
#include "Drawables/Image.h"
#include "Drawables/Text.h"

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
    ImageObject imageObject;
    Shader imageShader;

    TextObject textObject;
    GLData glData;
    Window& window;

    void drawMainView();
    std::vector<FrameBuffer*> frameBuffers;
    FrameBuffer* makeFrameBuffer(int width, int height);
public:
    Graphics(Window& _window);
    ~Graphics();

    void clearViews();
    void display();
    void initViews(std::vector<View> views);
    void drawImage(Image& image, std::size_t viewID = 0);
    void drawText(Text& text, std::size_t viewID = 0);
    std::pair<int, int> getPixelPosition(int _x, int _y, std::size_t viewID = 0);
    bool isInsideView(int _x, int _y, std::size_t viewID = 0);
};

#endif // !GRAPHICS_H
