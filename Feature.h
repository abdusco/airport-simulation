#ifndef PROJECT2_FEATURE_H
#define PROJECT2_FEATURE_H


#include <string>

enum Feature {
    FIRST_COME_FIRST_SERVE = 1 << 0,
    FIRST_FLY_FIRST_SERVE = 1 << 1,
    VIP_SKIP_SECURITY = 1 << 2,
    ONLINE_TICKETING = 1 << 3
};

inline Feature operator|(Feature a, Feature b) {
    { return static_cast<Feature>(static_cast<int>(a) | static_cast<int>(b)); }
}

inline Feature operator&(Feature a, Feature b) {
    { return static_cast<Feature>(static_cast<int>(a) & static_cast<int>(b)); }
}


#endif //PROJECT2_FEATURE_H
