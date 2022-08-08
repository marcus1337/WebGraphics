#include "ButtonImage.h"

void ButtonImage::render(Graphics& _graphics) {
    GLuint _textureID = _graphics.glData.getTexture(texture);
    if (isHighlighted) {
        addHighlightedImageVariablesToShader(_graphics.buttonShader, _textureID);
        _graphics.imageObject.draw(_graphics.buttonShader);
    }
    addImageVariablesToShader(_graphics.buttonShader, _textureID);
    _graphics.imageObject.draw(_graphics.buttonShader);
}

Image* ButtonImage::clone() const {
    return new ButtonImage(*this);
}