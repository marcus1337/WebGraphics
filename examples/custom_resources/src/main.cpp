
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

    Camera camera(1920, 1080);
    float r = 1.0f;
    looper.onRender = [&]() {
        camera.setProjectionType(false);
        camera.setPosition({ 1920/2, 1080/2, 1500 });
        camera.setYaw(-90.0f);
        //camera.setPitch(5.0f);
        image.setCamera(camera);
        image.setRotation(r);
        r = r + 1.0f;


        view.clear();
        view.setPosition(300, 0);
        view.paint(image);
        view.paint(text);
        view.render();

    };

    looper.loop();

    return 0;
}



