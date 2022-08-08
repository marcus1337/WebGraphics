#include "ShaderTimer.h"
#include <algorithm>


float ShaderTimer::getDeltaTimeSeconds() {
    float deltaTimeSeconds = 0.0f;
    auto endTime = std::chrono::system_clock::now();
    std::chrono::microseconds elapsedTime = std::chrono::duration_cast<std::chrono::microseconds>(endTime - lastUpdateTime);
    double elapsedMicroSeconds = elapsedTime.count();
    deltaTimeSeconds = elapsedMicroSeconds / 1000000.0;
    lastUpdateTime = std::chrono::system_clock::now();
    return deltaTimeSeconds;
}

void ShaderTimer::updateEffectInterpolation() {
    float deltaTime = getDeltaTimeSeconds();
    float deltaUnitInterval = deltaTime / animationTimeSeconds;
    if (forwardAnimation) {
        effectInterpolation += deltaUnitInterval;
    }
    if (backAnimation) {
        effectInterpolation -= deltaUnitInterval;
    }
    effectInterpolation = std::clamp<float>(effectInterpolation, 0.0f, 1.0f);
}
