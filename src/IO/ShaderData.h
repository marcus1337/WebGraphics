#include <vector>
#include <string>

#ifndef SHADERDATA_H
#define SHADERDATA_H

struct ShaderCode {
    std::string glslCode;
    uint32_t shaderType;
};

class ShaderData{
public:
    std::vector<ShaderCode> shaders;
    std::string name;
};

#endif