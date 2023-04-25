#include "IO/Files/Pose/Animation.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/compatibility.hpp>
#include <glm/gtx/quaternion.hpp>
#include <algorithm>

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

void Animation::reorderVertexJointWeights(VertexJointWeights& data, const std::vector<int>& vertexIndices) {
    std::vector<int> newJointIndices(vertexIndices.size());
    std::vector<float> newWeights(vertexIndices.size());
    for (size_t i = 0; i < vertexIndices.size(); i++) {
        newJointIndices[i] = data.jointIndices[vertexIndices[i]];
        newWeights[i] = data.weights[vertexIndices[i]];
    }
    data.jointIndices = newJointIndices;
    data.weights = newWeights;
}

Animation::Animation(Joint rootJoint, std::vector<glm::mat4> jointInvMatrices) : rootJoint(rootJoint), jointInvMatrices(jointInvMatrices), vertexJointWeights{} {

}

VertexJointWeights Animation::getVertexJointWeights(const std::vector<int>& vertexIndices) {
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
    vertexJointWeights.weights = std::vector<float>(vertexJointCount.size() * batchSize, 0);
    vertexJointWeights.jointIndices = std::vector<int>(vertexJointCount.size() * batchSize);
    int traversedWeightIndices = 0;
    for (int vi = 0; vi < vertexJointCount.size(); vi++) {
        int numJoints = vertexJointCount[vi];

        std::vector<std::pair<float, int>> weightIndexPairs(numJoints);
        for (int ji = 0; ji < numJoints; ji++) {
            int weightIndex = vertexJointWeightIndices[traversedWeightIndices + ji];
            float weight = weights[weightIndex];
            weightIndexPairs[ji] = std::make_pair(weight, weightIndex);
        }
        std::sort(weightIndexPairs.begin(), weightIndexPairs.end(), std::greater<>());

        for (int ji = 0; ji < numJoints && ji < batchSize; ji++) {
            vertexJointWeights.weights[vi * batchSize + ji] = weightIndexPairs[ji].first;
            vertexJointWeights.jointIndices[vi * batchSize + ji] = weightIndexPairs[ji].second;
        }

        traversedWeightIndices += numJoints;
    }
}

std::vector<glm::mat4> Animation::getDefaultJointTransforms() {
    return jointInvMatrices;
}