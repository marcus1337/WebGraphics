
#include "App.h"
#include "glm/glm.hpp"
#include "Drawables/Rectangle.h"

App::App() 
{
}

App::~App()
{
}

void App::run()
{
    while (!engine.window.hasQuit())
    {
        if (updateTimer.isRenderUpdate())
            update();
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

void App::resizeWindow(int _width, int _height)
{
    engine.window.resizeWindow(_width, _height);
}

void App::update(){
    if (updateTimer.isLogicUpdate()) {
        updateLogic();
        engine.window.pollEvents();
    }
    render();
}

void App::updateLogic() {
    int x = engine.window.mouse.x;
    int y = engine.window.mouse.y;
    std::pair<int, int> pos = engine.graphics.getPixelPosition(x, y);
    if (engine.window.mouse.isLeftReleased) {
        std::cout << "CLICK DOWN " << "x: " << pos.first << " y: " << pos.second << "\n";
    }
    if (engine.window.mouse.isRightReleased) {
        std::cout << "CLICK UP " << "x: " << pos.first << " y: " << pos.second << "\n";
    }
}

void App::render() {
    engine.graphics.clearViews();
    renderViews();
    engine.graphics.display();
}

void App::renderViews(){
    Image image;
    Text text, text2;
    Rectangle rectangle;
    rectangle.x = 150;
    rectangle.y = 500;
    text2.text = "another text";
    text2.color = glm::vec4(1.0f, 1.0f, 0.0f, 1.0f);
    text2.rotation = 45.0f;
    text2.y = 400;
    text2.x = 100;
    image.x = 300;
    image.y = 300;
    engine.graphics.drawImage(image);
    engine.graphics.drawRectangle(rectangle);
    engine.graphics.drawText(text);
    engine.graphics.drawText(text2);
}