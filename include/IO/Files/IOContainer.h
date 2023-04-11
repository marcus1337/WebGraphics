
#ifndef IOCONTAINER_H
#define IOCONTAINER_H
#include "Path/FilePathContainer.h"
#include "IOFonts.h"
#include "Shader/IOShader.h"
#include "Texture/IOTexture.h"
#include "IO/Files/OBJ/IOOBJ.h"

class IOContainer {
    IOContainer();
public:
    FilePathContainer filePathContainer;
    IOFonts ioFonts;
    IOShader ioShader;
    IOTexture ioTexture;
    IOOBJ ioOBJ;
    static IOContainer& getInstance();
};


#endif