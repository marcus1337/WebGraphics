
#ifdef EMSCRIPTEN
    #include <emscripten.h>
    #include <emscripten/html5.h>
    #include <emscripten/bind.h>
#endif

#include "Engine/Engine.h"
#include "Drawables/Image.h"
#include <vector>
#include <string>
#include <filesystem>
#include <iostream>

Engine* engine;

void loopStep(){
    engine->window.pollEvents();
    engine->graphics->mainView.clear();
    Image image(*engine->graphics, engine->ioContainer, "background1");
    image.setSize(1920, 1080);
    image.render();
    engine->graphics->mainView.display();
}

void loop(){
    while (!engine->window.hasQuit()) {
        loopStep();
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

void resizeWindow(int width, int height){
    engine->window.resizeWindow(width, height);
}

#ifdef EMSCRIPTEN
    EMSCRIPTEN_BINDINGS(my_module) {
        emscripten::function("resizeWindow", &resizeWindow);
    }
#endif

std::vector<std::string> getResourceFolderPaths() {
    std::vector<std::string> paths;
    #ifdef EMSCRIPTEN
        std::string resourceFolderPath = "./res/";
    #else
        std::string resourceFolderPath = std::filesystem::current_path().string() + "//res//";
    #endif
    paths.push_back(resourceFolderPath + "textures//");
    paths.push_back(resourceFolderPath + "textures//icons//");
    paths.push_back(resourceFolderPath + "fonts//");
    paths.push_back(resourceFolderPath + "audio//");
    return paths;
}

int main(int argc, char* argv[]) {

    engine = new Engine(getResourceFolderPaths());

#ifdef EMSCRIPTEN
    emscripten_set_main_loop(loopStep, 0, 1);
#else
    loop();
#endif

    return 0;
}