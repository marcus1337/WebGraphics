#include <Engine/Engine.h>
#include <Graphics/Graphics.h>
#include <Drawables/View.h>
#include <Drawables/Image.h>
#include <Drawables/Text.h>
#include "UI/ShaderTimer.h"
#include <functional>

#ifndef UIELEMENT_H
#define UIELEMENT_H

class UIElement {

protected:
    bool active = true;
    bool pressed = false;
    int x = 0;
    int y = 0;
    int width = 0;
    int height = 0;
    Engine& engine;
    Graphics& graphics;
    Mouse& mouse;
    ShaderTimer shaderTimer;

public:

    UIElement(Engine& _engine);
    virtual ~UIElement() = default;

    int getX();
    int getY();
    int getWidth();
    int getHeight();
    bool isPressed();

    bool isActive();
    virtual void setActive(bool _active);
    virtual void update() = 0;
    virtual void render() = 0;

    bool isHovered();
};

#endif