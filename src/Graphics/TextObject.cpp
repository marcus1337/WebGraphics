
#include "TextObject.h"

#include <iostream>
#include <glm/gtx/quaternion.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H

TextObject::TextObject() : position(glm::vec3(0.f, 0.f, 0.f)), scale(glm::vec3(1.0f, 1.0f, 1.0f)), rotation(0)
{
    initVBO();

    for (const auto &[key, value] : iofonts.fonts)
    {
        int isError = loadGlyphs(value, key);
        if(isError != 0){
            std::cout << "Load glyphs failed: " << isError << ", " << value << std::endl;
            return;
        }
    }
}

TextObject::~TextObject()
{
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
}

void TextObject::addCharacter(char c, unsigned int textureID, FT_Face &face, const std::string& fontName)
{
    Character character = {
        textureID,
        glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
        glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
        static_cast<unsigned int>(face->glyph->advance.x)};

    CharactersMap[fontName].insert(std::pair<char, Character>(c, character));
}

unsigned int TextObject::makeGlyphTexture(FT_Face &face)
{
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    int bitWidth = face->glyph->bitmap.width;
    int bitHeight = face->glyph->bitmap.rows;
    unsigned char* tmpBuffer = new unsigned char[bitWidth*bitHeight*3];
    for (int i = 0; i < bitWidth * bitHeight; i++) {
        tmpBuffer[i*3] = face->glyph->bitmap.buffer[i];
    }
    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RGB,
        face->glyph->bitmap.width,
        face->glyph->bitmap.rows,
        0,
        GL_RGB,
        GL_UNSIGNED_BYTE,
        tmpBuffer);
    delete[] tmpBuffer;

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    return texture;
}

int TextObject::loadGlyphs(FT_Face face, const std::string& fontName)
{
    CharactersMap[fontName] = std::map<char, Character>();
    FT_Set_Pixel_Sizes(face, 0, 60);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // disable byte-alignment restriction

    for (unsigned char c = 0; c < 128; c++)
    {
        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
            continue;
        }
        addCharacter(c, makeGlyphTexture(face), face, fontName);
    }

    glBindTexture(GL_TEXTURE_2D, 0);

    return 0;
}

void TextObject::setPosition(glm::vec3 _position)
{
    position = _position;
}

void TextObject::setScale(glm::vec3 _scale)
{
    scale = _scale * glm::vec3(1.0f, 1.0f, 1.0f);
}

void TextObject::setViewProjectionMatrix(glm::mat4 &_VP, glm::mat4 &_V, glm::mat4 &_P)
{
    VP = _VP;
    V = _V;
    P = _P;
}

void TextObject::setText(std::string _text)
{
    text = _text;
}

void TextObject::initVBO()
{
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

glm::mat4 TextObject::getMVP()
{
    glm::mat4 scaleMat = glm::scale(glm::mat4(1.0f), scale);
    glm::vec3 rotationAxis(0, 0, 1.0f);
    glm::quat myQuat = glm::angleAxis(glm::radians(rotation), rotationAxis);

    glm::mat4 rotateMat = glm::toMat4(myQuat);
    std::tuple<float,float> widthAndHeight = getTextWidthAndHeight(text);
    float width = std::get<0>(widthAndHeight);
    float height = std::get<1>(widthAndHeight);
    glm::mat4 offsetToMiddle = glm::translate(glm::mat4(1.0f),
                                               glm::vec3(-width/2.0f, -height/2.0f, 0.0f));
    glm::mat4 revertOffsetToMiddle = glm::translate(glm::mat4(1.0f),
        glm::vec3(width / 2.0f, height / 2.0f, 0.0f));

    glm::mat4 translateMat = glm::translate(glm::mat4(1.0f), position);
    glm::mat4 modModel = translateMat * revertOffsetToMiddle * rotateMat * offsetToMiddle * scaleMat;

    glm::mat4 MVP = VP * modModel;
    return MVP;
}

std::tuple<float, float> TextObject::getTextWidthAndHeight(std::string _text)
{
    float _width = 0;
    float _height = 0;
    float x = 0;
    float y = 0;

    std::string::const_iterator c;
    auto& Characters = CharactersMap[font];
    for (c = _text.begin(); c != _text.end(); c++)
    {
        Character ch = Characters[*c];
        float xpos = x + ch.Bearing.x;
        float ypos = y - (ch.Size.y - ch.Bearing.y);
        float w = ch.Size.x;
        float h = ch.Size.y;

        _width = std::max(xpos + w, _width);
        _height = std::max(ypos + h, _height);

        x += (ch.Advance >> 6);
    }

    return std::make_tuple(_width, _height);
}

void TextObject::setCharVertices(float &_x, Character ch)
{
    float xpos = _x + ch.Bearing.x;
    float ypos = -(ch.Size.y - ch.Bearing.y);
    float w = ch.Size.x;
    float h = ch.Size.y;

    float vertices[6][4] = {
        {xpos, ypos + h, 0.0f, 0.0f},
        {xpos, ypos, 0.0f, 1.0f},
        {xpos + w, ypos, 1.0f, 1.0f},

        {xpos, ypos + h, 0.0f, 0.0f},
        {xpos + w, ypos, 1.0f, 1.0f},
        {xpos + w, ypos + h, 1.0f, 0.0f}};

    glBindTexture(GL_TEXTURE_2D, ch.TextureID);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // be sure to use glBufferSubData and not glBufferData
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glDrawArrays(GL_TRIANGLES, 0, 6);
    _x += (ch.Advance >> 6); // bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
}

void TextObject::bindAndDrawTextTextures()
{
    if (!CharactersMap.contains(font)) {
        std::cout << "Error: font not found\n";
        return;
    }

    std::map<char, Character>& Characters = CharactersMap[font];
    float _x = 0;
    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++)
        setCharVertices(_x, Characters[*c]);
}

void TextObject::setUniforms()
{
    glUniform4fv(glGetUniformLocation(programID, "textColor"), 1, &color[0]);
    glm::mat4 MVP = getMVP();
    glUniformMatrix4fv(glGetUniformLocation(programID, "MVP"), 1, GL_FALSE, &MVP[0][0]);
    glActiveTexture(GL_TEXTURE0);
}

void TextObject::draw()
{
    glBindVertexArray(vao);
    glUseProgram(programID);

    setUniforms();
    bindAndDrawTextTextures();

    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);
}