
#include "FilePathContainer.h"
#include "IOFonts.h"
#include "IOLogs.h"
#include "IOShader.h"
#include "IOTexture.h"

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