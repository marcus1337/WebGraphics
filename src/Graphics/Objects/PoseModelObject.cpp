#include "Graphics/Objects/PoseModelObject.h"
#include "IO/Files/IOContainer.h"

PoseModelObject::PoseModelObject(std::string objName, std::string daeName) {
    ebo = 0;
    modelData = IOContainer::getInstance().ioOBJ.getModelData(objName);
    animation = IOContainer::getInstance().ioPose.getAnimation(daeName);
    vertexJointWeights = animation->getVertexJointWeights(modelData.vertexIndices);

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    setBufferObjects();
}

PoseModelObject::~PoseModelObject() {
    for (auto value : { ebo, jointIndicesVBO, weightsVBO }) {
        if (value != 0)
            glDeleteBuffers(1, &value);
    }
}

void PoseModelObject::setVBO() {
    auto& interleavedData = modelData.interleavedData;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, interleavedData.size() * sizeof(interleavedData[0]), interleavedData.data(), GL_STATIC_DRAW);
}

void PoseModelObject::setEBO() {
    auto& vertexIndices = modelData.vertexIndices;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, vertexIndices.size() * sizeof(vertexIndices[0]), vertexIndices.data(), GL_STATIC_DRAW);
}

void PoseModelObject::setShaderBufferPointers() {
    GLuint vertLoc = 0;
    GLuint normalLoc = 1;
    GLuint uvLoc = 2;
    GLuint jointLoc = 3;
    GLuint weightLoc = 4;

    unsigned int blockSize1 = sizeof(float) * 8;
    glVertexAttribPointer(vertLoc, 3, GL_FLOAT, GL_FALSE, blockSize1, 0);
    glEnableVertexAttribArray(vertLoc);
    glVertexAttribPointer(normalLoc, 3, GL_FLOAT, GL_FALSE, blockSize1, (void*)(sizeof(float) * 3));
    glEnableVertexAttribArray(normalLoc);
    glVertexAttribPointer(uvLoc, 2, GL_FLOAT, GL_FALSE, blockSize1, (void*)(sizeof(float) * 6));
    glEnableVertexAttribArray(uvLoc);


    glGenBuffers(1, &jointIndicesVBO);
    glBindBuffer(GL_ARRAY_BUFFER, jointIndicesVBO);
    auto& jointIndices = vertexJointWeights.jointIndices;
    glBufferData(GL_ARRAY_BUFFER, jointIndices.size() * sizeof(jointIndices[0]), jointIndices.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &weightsVBO);
    glBindBuffer(GL_ARRAY_BUFFER, weightsVBO);
    auto& weights = vertexJointWeights.weights;
    glBufferData(GL_ARRAY_BUFFER, weights.size() * sizeof(weights[0]), weights.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, jointIndicesVBO);
    glVertexAttribIPointer(jointLoc, 3, GL_INT, 3 * sizeof(int), (void*)0);
    glEnableVertexAttribArray(jointLoc);

    glBindBuffer(GL_ARRAY_BUFFER, weightsVBO);
    glVertexAttribPointer(weightLoc, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(weightLoc);
}

void PoseModelObject::setBufferObjects() {
    setVBO();
    setEBO();
    setShaderBufferPointers();
}

void PoseModelObject::draw(Shader& shader) {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);

    glBindVertexArray(vao);
    shader.setUniforms();
    auto matrices = animation->getDefaultJointTransforms();
    shader.setMatricesUniform("jointTransforms", matrices);

    glDrawElements(GL_TRIANGLES, modelData.vertexIndices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    glDisable(GL_CULL_FACE);
}
