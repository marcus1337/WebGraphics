
#ifndef FILEPATH_H
#define FILEPATH_H
#include <string>
#include <map>
#include <cstring>
#include <filesystem>

enum class FileType {
    BIN, TTF, PNG, TXT, SHADER, UNKNOWN, WAV, LUA, OBJ, COLLADA
};

class FilePath {

    std::filesystem::file_time_type ftime;
    std::string path;
    static std::map<std::string, FileType> extensionMap;
    std::filesystem::file_time_type getFileWriteTime() const;

public:

    FilePath(std::string _path);
    FileType getType() const;
    std::string getExtension() const;
    std::string getName() const;
    std::string getPath() const;

    bool isFileChanged() const;
    void setFileChangeTime();

};

#endif