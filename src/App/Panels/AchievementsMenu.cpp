#include "AchievementsMenu.h"


AchievementsMenu::AchievementsMenu(Engine& _engine) : Panel(_engine) {
    backgroundImage.width = 1920;
    backgroundImage.height = 1080;
    backgroundImage.texture = "background2.png";

    backButton.onPressCallback = std::bind(&AchievementsMenu::onExit, this);
    backButton.text.text = "Back";
    backButton.setSize(200, 100);
    backButton.setPosition(50, 50);
    buttons.push_back(&backButton);
}

void AchievementsMenu::update() {
    int x = getRelativeMouseXPosition();
    int y = getRelativeMouseYPosition();
    updateButtons(x, y);
}

void AchievementsMenu::render() {
    engine.graphics.drawImage(backgroundImage);
    renderButtons();
}

