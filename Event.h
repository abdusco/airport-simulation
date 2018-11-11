#ifndef PROJECT2_EVENT_H
#define PROJECT2_EVENT_H

#include <ostream>
#include "EventType.h"

class Passenger;

class Event {
public:
    EventType type;
    int timestamp;
    Passenger* passenger;

    Event(EventType type, int timestamp, Passenger* passenger);

    friend std::ostream& operator<<(std::ostream& os, const Event& event);

    bool operator<(const Event& rhs) const;
};


#endif //PROJECT2_EVENT_H
