
#include "Panel.h"
#include <Drawables/Button.h>
#include <Drawables/Image.h>

#ifndef ACHIEVEMENTS_H
#define ACHIEVEMENTS_H

class AchievementsMenu : public Panel {

    Image backgroundImage;
    Button backButton;

public:

    AchievementsMenu(Engine& _engine);
    void update() override;
    void render() override;

};

#endif // !ACHIEVEMENTS_H
