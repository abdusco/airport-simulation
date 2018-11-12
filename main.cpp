#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

#include "Airport.h"
#include "models/Passenger.h"
#include "models/Feature.h"

typedef std::pair<Airport, std::vector<Passenger>> ParsedInput;

ParsedInput parseInput(const std::string& filename) {
    std::ifstream infile(filename);

    // Read the first line for airport parameters
    unsigned long numPassenger, numLuggage, numSecurity;

    std::string line;
    getline(infile, line);
    std::istringstream lss(line);
    lss >> numPassenger >> numLuggage >> numSecurity;

    Airport airport(numSecurity, numLuggage);

    // remaining lines are passenger details
    PassengerList passengers;
    while (std::getline(infile, line) && numPassenger--) {
        unsigned long tEntry, tFlight, waitLuggage, waitSecurity;
        bool isVip, hasLuggage;
        char vip, luggage;

        std::istringstream ss(line);
        ss >> tEntry >> tFlight >> waitLuggage >> waitSecurity >> vip >> luggage;
        isVip = vip == 'V';
        hasLuggage = luggage == 'L';

        passengers.push_back(Passenger(
                tEntry,
                tFlight,
                waitLuggage,
                waitSecurity,
                isVip,
                hasLuggage
        ));
    }

    return {airport, passengers};
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cout << "Syntax: ./project2 <input_file> <output_file> [verbose]" << std::endl;
        std::cout << "(add any character to the end to output results to the console)" << std::endl;
        return 1;
    }
    bool verbose = argc > 3;

    Feature features[] = {
            // TEST CASE 1
            FIRST_COME_FIRST_SERVE,
            // TEST CASE 2
            FIRST_FLY_FIRST_SERVE,
            // TEST CASE 3
            VIP_SKIP_SECURITY,
            // TEST CASE 4
            FIRST_FLY_FIRST_SERVE | VIP_SKIP_SECURITY,
            // TEST CASE 5
            ONLINE_TICKETING,
            // TEST CASE 6
            FIRST_FLY_FIRST_SERVE | ONLINE_TICKETING,
            // TEST CASE 7
            ONLINE_TICKETING | VIP_SKIP_SECURITY,
            // TEST CASE 8
            FIRST_FLY_FIRST_SERVE | VIP_SKIP_SECURITY | ONLINE_TICKETING
    };

    ParsedInput input = parseInput(argv[1]);

    Airport airport = input.first;
    PassengerList passengers = input.second;

    std::ofstream outfile(argv[2], std::ios::app);

    for (const auto& feature : features) {
        airport.setFeatures(feature);
        Report report = airport.run(passengers);

        outfile << report << std::endl;
        if (verbose) std::cout << report << std::endl;
    }

    return 0;
}