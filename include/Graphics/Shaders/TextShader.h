
#ifndef TEXTSHADER_H
#define TEXTSHADER_H
#include "Shader.h"

class TextShader : public Shader {
    virtual void setCustomUniforms() override;
public:
    TextShader();
};

#endif // !TEXTSHADER_H
