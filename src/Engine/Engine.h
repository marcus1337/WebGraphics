#include "Utility/GLData.h"
#include "Window/Window.h"
#include "Window/Image.h"
#include "Utility/MatrixData.h"
#include "Window/Shader.h"
#include "Window/Text.h"
#include "Window/Framebuffer.h"
#include "Window/Camera.h"

#include <stack>
#include <tuple>
#include <functional>
#include <chrono>
#include <thread>
#include <string>
#include <iostream>
#include <vector>

#include "Graphics.h"

#ifndef ENGINE_H
#define ENGINE_H

class Engine {
public:
    Window window;
    Graphics graphics;
private:
    void setGLSettings();

public:
    Engine();
    ~Engine();
};

#endif // !ENGINE_H
