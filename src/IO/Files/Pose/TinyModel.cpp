#include "IO/Files/Pose/TinyModel.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <glm/gtx/string_cast.hpp>
#include <functional>
#include <string_view>
#include <cstring>

// Define these only in *one* .cc file.
#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
// #define TINYGLTF_NOEXCEPTION // optional. disable exception handling.
#include "IO/Files/Pose/tiny_gltf.h"

TinyModel::TinyModel() {

}

bool TinyModel::load(const std::string& path) {
    skinnedNodeIndex = -1;
    tinygltf::TinyGLTF loader;
    std::string err;
    std::string warn;

    bool ret = loader.LoadASCIIFromFile(&model, &err, &warn, path);
    if (!warn.empty()) {
        std::cout << "WARNING: " << warn << "\n";
    }
    if (!err.empty()) {
        std::cerr << "ERROR: " << err << "\n";
        return false;
    }
    if (!ret) {
        std::cerr << "ERROR: TinyModel::load() Failed to parse glTF '" << path << "'\n";
        return false;
    }

    for (size_t i = 0; i < model.nodes.size(); i++) {
        tinygltf::Node& node = model.nodes[i];
        if (node.skin >= 0) {
            skinnedNodeIndex = (int)i;
            break;
        }
    }
    if (skinnedNodeIndex < 0) {
        std::cout << "WARNING: No skinned node.\n";
    }

    return true;
}

tinygltf::Skin& TinyModel::getSkin() {
    tinygltf::Node& skinnedNode = model.nodes[skinnedNodeIndex];
    tinygltf::Skin& skin = model.skins[skinnedNode.skin];
    return skin;
}

tinygltf::Accessor& TinyModel::getAccessor(int index) {
    return model.accessors[index];
}

tinygltf::Model& TinyModel::getModel() {
    return model;
}

