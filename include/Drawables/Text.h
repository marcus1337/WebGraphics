
#ifndef TEXT_H
#define TEXT_H
#include <glm/glm.hpp>
#include <string>
#include <Graphics/Graphics.h>
#include <Drawables/Drawable.h>

class Text : public Drawable {
    std::string text = "_text_";
    std::string font = "Roboto-Regular";
    unsigned int pixelHeight = 60;
    TextShader textShader;

public:

    Text();
    virtual void render() override;
    unsigned int getPixelHeight();
    unsigned int getPixelWidth();
    void setText(std::string _text);
    void setFont(std::string _font);
    void setPixelHeight(unsigned int _pixelHeight);
    void center(int _x, int _y, int _width, int _height);
};

#endif // !TEXT_H


