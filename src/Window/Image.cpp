#include "Window/Image.h"


Image::Image()
{
    vao = 0;
    vbo = 0;
    initVBO();
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


void Image::draw(ImageUniform* imageUniform)
{
    glBindVertexArray(vao);
    imageUniform->setUniforms();
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    glBindVertexArray(0);
}