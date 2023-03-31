
#include <vector>
#include <string>
#include <filesystem>
#include <iostream>
#include "Engine/Engine.h"

int main(int argc, char* argv[]) {

    std::vector<std::string> paths;
    Engine* engine = new Engine(paths);

    while (!engine->window.hasQuit()) {
        engine->window.pollEvents();
        engine->graphics->mainView.clear();
        engine->graphics->mainView.display();
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    delete engine;

    return 0;
}