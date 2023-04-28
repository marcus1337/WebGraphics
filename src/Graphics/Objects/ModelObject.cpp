#include "Graphics/Objects/ModelObject.h"
#include "IO/Files/IOContainer.h"

ModelObject::ModelObject(std::string objName) {
    vbo = 0;
    ebo = 0;
    modelData = IOContainer::getInstance().ioOBJ.getModelData(objName);
    std::cout << "ModelObject " << objName << " - Indices: " << modelData.vertexIndices.size() << " Positions: " << modelData.positions.size() << "\n";

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
    auto& interleavedIndices = modelData.interleavedIndices;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, interleavedIndices.size() * sizeof(interleavedIndices[0]), interleavedIndices.data(), GL_STATIC_DRAW);
}

void ModelObject::setShaderBufferPointers() {
    GLuint vertLoc = 0;
    GLuint normalLoc = 1;
    GLuint uvLoc = 2;

    glVertexAttribPointer(vertLoc, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, 0);
    glEnableVertexAttribArray(vertLoc);

    glVertexAttribPointer(normalLoc, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(sizeof(float) * 3)); 
    glEnableVertexAttribArray(normalLoc);

    glVertexAttribPointer(uvLoc, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(sizeof(float) * 6)); 
    glEnableVertexAttribArray(uvLoc);
}

void ModelObject::setBufferObjects() {
    setVBO();
    setEBO();
    setShaderBufferPointers();
}

ModelObject::~ModelObject() {
    for (auto value : { ebo }) {
        if (value != 0)
            glDeleteBuffers(1, &value);
    }
}

void ModelObject::draw(Shader& shader) {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);

    glBindVertexArray(vao);
    shader.setUniforms();
    
    glDrawElements(GL_TRIANGLES, modelData.interleavedIndices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    glDisable(GL_CULL_FACE);
}
