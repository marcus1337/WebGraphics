#include "Rect.h"


#ifndef LINE_H
#define LINE_H

class Line : public Rect {

public:
    Line(Engine& _engine, int fromX, int fromY, int toX, int toY);
    void setThickness(int _thickness);

};

#endif // !LINE_H
