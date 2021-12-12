#include "IOFonts.h"
#include "FolderPaths.h"

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

    for (const auto &entry : std::filesystem::directory_iterator(FolderPaths::getFontsPath()))
    {
        const std::string fontName = entry.path().stem().string();
        loadFont(fontName);
    }
}

void IOFonts::loadFont(const std::string& fontName){
    FT_Face face;
    std::string fontPathAndName = FolderPaths::getFontsPath() + fontName + ".ttf";
    if (FT_New_Face(ft, fontPathAndName.c_str(), 0, &face))
    {
        std::cout << "ERROR::FREETYPE: Failed to load font: " << fontPathAndName << std::endl;
    }
    fonts[fontName] = face;
}

IOFonts::~IOFonts()
{
    for (const auto &[key, value] : fonts)
    {
        FT_Done_Face(value);
    }
    FT_Done_FreeType(ft);
}