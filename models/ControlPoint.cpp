#include <algorithm>
#include "ControlPoint.h"

ControlPoint::ControlPoint(unsigned long workers) : workers(workers) {}

unsigned long clamp(unsigned long x, unsigned long min, unsigned long max) {
    if (x < min) x = min;
    if (x > max) x = max;
    return x;
}

void ControlPoint::occupyWorker() {
    busyWorkers = clamp(busyWorkers + 1, 0, workers);
}

void ControlPoint::releaseWorker() {
    busyWorkers = clamp(busyWorkers - 1, 0, workers);
}

bool ControlPoint::isBusy() const {
    return busyWorkers == workers;
}

std::ostream& operator<<(std::ostream& os, const ControlPoint& point) {
    os << "busyWorkers: " << point.busyWorkers << " workers: " << point.workers;
    return os;
}



