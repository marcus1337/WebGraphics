#include "ModelManager.h"


ModelManager::ModelManager(){


}


void ModelManager::init(IO& io){
    stallModel.objFilename = "stall.obj";
    arrowModel.objFilename = "arrow4.obj";
    stallModel.init(io);
    arrowModel.init(io);
}