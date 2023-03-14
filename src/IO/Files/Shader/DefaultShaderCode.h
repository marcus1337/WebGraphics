
#include <string>
#include <vector>
#include "ShaderCode.h"

#ifndef DEFAULTSHADERCODE_H
#define DEFAULTSHADERCODE_H

class DefaultShaderCode {
    ShaderCode getDefault2DVertexCode();

public:

    std::vector<ShaderCode> getImageCode();
    std::vector<ShaderCode> getRectangleCode();
    std::vector<ShaderCode> getTextCode();

};


#endif
