#ifndef OBJECT_CONTAINER_H
#define OBJECT_CONTAINER_H
#include "ImageObject.h"
#include "TextObject.h"
#include "VertexObject.h"
#include "ModelObject.h"
#include <map>
#include <memory>
#include "IO/Files/IOContainer.h"
#include <tuple>

class ObjectContainer {

    ObjectContainer();
    std::map<std::string, std::shared_ptr<ModelObject>> modelObjects;


public:
    ImageObject imageObj;
    TextObject textObj;
    ModelObject* getModelObject(std::string model);
    static ObjectContainer& getInstance();

};

#endif // !OBJECT_CONTAINER_H
