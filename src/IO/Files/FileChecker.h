#include <string>

#ifndef FILECHECKER_H
#define FILECHECKER_H

class FileChecker {

    std::string filePath;
    uint64_t mostRecentShaderEditTime;
    uint64_t getMostRecentEditTime();

public:
    FileChecker(std::string _filePath);
    bool isChanged();
    void setUnchanged();
};

#endif