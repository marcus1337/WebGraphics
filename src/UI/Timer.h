
#include <chrono>

#ifndef TIMER_H
#define TIMER_H

class Timer {

    std::chrono::steady_clock::time_point objectStartTime, lastDeltaTime;

public:

    Timer();
    float getDeltaTimeMilliseconds();
    int getPassedMilliseconds();
    float getPassedTimeInterpolation(int durationInMilliseconds);
    float getPassedTimeInterpolationCurve(int durationInMilliseconds);

};


#endif // !TIMER_H
