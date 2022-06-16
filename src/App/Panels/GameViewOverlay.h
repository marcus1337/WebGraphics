
#include "Panel.h"
#include <Drawables/Button.h>
#include <Drawables/Image.h>
#include "GameView.h"

#ifndef GAMEPANEL_H
#define GAMEPANEL_H

class GameViewOverlay : public Panel {

    Image backgroundImage;
    Button backButton;
    GameView gameView;

public:

    GameViewOverlay(Engine& _engine);
    void update() override;
    void render() override;

};

#endif // !GAMEPANEL_H
