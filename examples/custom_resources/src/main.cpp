
#include "Engine/Engine.h"
#include "Engine/Looper.h"
#include "Drawables/Image.h"
#include "Drawables/Text.h"
#include <vector>
#include <string>
#include <iostream>

int main(int argc, char* argv[]) {

    Looper looper;
    auto& engine = Engine::getInstance();
    engine.resources.loadDefaultResourceFiles();
    engine.setIconImage();

    Image image("background1");
    image.setSize(1920, 1080);
    Text text;
    text.setText("Okay bro");
    text.setPosition(100, 100);

    looper.onRender = [&]() {
        image.render();
        text.render();
    };

    looper.loop();

    return 0;
}



