#include <glm/glm.hpp>
#include <glm/ext.hpp>

#ifndef MOUSE_H
#define MOUSE_H

class Mouse
{

public:

    bool isLeftPressed = false;
    bool isRightPressed = false;
    bool isLeftReleased = false;
    bool isRightReleased = false;
    bool isRightPress = false;
    bool isLeftPress = false;
    
    double deltaX = 0;
    double deltaY = 0;
    double scrollDelta = 0;
    double x = 0.0f;
    double y = 0.0f;
    bool hasInitPos = false;
    
    void drag(int toPosX, int toPosY);
    void click(int button, int action, int mods);

    void clearDeltas();
    void reset();

};

#endif