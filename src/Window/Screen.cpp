#include "Screen.h"
#include <iostream>

#if defined(_MSC_VER)
    #include "GL/wglew.h"
#elif defined(EMSCRIPTEN)
#elif defined(__GNUG__) 
    #include <GL/glxew.h>
    #include <GL/glx.h>
#endif


auto Screen::mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    Screen* mw = static_cast<Screen*>(glfwGetWindowUserPointer(window));
    mw->mouse.click(button, action, mods);
}

auto Screen::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    Screen* mw = static_cast<Screen*>(glfwGetWindowUserPointer(window));
    mw->keyboard.setKeys(window, key, scancode, action, mods);
}

auto Screen::window_size_callback(GLFWwindow* window, int width, int height)
{
    Screen* mw = static_cast<Screen*>(glfwGetWindowUserPointer(window));
    mw->width = width;
    mw->height = height;
    glViewport(0, 0, width, height);
    if(mw->appResizeCallbackFunction)
        mw->appResizeCallbackFunction();
}

auto Screen::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    Screen* mw = static_cast<Screen*>(glfwGetWindowUserPointer(window));
    mw->mouse.drag((int)xpos, mw->height - 1 - (int)ypos);
}

auto Screen::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    Screen* mw = static_cast<Screen*>(glfwGetWindowUserPointer(window));
    mw->mouse.scrollDelta = yoffset;
}

void Screen::autoScreenResize(double yoffset){
    for(int i = 0 ; i < 30; i++)
        if(yoffset > 0){
            aspectRatio.increase();
        }else{
            aspectRatio.decrease();
        }
    resizeWindow(aspectRatio.getWidth(), aspectRatio.getHeight());
}

bool Screen::initWindow() {
    if (initGLFW() == EXIT_FAILURE) {
        return EXIT_FAILURE;
    }
    SetVSync(true);
    return EXIT_SUCCESS;
}

void Screen::resizeWindow(int _width, int _height){
    glfwSetWindowSize(window, _width, _height);
    glViewport(0, 0, _width, _height);
    width = _width;
    height = _height;
}

void Screen::setWindowHints(){
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

void Screen::setWindowCallbacks(GLFWwindow* window){
    glfwSetWindowUserPointer(window, this);
    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetWindowSizeCallback(window, window_size_callback);
}

bool Screen::initGLFW()
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


Screen::Screen() {
    initWindow();
}
Screen::~Screen() {
    glfwTerminate();
}

void Screen::SetVSync(bool sync)
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

bool Screen::hasQuit() {
    return glfwWindowShouldClose(window) || keyboard.quitProgram;
}

void Screen::display() {
    glfwSwapBuffers(window);
}

void Screen::pollEvents() {
    mouse.reset();
    glfwPollEvents();
}