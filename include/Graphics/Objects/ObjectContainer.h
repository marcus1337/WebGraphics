#ifndef OBJECT_CONTAINER_H
#define OBJECT_CONTAINER_H
#include "ImageObject.h"
#include "TextObject.h"
#include "VertexObject.h"

class ObjectContainer {

    ObjectContainer();

public:
    ImageObject imageObj;
    TextObject textObj;
    static ObjectContainer& getInstance();

};

#endif // !OBJECT_CONTAINER_H
