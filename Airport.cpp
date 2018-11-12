#include <iostream>

#include "Airport.h"
#include "models/Feature.h"

Report Airport::run(PassengerList& passengers) {
    for (auto& passenger : passengers) {
        passenger.reset();
        acceptPassenger(passenger);
    }

    while (!events.empty()) {
        Event event = events.top();
        events.pop();
        clock = event.timestamp;
        dispatchHandler(event);
    }

    return prepareReport(passengers);
}

void Airport::dispatchHandler(Event& event) {
    Passenger& passenger = *event.passenger;
    passenger.log(event);

    switch (event.type) {
        case ENTERED:
            handleEntry(passenger);
            break;
        case PAST_LUGGAGE:
            handlePastLuggage(passenger);
            break;
        case PAST_SECURITY:
            handlePastSecurity(passenger);
            break;
        case DEPARTED:
            handleDeparture(passenger);
            break;
        case EXITED:
            // handleExited(passenger);
            break;
    }
}

void Airport::acceptPassenger(Passenger& passenger) {
    return emit(Event(ENTERED,
                      passenger.tEnter,
                      &passenger));
}

void Airport::handleEntry(Passenger& passenger) {
    if (canSkipLuggageControl(passenger)) {
        passenger.skipLuggageControl();
        return emit(Event(PAST_LUGGAGE,
                          clock,
                          &passenger));
    }

    if (luggageControl.isBusy()) {
        return pushLuggageQueue(passenger);
    }

    luggageControl.occupyWorker();
    emit(Event(PAST_LUGGAGE,
               clock + passenger.waitAtLuggage,
               &passenger));
}

void Airport::handlePastLuggage(Passenger& passenger) {
    if (!passenger.skippedLuggage) {
        luggageControl.releaseWorker();
        processLuggageQueue();
    }

    if (canSkipSecurityControl(passenger)) {
        passenger.skipSecurityControl();
        return emit(Event(PAST_SECURITY,
                          clock,
                          &passenger));
    }

    if (securityControl.isBusy()) {
        return pushSecurityQueue(passenger);
    }

    securityControl.occupyWorker();
    emit(Event(PAST_SECURITY,
               clock + passenger.waitAtSecurity,
               &passenger));
}

void Airport::handlePastSecurity(Passenger& passenger) {
    if (!passenger.skippedSecurity) {
        securityControl.releaseWorker();
        processSecurityQueue();
    }

    emit(Event(DEPARTED,
               clock,
               &passenger));
}

void Airport::handleDeparture(Passenger& passenger) {
    emit(Event(EXITED,
               clock,
               &passenger));
}

void Airport::handleExited(Passenger& passenger) {
}

void Airport::processLuggageQueue() {
    Passenger* passenger = popLuggageQueue();
    if (passenger == nullptr) return;

    luggageControl.occupyWorker();
    emit(Event(PAST_LUGGAGE,
               clock + passenger->waitAtLuggage,
               passenger));
}

void Airport::processSecurityQueue() {
    Passenger* passenger = popSecurityQueue();
    if (passenger == nullptr) return;

    securityControl.occupyWorker();
    emit(Event(PAST_SECURITY,
               clock + passenger->waitAtSecurity,
               passenger));
}

Passenger* Airport::popLuggageQueue() {
    // first fly first serve
    if (canCutInLine()) {
        if (pLuggageQueue.empty()) return nullptr;

        Passenger* p = pLuggageQueue.top();
        pLuggageQueue.pop();
        return p;
    }
    // first come first serve
    if (luggageQueue.empty()) return nullptr;

    Passenger* p = luggageQueue.front();
    luggageQueue.pop();
    return p;
}

Passenger* Airport::popSecurityQueue() {
    // first fly first serve
    if (canCutInLine()) {
        if (pSecurityQueue.empty()) return nullptr;

        Passenger* p = pSecurityQueue.top();
        pSecurityQueue.pop();
        return p;
    }
    // first come first serve
    if (securityQueue.empty()) return nullptr;

    Passenger* p = securityQueue.front();
    securityQueue.pop();
    return p;
}

void Airport::pushLuggageQueue(Passenger& passenger) {
    if (canCutInLine()) {
        return pLuggageQueue.push(&passenger);
    }
    return luggageQueue.push(&passenger);
}

void Airport::pushSecurityQueue(Passenger& passenger) {
    if (canCutInLine()) {
        return pSecurityQueue.push(&passenger);
    }
    return securityQueue.push(&passenger);
}

void Airport::emit(Event event) {
    events.push(event);
}

Report Airport::prepareReport(PassengerList& passengers) {
    unsigned long totalWait = 0;
    unsigned long missedFlights = 0;

    for (auto& passenger : passengers) {
        totalWait += passenger.getWaitedTime();
        if (passenger.missedFlight()) missedFlights++;
    }

    long double avgWaitingTime = (long double) totalWait / (long double) passengers.size();
    return {avgWaitingTime, missedFlights};
}

std::ostream& operator<<(std::ostream& os, const Airport& airport) {
    os << "luggageControl: " << airport.luggageControl << " securityControl: " << airport.securityControl;
    return os;
}

