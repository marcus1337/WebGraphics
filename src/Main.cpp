

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <iostream>
#include <string>

#ifdef EMSCRIPTEN
    #include <emscripten.h>
    #include <emscripten/html5.h>
    #include <emscripten/bind.h>
#endif

#include "App.h"

#ifdef EMSCRIPTEN
    App app;

    void oneLoop(){
        app.gameStep();
    }

    void resizeWindow(int width, int height){
        app.resizeWindow(width, height);
    }
    EMSCRIPTEN_BINDINGS(my_module) {
        emscripten::function("resizeWindow", &resizeWindow);
    }
#endif

int main(int argc, char *argv[]){

    #ifdef EMSCRIPTEN
        emscripten_set_main_loop(oneLoop, 0, 1);
    #else
        App app;
        app.run();
    #endif
    return 0;
}
