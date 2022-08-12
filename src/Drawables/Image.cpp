#include "Image.h"

Image::Image(Engine& _engine, std::string _texture) : Drawable(_engine, imageShader) {
    imageShader.setProgram(graphics.glData.getProgram("image"));
    imageShader.rotation = 180.0f;
    imageShader.setTexture(graphics.glData.getTexture(_texture));
    imageShader.mirror = true;
}

void Image::render() {
    graphics.imageObject.draw(imageShader);
}
