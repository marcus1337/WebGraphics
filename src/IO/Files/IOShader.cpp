#include "IOShader.h"

#include <filesystem>
#include <fstream>

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <map>
#include <GL/glew.h>

#include "FolderPaths.h"

IOShader::IOShader()
{

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

std::vector<std::string> IOShader::getShaderFilePaths() {
    std::vector<std::string> paths;
    for (const auto& entry : std::filesystem::directory_iterator(FolderPaths::getShaderPath()))
        paths.push_back(entry.path().string());
    return paths;
}

std::vector<std::vector<std::string>> IOShader::getShaderFilenames()
{
    std::map<std::string, std::vector<std::string>> shaderGroups;
    std::vector<std::string> names;
    for (const auto &entry : std::filesystem::directory_iterator(FolderPaths::getShaderPath()))
    {
        const std::string filename = entry.path().filename().string();
        if (isShaderFile(filename))
        {
            std::string name = entry.path().stem().string();
            if (!shaderGroups.contains(name))
                shaderGroups[name] = std::vector<std::string>();
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

ShaderCode IOShader::getShaderCode(const std::string &fileName)
{
    ShaderCode shaderCode;
    std::string fileExtension = getFileExtension(fileName);
    shaderCode.glslCode = readShaderSource(fileName);
    shaderCode.shaderType = getShaderValue(fileExtension);
    return shaderCode;
}

std::string IOShader::readShaderSource(const std::string &fileName)
{
    std::string filePathAndName = FolderPaths::getShaderPath() + fileName;
    std::ifstream file(filePathAndName);
    std::stringstream stream;
    stream << file.rdbuf();
    return stream.str();
}

void IOShader::removeExtension(std::string &fileName)
{
    std::string tmpExtension = getFileExtension(fileName);
    fileName.erase(fileName.find(tmpExtension), tmpExtension.size());
}

std::vector<ShaderData> IOShader::getShaderData()
{
    std::vector<ShaderData> infos;
    std::vector<std::vector<std::string>> shaderGroups = getShaderFilenames();
    for (const auto &group : shaderGroups)
    {
        ShaderData shaderData;
        shaderData.name = group[0];
        removeExtension(shaderData.name);

        for (const std::string &fileName : group)
        {
            shaderData.shaders.push_back(getShaderCode(fileName));
        }
        infos.push_back(shaderData);
    }
    return infos;
}