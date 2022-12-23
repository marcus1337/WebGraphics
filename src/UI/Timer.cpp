#include "Timer.h"

#include <algorithm>
#include <limits>
#include <numbers>
#include <cmath>

Timer::Timer() {
    objectStartTime = std::chrono::steady_clock::now();
    lastDeltaTime = std::chrono::steady_clock::now();
}

float Timer::getDeltaTimeMilliseconds() {
    using namespace std::chrono;
    long long elapsedMilliseconds = duration_cast<milliseconds>(steady_clock::now() - lastDeltaTime).count();
    lastDeltaTime = steady_clock::now();
    return (float)elapsedMilliseconds;
}

int Timer::getPassedMilliseconds() {
    using namespace std::chrono;
    long long passedTime = duration_cast<milliseconds>(steady_clock::now() - objectStartTime).count();
    passedTime = passedTime % std::numeric_limits<int>::max();
    return (int)passedTime;
}

float Timer::getPassedTimeInterpolation(int durationInMilliseconds) {
    int ms = getPassedMilliseconds();
    int passedTime = ms % (durationInMilliseconds + 1);
    return (float)passedTime / (float)durationInMilliseconds;
}

float Timer::getPassedTimeInterpolationCurve(int durationInMilliseconds) {
    float pi = std::numbers::pi_v<float>;
    float x = getPassedTimeInterpolation(durationInMilliseconds);
    return std::sin(x * pi);
}

