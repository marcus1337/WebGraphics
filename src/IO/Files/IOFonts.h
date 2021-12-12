
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include <ft2build.h>
#include FT_FREETYPE_H

#ifndef IOFONTS_H
#define IOFONTS_H


class IOFonts
{
private:
    FT_Library ft;
    void loadFont(const std::string& fontName);

public:
    IOFonts();
    ~IOFonts();

    std::map<std::string, FT_Face> fonts;
};

#endif