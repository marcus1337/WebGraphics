#include "CanvasSettings.h"
#include <IO/Files/IOBinary.h>

CanvasSettings::CanvasSettings() {
    load();
}
CanvasSettings::~CanvasSettings() {
    save();
}

void CanvasSettings::save() {
#ifndef EMSCRIPTEN
    IOBinary<CanvasSettings> ioBinary; 
    ioBinary.saveFile(*this, fileName);
#endif // !EMSCRIPTEN
}

void CanvasSettings::load() {
#ifndef EMSCRIPTEN
    IOBinary<CanvasSettings>().loadFile(*this, fileName);
#endif // !EMSCRIPTEN
}