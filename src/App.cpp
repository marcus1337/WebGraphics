
#include "App.h"

#include "glm/glm.hpp"

bool App::isGameUpdate()
{
    using namespace std::chrono;
    steady_clock::time_point timeGameUpdate = steady_clock::now();
    MS_PASSED += duration_cast<microseconds>(timeGameUpdate - timeSinceGameUpdate).count();
    timeSinceGameUpdate = timeGameUpdate;
    return MS_PASSED >= MS_FRAME;
}


void App::run()
{
    while (!engine.window.hasQuit())
    {
        if (isGameUpdate()){
            step();
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

App::App() 
{
    MS_PASSED = 0;
    MS_FRAME = 16600;
}

App::~App()
{

}

void App::step(){
    gameTicks++;
    MS_PASSED = 0;
    engine.window.pollEvents();
    update();

    engine.graphics.clearViews();

    Image image;
    Text text, text2;
    text2.text = "another text";
    text2.color = glm::vec4(1.0f, 1.0f, 0.0f, 1.0f);
    text2.rotation = 45.0f;
    text2.y = 400;
    text2.x = 100;
    image.x = 300;
    image.y = 300;
    engine.graphics.drawImage(image);
    engine.graphics.drawText(text);
    engine.graphics.drawText(text2);

    engine.graphics.display();
}

void App::update()
{
    if (engine.window.mouse.isLeftReleased) {
        std::cout << "CLICK1!\n";
    }
    if(engine.window.mouse.isRightReleased){
        std::cout << "CLICK2!\n";
    }

}

void App::resizeWindow(int _width, int _height)
{
    engine.window.resizeWindow(_width, _height);
}