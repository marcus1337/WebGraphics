
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
    while (!engine.hasQuit())
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

void App::beforeStep()
{
    gameTicks++;
    MS_PASSED = 0;
    engine.pollEvents();
}

void App::step(){
    beforeStep();
    update();
    engine.draw();
}

void App::update()
{
    //camera.move(engine.getMouse(), mywindow.keyboard);
    /*if (mywindow.mouse.wasLeftReleased) {
        std::cout << "CLICK1!\n";
        framebuffer.postImageUniform->blur += 0.1f;
    }
    if(mywindow.mouse.wasRightReleased){
        std::cout << "CLICK2!\n";
        framebuffer.postImageUniform->blur -= 0.1f;
    }*/

}

void App::resizeWindow(int _width, int _height)
{
    engine.resizeWindow(_width, _height);
}