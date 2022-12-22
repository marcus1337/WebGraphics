
#include "App.h"
#include <iostream>

#include <filesystem>

App::App() {
    engine = new Engine(getResourceFolderPaths());
    panelHandler = new PanelHandler(*engine);
}

App::~App() {
    delete engine;
    delete panelHandler;
}

std::vector<std::string> App::getResourceFolderPaths() {
    std::vector<std::string> paths;
    std::string resourceFolderPath;
#ifndef EMSCRIPTEN
    resourceFolderPath = std::filesystem::current_path().string() + "//res//";
#else
    resourceFolderPath = "./res/";
#endif 
    paths.push_back(resourceFolderPath + "textures//");
    paths.push_back(resourceFolderPath + "textures//icons//");
    paths.push_back(resourceFolderPath + "fonts//");
    paths.push_back(resourceFolderPath + "audio//");
    return paths;
}


void App::loop()
{
    while (!engine->window.hasQuit())
    {
        loopStep();
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

void App::resizeWindow(int _width, int _height)
{
    engine->window.resizeWindow(_width, _height);
}

void App::loopStep() {
    if (updateTimer.isLogicUpdate()) {
        panelHandler->update();
        engine->window.pollEvents();
    }
#ifndef EMSCRIPTEN 
    if (updateTimer.isRenderUpdate())
#endif
        render();
}

void App::render() {
    engine->graphics->mainView.clear();
    panelHandler->render();
    engine->graphics->mainView.display();
}
