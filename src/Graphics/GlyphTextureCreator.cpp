#include "Graphics/GlyphTextureCreator.h"
#include <iostream>
#include "IO/Files/IOContainer.h"
#include <wchar.h>
#include <GL/gl.h>
#include <GL/glew.h>

GlyphTextureCreator::GlyphTextureCreator() : ioFonts(IOContainer::getInstance().ioFonts) {

}
GlyphTextureCreator::~GlyphTextureCreator() {
    for (const auto& [key, character] : characters) {
        glDeleteTextures(1, &character.TextureID);
    }
}

Character GlyphTextureCreator::getCharacter(wchar_t c, std::string font, unsigned int pixelHeight) {
    std::tuple<wchar_t, std::string, unsigned int> key = std::make_tuple(c, font, pixelHeight);
    if (!characters.contains(key)) {
        characters[key] = loadGlyph(c, font, pixelHeight);
    }
    return characters[key];
}

bool GlyphTextureCreator::fontExists(std::string font) {
    return ioFonts.fonts.contains(font);
}

unsigned int GlyphTextureCreator::makeGlyphTexture(FT_Face& face)
{
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    int bitWidth = face->glyph->bitmap.width;
    int bitHeight = face->glyph->bitmap.rows;
    unsigned char* tmpBuffer = new unsigned char[bitWidth * bitHeight * 3];
    for (int i = 0; i < bitWidth * bitHeight; i++) {
        tmpBuffer[i * 3] = face->glyph->bitmap.buffer[i];
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

Character GlyphTextureCreator::loadGlyph(wchar_t c, std::string font, unsigned int pixelHeight) {
    FT_Face face = ioFonts.fonts[font];
    Character character;
    FT_Set_Pixel_Sizes(face, 0, pixelHeight);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // disable byte-alignment restriction

    if (!FT_Load_Char(face, c, FT_LOAD_RENDER))
    {
        unsigned int glyphTexture = makeGlyphTexture(face);
        character = makeCharacter(c, glyphTexture, face);
    }
    else {
        std::cout << "ERROR::FREETYTPE: Failed to load Glyph. Face: " << face << " char: " << (int)c << std::endl;
    }
    return character;
}

Character GlyphTextureCreator::makeCharacter(wchar_t c, unsigned int textureID, FT_Face& face) {
    return { textureID,
        glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
        glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
        static_cast<unsigned int>(face->glyph->advance.x) };
}