#pragma once
#include <vector>
#include <string>
#include "Flight.h"
#include "Route.h"

class RouteService {
private:
    std::vector<Flight> flights;

public:
    RouteService();

    void addFlight(const Flight& flight);
    void addFlights(const std::vector<Flight>& newFlights);

    bool loadFlightsFromFile(const std::string& filename);
    std::vector<Route> findRoutes(
        const std::string& origin,
        const std::string& destination,
        uint32_t maxFlights = 0
    ) const;
    std::vector<Flight> getFlights() const;
};
