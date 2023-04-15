#ifndef MOUSE_H
#define MOUSE_H
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <map>

enum class MouseButton {
    LEFT, RIGHT
};

struct ButtonState {
    bool pressed = false;
    bool pressEvent = false;
    bool unPressEvent = false;
    void clearEvents() {
        pressEvent = false;
        unPressEvent = false;
    }
};

class Mouse
{

    double xDragDelta = 0;
    double yDragDelta = 0;
    double scrollDelta = 0;
    double x = 0.0f;
    double y = 0.0f;
    std::map<MouseButton, ButtonState> buttons;

public:    
    
    Mouse();
    double getX();
    double getY();
    double getDragDeltaX();
    double getDragDeltaY();
    double getScrollDelta();
    bool isPressed(MouseButton btn);
    bool isPressEvent(MouseButton btn);
    bool isUnPressEvent(MouseButton btn);

    //Update methods
    void addScroll(double _scrollDelta);
    void addDrag(int _x, int _y);
    void onButtonPress(MouseButton btn);
    void onButtonLift(MouseButton btn);
    void reset();

};

#endif