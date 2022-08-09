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