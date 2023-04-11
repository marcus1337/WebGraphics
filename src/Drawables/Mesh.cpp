#include "Drawables/Mesh.h"


Mesh::Mesh(std::string _modelName, std::string textureName) : Drawable(imageShader), modelName(_modelName) {
    imageShader.setTexture(textureName, Shader::getDefaultShaderTextureName());
}

void Mesh::setTexture(std::string textureName) {
    imageShader.setTexture(textureName, Shader::getDefaultShaderTextureName());
}

void Mesh::render() {
    imageShader.setModel(model);
    imageShader.setFloatUniform("useTexture", 1.0f);
    objectContainer.getModelObject(modelName)->draw(imageShader);
}

