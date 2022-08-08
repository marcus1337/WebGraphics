#include <glm/glm.hpp>
#include <string>
#include <Engine/Graphics.h>

#ifndef IMAGE_H
#define IMAGE_H

class Image {

protected:
    void addImageVariablesToShader(ImageShader& _shader, GLuint _textureID);
    void addHighlightedImageVariablesToShader(ImageShader& _shader, GLuint _textureID);

public:
    virtual void render(Graphics& _graphics);
    virtual ~Image();
    virtual Image* clone() const;

    int width = 100, height = 100;
    int x = 0, y = 0;
    std::string texture = "background1.png";
    float rotation = 180;
    glm::vec3 extraColor = glm::vec3(0.0f, 0.0f, 0.01f);
    glm::vec3 singleColor = glm::vec3(0.0f, 0.0f, 0.0f);
    float alpha = 1.0f;
    float effect = 0.0f;
    bool isHighlighted = false;
    int borderSize = 10;
    bool mirror = false;
    bool grayscale = false;
    bool darken = false;
    float mouseX = 0.0f;
    float mouseY = 0.0f;
};

#endif