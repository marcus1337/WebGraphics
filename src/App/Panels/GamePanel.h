
#include "Panel.h"
#include <Drawables/Button.h>
#include <Drawables/Image.h>

#ifndef GAMEPANEL_H
#define GAMEPANEL_H

class GamePanel : public Panel {

    Image backgroundImage;
    Button backButton;

public:

    GamePanel(Engine& _engine);
    void update() override;
    void render() override;

};

#endif // !GAMEPANEL_H
