#include <glm/glm.hpp>
#include <string>
#include <Graphics/Graphics.h>
#include "Drawable.h"

#ifndef IMAGE_H
#define IMAGE_H

class Image : public Drawable {
    ImageShader imageShader;
public:
    Image(Graphics& _graphics, IOContainer& _ioContainer, std::string _texture);
    void setTexture(std::string textureName);
    virtual void render() override;

};

#endif