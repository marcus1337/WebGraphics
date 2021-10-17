

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <iostream>

#ifdef EMSCRIPTEN
    #include <emscripten.h>
    #include <emscripten/html5.h>
#endif

#include "App.h"

App app;

void oneLoop(){
    app.gameStep();
}

int main(int argc, char *argv[]){

    #ifdef EMSCRIPTEN
        emscripten_set_main_loop(oneLoop, 0, 1);
    #else
        app.run();
    #endif
    return 0;
}
