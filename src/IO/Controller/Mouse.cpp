#include "Mouse.h"
#include <GLFW/glfw3.h>

glm::vec2 Mouse::getRelativePosition(int windowWidth, int windowHeight, double _fromX, double _fromY, double _toX, double _toY)
{
    if (windowWidth == 0.0f || windowHeight == 0.0f)
        return glm::vec2(0, 0);

    glm::vec2 relativePosition = glm::vec2(x / (double)windowWidth, y / (double)windowHeight);
    relativePosition.x -= _fromX;
    relativePosition.y -= _fromY;
    relativePosition.x /= (_toX - _fromX);
    relativePosition.y /= (_toY - _fromY);
    return relativePosition;
}

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
    deltaX = deltaY = 0;
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