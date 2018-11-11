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
    this->id = makeId();
}

void Passenger::log(Event& event) {
    switch (event.type) {
        case ENTERED:
            timeLog.enter = event.timestamp;
            break;
        case PAST_LUGGAGE:
            timeLog.luggage = event.timestamp;
            break;
        case PAST_SECURITY:
            timeLog.security = event.timestamp;
            break;
        case DEPARTED:
            timeLog.depart = event.timestamp;
            break;
        case EXITED:
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

std::string Passenger::makeId() {
    std::ostringstream ss;
    ss << tEnter
       << "." << timeFlight
       << "." << waitAtLuggage
       << "." << waitAtSecurity
       << "." << hasLuggage
       << "." << isVip;
    return ss.str();
}

std::ostream& operator<<(std::ostream& os, Passenger& passenger) {
    os << "id: " << passenger.makeId()
       << " missed: " << passenger.missedFlight();
    return os;
}


void Passenger::reset() {
    skippedLuggage = false;
    skippedSecurity = false;
    this->timeLog = TimeLog();
}

void Passenger::skipLuggage() {
    this->skippedLuggage = true;
}

void Passenger::skipSecurity() {
    this->skippedSecurity = true;
}

bool Passenger::operator<(const Passenger& other) const {
    if (other.timeFlight == this->timeFlight) {
        return other.tEnter < this->tEnter;
    }
    return other.timeFlight < this->timeFlight;
}



