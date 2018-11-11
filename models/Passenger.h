#ifndef PROJECT2_PASSENGER_H
#define PROJECT2_PASSENGER_H


#include <ostream>
#include "EventType.h"

class Event;

struct TimeLog {
    int enter = 0;
    int luggage = 0;
    int security = 0;
    int depart = 0;
    int exit = 0;
};

class Passenger {
private:
public:
    int tEnter;
    int timeFlight;
    int waitAtLuggage;
    int waitAtSecurity;
    bool isVip;
    bool hasLuggage;
    bool skippedLuggage = false;
    bool skippedSecurity = false;
    TimeLog timeLog;
    std::string id;

    Passenger(int timeBeforeEntry,
              int timeBeforeFlight,
              int waitAtLuggage,
              int waitAtSecurity,
              bool isVip,
              bool hasLuggage);

    bool missedFlight();

    void log(Event& event);

    void reset();

    void skipLuggage();

    void skipSecurity();

    int getWaitedTime();


    friend std::ostream& operator<<(std::ostream& os, Passenger& passenger);

    bool operator<(const Passenger& rhs) const;

private:
    std::string makeId();
};


#endif //PROJECT2_PASSENGER_H
