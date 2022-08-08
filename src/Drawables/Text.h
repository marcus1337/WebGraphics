#include <glm/glm.hpp>
#include <string>
#include <Engine/Graphics.h>

#ifndef TEXT_H
#define TEXT_H

class Text {
    std::string text = "_text_";
    std::string font = "Roboto-Regular";
    unsigned int pixelHeight = 60;
    glm::vec4 color = glm::vec4(1.0f, 0.0f, 1.0f, 1.0f);

public:

    void render(Graphics& _graphics);
    Text() = default;
    Text(std::string _text, std::string _font, unsigned int _pixelHeight);
    int x = 0, y = 0;
    float rotation = 0;
    unsigned int getPixelHeight();
    unsigned int getPixelWidth(Graphics& _graphics);
    void setText(std::string _text);
    void setFont(std::string _font);
    void setPixelHeight(unsigned int _pixelHeight);
    void setColor(glm::vec3 _color);
    void setColor(glm::vec4 _color);
    void setAlpha(float _alpha);
};

#endif // !TEXT_H
