#include "Image.h"
#include "Text.h"
#include <functional>
#include "IO/Controller/Mouse.h"
#include <Engine/Graphics.h>
#include "ShaderTimer.h"

#ifndef BUTTON_H
#define BUTTON_H

enum class ButtonType {
    PLAIN, CARD, SETTING, LOBBY
};

class Button {
    Image* makeImage(ButtonType _buttonType);
    bool pressed = false;
    bool holdPress = false;

    glm::vec3 getHighlightColor();
    glm::vec3 getPressedColor();
    glm::vec3 getDefaultColor();

    glm::vec3 nullColor = { 0.0f,0.0f,0.0f };
    int viewIndex = 0;
    bool active = true;
    bool highlighted = false;
    glm::vec3 highlightColor = { 0.0f, 0.05f, 0.0f };
    glm::vec3 pressedColor = { 0.0f, 0.1f, 0.0f };
    glm::vec3 defaultColor = { 0,0,0 };
    Text text;
    Image* image = nullptr;
    ShaderTimer shaderTimer;

    bool isPointerInside(int _x, int _y);
    void update(int _x, int _y, bool _isPress, bool _isRelease);
    void onPress(int _x, int _y);
    void onRelease(int _x, int _y);
    void onHover(int _x, int _y);
    void onHoverEnter(int _x, int _y);
    void onHoverExit(int _x, int _y);

    float getMouseXInterval(int _x);
    float getMouseYInterval(int _y);

public:
    Button(ButtonType _buttonType = ButtonType::PLAIN);
    Button(const Button& _button);
    ~Button();
    Button& operator=(const Button& _button);
    std::function<void(void)> onPressCallback;

    void setActive(bool _isActive);
    bool isHighlighted();

    void setColor(glm::vec3 _color);
    void setTextColor(glm::vec3 _color);
    void setBorderColor(glm::vec3 _color);
    void setAlpha(float _alpha);

    void setDark(bool _dark);
    void setGray(bool _gray);
    void setText(std::string _text);
    void setTextPixelHeight(int _pixelHeight);
    void setBorderSize(int _size);
    void setTexture(std::string _texture);
    
    void setSize(int _width, int _height);
    void setPosition(int _x, int _y);
    void setHoldPress(bool _holdPress);
    bool isHoldingPress();
    bool isActive();
    void update(Graphics& _graphics, Mouse& _mouse);
    void centerText(Graphics& _graphics);
    void render(Graphics& _graphics, Mouse& _mouse);
    int getWidth();
    int getHeight();
    int getX();
    int getY();
};

#endif // !BUTTON_H