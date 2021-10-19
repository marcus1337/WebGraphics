#include "MyWindow.h"
#include <iostream>



auto MyWindow::mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    MyWindow* mw = static_cast<MyWindow*>(glfwGetWindowUserPointer(window));
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        mw->isLeftMousePressed = true;
    }

    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
    {
        mw->isLeftMousePressed = false;
    }

}

void MyWindow::debugKeys(MyWindow* mywindow, GLFWwindow* window) {

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        mywindow->goForward = true;
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_RELEASE) {
        mywindow->goForward = false;
    }

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        mywindow->goBack = true;
    }

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_RELEASE) {
        mywindow->goBack = false;
    }

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        mywindow->goLeft = true;
    }

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_RELEASE) {
        mywindow->goLeft = false;
    }

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        mywindow->goRight = true;
    }

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_RELEASE) {
        mywindow->goRight = false;
    }

    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        mywindow->rotateRight = true;
    }

    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        mywindow->rotateLeft = true;
    }

    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        mywindow->rotateRight = true;
    }

    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        mywindow->rotateLeft = true;
    }

    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_RELEASE) {
        mywindow->rotateRight = false;
    }

    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_RELEASE) {
        mywindow->rotateLeft = false;
    }
}

auto MyWindow::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    MyWindow* mywindow = static_cast<MyWindow*>(glfwGetWindowUserPointer(window));

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
        mywindow->quitProgram = true;
    }

    debugKeys(mywindow, window);

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
    if (mw->firstMouse)
    {
        mw->lastX = xpos;
        mw->lastY = ypos;
        mw->firstMouse = false;
    }

    mw->deltaMouseX += xpos - mw->lastX;
    mw->deltaMouseY += mw->lastY - ypos; // reversed since y-coordinates go from bottom to top
    mw->lastX = xpos;
    mw->lastY = ypos;
}

glm::vec2 MyWindow::getRelativeMousePosition(float _fromX, float _fromY, float _toX, float _toY)
{
    if (SCR_WIDTH == 0.0f || SCR_HEIGHT == 0.0f)
        return glm::vec2(0, 0);

    glm::vec2 relativeMousePosition = glm::vec2(lastX / (float)SCR_WIDTH, lastY / (float)SCR_HEIGHT);
    relativeMousePosition.x -= _fromX;
    relativeMousePosition.y -= _fromY;
    relativeMousePosition.x /= (_toX - _fromX);
    relativeMousePosition.y /= (_toY - _fromY);
    return relativeMousePosition;
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

    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Mototrica", nullptr, nullptr);
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


MyWindow::MyWindow() {}
MyWindow::~MyWindow() {
    glfwTerminate();
}

void MyWindow::moveCamera(Camera& camera) {
    camera.ProcessMouseMovement(deltaMouseX, deltaMouseY);
    deltaMouseX = deltaMouseY = 0;

    if (goForward)
        camera.ProcessKeyboard(FORWARD, 0);
    if (goBack)
        camera.ProcessKeyboard(BACKWARD, 0);
    if (goLeft)
        camera.ProcessKeyboard(LEFT, 0);
    if (goRight)
        camera.ProcessKeyboard(RIGHT, 0);
    if (rotateLeft) {
        camera.ProcessKeyboard(ROTATELEFT, 0);
    }
    if (rotateRight) {
        camera.ProcessKeyboard(ROTATERIGHT, 0);
    }

}


#if defined(_MSC_VER)
    #include "GL/wglew.h"
#elif defined(EMSCRIPTEN)
#elif defined(__GNUG__) 
    #include <GL/glxew.h>
    #include <GL/glx.h>
#endif

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