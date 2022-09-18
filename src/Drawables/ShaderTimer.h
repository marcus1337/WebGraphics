
#include <chrono>

#ifndef SHADERTIMER_H
#define SHADERTIMER_H

class ShaderTimer {
    bool animateForward = false;
    float effectInterpolation = 0.0f;
    float animationTimeSeconds = 0.35f;
    std::chrono::time_point<std::chrono::system_clock> lastUpdateTime;
    float getDeltaTimeSeconds();

public:
    void setAnimationForward();
    void setAnimationBackward();
    void updateEffectInterpolation();
    float getEffect();
};

#endif