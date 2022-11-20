
#include <chrono>
#include "Timer.h"

#ifndef SHADERTIMER_H
#define SHADERTIMER_H

class ShaderTimer {
    bool animateForward = false;
    float effect = 0.0f;
    float animationTimeSeconds = 0.35f;
    Timer timer;

    void updateEffect();
public:
    ShaderTimer();
    void setAnimationForward();
    void setAnimationBackward();
    float getEffect();

};

#endif