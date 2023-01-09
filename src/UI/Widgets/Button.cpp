#include "Button.h"
#include <utility>

Button::Button(Graphics& _graphics, Mouse& _mouse, IOContainer& _ioContainer, int pixelWidth, int pixelHeight) : UIElement(_graphics, _mouse), view(_graphics, _ioContainer, pixelWidth, pixelHeight), ioContainer(_ioContainer) {
    Text text(_graphics, _ioContainer);
    text.setText("Button");
    text.setPixelHeight(40);
    text.setColor({ 0.9,0.9,0.9 });
    setText(text);
    width = pixelWidth;
    height = pixelHeight;
}

void Button::render() {
    view.setEffect(std::min<float>(shaderTimer.getEffect(), maxEffect));
    if (!isActive())
        view.setEffect(0.0f);
    view.render();
}

void Button::update() {
    if (isHovered() && mouse.isLeftPress)
        pressed = true;
    if (mouse.isLeftReleased)
        onRelease();
    if (isHovered())
        shaderTimer.setAnimationForward();
    else
        shaderTimer.setAnimationBackward();
    if (pressed) {
        view.setColor(pressAddColor);
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

void Button::onRelease() {
    if (isActive() && pressed && isHovered() && onPressCallback)
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
    if (imageName.empty())
        return;

    Image img(graphics, ioContainer, imageName);
    img.setSize(view.getWidth(), view.getHeight());
    view.paint(img);
}

void Button::setMaxEffect(float _effect) {
    maxEffect = _effect;
}

void Button::setPressAddColor(glm::vec3 _color) {
    pressAddColor = _color;
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

void Button::setAlpha(float _alpha) {
    view.setAlpha(_alpha);
}
