#include <Engine/Engine.h>
#include <Engine/Graphics.h>
#include <Drawables/View.h>
#include <Drawables/Image.h>
#include <Drawables/Text.h>
#include <Drawables/ShaderTimer.h>
#include <functional>
#include "UIElement.h"

#ifndef BUTTON_H
#define BUTTON_H

class Button : public UIElement {
    View view;
    bool pressed = false;
    bool isPointerInside();
    void onRelease();
    std::string imageName = "button1.png";
    void paintImage();

public:

    Button(Engine& _engine, int pixelWidth, int pixelHeight);
    virtual void render() override;
    virtual void update() override;
    void setText(Text& _text);
    void setPosition(int _x, int _y);
    void setImage(std::string _imageName);
    void paint(Drawable& drawable);
    void clearView();
    std::function<void(void)> onPressCallback;

};

#endif // !BUTTON_H
