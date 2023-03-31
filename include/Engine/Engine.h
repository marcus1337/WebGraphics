
#ifndef ENGINE_H
#define ENGINE_H
#include "Graphics/Graphics.h"
#include "IO/Files/IOContainer.h"
#include <vector>
#include <memory>
#include "Resources.h"

class Engine {
    Engine();
    ~Engine();
public:
    Canvas window;
    std::shared_ptr<Graphics> graphics;
    Resources resources;
    void setIconImage();

    static Engine& getInstance();

};

#endif // !ENGINE_H
