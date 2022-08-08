#include "Image.h"

Image::~Image() {

}

void Image::addImageVariablesToShader(ImageShader& _shader, GLuint _textureID) {
    _shader.setTexture(_textureID);
    _shader.rotation = rotation;
    _shader.color = extraColor;
    _shader.mirror = !mirror;
    _shader.grayscale = grayscale;
    _shader.darken = darken;
    _shader.alpha = alpha;
    _shader.singleColor = singleColor;
    _shader.scale = glm::vec3(width, height, 1.0f);
    _shader.isSingleColor = false;
    _shader.setPosition(glm::vec3(x, y, 0.0f));
    _shader.effect = effect;
    _shader.mouse = { mouseX, mouseY };
}

void Image::addHighlightedImageVariablesToShader(ImageShader& _shader, GLuint _textureID) {
    addImageVariablesToShader(_shader, _textureID);
    _shader.scale = glm::vec3(width + borderSize, height + borderSize, 1.0f);
    glm::vec3 positionTmp = glm::vec3(x, y, 0.0f);
    positionTmp.x -= (float)borderSize / 2.0f;
    positionTmp.y -= (float)borderSize / 2.0f;
    _shader.setPosition(positionTmp);
    _shader.isSingleColor = true;
}

void Image::render(Graphics& _graphics) {
    GLuint _textureID = _graphics.glData.getTexture(texture);
    if (isHighlighted) {
        addHighlightedImageVariablesToShader(_graphics.imageShader, _textureID);
        _graphics.imageObject.draw(_graphics.imageShader);
    }
    addImageVariablesToShader(_graphics.imageShader, _textureID);
    _graphics.imageObject.draw(_graphics.imageShader);
}

Image* Image::clone() const {
    return new Image(*this);
}