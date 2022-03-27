#include <glm/glm.hpp>
#include <string>

#ifndef TEXT_H
#define TEXT_H

class Text {

public:
    int x = 0, y = 0;
    std::string text = "Hello World";
    std::string font = "Roboto-Regular";
    float rotation = 0;
    glm::vec4 color = glm::vec4(1.0f, 0.0f, 1.0f, 1.0f);
};

#endif // !TEXT_H
