
#ifndef ENGINE_H
#define ENGINE_H
#include "Graphics/Graphics.h"
#include "IO/Files/IOContainer.h"
#include <vector>
#include <memory>
#include "Resources.h"

class Engine {

public:
    Canvas window;
    std::shared_ptr<Graphics> graphics;
    Resources resources;

    Engine();
    ~Engine();
    void setIconImage();

};

#endif // !ENGINE_H
