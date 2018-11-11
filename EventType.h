#ifndef PROJECT2_EVENTTYPE_H
#define PROJECT2_EVENTTYPE_H

#include <string>

enum EventType {
    ENTERED = 1 << 0,
    PAST_LUGGAGE = 1 << 1,
    PAST_SECURITY = 1 << 2,
    DEPARTED = 1 << 3,
    EXITED = 1 << 4,
};

std::string getEventTypeName(EventType type);

#endif //PROJECT2_EVENTTYPE_H
