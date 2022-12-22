#include "Slider.h"
#include <Drawables/Rect.h>
#include <Drawables/Line.h>

Slider::Slider(Engine& _engine, int pixelWidth, int pixelHeight) : UIElement(_engine), view(*_engine.graphics, _engine.ioContainer, pixelWidth, pixelHeight) {
    width = pixelWidth;
    height = pixelHeight;
}
void Slider::render() {
    view.clear();
    Rect background(*engine.graphics, engine.ioContainer);
    background.setColor(backgroundColor);
    background.setSize(view.getWidth(), view.getHeight());
    background.setAlpha(backgroundAlpha);
    int padding = std::max<int>(view.getWidth() / 100, 5);

    Rect valueBox(*engine.graphics, engine.ioContainer);
    valueBox.setSize(padding, view.getHeight());
    valueBox.setPosition((int)(padding + getValue() * (view.getWidth()-padding*2) - valueBox.getWidth() / 2), 0);
    valueBox.setColor(boxColor);
    valueBox.setThickness(1.0f);
    valueBox.setRadius(0.1f);

    Line line(*engine.graphics, engine.ioContainer, padding, view.getHeight() / 2, view.getWidth() - padding, view.getHeight() / 2);
    line.setColor(lineColor);

    Line markedLine(*engine.graphics, engine.ioContainer, padding, view.getHeight() / 2, valueBox.getX(), view.getHeight() / 2);
    markedLine.setLineWidth(8);
    markedLine.setColor(markedLineColor);

    view.paint(background);
    view.paint(line);
    view.paint(markedLine);
    view.paint(valueBox);
    view.render();
}
void Slider::update() {
    if (!active)
        return;

    if (onValueChangeCallback && pressed && mouse.deltaX != 0.0) {
        auto mousePos = engine.graphics->mainView.getMousePosition();
        value = ((float)std::get<0>(mousePos) - (float)view.getX())/(float)view.getWidth();
        value = std::clamp<float>(value, 0.0f, 1.0f);
        onValueChangeCallback(value);
    }

    if (isPointerInside() && engine.window.mouse.isLeftPress)
        pressed = true;
    if (engine.window.mouse.isLeftReleased)
        pressed = false;
}

void Slider::setValue(float _value) {
    value = _value;
}

float Slider::getValue() {
    return value;
}

bool Slider::isPointerInside() {
    auto mousePos = graphics.mainView.getMousePosition();
    int mouseX = std::get<0>(mousePos);
    int mouseY = std::get<1>(mousePos);
    return mouseX >= view.getX() && mouseX <= view.getX() + view.getWidth() && mouseY >= view.getY() && mouseY <= view.getY() + view.getHeight();
}

void Slider::setPosition(int _x, int _y) {
    view.setPosition(_x, _y);
    x = _x;
    y = _y;
}
void Slider::setBoxColor(glm::vec3 _color) {
    boxColor = _color;
}
void Slider::setLineColor(glm::vec3 _color) {
    lineColor = _color;
}
void Slider::setMarkedLineColor(glm::vec3 _color) {
    markedLineColor = _color;
}
void Slider::setBackgroundColor(glm::vec3 _color) {
    backgroundColor = _color;
}
void Slider::setBackgroundAlpha(float _alpha) {
    backgroundAlpha = _alpha;
}

void Slider::setActive(bool _active) {
    active = _active;
    if(active)
        view.setAlpha(1.0f);
    else
        view.setAlpha(0.7f);
}


