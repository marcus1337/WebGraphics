
#ifndef RECT_H
#define RECT_H
#include <glm/glm.hpp>
#include <Graphics/Graphics.h>
#include <Drawables/Drawable.h>

class Rect : public Drawable {
protected:
    ImageShader imageShader;
public:
    Rect();
    virtual void render() override;
};


#endif