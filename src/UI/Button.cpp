#include "Button.h"

Button::Button(Engine& _engine) : engine(_engine), graphics(_engine.graphics), view(_engine, 200, 100) {
    Image img(engine, "button1.png");

    img.setSize(200, 100);
    view.paint(img);
    Text text(engine);
    text.setText("Button1");
    text.setPixelHeight(40);
    text.center(0, 0, 200, 100);
    view.paint(text);
    view.setShaderProgram("button");
}

void Button::render() {
    shaderTimer.updateEffectInterpolation();
    view.getShaderRef().effect = shaderTimer.effectInterpolation;
    view.render();
}

void Button::update() {
    if (isPointerInside() && engine.window.mouse.isLeftPress)
        pressed = true;
    if (engine.window.mouse.isLeftReleased)
        onRelease();
    shaderTimer.forwardAnimation = isPointerInside();
    shaderTimer.backAnimation = !shaderTimer.forwardAnimation;
    if (pressed) {
        view.setColor({ 0.1f,0.1f,0.1f }); //
    }
    else {
        view.setColor({ 0,0,0 });
    }
}

void Button::setPosition(int _x, int _y) {
    view.setPosition(_x, _y);
}

bool Button::isPointerInside() {
    auto mousePos = graphics.getPixelPosition(engine.window.mouse.x, engine.window.mouse.y);
    int mouseX = std::get<0>(mousePos);
    int mouseY = std::get<1>(mousePos);
    return mouseX >= view.getX() && mouseX <= view.getX() + view.getWidth() && mouseY >= view.getY() && mouseY <= view.getY() + view.getHeight();
}

void Button::onRelease() {
    if (pressed && isPointerInside() && onPressCallback)
        onPressCallback();
    pressed = false;
}

