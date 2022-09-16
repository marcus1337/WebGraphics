#include "UIElement.h"

UIElement::UIElement(Engine& _engine) : engine(_engine), graphics(_engine.graphics), mouse(_engine.window.mouse) {

}

int UIElement::getX() {
    return x;
}
int UIElement::getY() {
    return y;
}
int UIElement::getWidth() {
    return width;
}
int UIElement::getHeight() {
    return height;
}