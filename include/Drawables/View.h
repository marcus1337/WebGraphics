
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
    Camera camera;
    View(int _pixelWidth, int _pixelHeight);
    ~View();

    void setRenderPixelPerfect();

    void clear();
    void paint(Drawable& drawable);
    void paintMinusAlpha(Drawable& drawable);
    void subPaint(Drawable& drawable);

    virtual void render() override;
    int getPixelWidth();
    int getPixelHeight();

};

#endif