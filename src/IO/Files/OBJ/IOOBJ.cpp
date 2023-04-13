#include "IO/Files/OBJ/IOOBJ.h"
#include "IO/Files/OBJ/OBJLoader.h"

#include "glm/gtx/string_cast.hpp"

#include <algorithm>


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


void IOOBJ::loadModel(std::string path, std::string name) {

    objl::Loader Loader;
    bool loadout = Loader.LoadFile(path);
    ModelData data;

    if (loadout) {
        for (int i = 0; i < Loader.LoadedMeshes.size(); i++)
        {
            objl::Mesh curMesh = Loader.LoadedMeshes[i];
            for (int j = 0; j < curMesh.Vertices.size(); j++)
            {
                glm::vec3 vertice = { curMesh.Vertices[j].Position.X, curMesh.Vertices[j].Position.Y, curMesh.Vertices[j].Position.Z };
                glm::vec3 normal = { curMesh.Vertices[j].Normal.X, curMesh.Vertices[j].Normal.Y, curMesh.Vertices[j].Normal.Z };
                glm::vec2 texCoord = { curMesh.Vertices[j].TextureCoordinate.X, curMesh.Vertices[j].TextureCoordinate.Y };
                data.positions.push_back(vertice);
                data.normals.push_back(normal);
                data.texCoords.push_back(texCoord);
            }

            data.vertexIndices = curMesh.Indices;

        }
    }
    else {
        std::cerr << "IOOBJ::loadModel() failed, " << path << "!\n";
        return;
    }

    data.setInterleavedData();
    modelDataMap[name] = data;
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