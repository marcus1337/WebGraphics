
#include "FileChecker.h"
#include <filesystem>
#include <limits>
#include <iostream>

FileChecker::FileChecker(std::string _filePath) : filePath(_filePath) {
    setUnchanged();
    std::cout << "FileChecker() " << filePath << "\n";
}

bool FileChecker::isChanged() {
    return mostRecentShaderEditTime != getMostRecentEditTime();
}

void FileChecker::setUnchanged() {
    mostRecentShaderEditTime = getMostRecentEditTime();
}

uint64_t FileChecker::getMostRecentEditTime() {
    std::filesystem::file_time_type ftime = std::filesystem::last_write_time(filePath);
    uint64_t timeSinceEpoch = std::max<uint64_t>(ftime.time_since_epoch().count(), std::numeric_limits<uint64_t>::min());
    return timeSinceEpoch;
}
