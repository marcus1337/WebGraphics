#include "Utility/GLData.h"
#include "Window/Window.h"
#include "Graphics/ImageObject.h"
#include "Utility/MatrixData.h"
#include "Graphics/Shader.h"
#include "Graphics/TextObject.h"
#include "Graphics/FrameBuffer.h"
#include "Window/Camera.h"

#include <stack>
#include <tuple>
#include <functional>
#include <chrono>
#include <thread>
#include <string>
#include <iostream>
#include <vector>


#ifndef GRAPHICS_H
#define GRAPHICS_H

class Graphics {

    Camera camera;
    ImageObject image;
    Shader imageShader;
    FrameBuffer framebuffer;

    TextObject text;
    GLData glData;

    void preDraw();
    Window& window;
public:
    Graphics(Window& _window);
    ~Graphics();

    void draw();

    FrameBuffer& getDefaultView();

};

#endif // !GRAPHICS_H
