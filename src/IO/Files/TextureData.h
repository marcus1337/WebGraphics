
#include <vector>

#ifndef TEXTUREDATA_H
#define TEXTUREDATA_H

class TextureData{
public:
    std::vector<unsigned char> data;
    unsigned width, height;
    unsigned error;
    std::string fileName;
};

#endif