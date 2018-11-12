#ifndef PROJECT2_CONTROLPOINT_H
#define PROJECT2_CONTROLPOINT_H

#include <ostream>

class ControlPoint {
    unsigned long busyWorkers = 0;
    unsigned long workers;
public:
    explicit ControlPoint(unsigned long workers);

    void occupyWorker();

    void releaseWorker();

    bool isBusy() const;

    friend std::ostream& operator<<(std::ostream& os, const ControlPoint& point);
};

#endif //PROJECT2_CONTROLPOINT_H
