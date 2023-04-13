#include "IO/Files/OBJ/ModelData.h"


void ModelData::setInterleavedData() {   
    interleavedData.clear();
    //interleavedData.reserve(vertexIndices.size() * 8); // 8 floats per vertex: 3 position, 2 texCoord, 3 normal

    if (texCoords.empty())
        texCoords = std::vector<glm::vec2>(positions.size(), { 0,0 });
    if(normals.empty())
        normals = std::vector<glm::vec3>(positions.size(), { 0,0,0 });

    for (int i = 0; i < vertexIndices.size(); i++) {
        auto vertice = positions[i];
        glm::vec2 texCoord = texCoords[i];
        glm::vec3 normal = normals[i];

        interleavedData.push_back(vertice.z);
        interleavedData.push_back(vertice.y);
        interleavedData.push_back(vertice.x);

        interleavedData.push_back(normal.x);
        interleavedData.push_back(normal.y);
        interleavedData.push_back(normal.z);

        interleavedData.push_back(texCoord.x);
        interleavedData.push_back(texCoord.y);
    }
}