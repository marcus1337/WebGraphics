#include <Engine/Engine.h>
#include <Engine/Graphics.h>
#include <Drawables/View.h>
#include <Drawables/Image.h>
#include <Drawables/Text.h>
#include <Drawables/ShaderTimer.h>
#include <functional>

#ifndef UIELEMENT_H
#define UIELEMENT_H

class UIElement {

protected:
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

    virtual void setActive();
    virtual void setInactive();
    virtual void update() = 0;
    virtual void render() = 0;

    bool isHovered();
};

#endif