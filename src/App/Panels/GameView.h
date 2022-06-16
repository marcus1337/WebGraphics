
#include "Panel.h"
#include <Drawables/Button.h>
#include <Drawables/Image.h>

#ifndef GAMEVIEW_H
#define GAMEVIEW_H

class GameView : public Panel {

public:

    GameView(Engine& _engine);
    void update() override;
    void render() override;

};

#endif
