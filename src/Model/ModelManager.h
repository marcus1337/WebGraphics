
#include <vector>
#include <string>
#include "Model.h"
#include "IO/IO.h"


#ifndef MODELMANAGER_H
#define MODELMANAGER_H



class ModelManager{
public:

    enum class Program{IMAGE = 0, TEXT};
    enum class Texture{STALL = 0};

    Model stallModel;
    Model arrowModel;

    ModelManager();
    void init(IO& io);


};

#endif