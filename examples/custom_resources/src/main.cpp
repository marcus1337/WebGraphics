
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
    image.setShaderProgram("background");
    image.setSize(1920, 1080);
    Text text;
    text.setText(L"Okay bro こんにちは世界 北島 美奈");
    text.setFont("Hosohuwafont");
    text.setPosition(100, 100);

    bool tmp = true;

    looper.onRender = [&]() {
        if (tmp) {
            text.setPixelHeight(30);
        }
        else {
            text.setPixelHeight(60);
        }
        tmp = !tmp;
        image.render();
        text.render();
    };

    looper.loop();

    return 0;
}



