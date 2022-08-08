
#include <GL/glew.h>
#include "glm/glm.hpp"
#include <map>
#include <string>
#include <tuple>

#include "Graphics/GlyphTextureCreator.h"
#include <array>
#include "Graphics/Shaders/Shader.h"
#include "VertexObject.h"

#ifndef TEXTOBJECT_H
#define TEXTOBJECT_H

class TextObject : public VertexObject
{
    GlyphTextureCreator glyphTextureCreator;

private:
    void setCharVertices(float& _x, Character ch);
    void bindAndDrawTextTextures(std::string& _text);
    std::string font;
    unsigned int pixelHeight = 60;
    std::string text;

    std::array<std::array<float, 4>, 6> getGlyphVertices(float _x, float _y, float _w, float _h);
    std::array<std::array<float, 4>, 6> getGlyphVertices(float& _xOffset, Character ch);

public:
    void setFont(std::string _font);
    void setText(std::string text);
    void draw(Shader& shader);
    void setTextPixelHeight(unsigned int _pixelHeight);
    ~TextObject();
    TextObject();
    int getTextWidth(std::string _text, int _pixelHeight, std::string _font);
};

#endif
