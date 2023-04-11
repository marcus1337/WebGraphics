
#ifndef IMAGESHADER_H
#define IMAGESHADER_H
#include "Shader.h"
#include "IO/Files/Texture/IOTexture.h"

class ImageShader : public Shader {

    IOTexture& iotexture;
    virtual void setCustomUniforms() override;
    GLuint texture;

public:

    ImageShader();
    bool grayscale = false;

};

#endif // !IMAGESHADER_H
