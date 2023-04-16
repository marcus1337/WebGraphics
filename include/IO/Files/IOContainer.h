
#ifndef IOCONTAINER_H
#define IOCONTAINER_H
#include "Path/FilePathContainer.h"
#include "IOFonts.h"
#include "Shader/IOShader.h"
#include "Texture/IOTexture.h"
#include "IO/Files/OBJ/IOOBJ.h"
#include "IO/Files/Pose/IOPose.h"

class IOContainer {
    IOContainer();
public:
    FilePathContainer filePathContainer;
    IOFonts ioFonts;
    IOShader ioShader;
    IOTexture ioTexture;
    IOOBJ ioOBJ;
    IOPose ioPose;
    static IOContainer& getInstance();
};


#endif