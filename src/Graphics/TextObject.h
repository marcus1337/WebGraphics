
#include <GL/glew.h>
#include "glm/glm.hpp"
#include <map>
#include <string>
#include <tuple>

#include "GlyphTextureCreator.h"

#ifndef TEXTOBJECT_H
#define TEXTOBJECT_H

class TextObject
{

protected:
    GlyphTextureCreator glyphTextureCreator;
    glm::mat4 VP, V, P;
    GLuint vao, vbo;
    glm::mat4 getMVP();

private:
    void setCharVertices(float& _x, Character ch);
    void bindAndDrawTextTextures();
    void setUniforms();
    void initVBO();
    std::string font;

public:
    void setFont(std::string _font);
    void setText(std::string text);
    std::tuple<float, float> getTextWidthAndHeight(std::string _text);
    void setScale(glm::vec3 _scale);
    void setPosition(glm::vec3 _position);
    void setViewProjectionMatrix(glm::mat4& _VP, glm::mat4& _V, glm::mat4& _P);
    void draw();
    void setTextPixelHeight(unsigned int pixelHeight);
    ~TextObject();
    TextObject();

    std::string text;
    glm::vec4 color = glm::vec4(1.0f, 0.0f, 1.0f, 1.0f);
    glm::vec3 position, scale;
    float rotation;
    GLuint programID = 0;
};

#endif
