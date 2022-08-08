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

    void setTexture(std::string _texture);
    void setSingleColor(glm::vec3 _color);

    void setMirror(bool _mirror);
    void setEffect(float _effect);
    void setIsSingleColor(bool _isSingleColor);
    void setGray(bool _gray);
    void setDark(bool _dark);

};

#endif