#include "IO/Files/Pose/Animation.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/compatibility.hpp>
#include <glm/gtx/quaternion.hpp>

Animation::Animation(std::vector<KeyFrame> keyFrames, Joint rootJoint) : keyFrames(keyFrames), rootJoint(rootJoint) {

}

std::vector<glm::mat4> Animation::getJointTransforms(float animationTime) {
    animationTime = getWrappedTime(animationTime);
    auto frames = getInterpolatedFrames(animationTime);
    float interpolationFactor = (animationTime - frames.first.timeStamp) / (frames.second.timeStamp - frames.first.timeStamp);
    std::vector<glm::mat4> jointTransforms;
    for (int i = 0; i < frames.first.jointTransforms.size(); i++) {
        auto fromMatrix = frames.first.jointTransforms[i];
        auto toMatrix = frames.second.jointTransforms[i];
        jointTransforms.push_back(interpolateMatrices(fromMatrix, toMatrix, interpolationFactor));
    }
    return jointTransforms;
}

float Animation::getWrappedTime(float animationTime) {
    float maxTime = keyFrames.back().timeStamp;
    return fmodf(animationTime, maxTime);
}

std::pair<KeyFrame, KeyFrame> Animation::getInterpolatedFrames(float animationTime) {
    for (int i = 0; i < keyFrames.size(); i++) {
        if (keyFrames[i].timeStamp <= animationTime) {
            return std::make_pair(keyFrames[i], keyFrames[i + 1]);
        }
    }
    return std::make_pair(KeyFrame(), KeyFrame());
}

glm::mat4 interpolateMatrices(const glm::mat4& matrix1, const glm::mat4& matrix2, float t) {
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