
#ifdef EMSCRIPTEN
    #include <emscripten.h>
    #include <emscripten/html5.h>
    #include <emscripten/bind.h>
#endif

#include "App/App.h"

#ifdef EMSCRIPTEN
    App app;
    void loopStep(){
        app.loopStep();
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
        emscripten_set_main_loop(loopStep, 0, 1);
    #else
        App app; 
        app.loop(); 
    #endif
    return 0; //
}
