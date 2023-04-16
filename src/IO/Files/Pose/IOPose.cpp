#include "IO/Files/Pose/IOPose.h"
#include "IO/Files/Pose/tinyxml2.h"
#include <iostream>

void IOPose::loadAnimations(std::vector<std::string> colladaFilePaths, std::vector<std::string> colladaNames) {
    std::cout << "Loading animations. Num Collada files: " << colladaFilePaths.size() << "\n";

    tinyxml2::XMLDocument doc;
    tinyxml2::XMLElement* root = nullptr;


}