#include <glm/glm.hpp>
#include <glm/ext.hpp>

#ifndef MATRIXDATA_H
#define MATRIXDATA_H

class MatrixData{
public:

    MatrixData() = default;
    MatrixData(glm::mat4 _V, glm::mat4 _P) : V(_V), P(_P){
        VP = P * V;
    }

    glm::mat4 V, P, VP;

};

#endif