#include "ImageUniform.h"

#ifndef POSTIMAGE_UNIFORM_H
#define POSTIMAGE_UNIFORM_H

class PostImageUniform : public ImageUniform{

protected:
    virtual void setCustomUniforms();

public:
    using ImageUniform::ImageUniform;
    float blur = 1.0f;

};

#endif