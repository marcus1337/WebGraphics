
#ifndef FILEPATHCONTAINER_H
#define FILEPATHCONTAINER_H
#include <string>
#include <vector>
#include <iostream>
#include "FilePath.h"

class FilePathContainer {

    std::vector<FilePath> filePaths;
    bool hasFilePath(const std::string& filePath);

    std::vector<std::string> getFilePathsInFolder(const std::string& folderPath);
    std::vector<std::string> getDefaultFolderPaths();
    bool isFolderPath(std::string path);

public:

    void addDefaultFolderPaths();
    void addFolderPath(std::string folderPath);
    std::vector<std::string> getFilePaths(FileType fileType);
    std::vector<std::string> getFileNames(FileType fileType);
    std::vector<std::string> getFileExtensions(FileType fileType);
    std::string getFilePath(std::string fileName, FileType fileType);
    
    bool isFileUpdate(FileType fileType);
    void setFilesUpdated(FileType fileType);


};

#endif
