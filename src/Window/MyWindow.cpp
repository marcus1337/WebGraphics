#include "MyWindow.h"
#include <iostream>

#if defined(_MSC_VER)
    #include "GL/wglew.h"
#elif defined(EMSCRIPTEN)
#elif defined(__GNUG__) 
    #include <GL/glxew.h>
    #include <GL/glx.h>
#endif


auto MyWindow::mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    MyWindow* mw = static_cast<MyWindow*>(glfwGetWindowUserPointer(window));
    mw->mouse.click(button, action, mods);
}

auto MyWindow::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    MyWindow* mw = static_cast<MyWindow*>(glfwGetWindowUserPointer(window));
    mw->keyboard.setKeys(window, key, scancode, action, mods);
}

auto MyWindow::window_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    MyWindow* mywindow = static_cast<MyWindow*>(glfwGetWindowUserPointer(window));
    mywindow->SCR_WIDTH = width;
    mywindow->SCR_HEIGHT = height;
}

auto MyWindow::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    MyWindow* mw = static_cast<MyWindow*>(glfwGetWindowUserPointer(window));
    mw->mouse.drag(xpos,ypos);
}

auto MyWindow::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    MyWindow* mw = static_cast<MyWindow*>(glfwGetWindowUserPointer(window));
}

bool MyWindow::initWindow() {
    if (initGLFW() == EXIT_FAILURE) {
        return EXIT_FAILURE;
    }
    SetVSync(true);
    return EXIT_SUCCESS;
}

void MyWindow::resizeWindow(int _width, int _height){
    glfwSetWindowSize(window, _width, _height);
    glViewport(0, 0, _width, _height);
    SCR_WIDTH = _width;
    SCR_HEIGHT = _height;
}

void MyWindow::setWindowHints(){
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

void MyWindow::setWindowCallbacks(GLFWwindow* window){
    glfwSetWindowUserPointer(window, this);
    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwGetFramebufferSize(window, &SCR_WIDTH, &SCR_WIDTH);
    glfwSetWindowSizeCallback(window, window_size_callback);
}

bool MyWindow::initGLFW()
{
    if(GLFW_TRUE != glfwInit()){
        std::clog << "Failed to init glfw\n";
        return EXIT_FAILURE;
    }

    setWindowHints();
    glfwSwapInterval(1);

    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "WebGL_UI", nullptr, nullptr);
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

    glfwGetWindowSize(window, &SCR_WIDTH, &SCR_HEIGHT);
    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
    
    glEnable(GL_STENCIL_TEST);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    #ifdef EMSCRIPTEN
        std::clog << "version: " << glGetString(GL_VERSION)<< std::endl;
    #endif

    return EXIT_SUCCESS;
}


MyWindow::MyWindow() {
    initWindow();
}
MyWindow::~MyWindow() {
    glfwTerminate();
}

void MyWindow::SetVSync(bool sync)
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