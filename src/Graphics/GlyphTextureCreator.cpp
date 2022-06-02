#include "GlyphTextureCreator.h"
#include <iostream>

GlyphTextureCreator::GlyphTextureCreator() {
    createAndAddTextures(60);
}
GlyphTextureCreator::~GlyphTextureCreator() {

}

void GlyphTextureCreator::createAndAddTextures(unsigned int pixelHeight) {
    auto textures = createTextures(pixelHeight);
    for (const auto& [font, value] : textures) {
        auto key = std::make_pair(font, pixelHeight);
        characterMap[key] = value;
    }
}

const std::map<char, Character>& GlyphTextureCreator::getCharacters(std::string font, unsigned int _pixelHeight) {
    auto key = std::make_pair(font, _pixelHeight);
    if (!characterMap.contains(key))
        createAndAddTextures(_pixelHeight);
    return characterMap[key];
}

bool GlyphTextureCreator::fontExists(std::string font) {
    return iofonts.fonts.contains(font);
}

std::map<std::string, std::map<char, Character>> GlyphTextureCreator::createTextures(unsigned int pixelHeight) {
    std::map<std::string, std::map<char, Character>> characterMap;
    for (const auto& [key, value] : iofonts.fonts)
        characterMap[key] = loadGlyphs(value, pixelHeight);
    return characterMap;
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

std::map<char, Character> GlyphTextureCreator::loadGlyphs(FT_Face face, unsigned int pixelHeight)
{
    std::map<char, Character> _characterMap;
    FT_Set_Pixel_Sizes(face, 0, pixelHeight);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // disable byte-alignment restriction

    for (unsigned char c = 0; c < 128; c++)
    {
        if (!FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            unsigned int glyphTexture = makeGlyphTexture(face);
            addCharacter(c, glyphTexture, face, _characterMap);
        }
        else {
            std::cout << "ERROR::FREETYTPE: Failed to load Glyph. Face: " << face << " char: " << (int)c << std::endl;
        }
    }

    return _characterMap;
}

void GlyphTextureCreator::addCharacter(char c, unsigned int textureID, FT_Face& face, std::map<char, Character>& _characterMap)
{
    Character character = {
        textureID,
        glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
        glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
        static_cast<unsigned int>(face->glyph->advance.x) };

    _characterMap.insert(std::pair<char, Character>(c, character));
}