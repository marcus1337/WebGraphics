
#ifndef CHARACTER_H
#define CHARACTER_H
#include <GL/glew.h>
#include "glm/glm.hpp"
#include <map>
#include <string>
#include <tuple>
#include <vector>
#include <algorithm>
#include <array>
#include <tuple>
#include "IO/Files/IOFonts.h"

#include <ft2build.h>
#include FT_FREETYPE_H

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
   IOFonts& ioFonts;
   std::map<std::tuple<wchar_t, std::string, unsigned int>, Character> characters; //character, textureID, pixelHeight
   Character loadGlyph(wchar_t c, std::string font, unsigned int pixelHeight);
   Character makeCharacter(wchar_t c, unsigned int textureID, FT_Face& face);
   unsigned int makeGlyphTexture(FT_Face& face);
public:
    GlyphTextureCreator();
    ~GlyphTextureCreator();
    Character getCharacter(wchar_t c, std::string font, unsigned int pixelHeight);
    bool fontExists(std::string font);
};

#endif // !GLYPH_TEXTURE_CREATOR_H