
#include "Line.h"

Line::Line(Engine& _engine, int fromX, int fromY, int toX, int toY) : Rect(_engine) {
    setThickness(4);
}

void Line::setThickness(int _thickness) {
    setSize(getWidth(), _thickness);
}

