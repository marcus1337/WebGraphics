#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "Graphics/Shaders/Shader.h"

#ifndef VERTEXOBJECT_H
#define VERTEXOBJECT_H

class VertexObject {
protected:
    GLuint vao, vbo;

public:
    VertexObject();
    virtual ~VertexObject();
    virtual void draw(Shader& shader) = 0;
};

#endif // !VERTEXOBJECT_H
