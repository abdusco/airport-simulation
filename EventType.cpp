#include "EventType.h"

std::string getEventTypeName(EventType type) {
    switch (type) {
        case ENTERED:
            return std::string("ENTERED");
        case EXITED:
            return std::string("EXITED");
        case PAST_LUGGAGE:
            return std::string("PAST_LUGGAGE");
        case PAST_SECURITY:
            return std::string("PAST_SECURITY");
        case DEPARTED:
            return std::string("DEPARTED");
    }
}
