#include <glm/glm.hpp>
#include <Graphics/Graphics.h>
#include <Drawables/Drawable.h>

#ifndef RECT_H
#define RECT_H

class Rect : public Drawable {
protected:
    ImageShader imageShader;
public:
    Rect(Engine& _engine);
    virtual void render() override;
    void setFade(float _fade);
    void setThickness(float _thickness);
    void setRadius(float _radius);
};


#endif