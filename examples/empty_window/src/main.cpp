#include "Engine/Engine.h"
#include <vector>
#include <string>
#include <filesystem>
#include <iostream>
#include "Engine/Engine.h"

int main(int argc, char* argv[]) {

    auto& engine = Engine::getInstance();
    while(!engine.window.hasQuit()){
        engine.window.pollEvents();
        for(char c : "ABCDEFGHIJKLMNOPQRSTUVWZYZ"){
            if(engine.window.keyboard.isDownClick[c]){
                std::string str = "Press: ";
                str += c;
                std::cout << str << "\n";
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    return 0;
}