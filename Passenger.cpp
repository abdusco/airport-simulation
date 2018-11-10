#include <sstream>
#include <iostream>

#include "Passenger.h"
#include "Event.h"

Passenger::Passenger(int timeBeforeEntry,
                     int timeBeforeFlight,
                     int waitAtLuggage,
                     int waitAtSecurity,
                     bool isVip,
                     bool hasLuggage) {
    this->tEnter = timeBeforeEntry;
    this->timeFlight = timeBeforeFlight;
    this->waitAtLuggage = waitAtLuggage;
    this->waitAtSecurity = waitAtSecurity;
    this->isVip = isVip;
    this->hasLuggage = hasLuggage;
}

void Passenger::logEvent(const Event& event) {
    switch (event.type) {
        case ENTRY:
            timeLog.enter = event.timestamp;
            break;
        case LUGGAGE:
            timeLog.luggage = event.timestamp;
            break;
        case SECURITY:
            timeLog.security = event.timestamp;
            break;
        case DEPARTURE:
            timeLog.depart = event.timestamp;
            break;
        case EXIT:
            timeLog.exit = event.timestamp;
            break;
    }
}

bool Passenger::missedFlight() {
    return timeFlight < timeLog.depart;
}

int Passenger::getWaitedTime() {
    return timeLog.exit - timeLog.enter;
}

std::string Passenger::getId() {
    std::ostringstream ss;
    ss << "" << tEnter
       << "" << timeFlight
       << "" << waitAtLuggage
       << "" << waitAtSecurity
       << "" << hasLuggage
       << "" << isVip;
    return ss.str();
}

std::ostream& operator<<(std::ostream& os, Passenger& passenger) {
    os << "actualD: " << passenger.timeLog.depart
       << " timeD: " << passenger.timeFlight
       << " missed: " << passenger.missedFlight();
    return os;
}


