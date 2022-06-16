#include "GameView.h"

GameView::GameView(Engine& _engine) : Panel(_engine) {

}

void GameView::update() {
    int x = getRelativeMouseXPosition();
    int y = getRelativeMouseYPosition();
    updateButtons(x, y);
}

void GameView::render() {
    renderButtons();
}

std::string GameView::getRankName(int cardRank) {
    if (cardRank <= 8)
        return std::to_string(cardRank + 2);
    if (cardRank == 9)
        return "jack";
    if (cardRank == 10)
        return "queen";
    if (cardRank == 11)
        return "king";
    return "ace"; //12
}

std::string GameView::getSuitName(int cardSuit) {
    if (cardSuit == 0)
        return "spades";
    if (cardSuit == 1)
        return "hearts";
    if (cardSuit == 2)
        return "diamonds";
    return "clubs";
}

Image GameView::getCardImage(int cardValue) {
    Image image;
    image.texture = getCardTextureName(cardValue);
    return image;
}

std::string GameView::getCardTextureName(int cardValue) {
    int rank = cardValue % 13;
    int suit = cardValue / 4;
    bool isBlackJoker = cardValue == 52;
    bool isRedJoker = cardValue == 53;
    std::string imageFolder = "deck1//";
    std::string imageName = "";

    if (isBlackJoker)
        imageName = "black_joker";
    else if (isRedJoker)
        imageName = "red_joker";
    else
        imageName = getRankName(rank) + "_of_" + getSuitName(suit);
    return imageFolder + imageName;
}