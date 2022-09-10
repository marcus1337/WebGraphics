#include "Graphics.h"
#include "Audio/Audio.h"

#ifndef ENGINE_H
#define ENGINE_H

class Engine {
public:
    Canvas window;
    Graphics graphics;
    Audio audio;

    Engine();
    ~Engine();
};

#endif // !ENGINE_H
