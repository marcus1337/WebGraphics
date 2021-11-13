#include "IOShader.h"

#include <filesystem>
#include <fstream>

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <map>
#include <GL/glew.h>

IOShader::IOShader()
{
#ifdef EMSCRIPTEN
    binFolderPath = "./res/";
    shaderPath = binFolderPath + "shaders/";
#else
    binFolderPath = std::filesystem::current_path().string() + "//res//";
    shaderPath = binFolderPath + "shaders//";
#endif
}

std::string IOShader::getFileExtension(const std::string &fileName)
{
    std::size_t i = fileName.rfind('.', fileName.length());
    if (i != std::string::npos)
        return (fileName.substr(i, fileName.length() - i));
    return "";
}

bool IOShader::isShaderFile(const std::string &fileName)
{
    std::string extension = getFileExtension(fileName);
    return isVertexShaderExtension(extension) || isFragmentShaderExtension(extension);
}
bool IOShader::isFragmentShaderExtension(const std::string &extension)
{
    return extension == ".frag";
}
bool IOShader::isVertexShaderExtension(const std::string &extension)
{
    return extension == ".vert";
}
uint32_t IOShader::getShaderValue(const std::string &extension)
{
    if (isVertexShaderExtension(extension))
        return GL_VERTEX_SHADER;
    if (isFragmentShaderExtension(extension))
        return GL_FRAGMENT_SHADER;
    return 0;
}

std::vector<std::vector<std::string>> IOShader::getShaderFilenames()
{
    std::map<std::string, std::vector<std::string>> shaderGroups;
    std::vector<std::string> names;
    for (const auto &entry : std::filesystem::directory_iterator(shaderPath))
    {
        std::string filename = entry.path().filename();
        if (isShaderFile(filename))
        {
            std::string name = entry.path().stem().string();
            if (!shaderGroups.contains(name))
            {
                shaderGroups[name] = std::vector<std::string>();
            }
            shaderGroups[name].push_back(filename);
        }
    }

    std::vector<std::vector<std::string>> result;
    for (auto it = shaderGroups.begin(); it != shaderGroups.end(); ++it)
    {
        result.push_back(it->second);
    }
    return result;
}

std::tuple<std::string, uint32_t> IOShader::getShaderInfo(const std::string &fileName)
{
    std::string fileExtension = getFileExtension(fileName);
    std::string shaderCode = readShaderSource(fileName);
    uint32_t shaderType = getShaderValue(fileExtension);
    return std::make_tuple(shaderCode, shaderType);
}

std::string IOShader::readShaderSource(const std::string &fileName)
{
    std::string filePathAndName = shaderPath + fileName;
    std::ifstream file(filePathAndName);
    std::stringstream stream;
    stream << file.rdbuf();
    return stream.str();
}

std::vector<std::vector<std::tuple<std::string, uint32_t>>> IOShader::getShaderInfos(){
    std::vector<std::vector<std::tuple<std::string, uint32_t>>> infos;
    std::vector<std::vector<std::string>> shaderGroups = getShaderFilenames();
    for(const auto& group : shaderGroups){
        std::vector<std::tuple<std::string, uint32_t>> info;
        for(const std::string& fileName : group){
            info.push_back(getShaderInfo(fileName));
        }
        infos.push_back(info);
    }
    return infos;
}