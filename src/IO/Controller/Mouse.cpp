#include "Mouse.h"
#include <GLFW/glfw3.h>

glm::vec2 Mouse::getRelativeMousePosition(int windowWidth, int windowHeight, double _fromX, double _fromY, double _toX, double _toY)
{
    if (windowWidth == 0.0f || windowHeight == 0.0f)
        return glm::vec2(0, 0);

    glm::vec2 relativeMousePosition = glm::vec2(mouseX / (double)windowWidth, mouseY / (double)windowHeight);
    relativeMousePosition.x -= _fromX;
    relativeMousePosition.y -= _fromY;
    relativeMousePosition.x /= (_toX - _fromX);
    relativeMousePosition.y /= (_toY - _fromY);
    return relativeMousePosition;
}

void Mouse::drag(int toPosX, int toPosY)
{
    if (!hasInitMousePos)
    {
        mouseX = toPosX;
        mouseY = toPosY;
        hasInitMousePos = true;
    }
    deltaMouseX += toPosX - mouseX;
    deltaMouseY += mouseY - toPosY; // reversed since y-coordinates go from bottom to top
    mouseX = toPosX;
    mouseY = toPosY;
}

void Mouse::click(int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        isLeftPressed = true;
    }
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
    {
        isLeftPressed = false;
    }
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
    {
        isRightPressed = true;
    }
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE)
    {
        isRightPressed = false;
    }
}

void Mouse::clearDeltas()
{
    deltaMouseX = deltaMouseY = 0;
}

void Mouse::beginPress(bool& _wasPressed, bool& _wasReleased, bool& _isPressed){
    if (!_wasPressed && _isPressed)
        _wasPressed = true;
    if (_wasPressed && !_isPressed)
    {
        _wasPressed = false;
        _wasReleased = true;
    }
}

void Mouse::beginFrame()
{
    beginPress(wasLeftPressed, wasLeftReleased, isLeftPressed);
    beginPress(wasRightPressed, wasRightReleased, isRightPressed);
}
void Mouse::endFrame()
{
    if (wasLeftReleased)
        wasLeftReleased = false;
    if (wasRightReleased)
        wasRightReleased = false;
    clearDeltas();
}