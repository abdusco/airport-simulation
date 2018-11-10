#include <algorithm>
#include "ControlPoint.h"

void ControlPoint::occupyWorker() {
    busyWorkers++;
    if (busyWorkers > workers) busyWorkers = workers;
//    busyWorkers = std::max(busyWorkers + 1, workers);
}

void ControlPoint::releaseWorker() {
    busyWorkers--;
//    busyWorkers = std::min(busyWorkers - 1, 0);
    if (busyWorkers < 0) busyWorkers = 0;
}

bool ControlPoint::isAvailable() {
    return busyWorkers < workers;
}

ControlPoint::ControlPoint(int workers) : workers(workers) {}

std::ostream &operator<<(std::ostream &os, const ControlPoint &point) {
    os << "busyWorkers: " << point.busyWorkers << " workers: " << point.workers;
    return os;
}



