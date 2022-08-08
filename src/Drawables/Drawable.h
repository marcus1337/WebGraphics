#include <functional>
#include "IO/Controller/Mouse.h"
#include <Engine/Graphics.h>
#include <Engine/Engine.h>

#ifndef DRAWABLE_H
#define DRAWABLE_H

class Drawable {

protected:
    Engine& engine;
    Graphics& graphics;
    Mouse& mouse;

public:
    Drawable(Engine& _engine);

};

#endif