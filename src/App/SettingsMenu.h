#include "Panel.h"
#include <Drawables/Button.h>
#include <Drawables/Image.h>


#ifndef SETTINGSMENU_H
#define SETTINGSMENU_H

class SettingsMenu : public Panel {

    Image backgroundImage;
    Button backButton;

public:

    SettingsMenu(Engine& _engine);
    void update() override;
    void render() override;
};

#endif
