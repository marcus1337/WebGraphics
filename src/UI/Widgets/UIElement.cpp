#include "UIElement.h"

UIElement::UIElement(Graphics& _graphics, Mouse& _mouse) : graphics(_graphics), mouse(_mouse) {

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

void UIElement::setActive(bool _active) {
    active = _active;
}

bool UIElement::isActive() {
    return active;
}

bool UIElement::isPressed() {
    if (!isActive())
        return false;
    return pressed;
}

bool UIElement::isHovered() {
    if (!isActive())
        return false;
    auto mousePos = graphics.mainView.getMousePosition();
    int mouseX = std::get<0>(mousePos);
    int mouseY = std::get<1>(mousePos);
    return mouseX >= getX() && mouseX <= getX() + getWidth() && mouseY >= getY() && mouseY <= getY() + getHeight();
}
