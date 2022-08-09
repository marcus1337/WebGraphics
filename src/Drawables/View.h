#include "Drawable.h"
#include "Graphics/FrameBuffer.h"
#include <glm/glm.hpp>
#include <string>
#include <Engine/Graphics.h>
#include "Drawable.h"

#ifndef VIEW_H
#define VIEW_H

class View : public Drawable {
    FrameBuffer frameBuffer;
    int pixelWidth, pixelHeight;

public:

    View(Engine& _engine, int _pixelWidth, int _pixelHeight);
    ~View();
    void clear();
    void paint(Drawable& drawable);
    virtual void render() override;

};

#endif