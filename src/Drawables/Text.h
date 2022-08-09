#include <glm/glm.hpp>
#include <string>
#include <Engine/Graphics.h>
#include <Engine/Engine.h>
#include <Drawables/Drawable.h>

#ifndef TEXT_H
#define TEXT_H

class Text : public Drawable {
    std::string text = "_text_";
    std::string font = "Roboto-Regular";
    unsigned int pixelHeight = 60;

public:

    Text(Engine& _engine);
    virtual void render() override;
    unsigned int getPixelHeight();
    unsigned int getPixelWidth();
    void setText(std::string _text);
    void setFont(std::string _font);
    void setPixelHeight(unsigned int _pixelHeight);
    void center(int _x, int _y, int _width, int _height);
};

#endif // !TEXT_H


