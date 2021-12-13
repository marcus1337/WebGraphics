#include "PostImageUniform.h"


void PostImageUniform::setCustomUniforms(){
    glUniform1f(glGetUniformLocation(programID, "blur"), blur);
}