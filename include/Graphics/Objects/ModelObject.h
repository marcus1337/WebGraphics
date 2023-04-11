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

class ModelObject : public VertexObject {

    GLuint positionVbo, texCoordVbo, normalVbo, indexBuffer;
    std::vector<glm::vec3> positions;
    std::vector<glm::vec2> texCoords;
    std::vector<glm::vec3> normals;
    std::vector<unsigned int> vertexIndices, texCoordIndices, normalIndices;

    void setModelData();
    void setBufferObjects();

public:
    ModelObject(std::string objName);
    ~ModelObject();
    virtual void draw(Shader& shader) override;

};

#endif // !MODEL_OBJECT_H
