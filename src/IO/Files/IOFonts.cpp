#include "IOFonts.h"
#include <iostream>
#include <filesystem>
#include <fstream>

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

IOFonts::IOFonts()
{
    if (FT_Init_FreeType(&ft))
    {
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
        return;
    }
}

void IOFonts::loadFonts(std::vector<std::string> fontFilePaths, std::vector<std::string> fontNames) {
    for (int i = 0; i < fontNames.size(); i++) {
        std::string fontFilePath = fontFilePaths[i];
        std::string fontName = fontNames[i];
        FT_Face face;
        if (FT_New_Face(ft, fontFilePath.c_str(), 0, &face))
        {
            std::cout << "ERROR::FREETYPE: Failed to load font: " << fontFilePath << std::endl;
        }
        fonts[fontName] = face;
    }
}

IOFonts::~IOFonts()
{
    for (const auto &[key, value] : fonts)
    {
        FT_Done_Face(value);
    }
    FT_Done_FreeType(ft);
}

void IOFonts::print() {
    std::cout << "Num fonts: " << fonts.size() << std::endl;
    std::cout << "Loaded fonts: \n";
    for (auto keyValue : fonts) {
        std::cout << std::get<0>(keyValue) << std::endl;
    }
}