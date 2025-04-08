#include "RouteService.h"
#include <fstream>
#include <sstream>

RouteService::RouteService() {}

void RouteService::addFlight(const Flight& flight) {
    flights.push_back(flight);
}

void RouteService::addFlights(const std::vector<Flight>& newFlights) {
    flights.insert(flights.end(), newFlights.begin(), newFlights.end());
}

bool RouteService::loadFlightsFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open())
        return false;

    flights.clear();
    std::string line;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string origin, destination, priceStr;

        if (std::getline(iss, origin, ',') &&
            std::getline(iss, destination, ',') &&
            std::getline(iss, priceStr)) {

            try {
                uint32_t price = std::stoi(priceStr);
                flights.push_back(Flight(origin, destination, price));
            }
            catch (const std::exception&) {
                continue;
            }
        }
    }

    file.close();
    return true;
}

std::vector<Route> RouteService::findRoutes(const std::string& origin,
    const std::string& destination,
    uint32_t maxFlights
) const
{
    return Route::findPossibleRoutes(flights, origin, destination, maxFlights);
}

std::vector<Flight> RouteService::getFlights() const {
    return flights;
}
