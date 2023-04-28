#ifndef IO_POSE_H
#define IO_POSE_H
#include <string>
#include <vector>
#include <map>
#include <glm/glm.hpp>
#include "IO/Files/Pose/tinyxml2.h"
#include "Animation.h"
#include <memory>

class IOPose {
    std::map<std::string, std::shared_ptr<Animation>> animations;

    std::vector<float> parseFloatArray(const char* str);
    std::vector<int> parseIntArray(const char* str);
    std::vector<std::string> parseStrArray(const char* str);
    std::vector<glm::mat4> parseMatrixArray(const char* str);

    std::vector<glm::mat4> getJointInvMatrices(tinyxml2::XMLDocument& doc);
    tinyxml2::XMLElement* getInput(tinyxml2::XMLElement* parent, const char* semantic);
    tinyxml2::XMLElement* getSource(tinyxml2::XMLElement* input);
    std::string getElementValues(tinyxml2::XMLElement* parent, const std::string& semantic, const std::string& element);
    tinyxml2::XMLElement* getVertexWeightsElement(tinyxml2::XMLDocument& doc);
    tinyxml2::XMLElement* getRootNodeElement(tinyxml2::XMLDocument& doc);
    tinyxml2::XMLElement* getNodeElement(tinyxml2::XMLDocument& doc, tinyxml2::XMLElement* jointElement, const std::string& parentJointName);
    std::vector<tinyxml2::XMLElement*> getChildElements(tinyxml2::XMLElement* parentElement);
    std::vector<std::string> getChildJointNames(tinyxml2::XMLDocument& doc, const std::string& parentJointName);

    std::vector<tinyxml2::XMLElement*> getAnimationElements(tinyxml2::XMLDocument& doc);
    tinyxml2::XMLElement* getAnimationElement(tinyxml2::XMLDocument& doc, const std::string jointName);

    Joint loadRootJoint(tinyxml2::XMLDocument& doc, tinyxml2::XMLElement* vDataXML);
    bool isChildJoint(tinyxml2::XMLDocument& doc, const std::string& parentName, const std::string& childName);
    std::vector<float> getKeyframeTimes(tinyxml2::XMLDocument& doc, const std::string jointName);
    std::vector<glm::mat4> getKeyframeBoneTransforms(tinyxml2::XMLDocument& doc, const std::string jointName);

    void loadAnimation(std::string path, std::string name);
public:
    void loadAnimations(std::vector<std::string> colladaFilePaths, std::vector<std::string> colladaNames);
    std::shared_ptr<Animation> getAnimation(std::string animationName);

};

#endif // !IO_POSE_H
