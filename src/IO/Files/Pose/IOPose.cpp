#include "IO/Files/Pose/IOPose.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <glm/gtx/string_cast.hpp>
#include <functional>

void IOPose::loadAnimations(std::vector<std::string> colladaFilePaths, std::vector<std::string> colladaNames) {
    std::cout << "Loading animations. Num Collada files: " << colladaFilePaths.size() << "\n";
    for (int i = 0; i < colladaFilePaths.size(); i++) {
        loadAnimation(colladaFilePaths[i], colladaNames[i]);
    }
}

std::vector<float> IOPose::parseFloatArray(const char* str) {
    std::vector<float> result;
    std::stringstream ss(str);
    float value;
    while (ss >> value) {
        result.push_back(value);
    }
    return result;
}

std::vector<int> IOPose::parseIntArray(const char* str) {
    std::vector<int> result;
    std::stringstream ss(str);
    int value;
    while (ss >> value) {
        result.push_back(value);
    }
    return result;
}

std::vector<std::string> IOPose::parseStrArray(const char* str) {
    std::vector<std::string> result;
    std::stringstream ss(str);
    std::string value;
    while (ss >> value) {
        result.push_back(value);
    }
    return result;
}

std::vector<glm::mat4> IOPose::parseMatrixArray(const char* str) {
    std::vector<glm::mat4> result;
    std::vector<float> floats = parseFloatArray(str);
    int numMatrices = floats.size() / 16;
    for (int i = 0; i < numMatrices; i++) {
        glm::mat4 mat;
        for (int j = 0; j < 16; j++) {
            mat[j / 4][j % 4] = floats[i * 16 + j];
        }
        result.push_back(mat);
    }
    return result;
}

std::vector<glm::mat4> IOPose::getJointInvMatrices(tinyxml2::XMLDocument& doc) {
    tinyxml2::XMLElement* joints = doc.FirstChildElement("COLLADA")->FirstChildElement("library_controllers")->FirstChildElement("controller")->FirstChildElement("skin")->FirstChildElement("joints");
    std::string matrixValues = getElementValues(joints, "INV_BIND_MATRIX", "float_array");
    return parseMatrixArray(matrixValues.c_str());
}

tinyxml2::XMLElement* IOPose::getInput(tinyxml2::XMLElement* parent, const char* semantic) {
    for (tinyxml2::XMLElement* input = parent->FirstChildElement("input"); input != nullptr; input = input->NextSiblingElement("input")) {
        const char* inputSemantic = input->Attribute("semantic");
        if (std::strcmp(semantic, inputSemantic) == 0) {
            return input;
        }
    }
    return nullptr;
}

tinyxml2::XMLElement* IOPose::getSource(tinyxml2::XMLElement* input) {
    const char* sourceId = input->Attribute("source");
    tinyxml2::XMLElement* source = input->Parent()->Parent()->FirstChildElement("source");
    while (source != nullptr) {
        const char* id = source->Attribute("id");
        if (id != nullptr && std::strcmp(sourceId + 1, id) == 0) {
            return source;
        }
        source = source->NextSiblingElement("source");
    }
    return nullptr;
}

std::string IOPose::getElementValues(tinyxml2::XMLElement* parent, const std::string& semantic, const std::string& element) {
    return getSource(getInput(parent, semantic.c_str()))->FirstChildElement(element.c_str())->GetText();
}

tinyxml2::XMLElement* IOPose::getVertexWeightsElement(tinyxml2::XMLDocument& doc) {
    return doc.FirstChildElement("COLLADA")->FirstChildElement("library_controllers")->FirstChildElement("controller")->FirstChildElement("skin")->FirstChildElement("vertex_weights");
}

tinyxml2::XMLElement* IOPose::getRootNodeElement(tinyxml2::XMLDocument& doc) {
    tinyxml2::XMLElement* node = doc.FirstChildElement("COLLADA")->FirstChildElement("library_visual_scenes")->FirstChildElement("visual_scene")->FirstChildElement("node");
    while (node != nullptr) {
        tinyxml2::XMLElement* childNode = node->FirstChildElement("node");
        if (childNode != nullptr) {
            const char* type = childNode->Attribute("type");
            if (type != nullptr && std::strcmp(type, "JOINT") == 0) {
                return childNode;
            }
        }
        node = node->NextSiblingElement("node");
    }
    return nullptr;
}

std::vector<tinyxml2::XMLElement*> IOPose::getChildElements(tinyxml2::XMLElement* parentElement) {
    std::vector<tinyxml2::XMLElement*> elements;
    tinyxml2::XMLElement* child = parentElement->FirstChildElement();
    while (child != nullptr) {
        elements.push_back(child);
        child = child->NextSiblingElement();
    }
    return elements;
}

tinyxml2::XMLElement* IOPose::getNodeElement(tinyxml2::XMLDocument& doc, tinyxml2::XMLElement* jointElement, const std::string& parentJointName) {
    if (jointElement == nullptr)
        return nullptr;
    const char* jointName = jointElement->Attribute("name");
    if (jointName != nullptr && parentJointName == jointName)
        return jointElement;
    for (tinyxml2::XMLElement* child : getChildElements(jointElement)) {
        tinyxml2::XMLElement* result = getNodeElement(doc, child, parentJointName);
        if (result != nullptr)
            return result;
    }
    return nullptr;
}

std::vector<std::string> IOPose::getChildJointNames(tinyxml2::XMLDocument& doc, const std::string& parentJointName) {
    std::vector<std::string> names;
    tinyxml2::XMLElement* root = getRootNodeElement(doc);
    tinyxml2::XMLElement* parent = getNodeElement(doc, root, parentJointName);
    if (parent == nullptr)
        return names;
    for (tinyxml2::XMLElement* child : getChildElements(parent)) {
        const char* childName = child->Attribute("name");
        if (childName != nullptr)
            names.push_back(childName);
    }
    return names;
}

std::vector<tinyxml2::XMLElement*> IOPose::getAnimationElements(tinyxml2::XMLDocument& doc) {
    std::vector<tinyxml2::XMLElement*> elements;
    tinyxml2::XMLElement* element = doc.FirstChildElement("COLLADA")->FirstChildElement("library_animations")->FirstChildElement("animation");
    while (element != nullptr) {
        elements.push_back(element);
        element = element->NextSiblingElement("animation");
    }
    return elements;
}

tinyxml2::XMLElement* IOPose::getAnimationElement(tinyxml2::XMLDocument& doc, const std::string jointName) {
    std::string targetName = jointName + "/transform";
    for (tinyxml2::XMLElement* element : getAnimationElements(doc)) {
        const char* target = element->FirstChildElement("channel")->Attribute("target");
        if (target == targetName)
            return element;
    }
    return nullptr;
}

std::vector<float> IOPose::getKeyframeTimes(tinyxml2::XMLDocument& doc, const std::string jointName) {
    std::vector<float> times;
    tinyxml2::XMLElement* animElement = getAnimationElement(doc, jointName);
    if (animElement != nullptr) {
        tinyxml2::XMLElement* inputElement = animElement->FirstChildElement("source")->FirstChildElement("float_array");
        if (inputElement != nullptr) {
            const char* inputStr = inputElement->GetText();
            times = parseFloatArray(inputStr);
        }
    }
    return times;
}

std::vector<glm::mat4> IOPose::getKeyframeBoneTransforms(tinyxml2::XMLDocument& doc, const std::string jointName) {
    std::vector<glm::mat4> transforms;
    tinyxml2::XMLElement* animElement = getAnimationElement(doc, jointName);
    if (animElement != nullptr) {
        tinyxml2::XMLElement* outputElement = animElement->FirstChildElement("source")->NextSiblingElement("source")->FirstChildElement("float_array");
        if (outputElement != nullptr) {
            const char* outputStr = outputElement->GetText();
            return parseMatrixArray(outputStr);
        }
    }
    return transforms;
}

void IOPose::loadAnimation(std::string path, std::string name) {
    tinyxml2::XMLDocument doc;
    doc.LoadFile(path.c_str());

    auto vDataXML = getVertexWeightsElement(doc);
    auto vCountData = parseIntArray(vDataXML->FirstChildElement("vcount")->GetText());
    auto vData = parseIntArray(vDataXML->FirstChildElement("v")->GetText());
    std::vector<float> weights = parseFloatArray(getElementValues(vDataXML, "WEIGHT", "float_array").c_str());

    Animation animation(loadRootJoint(doc, vDataXML), getJointInvMatrices(doc));
    animation.setVertexJointWeights(vCountData, vData, weights);
    animations.emplace(name, animation);
}

Animation IOPose::getAnimation(std::string animationName) {
    return animations.at(animationName);
}

bool IOPose::isChildJoint(tinyxml2::XMLDocument& doc, const std::string& parentName, const std::string& childName) {
    for (const auto& name : getChildJointNames(doc, parentName))
        if (name == childName)
            return true;
    return false;
}

Joint IOPose::loadRootJoint(tinyxml2::XMLDocument& doc, tinyxml2::XMLElement* vDataXML) {
    Joint rootJoint;
    std::vector<Joint> joints;
    std::vector<std::string> jointNames = parseStrArray(getElementValues(vDataXML, "JOINT", "Name_array").c_str());
    for (int i = 0; i < jointNames.size(); i++) {
        Joint joint;
        joint.id = i;
        joint.name = jointNames[i];
        auto frameTimes = getKeyframeTimes(doc, jointNames[i]);
        auto frameTransforms = getKeyframeBoneTransforms(doc, jointNames[i]);
        for (int j = 0; j < frameTimes.size(); j++) {
            joint.frames.push_back(KeyFrame{ frameTimes[j], frameTransforms[j] });
        }
        joints.push_back(joint);
    }

    std::function<void(Joint&)> addChildJointsRecursive = [&](Joint& parentJoint) {
        for (auto& childJoint : joints) {
            if (childJoint.id == parentJoint.id || childJoint.id == 0)
                continue;
            if (isChildJoint(doc, parentJoint.name, childJoint.name)) {
                childJoint.parentID = parentJoint.id;
                parentJoint.children.push_back(childJoint);
                addChildJointsRecursive(parentJoint.children.back());
            }
        }
    };

    addChildJointsRecursive(rootJoint);

    return rootJoint;
}