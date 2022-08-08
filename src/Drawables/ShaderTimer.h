
#include <chrono>

#ifndef SHADERTIMER_H
#define SHADERTIMER_H

class ShaderTimer {

public:
    bool forwardAnimation = false;
    bool backAnimation = false;
    float effectInterpolation = 0.0f; //0...1
    float animationTimeSeconds = 0.35f; 
    void updateEffectInterpolation();
    float getDeltaTimeSeconds();
    std::chrono::time_point<std::chrono::system_clock> lastUpdateTime;

};

#endif