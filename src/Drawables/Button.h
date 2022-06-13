#include "Image.h"
#include "Text.h"
#include <functional>

#ifndef BUTTON_H
#define BUTTON_H

class Button {
    bool isPressed = false;
    bool isPointerInside(int _x, int _y);
    void setTextPositionCenter();

public:
    Image image;
    Text text;
    std::function<void(void)> onPressCallback;
    Button();

    void onPress(int _x, int _y);
    void onRelease(int _x, int _y);
    void onHover(int _x, int _y);
    void setSize(int _width, int _height);
    void setPosition(int _x, int _y);
};

#endif // !BUTTON_H