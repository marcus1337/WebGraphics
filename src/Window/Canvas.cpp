#include "Window/Canvas.h"
#include <iostream>

#if defined(_MSC_VER)
#include "GL/wglew.h"
#elif defined(EMSCRIPTEN)
#elif defined(__GNUG__) 
#include <GL/glxew.h>
#include <GL/glx.h>
#endif
#include "IO/Files/Texture/IOTexture.h"

Canvas::Canvas() {
    if (!initGLFW())
        return;
    SetVSync(true);

    if (isFullScreen())
        setFullScreen(true);
}

Canvas::~Canvas() {
    glfwTerminate();
}

void Canvas::setResizeCallbackFunction(std::function<void(void)> _function) {
    canvasCallbacks.resizeCallbackFunction = _function;
}

void Canvas::resizeWindow(int _width, int _height) {
    glfwSetWindowSize(window, _width, _height);
    glViewport(0, 0, _width, _height);
    canvasSettings.width = _width;
    canvasSettings.height = _height;
    if (canvasCallbacks.resizeCallbackFunction)
        canvasCallbacks.resizeCallbackFunction();
    display();
}

void Canvas::setWindowHints() {
    int versionMajor = 3;
    int versionMinor = 0;
#ifndef EMSCRIPTEN
    versionMajor = 4;
    versionMinor = 5;
#endif
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, versionMajor);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, versionMinor);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
}

int Canvas::getWidth() {
    return canvasSettings.width;
}
int Canvas::getHeight() {
    return canvasSettings.height;
}

bool Canvas::initGLFW()
{
    if (GLFW_TRUE != glfwInit()) {
        std::cout << "Failed to init glfw\n";
        return false;
    }

    setWindowHints();
    glfwSwapInterval(1);
    window = glfwCreateWindow(canvasSettings.width, canvasSettings.height, canvasSettings.appName.c_str(), nullptr, nullptr);
    if (nullptr == window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        return false;
    }

    canvasCallbacks.set(window, &mouse, &keyboard, &canvasSettings);
    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    if (GLEW_OK != glewInit())
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return false;
    }

    glfwGetWindowSize(window, &canvasSettings.width, &canvasSettings.height);
    glViewport(0, 0, canvasSettings.width, canvasSettings.height);
#ifdef EMSCRIPTEN
    std::clog << "version: " << glGetString(GL_VERSION) << std::endl;
#endif
    return true;
}

void Canvas::SetVSync(bool sync)
{
#if defined(_MSC_VER)
    typedef BOOL(APIENTRY* PFNWGLSWAPINTERVALPROC)(int);
    PFNWGLSWAPINTERVALPROC wglSwapIntervalEXT = 0;
    const char* extensions = (char*)glGetString(GL_EXTENSIONS);
    wglSwapIntervalEXT = (PFNWGLSWAPINTERVALPROC)wglGetProcAddress("wglSwapIntervalEXT");
    if (wglSwapIntervalEXT)
        wglSwapIntervalEXT(sync);
#endif

#if defined(__GNUG__)
    glfwSwapInterval(sync);
    //glXSwapIntervalSGI(sync);
#endif
}

bool Canvas::hasQuit() {
    return glfwWindowShouldClose(window) || keyboard.quitProgram;
}

void Canvas::display() {
    glfwSwapBuffers(window);
}

void Canvas::pollEvents() {
    mouse.reset();
    keyboard.reset();
    glfwPollEvents();
}

void Canvas::setIconImage(GLFWimage& image) {
    glfwSetWindowIcon(window, 1, &image);
}

void Canvas::setFullScreen(bool _fullScreen) {
    canvasSettings.fullScreen = _fullScreen;
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    if (_fullScreen) {
        glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, 0);
    }
    else {
        int xOffset = 200;
        int yOffset = 150;
        int _w = std::max<int>(mode->width - xOffset * 2, 10);
        int _h = std::max<int>(mode->height - yOffset * 2, 10);
        glfwSetWindowMonitor(window, NULL, xOffset, yOffset, _w, _h, 0);
    }

}
bool Canvas::isFullScreen() {
    return canvasSettings.fullScreen;
}

void Canvas::setTitle(std::string _title) {
    glfwSetWindowTitle(window, _title.c_str());
}
