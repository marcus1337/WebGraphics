#include "Button.h"
#include <utility>

Button::Button(Engine& _engine, int pixelWidth, int pixelHeight) : UIElement(_engine), view(_engine, pixelWidth, pixelHeight) {
    Text text(engine);
    text.setText("Button");
    text.setPixelHeight(40);
    text.setColor({ 0.9,0.9,0.9 });
    setText(text);
    view.setShaderProgram("button");
    width = pixelWidth;
    height = pixelHeight;
}

void Button::render() {
    shaderTimer.updateEffectInterpolation();
    view.setEffect(shaderTimer.getEffect());
    view.render();
}

void Button::update() {
    if (isPointerInside() && engine.window.mouse.isLeftPress)
        pressed = true;
    if (engine.window.mouse.isLeftReleased)
        onRelease();
    if (isPointerInside())
        shaderTimer.setAnimationForward();
    else
        shaderTimer.setAnimationBackward();
    if (pressed) {
        view.setColor({ 0.1f,0.1f,0.1f }); 
    }
    else {
        view.setColor({ 0,0,0 });
    }
}

void Button::setPosition(int _x, int _y) {
    view.setPosition(_x, _y);
    x = _x;
    y = _y;
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
    _text.center(_text.getX(), _text.getY(), view.getWidth(), view.getHeight());
    view.paint(_text);
}

void Button::paintImage() {
    view.clear();
    Image img(engine, imageName);
    img.setSize(view.getWidth(), view.getHeight());
    view.paint(img);
}

void Button::setImage(std::string _imageName) {
    imageName = _imageName;
    paintImage();
}

void Button::paint(Drawable& drawable) {
    view.paint(drawable);
}

void Button::clearView() {
    view.clear();
}