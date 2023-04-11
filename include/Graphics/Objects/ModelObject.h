#ifndef MODEL_OBJECT_H
#define MODEL_OBJECT_H
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

class ModelObject : public VertexObject {

    GLuint vbo, ebo;
    ModelData modelData;

    void setVBO();
    void setEBO();
    void setBufferObjects();
    void setShaderBufferPointers();

public:
    ModelObject(std::string objName);
    ~ModelObject();
    virtual void draw(Shader& shader) override;

};

#endif // !MODEL_OBJECT_H
