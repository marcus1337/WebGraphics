
#ifndef GAMECAMERA_H
#define GAMECAMERA_H

class GameCamera {

    int x = 0;
    int y = 0;
    float zoom = 1.0f;

public:

    int getX();
    int getY();
    void setPosition(int _x, int _y);
    int getXOffset(int _x);
    int getYOffset(int _y);
    void addZoomStep(float _zoom);
    void resetZoom();

};

#endif // !GAMECAMERA_H
