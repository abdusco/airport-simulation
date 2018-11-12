#ifndef PROJECT2_CONTROLPOINT_H
#define PROJECT2_CONTROLPOINT_H

#include <ostream>

class ControlPoint {
    int busyWorkers = 0;
    int workers;
public:
    explicit ControlPoint(int workers);

    void occupyWorker();

    void releaseWorker();

    bool isBusy() const;

    friend std::ostream& operator<<(std::ostream& os, const ControlPoint& point);
};

#endif //PROJECT2_CONTROLPOINT_H
