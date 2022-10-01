#include "Shader.h"


#ifndef TEXTSHADER_H
#define TEXTSHADER_H

class TextShader : public Shader {
    virtual void setCustomUniforms() override;
public:
    TextShader(ShaderPrograms& _shaderPrograms);
};

#endif // !TEXTSHADER_H
