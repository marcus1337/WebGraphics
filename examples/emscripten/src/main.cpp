
#ifdef EMSCRIPTEN
    #include <emscripten/emscripten.h>
    #include <emscripten/html5.h>
    #include <emscripten/fetch.h>
    #include <emscripten/bind.h>
    //#include <emscripten/websocket.h>
#endif

#include "Engine/Engine.h"
#include "Engine/Looper.h"
#include "Drawables/Image.h"
#include "Drawables/Text.h"
#include <vector>
#include <string>
#include <iostream>

Looper looper;

void loopStep()
{
    looper.loopStep();
}

void resizeWindow(int width, int height){
    auto &engine = Engine::getInstance();
    engine.window.resizeWindow(width, height);
}

#ifdef EMSCRIPTEN
    EMSCRIPTEN_BINDINGS(resize_module) {
        emscripten::function("resizeWindow", &resizeWindow);
    }
#endif

int main(int argc, char *argv[])
{

    auto &engine = Engine::getInstance();
    engine.resources.loadDefaultResourceFiles();
    engine.setIconImage();

    Image image("background1");
    image.setShaderProgram("background");
    image.setSize(1920, 1080);
    Text text;
    text.setText("Okay bro");
    text.setPosition(100, 100);

    looper.onRender = [&]()
    {
        image.render();
        text.render();
    };

#ifdef EMSCRIPTEN
    emscripten_set_main_loop(loopStep, 0, 1);
#else
    std::cout << "Should compile this as emscripten instead...\n";
    looper.loop();
#endif

    return 0;
}
