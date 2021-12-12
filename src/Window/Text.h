
#include <GL/glew.h>
#include "glm/glm.hpp"
#include <map>
#include <string>
#include <tuple>

#ifndef FREETYPETEXT_H
#define FREETYPETEXT_H

class Text
{

protected:
    struct Character
    {
        unsigned int TextureID; // ID handle of the glyph texture
        glm::ivec2 Size;        // Size of glyph
        glm::ivec2 Bearing;     // Offset from baseline to left/top of glyph
        unsigned int Advance;   // Offset to advance to next glyph
    };

    std::map<char, Character> Characters;
    //unsigned int textVBO;

    GLuint programID = 0;

    glm::mat4 VP, V, P;
    GLuint vao, vbo;

    glm::mat4 getMVP();
    glm::vec3 midPosition, lastPosition;
    bool isMidPositionSet = false;
    bool isPositionSet = false;

    float SCR_WIDTH = 0;
    float SCR_HEIGHT = 0;
    float scaleValX = 0.0f;
    float scaleValY = 0.0f;

private:
    void setCharVertices(float& _x, char c);
    void bindAndDrawTextTextures();
    void setUniforms();

public:
    void setSourceWindowSize(float _SCR_WIDTH, float _SCR_HEIGHT);

    std::string text;
    glm::vec4 color = glm::vec4(1.0f,0.0f,1.0f,1.0f);

    void setText(std::string text);

    std::tuple<float, float> getTextWidthAndHeight(std::string _text);

    float totalWidth = 0;
    float totalHeight = 0;

    void setMidPosition(glm::vec3 _midPosition);
    void setScale(glm::vec3 _scale);
    void setPosition(glm::vec3 _position);

    void setViewProjectionMatrix(glm::mat4 &_VP, glm::mat4 &_V, glm::mat4 &_P);

    glm::vec3 cameraPosition;
    glm::vec3 position, scale;
    glm::vec3 rotationAxis;
    float rotation;

    void draw();
    int loadGlyphs(GLuint _programID, std::string &fontPath);
    void initVBO();

    ~Text();
    Text();
};

#endif
