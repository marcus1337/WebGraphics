#include "IO/Files/Pose/Animation.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/compatibility.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <algorithm>
#include <iostream>

glm::mat4 Joint::getJointTransformInterpolation(float timeStamp) {
    for (int i = 0; i < frames.size() - 1; i++) {
        if (frames[i].timeStamp <= timeStamp && frames[i + 1].timeStamp >= timeStamp) {
            float t = (timeStamp - frames[i].timeStamp) / (frames[i + 1].timeStamp - frames[i].timeStamp);
            return interpolateMatrices(frames[i].getJointTransform(), frames[i + 1].getJointTransform(), t);
        }
    }
    return frames.back().getJointTransform();
}

glm::mat4 Joint::interpolateMatrices(const glm::mat4& matrix1, const glm::mat4& matrix2, float t) {
    glm::vec3 translation1 = matrix1[3];
    glm::vec3 translation2 = matrix2[3];
    glm::quat rotation1(matrix1);
    glm::quat rotation2(matrix2);

    glm::vec3 interpolatedTranslation = glm::lerp(translation1, translation2, t);
    glm::quat interpolatedRotation = glm::slerp(rotation1, rotation2, t);
    glm::mat4 interpolatedMatrix = glm::translate(glm::mat4(1.0f), interpolatedTranslation);
    interpolatedMatrix *= glm::toMat4(interpolatedRotation);
    return interpolatedMatrix;
}

void Animation::reorderVertexJointWeights(VertexJointWeights& data, const std::vector<unsigned int>& vertexIndices) {
    std::vector<int> newJointIndices(vertexIndices.size() * MAX_WEIGHTS);
    std::vector<float> newWeights(vertexIndices.size() * MAX_WEIGHTS);
    for (size_t i = 0; i < vertexIndices.size(); i++) {
        int vi = vertexIndices[i]* MAX_WEIGHTS;
        for (int j = 0; j < MAX_WEIGHTS; j++) {
            newJointIndices[i * MAX_WEIGHTS + j] = data.jointIndices[vi + j];
            newWeights[i * MAX_WEIGHTS + j] = data.weights[vi + j];
        }
    }
    data.jointIndices = newJointIndices;
    data.weights = newWeights;
}

Animation::Animation(Joint rootJoint, std::vector<glm::mat4> jointInvMatrices, const VertexJointWeights& vertexJointWeights) : rootJoint(rootJoint), jointInvMatrices(jointInvMatrices), vertexJointWeights(vertexJointWeights) {
    normalizeWeights();
}

void Animation::normalizeWeights() {
    auto& weights = vertexJointWeights.weights;
    for (int i = 0; i < weights.size() / MAX_WEIGHTS; i++) {
        float totalWeight = weights[i * MAX_WEIGHTS] + weights[i * MAX_WEIGHTS + 1] + weights[i * MAX_WEIGHTS + 2];
        weights[i * MAX_WEIGHTS] /= totalWeight;
        weights[i * MAX_WEIGHTS + 1] /= totalWeight;
        weights[i * MAX_WEIGHTS + 2] /= totalWeight;
    }
}

VertexJointWeights Animation::getVertexJointWeights(const std::vector<unsigned int>& vertexIndices) {
    VertexJointWeights dataCopy = vertexJointWeights;
    reorderVertexJointWeights(dataCopy, vertexIndices);
    return dataCopy;
}

std::vector<glm::mat4> Animation::getJointTransforms(float timeStamp) {
    std::map<int, glm::mat4> jointTransforms;
    addJointsToArray(rootJoint, timeStamp, jointTransforms);
    std::vector<glm::mat4> sortedTransforms;
    for (const auto& [id, transform] : jointTransforms)
        sortedTransforms.push_back(transform);
    return sortedTransforms;
}

void Animation::addJointsToArray(Joint& joint, float timeStamp, std::map<int, glm::mat4>& jointTransforms) {
    jointTransforms[joint.id] = jointInvMatrices[joint.id] * joint.getJointTransformInterpolation(timeStamp);
    if (joint.parentID != -1)
        jointTransforms[joint.id] = jointTransforms[joint.parentID] * jointTransforms[joint.id];
    for (auto& child : joint.children)
        addJointsToArray(child, timeStamp, jointTransforms);
}

std::vector<glm::mat4> Animation::getDefaultJointTransforms() {
    return jointInvMatrices;
}