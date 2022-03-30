#include <glm/glm.hpp>
#include <string>

#ifndef IMAGE_H
#define IMAGE_H

class Image {

public:
    int width = 100, height = 100;
    int x = 0, y = 0;
    std::string texture = "stallTexture.png";
    float rotation = 0;
    glm::vec3 color = glm::vec3(1.0f, 0.0f, 1.0f);
    float alpha = 1.0f;
};

#endif