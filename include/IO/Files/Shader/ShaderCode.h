
#ifndef SHADERCODE_H
#define SHADERCODE_H
#include <string>
#include <vector>
#include <cstdint>

struct ShaderCode {
    std::string glslCode;
    uint32_t shaderType;
};

struct ShaderCodeSet {
    std::vector<ShaderCode> shaders;
    std::string name;
};
#endif