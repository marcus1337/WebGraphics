#include "IO/Files/OBJ/IOOBJ.h"

#define TINYOBJLOADER_IMPLEMENTATION // define this in only *one* .cc
#include "IO/Files/OBJ/tiny_obj_loader.h"
#include "glm/gtx/string_cast.hpp"

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
    tinyobj::ObjReaderConfig reader_config;
    tinyobj::ObjReader reader;
    if (!reader.ParseFromFile(path, reader_config)) {
        if (!reader.Error().empty()) {
            std::cerr << "TinyObjReader: " << reader.Error();
        }
        return;
    }
    if (!reader.Warning().empty()) {
        std::cout << "TinyObjReader: " << reader.Warning();
    }


    ///////// readModelData --
    ModelData data;
    auto& attrib = reader.GetAttrib();
    auto& shapes = reader.GetShapes();
    for (size_t s = 0; s < shapes.size() && s < 1; s++) { //s < 1 because only loading one shape per file, currently.
        size_t index_offset = 0;
        for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
            size_t fv = size_t(shapes[s].mesh.num_face_vertices[f]);
            for (size_t v = 0; v < fv; v++) {
                tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
                ////////////////////////////////// addMeshIndex --
                auto vi = idx.vertex_index;
                auto ni = idx.normal_index;
                auto ti = idx.texcoord_index;
                auto& vertices = attrib.vertices;
                auto& normals = attrib.normals;
                auto& texCoords = attrib.texcoords;
             
                glm::vec3 position = glm::vec3(vertices[3 * vi],
                    vertices[3 * vi + 1],
                    vertices[3 * vi + 2]);

                data.positions.push_back(position);
                data.vertexIndices.push_back(idx.vertex_index);

                if (idx.normal_index >= 0) {
                    glm::vec3 normal = glm::vec3(normals[3 * ni],
                        normals[3 * ni + 1],
                        normals[3 * ni + 2]);
                    data.normals.push_back(normal);
                    data.normalIndices.push_back(idx.normal_index);
                }
                if (idx.texcoord_index >= 0) {
                    glm::vec2 texCoord = glm::vec2(texCoords[2 * ti],
                        texCoords[2 * ti + 1]);
                    data.texCoords.push_back(texCoord);
                    data.texCoordIndices.push_back(idx.texcoord_index);
                }
              
                ////////////////////////////////// --
            }

            index_offset += fv;
        }
    }
    //////////////// --

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