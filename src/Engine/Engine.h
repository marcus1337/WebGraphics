
#include "Graphics.h"

#ifndef ENGINE_H
#define ENGINE_H

class Engine {
public:
    Canvas window;
    Graphics graphics;
private:
    void setGLSettings();

public:
    Engine();
    ~Engine();
};

#endif // !ENGINE_H
