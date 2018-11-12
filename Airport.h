#ifndef PROJECT2_AIRPORT_H
#define PROJECT2_AIRPORT_H

#include <vector>
#include <queue>
#include <ostream>

#include "models/Feature.h"
#include "models/Passenger.h"
#include "models/ControlPoint.h"
#include "models/Event.h"
#include "models/Report.h"

typedef std::vector<Passenger> PassengerList;

struct PassengerLessImportant {
    // less than operator
    bool operator()(const Passenger* a, const Passenger* b) {
        return *a < *b;
    }
};

class Airport {
private:
    unsigned long clock = 0;
    Feature features;
    std::priority_queue<Event> events;
    std::queue<Passenger*> luggageQueue;
    std::queue<Passenger*> securityQueue;
    std::priority_queue<Passenger*, std::vector<Passenger*>, PassengerLessImportant> pSecurityQueue;
    std::priority_queue<Passenger*, std::vector<Passenger*>, PassengerLessImportant> pLuggageQueue;
    ControlPoint luggageControl;
    ControlPoint securityControl;

    void dispatchHandler(Event& event);

    void emit(Event event);

    void acceptPassenger(Passenger& passenger);

    void handleEntered(Passenger& passenger);

    void handlePastLuggage(Passenger& passenger);

    void handlePastSecurity(Passenger& passenger);

    void handleDeparture(Passenger& passenger);

    void handleExited(Passenger& passenger);

    void processSecurityQueue();

    void processLuggageQueue();

    Passenger* popLuggageQueue();

    Passenger* popSecurityQueue();

    Report prepareReport(PassengerList& passengers);

    bool canSkipLuggageControl(Passenger& passenger) {
        return features & ONLINE_TICKETING && !passenger.hasLuggage;
    }

    bool canSkipSecurityControl(Passenger& passenger) {
        return features & VIP_SKIP_SECURITY && passenger.isVip;
    }

    bool canCutInLine() {
        return features & FIRST_FLY_FIRST_SERVE;
    }

    void pushSecurityQueue(Passenger& passenger);

    void pushLuggageQueue(Passenger& passenger);

public:
    Airport(unsigned long securityCounters, unsigned long luggageCounters)
            : luggageControl(ControlPoint(luggageCounters)),
              securityControl(ControlPoint(securityCounters)) {
        this->features = FIRST_COME_FIRST_SERVE;
    }

    void setFeatures(Feature features) {
        this->features = features;
        if (!(features & FIRST_FLY_FIRST_SERVE)) {
            this->features = features | FIRST_COME_FIRST_SERVE;
        }
    }

    Report run(PassengerList& passengers);

    friend std::ostream& operator<<(std::ostream& os, const Airport& airport);
};

#endif //PROJECT2_AIRPORT_H
