
#ifndef TEXTOBJECT_H
#define TEXTOBJECT_H

#include <GL/glew.h>
#include "glm/glm.hpp"
#include <map>
#include <string>
#include <tuple>

#include "Graphics/GlyphTextureCreator.h"
#include <array>
#include "Graphics/Shaders/Shader.h"
#include "VertexObject.h"

class TextObject : public VertexObject
{
    GlyphTextureCreator glyphTextureCreator;
    IOFonts& ioFonts;

private:
    void setCharVertices(float& _x, Character ch);
    void bindAndDrawTextTextures(std::wstring& _text);
    std::vector<Character> getCharacters(const std::wstring& text);
    std::string font;
    unsigned int pixelHeight = 60;
    std::wstring text;

    std::array<std::array<float, 4>, 6> getGlyphVertices(float _x, float _y, float _w, float _h);
    std::array<std::array<float, 4>, 6> getGlyphVertices(float& _xOffset, Character ch);

    void setDefaultFont();

public:
    void setFont(std::string _font);
    void setText(std::wstring text);
    virtual void draw(Shader& shader) override;
    void setTextPixelHeight(unsigned int _pixelHeight);
    ~TextObject();
    TextObject();
    int getTextWidth(std::wstring _text, int _pixelHeight, std::string _font);
};

#endif
