#include "IO/Files/Pose/IOPose.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <glm/gtx/string_cast.hpp>

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

void IOPose::loadAnimation(std::string path, std::string name) {
    tinyxml2::XMLDocument doc;
    doc.LoadFile(path.c_str());
    tinyxml2::XMLElement* vertex_weights = doc.FirstChildElement("COLLADA")->FirstChildElement("library_controllers")->FirstChildElement("controller")->FirstChildElement("skin")->FirstChildElement("vertex_weights");
    
    int count = vertex_weights->IntAttribute("count");
    auto vcountData = parseIntArray(vertex_weights->FirstChildElement("vcount")->GetText());
    auto vData = parseIntArray(vertex_weights->FirstChildElement("v")->GetText());
    std::vector<glm::mat4> jointInvMatrices = getJointInvMatrices(doc);    
    std::vector<std::string> jointNames = parseStrArray(getElementValues(vertex_weights, "JOINT", "Name_array").c_str());
    std::vector<float> weights = parseFloatArray(getElementValues(vertex_weights, "WEIGHT", "float_array").c_str());


}