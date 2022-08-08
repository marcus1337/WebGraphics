
#include "Engine/Engine.h"
#include <string>
#include <Drawables/Drawable.h>
#include <Drawables/Image.h>
#include <Drawables/Rect.h>
#include <Drawables/Text.h>
#include <vector>
#include "App/Panels/Panel.h"

#ifndef MAINMENU_H
#define MAINMENU_H

class MainMenu : public Panel {
    Image backgroundImage;
    void onQuit();
    virtual void onEnter() override;
public:
    MainMenu(Engine& _engine);
    void update() override;
    void render() override;

};

#endif // !MAINMENU_H
