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
    int clock = 0;
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

    void handleEntry(Passenger& passenger);

    void handlePastLuggage(Passenger& passenger);

    void handlePastSecurity(Passenger& passenger);

    void handleDeparture(Passenger& passenger);

    void handleExit(Passenger& passenger);

    void processSecurityQueue();

    void processLuggageQueue();

    Report prepareReport(PassengerList& passengers);

    inline bool securityControlBusy();

    inline bool luggageControlBusy();

    inline bool canSkipLuggageControl(Passenger& passenger);

    inline bool canSkipSecurityControl(Passenger& passenger);

    inline bool canGoFirst();

public:
    Airport(int securityCounters, int luggageCounters);

    void setFeatures(Feature features);

    Report run(PassengerList& passengers);

    ~Airport();

    friend std::ostream& operator<<(std::ostream& os, const Airport& airport);
};

#endif //PROJECT2_AIRPORT_H
