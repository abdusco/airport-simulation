#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

#include "Airport.h"
#include "Passenger.h"
#include "Feature.h"

typedef std::pair<Airport, std::vector<Passenger>> ParsedInput;

ParsedInput parseInput(const std::string& filename) {
    std::ifstream infile(filename);

    // Read the first line for airport parameters
    int numPassenger, numLuggage, numSecurity;

    std::string line;
    getline(infile, line);
    std::istringstream lss(line);
    lss >> numPassenger >> numLuggage >> numSecurity;

    Airport airport(numSecurity, numLuggage);

    // remaining lines are passenger details
    PassengerList passengers;
    while (std::getline(infile, line) && numPassenger--) {
        int timeEntry, timeFlight, waitLuggage, waitSecurity;
        bool isVip, hasLuggage;
        char vip, luggage;

        std::istringstream ss(line);
        ss >> timeEntry >> timeFlight >> waitLuggage >> waitSecurity >> vip >> luggage;
        isVip = vip == 'V';
        hasLuggage = luggage == 'L';

        passengers.push_back(Passenger(
                timeEntry,
                timeFlight,
                waitLuggage,
                waitSecurity,
                isVip,
                hasLuggage
        ));
    }

    return {airport, passengers};
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cout << "Syntax: ./project2 <input_file> <output_file>" << std::endl;
        return 1;
    }

    ParsedInput input = parseInput(argv[1]);

    Airport airport = input.first;
    PassengerList passengers = input.second;

    Feature features[] = {
            FIRST_COME_FIRST_SERVE, // CASE 1
            FIRST_FLY_FIRST_SERVE, // CASE 2
            VIP_SKIP_SECURITY, // CASE 3
            FIRST_FLY_FIRST_SERVE | VIP_SKIP_SECURITY, // CASE 4
            ONLINE_TICKETING, // CASE 5
            FIRST_FLY_FIRST_SERVE | ONLINE_TICKETING, // CASE 6
            ONLINE_TICKETING | VIP_SKIP_SECURITY, // CASE 7
            FIRST_FLY_FIRST_SERVE | VIP_SKIP_SECURITY | ONLINE_TICKETING
    };

     std::ofstream outfile(argv[2], std::ios::app);

    for (const auto& feature : features) {
        airport.setFeatures(feature);
        Report report = airport.run(passengers);
        std::cout << report << std::endl;

         outfile << report << std::endl;
    }

    return 0;
}