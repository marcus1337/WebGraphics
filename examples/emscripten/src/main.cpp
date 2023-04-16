
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
#include "Drawables/View.h"
#include "Drawables/Mesh.h"
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

    std::cout << "Emscripten test...\n";

    auto &engine = Engine::getInstance();
    engine.resources.loadDefaultResourceFiles();
    engine.setIconImage();

    Image image("background1");
    image.setShaderProgram("background");
    image.setSize(1920, 1080);
    Text text;
    text.setText(L"Okay bro こんにちは世界 北島 美奈");
    text.setPosition(100, 100);

    Mesh stallMesh("stall", "stall");
    auto camera = stallMesh.getCamera();
    camera->setProjectionType(false);
    camera->setPosition({ 0.f, 0, -50.0f });
    camera->setYaw(90.0f);
    camera->setOrbitTarget({ 0, 0, 0 });
    camera->setOrbitDistance(700.0f);

    stallMesh.setSize({ 20, 20, 20 });
    stallMesh.setCamera(camera);
    stallMesh.setPosition({ -10.f, -10.f, -10.f });

    looper.onRender = [&]()
    {
        //image.render();
        //text.render();
        stallMesh.render();
    };

#ifdef EMSCRIPTEN
    emscripten_set_main_loop(loopStep, 0, 1);
#else
    std::cout << "Should compile this as emscripten instead...\n";
    looper.loop();
#endif

    return 0;
}
