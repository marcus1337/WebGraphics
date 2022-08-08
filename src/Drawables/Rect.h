#include <glm/glm.hpp>
#include <Engine/Graphics.h>

#ifndef RECT_H
#define RECT_H

class Rect {
public:
    void render(Graphics& _graphics);
    int x = 0, y = 0;
    int width = 300;
    int height = 100;
    float rotation = 0;
    glm::vec3 color = glm::vec3(1.0f, 0.5f, 0.2f);
    float alpha = 1.0f;
};


#endif