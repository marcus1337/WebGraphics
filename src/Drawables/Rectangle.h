
#ifndef RECTANGLE_H
#define RECTANGLE_H

class Rectangle {
public:
    int x = 0, y = 0;
    int width = 300;
    int height = 100;
    float rotation = 90;
    glm::vec3 color = glm::vec3(1.0f, 0.5f, 0.2f);
    float alpha = 1.0f;
};


#endif RECTANGLE_H