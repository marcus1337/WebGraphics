
#ifndef ENGINE_H
#define ENGINE_H
#include "Graphics/Graphics.h"
#include "IO/Files/IOContainer.h"
#include <vector>
#include "Resources.h"

class Engine {
public:
    Canvas window;
    Graphics graphics;
    Resources resources;
    void setIconImage();
    Engine();
    ~Engine();

};

#endif // !ENGINE_H
