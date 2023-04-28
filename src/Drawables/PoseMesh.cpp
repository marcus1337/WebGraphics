#include "Drawables/PoseMesh.h"


PoseMesh::PoseMesh(const std::string& objName, const std::string& textureName, const std::string& daeName) : Drawable(imageShader), objName(objName), daeName(daeName) {
    imageShader.setProgram("animated_model");
    imageShader.setFloatUniform("useTexture", 1.0f);
    imageShader.setTexture(textureName, Shader::getDefaultShaderTextureName());
}

void PoseMesh::setTexture(const std::string& textureName) {
    imageShader.setTexture(textureName, Shader::getDefaultShaderTextureName());
}

void PoseMesh::render() {
    imageShader.setModel(model);
    objectContainer.getPoseModelObject(objName, daeName)->draw(imageShader);
}

