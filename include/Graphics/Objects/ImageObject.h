
#ifndef IMAGEOBJECT_H
#define IMAGEOBJECT_H
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "Graphics/Shaders/Shader.h"
#include "VertexObject.h"

class ImageObject : public VertexObject
{
public:

    ImageObject();
    ~ImageObject();
    virtual void draw(Shader& shader) override;
};

#endif