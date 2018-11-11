#include "Event.h"
#include "Passenger.h"


Event::Event(EventType type, int timestamp, Passenger* passenger) {
    this->type = type;
    this->timestamp = timestamp;
    this->passenger = passenger;
}

std::ostream& operator<<(std::ostream& os, const Event& event) {
    std::string type = getEventTypeName(event.type);

    os << "type: " << type
       << " timestamp: " << event.timestamp
       << " passenger: " << event.passenger->id;
    return os;
}

bool Event::operator<(const Event& other) const {
    if (other.timestamp == this->timestamp) {
        return other.type > this->type;
    }
    return other.timestamp < this->timestamp;
}
