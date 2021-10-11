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
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) {
        mywindow->increaseZoom = true;
        mywindow->decreaseZoom = false;
    }
    if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) {
        mywindow->increaseZoom = false;
        mywindow->decreaseZoom = true;
    }

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

    mywindow->P11 = 1.f / tanf(glm::radians(mywindow->camera.Zoom) / 2.f);
    mywindow->projection = glm::perspective(glm::radians(mywindow->camera.Zoom), (float)mywindow->SCR_WIDTH / (float)mywindow->SCR_HEIGHT, 0.1f, 1000.0f);
    mywindow->view = mywindow->camera.GetViewMatrix();
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

    float xoffset = xpos - mw->lastX;
    float yoffset = mw->lastY - ypos; // reversed since y-coordinates go from bottom to top
    mw->lastX = xpos;
    mw->lastY = ypos;

    mw->setRelMousePos();
    mw->camera.ProcessMouseMovement(xoffset, yoffset);
}

void MyWindow::setRelMousePos(float _fromX, float _fromY, float _toX, float _toY)
{
    glm::vec2 relativeMousePosition = getRelativeMousePosition();
    relativeMousePosition.x -= _fromX;
    relativeMousePosition.y -= _fromY;
    float xLen = _toX - _fromX;
    float yLen = _toY - _fromY;
    relativeMousePosition.x = relativeMousePosition.x / xLen;
    relativeMousePosition.y = relativeMousePosition.y / yLen;
    relativeMouseX = relativeMousePosition.x;
    relativeMouseY = relativeMousePosition.y;
}

auto MyWindow::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    MyWindow* mw = static_cast<MyWindow*>(glfwGetWindowUserPointer(window));
    //mw->camera.ProcessMouseScroll(yoffset);

}

#if defined(_MSC_VER)
    #include "GL/wglew.h"
#elif defined(EMSCRIPEN)
#elif defined(__GNUG__) 
    //#include <GL/glxew.h>
    //#include <GL/glx.h>
#endif

void SetVSync(bool sync)
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

bool MyWindow::initWindow() {
    if (initGLFW() == EXIT_FAILURE) {
        return EXIT_FAILURE;
    }

    SetVSync(true);

    return EXIT_SUCCESS;
}




bool MyWindow::initGLFW()
{
    if(GLFW_TRUE != glfwInit()){
        std::clog << "Failed to init glfw\n";
        return EXIT_FAILURE;
    }

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
    glfwSwapInterval(1);
    
    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Mototrica", nullptr, nullptr);
    if (nullptr == window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return EXIT_FAILURE;
    }
    
    glfwSetWindowUserPointer(window, this);
    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwGetFramebufferSize(window, &SCR_WIDTH, &SCR_WIDTH);
    glfwSetWindowSizeCallback(window, window_size_callback);
    
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

    #ifndef EMSCRIPTEN
    #endif
    #ifdef EMSCRIPTEN
        std::clog << "version: " << glGetString(GL_VERSION)<< std::endl;
    #endif

    return EXIT_SUCCESS;
}


MyWindow::MyWindow() :camera(glm::vec3(0.0f, 0.0f, 4.0f)) {}


glm::vec2 MyWindow::getRelativeMousePosition() {
    if (SCR_WIDTH == 0.0f || SCR_HEIGHT == 0.0f)
        return glm::vec2(0, 0);
    return glm::vec2(lastX / (float)SCR_WIDTH, lastY / (float)SCR_HEIGHT);
}


void MyWindow::handleFrame() {

    if (SCR_HEIGHT == 0)
        SCR_HEIGHT = 1;

    P11 = 1.f / tanf(glm::radians(camera.Zoom) / 2.f);
    projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.2f, 500.0f);
    view = camera.GetViewMatrix();
}

MyWindow::~MyWindow() {
    glfwTerminate();
}

void MyWindow::processActions() {

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