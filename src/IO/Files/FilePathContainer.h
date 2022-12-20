#include <string>
#include <vector>
#include <iostream>
#include "FilePath.h"


#ifndef FILEPATHCONTAINER_H
#define FILEPATHCONTAINER_H

class FilePathContainer {

    std::vector<FilePath> filePaths;

public:

    void addFolderPath(std::string folderPath);
    std::vector<std::string> getFilePaths(FileType fileType);
    std::string getFilePath(std::string fileName, FileType fileType);


};

#endif
