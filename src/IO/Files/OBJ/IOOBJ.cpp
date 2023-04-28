#include "IO/Files/OBJ/IOOBJ.h"
#include "IO/Files/OBJ/OBJLoader.h"

#include "glm/gtx/string_cast.hpp"

#include <algorithm>
#include <map>


void IOOBJ::loadModels(std::vector<std::string> modelFilePaths, std::vector<std::string> modelNames) {
    if (modelFilePaths.size() != modelNames.size()) {
        std::cerr << "ERROR: modelFilePaths.size() != modelNames.size()!\n";
        return;
    }
    for (int i = 0; i < modelFilePaths.size(); i++) {
        std::string path = modelFilePaths[i];
        std::string name = modelNames[i];
        loadModel(path, name);
    }
}

bool IOOBJ::loadModelData(const std::string& path, ModelData& data) {
    objl::Loader Loader;
    bool loadout = Loader.LoadFile(path);
    if (loadout) {
        for (int i = 0; i < Loader.LoadedMeshes.size() && i < 1; i++) //only loads one mesh per file
        {
            objl::Mesh curMesh = Loader.LoadedMeshes[i];

            std::map<std::string, unsigned int> uniqueVertices, uniqueNormals, uniqueTexCoords;

            for (int j = 0; j < curMesh.Vertices.size(); j++)
            {
                glm::vec3 vertex = { curMesh.Vertices[j].Position.X, curMesh.Vertices[j].Position.Y, curMesh.Vertices[j].Position.Z };
                glm::vec3 normal = { curMesh.Vertices[j].Normal.X, curMesh.Vertices[j].Normal.Y, curMesh.Vertices[j].Normal.Z };
                glm::vec2 texCoord = { curMesh.Vertices[j].TextureCoordinate.X, curMesh.Vertices[j].TextureCoordinate.Y };

                std::string vertexKey = glm::to_string(vertex);
                if (!uniqueVertices.contains(vertexKey)) {
                    data.positions.push_back(vertex);
                    uniqueVertices[vertexKey] = uniqueVertices.size();
                }
                data.vertexIndices.push_back(uniqueVertices[vertexKey]);

                std::string normalKey = glm::to_string(normal);
                if (!uniqueNormals.contains(normalKey)) {
                    data.normals.push_back(normal);
                    uniqueNormals[normalKey] = uniqueNormals.size();
                }
                data.normalIndices.push_back(uniqueNormals[normalKey]);

                std::string texCoordKey = glm::to_string(texCoord);
                if (!uniqueTexCoords.contains(texCoordKey)) {
                    data.texCoords.push_back(texCoord);
                    uniqueTexCoords[texCoordKey] = uniqueTexCoords.size();
                }
                data.texCoordIndices.push_back(uniqueTexCoords[texCoordKey]);
            }



        }
    }
    else {
        std::cerr << "IOOBJ::loadModel() failed, " << path << "!\n";
    }
    return loadout;
}

void IOOBJ::loadModel(std::string path, std::string name) {

    ModelData data;
    if (loadModelData(path, data)) {
        //TODO: optimize away duplicate vertices
        data.setInterleavedData();
        modelDataMap[name] = data;
    }
}


ModelData IOOBJ::getModelData(std::string name) {
    if (!modelDataMap.contains(name)) {
        std::cerr << "ERROR: Could not find modelData for " << name << "!\n";
        return ModelData();
    }
    return modelDataMap[name];
}

std::vector<std::string> IOOBJ::getModelNames() {
    std::vector<std::string> names;
    for (const auto& [key, value] : modelDataMap) {
        names.push_back(key);
    }
    return names;
}