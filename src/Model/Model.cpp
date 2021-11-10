#include "Model.h"

#include <string>

#include <iostream>

void Model::init(IO &io)
{
    std::string objFilePath = io.iostuff.modelsPath + objFilename;
    /*Load obj-files here, currently missing.*/
}

void Model::draw(IO& io, MatrixData& matrixData)
{
    float fUseTexture = useTexture ? 1.0f : 0.0f;
    glm::mat4 rotateMat = glm::toMat4(orientation);
    glm::mat4 modModel = scaleMat * translateMat * rotateMat;
    glm::mat4 MVP = matrixData.VP * modModel;

    GLuint programID = io.gldata.getProgram((GLuint)program);
    GLuint textureID = io.gldata.getTexture((GLuint)texture);

    glUseProgram(programID);
    glUniformMatrix4fv(glGetUniformLocation(programID, "MVP"), 1, GL_FALSE, &MVP[0][0]);
    glUniform1f(glGetUniformLocation(programID, "useTexture"), fUseTexture);

    GLuint mTex1Handle  = glGetUniformLocation( programID, "tex");
    glUniform1i(mTex1Handle, 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glBindVertexArray(mesh.vao);
    glDrawElements(GL_TRIANGLES, mesh.numIndices, GL_UNSIGNED_INT, 0);

}

void Model::setScale(float x, float y, float z) {
    scaleMat = glm::scale(glm::mat4(1.0f), glm::vec3(x, y, z));
}


void Model::setRotation(float x, float y, float z) {
    angles.x = x;
    angles.y = y;
    angles.z = z;
    glm::vec3 radianAngles(glm::radians(x), glm::radians(y), glm::radians(z));    
    orientation = glm::quat(radianAngles);
}