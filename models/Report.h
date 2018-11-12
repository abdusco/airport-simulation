#ifndef PROJECT2_REPORT_H
#define PROJECT2_REPORT_H


#include <ostream>

class Report {
    long double avgWaitingTime = 0;
    unsigned long missedFlights = 0;
public:
    Report(long double avgWaitingTime, unsigned long missedFlights);

    friend std::ostream& operator<<(std::ostream& os, const Report& report);
};


#endif //PROJECT2_REPORT_H
