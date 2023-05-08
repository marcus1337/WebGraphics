
#ifndef VIEW_H
#define VIEW_H
#include "Drawable.h"
#include "Graphics/FrameBuffer.h"
#include <glm/glm.hpp>
#include <string>
#include <Graphics/Graphics.h>
#include "Drawable.h"

class View : public Drawable {
    FrameBuffer frameBuffer;
    int pixelWidth, pixelHeight;

public:
    View(int _pixelWidth, int _pixelHeight, bool depthBuffer = false);
    ~View();

    void setRenderPixelPerfect();
    void setPixel(int x, int y, glm::vec3 color);

    void clear();
    void paint(Drawable& drawable);
    void paintMinusAlpha(Drawable& drawable);
    void subPaint(Drawable& drawable);

    virtual void render() override;
    int getPixelWidth();
    int getPixelHeight();

};

#endif