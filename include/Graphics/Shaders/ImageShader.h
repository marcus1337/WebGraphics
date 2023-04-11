
#ifndef IMAGESHADER_H
#define IMAGESHADER_H
#include "Shader.h"
#include "IO/Files/Texture/IOTexture.h"

class ImageShader : public Shader {

    IOTexture& iotexture;
    virtual void setCustomUniforms() override;
    GLuint texture;
    void setTextureUniforms();

public:

    ImageShader();
    bool grayscale = false;
    void setTexture(std::string textureName);
    void setTexture(GLuint _texture);

};

#endif // !IMAGESHADER_H
