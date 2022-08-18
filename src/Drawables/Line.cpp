
#include "Line.h"
#include <math.h> 
#include <numbers>

Line::Line(Engine& _engine, int fromX, int fromY, int toX, int toY) : Rect(_engine) {
    int length = (int) glm::length(glm::vec2(fromX, fromY) - glm::vec2(toX, toY));
    int thickness = 4;
    setSize(length, thickness);

    double deltaX = toX - fromX;
    double deltaY = toY - fromY;
    double rotationRadians = atan2(deltaY, deltaX);
    double pi = std::numbers::pi_v<double>;
    double degrees = rotationRadians * (180.0 / pi);
    setRotation(degrees);

    setPosition(-length/2+deltaX/2+fromX, -thickness/2+deltaY/2+fromY);

}

