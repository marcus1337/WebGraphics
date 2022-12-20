
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

public:
    IOFonts();
    ~IOFonts();

    void loadFonts(std::vector<std::string> fontFilePaths, std::vector<std::string> fontNames);
    void print();

    std::map<std::string, FT_Face> fonts;
};

#endif