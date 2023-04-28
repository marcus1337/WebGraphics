#include "IO/Files/Pose/Animation.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/compatibility.hpp>
#include <glm/gtx/quaternion.hpp>
#include <algorithm>
#include <iostream>

glm::mat4 Joint::getJointTransformInterpolation(float timeStamp) {
    for (int i = 0; i < frames.size() - 1; i++) {
        if (frames[i].timeStamp <= timeStamp && frames[i + 1].timeStamp >= timeStamp) {
            float t = (timeStamp - frames[i].timeStamp) / (frames[i + 1].timeStamp - frames[i].timeStamp);
            return interpolateMatrices(frames[i].jointTransform, frames[i + 1].jointTransform, t);
        }
    }
    return frames.back().jointTransform;
}

glm::mat4 Joint::interpolateMatrices(const glm::mat4& matrix1, const glm::mat4& matrix2, float t) {
    glm::vec3 translation1 = matrix1[3];
    glm::vec3 translation2 = matrix2[3];
    glm::vec3 interpolatedTranslation = glm::lerp(translation1, translation2, t);
    glm::quat rotation1(matrix1);
    glm::quat rotation2(matrix2);
    glm::quat interpolatedRotation = glm::slerp(rotation1, rotation2, t);
    glm::mat4 interpolatedMatrix = glm::translate(glm::mat4(1.0f), interpolatedTranslation);
    interpolatedMatrix *= glm::toMat4(interpolatedRotation);
    return interpolatedMatrix;
}

void Animation::reorderVertexJointWeights(VertexJointWeights& data, const std::vector<unsigned int>& vertexIndices) {
    //TODO: Remove this method or change it fundamentally to map 3 joints/weights per vertice
    std::vector<int> newJointIndices(vertexIndices.size(), 0);
    std::vector<float> newWeights(vertexIndices.size(), 0.f);
    if (vertexIndices.size() != data.jointIndices.size()) {
        std::cout << "WARNING Animation::reorderVertexJointWeights(): different array sizes, vertexIndices: " << vertexIndices.size() << " data.jointIndices: " << data.jointIndices.size() << "\n";
    }

    for (size_t i = 0; i < vertexIndices.size(); i++) {
        if (vertexIndices[i] < data.jointIndices.size() && vertexIndices[i] < data.weights.size()) {
            newJointIndices[i] = data.jointIndices[vertexIndices[i]];
            newWeights[i] = data.weights[vertexIndices[i]];
        }
    }
    data.jointIndices = newJointIndices;
    data.weights = newWeights;
}

Animation::Animation(Joint rootJoint, std::vector<glm::mat4> jointInvMatrices, const std::vector<int>& vertexJointCount, const std::vector<int>& vertexJointWeightIndices, const std::vector<float>& weights) : rootJoint(rootJoint), jointInvMatrices(jointInvMatrices), vertexJointWeights{} {
    setVertexJointWeights(vertexJointCount, vertexJointWeightIndices, weights);
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

void Animation::setVertexJointWeights(const std::vector<int>& vertexJointCount, const std::vector<int>& vertexJointWeightIndices, const std::vector<float>& weights) {
    const int batchSize = 3;
    std::cout << "Animation::setVertexJointWeights() vertexJointCount: " << vertexJointCount.size() << " vertexJointWeightIndices: " << vertexJointWeightIndices.size() << " weights: " << weights.size() << "\n";
    vertexJointWeights.weights.clear();
    vertexJointWeights.jointIndices.clear();

    int traversedWeightIndices = 0;
    for (const int numJoints : vertexJointCount) {
        std::vector<std::pair<float, int>> weightIndexPairs(std::max(numJoints, batchSize));
        for (int ji = 0; ji < numJoints; ji++) {
            int weightIndex = vertexJointWeightIndices[traversedWeightIndices + ji];
            float weight = weights[weightIndex];
            weightIndexPairs[ji] = std::make_pair(weight, weightIndex);
        }
        std::sort(weightIndexPairs.begin(), weightIndexPairs.end(), std::greater<>());

        for (int ji = 0; ji < batchSize; ji++) {
            vertexJointWeights.weights.push_back(weightIndexPairs[ji].first);
            vertexJointWeights.jointIndices.push_back(weightIndexPairs[ji].second);
        }
        traversedWeightIndices += numJoints;
    }
}

std::vector<glm::mat4> Animation::getDefaultJointTransforms() {
    return jointInvMatrices;
}