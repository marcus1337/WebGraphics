
#ifndef GRAPHICS_H
#define GRAPHICS_H
#include "IO/Files/Texture/IOTexture.h"
#include "IO/Files/Shader/IOShader.h"
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

#include "MainView.h"

class Graphics {
    Canvas& window;
    void setGLSettings();
    GLuint depthBuffer = 0;

public:
    MainView mainView;
    Graphics(Canvas& _window);
    ~Graphics();

};

#endif // !GRAPHICS_H
