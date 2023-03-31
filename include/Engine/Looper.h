#ifndef LOOPER_H
#define LOOPER_H
#include "Engine.h"
#include <functional>

class Looper {

    int FPS = 60;
    int ticksPS = 30;

    bool isRenderUpdate();
    bool isTickUpdate();
    void render();
    void tick();

public:
    Engine engine;
    std::functional<void> onRender;
    std::functional<void> onTick;

    Looper();
    void setDefaultResourceFolders();
    void setFramesPerSecond(int numFrames);
    void setTicksPerSecond(int numTicks);
    void loop();
    void loopStep();
};


#endif // !LOOPER_H
