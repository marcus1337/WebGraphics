#include <GL/glew.h>
#include "glm/glm.hpp"
#include <map>
#include <string>
#include <tuple>

#include "IO/Files/IOFonts.h"

#include <ft2build.h>
#include FT_FREETYPE_H

#ifndef CHARACTER_H
#define CHARACTER_H
struct Character
{
    unsigned int TextureID; // ID handle of the glyph texture
    glm::ivec2 Size;        // Size of glyph
    glm::ivec2 Bearing;     // Offset from baseline to left/top of glyph
    unsigned int Advance;   // Offset to advance to next glyph
};
#endif // !CHARACTER_H

#ifndef GLYPH_TEXTURE_CREATOR_H
#define GLYPH_TEXTURE_CREATOR_H
class GlyphTextureCreator {
    IOFonts iofonts;
    std::map<char, Character> loadGlyphs(FT_Face face, unsigned int pixelHeight);
    unsigned int makeGlyphTexture(FT_Face& face);
    void addCharacter(char c, unsigned int textureID, FT_Face& face, std::map<char, Character>& _characterMap);
public:
    GlyphTextureCreator();
    ~GlyphTextureCreator();

    std::map<std::string, std::map<char, Character>> createTextures();
};

#endif // !GLYPH_TEXTURE_CREATOR_H