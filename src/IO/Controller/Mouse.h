#include <glm/glm.hpp>
#include <glm/ext.hpp>

#ifndef MOUSE_H
#define MOUSE_H

class Mouse
{

    void beginPress(bool& _wasPressed, bool& _wasReleased, bool& _isPressed);

public:

    bool isLeftPressed = false;
    bool wasLeftPressed = false;
    bool wasLeftReleased = false;

    bool isRightPressed = false;
    bool wasRightPressed = false;
    bool wasRightReleased = false;
    
    double deltaMouseX = 0;
    double deltaMouseY = 0;
    double mouseX = 0.0f;
    double mouseY = 0.0f;
    bool hasInitMousePos = false;
    glm::vec2 getRelativeMousePosition(int windowWidth, int windowHeight, double _fromX = 0.f, double _fromY = 0.f, double _toX = 1.f, double _toY = 1.f);
    
    void drag(int toPosX, int toPosY);
    void click(int button, int action, int mods);

    void clearDeltas();
    void beginFrame();
    void endFrame();

};

#endif