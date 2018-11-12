#include <iostream>
#include <iomanip>
#include "Report.h"

long double truncate(long double num, int digits = 3) {
    int factor = 10;
    while (--digits) factor *= 10;
    return (long double) ((long double) (num * factor)) / factor;
}

Report::Report(long double avgWaitingTime, unsigned long missedFlights)
        : avgWaitingTime(avgWaitingTime),
          missedFlights(missedFlights) {}

std::ostream& operator<<(std::ostream& os, const Report& report) {
    os << std::fixed;
    os << std::setprecision(3);
    os << truncate(report.avgWaitingTime) << " " << report.missedFlights;
    return os;
}
