#include "IO/Files/OBJ/ModelData.h"
#include <algorithm>
#include <map>
#include <unordered_map>
#include "glm/gtx/string_cast.hpp"

void ModelData::setInterleavedData() {   
    interleavedData.clear();
    interleavedIndices.clear();
    //interleavedData.reserve(vertexIndices.size() * 8); // 8 floats per vertex: 3 position, 2 texCoord, 3 normal

    std::unordered_map<std::string, int> uniqueVertices;
    for (int i = 0; i < vertexIndices.size(); i++) {
        auto vertex = positions[vertexIndices[i]];
        glm::vec2 texCoord{};
        glm::vec3 normal{};
        if (!texCoordIndices.empty())
            texCoord = texCoords[texCoordIndices[i]];
        if (!normalIndices.empty())
            normal = normals[normalIndices[i]];

        std::string key = glm::to_string(vertex) + glm::to_string(normal) + glm::to_string(texCoord);
        if (!uniqueVertices.contains(key)) {
            interleavedData.push_back(vertex.z);
            interleavedData.push_back(vertex.y);
            interleavedData.push_back(vertex.x);

            interleavedData.push_back(normal.x);
            interleavedData.push_back(normal.y);
            interleavedData.push_back(normal.z);

            interleavedData.push_back(texCoord.x);
            interleavedData.push_back(texCoord.y);

            int index = interleavedData.size() / 8 - 1;
            uniqueVertices[key] = index;
        }
        interleavedIndices.push_back(uniqueVertices[key]);
    }
}

