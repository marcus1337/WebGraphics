#include "Keyboard.h"

void Keyboard::setKeys(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        goForward = true;
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_RELEASE)
    {
        goForward = false;
    }

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        goBack = true;
    }

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_RELEASE)
    {
        goBack = false;
    }

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        goLeft = true;
    }

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_RELEASE)
    {
        goLeft = false;
    }

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        goRight = true;
    }

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_RELEASE)
    {
        goRight = false;
    }

    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
    {
        rotateRight = true;
    }

    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
    {
        rotateLeft = true;
    }

    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
    {
        rotateRight = true;
    }

    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
    {
        rotateLeft = true;
    }

    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_RELEASE)
    {
        rotateRight = false;
    }

    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_RELEASE)
    {
        rotateLeft = false;
    }
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        quitProgram = true;
    }
}