#include <GLFW/glfw3.h>

#ifndef KEYBOARD_H
#define KEYBOARD_H

class Keyboard
{
public:

    void setKeys(GLFWwindow* window, int key, int scancode, int action, int mods);

    bool quitProgram = false;
    bool goForward = false;
    bool goBack = false;
    bool goLeft = false;
    bool goRight = false;
    bool rotateRight = false;
    bool rotateLeft = false;
};

#endif