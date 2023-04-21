#include "IO/Files/Pose/Animation.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/compatibility.hpp>
#include <glm/gtx/quaternion.hpp>

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

Animation::Animation(Joint rootJoint) : rootJoint(rootJoint), vertexJointWeights{} {

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
    jointTransforms[joint.id] = joint.getJointTransformInterpolation(timeStamp);
    for (auto& child : joint.children)
        addJointsToArray(child, timeStamp, jointTransforms);
}

void Animation::setVertexJointWeights(const std::vector<int>& vCountData, const std::vector<int>& vData, const std::vector<float>& weights) {
    vertexJointWeights.weights.clear();
    vertexJointWeights.jointIndices.clear();

}