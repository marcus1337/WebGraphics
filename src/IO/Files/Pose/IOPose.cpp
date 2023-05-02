#include "IO/Files/Pose/IOPose.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <glm/gtx/string_cast.hpp>
#include <functional>
#include <string_view>
#include <cstring>


void IOPose::loadAnimations(std::vector<std::string> colladaFilePaths, std::vector<std::string> colladaNames) {
    std::cout << "Loading animations. Num Collada files: " << colladaFilePaths.size() << "\n";
    for (int i = 0; i < colladaFilePaths.size(); i++) {
        loadAnimation(colladaFilePaths[i], colladaNames[i]);
    }
}

VertexJointWeights IOPose::getVertexJointWeights() {
    VertexJointWeights data;
    /*tinygltf::Mesh& mesh = model.meshes.front();
    for (tinygltf::Primitive& primitive : mesh.primitives) {
        tinygltf::Accessor& jointsAccessor = model.accessors[primitive.attributes["JOINTS_0"]];
        tinygltf::Accessor& weightsAccessor = model.accessors[primitive.attributes["WEIGHTS_0"]];
        const int MAX_WEIGHTS = Animation::MAX_WEIGHTS;
    }*/
    return data;
}

Joint IOPose::getRootJoint() {
    Joint root;


    return root;
}

void IOPose::populateJoint(Joint& joint, const tinygltf::Node& node, const std::vector<tinygltf::Node>& nodes) {

}

std::vector<glm::mat4> IOPose::getInvBindMatrices() {

    auto& skin = tinyModel.getSkin();
    auto& model = tinyModel.getModel();
    tinygltf::Accessor& inverseBindMatricesAccessor = tinyModel.getAccessor(skin.inverseBindMatrices);
    int bufferViewIndex = inverseBindMatricesAccessor.bufferView;
    const tinygltf::BufferView& bufferView = model.bufferViews[bufferViewIndex];
    const tinygltf::Buffer& buffer = model.buffers[bufferView.buffer];
    const void* bufferData = buffer.data.data() + bufferView.byteOffset;

    std::vector<glm::mat4> inverseBindMatrices;
    for (int jointIndex : skin.joints) {
        const int matrixSize = sizeof(float) * 16;
        const void* matrixData = static_cast<const uint8_t*>(bufferData) + jointIndex * matrixSize;
        inverseBindMatrices.push_back(*reinterpret_cast<const glm::mat4*>(matrixData));
    }
    return inverseBindMatrices;
}

void IOPose::loadAnimation(const std::string& path, const std::string& name) {
    if (!tinyModel.load(path))
        return;

    VertexJointWeights vertexJointWeights = getVertexJointWeights();
    Joint rootJoint = getRootJoint();
    auto invBindMatrices = getInvBindMatrices();

    std::cout << "LOADED ANIMATION " << name << "\n\n";
    std::cout << "vertexJointWeights " << vertexJointWeights.weights.size() << " - " << vertexJointWeights.jointIndices.size() << "\n";
    for (const auto& mat : invBindMatrices) {
        std::cout << glm::to_string(mat) << "\n";
    }
    std::cout << "\n\n";

    std::shared_ptr<Animation> animation = std::make_shared<Animation>(rootJoint, invBindMatrices, vertexJointWeights);
    animations.emplace(name, animation);
}

std::shared_ptr<Animation> IOPose::getAnimation(std::string animationName) {
    if (!animations.contains(animationName)) {
        std::cerr << "ERROR: IOPose::getAnimation() '" << animationName << "' not loaded!\n";
        exit(EXIT_FAILURE);
        return nullptr;
    }
    return animations.at(animationName);
}


