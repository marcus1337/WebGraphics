#include <glm/glm.hpp>
#include <string>
#include <Engine/Graphics.h>
#include "Drawable.h"

#ifndef IMAGE_H
#define IMAGE_H

class Image : public Drawable {
public:
    Image(Engine& _engine);
    virtual void render() override;

};

#endif