#include "Window/Image.h"


Image::Image() : position(glm::vec3(0.f, 0.f, 0.f)), scale(glm::vec3(1.0f, 1.0f, 1.0f))
{
    rotation = glm::angleAxis( glm::radians(0.0f), glm::vec3(0.f, 0.f, 1.f) );
    textureSize = glm::vec2(1.0f, 1.0f);
    textureCorner = glm::vec2(0.0f, 0.0f);
    initVBO();
}

void Image::setPosition(glm::vec3 _position)
{
    position = glm::vec3(_position.x + scale.x / 2.0f, _position.y + scale.y / 2.0f, _position.z);
}

void Image::setMidPosition(glm::vec3 _position)
{
    position = _position;
}

void Image::setProgram(GLuint program)
{
    programID = program;
}

void Image::setTexture(GLuint texture)
{
    textureID = texture;
}

void Image::setNormal(GLuint texture)
{
   normalID = texture;
}

void Image::setViewProjectionMatrix(glm::mat4 &_VP, glm::mat4 &_V, glm::mat4 &_P)
{
    VP = _VP;
    V = _V;
    P = _P;
}

void Image::setTextureArea(glm::vec2 _textureSize, glm::vec2 _textureCorner)
{
    textureSize = _textureSize;
    textureCorner = _textureCorner;
}

Image::~Image()
{
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
}

void Image::initVBO()
{
    glGenVertexArrays(1, &vao);

    const float numReps = 1.0f;
    const float width = 0.5f;
    const float height = 0.5f;
    GLfloat vertices[] = {// format = x, y, z, u, v
                          -width, height, 0.0f, 0.0f, numReps, width, height, 0.0f, numReps, numReps,
                          width, -height, 0.0f, numReps, 0.0f, -width, -height, 0.0f, 0.0f, 0.0f};

    glBindVertexArray(vao);
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, nullptr);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void *)(sizeof(float) * 3));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glBindVertexArray(0);
}

glm::mat4 Image::getModel()
{
    glm::mat4 scaleMat = glm::scale(glm::mat4(1.0f), scale);
    glm::mat4 rotateMat = glm::toMat4(rotation);
    glm::mat4 translateMat = glm::translate(glm::mat4(1.0f), position);
    glm::mat4 modModel = translateMat * rotateMat * scaleMat;
    return modModel;
}

void Image::draw()
{
    setUniforms();
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    glBindVertexArray(0);
}

void Image::setUniforms()
{
    glBindVertexArray(vao);
    glUseProgram(programID);

    setMatrixUniforms();
    setClippingUniforms();
    setColorUniforms();
    setTextureUniforms();
}

void Image::setColorUniforms()
{
    glUniform1f(glGetUniformLocation(programID, "alpha"), alpha);
    glUniform1f(glGetUniformLocation(programID, "usingNormalMap"), isNormalUsed ? 1.0f : 0.0f);
}
void Image::setClippingUniforms()
{
    glUniform2fv(glGetUniformLocation(programID, "inTexCoord"), 1, &textureCorner[0]);
    glUniform2fv(glGetUniformLocation(programID, "textureSize"), 1, &textureSize[0]);
}

void Image::setMatrixUniforms()
{
    glm::mat4 M = getModel();
    glm::mat4 MVP = VP * M;
    glm::mat4 MV = V * M;
    glUniformMatrix4fv(glGetUniformLocation(programID, "MVP"), 1, GL_FALSE, &MVP[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(programID, "MV"), 1, GL_FALSE, &MV[0][0]);
}

void Image::setTextureUniforms()
{
    GLuint mTex1Handle0 = glGetUniformLocation(programID, "tex");
    glUniform1i(mTex1Handle0, 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);
    if (isNormalUsed)
    {
        GLuint mTex1Handle1 = glGetUniformLocation(programID, "normalMap");
        glUniform1i(mTex1Handle1, 1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, normalID);
    }
}