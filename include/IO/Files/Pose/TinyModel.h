#ifndef TINY_MODEL_H
#define TINY_MODEL_H
#include <string>
#include <vector>
#include <map>
#include <glm/glm.hpp>
#include "Animation.h"
#include <memory>
#include "tiny_gltf.h"

class TinyModel {
    tinygltf::Model model;
    int skinnedNodeIndex = -1;

public:
    TinyModel();
    bool load(const std::string& path);
    tinygltf::Skin& getSkin();
    tinygltf::Accessor& getAccessor(int index);
    tinygltf::Model& getModel();

};

#endif // !TINY_MODEL_H
