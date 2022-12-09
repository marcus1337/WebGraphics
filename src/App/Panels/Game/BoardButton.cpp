#include "BoardButton.h"
#include "Drawables/Rect.h"
#include "Drawables/Circle.h"
#include "Drawables/Line.h"
#include <functional>

BoardButton::BoardButton(Engine& _engine, int _row, int _col, TicTacToe& _ticTacToe) : engine(_engine), row(_row), col(_col), ticTacToe(_ticTacToe) {
    makeButton();
    setPosition();
    setDefaultVisuals();
}

void BoardButton::setPosition() {
    int boardXPosition = 400;
    int boardYPosition = 700;
    int spacing = 4;
    int xPosition = boardXPosition + col * button->getWidth() + spacing * col;
    int yPosition = boardYPosition - row * button->getHeight() - spacing * row;
    button->setPosition(xPosition, yPosition);
}

void BoardButton::setDefaultVisuals() {
    button->clearView();
    int width = button->getWidth();
    int height = button->getHeight();
    Rect innerRect(engine);
    innerRect.setSize(width, height);
    innerRect.setRadius(0.1f);
    innerRect.setColor({ 0.5,0.5,0.5 });
    Rect outerRect(engine);
    outerRect.setSize(width, height);
    outerRect.setRadius(0.1f);
    outerRect.setThickness(0.05f);
    outerRect.setColor({ 0.1,0.1,0.1 });
    button->paint(innerRect);
    button->paint(outerRect);
}

void BoardButton::setCircleVisuals() {
    Circle circle(engine);
    int width = button->getWidth();
    int height = button->getHeight();
    circle.setSize(width, height);
    circle.setColor({ 1.0,0.0,0.0 });
    circle.setThickness(0.3f);
    button->paint(circle);
}

void BoardButton::setCrossVisuals() {
    int width = button->getWidth();
    int height = button->getHeight();

    Line line1(engine, 0, 0, width, height);
    line1.setColor({ 0,0,0 });
    line1.setLineWidth(14);
    Line line2(engine, 0, height, width, 0);
    line2.setColor({ 0,0,0 });
    line2.setLineWidth(14);
    button->paint(line1);
    button->paint(line2);
}

void BoardButton::makeButton() {
    const int buttonWidth = 200;
    const int buttonHeight = 200;
    button = std::make_unique<Button>(engine, buttonWidth, buttonHeight);
    button->onPressCallback = std::bind(&BoardButton::onPress, this);
}

void BoardButton::onPress() {
    std::cout << "Tile button (" << row << "," << col << ")\n";
    button->setActive(false);
    ticTacToe.setTile(row, col);
    Tile tile = ticTacToe.getTile(row, col);
    if (tile == Tile::CROSS)
        setCrossVisuals();
    if (tile == Tile::CIRCLE)
        setCircleVisuals();
}

void BoardButton::update() {
    if (ticTacToe.isGameOver())
        return;
    button->update();
}

void BoardButton::render() {
    button->render();
}

void BoardButton::onReset() {
    button->setActive(true);
    setDefaultVisuals();
}

