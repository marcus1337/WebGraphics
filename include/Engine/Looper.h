#ifndef LOOPER_H
#define LOOPER_H
#include "Engine.h"
#include <functional>
#include <chrono>

class Looper {

    Engine& engine;
    int FPS = 60;
    int ticksPS = 30;
    std::chrono::steady_clock::time_point lastRenderTimePoint, lastTickTimePoint, lastEventPollTimePoint;

    bool isTimePassed(std::chrono::steady_clock::time_point& tp, int updatesPS);
    bool isRenderUpdate();
    bool isTickUpdate();
    bool isEventPollUpdate();
    void render();
    void tick();
    void eventPoll();

public:
    std::function<void(void)> onRender;
    std::function<void(void)> onTick;
    std::function<void(void)> onEventPoll;

    Looper();
    void setFramesPerSecond(int _FPS);
    void setTicksPerSecond(int _ticksPS);
    void loop();
    void loopStep();
};


#endif // !LOOPER_H
