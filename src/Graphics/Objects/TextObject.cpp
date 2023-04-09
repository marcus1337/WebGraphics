
#include "Graphics/Objects/TextObject.h"
#include "IO/Files/IOContainer.h"

#include <iostream>
#include <glm/gtx/quaternion.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H

TextObject::TextObject() : glyphTextureCreator(), ioFonts(IOContainer::getInstance().ioFonts)
{
    setDefaultFont();

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void TextObject::setDefaultFont() {
    if (ioFonts.fonts.empty()) {
        std::cerr << "No fonts loaded! Not setting a default font... \n";
        return;
    }
    std::string defaultFont = ioFonts.fonts.begin()->first;
    std::cout << "Setting default font to: [" << defaultFont << "] \n";
    setFont(defaultFont);
}

void TextObject::setTextPixelHeight(unsigned int _pixelHeight) {
    pixelHeight = _pixelHeight;
}

TextObject::~TextObject()
{
}

void TextObject::setText(std::wstring _text)
{
    text = _text;
}

std::array<std::array<float, 4>, 6> TextObject::getGlyphVertices(float _x, float _y, float _w, float _h) {
    return { {
        {_x, _y + _h, 0.0f, 0.0f},
        {_x, _y, 0.0f, 1.0f},
        {_x + _w, _y, 1.0f, 1.0f},

        {_x, _y + _h, 0.0f, 0.0f},
        {_x + _w, _y, 1.0f, 1.0f},
        {_x + _w, _y + _h, 1.0f, 0.0f} } };
}

std::array<std::array<float, 4>, 6> TextObject::getGlyphVertices(float& _xOffset, Character ch) {
    float _x = _xOffset + ch.Bearing.x;
    _xOffset += (ch.Advance >> 6); // bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
    float _y = -(ch.Size.y - ch.Bearing.y);
    return getGlyphVertices(_x, _y, ch.Size.x, ch.Size.y);
}

void TextObject::setCharVertices(float& _xOffset, Character ch)
{
    std::array<std::array<float, 4>, 6> vertices = getGlyphVertices(_xOffset, ch);
    glBindTexture(GL_TEXTURE_2D, ch.TextureID);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices.data()); // be sure to use glBufferSubData and not glBufferData
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void TextObject::setFont(std::string _font) {
    if (!glyphTextureCreator.fontExists(_font)) {
        std::cerr << "Error: font [" <<  _font <<"] not found\n";
        return;
    }
    font = _font;
}

void TextObject::bindAndDrawTextTextures(std::wstring& _text)
{
    const std::map<wchar_t, Character>& characters = glyphTextureCreator.getCharacters(font, pixelHeight);
    float _xOffset = 0;
    for (std::wstring::const_iterator c = _text.begin(); c != _text.end(); c++) {
        if (!characters.contains(*c)) {
            std::cerr << "ERROR " << (int)*c << " DOES NOT EXIST IN CHARACTER MAP!\n";
        }
        else {
            setCharVertices(_xOffset, characters.at(*c));
        }
    }
}

int TextObject::getTextWidth(std::wstring _text, int _pixelHeight, std::string _font) {
    const std::map<wchar_t, Character>& characters = glyphTextureCreator.getCharacters(_font, _pixelHeight);
    float _xOffset = 0;
    for (std::wstring::const_iterator c = _text.begin(); c != _text.end(); c++) {
        if (!characters.contains(*c)) {
            std::cerr << "ERROR " << (int)*c << " DOES NOT EXIST IN CHARACTER MAP!\n";
        }
        else {
            getGlyphVertices(_xOffset, characters.at(*c));
        }
    }
    return (int)_xOffset;
}

void TextObject::draw(Shader& shader)
{
    glBindVertexArray(vao);
    shader.rotateOffset = glm::vec2(getTextWidth(text, pixelHeight, font), pixelHeight);
    shader.setUniforms();
    bindAndDrawTextTextures(text);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);
}