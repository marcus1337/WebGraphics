#include "Engine/Looper.h"

Looper::Looper() {
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
    if (isRenderUpdate())
        render();
    if (isTickUpdate())
        tick();
}

bool Looper::isRenderUpdate() {
    return false;
}
bool Looper::isTickUpdate() {
    return false;
}

void Looper::render() {
    clearScreen();
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
