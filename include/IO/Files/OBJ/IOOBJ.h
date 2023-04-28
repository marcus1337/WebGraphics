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

#include "ModelData.h"

class IOOBJ {
    std::map<std::string, ModelData> modelDataMap;
    void loadModel(std::string path, std::string name);
    bool loadModelData(const std::string& path, ModelData& data);
public:
    void loadModels(std::vector<std::string> modelFilePaths, std::vector<std::string> modelNames);
    ModelData getModelData(std::string name);
    std::vector<std::string> getModelNames();
};

#endif // !IO_OBJ_H
