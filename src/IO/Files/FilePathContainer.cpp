#include "FilePathContainer.h"
#include <filesystem>



void FilePathContainer::addFolderPath(std::string folderPath) {
    std::filesystem::directory_iterator iterator(folderPath);
    for (const auto& entry : iterator) {
        if (entry.is_regular_file()) {
            filePaths.push_back(FilePath(entry.path().string()));
        }
    }
}

std::vector<std::string> FilePathContainer::getFilePaths(FileType fileType) {
    std::vector<std::string> paths;
    for (FilePath filePath : filePaths) {
        if (filePath.getType() == fileType) {
            paths.push_back(filePath.getPath());
        }
    }
    return paths;
}

std::string FilePathContainer::getFilePath(std::string fileName, FileType fileType) {
    for (FilePath filePath : filePaths) {
        if (filePath.getName() == fileName) {
            return filePath.getName();
        }
    }
    return "";
}


