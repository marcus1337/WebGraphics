#include "IO/Files/OBJ/ModelData.h"


void ModelData::setInterleavedData() {
    if (vertexIndices.size() != normalIndices.size() || normalIndices.size() != texCoordIndices.size()) {
        std::cerr << "ModelData::setInterleavedIndices(): Different buffer sizes!\n";
        return;
    }
   
    interleavedData.clear();
    interleavedData.reserve(vertexIndices.size() * 8); // 8 floats per vertex: 3 position, 2 texCoord, 3 normal

    for (int i = 0; i < vertexIndices.size(); i++) {
        auto vertice = positions[vertexIndices[i]];
        auto texCoord = texCoords[texCoordIndices[i]];
        auto normal = normals[normalIndices[i]];
        interleavedData.push_back(vertice.x);
        interleavedData.push_back(vertice.y);
        interleavedData.push_back(vertice.z);

        interleavedData.push_back(texCoord.x);
        interleavedData.push_back(texCoord.y);

        interleavedData.push_back(normal.x);
        interleavedData.push_back(normal.y);
        interleavedData.push_back(normal.z);
    }
}