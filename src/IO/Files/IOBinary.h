#include "bitsery/adapter/stream.h"
#include <bitsery/adapter/buffer.h>
#include <bitsery/bitsery.h>
#include <bitsery/traits/array.h>
#include <bitsery/traits/vector.h>
#include <array>
#include <vector>
#include <string>
#include "FolderPaths.h"
#include <filesystem>
#include <fstream>
#include <iostream>

#ifndef IOBINARY_H
#define IOBINARY_H

template<class T>
class IOBinary {

    std::string getFilePath(std::string fileName) {
        std::string folderPath = FolderPaths::getSavesPath();
        std::string filePath = folderPath + fileName + ".bin";
        return filePath;
    }

public:

    void saveFile(T& t, std::string fileName) {
        std::string filePath = getFilePath(fileName);
        std::fstream fileStream{ filePath, std::fstream::binary | std::fstream::trunc | std::fstream::out };
        if (!fileStream.is_open())
        {
            std::cout << "Cannot open <" << filePath << "> for writing.\n";
            return;
        }
        bitsery::Serializer<bitsery::OutputBufferedStreamAdapter> serializer{fileStream};
        serializer.object(t);
        serializer.adapter().flush();
        fileStream.close();
    }

    void loadFile(T& t, std::string fileName) {
        std::string filePath = getFilePath(fileName);
        if (!std::filesystem::exists(filePath))
            return;
        std::fstream fileStream{ filePath, std::fstream::binary | std::fstream::in };
        if (!fileStream.is_open()) {
            std::cout << "Couldn't load file <" << filePath << ">.\n";
            return;
        }
        auto loadStatus = bitsery::quickDeserialization<bitsery::InputStreamAdapter>(fileStream, t);
        if (!(loadStatus.first == bitsery::ReaderError::NoError && loadStatus.second))
            std::cout << "Error when loading <" << filePath << ">\n";
    }

};

#endif // !IOBINARY_H
