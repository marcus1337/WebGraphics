
#include <chrono>

#ifndef UPDATETIMER_H
#define UPDATETIMER_H

class UpdateTimer {

    double rendersPerSecond, logicUpdatesPerSecond;
    long long passedRenderMicroseconds, renderMicroseconds;
    long long passedLogicMicroseconds, logicMicroseconds;
    std::chrono::steady_clock::time_point timeLastRenderUpdateCheck, timeLastLogicUpdateCheck;

public:
    UpdateTimer(double _rendersPerSecond = 60.0, double _logicUpdatesPerSecond = 20.0);
    bool isLogicUpdate();
    bool isRenderUpdate();
};


#endif
