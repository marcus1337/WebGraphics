#include "Graphics/Objects/VertexObject.h"

VertexObject::VertexObject() : vao(0), vbo(0) {

}

VertexObject::~VertexObject() {
    if(vbo != 0)
        glDeleteBuffers(1, &vbo);
    if(vao != 0)
        glDeleteVertexArrays(1, &vao);
}