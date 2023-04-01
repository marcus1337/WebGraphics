
#ifndef FILEPATH_H
#define FILEPATH_H
#include <string>
#include <map>
#include <cstring>

enum class FileType {
    BIN, TTF, PNG, TXT, SHADER, UNKNOWN, WAV, LUA
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