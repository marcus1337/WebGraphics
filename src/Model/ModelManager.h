
#include <vector>
#include <string>
#include "Model.h"
#include "IO/IO.h"


#ifndef MODELMANAGER_H
#define MODELMANAGER_H

class ModelManager{
public:

    Model stallModel;
    Model arrowModel;

    ModelManager();
    void init(IO& io);


};

#endif