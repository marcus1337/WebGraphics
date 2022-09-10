
#ifdef EMSCRIPTEN
    #include <emscripten.h>
    #include <emscripten/html5.h>
    #include <emscripten/bind.h>
#endif

#include "App/App.h"

#ifdef EMSCRIPTEN
    App app;
    void update(){
        app.update();
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
        emscripten_set_main_loop(update, 60, 1);
    #else
        App app; 
        app.run(); 
    #endif
    return 0;
}
