#include <Engine/Engine.h>
#include <Graphics/Graphics.h>
#include <Drawables/View.h>
#include <Drawables/Image.h>
#include <Drawables/Text.h>
#include <functional>
#include "UIElement.h"

#ifndef SLIDER_H
#define SLIDER_H

class Slider : public UIElement {
    View view;
    float value = 0.5f;
    bool isPointerInside();
    glm::vec3 lineColor = { 0,0,0 };
    glm::vec3 markedLineColor = { 0,0,0 };
    glm::vec3 boxColor = { 0.8f, 0.0f, 0.0f };
    glm::vec3 backgroundColor = { 0.5f,0.5f,0.5f };
    float backgroundAlpha = 0.6f;
    bool active = true;

public:
    Slider(Engine& _engine, int pixelWidth, int pixelHeight);
    virtual void render() override;
    virtual void update() override;
    void setValue(float _value);
    float getValue();
    std::function<void(float)> onValueChangeCallback;
    void setPosition(int _x, int _y);
    void setBoxColor(glm::vec3 _color);
    void setLineColor(glm::vec3 _color);
    void setMarkedLineColor(glm::vec3 _color);
    void setBackgroundColor(glm::vec3 _color);
    void setBackgroundAlpha(float _alpha);
    virtual void setActive(bool _active) override;
    
};

#endif