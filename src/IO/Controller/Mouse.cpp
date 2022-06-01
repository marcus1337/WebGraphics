#include "Mouse.h"
#include <GLFW/glfw3.h>
#include <iostream>


void Mouse::drag(int toPosX, int toPosY)
{
    if (!hasInitPos)
    {
        x = toPosX;
        y = toPosY;
        hasInitPos = true;
    }
    deltaX += toPosX - x;
    deltaY += y - toPosY; // reversed since y-coordinates go from bottom to top
    x = toPosX;
    y = toPosY;
}

void Mouse::click(int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        isLeftPress = true;
        isLeftPressed = true;
    }
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
    {
        isLeftPressed = false;
        isLeftReleased = true;
    }
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
    {
        isRightPress = true;
        isRightPressed = true;
    }
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE)
    {
        isRightReleased = true;
        isRightPressed = false;
    }
}

void Mouse::clearDeltas()
{
    deltaX = deltaY = 0;
    scrollDelta = 0;
}

void Mouse::reset()
{
    isRightReleased = isLeftReleased = false;
    isRightPress = isLeftPress = false;
    clearDeltas();
}