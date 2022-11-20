#include "UpdateTimer.h"
#include <iostream>

UpdateTimer::UpdateTimer(double _rendersPerSecond, double _logicUpdatesPerSecond) :
    rendersPerSecond(_rendersPerSecond), logicUpdatesPerSecond(_logicUpdatesPerSecond) {
    passedRenderMicroseconds = 0;
    const double microsecondsPerSecond = 1000000.0;
    renderMicroseconds = (long long)((1.0 / rendersPerSecond) * microsecondsPerSecond);
    passedLogicMicroseconds = 0;
    logicMicroseconds = (long long)((1.0 / logicUpdatesPerSecond) * microsecondsPerSecond);
}

bool UpdateTimer::isLogicUpdate() {
    using namespace std::chrono;
    steady_clock::time_point timeNow = steady_clock::now();
    passedLogicMicroseconds += duration_cast<microseconds>(timeNow - timeLastLogicUpdateCheck).count();
    timeLastLogicUpdateCheck = timeNow;
    if (passedLogicMicroseconds < logicMicroseconds)
        return false;
    passedLogicMicroseconds = 0;
    return true;
}

bool UpdateTimer::isRenderUpdate() {
    using namespace std::chrono;
    steady_clock::time_point timeNow = steady_clock::now();
    passedRenderMicroseconds += duration_cast<microseconds>(timeNow - timeLastRenderUpdateCheck).count();
    timeLastRenderUpdateCheck = timeNow;
    if (passedRenderMicroseconds < renderMicroseconds)
        return false;
    passedRenderMicroseconds = 0;
    return true;
}

