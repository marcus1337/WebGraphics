
#include "Mesh.h"
#include "IO/IO.h"
#include "Utility/GLData.h"
#include "MatrixData.h"

#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/common.hpp>
#include <string>

#ifndef MODEL_H
#define MODEL_H

class Model{

    GLData::Program program = (GLData::Program)0;
    GLData::Texture texture = (GLData::Texture)0;
    Mesh mesh;
    glm::vec3 angles;

public:

    void setScale(float x, float y, float z);
    void setRotation(float x, float y, float z);

    bool useTexture = true;
    glm::mat4 scaleMat = glm::scale(glm::mat4(1.0f), glm::vec3(1.f, 1.f, 1.f));
    glm::quat orientation = glm::quat(1.f, 0.f, 0.f, 0.f);
    glm::mat4 translateMat = glm::translate(glm::mat4(1.0f), glm::vec3(0.f, 0.f, 0.f));
    std::string objFilename = "stall.obj";
    void init(IO& io);
    void draw(IO& io, MatrixData& matrixData);


};

#endif