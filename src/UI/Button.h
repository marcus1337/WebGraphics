#include <Engine/Engine.h>
#include <Engine/Graphics.h>
#include <Drawables/View.h>
#include <Drawables/Image.h>
#include <Drawables/Text.h>

#ifndef BUTTON_H
#define BUTTON_H

class Button {
    Engine& engine;
    Graphics& graphics;
    View view;

public:

    Button(Engine& _engine);
    void render();
    void update();
    void setPosition(int _x, int _y);
    std::function<void(void)> onPressCallback;

};

#endif // !BUTTON_H
