
#ifndef IOCONTAINER_H
#define IOCONTAINER_H
#include "Path/FilePathContainer.h"
#include "IOFonts.h"
#include "Shader/IOShader.h"
#include "Texture/IOTexture.h"

class IOContainer {

public:
    FilePathContainer filePathContainer;
    IOFonts ioFonts;
    IOShader ioShader;
    IOTexture ioTexture;
};


#endif