#include "Engine/Looper.h"

Looper::Looper() {
    lastRenderTimePoint = lastTickTimePoint = std::chrono::steady_clock::now();
    engine.window.setResizeCallbackFunction([&]() {
        render();
        });
}

void Looper::setDefaultResourceFolders() {

}

void Looper::setFramesPerSecond(int _FPS) {
    FPS = _FPS;
}

void Looper::setTicksPerSecond(int _ticksPS) {
    ticksPS = _ticksPS;
}

void Looper::loop() {
    while (!engine.window.hasQuit()) {
        loopStep();
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }
}

void Looper::loopStep() {
    if (isRenderUpdate()) {
        lastRenderTimePoint = std::chrono::steady_clock::now();
        render();
    }
    if (isTickUpdate()) {
        lastTickTimePoint = std::chrono::steady_clock::now();
        tick();
    }
}

bool Looper::isTimePassed(std::chrono::steady_clock::time_point& timePoint, int updatesPS) {
    if (updatesPS <= 0)
        return false;
    using namespace std::chrono;
    double passedMS = (double)duration_cast<milliseconds>(steady_clock::now() - timePoint).count();
    double updateMS = 1000.0 / updatesPS;
    return passedMS >= updateMS;
}

bool Looper::isRenderUpdate() {
    return isTimePassed(lastRenderTimePoint, FPS);
}

bool Looper::isTickUpdate() {
    return isTimePassed(lastTickTimePoint, ticksPS);
}

void Looper::render() {
    engine.clearScreen();
    engine.graphics.mainView.clear();
    if(onRender)
        onRender();
    engine.graphics.mainView.display();
}

void Looper::tick() {
    engine.window.pollEvents();
    if(onTick)
        onTick();
}
