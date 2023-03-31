#ifndef LOOPER_H
#define LOOPER_H
#include "Engine.h"
#include <functional>
#include <chrono>

class Looper {

    int FPS = 60;
    int ticksPS = 30;

    std::chrono::steady_clock::time_point lastRenderTimePoint, lastTickTimePoint;

    bool isRenderUpdate();
    bool isTickUpdate();
    void render();
    void tick();

public:
    Engine engine;
    std::function<void(void)> onRender;
    std::function<void(void)> onTick;

    Looper();
    void setDefaultResourceFolders();
    void setFramesPerSecond(int numFrames);
    void setTicksPerSecond(int numTicks);
    void loop();
    void loopStep();
};


#endif // !LOOPER_H
