#include "Engine/Looper.h"

Looper::Looper() {
    lastRenderTimePoint = lastTickTimePoint = std::chrono::steady_clock::now();
    engine.window.setResizeCallbackFunction([&]() {
        render();
        });
}

void Looper::setDefaultResourceFolders() {

}

void Looper::setFramesPerSecond(int numFrames) {

}

void Looper::setTicksPerSecond(int numTicks) {

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

bool Looper::isRenderUpdate() {
    return false;
}
bool Looper::isTickUpdate() {
    return false;
}

void Looper::render() {
    engine.clearScreen();
    engine.graphics.mainView.clear();
   // if(onRender)
   //     onRender();
    engine.graphics.mainView.display();
}

void Looper::tick() {
    engine.window.pollEvents();
    //if(onTick)
    //    onTick();
}
