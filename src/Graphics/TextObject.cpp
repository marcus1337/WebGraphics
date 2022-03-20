
#include "TextObject.h"

#include <iostream>
#include <glm/gtx/quaternion.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H

TextObject::TextObject() : position(glm::vec3(0.f, 0.f, 0.f)), scale(glm::vec3(1.0f, 1.0f, 1.0f)),
               rotationAxis(glm::vec3(0.f, 0.f, 1.f)), rotation(0)
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
    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RED,
        face->glyph->bitmap.width,
        face->glyph->bitmap.rows,
        0,
        GL_RED,
        GL_UNSIGNED_BYTE,
        face->glyph->bitmap.buffer);

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
    lastPosition = _position;
    position = _position;
    //position.y -= (totalHeight * scale.y);
    isMidPositionSet = false;
    isPositionSet = true;
}

void TextObject::setScale(glm::vec3 _scale)
{
    scale = _scale * glm::vec3(0.001f, 0.001f, 1.0f);
    if (isMidPositionSet)
        setMidPosition(midPosition);
    if (isPositionSet)
        setPosition(lastPosition);
}

void TextObject::setMidPosition(glm::vec3 _midPosition)
{
    position = _midPosition;
    position.x = position.x - (totalWidth * scale.x) / 2.0f;
    position.y = position.y + (totalHeight * scale.y) / 2.0f;
    isMidPositionSet = true;
    isPositionSet = false;
    midPosition = _midPosition;
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
    auto wh = getTextWidthAndHeight(text);
    totalHeight = std::get<1>(wh);
    totalWidth = std::get<0>(wh);
}

void TextObject::initVBO()
{
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glCreateBuffers(1, &vbo);
    glNamedBufferStorage(vbo, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_STORAGE_BIT);
    glVertexArrayVertexBuffer(vao, 0, vbo, 0, sizeof(GLfloat) * 4);
    glVertexArrayAttribFormat(vao, 0, 4, GL_FLOAT, GL_FALSE, 0);
    glVertexArrayAttribBinding(vao, 0, 0);
    glEnableVertexArrayAttrib(vao, 0);
    glBindVertexArray(0);
}

glm::mat4 TextObject::getMVP()
{
    glm::mat4 scaleMat = glm::scale(glm::mat4(1.0f), scale);
    glm::quat myQuat = glm::angleAxis(glm::radians(rotation), rotationAxis);

    glm::mat4 rotateMat = glm::toMat4(myQuat);
    glm::mat4 pointOfRotation = glm::translate(glm::mat4(1.0f),
                                               glm::vec3(0, -(totalHeight * scale.y), 0));

    glm::mat4 translateMat = glm::translate(glm::mat4(1.0f), position);
    glm::mat4 modModel = translateMat * rotateMat * pointOfRotation * scaleMat;

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

void TextObject::setSourceWindowSize(float _SCR_WIDTH, float _SCR_HEIGHT)
{
    SCR_WIDTH = _SCR_WIDTH;
    SCR_HEIGHT = _SCR_HEIGHT;
    scaleValX = 1.0f / SCR_WIDTH;
    scaleValY = 1.0f / SCR_HEIGHT;
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