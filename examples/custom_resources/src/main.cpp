
#include "Engine/Engine.h"
#include "Drawables/Image.h"
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
    paths.push_back(resourceFolderPath + "audio//");
    return paths;
}

int main(int argc, char* argv[]) {

    Engine* engine = new Engine(getResourceFolderPaths());

    while (!engine->window.hasQuit()) {
        engine->window.pollEvents();
        engine->graphics->mainView.clear();
        Image image(*engine->graphics, engine->ioContainer, "background1");
        image.setSize(1920, 1080);
        image.render();
        engine->graphics->mainView.display();
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    delete engine;

    return 0;
}