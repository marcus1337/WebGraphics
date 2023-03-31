
#ifndef IMAGE_H
#define IMAGE_H
#include <glm/glm.hpp>
#include <string>
#include <Graphics/Graphics.h>
#include "Drawable.h"

class Image : public Drawable {
    ImageShader imageShader;
public:
    Image(std::string _texture);
    void setTexture(std::string textureName);
    virtual void render() override;

};

#endif