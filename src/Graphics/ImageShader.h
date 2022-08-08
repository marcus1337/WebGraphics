#include "Shader.h"


#ifndef IMAGESHADER_H
#define IMAGESHADER_H

class ImageShader : public Shader {

    virtual void setCustomUniforms() override;
    GLuint textureID;
    GLuint normalID;

    void setClippingUniforms();
    void setTextureUniforms();

public:

    ImageShader(GLuint _programID = 0);

    glm::vec3 singleColor;
    float effect = 0.0f;
    bool isNormalUsed = false;
    bool isSingleColor = false;
    bool grayscale = false;
    bool darken = false;
    glm::vec2 mouse = {0.0f,0.0f};
    glm::vec2 textureSize, textureCorner;

    void setTexture(GLuint _textureID);
    void setNormal(GLuint _textureID);
    void setTextureArea(glm::vec2 _textureSize, glm::vec2 _textureCorner);
};

#endif // !IMAGESHADER_H
