#ifndef OBJECT_CONTAINER_H
#define OBJECT_CONTAINER_H
#include "ImageObject.h"
#include "TextObject.h"
#include "VertexObject.h"
#include "ModelObject.h"
#include "PoseModelObject.h"
#include <map>
#include <memory>
#include "IO/Files/IOContainer.h"
#include <tuple>

class ObjectContainer {

    ObjectContainer();
    std::map<std::string, std::shared_ptr<ModelObject>> modelObjects;
    std::map<std::pair<std::string, std::string>, std::shared_ptr<PoseModelObject>> poseModelObjects;


public:
    ImageObject imageObj;
    TextObject textObj;
    ModelObject* getModelObject(std::string model);
    PoseModelObject* getPoseModelObject(const std::string& objName, const std::string& daeName);
    static ObjectContainer& getInstance();

};

#endif // !OBJECT_CONTAINER_H
