#ifndef PROJECT2_CONTROLPOINT_H
#define PROJECT2_CONTROLPOINT_H

#include <ostream>

class ControlPoint {
public:
    explicit ControlPoint(int workers);

    void occupyWorker();

    void releaseWorker();

    friend std::ostream& operator<<(std::ostream& os, const ControlPoint& point);

    int busyWorkers = 0;
    int workers;
    bool busy = false;
};


#endif //PROJECT2_CONTROLPOINT_H
