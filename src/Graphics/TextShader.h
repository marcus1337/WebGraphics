#include "Shader.h"


#ifndef TEXTSHADER_H
#define TEXTSHADER_H

class TextShader : public Shader {
    virtual void setCustomUniforms() override;
public:
    TextShader(GLuint _programID = 0);
    int textWidth = 0;
    int textHeight = 0;
};

#endif // !TEXTSHADER_H
