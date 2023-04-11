#include "Graphics/Objects/ModelObject.h"


ModelObject::ModelObject(std::string objName) {
    positionVbo = 0;
    texCoordVbo = 0;
    normalVbo = 0;
    indexBuffer = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    setModelData();
    //setBufferObjects();
}

void ModelObject::setModelData() {
    //ioOBJ.getPositions(objName);
}

void ModelObject::setBufferObjects() {
    glGenBuffers(1, &positionVbo);
    glBindBuffer(GL_ARRAY_BUFFER, positionVbo);
    glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(glm::vec3), &positions[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &texCoordVbo);
    glBindBuffer(GL_ARRAY_BUFFER, texCoordVbo);
    glBufferData(GL_ARRAY_BUFFER, texCoords.size() * sizeof(glm::vec2), &texCoords[0], GL_STATIC_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(1);

    glGenBuffers(1, &normalVbo);
    glBindBuffer(GL_ARRAY_BUFFER, normalVbo);
    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(2);

    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, vertexIndices.size() * sizeof(unsigned int), &vertexIndices[0], GL_STATIC_DRAW);
}

ModelObject::~ModelObject() {
    for (auto value : { positionVbo, texCoordVbo, normalVbo, indexBuffer }) {
        if (value != 0)
            glDeleteBuffers(1, &value);
    }
}

void ModelObject::draw(Shader& shader) {

}
