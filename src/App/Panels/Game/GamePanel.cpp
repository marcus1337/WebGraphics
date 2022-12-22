#include "GamePanel.h"
#include "Drawables/Rect.h"

void GamePanel::onEnter() {
    std::cout << "onEnter() GamePanel" << std::endl;
}

GamePanel::GamePanel(Engine& _engine, PanelContext& _panelContext) : Panel(_engine, "game", _panelContext), boardButtons{} {
    setBoardButtons();
    makeResetButton();
    makeBackgroundImage();
}

void GamePanel::makeResetButton() {
    resetButton = std::make_unique<Button>(engine, 300, 100);
    resetButton->setImage("button1");
    resetButton->setPosition(1250, 700);
    Text resetText(*engine.graphics, engine.ioContainer);
    resetText.setText("RESET");
    resetText.setColor({ 0.9,0.9,0.9 });
    resetText.setPixelHeight(50);
    resetButton->setText(resetText);
    resetButton->onPressCallback = [&]() {
        ticTacToe.reset();
        for (auto& boardButtonPtr : boardButtons)
            boardButtonPtr->onReset();
    };
}

void GamePanel::makeBackgroundImage() {
    backgroundImage = std::make_unique<Image>(*engine.graphics, engine.ioContainer, "background1");
    backgroundImage->setSize(1920, 1080);
}

void GamePanel::setBoardButtons() {
    int buttonIndex = 0;
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            boardButtons[buttonIndex++] = std::make_unique<BoardButton>(engine, row, col, ticTacToe);
        }
    }
}

void GamePanel::updateGame() {
    if (isPlayerTurn()) {
        for (auto& buttonPtr : boardButtons) {
            buttonPtr->update();
        }
    }
    else {
        handleAIMove();
    }
}

void GamePanel::update() {
    if(!ticTacToe.isGameOver())
        updateGame();
    resetButton->update();
}

bool GamePanel::isPlayerTurn() {
    return ticTacToe.getTurnMark() == Tile::CIRCLE;
}

void GamePanel::handleAIMove() {
    aiDelayCounter++;
    if (aiDelayCounter > 20) {
        ai.placeMark(ticTacToe);
        aiDelayCounter = 0;
        for (auto& buttonPtr : boardButtons) {
            buttonPtr->update();
        }
    }
}

void GamePanel::render() {
    backgroundImage->render();
    for (auto& buttonPtr : boardButtons) {
        buttonPtr->render();
    }
    resetButton->render();
    if (ticTacToe.isGameOver())
        renderGameOverText();
}

void GamePanel::renderGameOverText() {
    Text gameOverText(*engine.graphics, engine.ioContainer);
    if (ticTacToe.isDraw())
        gameOverText.setText("Draw!");
    if (ticTacToe.getWinner() == Tile::CIRCLE)
        gameOverText.setText("Circle wins!");
    if (ticTacToe.getWinner() == Tile::CROSS)
        gameOverText.setText("Cross wins!");
    gameOverText.setPosition(550, 150);
    gameOverText.setColor({ 1.0,1.0,1.0 });
    gameOverText.render();
}

