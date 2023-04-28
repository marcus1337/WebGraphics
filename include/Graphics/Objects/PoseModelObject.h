#ifndef POSE_MODEL_H
#define POSE_MODEL_H
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <vector>
#include <glm/gtx/quaternion.hpp>
#include <glm/common.hpp>
#include "glm/glm.hpp"
#include <vector>

#include "Graphics/Shaders/Shader.h"
#include "VertexObject.h"
#include "IO/Files/OBJ/ModelData.h"
#include "IO/Files/Pose/Animation.h"
#include <memory>

class PoseModelObject : public VertexObject {

    GLuint ebo;
    ModelData modelData;
    std::shared_ptr<Animation> animation;
    VertexJointWeights vertexJointWeights;

    GLuint jointIndicesVBO = 0;
    GLuint weightsVBO = 0;

    void setVBO();
    void setEBO();
    void setBufferObjects();
    void setShaderBufferPointers();

public:
    PoseModelObject(std::string objName, std::string daeName);
    ~PoseModelObject();
    virtual void draw(Shader& shader) override;
};

#endif // !POSE_MODEL_H
