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

void UIElement::setActive() {

}
void UIElement::setInactive() {

}

bool UIElement::isPressed() {
    return pressed;
}

bool UIElement::isHovered() {
    auto mousePos = graphics.getPixelPosition(engine.window.mouse.x, engine.window.mouse.y);
    int mouseX = std::get<0>(mousePos);
    int mouseY = std::get<1>(mousePos);
    return mouseX >= getX() && mouseX <= getX() + getWidth() && mouseY >= getY() && mouseY <= getY() + getHeight();
}
