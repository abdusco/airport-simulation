#ifndef PROJECT2_AIRPORT_H
#define PROJECT2_AIRPORT_H


#include <vector>
#include <queue>
#include <ostream>

#include "Feature.h"
#include "Passenger.h"
#include "ControlPoint.h"
#include "Event.h"
#include "Report.h"


typedef std::vector<Passenger> PassengerList;

class Airport {
private:
    int clock = 0;
    Feature features;
    std::priority_queue<Event> events;
    std::queue<Passenger*> luggageQueue;
    std::queue<Passenger*> securityQueue;
    ControlPoint luggageControl;
    ControlPoint securityControl;


    void dispatch(Event event);

    void acceptPassenger(Passenger& passenger);

    void handleEntry(Passenger& passenger);

    void handleLuggage(Passenger& passenger);

    void handleSecurity(Passenger& passenger);

    void handleDeparture(Passenger& passenger);

    void handleExit(Passenger& passenger);

    bool luggageReady();

    bool securityReady();

    void moveSecurityQueue();

    void moveLuggageQueue();

    Report prepareReport(PassengerList& passengers);

public:
    Airport(int securityCounters, int luggageCounters);

    void setFeatures(Feature features);

    Report run(PassengerList& passengers);

    ~Airport();

};


#endif //PROJECT2_AIRPORT_H
