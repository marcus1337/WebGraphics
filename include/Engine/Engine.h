
#ifndef ENGINE_H
#define ENGINE_H
#include "Graphics/Graphics.h"
#include "IO/Files/IOContainer.h"
#include <vector>
#include "Resources.h"

class Engine {
    Engine();
    ~Engine() = default;
public:
    static Engine& getInstance();
    Canvas window;
    Graphics graphics;
    Resources resources;
    void setIconImage();
    void clearScreen();

};

#endif // !ENGINE_H
