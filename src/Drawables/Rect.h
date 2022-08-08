#include <glm/glm.hpp>
#include <Engine/Graphics.h>
#include <Drawables/Drawable.h>

#ifndef RECT_H
#define RECT_H

class Rect : public Drawable {

public:
    Rect(Engine& _engine);
    virtual void render() override;
};


#endif