#ifndef IO_ANIMATION_H
#define IO_ANIMATION_H
#include <string>
#include <vector>
#include <map>
#include <glm/glm.hpp>
#include <tuple>

struct KeyFrame {
    float timeStamp;
    glm::mat4 jointTransform;
};

struct Joint {
    int id = -1;
    int parentID = -1;
    std::string name;
    std::vector<KeyFrame> frames;
    std::vector<Joint> children;
    glm::mat4 interpolateMatrices(const glm::mat4& matrix1, const glm::mat4& matrix2, float t);
    glm::mat4 getJointTransformInterpolation(float timeStamp);
};

struct VertexJointWeights {
    std::vector<int> jointIndices;
    std::vector<float> weights;
};

class Animation {
    Joint rootJoint;
    std::vector<glm::mat4> jointInvMatrices;
    VertexJointWeights vertexJointWeights;
    void addJointsToArray(Joint& joint, float timeStamp, std::map<int, glm::mat4>& jointTransforms);
    void reorderVertexJointWeights(VertexJointWeights& data, const std::vector<unsigned int>& vertexIndices);
    void setVertexJointWeights(const std::vector<int>& vCountData, const std::vector<int>& vData, const std::vector<float>& weights);
    void normalizeWeights();
public:
    Animation(Joint rootJoint, std::vector<glm::mat4> jointInvMatrices, const std::vector<int>& vCountData, const std::vector<int>& vData, const std::vector<float>& weights);
    VertexJointWeights getVertexJointWeights(const std::vector<unsigned int>& vertexIndices);
    std::vector<glm::mat4> getJointTransforms(float timeStamp);
    std::vector<glm::mat4> getDefaultJointTransforms();
};

#endif // !IO_ANIMATION_H