#include <algorithm>
#include "ControlPoint.h"

int clamp(int x, int min, int max) {
    if (x < min) x = min;
    if (x > max) x = max;
    return x;
}

void ControlPoint::occupyWorker() {
    busyWorkers = clamp(busyWorkers + 1, 0, workers);
    busy = busyWorkers == workers;
}

void ControlPoint::releaseWorker() {
    busyWorkers = clamp(busyWorkers - 1, 0, workers);
    busy = busyWorkers == workers;
}

ControlPoint::ControlPoint(int workers) : workers(workers) {}

std::ostream& operator<<(std::ostream& os, const ControlPoint& point) {
    os << "busyWorkers: " << point.busyWorkers << " workers: " << point.workers;
    return os;
}



