
#include "Engine/Engine.h"
#include "Engine/Looper.h"
#include "Drawables/Image.h"
#include "Drawables/Text.h"
#include "Drawables/View.h"
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
    image.setCamera(Camera(1920, 1080));
    Text text;
    text.setText(L"Okay bro こんにちは世界 北島 美奈");
    text.setFont("Hosohuwafont");
    text.setPosition(100, 100);
    text.setCamera(Camera(1920, 1080));

    View view(500, 500);
    view.clear();
    view.setPosition(300, 0);
    view.paint(image);
    view.paint(text);

    looper.onRender = [&]() {
        image.render();
        text.render();
        view.render();
    };

    looper.loop();

    return 0;
}



