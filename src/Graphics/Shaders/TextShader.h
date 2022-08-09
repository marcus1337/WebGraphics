#include "Shader.h"


#ifndef TEXTSHADER_H
#define TEXTSHADER_H

class TextShader : public Shader {
    virtual void setCustomUniforms() override;
public:
    TextShader(GLuint _programID = 0);
};

#endif // !TEXTSHADER_H
