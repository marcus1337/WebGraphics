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

    ImageShader(GLData& _glData);

    glm::vec3 defaultColor;
    bool image = true;
    bool grayscale = false;
    bool darken = false;
    float fade = 0.08;
    float thickness = 0.1f;
    glm::vec2 mouse = {0.0f,0.0f};
    glm::vec2 textureSize, textureCorner;

    void setTexture(GLuint _textureID);
    void setNormal(GLuint _textureID);
    void setTexture(std::string textureName);
    void setNormal(std::string normalName);

    void setTextureArea(glm::vec2 _textureSize, glm::vec2 _textureCorner);
};

#endif // !IMAGESHADER_H
