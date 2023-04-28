#ifndef POSE_MESH_H
#define POSE_MESH_H
#include <glm/glm.hpp>
#include <string>
#include <Graphics/Graphics.h>
#include "Drawable.h"

class PoseMesh : public Drawable {
    ImageShader imageShader;
    std::string objName, daeName;
public:
    PoseMesh(const std::string& objName, const std::string& textureName, const std::string& daeName);
    void setTexture(const std::string& textureName);
    virtual void render() override;
};

#endif // !POSE_MESH_H
