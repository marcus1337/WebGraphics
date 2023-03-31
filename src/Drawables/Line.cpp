
#include "Drawables/Line.h"
#include <math.h> 
#include <numbers>

Line::Line(int _fromX, int _fromY, int _toX, int _toY) : fromX(_fromX), fromY(_fromY), toX(_toX), toY(_toY) {
    adjust();
}

void Line::adjust() {
    int length = (int)glm::length(glm::vec2(fromX, fromY) - glm::vec2(toX, toY));
    setSize(length, lineWidth);

    double deltaX = toX - fromX;
    double deltaY = toY - fromY;
    double rotationRadians = atan2(deltaY, deltaX);
    double pi = std::numbers::pi_v<double>;
    double degrees = rotationRadians * (180.0 / pi);
    setRotation(degrees);

    setPosition(-length / 2 + deltaX / 2 + fromX, -lineWidth / 2 + deltaY / 2 + fromY);
}

void Line::setLineWidth(int _lineWidth) {
    lineWidth = _lineWidth;
    adjust();
}


