#include "Rect.h"


#ifndef LINE_H
#define LINE_H

class Line : public Rect {
    int lineWidth = 4;
    int fromX, fromY, toX, toY;

public:
    Line(Engine& _engine, int fromX, int fromY, int toX, int toY);

    void adjust();
    void setLineWidth(int _lineWidth);

};

#endif // !LINE_H
