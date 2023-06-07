
#include "Engine/Engine.h"
#include "Engine/Looper.h"
#include "Drawables/Image.h"
#include "Drawables/Text.h"
#include "Drawables/View.h"
#include "Drawables/Mesh.h"
#include <vector>
#include <string>
#include <iostream>

int main(int argc, char* argv[]) {

    Looper looper;
    auto& engine = Engine::getInstance();
    engine.graphics.mainView.setSize(1920, 1080);
    engine.resources.loadDefaultResourceFiles();
    engine.setIconImage();

    Image image("background1");
    image.setShaderProgram("background");
    image.setSize(1920, 1080);   
  
    Text text;
    text.setText(L"Okay bro");
    text.setFont("Roboto-Regular");
    text.setPosition(0, 0);

    View view(500, 500);
    view.clear();
    view.paint(image);
    view.paint(text);

    looper.onRender = [&]() {
        view.render();
    };

    looper.loop();

    return 0;
}



