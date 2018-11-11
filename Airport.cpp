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
            // handleExit(passenger);
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
        passenger.skipLuggage();
        return emit(Event(PAST_LUGGAGE,
                          clock,
                          &passenger));
    }

    if (luggageControlBusy()) {
        if (canGoFirst()) {
            return pLuggageQueue.push(&passenger);
        }
        return luggageQueue.push(&passenger);
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
        passenger.skipSecurity();
        return emit(Event(PAST_SECURITY,
                          clock,
                          &passenger));
    }

    if (securityControlBusy()) {
        if (canGoFirst()) {
            return pSecurityQueue.push(&passenger);
        }
        return securityQueue.push(&passenger);
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

void Airport::handleExit(Passenger& passenger) {
}

void Airport::processLuggageQueue() {
    Passenger* passenger = nullptr;
    if (features & FIRST_COME_FIRST_SERVE) {
        if (luggageQueue.empty()) return;

        passenger = luggageQueue.front();
        luggageQueue.pop();
    } else if (features & FIRST_FLY_FIRST_SERVE) {
        if (pLuggageQueue.empty()) return;

        passenger = pLuggageQueue.top();
        pLuggageQueue.pop();
    }

    luggageControl.occupyWorker();
    emit(Event(PAST_LUGGAGE,
               clock + passenger->waitAtLuggage,
               passenger));
}


void Airport::processSecurityQueue() {
    Passenger* passenger = nullptr;
    if (features & FIRST_COME_FIRST_SERVE) {
        if (securityQueue.empty()) return;

        passenger = securityQueue.front();
        securityQueue.pop();
    } else if (features & FIRST_FLY_FIRST_SERVE) {
        if (pSecurityQueue.empty()) return;

        passenger = pSecurityQueue.top();
        pSecurityQueue.pop();
    }

    securityControl.occupyWorker();
    emit(Event(PAST_SECURITY,
               clock + passenger->waitAtSecurity,
               passenger));
}

bool Airport::luggageControlBusy() {
    return luggageControl.busy;
}


bool Airport::securityControlBusy() {
    return securityControl.busy;
}

inline bool Airport::canSkipLuggageControl(Passenger& passenger) {
    return (features & ONLINE_TICKETING) && !passenger.hasLuggage;
}


inline bool Airport::canSkipSecurityControl(Passenger& passenger) {
    return (features & VIP_SKIP_SECURITY) && passenger.isVip;
}

bool Airport::canGoFirst() {
    return features & FIRST_FLY_FIRST_SERVE;
}


Airport::Airport(int numSecurity, int numLuggage)
        : luggageControl(ControlPoint(numLuggage)),
          securityControl(ControlPoint(numSecurity)) {
    this->features = FIRST_COME_FIRST_SERVE;
}

void Airport::setFeatures(Feature features) {
    this->features = features;
    if (!(features & FIRST_FLY_FIRST_SERVE)) {
        this->features = features | FIRST_COME_FIRST_SERVE;
    }
}

Airport::~Airport() {
    this->luggageQueue.empty();
    this->securityQueue.empty();
}

void Airport::emit(Event event) {
    events.push(event);
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

std::ostream& operator<<(std::ostream& os, const Airport& airport) {
    os << "luggageControl: " << airport.luggageControl << " securityControl: " << airport.securityControl;
    return os;
}

