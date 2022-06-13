
#include "Engine/Engine.h"
#include <string>
#include <Drawables/Button.h>
#include <Drawables/Drawable.h>
#include <Drawables/Image.h>
#include <Drawables/Rectangle.h>
#include <Drawables/View.h>
#include <Drawables/Text.h>
#include <vector>


#ifndef MAINMENU_H
#define MAINMENU_H

class MainMenu {

    Engine& engine;

    Image backgroundImage;
    void onStartSinglePlayer();
    void onStartMultiPlayer();
    void onStartSettings();
    void onStartAchievements();
    void onQuit();

    Button singlePlayerButton, multiPlayerButton, settingsButton, achievementsButton, quitButton;
    std::vector<Button*> buttons;

public:
    MainMenu(Engine& _engine);
    void update();
    void render();

};

#endif // !MAINMENU_H
