#ifndef PROJECT2_PASSENGER_H
#define PROJECT2_PASSENGER_H


#include <ostream>
#include "EventType.h"

class Event;

struct TimeLog {
    unsigned long enter = 0;
    unsigned long luggage = 0;
    unsigned long security = 0;
    unsigned long depart = 0;
    unsigned long exit = 0;
};

class Passenger {
private:
public:
    unsigned long tEnter;
    unsigned long timeFlight;
    unsigned long waitAtLuggage;
    unsigned long waitAtSecurity;
    bool isVip;
    bool hasLuggage;
    bool skippedLuggage = false;
    bool skippedSecurity = false;
    TimeLog timeLog;
    std::string id;

    Passenger(unsigned long timeBeforeEntry,
              unsigned long timeBeforeFlight,
              unsigned long waitAtLuggage,
              unsigned long waitAtSecurity,
              bool isVip,
              bool hasLuggage);

    bool missedFlight();

    void log(Event& event);

    void reset();

    void skipLuggage();

    void skipSecurity();

    unsigned long getWaitedTime();


    friend std::ostream& operator<<(std::ostream& os, Passenger& passenger);

    bool operator<(const Passenger& rhs) const;

private:
    std::string makeId();
};


#endif //PROJECT2_PASSENGER_H
