#ifndef IO_ANIMATION_H
#define IO_ANIMATION_H
#include <string>
#include <vector>
#include <map>
#include <glm/glm.hpp>
#include <tuple>

struct KeyFrame {
    float timeStamp;
    std::vector<glm::mat4> jointTransforms;
};

struct Joint {
    std::vector<Joint> children;
    int id;
    glm::mat4 transform;
};

class Animation {
    std::vector<KeyFrame> keyFrames;
    Joint rootJoint;

    float getWrappedTime(float animationTime);
    std::pair<KeyFrame,KeyFrame> getInterpolatedFrames(float animationTime);
    glm::mat4 interpolateMatrices(const glm::mat4& matrix1, const glm::mat4& matrix2, float t);
public:
    Animation(std::vector<KeyFrame> keyFrames, Joint rootJoint);
    std::vector<glm::mat4> getJointTransforms(float animationTime);
};

#endif // !IO_ANIMATION_H
