#include "Window.h"
#include <iostream>

#if defined(_MSC_VER)
    #include "GL/wglew.h"
#elif defined(EMSCRIPTEN)
#elif defined(__GNUG__) 
    #include <GL/glxew.h>
    #include <GL/glx.h>
#endif


auto Window::mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    Window* mw = static_cast<Window*>(glfwGetWindowUserPointer(window));
    mw->mouse.click(button, action, mods);
}

auto Window::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    Window* mw = static_cast<Window*>(glfwGetWindowUserPointer(window));
    mw->keyboard.setKeys(window, key, scancode, action, mods);
}

auto Window::window_size_callback(GLFWwindow* window, int width, int height)
{
    Window* mw = static_cast<Window*>(glfwGetWindowUserPointer(window));
    mw->width = width;
    mw->height = height;
    glViewport(0, 0, width, height);
}

auto Window::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    Window* mw = static_cast<Window*>(glfwGetWindowUserPointer(window));
    mw->mouse.drag(xpos,ypos);
    //mw->resizeToAspectRatio();
}

void Window::scrollScreenResize(double yoffset){
    for(int i = 0 ; i < 30; i++)
        if(yoffset > 0){
            aspectRatio.increase();
        }else{
            aspectRatio.decrease();
        }
    resizeWindow(aspectRatio.getWidth(), aspectRatio.getHeight());
}

auto Window::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    Window* mw = static_cast<Window*>(glfwGetWindowUserPointer(window));
    
#ifndef EMSCRIPTEN
    mw->scrollScreenResize(yoffset);
#endif
}

/*void Window::resizeToAspectRatio() {
    bool shouldResize = aspectRatio.getWidth() != width || aspectRatio.getHeight() != height;
    if(shouldResize){
        aspectRatio.setIndexToClosestAspectRatio(width, height);
        resizeWindow(aspectRatio.getWidth(), aspectRatio.getHeight());
    }
}*/

bool Window::initWindow() {
    if (initGLFW() == EXIT_FAILURE) {
        return EXIT_FAILURE;
    }
    SetVSync(true);
    return EXIT_SUCCESS;
}

void Window::resizeWindow(int _width, int _height){
    glfwSetWindowSize(window, _width, _height);
    glViewport(0, 0, _width, _height);
    width = _width;
    height = _height;
}

void Window::setWindowHints(){
    #ifdef EMSCRIPTEN
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    #else
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    #endif
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
}

void Window::setWindowCallbacks(GLFWwindow* window){
    glfwSetWindowUserPointer(window, this);
    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetWindowSizeCallback(window, window_size_callback);
}

bool Window::initGLFW()
{
    if(GLFW_TRUE != glfwInit()){
        std::clog << "Failed to init glfw\n";
        return EXIT_FAILURE;
    }

    setWindowHints();
    glfwSwapInterval(1);

    window = glfwCreateWindow(width, height, "WebGL_UI", nullptr, nullptr);
    if (nullptr == window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        return EXIT_FAILURE;
    }
    
    setWindowCallbacks(window);
    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    if (GLEW_OK != glewInit())
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return EXIT_FAILURE;
    }

    glfwGetWindowSize(window, &width, &height);
    glViewport(0, 0, width, height);
    
    glEnable(GL_STENCIL_TEST);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    #ifdef EMSCRIPTEN
        std::clog << "version: " << glGetString(GL_VERSION)<< std::endl;
    #endif

    return EXIT_SUCCESS;
}


Window::Window() {
    initWindow();
/*#ifndef EMSCRIPTEN
    resizeToAspectRatio();
#endif*/
}
Window::~Window() {
    glfwTerminate();
}

void Window::SetVSync(bool sync)
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

bool Window::hasQuit() {
    return glfwWindowShouldClose(window) || keyboard.quitProgram;
}

void Window::display() {
    glfwSwapBuffers(window);
}

void Window::pollEvents() {
    mouse.reset();
    glfwPollEvents();
}