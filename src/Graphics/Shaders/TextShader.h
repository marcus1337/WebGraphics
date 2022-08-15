#include "Shader.h"


#ifndef TEXTSHADER_H
#define TEXTSHADER_H

class TextShader : public Shader {
    virtual void setCustomUniforms() override;
public:
    TextShader(GLData& _glData);
};

#endif // !TEXTSHADER_H
