#ifndef MESH_H
#define MESH_H
#include <glm/glm.hpp>
#include <string>
#include <Graphics/Graphics.h>
#include "Drawable.h"

class Mesh : public Drawable {
    ImageShader imageShader;
    std::string modelName;
public:
    Mesh(std::string modelName, std::string textureName);
    void setTexture(std::string textureName);
    virtual void render() override;
};

#endif // !MESH_H
