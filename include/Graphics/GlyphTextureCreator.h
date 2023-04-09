
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
    std::map<wchar_t, Character> loadGlyphs(FT_Face face, unsigned int pixelHeight);
    unsigned int makeGlyphTexture(FT_Face& face);
    void addCharacter(wchar_t c, unsigned int textureID, FT_Face& face, std::map<wchar_t, Character>& _characterMap);
    std::map<std::pair<std::string,int>, std::map<wchar_t, Character>> characterMap;
    std::map<std::string, std::map<wchar_t, Character>> createCharacterTextureMap(unsigned int pixelHeight);
    void createAndAddTextures(unsigned int pixelHeight);
public:
    GlyphTextureCreator();
    ~GlyphTextureCreator();
    const std::map<wchar_t, Character>& getCharacters(std::string font, unsigned int _pixelHeight);
    bool fontExists(std::string font);
};

#endif // !GLYPH_TEXTURE_CREATOR_H