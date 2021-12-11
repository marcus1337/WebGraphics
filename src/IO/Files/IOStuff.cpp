
#include "IOStuff.h"
#include <filesystem>
#include <fstream>

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <map>
#include <GL/glew.h>

IOStuff::IOStuff()
{
#ifdef EMSCRIPTEN
    binFolderPath = "./res/";
    modelsPath = binFolderPath + "models/";
#else
    binFolderPath = std::filesystem::current_path().string() + "//res//";
    modelsPath = binFolderPath + "models//";
#endif
}

IOStuff::~IOStuff()
{
}
