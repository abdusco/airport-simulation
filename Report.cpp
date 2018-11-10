#include <iostream>
#include "Report.h"

double truncate(double num, int digits = 3) {
    int factor = 10;
    while (--digits) factor *= 10;
    return (double) ((int) (num * factor)) / factor;
}


Report::Report(double avgWaitingTime, int missedFlights)
        : avgWaitingTime(avgWaitingTime),
          missedFlights(missedFlights) {}

std::ostream& operator<<(std::ostream& os, const Report& report) {
    os << truncate(report.avgWaitingTime) << " " << report.missedFlights;
    return os;
}
