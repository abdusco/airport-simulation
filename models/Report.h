#ifndef PROJECT2_REPORT_H
#define PROJECT2_REPORT_H


#include <ostream>

class Report {
    double avgWaitingTime = 0;
    int missedFlights = 0;
public:
    Report(double avgWaitingTime, int missedFlights);

    friend std::ostream& operator<<(std::ostream& os, const Report& report);
};


#endif //PROJECT2_REPORT_H
