#include "Button.h"

Button::Button(Engine& _engine) : engine(_engine), graphics(_engine.graphics), view(_engine, 200, 100) {
    Image img(engine);
    img.setTexture("button1.png");
    img.setSize(200, 100);
    view.paint(img);
    Text text(engine);
    text.setText("Button1");
    text.setPixelHeight(40);
    text.center(0, 0, 200, 100);
    view.paint(text);
}

void Button::render() {
    view.render();
}

void Button::update() {

}

void Button::setPosition(int _x, int _y) {
    view.setPosition(_x, _y);
}

bool Button::isPointerInside() {
    int mouseX = engine.window.mouse.x;
    int mouseY = engine.window.mouse.y;
    return mouseX >= view.getX() && mouseX <= view.getX() + view.getWidth() && mouseY >= view.getY() && mouseY <= view.getY() + view.getHeight();
}
void Button::onPress() {

}
void Button::onRelease() {

}
void Button::onHover() {

}

