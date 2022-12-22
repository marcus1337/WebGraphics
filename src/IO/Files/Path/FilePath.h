#include <string>
#include <map>
#include <cstring>

#ifndef FILEPATH_H
#define FILEPATH_H

enum class FileType {
    BIN, TTF, PNG, WAV, TXT, SHADER, UNKNOWN
};

class FilePath {

    std::string path;
    static std::map<std::string, FileType> extensionMap;

public:

    FilePath(std::string _path);
    FileType getType();
    std::string getExtension();
    std::string getName();
    std::string getPath();

};

#endif