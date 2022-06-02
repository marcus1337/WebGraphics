#include "Image.h"
#include "Text.h"
#include <functional>

#ifndef BUTTON_H
#define BUTTON_H

class Button {

    Image image;
    Text text;
    bool isPressed = false;
    bool isPointerInside(int _x, int _y);

public:
    std::function<void(void)> onPressCallback;
    Button();

    void onPress(int _x, int _y);
    void onRelease(int _x, int _y);
    void onHover(int _x, int _y);
    void setSize(int _width, int _height);
    void setPosition(int _x, int _y);
    Image getImage();
    Text getText();
};

#endif // !BUTTON_H