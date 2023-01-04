#include "Drawable.h"
#include "Graphics/FrameBuffer.h"
#include <glm/glm.hpp>
#include <string>
#include <Graphics/Graphics.h>
#include "Drawable.h"

#ifndef VIEW_H
#define VIEW_H

class View : public Drawable {
    FrameBuffer frameBuffer;
    int pixelWidth, pixelHeight;

public:

    View(Graphics& _graphics, IOContainer& _ioContainer, int _pixelWidth, int _pixelHeight);
    ~View();

    void setRenderPixelPerfect();
    void setPixelColor(int _x, int _y, glm::vec3 _color);
    void setPixelAlpha(int _x, int _y, float _alpha);
    void setPixel(int _x, int _y, glm::vec4 _color);
    glm::vec4 getPixel(int _x, int _y);

    void clear();
    void paint(Drawable& drawable);
    void subPaint(Drawable& drawable);

    virtual void render() override;
    int getPixelWidth();
    int getPixelHeight();

};

#endif