
#include "Engine/Engine.h"
#include "Engine/Looper.h"
#include "Drawables/Image.h"
#include "Drawables/Text.h"
#include <vector>
#include <string>
#include <filesystem>
#include <iostream>

std::vector<std::string> getResourceFolderPaths() {
    std::vector<std::string> paths;
    std::string resourceFolderPath = std::filesystem::current_path().string() + "//res//";
    paths.push_back(resourceFolderPath + "textures//");
    paths.push_back(resourceFolderPath + "textures//icons//");
    paths.push_back(resourceFolderPath + "fonts//");
    return paths;
}

int main(int argc, char* argv[]) {

    Looper looper;
    looper.engine.resources.loadResourceFiles(getResourceFolderPaths());
    looper.engine.setIconImage();

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

void testLoop() {
    Engine engine;
    while (!engine.window.hasQuit()) {
        engine.window.pollEvents();
        engine.graphics.mainView.clear();
        Image image("background1");
        image.setSize(1920, 1080);
        Text text;
        text.setText("Okay bro");
        text.setPosition(100, 100);

        image.render();
        text.render();
        engine.graphics.mainView.display();
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

