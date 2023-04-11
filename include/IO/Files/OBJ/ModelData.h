#ifndef MODELDATA_H
#define MODELDATA_H
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

class ModelData {

public:
    std::vector<glm::vec3> positions;
    std::vector<glm::vec2> texCoords;
    std::vector<glm::vec3> normals;
    std::vector<unsigned int> vertexIndices, texCoordIndices, normalIndices;
    std::vector<float> interleavedData;
    void setInterleavedData();
};

#endif // !MODELDATA_H
