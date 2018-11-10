#ifndef PROJECT2_PASSENGER_H
#define PROJECT2_PASSENGER_H


#include <ostream>

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
    TimeLog timeLog;

    Passenger(int timeBeforeEntry,
              int timeBeforeFlight,
              int waitAtLuggage,
              int waitAtSecurity,
              bool isVip,
              bool hasLuggage);

    bool missedFlight();

    void logEvent(const Event& event);

    int getWaitedTime();

    std::string getId();

    friend std::ostream& operator<<(std::ostream& os, Passenger& passenger);
};


#endif //PROJECT2_PASSENGER_H
