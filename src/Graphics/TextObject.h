
#include <GL/glew.h>
#include "glm/glm.hpp"
#include <map>
#include <string>
#include <tuple>

#include "IO/Files/IOFonts.h"

#include <ft2build.h>
#include FT_FREETYPE_H

#ifndef FREETYPETEXT_H
#define FREETYPETEXT_H

class TextObject
{

protected:
    struct Character
    {
        unsigned int TextureID; // ID handle of the glyph texture
        glm::ivec2 Size;        // Size of glyph
        glm::ivec2 Bearing;     // Offset from baseline to left/top of glyph
        unsigned int Advance;   // Offset to advance to next glyph
    };

    std::map<std::string, std::map<char, Character>> CharactersMap;
    glm::mat4 VP, V, P;
    GLuint vao, vbo;

    glm::mat4 getMVP();

private:
    IOFonts iofonts;
    void setCharVertices(float &_x, Character ch);
    void bindAndDrawTextTextures();
    void setUniforms();
    void addCharacter(char c, unsigned int textureID, FT_Face &face, const std::string& fontName);
    unsigned int makeGlyphTexture(FT_Face &face);

    int loadGlyphs(FT_Face face, const std::string& fontName);
    void initVBO();

public:
    void setText(std::string text);
    std::tuple<float, float> getTextWidthAndHeight(std::string _text);
    void setScale(glm::vec3 _scale);
    void setPosition(glm::vec3 _position);
    void setViewProjectionMatrix(glm::mat4 &_VP, glm::mat4 &_V, glm::mat4 &_P);
    void draw();
    ~TextObject();
    TextObject();

    std::string text;
    glm::vec4 color = glm::vec4(1.0f, 0.0f, 1.0f, 1.0f);
    glm::vec3 position, scale;
    float rotation;
    GLuint programID = 0;
    std::string font;
};

#endif
