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

#include "MainView.h"


#ifndef GRAPHICS_H
#define GRAPHICS_H

class Graphics {
public:
    ShaderPrograms shaderPrograms;
    IOTexture& ioTexture;
    IOFonts& ioFonts;

private:
    Canvas& window;
    void drawMainView();
    void setGLSettings();

public:
    ImageObject imageObject;
    TextObject textObject;
    MainView mainView;

    Graphics(Canvas& _window, IOShader& _ioShader, IOTexture& _ioTexture, IOFonts& _ioFonts);
    ~Graphics();

};

#endif // !GRAPHICS_H
