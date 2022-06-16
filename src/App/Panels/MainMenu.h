
#include "Engine/Engine.h"
#include <string>
#include <Drawables/Button.h>
#include <Drawables/Drawable.h>
#include <Drawables/Image.h>
#include <Drawables/Rectangle.h>
#include <Drawables/View.h>
#include <Drawables/Text.h>
#include <vector>
#include "Panel.h"

#include "../Network/DemoLobbyNet.h"
#include "../Network/GameNet.h"

#ifndef MAINMENU_H
#define MAINMENU_H

class MainMenu : public Panel {

    GameNet gameNet;
    DemoLobbyNet lobbyNet;

    Image backgroundImage;
    void onSinglePlayer();
    void onHostMultiPlayer();
    void onJoinMultiPlayer();
    void onSettings();
    void onAchievements();
    void onQuit();

    Button singlePlayerButton, joinMultiPlayerButton, hostMultiPlayerButton, settingsButton, achievementsButton, quitButton;

public:
    MainMenu(Engine& _engine);
    void update() override;
    void render() override;

};

#endif // !MAINMENU_H
