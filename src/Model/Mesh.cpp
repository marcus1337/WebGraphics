#include "Mesh.h"
#include <iostream>

void Mesh::init(std::vector<glm::vec3> _vertices, std::vector<glm::vec3> _normals, std::vector<uint32_t> _indices, std::vector<glm::vec2> _uvCoords){
    wasInitialized = true;
    vertices = _vertices;
    normals = _normals;
    indices = _indices;
    uvCoords = _uvCoords;
    numVertices = vertices.size();
    numIndices = indices.size();

    // Generates and populates a VBO for the vertices
    glGenBuffers(1, &(vertexVBO));
    glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
    auto verticesNBytes = vertices.size() * sizeof(vertices[0]);
    glBufferData(GL_ARRAY_BUFFER, verticesNBytes, vertices.data(), GL_STATIC_DRAW);

    // Generates and populates a VBO for the vertex normals
    glGenBuffers(1, &(normalVBO));
    glBindBuffer(GL_ARRAY_BUFFER, normalVBO);
    auto normalsNBytes = normals.size() * sizeof(normals[0]);
    glBufferData(GL_ARRAY_BUFFER, normalsNBytes, normals.data(), GL_STATIC_DRAW);

    // Generates and populates a VBO for the element indices
    glGenBuffers(1, &(indexVBO));
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVBO);
    auto indicesNBytes = indices.size() * sizeof(indices[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesNBytes, indices.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &(uvVBO));
    glBindBuffer(GL_ARRAY_BUFFER, uvVBO);
    auto uvsNBytes = uvCoords.size() * sizeof(uvCoords[0]);
    glBufferData(GL_ARRAY_BUFFER, uvsNBytes, uvCoords.data(), GL_STATIC_DRAW);

    // Creates a vertex array object (VAO) for drawing the mesh
    glGenVertexArrays(1, &(vao));
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);

    glEnableVertexAttribArray(POSITION);
    glVertexAttribPointer(POSITION, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glBindBuffer(GL_ARRAY_BUFFER, normalVBO);

    glEnableVertexAttribArray(NORMAL);
    glVertexAttribPointer(NORMAL, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVBO);

    glEnableVertexAttribArray(UVCOORDS);
    glVertexAttribPointer(UVCOORDS, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
    glBindBuffer(GL_ARRAY_BUFFER, uvVBO);

    glBindVertexArray(0);
}

Mesh::~Mesh(){
    if(wasInitialized){
        glDeleteBuffers(1, &vao);
    }
}