#include "Page.h"

Page::Page() : engine(Global::getEngineInstance()) {
    engine.window.setTitle("Neural Net");
    setBackground();
}

void Page::setBackground() {
    background = std::shared_ptr<Image>(new Image(*engine.graphics, engine.ioContainer, "background1"));
    background->setSize(1920, 1080);
}

void Page::loop() {
    while (!engine.window.hasQuit()) {
        processUserInput();

        engine.window.pollEvents();
        engine.graphics->mainView.clear();
        background->render();
        renderNetwork();

        engine.graphics->mainView.display();
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}


void Page::renderNetwork() {
    auto view = std::shared_ptr<View>(new View(*engine.graphics, engine.ioContainer, 100, 100));
    view->setPosition(100, 100);
    view->setShaderProgram("node");
    view->paintMinusAlpha(*background);
    view->render();
}

void Page::processUserInput() {
    if (engine.window.keyboard.isUpClick['A']) {
        Global::reload();
    }
}