#ifndef IO_POSE_H
#define IO_POSE_H
#include <string>
#include <vector>
#include <map>
#include <glm/glm.hpp>
#include "Animation.h"
#include <memory>

#include "TinyModel.h"

class IOPose {
    std::map<std::string, std::shared_ptr<Animation>> animations;
    TinyModel tinyModel;

    void populateJoint(Joint& joint, const tinygltf::Node& node, const std::vector<tinygltf::Node>& nodes);
    std::vector<glm::mat4> getInvBindMatrices();
    Joint getRootJoint();
    VertexJointWeights getVertexJointWeights();
    void loadAnimation(const std::string& path, const std::string& name);
public:
    void loadAnimations(std::vector<std::string> colladaFilePaths, std::vector<std::string> colladaNames);
    std::shared_ptr<Animation> getAnimation(std::string animationName);

};

#endif // !IO_POSE_H
