
#include "Engine/Engine.h"
#include "Engine/Looper.h"
#include "Drawables/Image.h"
#include "Drawables/Text.h"
#include "Drawables/View.h"
#include "Drawables/Mesh.h"
#include "Drawables/PoseMesh.h"
#include <vector>
#include <string>
#include <iostream>

int main(int argc, char* argv[]) {

    Looper looper;
    auto& engine = Engine::getInstance();
    //engine.graphics.mainView.setSize(1000, 1000);
    engine.graphics.mainView.setSize(1280, 720);
    //engine.graphics.mainView.setSize(1920, 1080);
    engine.resources.loadDefaultResourceFiles();
    engine.setIconImage();

    Image image("background1");
    image.setShaderProgram("background");
    image.setSize(1920, 1080);   
  
    Text text;
    text.setText(L"Okay bro こんにちは世界 北島 美奈");
    text.setFont("Hosohuwafont");
    text.setPosition(100, 100);

    View view(200, 200);
    view.clear();
    view.setPosition(-100, -100);
    view.paint(image);
    view.paint(text);

    auto camera = view.getCamera();
    camera->setProjectionType(false);
    camera->setPosition({ 0.f, 0, -50.0f });
    camera->setYaw(90.0f);

    camera->setOrbitTarget({ 0, 0, 0 });
    camera->setOrbitDistance(700.0f);

    Mesh stallMesh("stall", "stall");
    stallMesh.setSize({ 20, 20, 20 });
    stallMesh.setCamera(camera);
    stallMesh.setPosition({ -10.f, -10.f, -10.f });


    PoseMesh poseMesh("model", "stall", "model");
    poseMesh.setSize({ 20,20,20 });
    poseMesh.setCamera(camera);
    poseMesh.setPosition({ -10.f, -10.f, -10.f });

    float r = 1.0f;
    looper.onRender = [&]() {

        auto& mouse = engine.window.mouse;

        float scroll = mouse.getScrollDelta();

        float zoom = 0.f;
        bool zoomIn = mouse.isPressed(MouseButton::LEFT);
        bool zoomOut = mouse.isPressed(MouseButton::RIGHT);
        if (zoomIn)
            zoom = 10.0f;
        if (zoomOut)
            zoom = -10.0f;
        float pitchDelta = 0.f;
        bool pitchUp = engine.window.keyboard.isPressed('D');
        bool pitchDown = engine.window.keyboard.isPressed('C');
        if (pitchUp)
            pitchDelta = 1.f;
        if (pitchDown)
            pitchDelta = -1.f;

        camera->orbit(scroll * 10.0f, pitchDelta*3.0f, zoom);

        view.clear();
        view.paint(image);
        view.paint(text);
        view.setRotation({r,r,r});
        r = r + 1.0f;
        //view.render();

        stallMesh.render();
        //poseMesh.render();
    };

    looper.loop();

    return 0;
}



