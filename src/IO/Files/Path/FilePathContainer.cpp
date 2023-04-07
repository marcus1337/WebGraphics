#include "IO/Files/Path/FilePathContainer.h"
#include <filesystem>
#include <algorithm>
#include <ranges>

bool FilePathContainer::isFolderPath(std::string path) {
    std::filesystem::path filepath = std::string(path);
    return std::filesystem::is_directory(filepath.parent_path());
}

std::vector<std::string> FilePathContainer::getFilePathsInFolder(const std::string& folderPath) {
    std::vector<std::string> paths;
    std::filesystem::directory_iterator iterator(folderPath);
    for (const auto& entry : iterator) {
        if (entry.is_regular_file()) {
            paths.push_back(entry.path().string());
        }
    }
    return paths;
}

void FilePathContainer::addFolderPath(std::string folderPath) {
    if (!isFolderPath(folderPath)) {
        std::cerr << "Error, folder-path [" << folderPath << "] don't exists!\n";
        exit(EXIT_FAILURE);
    }
    for (const auto& path : getFilePathsInFolder(folderPath)) {
        if (!hasFilePath(path)) {
            std::cout << "Adding path [" << path << "] \n";
            filePaths.push_back(FilePath(path));
        }
    }
}

bool FilePathContainer::hasFilePath(const std::string& filePath) {
    for (auto& fp : filePaths) {
        if (fp.getPath() == filePath) {
            return true;
        }
    }
    return false;
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

std::vector<std::string> FilePathContainer::getFileNames(FileType fileType) {
    std::vector<std::string> paths;
    for (FilePath filePath : filePaths) {
        if (filePath.getType() == fileType) {
            paths.push_back(filePath.getName());
        }
    }
    return paths;
}

std::vector<std::string> FilePathContainer::getFileExtensions(FileType fileType) {
    std::vector<std::string> paths;
    for (FilePath filePath : filePaths) {
        if (filePath.getType() == fileType) {
            paths.push_back(filePath.getExtension());
        }
    }
    return paths;
}

std::string FilePathContainer::getFilePath(std::string fileName, FileType fileType) {
    for (FilePath filePath : filePaths) {
        if (filePath.getName() == fileName) {
            return filePath.getPath();
        }
    }
    return "";
}

std::vector<std::string> FilePathContainer::getDefaultFolderPaths() {
    std::string rootFolderPath = std::filesystem::current_path().string() + "//res//";
#ifdef EMSCRIPTEN
    rootFolderPath.insert(0, ".");
#endif
    std::vector<std::string> folderPaths;
    folderPaths.push_back(rootFolderPath);
    for (auto& entry : std::filesystem::recursive_directory_iterator(rootFolderPath)) {
        if (entry.is_directory()) {
            folderPaths.push_back(entry.path().string());
        }
    }
    return folderPaths;
}

void FilePathContainer::addDefaultFolderPaths() {
    for (const auto& folderPath : getDefaultFolderPaths()) {
        addFolderPath(folderPath);
    }
}

bool FilePathContainer::isFileUpdate(FileType fileType) {
    return std::any_of(filePaths.begin(), filePaths.end(), [fileType](const FilePath& fp) { return fp.getType() == fileType && fp.isFileChanged(); });
}

void FilePathContainer::setFilesUpdated(FileType fileType) {
    for (auto& fp : filePaths) {
        if (fp.getType() == fileType) {
            fp.setFileChangeTime();
        }
    }
}