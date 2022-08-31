#include <string>
#include "bitsery/adapter/stream.h"
#include <bitsery/adapter/buffer.h>
#include <bitsery/bitsery.h>
#include <bitsery/traits/array.h>
#include <bitsery/traits/vector.h>
#include <bitsery/traits/string.h>

#ifndef CANVASSETTINGS_H
#define CANVASSETTINGS_H

class CanvasSettings {
    void save();
    void load();
    std::string fileName = "canvasSettings";

public:
    CanvasSettings();
    ~CanvasSettings();

    int width = 1280;
    int height = 720;
    bool fullScreen = false;
    std::string appName = "MyApp";

};

template <typename S>
void serialize(S& s, CanvasSettings& o) {
    s.value4b(o.width);
    s.value4b(o.height);
    s.value1b(o.fullScreen);
}

#endif // !CANVASSETTINGS_H
