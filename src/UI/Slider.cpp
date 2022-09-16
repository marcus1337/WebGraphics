#include "Slider.h"
#include <Drawables/Rect.h>
#include <Drawables/Line.h>

Slider::Slider(Engine& _engine, int pixelWidth, int pixelHeight) : UIElement(_engine), view(_engine, pixelWidth, pixelHeight) {
    width = pixelWidth;
    height = pixelHeight;
}
void Slider::render() {
    view.clear();
    Rect background(engine);
    background.setColor(backgroundColor);
    background.setSize(view.getWidth(), view.getHeight());
    background.setAlpha(backgroundAlpha);
    int padding = std::max<int>(view.getWidth() / 100, 5);

    Line line(engine, padding, view.getHeight() / 2, view.getWidth() - padding, view.getHeight() / 2);
    line.setColor(lineColor);
    Rect valueBox(engine);
    valueBox.setSize(padding, view.getHeight());
    valueBox.setPosition((int)(padding + getValue() * (view.getWidth()-padding*2) - valueBox.getWidth() / 2), 0);
    valueBox.setColor(boxColor);
    valueBox.setThickness(1.0f);
    valueBox.setRadius(0.1f);

    view.paint(background);
    view.paint(line);
    view.paint(valueBox);
    view.render();
}
void Slider::update() {
    if (onValueChangeCallback && pressed && mouse.deltaX != 0.0) {
        auto mousePos = engine.graphics.getMousePixelPosition();
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
    auto mousePos = graphics.getPixelPosition(engine.window.mouse.x, engine.window.mouse.y);
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
void Slider::setBackgroundColor(glm::vec3 _color) {
    backgroundColor = _color;
}
void Slider::setBackgroundAlpha(float _alpha) {
    backgroundAlpha = _alpha;
}

