
#include "GLData.h"

GLData::GLData()
{
    iotexture.preloadTextures();
    programs.reload();
    std::cout << "GLData()\n";
}

void GLData::reload() {
    programs.reload();
}

GLuint GLData::getProgram(std::string name) {
    return programs.get(name);
}

GLuint GLData::getTexture(std::string name) {
    return iotexture.getTexture(name);
}