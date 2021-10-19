#include <glm/glm.hpp>
#include <glm/ext.hpp>

class Mouse
{

public:

    bool isLeftMousePressed = false;
    bool wasLeftMousePressed = false;
    bool wasLeftMouseReleased = false;
    
    double deltaMouseX = 0;
    double deltaMouseY = 0;
    double mouseX = 0.0f;
    double mouseY = 0.0f;
    bool hasInitMousePos = false;
    glm::vec2 getRelativeMousePosition(int windowWidth, int windowHeight, double _fromX = 0.f, double _fromY = 0.f, double _toX = 1.f, double _toY = 1.f);
    void drag(int toPosX, int toPosY);


    void clearDeltas();
    void beginFrame();
    void endFrame();

};