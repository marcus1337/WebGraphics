#include <Engine/Engine.h>
#include <Graphics/Graphics.h>
#include <Drawables/View.h>
#include <Drawables/Image.h>
#include <Drawables/Text.h>
#include <functional>
#include "UIElement.h"
#include "IO/Files/IOContainer.h"

#ifndef BUTTON_H
#define BUTTON_H

class Button : public UIElement {
    View view;
    void onRelease();
    std::string imageName = "";
    void paintImage();
    IOContainer& ioContainer;
    float maxEffect = 1.0f;
    glm::vec3 pressAddColor = { 0.1f,0.1f,0.1f };

public:

    Button(Graphics& _graphics, Mouse& _mouse, IOContainer& _ioContainer, int pixelWidth, int pixelHeight);
    virtual void render() override;
    virtual void update() override;
    void setText(Text& _text);
    void setPosition(int _x, int _y);
    void setImage(std::string _imageName);
    void paint(Drawable& drawable);
    void setAlpha(float _alpha);
    void clearView();
    void setMaxEffect(float _effect);
    void setPressAddColor(glm::vec3 _color);
    std::function<void(void)> onPressCallback;

};

#endif // !BUTTON_H
