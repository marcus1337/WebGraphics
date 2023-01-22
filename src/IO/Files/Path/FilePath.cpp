#include "FilePath.h"
#include <iostream>

FilePath::FilePath(std::string _path) : path(_path) {

}

FileType FilePath::getType() {
    std::string extension = getExtension();
    if (extensionMap.contains(extension))
        return extensionMap[extension];
    std::cout << "Unknown extension [" << extension << "], Name [" << getName() << "], Path [" << getPath() << "]\n";
    return FileType::UNKNOWN;
}

std::string FilePath::getExtension() {
    size_t dotIndex = path.find_last_of('.');
    if (dotIndex != std::string::npos) {
        return path.substr(dotIndex);
    }
    return "";
}

std::string FilePath::getName() {
    std::string name = path;
    size_t slashIndex = name.find_last_of("/\\");
    if (slashIndex != std::string::npos)
        name = name.substr(slashIndex + 1);
    name = name.substr(0, name.length() - getExtension().length());
    return name;
}

std::string FilePath::getPath() {
    return path;
}

std::map<std::string, FileType> FilePath::extensionMap = {
    {".bin", FileType::BIN},
    {".ttf", FileType::TTF},
    {".png", FileType::PNG},
    {".txt", FileType::TXT},
    {".vert", FileType::SHADER},
    {".frag", FileType::SHADER}
};