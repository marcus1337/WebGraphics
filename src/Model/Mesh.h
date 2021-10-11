
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <vector>

#ifndef MESH_H
#define MESH_H

enum AttributeLocation {
        POSITION = 0,
        NORMAL = 1,
        UVCOORDS = 2
};

class Mesh{

    bool wasInitialized = false;

    public:

    ~Mesh();

    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    std::vector<uint32_t> indices;
    std::vector<glm::vec2> uvCoords;

    GLuint vao;
    GLuint vertexVBO;
    GLuint normalVBO;
    GLuint uvVBO;
    GLuint indexVBO;
    
    int numVertices;
    int numIndices;

    void init(std::vector<glm::vec3> _vertices, std::vector<glm::vec3> _normals, std::vector<uint32_t> _indices, std::vector<glm::vec2> _uvCoords);

};

#endif
