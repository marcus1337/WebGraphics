#include "ShaderTimer.h"
#include <algorithm>
#include <limits>
#include <numbers>

ShaderTimer::ShaderTimer() {

}

void ShaderTimer::setAnimationForward() {
    animateForward = true;
}
void ShaderTimer::setAnimationBackward() {
    animateForward = false;
}

void ShaderTimer::updateEffect() {
    float effectDelta = timer.getDeltaTimeMilliseconds() / (animationTimeSeconds*1000.0f);
    if (!animateForward)
        effectDelta *= -1.0f;
    effect += effectDelta;
    effect = std::clamp<float>(effect, 0.0f, 1.0f);
}

float ShaderTimer::getEffect() {
    updateEffect();
    return effect;
}



