#include <iostream>

#include "Airport.h"
#include "Feature.h"

Airport::Airport(int numSecurity, int numLuggage)
        : luggageControl(ControlPoint(numLuggage)),
          securityControl(ControlPoint(numSecurity)) {
    this->features = FIRST_COME_FIRST_SERVE;
}

void Airport::setFeatures(Feature features) {
    this->features = features;
}

Airport::~Airport() {
    this->luggageQueue.empty();
    this->securityQueue.empty();
}

Report Airport::run(PassengerList& passengers) {
    for (auto& passenger : passengers) {
        acceptPassenger(passenger);
    }

    while (!events.empty()) {
        Event e = events.top();
        events.pop();
        clock = e.timestamp;

        Passenger& passenger = *e.passenger;
        passenger.logEvent(e);

        switch (e.type) {
            case ENTRY:
                handleEntry(passenger);
                break;
            case LUGGAGE:
                handleLuggage(passenger);
                break;
            case SECURITY:
                handleSecurity(passenger);
                break;
            case DEPARTURE:
                handleDeparture(passenger);
                break;
            case EXIT:
                handleExit(passenger);
                break;
        }
    }

    return prepareReport(passengers);
}

void Airport::dispatch(Event event) {
    events.push(event);
}

void Airport::acceptPassenger(Passenger& passenger) {
    dispatch(Event(ENTRY,
                   passenger.tEnter,
                   &passenger));
}

void Airport::handleEntry(Passenger& passenger) {
    if (!luggageReady()) {
        return luggageQueue.push(&passenger);
    }

    luggageControl.occupyWorker();
    dispatch(Event(LUGGAGE,
                   clock + passenger.waitAtLuggage,
                   &passenger));
}

void Airport::handleLuggage(Passenger& passenger) {
    if (!securityReady()) {
        return securityQueue.push(&passenger);
    }

    luggageControl.releaseWorker();
    securityControl.occupyWorker();
    dispatch(Event(SECURITY,
                   clock + passenger.waitAtSecurity,
                   &passenger));
}

void Airport::handleSecurity(Passenger& passenger) {
    moveLuggageQueue();

    securityControl.releaseWorker();
    dispatch(Event(DEPARTURE,
                   clock,
                   &passenger));
}

void Airport::handleDeparture(Passenger& passenger) {
    moveSecurityQueue();
    dispatch(Event(EXIT,
                   clock,
                   &passenger));
}

void Airport::handleExit(Passenger& passenger) {
}

void Airport::moveLuggageQueue() {
    if (luggageQueue.empty()) return;

    Passenger* waiting = luggageQueue.front();
    luggageQueue.pop();
    dispatch(Event(SECURITY,
                   clock + waiting->waitAtSecurity,
                   waiting));
}

void Airport::moveSecurityQueue() {
    if (securityQueue.empty()) return;

    Passenger* waiting = securityQueue.front();
    securityQueue.pop();
    dispatch(Event(DEPARTURE,
                   clock,
                   waiting));
}

bool Airport::luggageReady() {
    return luggageQueue.empty() && luggageControl.isAvailable();
}

bool Airport::securityReady() {
    return securityQueue.empty() && securityControl.isAvailable();
}

Report Airport::prepareReport(PassengerList& passengers) {
    int totalWait = 0;
    int missedFlights = 0;

    for (auto& passenger : passengers) {
        totalWait += passenger.getWaitedTime();
        if (passenger.missedFlight()) missedFlights++;
    }

    double avgWaitingTime = (double) totalWait / (double) passengers.size();
    return {avgWaitingTime, missedFlights};
}

