#include "Panel.h"
#include <Drawables/Button.h>
#include <Drawables/Image.h>

#ifndef LOBBYMENU_H
#define LOBBYMENU_H

class LobbyMenu : public Panel {

    Image backgroundImage;
    Button backButton;

public:

    LobbyMenu(Engine& _engine);
    void update() override;
    void render() override;

};


#endif // !LOBBYMENU_H
