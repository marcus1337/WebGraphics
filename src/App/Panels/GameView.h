
#include "Panel.h"
#include <Drawables/Button.h>
#include <Drawables/Image.h>

#ifndef GAMEVIEW_H
#define GAMEVIEW_H

class GameView : public Panel {

    Image getCardImage(int cardValue);
    std::string getRankName(int cardRank);
    std::string getSuitName(int cardSuit);
    std::string getCardTextureName(int cardValue);

public:

    GameView(Engine& _engine);
    void update() override;
    void render() override;

};

#endif
