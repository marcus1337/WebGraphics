#include "IO/Files/OBJ/ModelData.h"
#include <algorithm>
#include <map>
#include <unordered_map>

void ModelData::setInterleavedData() {   
    interleavedData.clear();
    interleavedIndices.clear();
    //interleavedData.reserve(vertexIndices.size() * 8); // 8 floats per vertex: 3 position, 2 texCoord, 3 normal

    std::unordered_map<std::string, int> uniqueVertices;
    for (int i = 0; i < vertexIndices.size(); i++) {
        auto vertice = positions[vertexIndices[i]];
        glm::vec2 texCoord{};
        glm::vec3 normal{};
        if (!texCoordIndices.empty())
            texCoord = texCoords[texCoordIndices[i]];
        if (!normalIndices.empty())
            normal = normals[normalIndices[i]];

        interleavedData.push_back(vertice.z);
        interleavedData.push_back(vertice.y);
        interleavedData.push_back(vertice.x);

        interleavedData.push_back(normal.x);
        interleavedData.push_back(normal.y);
        interleavedData.push_back(normal.z);

        interleavedData.push_back(texCoord.x);
        interleavedData.push_back(texCoord.y);

        interleavedIndices.push_back(i);
    }
}

