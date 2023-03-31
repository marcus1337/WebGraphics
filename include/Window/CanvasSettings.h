
#ifndef CANVASSETTINGS_H
#define CANVASSETTINGS_H
#include <string>

class CanvasSettings {

public:
    CanvasSettings();
    ~CanvasSettings();

    int width = 1280;
    int height = 720;
    bool fullScreen = false;
    std::string appName = "MyApp";

};

#endif // !CANVASSETTINGS_H
