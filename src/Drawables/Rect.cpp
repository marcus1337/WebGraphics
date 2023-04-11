#include "Drawables/Rect.h"

Rect::Rect() : Drawable(imageShader) {
    imageShader.setProgram("rectangle");
}

void Rect::render() {
    imageShader.setModel(model);
    objectContainer.imageObj.draw(imageShader);
}



