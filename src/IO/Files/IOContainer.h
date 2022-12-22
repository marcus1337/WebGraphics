
#include "Path/FilePathContainer.h"
#include "IOFonts.h"
#include "IOLogs.h"
#include "Shader/IOShader.h"
#include "Texture/IOTexture.h"

#ifndef IOCONTAINER_H
#define IOCONTAINER_H

class IOContainer {

public:
    FilePathContainer filePathContainer;
    IOFonts ioFonts;
    IOLogs ioLogs;
    IOShader ioShader;
    IOTexture ioTexture;
};


#endif