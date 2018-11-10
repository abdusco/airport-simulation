#include "Event.h"
#include "Passenger.h"


bool Event::operator<(const Event& rhs) const {
    // later events are less important
    // this < rhs if this happens later
    return timestamp > rhs.timestamp;
}

Event::Event(EventType type, int timestamp, Passenger* passenger) {
    this->type = type;
    this->timestamp = timestamp;
    this->passenger = passenger;
}

std::ostream& operator<<(std::ostream& os, const Event& event) {
    std::string type;

    switch (event.type) {
        case ENTRY:
            type = "ENTRY";
            break;
        case EXIT:
            type = "EXIT";
            break;
        case LUGGAGE:
            type = "LUGGAGE";
            break;
        case SECURITY:
            type = "SECURITY";
            break;
        case DEPARTURE:
            type = "DEPARTURE";
            break;
    }

    os << "type: " << type
       << " timestamp: " << event.timestamp
       << " passenger: " << event.passenger->getId();
    return os;
}
