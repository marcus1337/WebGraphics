#ifndef IO_OBJ_H
#define IO_OBJ_H
#include <GL/glew.h>
#include <vector>
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtx/quaternion.hpp>
#include <glm/common.hpp>
#include "glm/glm.hpp"

#include <string>
#include <map>
#include <iostream>
#include <vector>
#include <fstream>
#include <tuple>


struct ModelData {
    std::vector<glm::vec3> positions;
    std::vector<glm::vec2> texCoords;
    std::vector<glm::vec3> normals;
    std::vector<unsigned int> vertexIndices, texCoordIndices, normalIndices;
};

class IOOBJ {
    std::map<std::string, ModelData> modelDataMap;
    void loadModel(std::string path, std::string name);
public:
    void loadModels(std::vector<std::string> modelFilePaths, std::vector<std::string> modelNames);
    ModelData getModelData(std::string name);
};

#endif // !IO_OBJ_H
