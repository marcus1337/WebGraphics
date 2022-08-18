#include <glm/glm.hpp>
#include <Engine/Graphics.h>
#include <Drawables/Drawable.h>


#ifndef CIRCLE_H
#define CIRCLE_H

class Circle : public Drawable {

    ImageShader imageShader;
public:
    Circle(Engine& _engine);
    virtual void render() override;

};

#endif
