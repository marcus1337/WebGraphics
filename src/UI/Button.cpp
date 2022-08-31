#include "Button.h"
#include <utility>

Button::Button(Engine& _engine) : engine(_engine), graphics(_engine.graphics), view(_engine, 200, 100) {
    Text text(engine);
    text.setText("Button");
    text.setPixelHeight(40);
    text.setColor({ 0.9,0.9,0.9 });
    setText(text);
    view.setShaderProgram("button");
}

void Button::render() {
    shaderTimer.updateEffectInterpolation();
    view.setEffect(shaderTimer.effectInterpolation);
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

void Button::setText(Text& _text){
    paintImage();
    _text.center(view.getX(), view.getY(), view.getWidth(), view.getHeight()); 
    view.paint(_text);
}

void Button::paintImage() {
    Image img(engine, imageName);
    img.setSize(view.getWidth(), view.getHeight());
    view.paint(img);
}

void Button::setImage(std::string _imageName) {
    imageName = _imageName;
    paintImage();
}