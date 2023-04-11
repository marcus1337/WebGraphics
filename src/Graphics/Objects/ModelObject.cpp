#include "Graphics/Objects/ModelObject.h"
#include "IO/Files/IOContainer.h"

ModelObject::ModelObject(std::string objName) {
    vbo = 0;
    ebo = 0;
    modelData = IOContainer::getInstance().ioOBJ.getModelData(objName);
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    setBufferObjects();
}

void ModelObject::setVBO() {
    auto& interleavedData = modelData.interleavedData;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, interleavedData.size() * sizeof(interleavedData[0]), interleavedData.data(), GL_STATIC_DRAW);
}

void ModelObject::setEBO() {
    auto& vertexIndices = modelData.vertexIndices;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, vertexIndices.size() * sizeof(vertexIndices[0]), vertexIndices.data(), GL_STATIC_DRAW);
}

void ModelObject::setShaderBufferPointers() {
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(sizeof(float) * 3));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(sizeof(float) * 5));
    glEnableVertexAttribArray(2);
}

void ModelObject::setBufferObjects() {
    setVBO();
    setEBO();
    setShaderBufferPointers();
}

ModelObject::~ModelObject() {
    for (auto value : { ebo, vbo }) {
        if (value != 0)
            glDeleteBuffers(1, &value);
    }
}

void ModelObject::draw(Shader& shader) {
    glBindVertexArray(vao);
    shader.setUniforms();
    glDrawElements(GL_TRIANGLES, modelData.vertexIndices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
